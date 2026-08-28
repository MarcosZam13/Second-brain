---
proyecto: CoreBase
tema: Schema de base de datos — capa core y módulos compartidos
fecha: 2026-08-28
tipo: documentacion
estado: v1.0 — corregido y completado contra las HU, reemplaza a la parte [core]/[shared] del spec 02
tags: [corebase, schema, supabase, postgres]
---

# Schema — CoreBase (core + módulos compartidos)

Ver también: [[Proyectos/CoreBase/arquitectura|arquitectura.md]] · [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]] · [[Proyectos/DojoBase/schema-dojo|schema-dojo.md]] (capa vertical) · [[Proyectos/CoreBase/revision-critica-specs|Revisión crítica]]

> Reemplaza la parte `[core]` y `[shared]` de `_fuentes/02-spec-schema-database.md`. Las tablas `[dojo]` viven en [[Proyectos/DojoBase/schema-dojo|schema-dojo.md]]. Cambios respecto al spec original marcados con **▲**.
>
> Convenciones: todas las tablas llevan `created_at timestamptz default now()`; las que se editan llevan `updated_at` con trigger. Todo `id` es `uuid default gen_random_uuid()` salvo donde la PK sea compuesta. **Toda tabla multi-tenant lleva `org_id` explícito** — incluso las hijas, aunque se pudiera derivar por JOIN: encarece un byte y abarata cada policy (▲ corrige el spec, que dejaba `promotion_criteria`/`promotion_scores` sin `org_id`).

## 1. Identidad y organización — `[core]`

```sql
profiles (
  id            uuid primary key references auth.users on delete cascade,
  full_name     text,
  avatar_url    text,
  active_org_id uuid references organizations,   -- ▲ NUEVO: organización activa
  created_at    timestamptz default now()
)

organizations (
  id         uuid primary key default gen_random_uuid(),
  name       text not null,
  slug       text unique not null,
  logo_url   text,
  created_at timestamptz default now()
)

org_members (
  org_id    uuid references organizations on delete cascade,
  user_id   uuid references profiles on delete cascade,
  role      text not null default 'member' check (role in ('owner','admin','member')),
  status    text not null default 'active' check (status in ('active','suspended')),  -- ▲
  joined_at timestamptz default now(),
  primary key (org_id, user_id)
)

-- ▲ NUEVA: HU-22 / RF-20 — invitar sin registro público abierto
org_invitations (
  id          uuid primary key default gen_random_uuid(),
  org_id      uuid not null references organizations on delete cascade,
  email       text,                       -- null = invitación por código abierto
  code        text not null unique,       -- token de un solo uso
  role        text not null default 'member' check (role in ('owner','admin','member')),
  invited_by  uuid not null references profiles,
  expires_at  timestamptz not null,
  accepted_at timestamptz,
  accepted_by uuid references profiles,
  created_at  timestamptz default now()
)
```

**▲ `profiles.active_org_id`** cierra el hueco de B4: el hook que arma el JWT necesita saber de qué organización emitir el claim, y el spec nunca dijo dónde vivía ese dato. Cambiar de organización = `UPDATE profiles SET active_org_id` + `refreshSession()`.

**▲ `org_members.status`** permite suspender a un miembro sin borrar su historial (su rango, sus peleas, sus pagos). En v1 la única salida era eliminar la fila.

**Corrección de fondo respecto a v1:** `organizations` ya no carga columnas de un vertical (`gym_name`, `sinpe_number`, `sinpe_name`, `max_capacity`, `cancel_minutes` vivían todas ahí). Esa configuración va a una tabla de extensión propia de cada app — para DojoBase, `dojo_org_settings`.

## 2. Theming por tenant — `[core]`

```sql
tenant_themes (
  org_id     uuid primary key references organizations on delete cascade,
  colors     jsonb not null,     -- primary, secondary, accent, background, surface, textPrimary, textMuted
  typography jsonb,              -- headingFont, bodyFont (opcionales; si null, default del vertical)
  radius     text default 'soft' check (radius in ('sharp','soft','rounded')),
  updated_at timestamptz default now()
)
```

