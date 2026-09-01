---
proyecto: CoreBase
tema: Seguridad — resolución de tenant vía JWT, helpers y RLS
fecha: 2026-08-28
tipo: documentacion
estado: v1.0 — corrige los 4 bloqueantes de SQL del spec 03
tags: [corebase, seguridad, rls, jwt, supabase, owasp]
---

# Seguridad — tenant vía JWT y RLS

Ver también: [[Proyectos/CoreBase/arquitectura|arquitectura.md]] · [[Proyectos/CoreBase/schema|schema.md]] · [[Proyectos/DojoBase/schema-dojo|schema-dojo.md]] · [[Proyectos/CoreBase/revision-critica-specs|Revisión crítica]]

> Reemplaza a `_fuentes/03-spec-jwt-rls.md`. El spec original tenía cuatro cosas que **no compilan o no protegen** en Postgres/Supabase; están corregidas acá y marcadas con **▲**.

## 1. El cambio de fondo respecto a GymBase v1

En v1 el tenant se resuelve con un header HTTP custom (`x-org-id`) que inyecta el middleware de Next.js, llamando a un RPC que resuelve el hostname contra `LIKE '%.gymbase.app'` hardcodeado. Toda la RLS depende de eso: sin ese middleware exacto, Supabase deniega todo **en silencio** (devuelve `NULL`, no error).

Acá el tenant y el rol son **claims del JWT**, calculados al emitir el token. No depende de Next.js: cualquier cliente futuro (mobile, Edge Function, script) lee el claim directo. Es también lo que permite que onboardear un tenant nuevo sea un insert y no un deploy.

## 2. Cómo se llena el claim

Se activa `custom_access_token_hook()` en Supabase Auth para inyectar:

```json
{ "app_metadata": { "org_id": "uuid", "role": "owner|admin|member" } }
```

El hook lee `profiles.active_org_id` y busca el rol correspondiente en `org_members` (con `status = 'active'`). Se recalcula en tres momentos: login, refresh de sesión, y cambio explícito de organización activa.

**▲ Corrección B4:** el spec decía "se recalcula cuando el usuario cambia de organización activa" pero nunca definió dónde vive ese dato — el hook solo recibe el user_id. Ahora existe `profiles.active_org_id`. El flujo de cambio de org es: `UPDATE profiles SET active_org_id = ...` → `supabase.auth.refreshSession()` desde el cliente.

**Si el usuario no tiene `active_org_id`** (recién registrado, o su única membresía fue suspendida), el hook no inyecta claims y el usuario queda sin acceso a datos de ninguna organización — que es el comportamiento correcto, y hay que manejarlo en la UI con una pantalla de "no perteneces a ninguna organización" en vez de una pantalla en blanco.

## 3. El desfase del claim, y qué se hace con él

**▲ Corrección B5 — el spec no lo mencionaba.** Mover el rol al JWT tiene un costo real: **un admin degradado sigue siendo admin hasta que su token expire**. Con el TTL por defecto de Supabase (1 hora), eso es hasta una hora de acceso indebido. Mitigaciones, las tres:

1. **TTL del access token a 15 minutos.** Acota la ventana sin costo perceptible para el usuario (el refresh es transparente).
2. **Refresh forzado tras cualquier mutación de rol o de estado de membresía**, disparado desde el server action que la hace.
3. **Para lo verdaderamente sensible — finanzas y `org_payment_connections` — la comprobación no usa el claim**, consulta `org_members` en vivo. Son tres tablas y un puñado de operaciones al día: el costo del query vale el cierre del hueco.

Esto se documenta acá porque es una decisión consciente, no un descuido: el claim es la vía rápida para el 95% de los accesos, y las operaciones que justifican pagar un query lo pagan.

## 4. Funciones helper

**▲ Corrección B3:** el spec las definía en el schema `auth`. **Supabase no permite crear funciones ahí** — es un schema reservado, propiedad de la plataforma, y se sobrescribe en upgrades. Van todas a `public`.

