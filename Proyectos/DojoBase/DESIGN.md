---
proyecto: DojoBase
tema: DESIGN.md — guía de diseño, sistema de componentes e inventario de pantallas
fecha: 2026-08-28
tipo: documentacion
estado: v1.4 — 48 pantallas mapeadas a HU. v1.1 incorporó la revisión de los mockups (progresión por disciplina, ficha del alumno, mediciones); v1.2 suma lo del repaso de GymBase v1: sesión de sparring con cronómetro, anuncios, avisos y proyección de torneos; v1.4 (2026-09-05) corrige D9/D10/M10 contra lo que DOJO-11 terminó construyendo — ver 7.9 y 5.3 para el porqué
tags: [dojobase, diseño, ui-ux, design-system, componentes]
---

# DESIGN.md — DojoBase

Ver también: [[Proyectos/DojoBase/README|README]] · [[Proyectos/DojoBase/documentacion-v1|documentacion-v1.md]] · [[Proyectos/DojoBase/historias-usuario|historias-usuario.md]] · [[Proyectos/CoreBase/arquitectura|arquitectura.md]] · [[Proyectos/Tacha/DESIGN|DESIGN.md de Tacha (formato de referencia)]]

**Propósito:** dar el contexto completo — personalidad, tokens, navegación, inventario de pantallas, catálogo de componentes, estados y un prompt por pantalla — para que ni una pantalla se diseñe improvisando. Es el documento que faltaba, y la falta de su equivalente es exactamente cómo GymBase v1 terminó con 618 colores hex sueltos, cinco patrones de formulario y tres implementaciones de modal.

**Regla de oro de este documento:** si una pantalla no está acá, no se construye hasta que se agregue acá. Cambiar este archivo cuesta minutos; descubrir a mitad de la implementación que dos pantallas resuelven lo mismo de forma distinta cuesta días.

---

## 1. Personalidad

DojoBase se ve como un **dojo**, no como un panel de administración ni como un gimnasio de neón.

Tres adjetivos, que son el ancla contra el look genérico "hecho por IA":

- **Disciplinado** — retícula estricta, jerarquía tipográfica fuerte, nada decorativo que no comunique. El orden visual es el mensaje: esta app la usa una escuela donde el orden importa.
- **Preciso** — la información densa (una grilla de calificación, un marcador por rounds, un calendario de la semana) se lee de un vistazo. Sin adorno que compita con el dato.
- **Con peso** — contraste alto, tipografía de títulos condensada y firme, superficies definidas. No pastel, no "friendly startup", no gradiente morado-azul.

Y un momento emocional deliberado y **escaso**: cuando alguien asciende de cinturón o gana un sparring, la app celebra. Es el único lugar donde se permite la tipografía de display grande y una animación de impacto. Máximo 3 o 4 puntos en toda la app — si está en todas partes, no significa nada.

### Lo que NO es

| No | Por qué |
|---|---|
| Dashboard corporativo gris | Es un dojo, no un ERP. El sensei tiene que querer mostrarlo |
| Gimnasio de neón / "fitness bro" | Ese es el lenguaje de GymBase, y es el otro producto |
| Card blanca sobre fondo gris claro, sin identidad | Es el default de todo generador de UI. Se nota |
| Animación protagonista | RNF-07: gama media y conexión inestable. La landing impresiona una vez; la app se usa todos los días |

---

## 2. Design tokens

Dos capas que **nunca se mezclan**: la escala (igual para todos los dojos) y el tema (distinto por dojo).

### 2.1 Escala base — fija, en `@corebase/config`

No depende del tenant. Ningún componente usa un `px` suelto fuera de esta escala.

```ts
export const spacing = {
  '3xs': '2px', '2xs': '4px', xs: '8px', sm: '12px', md: '16px',
  lg: '24px', xl: '32px', '2xl': '48px', '3xl': '64px',
};

export const fontSize = {
  xs: '12px', sm: '14px', base: '16px', lg: '18px',
  xl: '22px', '2xl': '28px', '3xl': '36px', '4xl': '48px',
};

export const fontWeight = { regular: 400, medium: 500, semibold: 600, bold: 700 };
export const lineHeight = { tight: 1.15, snug: 1.3, normal: 1.5, relaxed: 1.7 };

export const radius = { none: '0', sm: '4px', md: '8px', lg: '12px', xl: '20px', full: '9999px' };

export const elevation = {
  none: 'none',
  sm: '0 1px 2px rgb(0 0 0 / 0.08)',
  md: '0 4px 12px rgb(0 0 0 / 0.12)',
  lg: '0 12px 32px rgb(0 0 0 / 0.18)',
};

export const duration = { instant: '80ms', fast: '150ms', normal: '250ms', slow: '400ms' };
// Nada supera 400ms en un flujo de uso diario (RNF-07).

export const breakpoints = { sm: '640px', md: '768px', lg: '1024px', xl: '1280px' };

export const zIndex = { base: 0, sticky: 10, header: 20, overlay: 40, modal: 50, toast: 60 };
```

**Regla de lint (CI):** cualquier valor de `px` fuera de esta escala, y cualquier hex literal, falla el build dentro de `packages/ui/**` y `apps/*/src/**`. Es lo que impide que se repita lo de v1.

### 2.2 Tokens de tema — variables por tenant

Vienen de `tenant_themes` y se inyectan como CSS vars en el `<html>` **antes del primer render** (server component en el layout raíz), para que no haya parpadeo de tema por defecto.

