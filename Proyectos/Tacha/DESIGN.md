---
proyecto: Tacha
tema: DESIGN.md — guía de diseño para generación de interfaz con Stitch AI
fecha: 2026-08-18
tipo: documentacion
estado: completo para generación en Stitch — cubre navegación (incluido el funnel público), pantallas, componentes y prompts de las 19 pantallas del alcance v1 (incluye grupos de productos, mis productos personalizados y landing/about/auth extendida, 2026-08-18)
tags: [diseño, ui-ux, stitch, tacha]
---

# DESIGN.md — Tacha

Ver también: [[Proyectos/Tacha/README|README]] · [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] (v2.1, secciones 3, 4, 6 y 9) · [[Proyectos/Tacha/historias-usuario|historias-usuario.md]] (v1.0) · [[Proyectos/Tacha/mockups/mockup-web-v2.html|mockups/mockup-web-v2.html]] · `Tacha_documentacion-v2.1.docx` (versión Word)

**Propósito de este documento:** dar a quien genere pantallas en Stitch AI (hoy: principalmente Melany — diseño UI, y Marcos — listas/PWA) el contexto completo — personalidad, tokens, navegación, inventario de pantallas, componentes y un prompt listo por pantalla — para que nada quede a medio definir. Cubre las 19 pantallas del alcance v1 completo de [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] (sección 3), incluidas [[Proyectos/Tacha/documentacion-v1#4.11 Grupos de productos (aceptado 2026-08-18, sujeto a confirmación del equipo)|grupos de productos]], [[Proyectos/Tacha/documentacion-v1#4.5.1 Mis productos personalizados (aceptado 2026-08-18, sujeto a confirmación del equipo)|mis productos personalizados]] y la [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|landing pública y autenticación extendida]] que pidió el profesor, ya todas parte del alcance de trabajo. Es más fácil quitar o ajustar algo de acá después que generarlo desde cero a mitad de la sesión de Stitch.

## 1. Personalidad de marca

**Cálida y hogareña**, evocando apps de cocina/familia — sin caer en lo infantil ni en el look genérico de fintech/SaaS. Ver [[Proyectos/Tacha/documentacion-v1#9. Dirección de diseño (UI/UX)|sección 9 del documento de proyecto]] para el detalle original.

Al prompt-ear en Stitch, incluir siempre estos tres adjetivos como contexto de personalidad — son el ancla que evita el look genérico "hecho por IA" (ver checklist en sección 8):

- **Cálida** — paleta crema/terracota/teal, nunca gradiente morado-azul por defecto.
- **Hogareña** — cercana a apps de cocina/familia, no a un dashboard corporativo.
- **Confiable sin ser fría** — el dashboard financiero y el catálogo deben verse profesionales, pero sin volverse "fintech genérico".

## 2. Design tokens

Tomados directamente de `mockup-web-v2.html` (ya construido) — reusar tal cual, no reinventar en Stitch.

### 2.1 Tipografía

| Uso | Fuente |
|---|---|
| Títulos / display | Fraunces (serif cálida, variable, pesos 500/600/700) |
| Cuerpo de texto | Public Sans (pesos 400/500/600/700) |

### 2.2 Color — modo claro

| Token | Uso | Hex |
|---|---|---|
| `--bg` | Fondo base | `#FBF6EE` |
| `--surface` | Cards/superficies | `#FFFFFF` |
| `--border` | Bordes sutiles | `#E8DFD0` |
| `--teal` | Acento principal (acciones, estados activos) | `#0E7C7B` |
| `--terracotta` | Acento secundario (etiquetas contextuales, montos) | `#D97B4F` |
| `--chipbg` | Fondo de chip/badge | `#FBEADF` |
| `--chipborder` | Borde de chip/badge | `#E9C4A5` |
| `--text` | Texto principal | `#2B2420` |
| `--textsec` | Texto secundario | `#8A7F70` |

### 2.3 Color — modo oscuro

| Token | Uso | Hex |
|---|---|---|
| `--bg` | Fondo base | `#1C1815` |
| `--surface` | Cards/superficies | `#26211C` |
| `--border` | Bordes sutiles | `#332C25` |
| `--teal` | Acento principal | `#3EC6C1` |
| `--terracotta` | Acento secundario | `#E89A6C` |
| `--chipbg` | Fondo de chip/badge | `#3A2A1E` |
| `--chipborder` | Borde de chip/badge | `#4A362A` |
| `--text` | Texto principal | `#F5EFE6` |
| `--textsec` | Texto secundario | `#B5A997` |

### 2.4 Forma, espaciado, iconos

- Checkboxes cuadrados redondeados (~7px de radio), nunca circulares.
- Cards con radio ~14px, chips/badges con radio ~8-20px (pill para chips de estado, más cerrado para badges inline).
- Un solo color de acento saturado (teal) para acciones/estados activos; terracota reservado para etiquetas contextuales y montos — nunca compiten entre sí en la misma pantalla.
- Iconografía outline consistente, un solo grosor de trazo — **sin emojis** en ninguna pantalla de producto.
- Espaciado generoso, agrupación por categoría con separación real (no solo un borde).
- Ambos modos (claro/oscuro) con el mismo nivel de cuidado — pedirle a Stitch ambas variantes, no solo claro con oscuro "invertido".

## 3. Estructura de navegación

### 3.0 Funnel público (antes de loguearse)

Agregado 2026-08-18 — requerimiento del profesor + [[Proyectos/Tacha/historias-usuario|historias-usuario.md]], ver [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|documentacion-v1.md sección 4.12]]. La app ya no manda directo al login: hay un shell público separado del shell autenticado de las secciones 3.1/3.2.

`Landing (Mirones) → About (opcional) → Registro/Login → Verificación de correo (si es registro manual) → Onboarding con/sin household (7.7) → shell autenticado`

Landing y About comparten navbar y footer públicos (no el sidebar/tabs de las secciones 3.1/3.2) — son las únicas pantallas de la app pensadas para verse sin ninguna sesión activa.

Decisión de navegación (para que Stitch genere pantallas dentro de un mismo shell, no sueltas). El mockup original ya proponía 6 ítems de sidebar sin ubicar todavía [[Proyectos/Tacha/documentacion-v1#4.11 Grupos de productos (aceptado 2026-08-18, sujeto a confirmación del equipo)|grupos]], [[Proyectos/Tacha/documentacion-v1#4.5.1 Mis productos personalizados (aceptado 2026-08-18, sujeto a confirmación del equipo)|mis productos]] ni el [[Proyectos/Tacha/documentacion-v1#4.10 Inventario doméstico|inventario]] — se resuelve así, agrupando por lo que el usuario va a *hacer* en cada sección en vez de sumar un ítem de sidebar por feature:

### 3.1 Desktop — sidebar fijo (6 ítems)

| Ítem de sidebar | Contiene |
|---|---|
| **General** | Lista general + resumen rápido de gasto + acceso directo "Agregar desde grupo" + widget opcional y descartable de Inventario (sugerencias de un toque) |
| **Fechas** | Sublistas por fecha + vista de calendario |
| **Listas privadas** | Calendario propio "Mis listas privadas" |
| **Catálogo** | Dos sub-tabs internos: **Buscar** (catálogo global estilo Uber Eats) y **Mis productos** (personalizados) |
| **Recetas** | Dos sub-tabs internos: **Recetas** y **Planificador semanal** |
| **Finanzas** | Dos sub-tabs internos: **Dashboard** y **Historial** |

"Mis grupos" (crear/editar/listar grupos de productos) no es un ítem de sidebar propio — se abre como pantalla secundaria desde el botón "Gestionar mis grupos" dentro de **General**, porque su rol es acelerar la lista, no ser un destino de navegación primario.

### 3.2 Mobile web — tabs inferiores (5 íconos, thumb-friendly)

`General · Fechas · Catálogo · Finanzas · Más`

**Más** despliega: Listas privadas, Recetas/Planificador, Mis grupos, Mis productos, Perfil/Household. Mismo criterio que ya usaba el mockup para mobile (tabs inferiores en vez de sidebar) — no meter más de 5 íconos directos, el resto vive en "Más".

## 4. Inventario de pantallas (alcance v1 completo)

Las 19 pantallas del alcance de [[Proyectos/Tacha/documentacion-v1#3. Alcance del proyecto (v1)|documentacion-v1.md sección 3]] — todas con prompt listo en la sección 7, ninguna queda para definir "después".

| # | Pantalla | Origen | Prioridad hoy | Referencia funcional |
|---|---|---|---|---|
| 1 | Onboarding — con/sin household | Nueva | Alta | [[Proyectos/Tacha/documentacion-v1#4.1 Gestión de usuarios, familias y perfiles|4.1]] |
| 2 | Catálogo — producto madre estilo Uber Eats | Nueva | Alta | [[Proyectos/Tacha/documentacion-v1#4.5 Catálogo de productos y categorías|4.5]] |
| 3 | Mis productos personalizados | Nueva | Alta | [[Proyectos/Tacha/documentacion-v1#4.5.1 Mis productos personalizados (aceptado 2026-08-18, sujeto a confirmación del equipo)|4.5.1]] |
| 4 | "¿Qué hiciste?" — resolución de faltante de receta al tachar | Nueva | Alta | [[Proyectos/Tacha/documentacion-v1#4.9.1 Reconciliación de cantidades al combinar listas (decisión 2026-08-16, alcance corregido 2026-08-18)|4.9.1]] |
| 5 | Edición rápida de item (pre-compra) | Nueva | Alta | [[Proyectos/Tacha/documentacion-v1#4.2 Lista general y dashboard financiero|4.2]] |
| 6 | Edición rápida de item comprado (tachado) | Nueva | Alta | [[Proyectos/Tacha/documentacion-v1#4.6 Historial de compras|4.6]] |
| 7 | Mis grupos — listar/crear/editar | Nueva | Alta | [[Proyectos/Tacha/documentacion-v1#4.11 Grupos de productos (aceptado 2026-08-18, sujeto a confirmación del equipo)|4.11]] |
| 8 | Lista general + resumen financiero + presupuesto estimado | Existe (mockup v2), ajustar | Alta | [[Proyectos/Tacha/documentacion-v1#4.2.1 Interacciones concretas de la fila de producto (detallado 2026-08-18, desde el desglose de historias de usuario)|4.2.1]] |
| 9 | Landing pública (Mirones) | Nueva | Alta | [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|4.12]] |
| 10 | Historial por día/semana/mes, total editable, filtros | Nueva | Media | [[Proyectos/Tacha/documentacion-v1#4.6 Historial de compras|4.6]] |
| 11 | Inventario doméstico — sugerencias ligeras | Nueva | Media | [[Proyectos/Tacha/documentacion-v1#4.10 Inventario doméstico|4.10]] |
| 12 | Finanzas — dashboard detallado | Existe (mockup v2), ajustar | Media | [[Proyectos/Tacha/documentacion-v1#4.2 Lista general y dashboard financiero|4.2]] |
| 13 | Listas privadas + calendario | Existe (mockup v2) | Baja | [[Proyectos/Tacha/documentacion-v1#4.4 Listas privadas (independientes del household)|4.4]] |
| 14 | Recetas + planificador semanal | Existe (mockup v2) | Baja | [[Proyectos/Tacha/documentacion-v1#4.9 Recetas y planificador semanal de comidas|4.9]] |
| 15 | Auth — login/signup (reCAPTCHA, OAuth, mostrar/ocultar contraseña) | Nueva | Baja | [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|4.12]] |
| 16 | Crear/unirse a household (por link) | Nueva | Baja | [[Proyectos/Tacha/documentacion-v1#4.1 Gestión de usuarios, familias y perfiles|4.1]] |
| 17 | About (misión/visión, contacto) | Nueva | Baja | [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|4.12]] |
| 18 | Verificación de correo | Nueva | Baja | [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|4.12]] |
| 19 | Recuperación de contraseña | Nueva | Baja | [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|4.12]] |

Orden recomendado para generar hoy en Stitch: primero las 9 de prioridad Alta (incluye ahora la landing, porque es lo que ve todo visitante antes que cualquier otra cosa), luego ajustar las 3 "Existe (mockup v2)" contra los tokens/patrones nuevos de catálogo y categoría, y dejar Auth/household/About/verificación/recuperación para el final — son las más genéricas y las que menos definen la identidad del producto.

## 5. Componentes base a mantener consistentes

Ya identificados como pendientes de extraer en [[Proyectos/Tacha/flujo-git-tablero#6. Pendiente|flujo-git-tablero.md, sección 6]] — lo que salga de Stitch debe poder mapear a estos primitivos, no inventar variantes nuevas por pantalla:

- **Button** (primario teal, secundario outline, destructivo)
- **Input / FormField** (con label, helper text, estado de error)
- **Modal**
- **Spinner**
- **Checkbox** (cuadrado redondeado — ver sección 2.4)
- **item-row** (fila de producto en lista: checkbox + nombre + meta + badge)
- **category-label** (encabezado de sección/categoría, uppercase, tracking amplio)
- **stat-card** (dashboard financiero)
- **chip / badge** (estado, tamaño, categoría)
- **calendar-cell** (sublistas por fecha, planificador semanal)

Componentes nuevos que salen de las decisiones del 2026-08-16 y del 2026-08-18 (no existían antes, definir su primer diseño en esta ronda de Stitch):

- **catalog-card** — tarjeta de resultado de búsqueda: imagen del **producto madre + tamaño** (ej. "Leche — 1L"), sin marca en la tarjeta misma — la marca ya no es parte de la identidad de la variante ([[Proyectos/Tacha/documentacion-v1#4.5 Catálogo de productos y categorías|4.5]]). Bloque repetible del catálogo estilo Uber Eats y también de **mis productos personalizados** ([[Proyectos/Tacha/documentacion-v1#4.5.1 Mis productos personalizados (aceptado 2026-08-18, sujeto a confirmación del equipo)|4.5.1]]), con una variante que agrega un badge "Agregado por mí".
- **product-detail-view** — al tocar un `catalog-card`, vista de detalle con: listado corto de marcas disponibles (logo + nombre) y, al lado de cada supermercado rastreado, su ícono + precio aproximado (rango, no promedio — ver [[Proyectos/Tacha/documentacion-v1#4.8 Sugerencias de dónde comprar|4.8]]). Es donde vive toda la información de marca que se sacó de la tarjeta.
- **recipe-status-tag** — tag pasivo, no interactivo, bajo un item de la lista cuando una receta o el plan semanal necesitan más cantidad de la que ya está apuntada (ej. "+ 500ml necesarios para Receta X"). No dispara ninguna decisión por sí solo — la decisión ocurre al tachar (ver `list-item-edit-sheet` variante post-compra). Ver [[Proyectos/Tacha/documentacion-v1#4.9.1 Reconciliación de cantidades al combinar listas (decisión 2026-08-16, alcance corregido 2026-08-18)|4.9.1]].
- **list-item-edit-sheet** — panel/hoja de edición rápida sobre un `item-row`, con dos variantes: **pre-compra** (cambiar cantidad, variante/tamaño, o quitar el item) y **post-compra/tachado** (cantidad realmente comprada + dónde + opcionalmente marca comprada, campo siempre opcional). Cuando el item tachado tiene un `recipe-status-tag` pendiente, la variante post-compra agrega el paso "¿Qué hiciste?" con acciones rápidas: "Agregué otra igual" / "Cambié a otra presentación" / "Ya tenía suficiente". Ambas variantes en 1-2 toques, sin salir de la lista.
- **price-disclaimer-banner** — aviso persistente y no intrusivo de "precios estimados, no garantizados por ningún supermercado" ([[Proyectos/Tacha/documentacion-v1#4.6 Historial de compras|4.6]]) — debe aparecer cerca de cualquier precio sugerido sin volverse ruido visual repetido en cada pantalla.
- **inventory-suggestion-chip** — sugerencia de un toque ("¿Se te acabó la leche?") con confirmar/descartar, nunca un formulario ([[Proyectos/Tacha/documentacion-v1#4.10 Inventario doméstico|4.10]]).
- **group-card** — tarjeta de un grupo de productos guardado (nombre, cantidad de productos, ej. "Mercado quincenal — 8 productos"), con botón directo "Agregar a lista". Bloque repetible de "Mis grupos" ([[Proyectos/Tacha/documentacion-v1#4.11 Grupos de productos (aceptado 2026-08-18, sujeto a confirmación del equipo)|4.11]]).
- **custom-product-badge** — badge pequeño "Agregado por mí" sobre `catalog-card` cuando el producto es personalizado (`source: manual`), para distinguirlo visualmente del catálogo scrapeado.

## 6. Estados a cubrir por pantalla

Por [[Sistema/skills/enterprise-ui-ux-design/SKILL|enterprise-ui-ux-design]]: cada pantalla nueva necesita más que el happy path.

| Pantalla | Estados mínimos a pedirle a Stitch |
|---|---|
| Catálogo | Resultados con imagen, resultado sin imagen disponible (fallback por categoría, no ícono roto), sin resultados de búsqueda, cargando |
| Detalle de producto (marcas + súper) | Con varias marcas/súpers, con una sola marca disponible, sin datos de precio en algún súper |
| Mis productos personalizados | Lista vacía (primera vez, con CTA a crear), lista con productos, formulario de alta abierto |
| "¿Qué hiciste?" (tachado de receta) | Item con `recipe-status-tag` pendiente, acción "agregué otra" confirmada, acción "ya tenía suficiente" (tag se descarta sin agregar nada) |
| Edición rápida (pre-compra) | Hoja cerrada/abierta, cambio de variante confirmado, item eliminado (undo breve) |
| Edición rápida (post-compra/tachado) | Edición inline abierta/cerrada, guardado confirmado (feedback inmediato) |
| Mis grupos | Lista vacía (primera vez, CTA "Crear tu primer grupo"), lista con grupos, edición de grupo abierta |
| Historial con total editable | Total confirmado, total "sin ingresar" (pendiente, con recordatorio visual), edición inline abierta, filtro por súper/categoría activo |
| Inventario doméstico | Chip de sugerencia pendiente, confirmado, descartado |
| Onboarding | Sin household (uso solo), creando household, uniéndose por invitación |
| Landing / About | Carrusel de testimonios en reposo/desplazándose, formulario de contacto válido/error, reCAPTCHA fallido |
| Auth | Formulario válido, error de validación, error de reCAPTCHA, cargando, contraseña oculta/visible |
| Registro | Fortaleza de contraseña débil/media/fuerte, contraseñas no coinciden, correo ya registrado |
| Verificación de correo / recuperación | Código válido, código expirado, mensaje genérico de confirmación |

## 7. Prompts listos para Stitch AI

Cada prompt asume que Stitch ya tiene cargada la personalidad (sección 1), los tokens (sección 2) y la navegación (sección 3) como contexto del proyecto — si Stitch no permite contexto persistente entre generaciones, repetir el bloque de personalidad + tokens al inicio de cada prompt individual.

### 7.1 Catálogo — producto madre, estilo Uber Eats

> Pantalla de catálogo de productos para una app de listas de compras colaborativa, dentro del ítem de sidebar "Catálogo" con sub-tabs "Buscar" / "Mis productos" (esta es la vista "Buscar"). Personalidad cálida y hogareña (crema `#FBF6EE`, teal `#0E7C7B`, terracota `#D97B4F`, tipografía Fraunces para títulos + Public Sans para cuerpo). Barra de búsqueda arriba ("Buscar producto, ej. leche"). Debajo, resultados en grid de tarjetas (`catalog-card`): cada tarjeta representa un producto madre + tamaño (ej. "Leche — 1L"), **sin marca en la tarjeta** — foto genérica del producto en la parte superior, nombre + tamaño, y precio aproximado como rango pequeño en terracota (ej. "₡800–₡1200"). Filtro de categoría como fila de chips horizontal encima del grid (Lácteos, Panadería, Limpieza, etc.), con la categoría activa resaltada en teal. Al tocar una tarjeta se abre el detalle del producto (7.1b) con las marcas disponibles. Diseñar para desktop (grid de 4 columnas) y mobile (grid de 2 columnas). Incluir estado de "sin resultados" con ilustración simple y sugerencia de crear producto nuevo (enlaza a "Mis productos").

### 7.1b Detalle de producto — marcas y precio por supermercado

> Vista de detalle al tocar un `catalog-card` (7.1). Cabecera con foto grande, nombre + tamaño del producto. Debajo, sección "Marcas disponibles": listado horizontal o en grid pequeño de logos de marca (`product-detail-view`) — solo informativo, no afecta qué se agrega a la lista. Debajo, sección "Precio aproximado por supermercado": una fila por supermercado rastreado, con su ícono/logo, y el precio aproximado como rango entre las marcas que tiene ese supermercado (ej. "🏬 Walmart — ₡800–₡1200"), ordenados del más barato al más caro. Botón principal "Agregar a mi lista" abajo, con selector de cantidad. Todo con la calidez de marca (Fraunces en el nombre del producto, fondo crema), nada de tabla plana tipo spreadsheet.

### 7.2 Mis productos personalizados

> Sub-tab "Mis productos" dentro de "Catálogo" (junto a "Buscar", ver 7.1 para el shell compartido). Lista de productos que el usuario agregó él mismo, usando el mismo `catalog-card` del catálogo global pero con un `custom-product-badge` visible ("Agregado por mí") en la esquina. Cada tarjeta puede mostrar opcionalmente el nombre de una tienda específica asociada (ej. "Carnicería Los Ángeles") como texto secundario debajo de la marca. Botón flotante o de cabecera "+ Agregar producto" que abre un formulario corto: nombre, marca, categoría (select), tamaño/presentación, foto opcional, y tienda + precio de referencia opcionales. Estado vacío (primera vez): ilustración simple + texto "Agregá productos que no encontrás en el catálogo" + botón CTA grande. El precio de referencia, si existe, se muestra en terracota con un ícono pequeño de "i" que al tocar explica que es un precio manual, no verificado.

### 7.3 "¿Qué hiciste?" — resolver un faltante de receta al tachar

> Corregido 2026-08-18: esto **ya no es un modal al agregar la receta a la lista** — solo aplica a recetas/plan semanal (nunca a sublistas o grupos, que son suma directa) y ocurre al **tachar** el item, no antes. Paso 1 (pasivo, en la lista): bajo el `item-row` de un producto que ya está en la lista, un `recipe-status-tag` chico en texto secundario: "+ 500ml necesarios para Receta X" — sin botones, solo información. Paso 2 (al tocar el checkbox de tachado de ese item): se abre una hoja corta (`list-item-edit-sheet`, variante post-compra) con el título "¿Qué hiciste?" y tres acciones de un toque, como chips grandes: "Agregué otra igual", "Cambié a otra presentación" (despliega las opciones del catálogo para ese producto, con precio aproximado), "Ya tenía suficiente" (descarta el tag, no agrega nada). Tono ligero y rápido, no como un formulario ni como una advertencia de error — es una decisión de 2 segundos, no una tarea.

### 7.4 Edición rápida de item (antes de comprar)

> Componente de edición inline (`list-item-edit-sheet`, variante pre-compra) sobre una fila de la lista general (`item-row`). La fila del `item-row` sigue una jerarquía visual estricta (definida 2026-08-18): **siempre visible** — nombre + tamaño, cantidad (con controles +/-, "-" nunca baja de 1), precio aproximado; **segunda línea, texto chico y secundario** — tag de origen (general/sublista/receta/grupo, solo si hay mezcla de orígenes en la lista) y "encargado" (solo si esa función está activada en configuración); **a la derecha, solo si hay un filtro de súper activo** — ícono del supermercado. Al tocar la fila (no el checkbox ni los controles de cantidad), se despliega un panel corto sin salir de la lista mostrando: selector de cantidad, chips de variante/tamaño disponibles para cambiar de presentación del mismo producto madre, y un botón de eliminar (ícono de basura, color neutro, no agresivo). Todo en 1-2 toques. Al eliminar, mostrar un toast breve "Producto eliminado" con opción de deshacer.

### 7.5 Edición rápida de item comprado (al tachar)

> Componente de edición inline (`list-item-edit-sheet`, variante post-compra) sobre una fila ya tachada en la lista de compras. Al tocar la fila tachada, se expande sin salir de la lista mostrando: cantidad/presentación realmente comprada (editable, con opciones rápidas tipo chip en vez de solo un input numérico — ej. "1 caja pequeña", "1 galón"), y dónde se compró. Todo debe poder editarse en menos de 2 toques, sin navegar a otra pantalla. Confirmación visual inmediata (check animado o cambio de color sutil) al guardar.

### 7.6 Mis grupos — listar, crear y editar

> Pantalla "Mis grupos", accesible desde un botón "Gestionar mis grupos" en la vista General. Lista de tarjetas (`group-card`), cada una con nombre del grupo (ej. "Mercado quincenal"), cantidad de productos que contiene, y un botón directo "Agregar a lista" que dispara la reconciliación de cantidades (7.3) si corresponde. Botón de cabecera "+ Crear grupo" que abre un flujo corto: nombre del grupo, luego búsqueda de productos (mismo patrón de búsqueda del catálogo, 7.1) para ir agregándolos con su cantidad/variante por defecto — nunca un formulario largo de una sola vez. Cada producto agregado al grupo aparece como una fila compacta con opción de quitar. Estado vacío (primera vez): "Agrupá los productos que siempre comprás juntos" + botón CTA grande.

### 7.7 Onboarding — con o sin household

> Pantalla de bienvenida después del signup, antes de entrar a la app. Personalidad cálida y hogareña, con la tipografía Fraunces en el título principal ("¿Cómo querés empezar?"). Dos opciones igual de válidas visualmente (ninguna se ve como "la opción incompleta"): (1) "Usar Tacha solo/a" — ícono de una sola persona, texto secundario explicando que igual tendrá su lista general, sublistas y listas privadas; (2) "Crear o unirme a un household" — ícono de familia/grupo, texto secundario explicando que permite compartir listas familiares. Ambas como cards grandes tocables, no como radio buttons pequeños. Debe quedar claro que la decisión no es permanente ni bloqueante.

### 7.8 Lista general + resumen financiero

> Ajuste sobre la pantalla ya prototipada en `mockup-web-v2.html` ("Desktop — Lista general + dashboard financiero"). Mantener el shell de sidebar (sección 3.1) y el patrón de `item-row` con checkbox cuadrado redondeado, siguiendo la jerarquía visual de 7.4. Agregar, arriba de la lista de productos: un botón "Agregar desde grupo" (abre 7.6) junto al buscador/agregar producto del catálogo, y — si el usuario tiene sugerencias pendientes de inventario — una fila horizontal descartable de `inventory-suggestion-chip` (ver 7.10) justo debajo del encabezado, antes de la lista de productos por categoría. El resumen de la cabecera muestra el **presupuesto estimado** como número grande editable (Fraunces, ej. "₡50,000 esta semana", con lápiz para editar) junto a 2-3 stat-cards compactos; el detalle completo del dashboard vive en Finanzas (7.11).

### 7.9 Historial de compras con total editable

> Sub-tab "Historial" dentro de "Finanzas" (junto a "Dashboard", ver 7.11 para el shell compartido). Selector de periodo arriba (Día / Semana / Mes, como pills, la seleccionada en teal sólido). Debajo, el total del periodo en tipografía Fraunces grande, con un ícono de lápiz pequeño al lado para editarlo directamente (sin entrar producto por producto). Debajo del total, un `price-disclaimer-banner` discreto tipo "Los precios son estimados, Tacha no está afiliado a ningún supermercado". Debajo, lista de sesiones de compra del periodo (fecha, supermercado, monto), cada una también con su propio total editable inline. Sesiones sin total ingresado deben distinguirse visualmente (ej. badge terracota "Sin total") sin sentirse como un error.

### 7.10 Inventario doméstico (sugerencias ligeras)

> Sección opcional dentro de la vista General (ver 7.8), nunca una pantalla obligatoria de por sí. Título discreto: "¿Se te está acabando algo?". Debajo, una fila horizontal scrolleable de `inventory-suggestion-chip`, cada uno con el nombre del producto y dos acciones rápidas: check (confirmar que sí, agregar a la lista) y X (descartar por ahora). Sin formularios, sin fechas, sin cantidades que ingresar a mano. Debe poder ignorarse completamente sin bloquear ninguna otra parte de la pantalla — tratarlo visualmente como una sugerencia opcional, no como una tarea pendiente.

### 7.11 Finanzas — dashboard detallado

> Ajuste sobre la pantalla ya prototipada en `mockup-web-v2.html` ("Desktop — Finanzas"), ahora como sub-tab "Dashboard" dentro del ítem de sidebar "Finanzas" (junto a "Historial", 7.9). Mantener stat-cards, gráfico de barras por categoría y lista de supermercados con monto. Agregar el `price-disclaimer-banner` cerca del total principal, mismo componente que en Historial.

### 7.12 Listas privadas + calendario

> Ajuste sobre la pantalla ya prototipada en `mockup-web-v2.html` ("Desktop — Listas privadas"). Mantener el `calendar-cell` y el patrón de estado (pendiente/completada/cancelada) ya definido. Sin cambios estructurales — solo alinear tipografía/tokens con el resto de pantallas nuevas de esta ronda.

### 7.13 Recetas + planificador semanal

> Ajuste sobre las pantallas ya prototipadas en `mockup-web-v2.html` ("Desktop — Planificador semanal de comidas" y su versión mobile), ahora organizadas como dos sub-tabs ("Recetas" / "Planificador semanal") dentro del ítem de sidebar "Recetas". El botón "Agregar receta a lista" y "Agregar semana a la lista" deben disparar la reconciliación de cantidades (7.3) cuando corresponda, igual que grupos.

### 7.14 Auth — login / signup

> Actualizado 2026-08-18 con el requerimiento del profesor ([[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|4.12]]). Pantalla de login y registro, formulario simple centrado, con la identidad de marca aplicada (Fraunces para el nombre "Tacha", fondo crema, botón primario teal). Toggle entre login y signup. **Login:** email, contraseña (con ícono de "ojo" para mostrar/ocultar, oculto por defecto), reCAPTCHA antes del botón de enviar, link "¿Olvidaste tu contraseña?" (va a 7.19). Debajo del formulario, separador "o" y dos botones secundarios "Continuar con Google" / "Continuar con Facebook". **Signup:** nombre, email, contraseña, repetir contraseña, barra de fortaleza de contraseña debajo del campo (colores del sistema: rojo/terracota → teal a medida que mejora), checkbox de términos y condiciones sin marcar por defecto, mismos botones de OAuth. Estado de error de validación con mensaje inline discreto (no un banner rojo agresivo) — genérico para credenciales inválidas, específico para cuenta no verificada/bloqueada. Estado de carga en el botón principal.

### 7.15 Crear o unirse a un household

> Pantalla posterior a elegir "Crear o unirme a un household" en el onboarding (7.7). Dos acciones igual de visibles: "Crear un household nuevo" (nombre del household) y "Unirme con una invitación" (campo para pegar link o código de `household_invite_links`). Tono cálido y simple, sin sensación de configuración técnica — 1-2 campos por acción, nada más.

### 7.16 Landing pública (Mirones)

> Página de inicio pública, primera pantalla que ve cualquier visitante — requerimiento del profesor, ver [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|4.12]] y [[Proyectos/Tacha/historias-usuario|historias-usuario.md]] (HU-01 a HU-11). Navbar pública arriba (logo Tacha, enlaces a secciones públicas, botón "Iniciar sesión" y "Registrarse" resaltado en teal). Hero section: título grande en Fraunces explicando el propósito ("Compras compartidas, sin líos"), subtítulo corto, CTA principal ("Empezar gratis") que lleva a signup. Sección introductoria con 2-3 puntos clave del producto + enlace "Leer más" hacia una sección ampliada más abajo en la misma página (ancla, no otra URL). Sección de demo: video o GIF corto mostrando el flujo de tachar/agregar productos, con controles de reproducción. Sección de testimonios en carrusel (foto/inicial, nombre, cita corta), con controles de flecha para desplazarse. Sección de formulario de contacto con reCAPTCHA. Footer: logo, info institucional breve, enlaces a redes sociales (con íconos), enlace a Términos y condiciones, enlace a About. Todo con la calidez de marca — nada de layout genérico de SaaS (hero + 3 cards + testimonios en el mismo orden de siempre sin personalidad).

### 7.17 About

> Página pública "Acerca de", accesible desde el navbar/footer de la landing (7.16) — ver [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|4.12]] (HU-12 a HU-14). Misma navbar/footer públicos que la landing. Sección de Misión y Visión, claramente diferenciadas (dos bloques o columnas, no mezcladas en un párrafo). Sección de información general de la organización. Formulario de contacto propio con reCAPTCHA al final (mismo patrón visual que el de la landing).

### 7.18 Verificación de correo

> Pantalla posterior al registro manual (mientras la cuenta está "pendiente de verificación"), ver [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|4.12]] (HU-17). Mensaje central cálido ("Te enviamos un correo a nombre@ejemplo.com — confirmá tu cuenta desde ahí"), ilustración simple de un sobre/check. Botón secundario "Reenviar correo" (con estado deshabilitado + countdown breve tras usarlo, para evitar spam). Si el usuario llega con un código expirado, mostrar el mismo botón de reenvío con el mensaje de expiración en vez del de bienvenida.

### 7.19 Recuperación de contraseña

> Dos pantallas del mismo flujo, ver [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|4.12]] (HU-28, HU-29). (a) Solicitud: formulario de un solo campo (correo) con botón "Enviar enlace de recuperación"; al enviar, siempre el mismo mensaje genérico de confirmación, sin revelar si el correo existe. (b) Nueva contraseña: accesible solo desde el link del correo — campos "Nueva contraseña" / "Repetir nueva contraseña" con la misma barra de fortaleza de 7.14, validación de coincidencia en tiempo real, y manejo de link expirado (mensaje + botón para reenviar la solicitud en vez de mostrar el formulario).

## 8. Cómo usar este documento con Stitch AI

1. Pegar la sección 1 (personalidad), 2 (tokens) y 3 (navegación) como contexto/system prompt del proyecto en Stitch, si la herramienta lo permite persistir entre generaciones.
2. Generar primero las 9 pantallas de prioridad Alta (sección 4) con los prompts 7.1, 7.1b, 7.2 a 7.8 y 7.16 — son las que no tienen ningún precedente visual todavía.
3. Revisar cada resultado contra el checklist "AI-genérico" de [[Sistema/skills/enterprise-ui-ux-design/SKILL|enterprise-ui-ux-design]] antes de darlo por bueno — nada de gradientes morado-azul, glassmorphism sin propósito, o el mismo radio de borde en todo.
4. Una vez aprobadas, exportar/adaptar a los componentes base de la sección 5 en vez de dejarlas como pantallas sueltas — así se reutilizan entre quien construye listas (Marcos), catálogo (Daniel) e inventario (Melany).
5. Actualizar la columna "Origen" de la tabla de la sección 4 a medida que cada pantalla pase de "Nueva" a "Generada" o "Implementada".
6. Si alguna pantalla o componente de este documento termina no siendo necesario al verlo generado, quitarlo o ajustarlo acá mismo — el criterio explícito de esta ronda es documentar de más y recortar después, no dejar huecos que alguien tenga que resolver a mitad de la generación.