```sql
create or replace function public.org_id() returns uuid
  language sql stable as $$
  select nullif(auth.jwt() -> 'app_metadata' ->> 'org_id', '')::uuid
$$;

create or replace function public.role_in_org() returns text
  language sql stable as $$
  select auth.jwt() -> 'app_metadata' ->> 'role'
$$;

create or replace function public.is_admin_or_owner() returns boolean
  language sql stable as $$
  select public.role_in_org() in ('admin','owner')
$$;

create or replace function public.is_owner() returns boolean
  language sql stable as $$
  select public.role_in_org() = 'owner'
$$;

-- Verificación en vivo, para operaciones sensibles que no confían en el claim (§3)
create or replace function public.is_owner_live() returns boolean
  language sql stable security definer set search_path = public as $$
  select exists (
    select 1 from org_members m
    join profiles p on p.id = m.user_id
    where m.user_id = auth.uid()
      and m.org_id = p.active_org_id
      and m.role = 'owner'
      and m.status = 'active'
  )
$$;

revoke execute on function public.is_owner_live() from anon;
```

**▲ Hallazgo heredado de la auditoría:** en v1 los helpers `SECURITY DEFINER` son ejecutables por `anon` vía `/rest/v1/rpc/*`. Hoy es inofensivo porque devuelven `NULL`, pero es superficie gratuita. Regla: **`revoke execute ... from anon` en toda función `SECURITY DEFINER` que no tenga que ser pública.**

Se elimina el colapso de v1, donde `get_user_role()` devolvía `admin` para los owners y dejaba rama muerta en toda policy `= ANY(['admin','owner'])`.

## 5. Patrón base de RLS

```sql
alter table <tabla> enable row level security;

create policy "org_scoped_select" on <tabla>
  for select using (org_id = public.org_id());

-- Tres policies, no una `for all`: `for all` incluye SELECT, así que
-- cualquier lectura evalúa esta política Y `org_scoped_select` (ambas
-- permisivas, se OR-ean) — trabajo doble en cada SELECT cuando la de
-- lectura ya cubre a todo el mundo en el dojo, staff incluido.
create policy "org_scoped_staff_insert" on <tabla>
  for insert with check (org_id = public.org_id() and public.is_admin_or_owner());

create policy "org_scoped_staff_update" on <tabla>
  for update using (org_id = public.org_id() and public.is_admin_or_owner())
  with check (org_id = public.org_id() and public.is_admin_or_owner());

create policy "org_scoped_staff_delete" on <tabla>
  for delete using (org_id = public.org_id() and public.is_admin_or_owner());
```

**▲ Corregido tras DOJO-7:** la primera versión de esta sección tenía
`org_scoped_staff_write` como una sola policy `for all`, que es exactamente
el anti-patrón de arriba. `disciplines`/`ranks`/`member_ranks` la copiaron
tal cual y el advisor de performance de Supabase lo marcó
(`multiple_permissive_policies`) recién al cerrar el módulo — migración
`dojo_optimizacion` (017) la separó en insert/update/delete. Nada de esto
afecta a quién se le permite qué, solo cuántas veces Postgres evalúa cada
política. (`public.org_id()`/`public.is_admin_or_owner()` son funciones
`stable` y no necesitan el envoltorio `(select ...)` — eso es solo para una
llamada cruda a `auth.uid()`/`auth.jwt()` en el cuerpo de una policy, ver
`dojo_member_ranks_rls_initplan`, migración 015.)

Cubre directo: `organizations` (lectura de la propia), `membership_plans`, `class_types`, `scheduled_classes`, `content_categories`, `content`, `challenges`, y del lado vertical `disciplines`, `ranks`, `promotion_events`, `promotion_criteria`, `tournaments`, `tournament_divisions`.

**▲ Nota heredada:** en v1 `organizations` no tenía policy de SELECT para `member` — un miembro no podía leer su propia organización por RLS estándar. Acá el patrón base lo cubre; hay que verificar que no se repita el parche de conseguir logo/nombre por una vía alterna.