Es la pieza que convierte onboardear un dojo nuevo de "un deploy" a "un insert". El logo vive en `organizations.logo_url` (es identidad, no tema). El contrato TypeScript y la inyección de CSS vars están en el design system.

## 3. Billing — `[core]`

```sql
membership_plans (
  id             uuid primary key default gen_random_uuid(),
  org_id         uuid not null references organizations on delete cascade,
  name           text not null,
  description    text,
  price_cents    int not null check (price_cents >= 0),
  billing_period text not null check (billing_period in ('monthly','yearly')),
  is_featured    boolean default false,     -- ▲ "plan recomendado", ya existe en v1 y se usa
  active         boolean default true,
  created_at     timestamptz default now()
)

subscriptions (
  id                 uuid primary key default gen_random_uuid(),
  org_id             uuid not null references organizations on delete cascade,
  member_id          uuid not null references profiles,
  plan_id            uuid not null references membership_plans,
  family_group_id    uuid references family_groups,          -- ▲ HU-23
  status             text not null check (status in ('active','past_due','cancelled')),
  current_period_end timestamptz,
  created_at         timestamptz default now()
)

payment_proofs (
  id              uuid primary key default gen_random_uuid(),
  org_id          uuid not null references organizations on delete cascade,   -- ▲ denormalizado
  subscription_id uuid not null references subscriptions on delete cascade,
  amount_cents    int not null,
  proof_url       text,
  status          text default 'pending' check (status in ('pending','verified','rejected')),
  reviewed_by     uuid references profiles,      -- ▲ trazabilidad de quién decidió
  reviewed_at     timestamptz,                   -- ▲
  rejection_note  text,                          -- ▲ HU-17b: el miembro debe saber por qué
  created_at      timestamptz default now()
)

org_payment_connections (
  org_id              uuid primary key references organizations on delete cascade,
  provider            text not null check (provider in ('onvo')),
  provider_account_id text not null,
  status              text default 'active' check (status in ('active','disconnected')),
  connected_at        timestamptz default now()
)

-- ▲ NUEVA: HU-23 / RF-21 — hermanos entrenando bajo un plan compartido
family_groups (
  id         uuid primary key default gen_random_uuid(),
  org_id     uuid not null references organizations on delete cascade,
  name       text not null,
  created_at timestamptz default now()
)

-- ▲ NUEVA: HU-20 / RF-17 — idempotencia del recordatorio de pago
membership_reminders_sent (
  subscription_id uuid not null references subscriptions on delete cascade,
  reminder_kind   text not null check (reminder_kind in ('due_soon','overdue')),
  period_end      timestamptz not null,
  sent_at         timestamptz default now(),
  primary key (subscription_id, reminder_kind, period_end)
)
```

**Se porta de v1 tal cual (ya funciona bien):** el trigger que completa `amount_cents` desde `membership_plans.price_cents` vía `subscriptions` cuando el comprobante viene sin monto, y la lógica de encolar el nuevo período desde el vencimiento de la suscripción activa al aprobar un pago.

**▲ Sobre el requisito "admin sin ver montos" (decisión 3):** no era exigible — el admin lee `membership_plans` y `subscriptions`, y el comprobante SINPE muestra el monto en la imagen que tiene que revisar. El requisito queda reescrito: *el admin no accede a reportes ni dashboards de ingresos, ni a `org_payment_connections`; sí ve el monto de la fila individual que aprueba.* La agregación financiera es exclusiva de `owner` y se expone por función, no por vista con policy (ver seguridad).

**▲ Nota sobre grupos familiares:** el plan se asocia a la suscripción, y la suscripción al grupo. Un grupo puede tener varios miembros con planes distintos (v1 ya lo resolvió así: "plan por integrante dentro de la familia") — el grupo es la unidad de cobro y de descuento, no un plan único forzado.

**▲ Pendiente de verificar antes de implementar billing:** que Onvo soporte conexión por comercio (cada dojo conecta su propia cuenta). Si exige contrato de agregador, `org_payment_connections` está mal modelada desde el schema. Es media hora de docs y hay que hacerla **antes** de escribir esta migración.

## 4. Notificaciones — `[module]`

