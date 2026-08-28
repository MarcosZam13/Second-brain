---
proyecto: MemberBase
tema: revisión crítica del paquete de specs 1-9
fecha: 2026-08-28
tipo: analisis
estado: pendiente de decisiones
tags: [memberbase, corebase, dojobase, arquitectura, revision]
---

# Revisión crítica — specs 1-9 de DojoBase/CoreBase

Ver también: [[Proyectos/MemberBase/README|MemberBase]] · [[Proyectos/DojoBase/README|DojoBase]] · [[Proyectos/GymBase/README|GymBase]]

Revisión de los 9 documentos de spec (`_fuentes/`) contra el código real de GymBase (`ProyectosPersonales/Gymbase`), su `auditoria-gymbase.md`, `extraccion-tecnica-dojo.md` y `Context/_CONTEXTO-IA.md`.

**Veredicto general:** el paquete de specs es sólido en dirección arquitectónica (separar core de vertical, JWT en vez de header, theming a tabla) y las correcciones de bugs heredados están bien identificadas. Los problemas están en **tres frentes**: (a) SQL que no funciona como está escrito, (b) el schema cubre ~70% de las historias de usuario, y (c) el encuadre del proyecto — el cronograma asume que esto es construcción nueva cuando en realidad es una migración de un cliente en producción.

Severidad: 🔴 bloqueante (rompe si se implementa tal cual) · 🟠 gap (falta algo que las HU exigen) · 🟡 criterio (decisión a revisar, no está roto)

---

## A. Encuadre del proyecto (lo más importante)

### A1 🔴 Dojo Shoto ya está en producción sobre GymBase — esto es una migración, no un producto nuevo

Los specs hablan de "primer cliente confirmado: Dojo Shoto" como si fuera un lanzamiento. Pero el `git log` de GymBase muestra tanda tras tanda de bugs del sensei, franjas, familias, planes: **Dojo Shoto es un cliente vivo, usando el producto hoy**, con datos reales en el proyecto Supabase `vwkxrjnxfjfzobzzoagj`.

Consecuencias que ningún spec cubre:

- DojoBase necesita un **proyecto Supabase nuevo** (el schema es incompatible: `member_ranks` vs `org_member_ranks`, JWT vs header `x-org-id`, `organizations` limpia). Eso no está decidido en ninguna parte.
- Existe un **plan de migración de datos** obligatorio (miembros, rangos, pagos, historial de peleas de Dojo Shoto) que no aparece en el cronograma de 8 semanas.
- Hasta que ese corte pase, **hay dos productos que mantener** — cualquier bug del sensei durante las 8 semanas se arregla en GymBase v1, no en DojoBase.

**Recomendación:** agregar semana 0 (plan de corte + migración de datos) y semana 9 (migración real + acompañamiento), y declarar congelamiento de features en GymBase v1 durante el período (solo fixes).

### A2 🟡 El objetivo de negocio real no es Dojo Shoto, es el segundo dojo

Dojo Shoto ya tiene todo lo que las 23 HU describen — funcionando. Reescribirlo no le entrega valor nuevo a él. Lo que hace vendible el producto es lo que hoy **no** se puede hacer: onboardear un dojo nuevo sin un deploy y sin un PR (hoy es `clients/gymbase/<tenant>/theme.config.ts` + build con `NEXT_PUBLIC_GYM_CLIENT`).

Eso reordena la prioridad. Lo que desbloquea vender:

1. Resolución de tenant en runtime (JWT) — spec 3.
2. `tenant_themes` en tabla — spec 4.
3. Alta de organización + invitación de miembros (HU-22, RF-19/20) — hoy es manual y ni siquiera está en el schema.

Eso es el producto mínimo vendible. Todo lo demás (sparring, promociones, torneos, peleas) ya existe y es **porte con limpieza**, no diseño. Sugiero re-cortar el cronograma alrededor de esto en vez de alrededor de módulos.

