---
proyecto: Tacha
tema: DESIGN.md — guía de diseño para generación de interfaz con Stitch AI
fecha: 2026-08-18
tipo: documentacion
estado: borrador — pantallas nuevas por generar hoy en Stitch AI; pantallas ya prototipadas en mockup-web-v2.html quedan como referencia de continuidad visual
tags: [diseño, ui-ux, stitch, tacha]
---

# DESIGN.md — Tacha

Ver también: [[Proyectos/Tacha/README|README]] · [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] (secciones 4, 6 y 9) · [[Proyectos/Tacha/mockups/mockup-web-v2.html|mockups/mockup-web-v2.html]]

**Propósito de este documento:** dar a quien genere pantallas en Stitch AI (hoy: principalmente Melany — diseño UI, y Marcos — listas/PWA) una referencia única y autocontenida de personalidad, tokens y pantallas, para que lo que salga de Stitch sea consistente con `mockup-web-v2.html` y con las decisiones de la reunión de equipo del 2026-08-16 (ver [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]]). No repite el detalle funcional completo de cada feature — para eso, el link a la sección correspondiente del documento de proyecto.

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

## 3. Inventario de pantallas

Pantallas ya prototipadas en `mockup-web-v2.html` (v2, el equipo las marca como "por mejorar mucho") vs. pantallas nuevas que salen de las decisiones del 2026-08-16 y todavía no existen en ningún mockup.