| Token | Uso |
|---|---|
| `--color-bg` | Fondo base de la app |
| `--color-surface` | Cards, paneles, superficies elevadas |
| `--color-surface-alt` | Filas alternas, encabezados de tabla, estados hover |
| `--color-border` | Separadores decorativos. Bajo contraste a proposito |
| `--color-border-strong` | Contorno de un control interactivo (input, boton secundario). Debe alcanzar 3:1 |
| `--color-primary` | Acción principal, estado activo, acento de marca del dojo |
| `--color-on-primary` | **Texto sobre primary — derivado, no configurado** (ver 2.3) |
| `--color-secondary` | Acento secundario |
| `--color-accent` | Destaque puntual (badges de logro, highlights) |
| `--color-text` | Texto principal |
| `--color-text-muted` | Texto secundario, metadatos |
| `--color-success` / `--color-warning` / `--color-danger` | Semánticos — **fijos, no configurables por tenant** |
| `--font-heading` / `--font-body` | Tipografías |
| `--radius-base` | Derivado de `radius: sharp \| soft \| rounded` |

**Los colores semánticos no son configurables.** Un dojo no puede definir que "error" sea verde. Verde es éxito, rojo es peligro, y eso no se negocia por tenant.

### 2.3 El problema real del theming dinámico: contraste

Si el dojo elige un amarillo como `primary`, el texto blanco encima queda ilegible. Si elige un azul oscuro, el texto negro queda ilegible. **No se puede hardcodear el color del texto sobre `primary`.**

Solucion, en `@corebase/core/theming`: el color de texto se **deriva** comparando el contraste real contra los dos neutros del sistema, y se devuelve el que gana:

```ts
// packages/core/theming/contrast.ts
export function onColor(background: string): string {
  return contrastRatio(background, neutral.ink) >= contrastRatio(background, neutral.paper)
    ? neutral.ink
    : neutral.paper;
}
```

**Por que no un umbral fijo de luminancia.** Es la solucion obvia (`luminancia > 0.45 ? oscuro : claro`) y esta mal: los colores de luminancia media caen del lado equivocado, y son justo donde un dojo elige su color de marca. Verificado contra la implementacion real:

| Color | Umbral fijo | Contraste real |
|---|---|---|
| Ambar `#E8A33D` | texto claro → ratio **2.00** (ilegible) | texto oscuro → ratio **8.80** |
| Verde oliva `#6B8E23` | texto claro → ratio **3.52** (no llega a AA) | texto oscuro → ratio **4.99** |

Con el umbral, la mitad de las paletas calidas del catalogo quedan ilegibles. Con el contraste real, los ocho colores de prueba — incluidos cinturon blanco y cinturon negro — pasan AA.

Y al guardar el tema, el editor **valida el contraste y avisa** si una combinación no alcanza AA (4.5:1 para texto normal, 3:1 para texto grande y elementos de UI), proponiendo el ajuste más cercano que sí cumple. El dojo puede elegir el color que quiera; lo que no puede es dejar la app ilegible sin enterarse.

**Por que hay dos tokens de borde.** Al correr esa validacion contra los tres presets, los tres fallaban en `border sobre surface` — y estaban bien. WCAG exige 3:1 para elementos de UI que delimitan un control, no para separadores decorativos: un divisor que alcanza 3:1 se ve como una linea gruesa y arruina el diseno. De ahi salio la separacion en `--color-border` (decorativo, no se valida) y `--color-border-strong` (contorno de input o boton secundario, si se valida). Es un hueco del sistema que aparecio por probarlo, no por disenarlo.

Esto es un requisito de accesibilidad **y** de venta: una app que se ve rota con los colores del cliente no se vende.

### 2.4 Tipografía

| Uso | Fuente | Dónde |
|---|---|---|
| Display / impacto | **Anton** | Solo en los 3-4 momentos de celebración. Nunca en formularios, tablas ni cuerpo |
| Títulos | **Barlow Condensed** (semibold/bold) | Encabezados de pantalla y de sección. Condensada = disciplinada y compacta, aguanta títulos largos en mobile |
| Cuerpo e interfaz | **Space Grotesk** | Todo lo demás. Geométrica, legible en densidad alta, con números tabulares para marcadores y montos |

Números siempre con `font-variant-numeric: tabular-nums` en marcadores, puntajes, montos y contadores — sin eso una columna de números "baila" al actualizarse.

Un dojo puede sobrescribir `--font-heading` y `--font-body` desde su tema; el display es de la marca DojoBase y no se toca.

### 2.5 Preset por defecto — "DojoBase"

El tema que ve un dojo recién creado, antes de personalizar. Toma prestado el lenguaje de la marca (spec 08b) pero **como una fila de `tenant_themes`, no como hardcoding**.

| Token | Valor |
|---|---|
| `--color-bg` | `#0B0B0D` |
| `--color-surface` | `#141417` |
| `--color-surface-alt` | `#1C1C21` |
| `--color-border` | `#2A2A31` |
| `--color-border-strong` | `#666670` |
| `--color-primary` | `#D91C2B` (carmesí) |
| `--color-secondary` | `#E8A33D` (ámbar) |
| `--color-accent` | `#E8A33D` |
| `--color-text` | `#F2F0EB` (papel) |
| `--color-text-muted` | `#8A8A94` |
| `--radius-base` | `soft` (8px) |

Presets adicionales que se ofrecen al configurar (HU-21 CA-04): **Papel** (claro, alto contraste, para dojos tradicionales), **Tatami** (verde/beige, cálido), **Combate** (el default oscuro). Dojo Shoto tendrá el suyo propio en blanco/rojo/azul — que es una fila, no un deploy.