## 6. Finanzas — el punto más sensible del producto

### ▲ B1 — No se pueden crear policies RLS sobre vistas

El spec definía `create policy "financial_summary_owner_only" on financial_summary`. **Postgres no soporta RLS en vistas**: `CREATE POLICY` sobre una vista falla, y una vista corre con los privilegios de su dueño ignorando por defecto el RLS de las tablas base. Ese fragmento no habría llegado a aplicarse.

### ▲ B2 — Y aunque se pudiera, no ocultaba nada

El admin tiene SELECT sobre `subscriptions` y `membership_plans` por el patrón base. Con eso suma `price_cents` él mismo desde PostgREST. El control era teatro.

Y no es arreglable sin romper el flujo: el admin es quien aprueba los comprobantes SINPE, **y el comprobante muestra el monto en la imagen que tiene que mirar para aprobarlo**.

### La solución adoptada

El requisito se reescribe con honestidad (decisión 3) y se implementa con una **función `SECURITY DEFINER` con guarda explícita**, no con una vista:

```sql
create or replace function public.get_financial_summary(p_from date, p_to date)
returns table (period date, revenue_cents bigint, active_subs int)
language plpgsql security definer set search_path = public as $fn$
begin
  if not public.is_owner_live() then
    raise exception 'forbidden' using errcode = '42501';
  end if;

  return query
    select date_trunc('month', s.current_period_end)::date,
           sum(mp.price_cents)::bigint,
           count(*)::int
    from subscriptions s
    join membership_plans mp on mp.id = s.plan_id
    where s.org_id = (select active_org_id from profiles where id = auth.uid())
      and s.current_period_end between p_from and p_to
    group by 1 order by 1;
end $fn$;

revoke execute on function public.get_financial_summary(date, date) from anon, authenticated;
grant execute on function public.get_financial_summary(date, date) to authenticated;
```

El control queda **explícito, en un solo lugar y auditable**, en vez de repartido en policies. Usa `is_owner_live()` (§3) porque es exactamente el caso que justifica no confiar en el claim.

```sql
-- org_payment_connections: exclusivo owner, verificación en vivo
create policy "payment_connections_owner_only" on org_payment_connections
  for all using (org_id = public.org_id() and public.is_owner_live())
  with check (org_id = public.org_id() and public.is_owner_live());
```

### Comprobantes y suscripciones

```sql
-- El miembro ve su propio comprobante y su estado (HU-17b)
create policy "proofs_own_read" on payment_proofs
  for select using (
    org_id = public.org_id()
    and (exists (select 1 from subscriptions s
                 where s.id = subscription_id and s.member_id = auth.uid())
         or public.is_admin_or_owner())
  );

create policy "proofs_member_upload" on payment_proofs
  for insert with check (
    org_id = public.org_id()
    and exists (select 1 from subscriptions s
                where s.id = subscription_id and s.member_id = auth.uid())
    and status = 'pending'          -- el miembro no puede autoaprobarse
  );

-- El admin decide, y solo puede mover a estos dos estados
create policy "proofs_staff_decide" on payment_proofs
  for update using (org_id = public.org_id() and public.is_admin_or_owner())
  with check (status in ('verified','rejected'));
```

## 7. Vistas derivadas — cómo se hacen bien

Para lecturas no sensibles se usa **`security_invoker`**, que sí existe y sí aplica el RLS de las tablas base con el usuario que consulta:

```sql
create view sparring_head_to_head with (security_invoker = on) as
  select ... from sparring_challenges where status = 'completed' and opponent_confirmed ...;
```

No lleva `CREATE POLICY` (no se puede): hereda el RLS de `sparring_challenges`, que ya limita a participantes y staff. Esa es la razón por la que la vista es segura.

**Regla general para el proyecto:** vista con `security_invoker` para lo que puede heredar RLS; función `SECURITY DEFINER` con guarda explícita para lo que necesita un permiso que las tablas base no expresan (finanzas). Nunca `CREATE POLICY` sobre una vista.