```sql
notifications (
  id           uuid primary key default gen_random_uuid(),
  org_id       uuid not null references organizations on delete cascade,
  recipient_id uuid not null references profiles on delete cascade,
  type         text not null,     -- 'sparring_challenge_received', 'promotion_result', ...
  payload      jsonb not null,
  read_at      timestamptz,
  created_at   timestamptz default now()
)
create index on notifications (recipient_id, read_at, created_at desc);

-- ▲ Nunca se definió en el spec 02 pese a referenciarse en el 05 como "ya existe"
push_subscriptions (
  id         uuid primary key default gen_random_uuid(),
  org_id     uuid not null references organizations on delete cascade,
  member_id  uuid not null references profiles on delete cascade,
  endpoint   text not null,
  keys       jsonb not null,
  created_at timestamptz default now(),
  unique (member_id, org_id, endpoint)
)
```

El motor es genérico (Realtime + Web Push); **qué dispara una notificación y cómo se redacta es de cada vertical**. Por eso es module y no core: si cambia qué notifica DojoBase, GymBase no se entera.

Un único punto de entrada server-side, `emitNotification({ orgId, recipientId, type, payload })`. Los server actions de sparring y de promociones lo llaman y no conocen ni Realtime ni Web Push.

**▲ Corrección al spec (D4):** el spec decía "si el destinatario no tiene sesión activa, dispara push", con la heurística de "sin conexión Realtime abierta". Saber eso desde el servidor requiere Realtime Presence con canal por usuario — infra adicional, no una consulta. Se simplifica: **insertar siempre y pushear siempre** si hay suscripción; el cliente deduplica marcando leída la que ya vio in-app. Se ahorra una pieza de infra completa sin perder comportamiento observable.

**▲ Corrección de aislamiento (heredada de la auditoría):** `push_subscriptions` en v1 tiene `org_id NOT NULL` sin FK y **sin filtro de org en su única policy** — el aislamiento de tenant depende 100% de la aplicación. Acá lleva FK, `UNIQUE` y policy con doble condición.

## 5. Clases y asistencia — `[module]`

```sql
class_types (                                    -- ▲ recuperado de v1, el spec lo perdió
  id       uuid primary key default gen_random_uuid(),
  org_id   uuid not null references organizations on delete cascade,
  name     text not null,
  color    text,
  unique (org_id, name)
)

scheduled_classes (                              -- ▲ renombrada: sin prefijo gym_
  id                 uuid primary key default gen_random_uuid(),
  org_id             uuid not null references organizations on delete cascade,
  class_type_id      uuid references class_types,
  discipline_id      uuid,                       -- nullable; FK la agrega la app vertical
  name               text not null,
  instructor_id      uuid references profiles,   -- ▲ RF-04: instructor = un admin de la org
  starts_at          timestamptz not null,
  ends_at            timestamptz not null,       -- ▲ el spec no tenía fin de clase
  capacity           int check (capacity > 0),
  is_cancelled       boolean default false,      -- ▲ HU-02c
  cancelled_reason   text,                       -- ▲
  is_private         boolean default false,      -- ▲ clases privadas, ya existe en v1
  allowed_plan_ids   uuid[],                     -- ▲
  recurrence_group_id uuid,                      -- ▲ recurrencia, ya existe en v1
  created_at         timestamptz default now()
)
create index on scheduled_classes (org_id, starts_at);

class_reservations (                             -- ▲ renombrada
  id         uuid primary key default gen_random_uuid(),
  org_id     uuid not null references organizations on delete cascade,
  class_id   uuid not null references scheduled_classes on delete cascade,
  member_id  uuid not null references profiles on delete cascade,
  status     text default 'confirmed' check (status in ('confirmed','cancelled','waitlisted')),
  attended   boolean,                            -- ▲ nullable: null = sin verificar
  created_at timestamptz default now(),
  unique (class_id, member_id)                   -- ▲ nada impedía inscribirse dos veces
)
```

