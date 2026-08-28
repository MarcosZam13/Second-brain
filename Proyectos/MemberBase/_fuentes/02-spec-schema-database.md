# Spec Dojo — Sección 2: Schema de base de datos

Convención: cada tabla lleva una etiqueta de capa (`[core]`, `[shared]`, `[dojo]`) según la regla de las 3 capas de la sección 1. RLS se resuelve vía JWT claim (`org_id`, `role`) — el detalle de ese mecanismo va en la sección 3, acá solo se asume que existe.

## [core] Identidad y organización

```sql
-- profiles: se porta tal cual, sin cambios de fondo
profiles (
  id uuid primary key references auth.users,
  full_name text,
  avatar_url text,
  created_at timestamptz default now()
)

-- organizations: limpia de columnas de un solo vertical (sin SINPE/capacidad de gym acá)
organizations (
  id uuid primary key default gen_random_uuid(),
  name text not null,
  slug text unique not null,
  created_at timestamptz default now()
)

-- org_members: rol real de 3 valores, sin colapso owner→admin
org_members (
  org_id uuid references organizations,
  user_id uuid references profiles,
  role text check (role in ('owner','admin','member')) not null default 'member',
  joined_at timestamptz default now(),
  primary key (org_id, user_id)
)
```

**Corrección de fondo respecto a GymBase:** `organizations` ya no carga columnas de configuración de un vertical específico. Esa configuración (SINPE para gym, o lo que sea propio de Dojo) vive en una tabla de extensión propia de cada app (`dojo_org_settings`), nunca en el core.

## [core] Billing

```sql
membership_plans (
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  name text not null,
  price_cents int not null,
  billing_period text check (billing_period in ('monthly','yearly')) not null,
  active boolean default true
)

subscriptions (
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  member_id uuid references profiles,
  plan_id uuid references membership_plans,
  status text check (status in ('active','past_due','cancelled')) not null,
  current_period_end timestamptz
)

payment_proofs (
  id uuid primary key default gen_random_uuid(),
  subscription_id uuid references subscriptions,
  amount_cents int not null,        -- se porta set_payment_proof_amount() tal cual, ya funciona bien
  proof_url text,
  status text check (status in ('pending','verified','rejected')) default 'pending',
  created_at timestamptz default now()
)

-- Conexión de pagos por comercio (Onvo) — no es una cuenta nuestra, cada org conecta la suya
org_payment_connections (
  org_id uuid references organizations primary key,
  provider text check (provider in ('onvo')) not null,
  provider_account_id text not null,
  connected_at timestamptz default now(),
  status text check (status in ('active','disconnected')) default 'active'
)
```

## [shared] Módulos parametrizables

```sql
-- routines: estructura genérica, sin nombres de gym ni de dojo
routines (
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  name text not null,
  context_type text not null,   -- 'strength' | 'martial_arts_drill' | futuro
  created_by uuid references profiles
)

routine_days (
  id uuid primary key default gen_random_uuid(),
  routine_id uuid references routines,
  position int not null,
  label text
)

routine_exercises (
  id uuid primary key default gen_random_uuid(),
  routine_day_id uuid references routine_days,
  exercise_name text not null,
  target_sets int,
  target_reps int,
  notes text
)

-- classes: reserva de cupo genérica; el "tipo" de clase lo define el contexto de negocio, no la tabla
gym_scheduled_classes (   -- nombre heredado, se mantiene por continuidad con hooks ya extraídos
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  martial_art_id uuid,            -- nullable: null = clase genérica no ligada a disciplina
  name text not null,
  starts_at timestamptz not null,
  capacity int
)

class_reservations (
  id uuid primary key default gen_random_uuid(),
  class_id uuid references gym_scheduled_classes,
  member_id uuid references profiles,
  status text check (status in ('confirmed','cancelled')) default 'confirmed',
  attended boolean
)

-- content: se porta la familia content_*/community_* completa, ya era genérica de por sí
content (
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  category_id uuid,
  title text not null,
  body text,
  required_plan_id uuid references membership_plans   -- gating por plan, ya existía
)
```

## [dojo] Disciplinas y rangos

```sql
martial_arts (
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  name text not null,             -- 'Karate', 'BJJ', 'MMA', 'Krav Magá'
  unique (org_id, name)
)

ranks (
  id uuid primary key default gen_random_uuid(),
  martial_art_id uuid references martial_arts,
  name text not null,             -- 'Cinturón blanco', 'Franja azul', etc.
  level int not null,             -- orden de progresión
  color_hex text,
  stripes_to_promote int default 0
)

-- ÚNICA fuente de verdad del rango — se descarta org_members.current_rank_id
member_ranks (
  member_id uuid references profiles,
  martial_art_id uuid references martial_arts,
  current_rank_id uuid references ranks,
  current_stripes int default 0,
  updated_at timestamptz default now(),
  primary key (member_id, martial_art_id)
)
```

## [dojo] Sparring (retos amistosos)

```sql
sparring_challenges (
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  martial_art_id uuid references martial_arts not null,  -- confirmado: siempre ligado a disciplina
  challenger_id uuid references profiles not null,
  opponent_id uuid references profiles not null,
  status text check (status in ('pending','accepted','declined','completed','cancelled')) default 'pending',
  created_at timestamptz default now(),
  scheduled_at timestamptz
)

sparring_notes (
  id uuid primary key default gen_random_uuid(),
  challenge_id uuid references sparring_challenges,
  author_id uuid references profiles,
  note text,
  created_at timestamptz default now()
)
```
Directo entre miembros, sin aprobación de instructor — confirmado. La notificación (in-app vía Realtime + push) se especifica en la sección de notificaciones (módulo compartido).

## [dojo] Promociones — con las correcciones de los 11 casos borde

