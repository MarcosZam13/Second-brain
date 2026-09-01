---
proyecto: DojoBase
tema: Schema de base de datos — capa vertical (artes marciales)
fecha: 2026-08-28
tipo: documentacion
estado: v1.0 — corregido y completado, reemplaza la parte [dojo] del spec 02
tags: [dojobase, schema, supabase, postgres]
---

# Schema — DojoBase (capa vertical)

Ver también: [[Proyectos/DojoBase/README|README]] · [[Proyectos/CoreBase/schema|schema.md (core y módulos)]] · [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]] · [[Proyectos/CoreBase/arquitectura|arquitectura.md]]

> Reemplaza la parte `[dojo]` de `_fuentes/02-spec-schema-database.md`. Estas tablas viven en `apps/dojobase/supabase/migrations/`, nunca en la raíz del monorepo — son lógica de disciplina marcial y no tienen nada que hacer en CoreBase. Cambios respecto al spec marcados con **▲**.

## 1. Configuración de la organización — extensión del vertical

```sql
-- ▲ El spec 01 la mencionaba pero nunca la definió
dojo_org_settings (
  org_id                    uuid primary key references organizations on delete cascade,
  sinpe_number              text,
  sinpe_holder_name         text,
  payment_mode              text not null default 'manual_sinpe'
                            check (payment_mode in ('manual_sinpe','onvo')),
  class_cancel_minutes      int default 30,     -- antelación mínima para cancelar inscripción
  sparring_expiry_days      int default 14,     -- RF-06b
  default_attendance_window_months int default 3,
  updated_at                timestamptz default now()
)

-- ▲ NUEVA: datos de competencia del alumno. Lo personal (cédula, nacimiento,
-- contacto de emergencia) vive en `member_profiles` del core: le sirve a
-- cualquier producto, no solo a un dojo.
dojo_member_details (
  member_id            uuid references profiles on delete cascade,
  org_id               uuid not null references organizations on delete cascade,
  federation_id        text,                    -- número de federación o asociación
  insurance_provider   text,
  insurance_policy     text,
  weight_class         text,                    -- categoría habitual, ej. '-77 kg'
  competes             boolean default false,
  medical_notes        text,                    -- lesiones y condiciones relevantes
  updated_at           timestamptz default now(),
  primary key (member_id, org_id)
)
```

Es la tabla que evita repetir el error de v1, donde `organizations` cargaba `gym_name`, `sinpe_number`, `sinpe_name`, `max_capacity` y `cancel_minutes` — columnas de un vertical dentro del core.

**El problema que resuelve `dojo_member_details`** (planteado por el usuario el 2026-08-28): para
inscribir a un alumno a un torneo hay que reunir cédula, fecha de nacimiento, peso actual, seguro,
federación y contacto de emergencia — y hoy eso está disperso o directamente no está. Con esta
tabla más `member_profiles` (core) y la última medición de peso, la **ficha para torneo** es una
consulta, no una búsqueda. La app además **marca los campos faltantes antes** de que hagan falta,
en vez de que aparezcan el día de la inscripción.

## 2. Disciplinas y rangos

```sql
disciplines (                                    -- ▲ renombrada desde martial_arts: más neutra
  id         uuid primary key default gen_random_uuid(),
  org_id     uuid not null references organizations on delete cascade,
  name       text not null,                      -- 'Karate', 'BJJ', 'MMA', 'Krav Magá'
  color      text,
  position   int default 0,
  is_active  boolean default true,               -- ▲ desactivar sin borrar el historial

  -- ▲▲ CÓMO PROGRESA ESTA DISCIPLINA. Ver la nota de abajo: es la corrección
  -- más importante del modelo, y no estaba en ningún spec.
  progression_style text not null default 'direct'
    check (progression_style in ('direct','stripes','time_based')),
  -- ▲ Valores con que se anota un sparring. En BJJ una barrida son 2, un pase 3
  -- y una montada 4; en karate 1, 2 y 3. Cuatro botones de valor directo, no un
  -- stepper de a uno.
  score_increments  int[] not null default '{1,2,3,4}',
  rank_display      text not null default 'belt'
    check (rank_display in ('belt','patch','none')),

  created_at timestamptz default now(),
  unique (org_id, name)
)

ranks (
  id                uuid primary key default gen_random_uuid(),
  org_id            uuid not null references organizations on delete cascade,  -- ▲
  discipline_id     uuid not null references disciplines on delete cascade,
  name              text not null,               -- 'Cinturón marrón', 'Franja azul'
  short_label       text,                        -- ▲ '3.º kyu', '1.º dan', 'P2'
  level             int not null,                -- orden de progresión
  color_hex         text,
  secondary_color_hex text,                      -- cinturones bicolor
  stripes_to_promote int default 0,              -- ▲ solo aplica si progression_style='stripes'
  min_months_in_rank int,                        -- ▲ tiempo mínimo antes de poder ascender
  min_classes_to_promote int,                    -- ▲ asistencia mínima acumulada
  created_at        timestamptz default now(),
  unique (discipline_id, level)                  -- ▲ dos rangos no pueden compartir nivel
)

-- ÚNICA fuente de verdad del rango de un miembro
member_ranks (
  member_id      uuid references profiles on delete cascade,
  discipline_id  uuid references disciplines on delete cascade,
  org_id         uuid not null references organizations on delete cascade,
  current_rank_id uuid references ranks,
  current_stripes int default 0 check (current_stripes >= 0),
  updated_at     timestamptz default now(),
  primary key (member_id, discipline_id)
)
```