Los tres presets estan implementados en `packages/core/src/theming/presets.ts` y **verificados**: los 30 pares de contraste de los tres pasan AA, y el texto derivado sobre cada color de acento tambien. El carmesi paso de `#C1121F` a `#D91C2B` y el gris del preset claro de `#6B7280` a `#5F6672` porque los originales quedaban apenas por debajo del minimo.

### 2.6 Modo claro y oscuro

El tema del tenant define su propia paleta y **ya trae su modo**: un dojo con paleta oscura se ve oscuro. No hay un toggle claro/oscuro por usuario en el MVP — sería un segundo eje de configuración multiplicado por cada tenant, y duplica el trabajo de contraste. Los presets cubren ambos gustos.

---

## 3. Navegación

### 3.1 Principio

**La navegación cambia por rol, no por permiso escondido.** Un miembro no ve items deshabilitados de admin: no los ve. Un admin que también entrena ve las dos cosas, separadas por una división visual clara, no mezcladas.

### 3.2 Desktop — sidebar fija

**Miembro** (5 items)

```
[logo del dojo]
● Inicio            → dashboard: próxima clase, retos pendientes, próximas peleas
● Clases            → calendario semanal + inscripción
● Sparring          → mis retos, rivalidades
● Mi progreso       → rangos, promociones, mis peleas
● Contenido         → biblioteca del dojo
─────────────
[avatar con anillo de rango] → perfil, membresía, notificaciones, salir
```

**Admin** (agrega un bloque, no reemplaza el anterior)

```
GESTIÓN
● Panel             → KPIs operativos
● Miembros
● Calendario        → vista mensual, crear clases, pasar lista
● Promociones
● Peleas
● Contenido
● Retos
● Pagos             → bandeja de comprobantes (con badge de pendientes)
```

**Owner** (agrega)

```
NEGOCIO
● Finanzas
● Configuración     → tema, datos del dojo, planes, pagos, grupos familiares
```

### 3.3 Mobile — tabs inferiores, máximo 5

**Miembro:** Inicio · Clases · Sparring · Progreso · Más
**Admin:** Panel · Miembros · Calendario · Pagos · Más

"Más" abre una hoja de navegación con el resto. Los cuatro fijos son los de uso diario, en la zona del pulgar. **Pagos ocupa un lugar fijo en admin porque es la tarea que se hace todos los días** y que si se atrasa, molesta al alumno.

### 3.5 Las tres vistas: owner, admin y alumno

**No son tres audiencias distintas: son hasta tres sombreros sobre la misma persona.**

Es el hallazgo que más cambia el diseño, y viene del propio GymBase v1: Dojo Shoto corre con `admins_pay: true` y `staff_as_members`, o sea que **el sensei entrena, tiene su cinturón y paga su mensualidad como cualquier alumno**. No es un administrador que mira un sistema desde afuera; es un practicante que además administra.

| Rol | Sombreros |
|---|---|
| Alumno | El suyo |
| Instructor (admin) | El suyo **+** la operación del dojo |
| Dueño (owner) | El suyo **+** la operación **+** el negocio |

Cada rol **suma** al anterior, no lo reemplaza.

#### Qué se decide con eso

**Una sola app, no tres.** GymBase v1 separaba `/portal`, `/admin` y `/owner` como si fueran productos distintos, y el sensei tenía que saltar entre ellos para ver si alguien pagó y después volver a ver su propia clase. Acá la navegación **acumula secciones**: primero lo personal, después *Gestión*, después *Negocio*. Un alumno ve un solo bloque; el dueño ve tres.

**Nada se muestra deshabilitado.** Un alumno no ve los items de gestión en gris: no los ve. Un control que no se puede usar hace que la app se sienta más grande y más confusa de lo que es, sin darle nada a nadie.

**Un solo inicio, con dos zonas.** El dueño no entra a un tablero de KPIs: entra a *su* inicio — su próxima clase, sus retos — y debajo, si es staff, un bloque de **El dojo hoy**: cuántos comprobantes esperan, cuántas clases hay, qué ascenso viene. Los números de negocio (ingresos, morosidad) **no** van ahí: viven en Finanzas, que es del owner.

Que el sensei vea primero su propia clase no es un detalle de acomodo. Es lo que hace que la app se sienta suya y no del sistema que le vendieron.

**"Ver como alumno".** El staff puede mirar la app exactamente como la ve un alumno. v1 lo tenía y es de las funciones más útiles para dar soporte: cuando alguien dice "no me aparece la clase", la respuesta es mirar lo mismo que él, no adivinar. Es solo de lectura y no cambia permisos — solo esconde las secciones de gestión.

#### Lo que esto NO cambia

La autorización no tiene nada que ver con la navegación. Que una sección esté oculta no protege nada: **cada pantalla verifica el rol en el servidor y cada consulta pasa por RLS**. "Ver como alumno" es una preferencia de interfaz; si el staff pide un dato de gestión estando en ese modo, lo obtiene igual, porque su rol real no cambió. Ocultar un botón nunca fue un control de acceso.

### 3.4 Reglas transversales

- **Todo se navega también en mobile.** No hay pantalla "solo desktop": el sensei va a usar el celular en el tatami. La grilla de calificación de promociones es la más difícil y tiene su solución específica (ver 5.3).
- **Header de pantalla consistente:** título, subtítulo opcional, y a la derecha la acción principal (una sola). Acciones secundarias en un menú de tres puntos.
- **Sin breadcrumbs.** La jerarquía es de dos niveles como máximo; si hace falta un breadcrumb, la navegación está mal.