### A3 🟡 8 semanas es optimista por un factor de ~2

23 HU + monorepo nuevo + design system nuevo + billing con pasarela + migración de un cliente vivo, en solo. GymBase tardó mucho más en llegar a los mismos módulos. No es razón para no empezar — sí para que el cronograma diga qué se cae primero si hay atraso. Corte duro sugerido: torneos (ya fuera de alcance), grupos familiares (HU-23) y challenges (HU-16) son los tres primeros candidatos a v1.1.

---

## B. SQL que no funciona como está escrito

### B1 🔴 No se pueden crear policies RLS sobre vistas

El spec 3 define `create policy "financial_summary_owner_only" on financial_summary` y `create policy "head_to_head_own_matches" on sparring_head_to_head`. **Postgres no soporta RLS en vistas** — `CREATE POLICY` sobre una vista falla. Una vista corre con los privilegios de su dueño y por defecto *ignora* el RLS de las tablas base.

Arreglo correcto (dos opciones):

```sql
-- Opción A: vista security_invoker (PG15+, disponible en Supabase) + predicado embebido
create view financial_summary with (security_invoker = on) as
  select ... from subscriptions s join membership_plans mp on ...
  where s.org_id = public.org_id() and public.is_owner()
  group by ...;

-- Opción B (preferida para finanzas): función SECURITY DEFINER con guarda explícita
create function public.get_financial_summary(p_from date, p_to date)
returns table (...) language plpgsql security definer as $func$
begin
  if not public.is_owner() then raise exception 'forbidden'; end if;
  return query select ...;
end $func$;
```

Prefiero **B para `financial_summary`** (el control queda explícito y auditable) y **A para `sparring_head_to_head`** (es lectura social, no sensible).

### B2 🔴 `financial_summary` no oculta nada — el control es teatro

Aunque B1 se arregle: el admin tiene SELECT sobre `subscriptions` y sobre `membership_plans` (patrón base, org-scoped). Con eso, desde PostgREST hace `select price_cents` y suma él mismo. RF-15/RF-16 y HU-18/HU-19 ("admin sin ver montos agregados") **no son exigibles** con este schema.

Para que fuera real habría que negarle al admin la columna `membership_plans.price_cents` y `payment_proofs.amount_cents` — pero el admin es justamente quien aprueba el comprobante SINPE, y **el comprobante muestra el monto en la imagen**. El control es inalcanzable por diseño del flujo.

**Recomendación:** reescribir el requisito con honestidad, en vez de construir un control que no se sostiene:

> El admin no tiene acceso a *reportes ni dashboards* de ingresos, ni a `org_payment_connections`. Sí ve el monto de la fila individual que está aprobando, porque el flujo de verificación SINPE lo requiere.

Si de verdad se quiere el admin ciego a montos, hay que cambiar el flujo: que el owner apruebe los comprobantes, o que el admin apruebe "identidad del pago" contra un monto esperado que el sistema no le muestra. Eso es una decisión de producto, no de RLS.

### B3 🔴 No se pueden crear funciones en el schema `auth` de Supabase

El spec 3 define `auth.org_id()`, `auth.role_in_org()`, `auth.is_admin_or_owner()`, `auth.is_owner()`. El schema `auth` es propiedad de Supabase, está reservado y se sobrescribe en upgrades de plataforma. Van todas a `public` (`public.org_id()`, etc.), revocando `execute` a `anon` donde no corresponda — la auditoría ya marcó que hoy los helpers `SECURITY DEFINER` son invocables por `anon` vía `/rest/v1/rpc/*`.

### B4 🟠 No está definido dónde vive la "organización activa"

El spec 3 dice que `custom_access_token_hook()` inyecta `org_id` en el JWT y que se recalcula "cuando el usuario cambia de organización activa". Pero el hook solo recibe el user_id — **necesita leer de algún lado cuál es la org activa**. No existe esa columna en el schema. Hace falta `profiles.active_org_id uuid references organizations` (o una tabla `user_active_org`), y el flujo de cambio de org es: UPDATE de esa columna → `supabase.auth.refreshSession()`.

