# Spec Dojo — Sección 3: Mecanismo de tenant (JWT) y RLS detallado

## El cambio de fondo respecto a GymBase

Hoy el tenant se resuelve vía un header custom inyectado por `middleware.ts`, contra un hostname hardcodeado a `.gymbase.app`. Se reemplaza por **tenant y rol resueltos como JWT claims**, calculados una sola vez al emitir el token (login, refresh, o cambio de organización activa), no en cada request vía middleware.

### Cómo se llena el claim

Se activa `custom_access_token_hook()` en Supabase Auth (hoy existe como no-op) para inyectar en el JWT:

```json
{
  "app_metadata": {
    "org_id": "uuid-de-la-org-activa",
    "role": "owner" | "admin" | "member"
  }
}
```

Esto se recalcula en tres momentos: login, refresh de sesión, y explícitamente cuando el usuario cambia de organización activa (si pertenece a más de una) — este último caso dispara `supabase.auth.refreshSession()` desde el cliente tras la mutación de "organización activa".

### Por qué esto resuelve el problema del middleware/hostname
No depende de Next.js middleware ni de resolver hostname — el JWT ya trae la info, así que cualquier cliente (web, futuro mobile con Expo, Edge Function) lee el claim directo sin mecanismo propio. Esto es lo que te deja el camino libre para Play Store/App Store el día que lo necesites sin rehacer la resolución de tenant.

## Funciones helper (reemplazan a `get_user_role()` con colapso)

```sql
create or replace function auth.org_id() returns uuid as $$
  select (auth.jwt() -> 'app_metadata' ->> 'org_id')::uuid
$$ language sql stable;

create or replace function auth.role_in_org() returns text as $$
  select auth.jwt() -> 'app_metadata' ->> 'role'
$$ language sql stable;

create or replace function auth.is_admin_or_owner() returns boolean as $$
  select auth.role_in_org() in ('admin','owner')
$$ language sql stable;

create or replace function auth.is_owner() returns boolean as $$
  select auth.role_in_org() = 'owner'
$$ language sql stable;
```

`is_admin_or_owner()` reemplaza el patrón anterior que trataba a ambos como iguales para todo — ahora existe también `is_owner()` para las policies donde el owner tiene acceso exclusivo (finanzas).

## RLS por tabla — patrón base (se aplica a la mayoría)

```sql
-- Patrón estándar: todo scoped a la org del JWT
create policy "org_scoped_select" on <tabla>
  for select using (org_id = auth.org_id());

create policy "org_scoped_admin_write" on <tabla>
  for insert with check (org_id = auth.org_id() and auth.is_admin_or_owner());
```

Esto cubre directo: `organizations` (solo lectura de la propia), `membership_plans`, `martial_arts`, `ranks`, `gym_scheduled_classes`, `content`, `promotion_events`, `promotion_criteria`, `tournaments`, `tournament_divisions`.

## RLS con reglas específicas (no siguen el patrón base)

### `payment_proofs` y `subscriptions` — admin solo aprueba/rechaza, cero visibilidad económica
```sql
-- admin ve y actualiza comprobantes, pero no ve montos agregados ni reportes
create policy "payment_proofs_admin_review" on payment_proofs
  for select using (
    org_id_via_subscription(subscription_id) = auth.org_id()
    and auth.is_admin_or_owner()
  );

create policy "payment_proofs_admin_decide" on payment_proofs
  for update using (auth.is_admin_or_owner())
  with check (status in ('verified','rejected'));  -- admin solo puede mover a estos dos estados

-- subscriptions: admin gestiona el ciclo de vida operativo (activar/cancelar), owner ve todo incluyendo financiero
create policy "subscriptions_admin_operational" on subscriptions
  for select using (
    org_id = auth.org_id() and auth.is_admin_or_owner()
  );
-- Nota clave: esta policy da acceso a la fila, pero el campo de reportes agregados
-- (ingresos totales, dashboards financieros) NO se expone vía esta tabla directamente —
-- vive en una vista separada (`financial_summary`) con su propia policy exclusiva de owner:

create view financial_summary as
  select org_id, date_trunc('month', current_period_end) as period,
         sum(mp.price_cents) as revenue_cents
  from subscriptions s join membership_plans mp on mp.id = s.plan_id
  group by org_id, period;

create policy "financial_summary_owner_only" on financial_summary
  for select using (org_id = auth.org_id() and auth.is_owner());
```
Con esto el admin ve la fila de una suscripción (para gestionar el estado operativo y aprobar comprobantes), pero **ningún camino de RLS lo lleva a un total de ingresos o reporte** — eso solo existe en `financial_summary`, exclusiva de `owner`.