---

## 4. Inventario de pantallas

48 pantallas. Cada una mapeada a las HU que resuelve. Las `K` son kioscos (pantalla completa, sin navegación) y las `P` son públicas (sin sesión).

### Acceso (5)

| # | Pantalla | HU | Notas |
|---|---|---|---|
| A1 | Login | HU-25 | Email + contraseña. Sin registro público (RF-19) |
| A2 | Aceptar invitación | HU-24 | Muestra a qué dojo te invitan y con qué rol antes de pedir datos |
| A3 | Recuperar contraseña | — | Flujo estándar en dos pasos |
| A4 | Sin organización | HU-25 CA-04 | Pantalla explicativa, no un error ni un blanco |
| A5 | Selector de organización | HU-25 | Solo si pertenecés a más de una |

### Miembro (17)

| # | Pantalla | HU | Notas |
|---|---|---|---|
| M1 | Inicio | HU-11, HU-40 | Próxima clase, retos pendientes, feed de próximas peleas, aviso de membresía. Para el staff, debajo aparece **El dojo hoy** (D1) |
| M2 | Clases — semana | HU-01 | Vista semanal, inscripción en un toque |
| M3 | Detalle de clase | HU-02, HU-03 | Inscribirse/cancelar + lista de asistentes con su rango |
| M4 | Sparring — mis retos | HU-05, HU-06, HU-09b | Tres secciones: por responder, activos, historial |
| M5 | Nuevo reto | HU-05 | `FormModal`: rival, disciplina, fecha opcional |
| M6 | Detalle de reto | HU-06, HU-07, HU-07b | Cambia según rol y estado: responder / cargar rounds / confirmar |
| M7 | Cargar resultado | HU-07 | Marcador por rounds, pensado para usarse al lado del tatami |
| M8 | Rivalidades | HU-08 | Head-to-head por rival y disciplina |
| M9 | Mi progreso | HU-14 | **Pantalla estrella.** Rango por disciplina, camino al siguiente, historial de promociones |
| M10 | Detalle de evaluación | HU-14 | *(2026-09-05: construida como acordeón inline dentro de M9, no como ruta aparte — mismo dato, sin navegación extra; ver 7.7)* Desglose por criterio con puntaje y máximo |
| M11 | Mis peleas | HU-10, HU-11b | Historial + toggle de publicación por pelea |
| M12 | Contenido | HU-15 | Explorador de carpetas |
| M13 | Detalle de contenido | HU-15, HU-15b | Lectura + favorito |
| M14 | Retos | HU-16 | Challenges activos con progreso |
| M15 | Mi membresía | HU-16c, HU-17b | Plan, vencimiento, historial de pagos |
| M16 | Subir comprobante | HU-17 | Datos SINPE del dojo + adjuntar imagen |
| M17 | Notificaciones | HU-09, HU-20 | Centro de notificaciones |
| M18 | Ficha del alumno | HU-32, 32b, 32c | Datos personales, emergencia, competencia y récord en una pantalla, con generación de la ficha para torneo y aviso de campos faltantes |
| M19 | Mis mediciones | HU-33 | **Módulo opcional.** Si el dojo no lo activó, la pantalla no existe ni aparece en la navegación |
| M20 | Sesión de sparring | HU-07c | **A pantalla completa.** Cronómetro grande, teclado de puntos y fase de descanso. La única pantalla del producto que rompe el marco de navegación |
| M21 | Anuncios del dojo | HU-35b | Feed de anuncios con portada, fijados arriba, comentarios y reacciones |
| M22 | Mis avisos | HU-36b | Canales por tipo de evento y activación de push por dispositivo |
| M23 | Editar perfil | HU-37 | Datos básicos y foto |
| M24 | Ver como alumno | HU-41 | No es una pantalla: es un modo. El staff mira la app tal como la ve un alumno, para dar soporte sin adivinar |

### Admin (13)

| # | Pantalla | HU | Notas |
|---|---|---|---|
| D1 | El dojo hoy | HU-40 | **No es una pantalla aparte**: es el bloque de gestión que aparece bajo el inicio personal del staff. Comprobantes esperando, clases de hoy, ascensos próximos. Sin números de negocio — esos son de Finanzas |
| D2 | Miembros | HU-28 | Lista con rango por disciplina y estado de membresía |
| D3 | Ficha de miembro | HU-27, HU-28 | Tabs: general, rangos, clases, promociones, peleas, pagos |
| D4 | Calendario — mes | HU-04 | Vista mensual con ocupación |
| D5 | Crear / editar clase | HU-04 | `FormPage` (tiene recurrencia y privacidad: es multi-paso) |
| D6 | Pasar lista | HU-04b | Lista de inscritos con tres estados. **Diseñada para el celular** |
| D7 | Disciplinas y rangos | HU-00 | Editor de la escala de cinturones, con vista previa |
| D8 | Promociones | HU-12 | Lista de eventos por estado |
| D9 | Evento — candidatos | HU-12b | *(2026-09-05: construida junto con D10 en una sola ruta — el detalle del evento, con secciones de criterios/candidatos/calificación; ver 7.9)* Postular. **Sin la asistencia en la ventana todavía** — pendiente, ver historias-usuario.md |
| D10 | Evento — calificación | HU-13 | La grilla, simplificada a un panel por candidato — ver 5.3 |
| D11 | Peleas | HU-10 | Registro y edición del historial oficial |
| D12 | Contenido — gestión | HU-15 | Carpetas y publicación |
| D13 | Pagos | HU-18 | Bandeja de comprobantes con la imagen al lado de la decisión |