### ▲▲ Cada disciplina progresa distinto — corrección del 2026-08-28

Los specs originales asumían que **toda** disciplina acumula franjas dentro del rango, porque el
modelo se derivó de BJJ. Es falso, y el usuario lo señaló al revisar los mockups:

| Estilo | Quién | Cómo funciona |
|---|---|---|
| `direct` | **Karate**, krav magá, taekwondo | Se asciende de un rango al siguiente, por examen. **No hay franjas.** El grado se nombra con `short_label` (`3.º kyu`, `1.º dan`) |
| `stripes` | **BJJ** — y hasta donde sabemos, es el único | Se acumulan franjas dentro del cinturón hasta llegar al tope, y ahí se asciende de cinturón |
| `time_based` | **MMA** y disciplinas sin sistema formal de grados | No hay escalera de rangos. El progreso se mide por tiempo entrenando, clases asistidas y récord competitivo. `ranks` puede estar vacía para esta disciplina |

`rank_display` es una decisión aparte de cómo se progresa: `belt` dibuja el cinturón, `patch` un
parche o nivel (krav magá usa niveles P/G/E, no cinturones), `none` no muestra insignia.

**Por qué importa más de lo que parece.** Dibujarle franjas a un cinturón de karate no es un detalle
cosmético: es inventarle a la escuela un sistema de grados que no tiene. Un sensei lo nota en la
primera pantalla, y es exactamente el tipo de error que hace que un producto se vea hecho por
alguien que no entiende el negocio.

Y respeta RNF-06: si aparece una disciplina con otro sistema, es una fila con otro
`progression_style`, no un caso especial en el código. Si ninguno de los tres calza, se agrega un
valor al check — pero primero hay que confirmar con quien la practica, no suponerlo.

**No es un bloqueante confirmar el estilo exacto de MMA.** `progression_style` se elige por
disciplina al crearla (HU-00b CA-01) — no es una decisión que tome el sistema por adelantado.
`time_based` es el preset sugerido para MMA porque es lo que describió el usuario, pero si un dojo
real la practica distinto, se cambia esa fila sin tocar código ni schema. Lo mismo vale para
cualquier disciplina que no calce en ninguno de los tres estilos con cinturón/franjas/parche: con
`rank_display = 'none'`, un `progression_style = 'direct'` ya funciona como una escalera de rangos
totalmente libre — nombre, `short_label` y color por rango, sin insignia dibujada — que es la forma
más simple de decir "rangos personalizados" sin agregar un cuarto valor al check.

**▲ Corrección de fondo.** Se descarta `org_members.current_rank_id` y `current_rank_stripes` de v1. Coexistían con `org_member_ranks` (el equivalente correcto por disciplina) sin ningún trigger que las mantuviera sincronizadas, y la lógica de resincronización tenía un bug real: al ascender en una disciplina secundaria, reseteaba las franjas del rango "general" — que podía ser el de otra disciplina que ni participó del ascenso (caso borde 7 de `logica-promociones.md`).

Acá el rango vive **solo** en `member_ranks`, una fila por disciplina. Si la UI necesita un "rango principal" para mostrar en el avatar, se calcula en vivo (el de mayor `level`), no se almacena.

**▲ `ranks.org_id` denormalizado:** el spec lo dejaba colgando de `discipline_id`. Tenerlo directo abarata cada policy y cada índice.

## 3. Sparring — retos amistosos