## 8. Acceso propio + staff

```sql
create policy "member_ranks_self_or_staff" on member_ranks
  for select using (member_id = auth.uid() or public.is_admin_or_owner());

create policy "promotion_candidates_self_or_staff" on promotion_candidates
  for select using (
    org_id = public.org_id()
    and (member_id = auth.uid() or public.is_admin_or_owner())
  );

-- ▲ B7: faltaba, y HU-14 (la pantalla nueva del miembro) depende de esto
create policy "promotion_scores_self_or_staff" on promotion_scores
  for select using (
    org_id = public.org_id()
    and (public.is_admin_or_owner()
         or exists (select 1 from promotion_candidates c
                    where c.id = candidate_id and c.member_id = auth.uid()))
  );
```

Esto resuelve a nivel de base el hallazgo del portal del miembro: ya no hace falta `requireAdmin()` como única puerta. El server action que devuelve el historial de promociones acepta `member_id = auth.uid()` como caso válido.

## 9. Notificaciones

```sql
-- ▲ B7: el spec definía la tabla sin ninguna policy
create policy "notifications_own" on notifications
  for select using (recipient_id = auth.uid() and org_id = public.org_id());

create policy "notifications_own_mark_read" on notifications
  for update using (recipient_id = auth.uid() and org_id = public.org_id())
  with check (recipient_id = auth.uid());
```

La inserción es exclusiva del servidor (service role) vía `emitNotification` — ningún cliente inserta notificaciones.

```sql
-- ▲ Fix del hallazgo de la auditoría: en v1 no filtra por org
create policy "push_subs_own_org_scoped" on push_subscriptions
  for all using (member_id = auth.uid() and org_id = public.org_id())
  with check (member_id = auth.uid() and org_id = public.org_id());
```

## 10. Sparring

```sql
create policy "sparring_participants_read" on sparring_challenges
  for select using (
    org_id = public.org_id()
    and (challenger_id = auth.uid() or opponent_id = auth.uid() or public.is_admin_or_owner())
  );

create policy "sparring_challenger_creates" on sparring_challenges
  for insert with check (
    challenger_id = auth.uid() and org_id = public.org_id()
    and opponent_id <> auth.uid()          -- ▲ nada impedía retarse a sí mismo
  );

-- El rival responde a la invitación
create policy "sparring_opponent_responds" on sparring_challenges
  for update using (opponent_id = auth.uid() and status = 'pending')
  with check (status in ('accepted','declined'));

-- El challenger carga resultados tras la aceptación
create policy "sparring_challenger_records" on sparring_challenges
  for update using (challenger_id = auth.uid() and status = 'accepted')
  with check (status in ('completed','cancelled'));

-- ▲ HU-09b: cualquiera de los dos cancela antes de completarse
create policy "sparring_either_cancels" on sparring_challenges
  for update using (
    (challenger_id = auth.uid() or opponent_id = auth.uid())
    and status in ('pending','accepted')
  ) with check (status = 'cancelled');
```

**▲ Corrección D2 — confirmación del rival (decisión 4).** El spec dejaba que el challenger cargara el resultado y que el head-to-head lo contara sin que el rival pudiera objetar. Como el head-to-head es explícitamente social ("llevo 3-1 contra Fulano"), un marcador auto-reportado no sobrevive al primer conflicto entre dos alumnos. Se agrega:

```sql
alter table sparring_challenges add column opponent_confirmed boolean default false;

create policy "sparring_opponent_confirms" on sparring_challenges
  for update using (opponent_id = auth.uid() and status = 'completed')
  with check (opponent_confirmed = true);
```

Y `sparring_head_to_head` cuenta **solo los confirmados**. Una columna, un botón y un `where` — y desaparece la categoría entera de problema.

## 11. Peleas oficiales — visibilidad de dos niveles