**▲ Corrección de la regla de asistencia (decisión 5).** El spec decía: inscribirse marca `attended = true` automáticamente, sin verificación posterior. Pero la elegibilidad para un examen de cinturón se calcula sobre la ventana de asistencia — con esa regla, un alumno se inscribe a todo, no va a nada, y aparece elegible para ascender. En un gimnasio es un detalle; en un dojo el cinturón es la moneda de reputación de la escuela.

La regla queda: `attended` es **nullable**. Se pone en `true` al confirmarse la inscripción (la inscripción sigue siendo el mecanismo de asistencia — no hay QR ni check-in físico), pero el instructor puede marcar no-show después de la clase. **La ventana de promoción cuenta solo `attended = true`.** Un botón y una columna nullable, no un módulo de check-in.

**Se porta de v1:** validar que la clase no empiece en menos de 30 minutos al reservar, y waitlist automática cuando se llena. Fechas siempre en UTC en la base; Costa Rica es UTC-6 sin DST y el servidor corre en UTC — todo cálculo de calendario usa métodos UTC.

## 6. Contenido — `[module]`

```sql
content_categories (                             -- ▲ el spec referenciaba category_id sin tabla
  id         uuid primary key default gen_random_uuid(),
  org_id     uuid not null references organizations on delete cascade,
  parent_id  uuid references content_categories on delete cascade,  -- ▲ carpetas anidadas (RF-13)
  name       text not null,
  slug       text not null,
  position   int default 0,
  unique (org_id, slug)                          -- ▲ v1 lo tenía UNIQUE global: rompía multi-tenancy
)

content (
  id          uuid primary key default gen_random_uuid(),
  org_id      uuid not null references organizations on delete cascade,
  category_id uuid references content_categories on delete set null,
  title       text not null,
  body        text,
  media_url   text,
  is_published boolean default false,            -- ▲ poder preparar material sin publicarlo
  created_by  uuid references profiles,
  created_at  timestamptz default now()
)

content_plans (                                  -- gating por plan, ya existía en v1
  content_id uuid references content on delete cascade,
  plan_id    uuid references membership_plans on delete cascade,
  primary key (content_id, plan_id)
)

content_favorites (                              -- ▲ HU-15b
  content_id uuid references content on delete cascade,
  member_id  uuid references profiles on delete cascade,
  created_at timestamptz default now(),
  primary key (content_id, member_id)
)
```

**▲** El gating pasa de una columna `required_plan_id` (un solo plan) a la tabla `content_plans` (N planes), que es lo que v1 ya usa en producción y lo que el negocio realmente necesita: un video de técnica visible para "Combate" y "Competencia" pero no para "Niños".

## 7. Rutinas — `[module]`

```sql
exercises (
  id          uuid primary key default gen_random_uuid(),
  org_id      uuid references organizations on delete cascade,  -- null = catálogo global
  name        text not null,
  media_url   text,
  muscle_group text
)

routines (
  id           uuid primary key default gen_random_uuid(),
  org_id       uuid not null references organizations on delete cascade,
  name         text not null,
  context_type text not null,     -- 'strength' | 'martial_arts_drill' | futuro
  created_by   uuid references profiles,
  is_member_created boolean default false,   -- ▲ patrón de ownership de v1, vale la pena conservar
  created_at   timestamptz default now()
)

routine_days (
  id         uuid primary key default gen_random_uuid(),
  routine_id uuid not null references routines on delete cascade,
  position   int not null,
  label      text
)

routine_exercises (
  id             uuid primary key default gen_random_uuid(),
  routine_day_id uuid not null references routine_days on delete cascade,
  exercise_id    uuid references exercises,
  exercise_name  text not null,     -- se conserva por si el ejercicio es libre
  target_sets    int,
  target_reps    int,
  notes          text,
  position       int not null default 0
)

member_routines (
  member_id  uuid references profiles on delete cascade,
  routine_id uuid references routines on delete cascade,
  is_featured boolean default false,
  assigned_at timestamptz default now(),
  primary key (member_id, routine_id)
)
```

## 8. Challenges — `[module]`

