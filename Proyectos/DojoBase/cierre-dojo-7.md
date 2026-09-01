---
tipo: cierre-modulo
ticket: DOJO-7
---

# Cierre — DOJO-7 (Disciplinas y rangos)

Ver también: [[Proyectos/DojoBase/README|DojoBase]] · [[Proyectos/DojoBase/schema-dojo|schema-dojo.md]]

Paso 8 del plan del módulo (`corebase/modulos/dojo-disciplinas-rangos/plan.md`):
qué se desvió del plan original en los 8 pasos, y por qué. El detalle paso a
paso con comandos y números vive en `corebase/ESTADO.md`; esto es la síntesis
para quien no va a leer el diff.

## Qué se planeó vs. qué pasó

El plan original tenía 8 pasos de abajo hacia arriba (migración → server
actions → UI). Los 8 se completaron, pero cuatro de ellos dejaron trabajo
real que no estaba listado, y el paso 8 mismo — el cierre — se convirtió en
una pasada completa de optimización, code review y QA además del cierre en
sí, a pedido explícito de Marcos.

### 1. La unicidad de nivel no quedó como trigger

El plan decía "trigger de unicidad de nivel". Terminó como **constraint
`deferrable`** — Postgres ya resuelve esto nativamente y es menos código que
mantener. Consecuencia en cadena: una constraint deferrable no sirve de nada
sin una acción que reordene *todos* los niveles en una sola transacción, así
que salió `reorder_ranks()` (RPC) en el paso 3, que no estaba en la lista
original.

### 2. El tipo `Database` no podía vivir en la capa compartida

Al llegar la primera tabla vertical (`ranks`), el lint anti-fuga rechazó el
tipo `Database` generado por `supabase gen types` en `packages/core/src/db`
— ese tipo vuelca el schema `public` completo, así que en cuanto existe una
sola tabla de producto ya no puede vivir en la capa compartida. Se movió a
`apps/dojobase/src/lib/supabase/database.types.ts`, y con él las migraciones
010/011 de `supabase/migrations/` a `apps/dojobase/supabase/migrations/`.
Esto es un hallazgo estructural para cualquier vertical futura, no solo para
DojoBase: la primera tabla propia de cada app va a pegar contra el mismo
lint.

### 3. Tailwind no escaneaba `packages/ui` ni `packages/core`

El más grande de los tres hallazgos estructurales. Turbopack solo escaneaba
`apps/dojobase` en busca de clases Tailwind — cualquier utilidad que solo
existiera dentro de un componente de `packages/ui` sin aparecer, por
coincidencia, en algún archivo de la app **no generaba su CSS, sin error ni
warning**. Se descubrió porque la variante `danger` de `Button` (nunca usada
hasta `ConfirmDialog`, paso 5) no tenía fondo. Se corrigió con dos
directivas `@source` en `globals.css`. Esto pudo estar rompiendo
silenciosamente cualquier variante poco usada del design system desde que
existe el repo — sigue pendiente auditar visualmente el resto del catálogo
(`Stepper`, `SegmentedControl`, tonos poco comunes de `Badge`) ahora que el
escaneo es correcto.

### 4. Dos criterios de aceptación se adelantaron fuera de su paso

- **HU-00 CA-05** (desactivar disciplina sin borrar historial) — el paso 6
  no lo listaba, pero es una CA explícita y salió barato como una acción
  directa junto al resto de la pantalla.
- **HU-28 CA-01** (la lista de Miembros muestra el rango inline) — se
  adelantó en el paso 7 porque fue literalmente lo que Marcos pidió al ver
  la lista pelada la primera vez que abrió Dojo Alfa en esta sesión. No
  estaba planeado para DOJO-7; iba a esperar al módulo de miembros.

### 5. Bugs reales encontrados probando de verdad, no en el plan

Cada paso de UI (5, 6, 7) encontró bugs que solo aparecen probando en el
navegador, no con tipos ni lint:

- Vista previa de `FormRango` crasheaba con un color hex a medio escribir.
- Botones de reordenar (↑/↓) se renderizaban vacíos por pasar el ícono como
  `children` en vez de como prop `icon`.
- `editarDisciplina` reseteaba `progression_style`/`rank_display` en
  cualquier edición — un `.partial()` de Zod no vuelve `undefined` un campo
  con `.default()`, lo rellena con el default aunque no venga en el input.
  Este patrón vale para cualquier schema de edición parcial en el repo, no
  solo este.
- Nada impedía asignarle a un miembro un rango de una disciplina distinta —
  faltaba una FK compuesta contra `ranks(id, discipline_id)`.
- Dos "bugs" que resultaron ser fantasmas de la herramienta de captura de
  pantalla/pestaña (instabilidad contra un `<dialog>` nativo abierto, y
  estado acumulado de pestaña por navegaciones repetidas durante debugging),
  no del código — confirmados como falsos con lectura directa del DOM/estado
  de React antes de tocar nada.

## El paso 8 en sí: más que un cierre

