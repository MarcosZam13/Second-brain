---
proyecto: CoreBase
tema: revisión crítica del paquete de specs 1-9
fecha: 2026-08-28
tipo: analisis
estado: revisado — las 7 decisiones se tomaron el 2026-08-28, ver bloque de decisiones al inicio
tags: [corebase, dojobase, arquitectura, revision]
---

# Revisión crítica — specs 1-9 de DojoBase/CoreBase

Ver también: [[Proyectos/CoreBase/README|CoreBase]] · [[Proyectos/DojoBase/README|DojoBase]] · [[Proyectos/GymBase/README|GymBase]]

Revisión de los 9 documentos de spec (`_fuentes/`) contra el código real de GymBase (`ProyectosPersonales/Gymbase`), su `auditoria-gymbase.md`, `extraccion-tecnica-dojo.md` y `Context/_CONTEXTO-IA.md`.

**Veredicto general:** el paquete de specs es sólido en dirección arquitectónica (separar core de vertical, JWT en vez de header, theming a tabla) y las correcciones de bugs heredados están bien identificadas. Los problemas están en **tres frentes**: (a) SQL que no funciona como está escrito, (b) el schema cubre ~70% de las historias de usuario, y (c) el encuadre del proyecto — lo que se está construyendo es un producto que hay que poder vender, no una reescritura de features para un usuario existente.

---

## Decisiones tomadas (2026-08-28)

Las 7 decisiones del resumen final quedaron resueltas. Este documento se conserva como el análisis que las fundamenta; la fuente de verdad de lo decidido es [[Proyectos/CoreBase/arquitectura|arquitectura.md]].

| # | Decisión | Resuelto |
|---|---|---|
| 1 | Repo | **Desde cero**, repo nuevo `corebase`. Se descarta evolucionar `Gymbase` — decisión del usuario: proyecto personal, no se pierde nada, y arrancar limpio es lo que garantiza mini-componentes y cero hardcoding desde el día uno. GymBase v1 **no está en uso** y queda como **fuente de especificación y de lógica de negocio ya validada**, nunca como código a copiar |
| 2 | Supabase | **Proyecto nuevo** — ya creado: org `CoreBase`, proyecto `CoreBase` (`pzyvvotltgipehsywqpi`, us-east-2, PG 17.6), vacío. La base vieja de GymBase también está vacía y queda solo como respaldo |
| 3 | Finanzas (B2) | Se reescribe el requisito: admin sin reportes ni `org_payment_connections`, pero sí ve el monto de la fila que aprueba |
| 4 | Sparring (D2) | Se agrega confirmación del rival |
| 5 | Asistencia (D1) | Se agrega no-show marcable por el instructor |
| 6 | `member_fights` (B6) | Privado por default + `upcoming` siempre visible |
| 7 | Recorte | Torneos → familias → challenges, en ese orden, si el cronograma se atrasa |

Además el usuario pidió aplicar **cualquier otra corrección que la revisión considere necesaria**, y dejó explícito que las funcionalidades de GymBase que deben sobrevivir (mejoradas) son: historial de peleas profesionales, retos de sparring entre miembros, contenido por carpetas, rutinas, rangos, artes marciales, clases, clases privadas, membresías, torneos y ascensos.


Severidad: 🔴 bloqueante (rompe si se implementa tal cual) · 🟠 gap (falta algo que las HU exigen) · 🟡 criterio (decisión a revisar, no está roto)

---

## A. Encuadre del proyecto (lo más importante)

### A1 ⚪ Corregido — no hay cliente en producción

*Escrito originalmente como bloqueante, a partir del `git log` de GymBase (tandas de fixes "del sensei", franjas, familias). **El usuario aclaró el 2026-08-28 que GymBase v1 no está en uso**: Dojo Shoto es un cliente al que se le quiere vender DojoBase ya terminado, no un cliente operando hoy, y la base de datos vieja está vacía y queda solo como respaldo.*

Consecuencias de la corrección, todas a favor:

- **No hay plan de migración de datos.** DojoBase arranca con una base vacía y datos de demo.
- **No hay corte ni ventana de riesgo.** No hay que coordinar nada con un cliente en operación.
- **No hay congelamiento de GymBase v1** — no se le va a tocar nada de todos modos.
- **No hay dos productos que mantener en paralelo.** Toda la atención va a DojoBase.

Lo que sí queda del análisis original: **el objetivo sigue siendo un producto vendible, no una reescritura para un usuario existente.** Ver A2.

### A2 🟡 El objetivo es vender — y el primer prospecto es Dojo Shoto

Dojo Shoto es el primer cliente a cerrar, no un usuario a migrar. Eso pone la vara en un lugar distinto al de "portar features": el producto tiene que estar **presentable y completo el día de la demo**, porque la demo es la venta.

Lo que hace que un dojo compre:

1. **Que se vea como un producto**, no como un panel de administración. Es la razón principal por la que se rehace la UI.
2. **Que resuelva su operación real** — clases, cinturones, ascensos, pagos. GymBase v1 ya probó cuáles son esas funciones; esa validación es el activo que se conserva.
3. **Que onboardearlo sea inmediato.** Colores, logo y disciplinas de Dojo Shoto configurados en minutos delante de él, no en un PR.