```sql
sparring_challenges (
  id                 uuid primary key default gen_random_uuid(),
  org_id             uuid not null references organizations on delete cascade,
  discipline_id      uuid not null references disciplines,    -- siempre ligado a disciplina (RF-05)
  challenger_id      uuid not null references profiles,
  opponent_id        uuid not null references profiles,
  status             text default 'pending'
                     check (status in ('pending','accepted','declined','completed','cancelled')),
  winner_id          uuid references profiles,                -- ▲ el spec lo mencionaba al pasar
  opponent_confirmed boolean default false,                   -- ▲ decisión 4
  -- ▲▲ La sesión tiene cronómetro. Hallazgo del repaso de v1: ningún spec lo
  -- mencionaba, y es la mitad de la función. Ver la nota de abajo.
  total_rounds       int not null default 3 check (total_rounds between 1 and 12),
  round_seconds      int not null default 180 check (round_seconds between 30 and 900),
  rest_seconds       int not null default 60 check (rest_seconds >= 0),
  scheduled_at       timestamptz,
  responded_at       timestamptz,                             -- ▲ base para la expiración
  completed_at       timestamptz,                             -- ▲
  created_at         timestamptz default now(),
  check (challenger_id <> opponent_id)                        -- ▲ no retarse a sí mismo
)

sparring_rounds (
  id               uuid primary key default gen_random_uuid(),
  org_id           uuid not null references organizations on delete cascade,   -- ▲
  challenge_id     uuid not null references sparring_challenges on delete cascade,
  round_number     int not null,
  challenger_score int,
  opponent_score   int,
  notes            text,
  recorded_at      timestamptz default now(),
  unique (challenge_id, round_number)
)

sparring_notes (
  id           uuid primary key default gen_random_uuid(),
  org_id       uuid not null references organizations on delete cascade,
  challenge_id uuid not null references sparring_challenges on delete cascade,
  author_id    uuid references profiles,
  note         text not null,
  created_at   timestamptz default now()
)
```

### ▲▲ El sparring tiene cronómetro — hallazgo del repaso de v1

`SparringSessionModal.tsx` de v1 corre una máquina de cuatro fases a pantalla completa:
**cronómetro del round → cargar resultado → descanso → resumen**, con `total_rounds` y
`round_duration_seconds` configurables al crear el reto (3 rounds de 180 s por defecto).

Esto cambia qué es la pantalla del marcador. No es un formulario para anotar puntos después: es
**la herramienta que se usa durante el sparring**, con el celular apoyado al lado del tatami. El
teclado de puntos encaja ahí dentro — se anota mientras corre el round.

Requisitos que salen de eso, y que no son obvios hasta que se usa:

- El cronómetro **sigue corriendo con la pantalla apagada o la app en segundo plano**: el tiempo se
  calcula contra un instante de inicio, no con un contador que se descuenta. Un `setInterval` que
  se pausa cuando el navegador suspende la pestaña arruina el round.
- **Aviso sonoro y vibración** al faltar 10 segundos y al terminar el round. Nadie mira la pantalla
  mientras pelea.
- El paso a descanso es automático; el paso al round siguiente **lo confirma la persona**, porque
  el descanso real nunca dura exactamente lo configurado.

**Flujo (RF-06):** el challenger crea → el rival acepta o rechaza → el challenger carga los rounds → al cerrar, el server action calcula `winner_id` con la **función pura compartida** de suma de rounds → el rival confirma.

**▲ Confirmación del rival (decisión 4).** El spec dejaba el resultado auto-reportado por el challenger, sin derecho a réplica, alimentando un historial explícitamente social ("llevo 3-1 contra Fulano"). Eso no sobrevive al primer conflicto entre dos alumnos. Con `opponent_confirmed`, el head-to-head cuenta **solo lo confirmado**; lo no confirmado se ve en el detalle del reto como "pendiente de confirmación", no en el marcador.

**Expiración (RF-06b, HU-09c):** un reto `pending` sin respuesta, o `accepted` sin rounds cargados, por más de `dojo_org_settings.sparring_expiry_days`, pasa a `cancelled`. Lo hace el **job diario único** definido en la arquitectura, junto con los recordatorios de pago y la expiración de suscripciones — no tres mecanismos distintos.

**Head-to-head (RF-07, HU-08):** vista con `security_invoker`, que hereda el RLS de `sparring_challenges`. Cuenta enfrentamientos `completed` y `opponent_confirmed = true`, agrupando por el par ordenado de miembros y la disciplina.