| Pantalla | Estado | Prioridad hoy | Referencia funcional |
|---|---|---|---|
| Onboarding — con/sin household | **Nueva** | Alta | [[Proyectos/Tacha/documentacion-v1#4.1 Gestión de usuarios, familias y perfiles|4.1]] |
| Catálogo de productos (búsqueda estilo Uber Eats) | **Nueva** | Alta | [[Proyectos/Tacha/documentacion-v1#4.5 Catálogo de productos y categorías|4.5]] |
| Reconciliación de cantidades al combinar listas | **Nueva** | Alta | [[Proyectos/Tacha/documentacion-v1#4.9.1 Reconciliación de cantidades al combinar listas (decisión 2026-08-16)|4.9.1]] |
| Edición rápida de item comprado (tachado) | **Nueva** | Alta | [[Proyectos/Tacha/documentacion-v1#4.6 Historial de compras|4.6]] |
| Lista general + dashboard financiero | Existe (mockup v2) | Media — ajustar con nuevos tokens de catálogo/categoría | [[Proyectos/Tacha/documentacion-v1#4.2 Lista general y dashboard financiero|4.2]] |
| Historial por día/semana/mes con total editable | **Nueva** (Finanzas del mockup no cubre esto) | Media | [[Proyectos/Tacha/documentacion-v1#4.6 Historial de compras|4.6]] |
| Inventario doméstico (sugerencias ligeras) | **Nueva** | Media | [[Proyectos/Tacha/documentacion-v1#4.10 Inventario doméstico|4.10]] |
| Listas privadas + calendario | Existe (mockup v2) | Baja — ya cubre el patrón | [[Proyectos/Tacha/documentacion-v1#4.4 Listas privadas (independientes del household)|4.4]] |
| Planificador semanal (desktop + mobile) | Existe (mockup v2) | Baja | [[Proyectos/Tacha/documentacion-v1#4.9 Recetas y planificador semanal de comidas|4.9]] |
| Auth (login/signup) | **Nueva** | Baja hoy | [[Proyectos/Tacha/documentacion-v1#4.1 Gestión de usuarios, familias y perfiles|4.1]] |

Recomendación para la sesión de hoy: generar primero las 4 de prioridad Alta en Stitch — son las que no tienen ningún precedente visual todavía, y las que más directamente destraban a Marcos (listas) y Melany (inventario). El resto puede iterar sobre lo que ya existe en `mockup-web-v2.html` en vez de regenerarse desde cero.

## 4. Componentes base a mantener consistentes

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

Componentes nuevos que salen de las decisiones del 2026-08-16 (no existían antes, definir su primer diseño en esta ronda de Stitch):

- **catalog-card** — tarjeta de resultado de búsqueda en el catálogo: imagen del producto, nombre, marca, chip de tamaño/presentación. Es el bloque repetible del catálogo estilo Uber Eats ([[Proyectos/Tacha/documentacion-v1#4.5 Catálogo de productos y categorías|4.5]]).
- **quantity-reconciliation-row** — fila de comparación "ya tenías X / necesitás Y", con selector de qué presentación agregar. Ver [[Proyectos/Tacha/documentacion-v1#4.9.1 Reconciliación de cantidades al combinar listas (decisión 2026-08-16)|4.9.1]] para la lógica exacta.
- **price-disclaimer-banner** — aviso persistente y no intrusivo de "precios estimados, no garantizados por ningún supermercado" ([[Proyectos/Tacha/documentacion-v1#4.6 Historial de compras|4.6]]) — debe aparecer cerca de cualquier precio sugerido sin volverse ruido visual repetido en cada pantalla.
- **inventory-suggestion-chip** — sugerencia de un toque ("¿Se te acabó la leche?") con confirmar/descartar, nunca un formulario ([[Proyectos/Tacha/documentacion-v1#4.10 Inventario doméstico|4.10]]).

## 5. Estados a cubrir por pantalla nueva

Por [[Sistema/skills/enterprise-ui-ux-design/SKILL|enterprise-ui-ux-design]]: cada pantalla nueva necesita más que el happy path.

| Pantalla | Estados mínimos a pedirle a Stitch |
|---|---|
| Catálogo de productos | Resultados con imagen, resultado sin imagen disponible (fallback por categoría, no ícono roto), sin resultados de búsqueda, cargando |
| Reconciliación de cantidades | Con diferencia a favor (ya alcanza), con déficit (hay que comprar más), producto sin variantes alternativas en catálogo |
| Edición rápida de item comprado | Edición inline abierta/cerrada, guardado confirmado (feedback inmediato) |
| Historial con total editable | Total confirmado, total "sin ingresar" (pendiente, con recordatorio visual), edición inline abierta |
| Inventario doméstico | Chip de sugerencia pendiente, confirmado, descartado |
| Onboarding | Sin household (uso solo), creando household, uniéndose por invitación |

## 6. Prompts listos para Stitch AI

Cada prompt asume que Stitch ya tiene cargada la personalidad (sección 1) y los tokens (sección 2) como contexto del proyecto — si Stitch no permite contexto persistente, repetir el bloque de personalidad + tokens al inicio de cada prompt individual.

### 6.1 Catálogo de productos (estilo Uber Eats)

> Pantalla de catálogo de productos para una app de listas de compras colaborativa. Personalidad cálida y hogareña (crema `#FBF6EE`, teal `#0E7C7B`, terracota `#D97B4F`, tipografía Fraunces para títulos + Public Sans para cuerpo). Barra de búsqueda arriba ("Buscar producto, ej. leche"). Debajo, resultados en grid de tarjetas (`catalog-card`): cada tarjeta con foto del producto en la parte superior, nombre del producto, marca en texto secundario, y chips de las presentaciones disponibles (ej. "1L", "200ml", "Galón") — al tocar un chip se selecciona esa variante para agregar a la lista. Filtro de categoría como fila de chips horizontal encima del grid (Lácteos, Panadería, Limpieza, etc.), con la categoría activa resaltada en teal. Diseñar para desktop (grid de 4 columnas) y mobile (grid de 2 columnas). Incluir estado de "sin resultados" con ilustración simple y sugerencia de crear producto nuevo.

### 6.2 Reconciliación de cantidades al combinar listas

> Pantalla/modal de reconciliación al agregar una receta o el plan semanal a la lista de compras. Título: "Ya tenías esto apuntado". Por cada producto en conflicto, una fila (`quantity-reconciliation-row`) con: nombre del producto, lo que el usuario ya tenía en la lista (ej. "1 caja pequeña — 1L"), lo que se necesita adicional (ej. "Necesitás 1L más"), y un selector de qué agregar con las opciones disponibles del catálogo para ese producto (ej. "+1 caja pequeña (1L)" vs "Cambiar a 1 galón (3.78L)"), mostrando idealmente el precio estimado de cada opción en terracota. Botón "Confirmar y agregar" al final, estilo cálido, sin sensación de formulario técnico. Debe sentirse como una decisión asistida, no como una advertencia de error.

### 6.3 Edición rápida de item comprado (al tachar)

> Componente de edición inline sobre una fila de item ya tachado en la lista de compras (`item-row` existente). Al tocar la fila tachada, se expande sin salir de la lista mostrando: cantidad/presentación realmente comprada (editable, con opciones rápidas tipo chip en vez de solo un input numérico — ej. "1 caja pequeña", "1 galón"), y dónde se compró. Todo debe poder editarse en menos de 2 toques, sin navegar a otra pantalla. Confirmación visual inmediata (check animado o cambio de color sutil) al guardar.

### 6.4 Historial de compras con total editable

> Pantalla de historial de compras con selector de periodo arriba (Día / Semana / Mes, como pills, la seleccionada en teal sólido). Debajo, el total del periodo en tipografía Fraunces grande, con un ícono de lápiz pequeño al lado para editarlo directamente (sin entrar producto por producto). Debajo del total, un aviso pequeño y discreto (`price-disclaimer-banner`) tipo "Los precios son estimados, Tacha no está afiliado a ningún supermercado". Debajo, lista de sesiones de compra del periodo (fecha, supermercado, monto), cada una también con su propio total editable inline. Sesiones sin total ingresado deben distinguirse visualmente (ej. badge terracota "Sin total") sin sentirse como un error.

### 6.5 Inventario doméstico (sugerencias ligeras)

> Sección opcional dentro de la lista general o del dashboard, nunca una pantalla obligatoria de por sí. Título discreto: "¿Se te está acabando algo?". Debajo, una fila horizontal scrolleable de chips de sugerencia (`inventory-suggestion-chip`), cada uno con el nombre del producto y dos acciones rápidas: check (confirmar que sí, agregar a la lista) y X (descartar por ahora). Sin formularios, sin fechas, sin cantidades que ingresar a mano. Debe poder ignorarse completamente sin bloquear ninguna otra parte de la pantalla — tratarlo visualmente como una sugerencia opcional, no como una tarea pendiente.

### 6.6 Onboarding — con o sin household

> Pantalla de bienvenida después del signup, antes de entrar a la app. Personalidad cálida y hogareña, con la tipografía Fraunces en el título principal ("¿Cómo querés empezar?"). Dos opciones igual de válidas visualmente (ninguna se ve como "la opción incompleta"): (1) "Usar Tacha solo/a" — ícono de una sola persona, texto secundario explicando que igual tendrá su lista general, sublistas y listas privadas; (2) "Crear o unirme a un household" — ícono de familia/grupo, texto secundario explicando que permite compartir listas familiares. Ambas como cards grandes tocables, no como radio buttons pequeños. Debe quedar claro que la decisión no es permanente ni bloqueante.

## 7. Cómo usar este documento con Stitch AI

1. Pegar la sección 1 (personalidad) y 2 (tokens) como contexto/system prompt del proyecto en Stitch, si la herramienta lo permite persistir entre generaciones.
2. Generar primero las 4 pantallas de prioridad Alta (sección 3) con los prompts de la sección 6.1-6.4.
3. Revisar cada resultado contra el checklist "AI-genérico" de [[Sistema/skills/enterprise-ui-ux-design/SKILL|enterprise-ui-ux-design]] antes de darlo por bueno — nada de gradientes morado-azul, glassmorphism sin propósito, o el mismo radio de borde en todo.
4. Una vez aprobadas, exportar/adaptar a los componentes base de la sección 4 en vez de dejarlas como pantallas sueltas — así se reutilizan entre quien construye listas (Marcos) y quien construye inventario (Melany).
5. Actualizar la tabla de la sección 3 (columna Estado) a medida que cada pantalla pase de "Nueva" a "Generada" o "Implementada".