```sql
challenges (
  id           uuid primary key default gen_random_uuid(),
  org_id       uuid not null references organizations on delete cascade,
  name         text not null,
  description  text,
  type         text not null check (type in ('attendance','routine','friendly_fights','custom')),
  target_value numeric,
  starts_at    timestamptz not null,
  ends_at      timestamptz not null,
  status       text default 'draft' check (status in ('draft','active','closed')),
  created_by   uuid references profiles
)

challenge_participants (
  challenge_id uuid references challenges on delete cascade,
  member_id    uuid references profiles on delete cascade,
  progress     numeric default 0,
  completed_at timestamptz,
  primary key (challenge_id, member_id)
)
```

**▲ Corrección importante.** En v1 el "motor genérico de retos" no era genérico: `gym_challenges` tiene FKs directas a `gym_exercises`/`gym_routines`, y `gym_challenge_participants` tiene columnas de composición corporal. Además el enum de tipos tenía valores redundantes (`weight`/`weight_loss`, `personal_record`/`one_rm`) y valores sin lógica de progreso implementada (`fat_loss`, `muscle_gain`).

Acá el motor se corta a lo que RF-14 exige — tres tipos reales (asistencia, rutina, peleas amistosas) más `custom` de progreso manual — sin FKs a tablas de vertical. El cálculo de progreso vive en la app, alimentado por eventos, no en un trigger acoplado a tablas de gimnasio.

## 9. Funciones puras compartidas (no son schema, pero son contrato)

Estas viven en TypeScript en `@corebase/core` o en el módulo correspondiente, **una sola implementación** importada por cliente y servidor. Es el hallazgo que más veces se repite en la extracción de v1 (lógica duplicada que se desincroniza):

| Función | Dónde | Por qué es única |
|---|---|---|
| Cálculo de puntaje final de promoción (promedio ponderado normalizado a /10) | vertical DojoBase | El cliente la usa para preview en vivo, el servidor para resolver. Duplicada, se desincronizan |
| Resolución del ganador de un sparring por suma de rounds | vertical DojoBase | Idem |
| Ventana de asistencia elegible | `@corebase/modules/classes` | Alimenta promociones y challenges |
| Próximo período de facturación al aprobar un pago | `@corebase/core/billing` | Cola desde el vencimiento actual, no desde hoy |

## 10. Cobertura contra las historias de usuario

Chequeo de que el schema alcanza para lo pedido (las tablas de la capa vertical están en [[Proyectos/DojoBase/schema-dojo|schema-dojo.md]]):

| HU / RF | Cubierto por |
|---|---|
| HU-01 a HU-04b, RF-03/03b/04 | `class_types`, `scheduled_classes`, `class_reservations` |
| HU-15, 15b, RF-13 | `content_categories` (anidada), `content`, `content_plans`, `content_favorites` |
| HU-16, RF-14 | `challenges`, `challenge_participants` |
| HU-16b, 16c, 17, 17b, 18, RF-22 | `membership_plans`, `subscriptions`, `payment_proofs` |
| HU-19, RF-16 | Función `get_financial_summary()` — ver seguridad |
| HU-20, RF-17 | `membership_reminders_sent` + job diario |
| HU-21, RF-18 | `tenant_themes` |
| HU-22, RF-20 | `org_invitations` |
| HU-23, RF-21 | `family_groups` + `subscriptions.family_group_id` |
| RF-08 | `notifications`, `push_subscriptions` |
| RF-19 | Alta manual — sin tabla, es proceso |

## 11. Migraciones — orden de aplicación

1. Extensiones, `updated_at` genérico, helpers de JWT (ver seguridad).
2. Identidad: `profiles`, `organizations`, `org_members`, `org_invitations` + trigger de alta de usuario.
3. Theming: `tenant_themes`.
4. Billing: `family_groups`, `membership_plans`, `subscriptions`, `payment_proofs`, `org_payment_connections`, `membership_reminders_sent` + trigger de monto + función de próximo período.
5. Notificaciones: `notifications`, `push_subscriptions`.
6. Módulos: clases, contenido, rutinas, challenges.
7. RLS de todo lo anterior, en su propia migración por tabla — separada de la creación, para que una policy rota se pueda revertir sin tocar el schema.

Las tablas de DojoBase (disciplinas, rangos, sparring, promociones, peleas, torneos) se aplican después, desde `apps/dojobase/supabase/migrations/`.