### B5 🟡 El JWT se queda viejo: un admin degradado sigue siendo admin hasta que expire su token

Consecuencia directa e inevitable de mover el rol al claim. Con el TTL por defecto de Supabase (1h), degradar a alguien tarda hasta una hora en surtir efecto en RLS. Mitigaciones a decidir explícitamente en el spec (hoy no se mencionan):

- bajar el TTL del access token (15 min es razonable para este producto),
- forzar refresh desde el cliente tras cualquier mutación de rol,
- y para las operaciones verdaderamente sensibles (finanzas, `org_payment_connections`), que la policy consulte `org_members` en vivo en vez del claim — vale el costo del query en 3 tablas.

### B6 🟠 `member_fights`: la prosa y el SQL se contradicen

El spec dice "por defecto el historial completo es privado del miembro", pero define `is_public boolean default true` y la policy `fights_public_feed` con `is_public = true or result = 'upcoming'`, OR'd con la otra. Efecto real: **todo el historial de peleas de todos es público para toda la org por defecto**. Hay que elegir uno de los dos y corregir el otro. Recomiendo `default false` + `upcoming` siempre visible (que es el feed social que se quiere), y un toggle "publicar en el feed" cuando el miembro carga un resultado.

### B7 🟠 Faltan policies para `promotion_scores` y `notifications`

- `promotion_scores` no tiene RLS en el spec 3 y **HU-14 (la pantalla nueva estrella) depende de que el candidato lea su propio desglose por criterio**. La extracción ya lo había marcado (§5.13). Necesita: `select using (exists (select 1 from promotion_candidates c where c.id = candidate_id and (c.member_id = auth.uid() or public.is_admin_or_owner())))`.
- `notifications` se define en el spec 5 sin ninguna policy. Necesita `recipient_id = auth.uid() and org_id = public.org_id()`.

Además `promotion_scores` y `promotion_criteria` no tienen `org_id` — dependen de un JOIN a `promotion_events` para saber su tenant. Es correcto normalizado pero encarece cada policy; considerar denormalizar `org_id` en las tablas hijas (es lo que hace el resto del schema).

---

## C. El schema no cubre las historias de usuario

El spec 2 define ~25 tablas. Las 23 HU + 22 RF exigen bastante más. **Gaps concretos, todos 🟠:**

| Falta | Lo exige |
|---|---|
| `dojo_org_settings` (mencionada en spec 1, nunca definida — SINPE, ventana de cancelación, días de expiración de sparring) | spec 1, RF-06b, HU-17 |
| `family_groups` + FK en `org_members`/`subscriptions` | HU-23, RF-21 |
| `challenges` / `challenge_participants` / `challenge_progress` | HU-16, RF-14 |
| `content_categories` (carpetas). Hoy solo hay `content.category_id` apuntando a la nada | HU-15, RF-13 |
| `content_favorites` | HU-15b |
| `org_invitations` (código de invitación / alta directa) | HU-22, RF-20 |
| `membership_reminders_sent` (idempotencia del recordatorio) | HU-20, RF-17 |
| `push_subscriptions` — el spec 5 la referencia como "[core, ya existe]" pero nunca se define en el spec 2 | RF-08 |
| `gym_scheduled_classes.instructor_id`, `.is_cancelled`, `.is_private`, `.allowed_plan_ids` | RF-03b, RF-04, HU-02c |
| `class_reservations` sin `UNIQUE(class_id, member_id)` — nada impide inscribirse dos veces | RF-03 |
| `sparring_challenges.winner_id` — se menciona en el spec 3 al pasar ("esto requiere agregar"), no está en el spec 2 | RF-07 |
| `promotion_events` sin estado o mecanismo de reapertura | HU-13b, RF-11 |