### Owner (5)

| # | Pantalla | HU | Notas |
|---|---|---|---|
| O1 | Finanzas | HU-19 | Ingresos por período, suscripciones activas, distribución por plan |
| O2 | Planes | HU-16b | CRUD de planes, marcar recomendado |
| O3 | Tema del dojo | HU-21 | Editor con vista previa en vivo y **validación de contraste** |
| O4 | Configuración del dojo | HU-29, HU-30 | SINPE, plazos, modo de cobro, conexión de pagos |
| O5 | Grupos familiares | HU-23 | Crear grupos y asignar integrantes |
| O6 | Módulos del dojo | HU-34 | Activar o desactivar módulos opcionales. Desactivar oculta, no borra |
| O7 | Página pública del dojo | HU-39 | Editor de historia, instructores, programas, logros y ubicación |
| D14 | Publicar anuncio | HU-35 | `FormPage`: tiene portada y gating por plan |
| D15 | Serie de clases | HU-02d | Programar recurrencia y resolver serie contra ocurrencia |
| K1 | Proyección de torneo | HU-38 | **Kiosco.** Pantalla completa, sin navegación, sin sesión, en tiempo real. Se ve desde el otro lado del gimnasio |
| P1 | Página pública del dojo | HU-39 | Vista pública, con el tema del dojo |

---

## 5. Catálogo de componentes

**Un solo patrón por tipo de interacción.** Si algo se puede resolver con un componente existente, se resuelve con él — no se crea uno nuevo "porque este caso es un poco distinto".

### 5.1 Primitivas — `@corebase/ui`

Cero conocimiento de negocio. No pueden nombrar `dojo`, `rank`, `belt`, `sparring` ni `martial` (regla de CI).

| Componente | Variantes | Reemplaza de v1 |
|---|---|---|
| `Button` | primary, secondary, ghost, danger · sm, md, lg · loading, disabled, iconOnly | Botones sueltos con clases ad-hoc |
| `FormField` | text, number, date, time, select, textarea, checkbox, switch, file | Inputs sin wrapper consistente |
| `FormModal` | sm, md, lg | **El patrón único** para crear/editar un registro simple |
| `FormPage` | — | **El patrón único** para flujos multi-paso o con mucho contenido |
| `ConfirmDialog` | neutral, destructive | Confirmaciones que a veces eran `alert()` |
| `Card` | flat, raised, interactive | Contenedor base de todo |
| `Badge` | neutral, success, warning, danger, info · sm, md | Estados sueltos con colores inline |
| `Avatar` | xs–xl · con anillo opcional, fallback de iniciales | |
| `AvatarGroup` | apilado con contador de excedente | |
| `EmptyState` | con ícono, título, descripción y acción opcional | Pantallas en blanco sin feedback |
| `Tabs` | line, pill | |
| `DataList` | **tabla en desktop, cards en mobile, misma API** | Tablas que no funcionaban en celular |
| `PageHeader` | título, subtítulo, acción principal, menú secundario | Encabezados distintos en cada pantalla |
| `FilterBar` | búsqueda + filtros + orden | Filtros ad-hoc por pantalla |
| `Stat` | valor, etiqueta, delta opcional | KPIs con estilos distintos por pantalla |
| `Progress` | barra y anillo | |
| `Skeleton` | text, block, circle | Spinners genéricos |
| `Toast` | success, error, info | |
| `Menu` | dropdown de acciones | |
| `Tooltip` | | |
| `SegmentedControl` | 2-4 opciones | Toggles improvisados |
| `Stepper` | numérico con +/− y `tabular-nums` | Inputs de puntaje sueltos |

**Eliminado como categoría: Sheet / Drawer.** Todo lo que en v1 usaba ese patrón cae en `FormModal` o `FormPage`. En mobile, `FormModal` se presenta como hoja desde abajo — pero es el **mismo componente**, no otro.

### 5.2 Componentes de dominio — `apps/dojobase`

Se construyen **componiendo primitivas**, nunca con HTML y clases sueltas. `SparringChallengeCard` es un `Card` + dos `Badge` + `Avatar`, no un `<div>` nuevo.

| Componente | Qué resuelve | HU |
|---|---|---|
| `RankBadge` | Insignia de grado, en tres formas según la disciplina — ver 5.4. **El componente con más peso visual del producto** | HU-00, HU-00b, HU-03, HU-14 |
| `DisciplinePill` | Etiqueta de disciplina con su color | transversal |
| `MemberIdentity` | Avatar con anillo de rango + nombre + rango en la disciplina del contexto | HU-03, HU-28 |
| `ClassCard` | Clase con disciplina, hora, instructor, ocupación y estado | HU-01 |
| `ClassCalendarWeek` | Vista semanal del miembro | HU-01 |
| `ClassCalendarMonth` | Vista mensual del admin, con ocupación | HU-04 |
| `AttendanceRoster` | Pasar lista con tres estados por alumno | HU-04b |
| `SparringChallengeCard` | Reto con estado y la acción disponible **según quién mira** | HU-05 a HU-09 |
| `ScorePad` | Marcador por round: botones de valor directo (+1 a +4) por peleador y un deshacer global — ver 5.5 | HU-07 |
| `HeadToHeadCard` | Marcador acumulado contra un rival | HU-08 |
| `RankProgressCard` | Rango actual y camino al siguiente, en las tres formas de progresión | HU-14, HU-00b |
| `MemberFileSheet` | Ficha del alumno con campos faltantes señalados y generación para torneo | HU-32 a HU-32c |
| `MeasurementStrip` | Última medición con su variación | HU-33 |
| `CandidatoCalificacion` | Panel de calificación de un candidato: un `Stepper` por criterio, puntaje final en vivo, promover/no promover — ver 5.3 (reemplaza a `PromotionScoreGrid` de v1.3, que era una grilla con dos presentaciones) | HU-13 |
| `PantallaMiProgreso` (desglose inline) | Reemplaza a `CriteriaBreakdown` como pantalla aparte: acordeón dentro de M9, mismo dato | HU-14 |
| `FightCard` | Pelea oficial con resultado y método | HU-10 |
| `UpcomingFightsFeed` | Feed de próximas peleas del dojo | HU-11 |
| `PaymentProofUploader` | Datos SINPE + adjuntar comprobante | HU-17 |
| `PaymentProofReview` | Imagen al lado de aprobar/rechazar con motivo | HU-18 |
| `ContentFolderTree` | Navegación por carpetas anidadas | HU-15 |
| `ChallengeCard` | Reto con progreso | HU-16 |
| `ThemeEditor` | Editor de tema con vista previa y contraste | HU-21 |
| `CelebrationOverlay` | El momento de impacto: ascenso, sparring ganado | HU-13, HU-07 |