**▲ Corrección B6 (decisión 6).** El spec decía en prosa "por defecto el historial completo es privado del miembro" pero definía `is_public default true`, dejando todo el historial de todos público para toda la organización. Se resuelve a favor de la prosa:

```sql
alter table member_fights alter column is_public set default false;

create policy "fights_own_or_staff" on member_fights
  for select using (
    org_id = public.org_id()
    and (member_id = auth.uid() or public.is_admin_or_owner())
  );

create policy "fights_org_feed" on member_fights
  for select using (
    org_id = public.org_id()
    and (is_public = true or result = 'upcoming')
  );
```

Las policies del mismo `FOR SELECT` se combinan con OR: el dueño y el staff ven todo; el resto ve lo publicado más **todo lo `upcoming`** sin importar `is_public` — el feed de "hay gente compitiendo" es el mecanismo social y se mantiene abierto a propósito.

El registro de peleas oficiales es escritura exclusiva de admin/owner (RF-09); el miembro solo lee y decide publicar el resultado.

## 12. Matriz de acceso

| Tabla / recurso | member (propio) | member (otros) | admin | owner |
|---|---|---|---|---|
| `member_ranks` | ✅ | ❌ | ✅ | ✅ |
| `promotion_candidates` | ✅ | ❌ | ✅ | ✅ |
| `promotion_scores` | ✅ (su desglose) | ❌ | ✅ | ✅ |
| `member_fights` | ✅ | publicado + `upcoming` | ✅ lectura y escritura | ✅ lectura y escritura |
| `sparring_challenges` | ✅ si participa | ❌ | ✅ lectura (moderación) | ✅ lectura |
| `sparring_rounds` | ✅ si participa; escribe solo el challenger | ❌ | ✅ lectura | ✅ lectura |
| `payment_proofs` | ✅ el suyo | ❌ | ✅ aprobar/rechazar (ve el monto de la fila) | ✅ |
| `get_financial_summary()` | ❌ | ❌ | ❌ | ✅ único acceso |
| `org_payment_connections` | ❌ | ❌ | ❌ | ✅ |
| `notifications` | ✅ | ❌ | ❌ | ❌ |

## 13. Checklist de seguridad por PR (OWASP 2025 aplicado a este proyecto)

El agente de seguridad revisa **antes de mergear**, no como auditoría final:

- **Control de acceso roto.** Ninguna mutación de estado depende de UI oculta: promociones, resultados de sparring y decisiones de pago validan el estado actual en el server action (RNF-01). Ocultar un botón no es un control.
- **Exposición de datos.** `get_financial_summary()` y `org_payment_connections` inalcanzables para `admin`, verificado con un test que se autentica como admin y espera el error.
- **Aislamiento de tenant.** Toda tabla nueva tiene `org_id`, RLS habilitada y policy con `org_id = public.org_id()`. Sin excepciones — una tabla sin RLS en un producto multi-tenant es una fuga, no un pendiente.
- **Superficie de RPC.** Toda función `SECURITY DEFINER` con `search_path` fijo y `execute` revocado a `anon` salvo que deba ser pública.
- **Inyección.** Filtros de búsqueda de contenido y clases parametrizados, nunca concatenados.
- **Sesión.** TTL de 15 minutos, refresh forzado tras cambios de rol, protección de contraseñas filtradas **habilitada** en Auth (en v1 está deshabilitada).
- **Utilidades de test fuera de producción.** En v1 quedó una función que resuelve el user id por email para los e2e. No se empaqueta nada así en CoreBase.

## 14. Tests de RLS

Un archivo por tabla sensible que se autentique como `member`, `admin` y `owner` y verifique la matriz de §12 — incluyendo los casos negativos, que son los que importan: que el admin **falle** al llamar `get_financial_summary()`, que un miembro **no vea** el sparring de otros dos, que un miembro de la org A **no vea nada** de la org B.

Esto es lo que evita que una migración futura abra un hueco en silencio, que es exactamente cómo se llega a los hallazgos que tiene v1 hoy.