Y lo que hace que haya un **segundo** dojo es lo mismo del punto 3, sin desarrollo de por medio: tenant por JWT, `tenant_themes` en tabla, y alta de organización con invitación de miembros. Eso es el producto mínimo vendible, y va primero.

### A3 🟡 8 semanas es optimista por un factor de ~2

23 HU + monorepo nuevo + design system nuevo + billing + un producto presentable, en solo y en paralelo con la universidad. GymBase tardó mucho más en llegar a los mismos módulos. No es razón para no empezar — sí para que el cronograma diga qué se cae primero si hay atraso. Corte duro sugerido: torneos (ya fuera de alcance), grupos familiares (HU-23) y challenges (HU-16) son los tres primeros candidatos a v1.1.

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

- **CoreBase** = la plataforma, el monorepo (`corebase`), el scope npm `@corebase/*` y la capa compartida. Es también el nombre de la organización y del proyecto de Supabase ya creados.
- **DojoBase** / **GymBase** = los dos productos vendibles, `apps/dojobase` y `apps/gymbase`.
- Se descarta **MemberBase** como nombre — era el nombre interno de GymBase v1 y arrastra la confusión que se está resolviendo.

*(Resuelto el 2026-08-28: CoreBase gana como nombre único.)*

### E3 🟡 `packages/core/{auth,billing,design-tokens}` como 3 paquetes es prematuro

Tres paquetes = tres `package.json`, tres `tsconfig`, tres builds y dependencias cruzadas para un proyecto de una persona. Un `@memberbase/core` con subpath exports (`@memberbase/core/auth`) da la misma separación conceptual con un décimo del wiring. Se puede partir después si duele; hoy no duele.

### E4 🟡 `gym_scheduled_classes` conservando su nombre en un schema nuevo

El spec 2 lo justifica por "continuidad con hooks ya extraídos" — pero esos hooks se están reescribiendo igual. Meter un prefijo `gym_` en el core de DojoBase es deuda gratuita el día uno. Renombrar a `scheduled_classes` y `class_reservations` mientras cuesta cero.

### E5 🟠 Falta todo lo de operación, no solo de features

Ningún spec menciona: estrategia de testing (GymBase ya tiene Vitest + Playwright configurados), CI, cuántos proyectos de Vercel, variables de entorno por app, seed de datos demo, monitoreo de errores, ni la landing de marketing (mencionada de pasada en 8b — resuelto 2026-08-31 como repo propio, `dojobase-landing`, no como app dentro de este monorepo). Son las cosas que aparecen en la semana 6 y descarrilan el cronograma.

### E6 ⚪ Resuelto — ONVO sí soporta conexión por comercio

Investigado el 2026-08-28: ONVO tiene un producto de marketplace tipo Stripe Connect (cuentas conectadas, onboarding alojado, enrutamiento con `onBehalfOf`, comisión porcentual y tarifa fija semanal para la plataforma). **El modelo de datos del spec era correcto.** Detalle completo, campos reales de la API y el camino de activación en [[Proyectos/CoreBase/billing-onvo|billing-onvo.md]].

Decisión asociada: **el MVP cobra por comprobante SINPE manual**, con el schema ya preparado para el enchufe. Integrar ONVO depende de la inscripción ante Hacienda, que es trámite y no desarrollo, y además conviene que el cobro automático sea opcional por dojo (un dojo chico puede preferir 0% de comisión).

---

## F. Lo que falta para "mejorar la UI", que era parte del objetivo

Los specs 4, 8 y 8b definen **tokens y catálogo de componentes** — el sistema. No definen **el diseño**: no hay inventario de pantallas, ni arquitectura de información, ni navegación, ni flujos. Es exactamente el artefacto que en Tacha es `DESIGN.md` (22 pantallas con prompt por pantalla) y acá no existe.

Sin eso, "mejorar la UI" termina siendo el agente de UI improvisando pantalla por pantalla — que es cómo GymBase llegó a tener cinco patrones de formulario y 618 hex sueltos. **Recomiendo un `DojoBase/DESIGN.md` antes de la semana 2**, con el mismo formato de Tacha: personalidad, tokens, navegación por rol (miembro / admin / owner), inventario de pantallas mapeado a HU, estados vacíos/carga/error, y prompt por pantalla.

---

## Resumen de decisiones que hay que tomar

| # | Decisión | Recomendación |
|---|---|---|
| 1 | ¿Repo nuevo o evolucionar `Gymbase`? | Evolucionar, con la regla de no-import (E1) |
| 2 | ¿Proyecto Supabase nuevo para DojoBase? | Sí — el schema es incompatible y la base vieja está vacía de todos modos (A1) |
| 3 | ¿Admin ciego a montos, de verdad? | No es alcanzable; reescribir el requisito (B2) |
| 4 | ¿Confirmación del rival en sparring? | Agregarla, cuesta una columna (D2) |
| 5 | ¿No-show marcable por el instructor? | Agregarlo, la integridad del cinturón lo pide (D1) |
| 6 | ¿`member_fights` público o privado por default? | Privado + `upcoming` siempre visible (B6) |
| 7 | ¿Qué se cae si el cronograma se atrasa? | Torneos → familias → challenges, en ese orden (A3) |
| 8 | ¿ONVO soporta marketplace? | Sí. MVP manual con el enchufe puesto (E6) |