**Recomendación:** cerrar el schema contra las HU una por una antes de escribir la primera migración. Es media jornada y evita 6 migraciones correctivas en las semanas 4-7.

---

## D. Reglas de negocio que se rompen solas

### D1 🟠 `attended = true` automático al inscribirse hace inflable la elegibilidad de promoción

RF-03: inscribirse marca asistencia, sin verificación posterior. Pero `promotion_events.attendance_window_months` usa asistencia como criterio de elegibilidad para ascender de cinturón. Resultado: un alumno se inscribe a todas las clases, no va a ninguna, y aparece elegible para examen de cinturón.

En un gimnasio es un detalle; **en un dojo el cinturón es la moneda de reputación de la escuela** — el sensei no va a aceptar un sistema donde eso pase. Arreglo mínimo (una columna y un botón, no un módulo de check-in): el instructor puede marcar no-show después de la clase (`attended` pasa a nullable, `null` = sin verificar, y la ventana de promoción cuenta solo `attended = true`). Recomendación fuerte, no bloqueante.

### D2 🟠 El challenger reporta el resultado del sparring y nadie lo confirma

Spec 3: solo el challenger carga rounds, el ganador se deriva, y la vista head-to-head "no requiere confirmación adicional del rival". El head-to-head es explícitamente social ("llevo 3-1 contra Fulano", HU-08). Un sistema de marcador donde una sola parte reporta y la otra no puede objetar no sobrevive al primer conflicto entre dos alumnos.

Arreglo barato: `sparring_challenges.opponent_confirmed boolean default false` + un botón "confirmar resultado" para el rival, y que `sparring_head_to_head` cuente solo los confirmados. Es una columna, un botón y un `where` — y elimina la categoría entera de problema.

### D3 🟡 La expiración automática de sparring (RF-06b) no tiene mecanismo

"Expira automáticamente a los 14 días" requiere un job de `pg_cron` o una Edge Function programada. No está en ningún spec ni en el cronograma. Mismo tema para RF-17 (recordatorios de pago) y para `expire_subscriptions()` que ya existe en GymBase. Conviene un solo job diario que corra las tres cosas, definido como pieza de CoreBase.

### D4 🟡 Realtime: la heurística de "¿tiene sesión activa?" no existe server-side

Spec 5: "si el destinatario no tiene sesión activa (heurística: sin conexión Realtime abierta), dispara Web Push". Saber eso desde el servidor requiere Realtime Presence con un canal por usuario — es infra adicional, no una consulta. Más simple y más confiable: **insertar siempre + pushear siempre** si hay `push_subscription`, y que el cliente deduplique (si ya la vio in-app, la marca leída y el push queda inofensivo). Ahorra una pieza de infra completa.

---

## E. Arquitectura y organización del código

### E1 🟡 El monorepo ya existe — no arrancar de cero

`ProyectosPersonales/Gymbase` **ya es un Turborepo** (`apps/gymbase`, `clients/gymbase/*`, `pnpm-workspace.yaml`, `turbo.json`, `.agents/skills/` completo con 40+ skills). Los specs describen crear `memberbase/` desde cero. Arrancar un repo nuevo significa perder el historial, duplicar el skills-lock, y dejar GymBase v1 huérfano en otro repo mientras Dojo Shoto lo sigue usando.

**Recomendación:** evolucionar el repo existente (renombrarlo a `memberbase`, agregar `packages/*` al workspace, crear `apps/dojobase`), con **una regla dura**: `apps/dojobase` no puede importar nada de `apps/gymbase`. El código viaja gymbase → `packages/*` → dojobase solo por porte explícito con limpieza, nunca por import. Sin esa regla, la deuda de GymBase se cuela en el producto nuevo el primer día.

### E2 🟡 Colisión de nombres: `memberbase` / CoreBase / DojoBase / `@memberbase/gymbase`