### 5.3 Las pantallas difíciles

**`PromotionScoreGrid` en mobile (D10) — corregido 2026-09-05.** El plan original era una matriz de candidatos × criterios en desktop y un flujo de a un candidato por vez en mobile, dos presentaciones sobre la misma data. DOJO-11 lo construyó como **una sola presentación para las dos superficies**: `CandidatoCalificacion`, un panel por candidato con un `Stepper` por criterio, dentro de la lista de candidatos de D9/D10 (que además se unificaron en una sola ruta). Con 1-2 candidatos por evento — lo normal en un dojo chico — la tabla completa no aporta nada sobre el panel, y evita mantener dos layouts para el mismo dato. La versión con las dos presentaciones queda documentada acá como la solución de fondo si algún dojo real llega a calificar muchos candidatos a la vez (del orden de 8-10 en pantalla) y el acordeón se vuelve incómodo de recorrer — no se descartó por error, se descartó por costo sin beneficio actual.

**`SparringSession` (M20).** Es la única pantalla que se usa **durante** una actividad física, no después. Rompe el marco de navegación a propósito: pantalla completa, sin barra, cronómetro en tamaño de display legible a un metro, y el teclado de puntos abajo, en la zona del pulgar. El descanso usa el mismo lienzo con la cuenta regresiva y el resumen del round anterior. Aviso sonoro y vibración — nadie mira la pantalla mientras pelea.

**`TournamentProjection` (K1).** Se ve desde el otro lado del gimnasio, en un televisor, por gente parada. Nada de tipografía de interfaz: tamaños de display, contraste máximo, cero elementos de navegación. Se actualiza en tiempo real — un marcador proyectado con 15 segundos de retraso se nota y desprestigia el torneo.

**`AttendanceRoster` (D6).** Se usa de pie, en el tatami, con una mano. Filas altas, área de toque grande, los tres estados como `SegmentedControl` compacto por fila. Sin scroll horizontal, sin menús anidados.

### 5.5 `ScorePad` — anotar como se anota de verdad

Los puntos de un sparring no llegan de a uno: en BJJ una barrida son 2, un pase de guardia 3, una montada 4; en karate un yuko 1, un waza-ari 2, un ippon 3. Un stepper de `+`/`−` obliga a tocar cuatro veces lo que es una sola acción, y con el celular en una mano al lado del tatami eso es lento y se presta a error.

- **Cuatro botones de valor directo por peleador** (+1, +2, +3, +4), en cuadrícula de 2×2 en móvil y en fila de 4 en pantalla ancha. Área de toque de 46 px de alto: se usa de pie.
- **Un solo deshacer, global**, que revierte la última anotación de cualquiera de los dos — que es como se equivoca alguien anotando en vivo, no "quiero bajarle un punto a este".
- **El deshacer dice qué va a revertir** antes de tocarlo ("Deshacer +3 de Kevin"). Sin eso, corregir a ciegas genera un segundo error.
- El puntaje **rebota al sumarse**: confirmación inmediata sin abrir un diálogo. Menos de 200 ms.
- El historial es del round en curso y vive en el cliente: es una ayuda para anotar, no una bitácora. Lo que se guarda sigue siendo el puntaje final de cada round.

**Los incrementos son configuración de la disciplina** (`disciplines.score_increments`, por defecto `{1,2,3,4}`), no una constante. Un dojo que solo puntúa 2-3-4 en BJJ los ajusta sin tocar código, y la pantalla sigue siendo la misma.

`Stepper` no desaparece: se sigue usando en la grilla de calificación de ascensos, donde los puntajes son arbitrarios dentro de un máximo y no hay valores típicos.

### 5.4 `RankBadge` — el detalle que define el producto

El cinturón es la identidad visual de un dojo. Este componente tiene que verse bien con **cualquier** color, incluido blanco y negro.

**Tres formas, según el estilo de progresión de la disciplina (HU-00b):**

| Estilo | Qué dibuja |
|---|---|
| `direct` — karate, krav magá | Barra de color **sin punta ni franjas**. El grado se nombra al lado con la etiqueta corta del rango (`3.º kyu`, `1.º dan`) |
| `stripes` — BJJ | Barra de color con punta oscura y las franjas acumuladas dentro de la punta |
| `time_based` — MMA | **No dibuja insignia.** El progreso se muestra como tiempo entrenando, clases y récord |