## 4. Promociones

```sql
promotion_events (
  id                       uuid primary key default gen_random_uuid(),
  org_id                   uuid not null references organizations on delete cascade,
  discipline_id            uuid not null references disciplines,
  name                     text not null,
  event_date               date,
  passing_score            numeric,          -- nullable: evento sin nota mínima es válido
  target_rank_id           uuid references ranks,   -- nullable = "siguiente rango" dinámico
  promotion_action         text not null check (promotion_action in ('rank','stripe')),
  attendance_window_months int default 3,
  status                   text default 'draft'
                           check (status in ('draft','active','completed')),
  completed_at             timestamptz,      -- ▲
  created_by               uuid references profiles
)

promotion_criteria (
  id         uuid primary key default gen_random_uuid(),
  org_id     uuid not null references organizations on delete cascade,   -- ▲
  event_id   uuid not null references promotion_events on delete cascade,
  name       text not null,
  max_score  numeric not null check (max_score > 0),
  weight     numeric not null check (weight > 0),
  position   int default 0
)

promotion_candidates (
  id             uuid primary key default gen_random_uuid(),
  org_id         uuid not null references organizations on delete cascade,   -- ▲
  event_id       uuid not null references promotion_events on delete cascade,
  member_id      uuid not null references profiles,
  rank_at_entry_id uuid references ranks,     -- ▲ snapshot real al postular, ver abajo
  status         text default 'pending'
                 check (status in ('pending','promoted','not_promoted','withdrawn')),
  final_score    numeric,
  scored_criteria_count int default 0,        -- ▲ para detectar evaluación incompleta
  resolved_at    timestamptz,                 -- ▲
  unique (event_id, member_id)                -- ▲ nada impedía duplicar un candidato
)

promotion_scores (
  org_id      uuid not null references organizations on delete cascade,   -- ▲
  candidate_id uuid references promotion_candidates on delete cascade,
  criteria_id uuid references promotion_criteria on delete cascade,
  score       numeric not null,
  updated_at  timestamptz default now(),
  primary key (candidate_id, criteria_id)
)
```

### Los 11 casos borde de v1, resueltos

`logica-promociones.md` documenta 11 comportamientos no especificados del código actual. Los specs cerraban 7; los otros 4 quedan resueltos acá.

| # | Caso borde de v1 | Resolución en DojoBase |
|---|---|---|
| 1 | Evento cerrado sin `passing_score` deja candidatos `pending` sin salida en la UI | Un evento `completed` puede **reabrirse** a `active` por un admin (HU-13b). Cerrar sin nota mínima es un estado válido, no requiere confirmación especial |
| 2 ▲ | `final_score` grabado queda desincronizado del que se ve en pantalla si se sigue calificando tras decidir | **`upsertScore` bloquea la edición de un candidato ya resuelto.** Para corregir un puntaje hay que revertir la decisión primero (`status` vuelve a `pending`). Una fuente de verdad, no dos |
| 3 | Fórmula duplicada cliente/servidor | **Función pura compartida**, una sola implementación importada por ambos |
| 4 ▲ | Calificar solo algunos criterios sesga el promedio a favor, sin aviso | `scored_criteria_count` vs. total de criterios del evento. **La UI marca "evaluación incompleta"** y la resolución automática **excluye** a los incompletos en vez de aprobarlos sobre base parcial. El admin sí puede resolverlos a mano, viendo el aviso |
| 5 | `current_rank_id` del candidato es dead data (siempre null) | Se llena de verdad como **`rank_at_entry_id`**: snapshot real al postular. El rango vigente se sigue mostrando en vivo desde `member_ranks`; el snapshot existe para que el historial diga con qué cinturón se presentó |
| 6 | Rango objetivo dinámico calcula "el siguiente" en el momento de cada ascenso | Se mantiene (es el comportamiento correcto para un evento multi-rango), pero **la UI lo dice explícitamente**: "cada candidato asciende al siguiente rango de su propia escala" |
| 7 | Resincronizar el rango tras un ascenso resetea franjas de otras disciplinas | No aplica: se eliminó la columna denormalizada. Cada ascenso toca **solo** la fila de `member_ranks` de su disciplina |
| 8 ▲ | Franjas al tope (4/4) no ascienden solas ni avisan | La UI muestra **"listo para ascender"** cuando `current_stripes >= stripes_to_promote`, y el botón de franja queda deshabilitado con esa explicación en vez de sin motivo visible. El ascenso sigue siendo un acto deliberado del sensei — correcto — pero deja de ser invisible |
| 9 | El miembro no tiene ninguna forma de ver su historial de promociones | **HU-14, pantalla nueva**: historial propio, rango actual por disciplina y desglose por criterio. Habilitado por RLS (`promotion_scores` con acceso propio) y por un server action que acepta `member_id = auth.uid()` |
| 10 | `removeCandidate`/`deleteCriteria` sin guarda de estado en el servidor | Ambos **validan `event.status = 'draft'` en el server action**. Ocultar el botón no es un control (RNF-01) |
| 11 | El puntaje se valida contra 0-100 fijo, no contra el `max_score` del criterio | Validación en servidor contra el `max_score` **real de ese criterio** (RF-11b). Sin constraint de DB, para dejar abierto el puntaje bonus a futuro |