```sql
promotion_events (
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  martial_art_id uuid references martial_arts not null,
  name text not null,
  event_date date,
  passing_score numeric,             -- nullable sigue existiendo, pero ver regla de cierre abajo
  target_rank_id uuid references ranks,   -- nullable: null = "siguiente rango" dinámico
  promotion_action text check (promotion_action in ('rank','stripe')) not null,
  attendance_window_months int default 3,
  status text check (status in ('draft','active','completed')) default 'draft'
)

promotion_criteria (
  id uuid primary key default gen_random_uuid(),
  event_id uuid references promotion_events,
  name text not null,
  max_score numeric not null,
  weight numeric not null
)

promotion_candidates (
  id uuid primary key default gen_random_uuid(),
  event_id uuid references promotion_events,
  member_id uuid references profiles,
  -- current_rank_id ELIMINADA: siempre se calcula en vivo desde member_ranks (patrón live_rank ya validado)
  status text check (status in ('pending','promoted','not_promoted','withdrawn')) default 'pending',
  final_score numeric
)

promotion_scores (
  candidate_id uuid references promotion_candidates,
  criteria_id uuid references promotion_criteria,
  score numeric not null,
  primary key (candidate_id, criteria_id)
  -- sin constraint de DB: score <= max_score se valida en el server action, no a nivel de columna
  -- (decisión: dejar flexibilidad de aplicación por si se necesita puntaje bonus en el futuro)
)
```

**Reglas de negocio que se corrigen respecto al código actual (server-side, no solo UI):**
- Un evento puede cerrarse (`status='completed'`) sin `passing_score` definido — es un estado válido, no requiere confirmación especial ni bloqueo. Simplemente esos candidatos no se resuelven automáticamente vía score.
- `removeCandidate`/`deleteCriteria` validan `event.status == 'draft'` en el server action, no solo se ocultan en la UI.
- La fórmula de cálculo (promedio ponderado normalizado a base 10) vive en **una función pura compartida**, importada tanto por el cliente (preview en vivo) como por el server action de resolución — nunca duplicada.
- La resincronización de rango tras un ascenso solo toca `member_ranks` de la disciplina afectada — no recalcula ni resetea franjas de otras disciplinas del miembro.

## [dojo] Portal del miembro — módulo nuevo (hallazgo §9 de la extracción)
No existe hoy. Se agrega como requerimiento explícito:

```sql
-- No requiere tabla nueva — es una función expuesta al propio miembro, no solo a admin
-- getMemberPromotionHistory(member_id) debe permitir member_id = auth.uid(), no solo requireAdmin()
```
Esto se documenta como historia de usuario en la sección de requerimientos (sección 5).

## [dojo] Torneos

```sql
tournaments (
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  martial_art_id uuid references martial_arts,
  name text not null,
  tournament_date date,
  source_promotion_event_id uuid references promotion_events  -- para el puente ya existente
)

tournament_divisions (
  id uuid primary key default gen_random_uuid(),
  tournament_id uuid references tournaments,
  name text not null,
  position int
)

tournament_participants (
  id uuid primary key default gen_random_uuid(),
  division_id uuid references tournament_divisions,
  member_id uuid references profiles,
  rank_snapshot_id uuid references ranks   -- se llena de verdad desde member_ranks, no queda null como hoy
)

tournament_matches (
  id uuid primary key default gen_random_uuid(),
  division_id uuid references tournament_divisions,
  participant_a_id uuid references tournament_participants,
  participant_b_id uuid references tournament_participants,
  winner_id uuid references tournament_participants,
  score_a int,
  score_b int
)
```

## [dojo] Historial de peleas oficiales — adenda (se había quedado fuera)

Distinta de `sparring_challenges`: esto es el registro de peleas competitivas/oficiales de un miembro (no el reto informal 1-a-1), y alimenta tanto el perfil individual como el feed de "próximas peleas" en el dashboard principal.

```sql
member_fights (
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  member_id uuid references profiles not null,
  martial_art_id uuid references martial_arts not null,
  opponent_name text,                 -- texto libre: el rival puede ser externo, no siempre otro miembro
  opponent_member_id uuid references profiles,  -- nullable: si el rival sí es miembro del dojo
  event_name text,                    -- ej. "Copa Nacional de Karate 2026", nullable si es informal-competitivo
  fight_date date not null,
  result text check (result in ('win','loss','draw','upcoming')) not null,
  method text,                        -- ej. "decisión", "sumisión", "KO" — libre, varía mucho por disciplina
  notes text,
  created_at timestamptz default now()
)
```

**Regla del feed de "próximas peleas":** cualquier fila con `result = 'upcoming'` y `fight_date >= now()` es visible en el dashboard principal para todos los miembros de la organización (no solo para el propio miembro) — esto es intencional, es el mecanismo social de "hay gente compitiendo" que describiste. El resto de resultados (`win`/`loss`/`draw`) solo entra al feed general si el propio miembro lo marca como público (ver `is_public` abajo); por defecto el historial completo es privado del miembro y visible para admin/owner.

```sql
alter table member_fights add column is_public boolean default true;
-- default true porque hoy en GymBase ya funciona así (feed abierto); si preferís default false, es un toggle simple
```

RLS de esta tabla se detalla en la sección 3 junto con el resto, pero queda anotado que necesita dos niveles de visibilidad (propio + org completa) a diferencia de casi todo lo demás del schema que es org-scoped simple.

## Pendiente para la siguiente sección
Sección 3: mecanismo de JWT/tenant y el detalle completo de RLS por tabla (incluyendo el fix del hallazgo de `push_subscriptions` sin filtro de org que señaló la auditoría original, y la visibilidad de dos niveles de `member_fights` recién agregada).