Esto no es cosmética: dibujarle franjas a un cinturón de karate le inventa a la escuela un sistema de grados que no tiene, y un sensei lo nota en la primera pantalla.

**Reglas de dibujo:**

- Las franjas van **proporcionales al tamaño del badge**, y su color se decide por contraste contra el color del cinturón — oscuras sobre cinturón claro, claras sobre oscuro. Es el mismo cálculo de `onColor` de 2.3.
- Un cinturón blanco necesita borde; uno negro no. Se resuelve con la misma regla de luminancia, no con un caso especial por color.
- El anillo de rango en un avatar usa el color del cinturón, ajustado si no se distingue del fondo — un cinturón negro sobre un tema oscuro desaparece.
- Tamaños: `xs` (fila de lista), `sm` (card), `md` (perfil), `lg` (celebración de ascenso).

---

## 6. Estados obligatorios por pantalla

Ninguna pantalla se da por terminada sin sus cinco estados. En v1 este es el hueco más visible: pantallas en blanco cuando no hay datos.

| Estado | Regla |
|---|---|
| **Carga** | `Skeleton` con la forma del contenido real, nunca un spinner centrado. La pantalla no debe "saltar" al cargar |
| **Vacío** | `EmptyState` con ícono, qué significa que esté vacío, y la acción que lo llena. "No tenés retos pendientes — retá a un compañero" |
| **Error** | Qué pasó y qué hacer, con reintento. Nunca un código de error crudo |
| **Sin permiso** | Explicación de por qué no se ve, no una pantalla en blanco ni un 404 |
| **Éxito** | `Toast` para lo rutinario; `CelebrationOverlay` **solo** para ascenso de rango y sparring ganado |

Además, por pantalla: **densidad mobile verificada**, foco visible en teclado, y contraste AA con al menos dos temas distintos (el preset por defecto y uno claro). El agente de UI entrega toda pantalla verificada con dos temas — es la única forma de comprobar que el theming realmente funciona y no solo con los colores con los que se diseñó.

---

## 7. Prompts por pantalla

Base común, a anteponer a todos:

> App SaaS para academias de artes marciales llamada DojoBase. Personalidad: disciplinada, precisa, con peso — retícula estricta, jerarquía tipográfica fuerte, contraste alto. NO dashboard corporativo gris, NO estética de gimnasio de neón, NO gradiente morado-azul. Tema oscuro: fondo `#0B0B0D`, superficie `#141417`, borde `#2A2A31`, primario carmesí `#C1121F`, acento ámbar `#E8A33D`, texto `#F2F0EB`, texto secundario `#8A8A94`. Títulos en Barlow Condensed semibold, cuerpo en Space Grotesk, números tabulares. Radio de bordes 8px. Espaciado en múltiplos de 4px. Diseñar mobile-first y mostrar también desktop.

### 7.1 M1 — Inicio del miembro
Dashboard de un alumno. Arriba, card de la próxima clase con disciplina, hora, instructor y botón de inscribirse. Debajo, sección "Te retaron" con tarjetas de retos de sparring pendientes de responder (avatar del retador, su cinturón, disciplina, botones aceptar/rechazar). Después, feed horizontal "Próximas peleas" con tarjetas de compañeros que compiten pronto. Si la membresía vence en menos de 7 días, una franja de aviso arriba de todo. Estado vacío por sección, nunca espacio en blanco.

### 7.2 M2 — Calendario semanal
Vista de semana con los 7 días como columnas en desktop y como carrusel de días en mobile. Cada clase es una tarjeta compacta: nombre, disciplina con su color, hora, instructor, y ocupación tipo "8/12". Estado visual distinto para inscrito, con cupo, lleno y cancelada. Navegación de semana anterior/siguiente arriba. Toque en la tarjeta abre el detalle.

### 7.3 M3 — Detalle de clase
Encabezado con nombre, disciplina, fecha, hora e instructor con su cinturón. Botón principal grande de inscribirse o cancelar según el estado. Debajo, lista de asistentes: avatar con anillo del color de su cinturón, nombre y su cinturón **en la disciplina de esta clase**. El instructor aparece primero, marcado. Si no hay inscritos, estado vacío invitando a ser el primero.

### 7.4 M4 — Mis retos de sparring
Tres secciones con encabezado: "Por responder" (con acción destacada), "Activos" y "Historial". Cada tarjeta muestra los dos avatares enfrentados con sus cinturones, la disciplina, el estado como badge y la acción disponible. En historial, el marcador final. Botón flotante de nuevo reto.

### 7.5 M6/M7 — Detalle de reto y marcador por rounds
Encabezado enfrentando a los dos peleadores: avatar grande, nombre y cinturón a cada lado, marcador acumulado grande al centro con números tabulares. Debajo, lista de rounds, cada uno con los dos puntajes. Para agregar un round, dos steppers enfrentados con área de toque grande, pensados para usarse de pie al lado del tatami. Botón de cerrar el reto al final. Si soy el rival y el reto está cerrado sin confirmar, banda superior con "Confirmar resultado" y opción de dejar una nota.

### 7.6 M9 — Mi progreso
Pantalla estrella del miembro. Arriba, una tarjeta por disciplina: nombre de la disciplina, cinturón actual grande con sus franjas, y una barra de progreso al siguiente rango con el texto de qué falta ("2 franjas más" o "12 clases más"). Debajo, línea de tiempo de eventos de promoción en los que participé, cada uno con fecha, nombre del evento, resultado como badge y puntaje final. Tocar uno abre el desglose por criterio.