### Fórmula

Promedio ponderado normalizado a base 10: para cada criterio calificado, `(score / max_score) * 10 * weight`, dividido por la suma de los `weight` de los criterios calificados. **Una sola implementación** en `apps/dojobase/lib/promotions/score.ts`, importada por el preview en vivo del grid y por la resolución del servidor, con tests unitarios contra los casos borde (criterios incompletos, peso cero, puntaje bonus por encima del máximo).

## 5. Peleas oficiales

```sql
member_fights (
  id                 uuid primary key default gen_random_uuid(),
  org_id             uuid not null references organizations on delete cascade,
  member_id          uuid not null references profiles,
  discipline_id      uuid not null references disciplines,
  opponent_name      text,                       -- el rival puede ser externo
  opponent_member_id uuid references profiles,   -- nullable: si el rival es del dojo
  event_name         text,                       -- 'Copa Nacional de Karate 2026'
  fight_date         date not null,
  result             text not null check (result in ('win','loss','draw','upcoming')),
  method             text,                       -- 'decisión', 'sumisión', 'KO' — libre
  notes              text,
  is_public          boolean default false,      -- ▲ decisión 6: privado por default
  created_by         uuid references profiles,
  created_at         timestamptz default now()
)
create index on member_fights (org_id, result, fight_date);
```

**Distinta de `sparring_challenges`:** esto es el registro competitivo/oficial, lo carga el admin, y el rival puede ni ser miembro del dojo.

| Aspecto | `member_fights` (oficial) | `sparring_challenges` (amistoso) |
|---|---|---|
| Quién carga | Admin/owner exclusivamente (RF-09) | El propio challenger |
| Quién inicia | Admin registra el evento | Cualquier miembro reta a otro |
| Resultado | Lo llena el admin | Lo carga el challenger por rounds, lo confirma el rival |
| Rol del rival | N/A, puede ser externo | Acepta o rechaza, y confirma el resultado |

**▲ Feed de próximas peleas (decisión 6, RF-10).** El spec se contradecía: la prosa decía "el historial es privado por defecto" y el SQL ponía `is_public default true`. Queda `default false`. El feed social se sostiene igual porque **toda pelea `upcoming` es visible para la organización sin importar `is_public`** — que es exactamente el mecanismo de "hay gente compitiendo" que se buscaba. Los resultados entran al feed solo si el miembro los publica.

## 6. Torneos

```sql
tournaments (
  id                        uuid primary key default gen_random_uuid(),
  org_id                    uuid not null references organizations on delete cascade,
  discipline_id             uuid references disciplines,
  name                      text not null,
  tournament_date           date,
  status                    text default 'draft' check (status in ('draft','active','completed')),
  -- ▲ Token del kiosco de proyección: la pantalla de TV se abre sin sesión,
  -- así que necesita su propia llave en vez de exponer el torneo a cualquiera.
  projection_token          text unique,
  source_promotion_event_id uuid references promotion_events   -- puente ya existente en v1
)

tournament_divisions (
  id             uuid primary key default gen_random_uuid(),
  org_id         uuid not null references organizations on delete cascade,
  tournament_id  uuid not null references tournaments on delete cascade,
  name           text not null,
  min_weight_kg  numeric,      -- ▲ divisiones tipadas en vez de solo nombre libre
  max_weight_kg  numeric,      -- ▲
  min_rank_level int,          -- ▲
  max_rank_level int,          -- ▲
  bracket_size   int,
  position       int default 0
)

tournament_participants (
  id               uuid primary key default gen_random_uuid(),
  org_id           uuid not null references organizations on delete cascade,
  division_id      uuid not null references tournament_divisions on delete cascade,
  member_id        uuid not null references profiles,
  rank_snapshot_id uuid references ranks,     -- ▲ se llena de verdad desde member_ranks
  seed             int,
  unique (division_id, member_id)             -- ▲
)

tournament_matches (
  id                uuid primary key default gen_random_uuid(),
  org_id            uuid not null references organizations on delete cascade,
  division_id       uuid not null references tournament_divisions on delete cascade,
  round             int not null,
  match_number      int not null,
  is_third_place    boolean default false,
  participant_a_id  uuid references tournament_participants,
  participant_b_id  uuid references tournament_participants,
  winner_id         uuid references tournament_participants,
  score_a           int,
  score_b           int,
  method            text,
  duration_sec      int,
  unique (division_id, round, match_number, is_third_place)   -- ▲ incluye division_id
)
```

