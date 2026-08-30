---
tipo: cierre-modulo
ticket: DOJO-8
---

# Cierre — DOJO-8 (Clases y asistencia)

Ver también: [[Proyectos/DojoBase/README|DojoBase]] · [[Proyectos/CoreBase/schema|schema.md]]

Paso 10 del plan del módulo (`corebase/modulos/clases-asistencia/plan.md`):
qué se desvió del plan original en los 10 pasos, y por qué. El detalle paso
a paso con comandos y números vive en `corebase/ESTADO.md`; esto es la
síntesis para quien no va a leer el diff.

## Qué se planeó vs. qué pasó

Los 10 pasos se completaron. Es el primer módulo que toca la capa
compartida de CoreBase (no solo la vertical de DojoBase) y el primero que
consume `packages/modules`, así que salieron dos hallazgos estructurales
nuevos además de bugs puntuales.

### 1. Primer consumidor real de `packages/modules` y de `FormPage`

`packages/modules` no existía; salió de este módulo (la función de
recurrencia y los cuatro componentes de calendario/asistencia). `FormPage`/
`FormSection` tampoco existían en `packages/ui` — estaban nombradas en
`CLAUDE.md` ("FormPage para flujos multi-paso o con mucho contenido") pero
nunca se habían construido. Mismo patrón que `FormModal`/`ConfirmDialog` en
DOJO-7: salen de un consumidor real, no de adivinar la forma.

### 2. `class_reservations` no tiene ninguna policy de autoservicio

El primer diseño sí dejaba que un miembro insertara/actualizara su propia
fila. El advisor de performance de Supabase marcó `multiple_permissive_policies`
contra la policy de staff, y revisando el motivo de fondo apareció algo más
serio: esa policy de autoservicio también permitía marcarse `attended = true`
a mano por un PATCH directo, sin pasar por ninguna validación de cupo,
antelación o duplicados. Se sacaron las dos policies y `reservar_clase()`
pasó a `SECURITY DEFINER` (como ya lo era `cancelar_reserva()`): la única
forma de que un miembro toque esta tabla es a través de esas dos funciones.

### 3. Cinco bugs reales, encontrados probando de verdad en el navegador

Ninguno de los cinco lo atrapaban `tsc` ni `eslint` — coherente con el
patrón ya visto en DOJO-7 de que la mayoría de los bugs reales aparecen
recién al usar la pantalla, no al compilarla:

1. **Un reexport inválido tumbaba la pantalla de detalle en runtime.**
   `actions/clases.ts` reexportaba `CLASS_COLUMNS` (un string) desde un
   archivo `'use server'` — Next exige que todo export de ese archivo sea
   una función async. Nada lo necesitaba; se borró.
2. **El calendario semanal nunca mostraba "hoy" sin hacer scroll, ni en
   desktop.** `ClassCalendarWeek` usaba `flex` + un ancho mínimo por
   columna; 7 columnas no entran así ni en 1512px de ancho. El diseño pedía
   grilla completa en desktop, carrusel solo en mobile — `grid-cols-7` desde
   `md:` lo corrige.
3. **`FormPage` no enviaba nada al tocar "Crear clase"/"Guardar cambios".**
   El footer con el botón de submit se renderizaba como *hermano* del
   `<form>`, no como descendiente — un `<button type="submit">` fuera del
   árbol de un formulario no dispara `onSubmit` sin un atributo `form="id"`
   a mano. Se movió el footer adentro del `<form>`.
4. **Editar una clase sin tipo asignado fallaba siempre.**
   `esquemaEdicionClase.classTypeId` no tenía `.nullable()` (a diferencia de
   `disciplineId`, justo al lado, que sí lo tenía), y el formulario siempre
   manda `null` cuando el campo queda en "Sin tipo". Como ninguna clase de
   prueba tenía tipo, esto rompía toda edición — un error real que sí se
   mostraba en pantalla, encontrado recién después de perder un rato
   buscando el texto de error equivocado.
5. **El corrimiento de huso horario rompía qué día de la semana salía
   generado en una serie recurrente — el más serio de los cinco.**
   `generateOccurrences()` (`packages/modules`) elige ocurrencias por
   weekday en UTC, correctamente: es una función pura y no puede saber de
   Costa Rica. Pero el admin tilda el día pensando en hora local, y una
   clase de noche cruza la medianoche UTC (Costa Rica es UTC-6 sin horario
   de verano): "lunes 6pm" es "martes 00:00 UTC". Sin corregir esto, tildar
   "lunes y miércoles" generaba la serie real en **domingo y martes**, hora
   local — confirmado comparando el resultado contra lo tildado, probando
   con el navegador configurado en la zona horaria real de Costa Rica, no
   solo verificando que la función corriera sin tirar error. El ajuste
   (`diasSemanaLocalAUtc`) vive en `apps/dojobase/src/lib/clases.ts`, no en
   el paquete compartido: es conversión local↔UTC específica de esta app,
   no un cálculo genérico que le sirva igual a un gimnasio en otro huso
   horario.