### 7.7 M10 — Desglose de evaluación
*(2026-09-05: construida como acordeón dentro de la tarjeta del evento en M9, no como pantalla aparte — se toca la tarjeta y se expande ahí mismo, sin navegar.)* Encabezado con el evento, la fecha y el resultado — ya visibles en la tarjeta cerrada. Al expandir: lista de criterios con nombre, puntaje obtenido sobre el máximo y barra de progreso. Al final, la nota mínima del evento si la tenía. Tono informativo, no de reprobación. El peso del criterio (planeado en v1.3) no se muestra — el puntaje ya normalizado es lo que le importa al miembro, no cómo se ponderó.

### 7.8 D6 — Pasar lista
Diseñada para usarse de pie con una mano. Encabezado con la clase, hora y contador "18 de 20 presentes". Filas altas: avatar, nombre, cinturón, y a la derecha un control segmentado compacto de tres opciones — presente, ausente, sin marcar. Sin scroll horizontal. Botón de guardar fijo abajo.

### 7.9 D9/D10 — Detalle del evento: criterios, candidatos y calificación
*(2026-09-05: D9 y D10 se construyeron como una sola pantalla — el detalle del evento — en vez de dos rutas separadas; ver 5.3 para por qué la grilla se simplificó a un panel por candidato.)* Encabezado con el nombre del evento, la disciplina, el estado (borrador/activo/completado) y qué otorga (rango fijo, rango dinámico al siguiente de la escala, o franja), más los botones de la etapa actual (activar, cerrar, reabrir, resolver por nota mínima). Debajo, la lista de criterios (nombre, máximo, peso) con agregar/editar/eliminar — editar y eliminar solo mientras el evento está en borrador. Debajo, la lista de candidatos postulados: nombre, rango con el que se presentó, estado. Cada candidato pendiente expande ahí mismo su panel de calificación — un `Stepper` por criterio con guardado automático, puntaje final recalculado en vivo, aviso de evaluación incompleta, y los botones promover/no promover. Un candidato ya resuelto muestra su puntaje final y el botón de revertir la decisión.

### 7.10 D13 — Revisar comprobantes
Lista de comprobantes pendientes. Al abrir uno: la imagen del comprobante ocupando la mitad de la pantalla (ampliable), y al lado el miembro, el plan, el monto y hasta cuándo se le extiende la membresía si se aprueba. Dos botones claros: aprobar y rechazar. Rechazar abre un campo obligatorio de motivo.

### 7.11 O1 — Finanzas
Fila de KPIs arriba: ingresos del mes, suscripciones activas, pagos pendientes, morosos. Debajo, gráfica de ingresos por mes. Al lado, distribución por plan. Abajo, tabla de últimos pagos. Números tabulares en todo. Sobrio y legible, no un dashboard sobrecargado.

### 7.12 O3 — Tema del dojo
Dos columnas: a la izquierda los controles — selectores de color por token, selector de tipografías, radio de bordes, subida de logo, y una fila de presets. A la derecha, vista previa en vivo de una pantalla real de la app (un calendario con tarjetas de clase). Si una combinación no alcanza el contraste mínimo, aviso inline con el ajuste sugerido. Botón de guardar fijo.

### 7.13 D7 — Disciplinas y rangos
Lista de disciplinas a la izquierda; al elegir una, su escala de rangos a la derecha, ordenada de menor a mayor. Cada rango es una fila con su cinturón dibujado, nombre, nivel, franjas necesarias, y controles de reordenar. Botón de agregar rango. Al crear una disciplina, ofrecer plantillas de escala conocidas (karate, BJJ) como punto de partida editable.

### 7.14 A2 — Aceptar invitación
Pantalla centrada, sobria. Logo del dojo, "Te invitaron a unirte a [Dojo]", el rol con el que entrás, y quién te invitó. Un solo botón principal. Debajo, alternativa de iniciar sesión si ya tenés cuenta. Si la invitación venció, mensaje claro con qué hacer.

### 7.15 CelebrationOverlay
Superposición a pantalla completa, breve. Fondo oscurecido, el cinturón nuevo grande al centro con una animación corta de entrada (menos de 400ms), la palabra "¡PROMOVIDO!" en Anton, y el nombre del rango. Un botón de continuar. Sin confeti genérico ni animación larga: impacto por contraste y tipografía, no por movimiento.

---

## 8. Cómo usar este documento

1. **Antes de diseñar una pantalla**, buscarla en la sección 4. Si no está, agregarla ahí primero con su HU.
2. **Antes de crear un componente**, buscarlo en la sección 5. Si algo parecido existe, se extiende con una variante; no se crea uno nuevo.
3. **Al generar UI con IA**, anteponer el prompt base de la sección 7 y agregar el prompt específico de la pantalla.
4. **Al implementar**, todo color y toda medida sale de los tokens de la sección 2. La regla de CI lo verifica, pero la disciplina es del que escribe.
5. **Antes de dar una pantalla por terminada**, los cinco estados de la sección 6, verificados con dos temas distintos.

## Pendiente

- **Prompts de las pantallas restantes** — están las 15 que definen el lenguaje visual; el resto se derivan de estas y de los componentes ya definidos.
- **Mockup navegable** — un HTML de las 4 o 5 pantallas clave, como el `mockup-web-v2.html` de Tacha, para validar el lenguaje visual antes de escribir componentes.
- **Iconografía** — definir el set (probablemente Lucide) y las reglas de tamaño y grosor.