Cuatro nombres para tres cosas. Propuesta:

- **MemberBase** = la plataforma / el monorepo / el scope npm `@memberbase/*` (ya es el nombre establecido en el código).
- **CoreBase** = nombre humano del conjunto `packages/core` + `packages/ui` + `packages/shared-modules`. No es un paquete npm.
- **DojoBase** / **GymBase** = los dos productos vendibles, `apps/dojobase` y `apps/gymbase`.

### E3 🟡 `packages/core/{auth,billing,design-tokens}` como 3 paquetes es prematuro

Tres paquetes = tres `package.json`, tres `tsconfig`, tres builds y dependencias cruzadas para un proyecto de una persona. Un `@memberbase/core` con subpath exports (`@memberbase/core/auth`) da la misma separación conceptual con un décimo del wiring. Se puede partir después si duele; hoy no duele.

### E4 🟡 `gym_scheduled_classes` conservando su nombre en un schema nuevo

El spec 2 lo justifica por "continuidad con hooks ya extraídos" — pero esos hooks se están reescribiendo igual. Meter un prefijo `gym_` en el core de DojoBase es deuda gratuita el día uno. Renombrar a `scheduled_classes` y `class_reservations` mientras cuesta cero.

### E5 🟠 Falta todo lo de operación, no solo de features

Ningún spec menciona: estrategia de testing (GymBase ya tiene Vitest + Playwright configurados), CI, cuántos proyectos de Vercel, variables de entorno por app, seed de datos demo, monitoreo de errores, ni la app de marketing (`apps/marketing`, mencionada de pasada en 8b). Son las cosas que aparecen en la semana 6 y descarrilan el cronograma.

### E6 🟠 Onvo con conexión por comercio: verificar antes de la semana 7

`org_payment_connections` asume que Onvo tiene un flujo tipo marketplace/connect donde cada dojo conecta su propia cuenta. Si Onvo no lo soporta (o exige contrato de agregador), el modelo de billing está mal desde el schema. Es una llamada o media hora de docs, y conviene hacerla **antes** de escribir la migración de billing, no en la semana 7.

---

## F. Lo que falta para "mejorar la UI", que era parte del objetivo

Los specs 4, 8 y 8b definen **tokens y catálogo de componentes** — el sistema. No definen **el diseño**: no hay inventario de pantallas, ni arquitectura de información, ni navegación, ni flujos. Es exactamente el artefacto que en Tacha es `DESIGN.md` (22 pantallas con prompt por pantalla) y acá no existe.

Sin eso, "mejorar la UI" termina siendo el agente de UI improvisando pantalla por pantalla — que es cómo GymBase llegó a tener cinco patrones de formulario y 618 hex sueltos. **Recomiendo un `DojoBase/DESIGN.md` antes de la semana 2**, con el mismo formato de Tacha: personalidad, tokens, navegación por rol (miembro / admin / owner), inventario de pantallas mapeado a HU, estados vacíos/carga/error, y prompt por pantalla.

---

## Resumen de decisiones que hay que tomar

| # | Decisión | Recomendación |
|---|---|---|
| 1 | ¿Repo nuevo o evolucionar `Gymbase`? | Evolucionar, con la regla de no-import (E1) |
| 2 | ¿Proyecto Supabase nuevo para DojoBase? | Sí — schema incompatible, y protege al cliente vivo (A1) |
| 3 | ¿Admin ciego a montos, de verdad? | No es alcanzable; reescribir el requisito (B2) |
| 4 | ¿Confirmación del rival en sparring? | Agregarla, cuesta una columna (D2) |
| 5 | ¿No-show marcable por el instructor? | Agregarlo, la integridad del cinturón lo pide (D1) |
| 6 | ¿`member_fights` público o privado por default? | Privado + `upcoming` siempre visible (B6) |
| 7 | ¿Qué se cae si el cronograma se atrasa? | Torneos → familias → challenges, en ese orden (A3) |