Lo pedido para el paso 8 era solo "qué se desvió → al vault". Lo que se hizo
además, a pedido explícito en esta sesión ("optimización, code review y un
poco de QA a todo"):

**Code review independiente sobre todo el diff de `corebase`** (`/code-review
high`, en background): 10 hallazgos, evaluados uno por uno en vez de
aplicados a ciegas.

- **Corregidos por ser bugs reales:**
  1. `FormRango` no podía *borrar* un campo opcional ya seteado — el cliente
     siempre mandaba `undefined` para un campo vacío, que el schema Zod
     interpreta como "no tocar", sin distinguir "no lo llenaste" (al crear)
     de "lo vaciaste" (al editar). Se agregó `.nullable()` a los campos
     opcionales y el cliente ahora manda `null` explícito al editar.
  2. `onClose` de `FormModal`/`ConfirmDialog` se disparaba dos veces al
     presionar Escape — `onCancel` (redundante) y el evento nativo `close`
     del `<dialog>` llamaban a lo mismo.
  3. El trigger `assert_stripes_match_progression` permitía franjas
     (`current_stripes > 0`) sin un rango asignado (`current_rank_id null`)
     — solo validaba el estilo de progresión, nunca que hubiera rango.
  4. `moverRango` (reordenar) no tenía guarda contra un segundo clic en el
     mismo tick de React, antes de que el primer reordenamiento se reflejara
     en el estado.
  7. `ETIQUETA_ROL` (owner/admin/member → Dueño/Instructor/Alumno) estaba
     declarado seis veces en cinco archivos distintos, ya divergiendo en
     forma (`Record<Rol,string>` en uno, `as const` en otro). Al
     centralizarlo salió un bug propio, atrapado antes de llegar a
     producción: `MenuUsuario.tsx` es un Client Component, y un *valor*
     importado de `lib/session.ts` (a diferencia de un `type`, que se borra
     en compilación) arrastra al bundle del cliente el `next/headers` que
     `session.ts` importa transitivamente — Next lo rechaza en build. La
     centralización terminó en un archivo nuevo, `lib/roles.ts`, sin
     dependencias server-only, exactamente para que esto no vuelva a pasar.
  8. El patrón `ranks.filter(discipline_id).sort(level)` repetido en D7, D3
     y el modal de asignar — un helper (`rangosDeDisciplina`) en
     `lib/rangos.ts`.
  9. Las columnas de `select()` para `disciplines`/`ranks` copiadas
     literalmente en tres pantallas — dos constantes exportadas
     (`DISCIPLINE_COLUMNS`, `RANK_COLUMNS`).
  10. Un `.filter().map().filter(x => x !== null)` en `FilaMiembro`
      simplificado a un solo `.flatMap()`.
- **Evaluado y descartado a propósito:** el hallazgo #6 (`crearRango` hace
  un SELECT del último nivel y después un INSERT, dos viajes con una
  ventana de carrera) ya tenía manejo explícito del choque (código `23505`,
  mensaje de "probá de nuevo") con una razón documentada en el propio código:
  es un admin armando su escala, no tráfico real, y pedir que reintente
  alcanza. Convertirlo en una RPC atómica sería sobre-ingeniería para el
  volumen real de este módulo.
- **Notado pero fuera de alcance:** `crear-cuenta/page.tsx` tiene su propio
  mapa de roles con forma distinta (`Record<string, string>` con fallback
  para roles desconocidos de una invitación). No se tocó — es un archivo
  preexistente que esta sesión no había modificado, y su contrato de tipos
  es genuinamente distinto al de `Rol`.

**Optimización de base de datos** (vía advisors de Supabase, no parte del
code review): las políticas RLS de escritura de `disciplines`/`ranks`/
`member_ranks` eran `for all`, lo que incluye `SELECT` — cada lectura
evaluaba esa política *y* la de lectura, ambas permisivas. Se separaron en
`insert`/`update`/`delete` explícitos. Además, tres FKs sin índice que las
cubra (dos compuestas contra `(discipline_id, org_id)`, una compuesta contra
`(current_rank_id, discipline_id)`) — cubiertas con tres migraciones nuevas
(017, 018).

**QA manual en el navegador** después de todo lo anterior: se creó una
disciplina y un rango de prueba, se verificó que borrar un campo opcional
persiste como `null` tras recargar (no solo en el estado del formulario), que
Escape cierra el modal una sola vez, que asignar un rango con franjas
funciona de punta a punta, y que tanto la ficha del miembro como la lista
usan los mismos helpers centralizados sin romperse. Limpieza de los datos de
prueba al final, sin dejar residuo en la base de demo.

## Qué queda para después de DOJO-7

- Auditar visualmente el resto de `packages/ui` por si algo más se veía
  "bien" antes del fix de Tailwind solo por casualidad (punto 3 de arriba).
- El PATH de este entorno Windows no tiene `pnpm` como binario propio, solo
  vía Corepack — rompe `turbo run typecheck` y cualquier script que llame a
  `pnpm` reentrante. Documentado en `corebase/CLAUDE.md`; se arregla una vez
  por máquina con `corepack enable`, no es un problema del repo.
- El patrón de `.partial()` + `.default()` de Zod (punto 5) es un footgun
  general del repo, no solo de este módulo — vale la pena tenerlo presente
  en cualquier schema de edición parcial futuro.

DOJO-7 queda completo y verificado — `corebase/ESTADO.md` tiene el detalle
paso a paso con comandos y números.