### 4. `/code-review high` independiente sobre el PR: 10 hallazgos, los 10 aplicados

A diferencia de DOJO-7 (donde uno de diez se descartó a propósito por
sobre-ingeniería), acá los 10 se evaluaron como reales y de bajo riesgo:

- **El corrimiento UTC-6 no estaba corregido en toda la superficie donde
  aplicaba** — el fix del bug #5 de arriba solo tocaba qué días de la
  semana se mandan a `generateOccurrences()`. Faltaban otros tres lugares
  con el mismo supuesto roto ("el día UTC de `starts_at` es el día
  local"): el corte de "repetir hasta" (podía perder la última semana en
  una clase de noche), el agrupamiento de clases por día en las vistas de
  calendario/semana, y "hoy"/"semana actual". Se agregaron `hastaUtc()` y
  `ahoraCR()`/`aClaveFechaLocal()` junto al `diasSemanaLocalAUtc()` ya
  existente.
- `class_type_id` no tenía FK compuesta contra `org_id`, a diferencia de
  `discipline_id` (FK compuesta) e `instructor_id` (validado a mano en el
  server action) — un staff podía guardar el uuid de un tipo de clase de
  otra organización sin ningún error. Migración nueva
  (`class_types_org_fk`) lo cierra igual que las otras dos columnas.
- `editarClase` no traía `ends_at` en el `select()` de la clase actual, así
  que validar `endsAt > startsAt` en una edición que solo cambia el inicio
  comparaba contra `undefined`.
- `eliminarSerie` bloqueaba borrar una serie completa por reservas
  confirmadas en ocurrencias **futuras** (que nunca tienen asistencia
  tomada) — ahora solo mira ocurrencias pasadas.
- La regla de lint anti-vocabulario-vertical nunca corría sobre
  `packages/modules/` — un descuido al agregar el paquete nuevo a la lista
  de carpetas protegidas, sin que nada lo hubiera avisado hasta que el
  code review lo señaló explícitamente.
- Varios botones/elementos de navegación en `h-9`/`w-9`, fuera de la
  escala de píxeles del design system — el lint solo atrapa sintaxis
  arbitraria (`h-[36px]`), no utilidades estándar fuera de escala.
- Faltaba `router.refresh()` tras guardar una edición, así como conectar
  el helper `contarConfirmados()` (ya escrito, sin usar) en tres pantallas
  que seguían filtrando reservas confirmadas a mano.
- Pasar lista mandaba las correcciones de asistencia en un `for...await`
  secuencial en vez de en paralelo.

Efecto colateral de la FK nueva: `scheduled_classes` quedó con dos caminos
de FK hacia `class_types`, así que todo `select()` que embebe
`class_types(...)` necesita el hint
`class_types!scheduled_classes_class_type_org_fk(...)` — sin eso Supabase
devuelve un tipo de error genérico (`SelectQueryError`) que `tsc` sí
atrapa, pero que no dice de entrada cuál es el problema real.

`pnpm lint`/`test`/`build` limpios después de los 10 fixes; RLS 18/18 sin
regresión tras la migración nueva.

## Decisiones de alcance, tomadas antes de escribir código

- **Clases privadas por plan quedan fuera** (HU-01 CA-03, HU-04 CA-05):
  dependen de `membership_plans`/`subscriptions`, que no existen todavía —
  entran junto con el módulo de billing.
- **El aviso de cancelación de clase queda fuera** (HU-02c CA-02): la tabla
  `notifications` no está migrada. El motivo sí se guarda
  (`cancelled_reason`), solo falta el envío.
- **La ventana de asistencia elegible para promociones no se escribe acá**:
  sin el módulo de promociones no hay consumidor real todavía.
- **Reprogramar el día/hora de toda una serie de una vez no se soporta**:
  `editarClase` con alcance "serie" no toca `startsAt`/`endsAt`. El camino
  real es cancelar la serie y crear una nueva.

## Qué queda para después de DOJO-8

- `scheduled_classes.recurrence_rule` guarda los días en **UTC**, no los
  días locales que tildó el admin — si alguna pantalla futura necesita
  reconstruir y mostrar "esta serie repite los ___", necesita la conversión
  inversa, no leer la columna tal cual.
- Auditar `ClassCalendarMonth`/`AttendanceRoster` con volumen real de datos
  (muchas clases el mismo día, muchos inscritos) — se probaron con pocos
  registros.
- Clases privadas por plan (HU-01 CA-03, HU-04 CA-05), cuando exista billing.

DOJO-8 queda completo y verificado — `corebase/ESTADO.md` y
`modulos/clases-asistencia/{plan,decisiones}.md` tienen el detalle paso a
paso.