**▲ Fix heredado:** en v1 el `UNIQUE` de `tournament_matches` era `(tournament_id, round, match_number, is_third_place)` **sin `division_id`** — con dos divisiones activas al mismo tiempo en un torneo, las llaves colisionan. Acá la unicidad es por división, que es la unidad real del bracket.

**▲ Divisiones tipadas:** el spec dejaba `name` de texto libre. Con `min/max_weight_kg` y `min/max_rank_level` el sistema puede sugerir la división de cada participante en vez de que el admin la asigne a mano — es la diferencia entre un módulo usable y uno que nadie usa.

### ▲ Kiosco de proyección (confirmado en el repaso)

Pantalla pública de solo lectura, a pantalla completa y con zoom, para proyectar el bracket en vivo
en un televisor durante el torneo. Existe en v1 (`TournamentProjection.tsx`) y se conserva, con dos
cambios:

- **Realtime de verdad**, no `setInterval` cada 15 segundos como en v1. Es exactamente la pantalla
  que la auditoría marcó como "realtime falso donde más importa": un marcador proyectado que tarda
  15 segundos en actualizarse se nota desde el otro lado del gimnasio.
- **Acceso por `projection_token`**, no por sesión: la tableta o la laptop conectada al proyector no
  debería tener que iniciar sesión como admin, y ese token solo abre la vista de lectura de ese
  torneo.

**Alcance:** el modelo de datos entra ahora, pero **la UI de armado de brackets es lo primero que se cae** si el cronograma se atrasa (decisión 7). Registrar el torneo y sus resultados sin bracket automático ya tiene valor. La proyección depende del bracket, así que se cae con él.

## 7. Cobertura contra las historias de usuario

| HU / RF | Cubierto por |
|---|---|
| HU-00, RF-01/02/02b | `disciplines`, `ranks`, `member_ranks` |
| HU-03 | `member_ranks` + `class_reservations` (core) |
| HU-05 a HU-09c, RF-05/06/06b/07/08 | `sparring_challenges`, `sparring_rounds`, `sparring_notes`, vista head-to-head |
| HU-10, HU-11, RF-09/10 | `member_fights` |
| HU-12, HU-13, HU-13b, HU-14, RF-11/11b/12 | `promotion_events`, `promotion_criteria`, `promotion_candidates`, `promotion_scores` |
| HU-17 (SINPE) | `dojo_org_settings` + `payment_proofs` (core) |
| RF-06b, RF-17 | `dojo_org_settings` + job diario |
| Torneos (fuera de MVP) | `tournaments` y familia |

## 8. Lo que NO se porta de GymBase v1

Explícito para que ningún agente lo reintroduzca "porque ya existía":

- **Check-in por QR** (`gym_qr_codes`, `gym_attendance_logs`, kiosko, ocupación en tiempo real). Es el perfil de gimnasio de fitness. En un dojo la asistencia es por inscripción a clase.
- **Métricas de salud / InBody / fotos de progreso.** Perfil de gimnasio.
- **Inventario, ventas, POS, marketplace, gastos.** No entra al MVP de DojoBase; si un dojo lo pide, se evalúa como módulo compartido después.
- **Check-in por QR, ocupación en vivo, PRs y tests de 1RM** — perfil de gimnasio de fitness.
- **La página pública del dojo tal como está en v1** (`gym_about` y familia): contenido hardcodeado por cliente, con el editor de admin removido. **La función sí vuelve** (ver el repaso), pero como contenido editable desde la app — si no, cada dojo nuevo vuelve a ser un despliegue, que es el problema que este proyecto existe para resolver.
- **Las tablas legacy vacías** que v1 arrastra sin uso.