### `org_payment_connections` — exclusivo `owner`
```sql
create policy "billing_owner_only_select" on org_payment_connections
  for select using (org_id = auth.org_id() and auth.is_owner());
```

### `member_ranks` y `promotion_candidates` — lectura propia + admin
```sql
create policy "member_ranks_self_or_staff" on member_ranks
  for select using (
    member_id = auth.uid() or auth.is_admin_or_owner()
  );
```
Esto es lo que resuelve el hallazgo §9 (portal del miembro) a nivel de base — ya no hace falta `requireAdmin()` como única puerta. El server action `getMemberPromotionHistory` se reescribe para aceptar `member_id = auth.uid()` como caso válido, no solo admin.

### `member_fights` — visibilidad de dos niveles (confirmado en la conversación anterior)
```sql
create policy "fights_own_full_access" on member_fights
  for select using (member_id = auth.uid() or auth.is_admin_or_owner());

create policy "fights_public_feed" on member_fights
  for select using (
    org_id = auth.org_id()
    and (is_public = true or result = 'upcoming')
  );
```
Nota de implementación: en Postgres las policies del mismo `for select` se combinan con OR, así que el efecto neto es: el dueño y el staff ven todo; cualquier otro miembro de la org ve lo público + todo lo "upcoming" (el feed de "hay gente compitiendo" es upcoming sin importar `is_public`, como pediste).

### `push_subscriptions` — fix del hallazgo de la auditoría original
Hoy no tiene filtro de org, lo que en teoría permite que un push se dispare cruzado entre organizaciones si el `member_id` coincide en dos orgs distintas (multi-tenencia real). Se corrige:
```sql
create policy "push_subs_own_org_scoped" on push_subscriptions
  for all using (member_id = auth.uid() and org_id = auth.org_id())
  with check (member_id = auth.uid() and org_id = auth.org_id());
```
Requiere agregar `org_id` a la tabla si no existe ya (confirmar en la extracción si la columna existe pero sin policy, o si falta la columna misma — es una de las cosas a validar en el kickoff técnico antes de escribir la migración real).

### `sparring_challenges` — el challenger reporta, el rival solo acepta/rechaza
```sql
create policy "sparring_participants_only" on sparring_challenges
  for select using (
    challenger_id = auth.uid() or opponent_id = auth.uid() or auth.is_admin_or_owner()
  );

create policy "sparring_challenger_creates" on sparring_challenges
  for insert with check (challenger_id = auth.uid() and org_id = auth.org_id());

-- el rival únicamente responde a la invitación inicial
create policy "sparring_opponent_responds" on sparring_challenges
  for update using (opponent_id = auth.uid())
  with check (status in ('accepted','declined'));

-- el challenger es quien corre el cronómetro y carga resultados round por round tras aceptarse
create policy "sparring_challenger_records_results" on sparring_challenges
  for update using (challenger_id = auth.uid() and status = 'accepted')
  with check (status in ('completed','cancelled'));
```

Esto implica una tabla adicional para los resultados por round, que se agrega acá porque no estaba contemplada en el schema de la sección 2:

```sql
sparring_rounds (
  id uuid primary key default gen_random_uuid(),
  challenge_id uuid references sparring_challenges,
  round_number int not null,
  challenger_score int,
  opponent_score int,
  notes text,
  recorded_at timestamptz default now(),
  unique (challenge_id, round_number)
)

create policy "sparring_rounds_challenger_writes" on sparring_rounds
  for insert with check (
    exists (select 1 from sparring_challenges c
            where c.id = challenge_id and c.challenger_id = auth.uid() and c.status = 'accepted')
  );

create policy "sparring_rounds_participants_read" on sparring_rounds
  for select using (
    exists (select 1 from sparring_challenges c
            where c.id = challenge_id
            and (c.challenger_id = auth.uid() or c.opponent_id = auth.uid() or auth.is_admin_or_owner()))
  );
```

## Aclaración de flujos (para no confundir peleas profesionales con sparring amistoso)

| Aspecto | `member_fights` (profesional/oficial) | `sparring_challenges` (amistoso) |
|---|---|---|
| Quién carga la info | Admin/owner exclusivamente | El propio challenger |
| Quién puede iniciar | Admin (registra el evento/pelea) | Cualquier miembro (reta a otro) |
| Resultado | Lo llena el admin (`result`, `method`, `notes`) | Lo carga el challenger, round por round, tras aceptado |
| Rol del rival | N/A (puede ni ser miembro del dojo) | Solo acepta o rechaza la invitación inicial |

## Resumen de la matriz de acceso (para revisión rápida)

| Tabla | member (propio) | member (otros) | admin | owner |
|---|---|---|---|---|
| `member_ranks` | ✅ | ❌ | ✅ todos | ✅ todos |
| `promotion_candidates` | ✅ (solo si es él) | ❌ | ✅ | ✅ |
| `member_fights` | ✅ lectura | solo público + upcoming | ✅ lectura + escritura completa | ✅ lectura + escritura completa |
| `sparring_challenges` | ✅ si participa | ❌ | ✅ lectura (moderación) | ✅ lectura (moderación) |
| `sparring_rounds` | ✅ si participa (lectura); ✅ escritura solo si es challenger | ❌ | ✅ lectura | ✅ lectura |
| `payment_proofs` | ❌ | ❌ | ✅ revisar/aprobar/rechazar, sin montos agregados | ✅ completo |
| `financial_summary` (vista de reportes) | ❌ | ❌ | ❌ | ✅ único acceso |
| `org_payment_connections` | ❌ | ❌ | ❌ | ✅ |

## Historial agregado entre dos miembros — vista derivada

Nace de `sparring_challenges` con `status = 'completed'`: cuántas veces se han enfrentado dos miembros y con qué resultado, para que cualquiera de los dos pueda consultar su historial cruzado (ej. "llevo 3-1 contra Fulano").

```sql
create view sparring_head_to_head as
  select
    least(challenger_id, opponent_id) as member_a,
    greatest(challenger_id, opponent_id) as member_b,
    martial_art_id,
    count(*) as total_matches,
    count(*) filter (where winner_id = least(challenger_id, opponent_id)) as wins_a,
    count(*) filter (where winner_id = greatest(challenger_id, opponent_id)) as wins_b
  from sparring_challenges
  where status = 'completed'
  group by least(challenger_id, opponent_id), greatest(challenger_id, opponent_id), martial_art_id;
```

Esto requiere agregar `winner_id uuid references profiles` a `sparring_challenges` (se determina a partir de la suma de `sparring_rounds` al cerrar el reto, calculado por el mismo server action que el challenger dispara al finalizar).

```sql
create policy "head_to_head_own_matches" on sparring_head_to_head
  for select using (member_a = auth.uid() or member_b = auth.uid() or auth.is_admin_or_owner());
```

La escritura de resultados por round se mantiene exclusiva del challenger (como ya quedó definido) — esta vista es solo de lectura y se recalcula automáticamente al consultarse, no requiere confirmación adicional del rival.

## Pendiente para la siguiente sección
Sección 4: contrato de theming dinámico (tokens por tenant) — cómo `theme.config.ts` de Dojo Shoto se traduce al sistema nuevo sin perder lo que ya funciona visualmente.
