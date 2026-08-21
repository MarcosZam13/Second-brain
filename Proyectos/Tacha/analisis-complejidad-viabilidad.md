---
proyecto: Tacha
tema: Análisis de complejidad, importancia y viabilidad (12 semanas, 6 personas + IA)
fecha: 2026-08-21
tipo: documentacion
estado: v2 — complejidad (Fibonacci) e importancia (opinión propia, desde cero) por HU, encargado rebalanceado (Esteban y Marcos estaban muy por encima del resto) y plan de 10 sprints de 1 semana respetando dependencias, más 2 semanas de testing/deploy. Pendiente de validar en equipo antes de repartir en JIRA
tags: [complejidad, viabilidad, planificacion, jira, tacha]
---

# Análisis de complejidad, importancia y viabilidad — Tacha

Ver también: [[Proyectos/Tacha/historias-usuario|historias-usuario.md]] (v2.2) · [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] · [[Proyectos/Tacha/README|README]]

Complejidad en escala Fibonacci (1, 2, 3, 5, 8, 13 — puntos relativos, no horas: 1-2 = medio día con IA, 3-5 = 1-3 días, 8 = 3-5 días con casos borde reales, 13 = una semana o más / componente de infraestructura). Importancia es **opinión propia construida desde cero** (no reutiliza las prioridades Alta/Media/Baja de pantallas de DESIGN.md): Crítica (el producto no es Tacha sin esto) / Alta (se espera en cualquier versión decente) / Media (aporta valor real, se puede diferir sin romper nada) / Baja (agradable, prescindible con poca pérdida).

**Encargado — v2, rebalanceado (2026-08-21):** la asignación original de [[Proyectos/Tacha/documentacion-v1#12. División de trabajo|documentacion-v1.md sección 12]] dejaba a Esteban con casi el doble de puntos que cualquiera (89, por la Landing/Auth extendida que se agregó el 18/08 después de repartir módulos el 16/08) y a Marcos bastante por encima también (75). Se movieron **bloques completos** (nunca HU sueltas, para no perder contexto) a quien tenía espacio:
- Registro social (HU-19,20,21) + formularios de contacto con reCAPTCHA (HU-06,14) → de Esteban a **Melany** (ya construye las pantallas de Landing/About donde viven).
- Household completo (HU-33,34,34b,34c,35,36) → de Esteban a **Laura** (trabajo de CRUD + reglas de negocio sobre Supabase, cercano a lo que ya hace en Dashboard/Historial; además le da trabajo desde temprano en vez de esperar a que existan datos de compra).
- Grupos de productos (HU-72 a HU-75b) → de Marcos a **Daniel** (documentacion-v1.md ya señalaba que Grupos depende del catálogo — queda mejor con quien lo construye).

## Resumen — puntos de complejidad por persona (v2, rebalanceado)

| Encargado | Puntos totales | # de HU | Módulo principal |
|---|---|---|---|
| **Marcos** | 60 | 14 | Lista general (tachado), Sublistas, Listas privadas |
| **Melany** | 55 | 18 | Landing/Footer/About + formularios de contacto + Registro social + Inventario doméstico (más diseño UI de las 22 pantallas, transversal, no puntuable como HU) |
| **Daniel** | 54 (incluye infra scraping) | 13 | Catálogo + pipeline de scraping (subestimado por conteo de HU) + Grupos de productos |
| **Laura** | 53 | 17 | Dashboard financiero + Historial de compras + Household |
| **Esteban** | 50 | 17 | Registro manual + Login + Recuperación + Perfil + Configuración |
| **Roberto** | 48 | 10 | Recetas, Planificador, Reconciliación al tachar |

Rango 48-60 (antes 32-89) — mucho más parejo. Roberto queda con el módulo que ya identifiqué como primer candidato de corte (Recetas/Planificador/Reconciliación, ver más abajo); si el equipo decide cortarlo, es quien más margen libera para ayudar a otro.

## Landing, Footer, About (rol Visitante)

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-01 | Barra de navegación | 1 | Alta | Melany |
| HU-02 | Sección principal (Hero) | 2 | Alta | Melany |
| HU-03 | Información introductoria | 1 | Media | Melany |
| HU-04 | Consultar información ampliada | 2 | Baja | Melany |
| HU-05 | Testimonios | 2 | Baja | Melany |
| HU-06 | Formulario de contacto (reCAPTCHA) | 5 | Media | Melany |
| HU-07 | Demo de uso | 3 | Baja | Melany |
| HU-08 | Información del pie de página | 1 | Alta | Melany |
| HU-09 | Redes sociales | 1 | Baja | Melany |
| HU-10 | Términos y condiciones | 2 | Media | Melany |
| HU-11 | Logotipo | 1 | Baja | Melany |
| HU-12 | Misión y visión | 1 | Media | Melany |
| HU-13 | Información de la organización | 1 | Media | Melany |
| HU-14 | Contacto desde About (reCAPTCHA) | 3 | Baja | Melany |

## Registro, login y recuperación (rol Visitante)

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-14b | Registro con datos básicos | 3 | Crítica | Esteban |
| HU-15 | Validar coincidencia de contraseña | 2 | Alta | Esteban |
| HU-16 | Feedback de seguridad de contraseña | 3 | Media | Esteban |
| HU-17 | Verificación de correo electrónico | 5 | Alta | Esteban |
| HU-18 | Aceptación de T&C | 1 | Alta | Esteban |
| HU-19 | Registro mediante proveedor externo (Google/Facebook) | 5 | Media | Melany |
| HU-20 | Completar datos faltantes tras registro social | 3 | Media | Melany |
| HU-21 | Aceptación T&C en registro social | 2 | Media | Melany |
| HU-22 | Login con reCAPTCHA | 3 | Alta | Esteban |
| HU-23 | Mostrar/ocultar contraseña | 1 | Baja | Esteban |
| HU-24 | Mensajes de error en login | 2 | Alta | Esteban |
| HU-25 | Feedback de seguridad de contraseña en login | 3 | Baja | Esteban |
| HU-26 | Token de seguridad de sesión (JWT) | 5 | Crítica | Esteban |
| HU-27 | Cierre de sesión por inactividad | 5 | Media | Esteban |
| HU-28 | Recuperación de contraseña | 3 | Alta | Esteban |
| HU-29 | Vista de actualización de contraseña | 3 | Alta | Esteban |

## Perfil, sesión y household (rol Usuario)

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-30 | Editar datos de perfil | 3 | Alta | Esteban |
| HU-31 | Cambiar contraseña | 3 | Media | Esteban |
| HU-32 | Cerrar sesión | 2 | Alta | Esteban |
| HU-33 | Crear link de invitación al household | 3 | Crítica | Laura |
| HU-34 | Unirse a un household por link | 3 | Crítica | Laura |
| HU-34b | Decidir qué hacer con mi lista al unirme | 5 | Alta | Laura |
| HU-34c | Salir de mi household | 5 | Alta | Laura |
| HU-35 | Consultar familiares del household | 2 | Alta | Laura |
| HU-36 | Eliminar un familiar del household | 3 | Media | Laura |

## Lista general (el corazón del producto)

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-36a | Buscar y añadir producto | 5 | Crítica | Marcos |
| HU-36b | Ajustar cantidad | 2 | Crítica | Marcos |
| HU-36c | Ver detalle de producto | 3 | Media | Marcos |
| HU-36d | Eliminar producto | 2 | Alta | Marcos |
| HU-36e | Tachar/destachar producto (sin checkbox, 2 secciones) | 8 | Crítica | Marcos |
| HU-36f | Modo compra | 8 | Alta | Marcos |
| HU-36g | Combinar lista general y sublista | 8 | Media | Marcos |

## Dashboard financiero

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-37 | Ver gasto total por periodo | 3 | Alta | Laura |
| HU-38 | Ver gastos por household o listas privadas | 3 | Media | Laura |
| HU-39 | Ver gastos por categoría de producto | 5 | Alta | Laura |
| HU-40 | Ver gastos por supermercado | 3 | Media | Laura |
| HU-41 | Ver gastos por persona | 3 | Media | Laura |
| HU-42 | Ver productos más comprados y más costosos | 3 | Baja | Laura |
| HU-43 | Aviso de precios estimados | 1 | Media | Laura |

## Sublistas por fecha y listas privadas

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-44 | Ver calendario de sublistas | 5 | Media | Marcos |
| HU-45 | Crear sublista en una fecha | 3 | Media | Marcos |
| HU-46 | Ver y gestionar estado de sublista | 3 | Media | Marcos |
| HU-47 | Ver total de gasto de una sublista | 2 | Baja | Marcos |
| HU-48 | Crear lista privada | 3 | Media | Marcos |
| HU-49 | Invitar colaboradores a lista privada | 5 | Media | Marcos |
| HU-50 | Gestionar una lista privada | 3 | Media | Marcos |

## Catálogo, scraping y mis productos personalizados

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| — | **Pipeline de scraping** (staging, dedup, legal por súper — infraestructura, no tiene HU/CA propia) | **13** | **Crítica** | Daniel |
| HU-51 | Buscar productos en el catálogo global | 5 | Crítica | Daniel |
| HU-52 | Filtrar catálogo por categoría | 3 | Alta | Daniel |
| HU-53 | Ver detalle de producto (marcas y precio) | 5 | Alta | Daniel |
| HU-55 | Ver mis productos personalizados | 2 | Media | Daniel |
| HU-56 | Crear un producto personalizado (fusiona HU-54) | 5 | Alta | Daniel |
| HU-57 | Asociar tienda y precio de referencia | 3 | Baja | Daniel |
| HU-58 | Editar o eliminar un producto personalizado | 3 | Media | Daniel |

## Historial de compras

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-59 | Ver historial de sesiones de compra | 3 | Alta | Laura |
| HU-60 | Editar el total de una sesión o periodo | 3 | Media | Laura |
| HU-61 | Ver sesiones sin total ingresado | 2 | Baja | Laura |
| HU-62 | Filtrar historial por supermercado y categoría | 3 | Baja | Laura |

## Recetas, planificador y reconciliación al tachar

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-63 | Ver catálogo de recetas del household | 2 | Media | Roberto |
| HU-64 | Crear o editar una receta | 8 | Media | Roberto |
| HU-64b | Eliminar una receta | 2 | Baja | Roberto |
| HU-65 | Agregar receta a la lista | 5 | Media | Roberto |
| HU-66 | Ver qué falta de una receta | 5 | Baja | Roberto |
| HU-67 | Ver calendario semanal de comidas | 3 | Baja | Roberto |
| HU-68 | Asignar receta, cocinero y porciones | 5 | Baja | Roberto |
| HU-69 | Agregar la semana completa a la lista | 5 | Baja | Roberto |
| HU-76 | Ver aviso pasivo de faltante de receta/plan | 5 | Media | Roberto |
| HU-77 | Resolver el faltante al tachar el item | 8 | Media | Roberto |

## Inventario doméstico (ya marcado como opcional en el alcance oficial)

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-70 | Ver sugerencias de inventario | 5 | Media | Melany |
| HU-70b | Indicar cuánto le va a durar un producto | 3 | Media | Melany |
| HU-71 | Confirmar o descartar una sugerencia | 2 | Media | Melany |
| HU-71b | Ver mi inventario completo | 3 | Baja | Melany |
| HU-71c | Marcar producto como agotado o ajustar vencimiento | 3 | Baja | Melany |
| HU-71d | Agregar algo al inventario manualmente | 3 | Baja | Melany |

## Grupos de productos y Configuración

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-72 | Ver "Mis grupos" | 2 | Baja | Daniel |
| HU-73 | Crear un grupo de productos | 5 | Baja | Daniel |
| HU-74 | Agregar un grupo a la lista | 3 | Baja | Daniel |
| HU-75 | Editar un grupo existente | 3 | Baja | Daniel |
| HU-75b | Eliminar un grupo | 2 | Baja | Daniel |
| HU-78 | Activar el "encargado" para una lista | 3 | Baja | Esteban |

## Mi recomendación de corte, si hace falta cortar

Con Landing+Auth+Configuración confirmados como rápidos (tu propia experiencia, 1-2 semanas), el resto tiene que caber en lo que quede del calendario entre 6 personas. Si hay que sacrificar algo, en este orden — de menos a más doloroso de cortar:

1. **Grupos de productos completo (HU-72 a HU-75b, 5 HU, 15 pts).** Es un atajo de conveniencia sobre algo que ya existe (buscar y añadir producto). Sin esto la app sigue siendo 100% funcional, solo un poco menos cómoda.
2. **Planificador semanal (HU-67 a HU-69, 3 HU, 13 pts).** Depende de que Recetas ya esté sólido; es la capa más alejada del value prop principal (listas + finanzas).
3. **Reconciliación al tachar / "¿Qué hiciste?" (HU-76, HU-77, 2 HU, 13 pts).** Solo importa si Recetas y Planificador sobreviven — si se cortan esos, esto se cae solo.
4. **Inventario doméstico completo (HU-70 a HU-71d, 6 HU, 19 pts).** Ya está marcado como opcional en el alcance oficial (sección 3 de documentacion-v1.md) — cortarlo no rompe ningún acuerdo con el profesor.
5. **Recetas (HU-63 a HU-66, 4 HU, 20 pts).** Más doloroso de cortar porque es una feature completa con su propio valor, pero si el tiempo aprieta de verdad, es la primera "epic completa" que yo sacrificaría antes que tocar Lista general, Catálogo o Dashboard.
6. **Listas privadas (HU-48 a HU-50, 3 HU, 11 pts).** El household ya cubre el caso de uso colaborativo principal; listas privadas es la variante "amigos/viaje", valiosa pero no la razón de ser del producto.

Lo que **no** tocaría bajo ninguna circunstancia: Lista general con tachado, Household, Catálogo (aunque sea con semilla manual en vez de scraping en vivo si el pipeline no está listo a tiempo), Dashboard financiero básico, y todo el bloque de Auth — eso es lo que hace que Tacha sea Tacha y lo que el profesor evalúa como base del curso.

## Plan de sprints (10 semanas de construcción + 2 de testing/deploy)

Con 320 puntos entre 10 semanas, el promedio es ~32 pts/semana entre 6 personas (~5.3 pts/persona/semana) — el mismo número que calculaste. El orden respeta dependencias reales: nadie puede "buscar y añadir producto" (HU-36a) sin que el catálogo tenga datos, nadie puede tachar (HU-36e) sin que la lista general exista, Recetas necesita el catálogo para linkear ingredientes, etc. **Landing (Melany) no depende de nada del backend, así que arranca en paralelo desde la semana 1** en vez de esperar al final.

| Semana | Marcos (60) | Melany (55) | Daniel (54) | Laura (53) | Esteban (50) | Roberto (48) | Total |
|---|---|---|---|---|---|---|---|
| 1 | Setup lista general + Ajustar cantidad (HU-36b) — 2 | Landing core: nav, hero, footer (HU-01,02,08,09,11) — 6 | Arranca pipeline de scraping + schema catálogo — 6 | Prep: shell de Dashboard sin datos reales | Registro manual (HU-14b,15,16,17,18) — 14 | Prep: schema de recetas/planificador | 28 |
| 2 | Buscar/añadir/eliminar producto (HU-36a,36d) — 7 | Landing resto + T&C/About (HU-03,04,05,07,10,12,13) — 10 | Pipeline de scraping (cont.) — 7 | Household: invitar y unirse (HU-33,34) — 6 | Login (HU-22,23,24,25,26) — 14 | Prep (esperando catálogo) | 44 |
| 3 | Ver detalle producto (HU-36c) — 3 | Formularios de contacto (HU-06,14) — 8 | Catálogo: buscar y filtrar (HU-51,52) — 8 | Household: salir/decidir lista/miembros (HU-34b,34c,35,36) — 15 | Login (HU-27,28,29) + Recuperación — 11 | Recetas: catálogo + crear/editar (HU-63,64) — 10 | 55 |
| 4 | **Tachar/destachar (HU-36e)** — 8 | Registro social (HU-19,20,21) — 10 | Detalle de producto + Mis productos (HU-53,55,56) — 12 | Dashboard básico contra datos reales (HU-37,43) — 4 | Perfil (HU-30,31,32) — 8 | Recetas: agregar a lista, qué falta (HU-64b,65,66) — 12 | 54 |
| 5 | Modo compra (HU-36f) — 8 | Buffer / QA de Auth+Landing | Mis productos resto (HU-57,58) — 6 | Historial de compras (HU-59,60,61,62) — 11 | Configuración (HU-78) — 3 | Planificador semanal (HU-67,68,69) — 13 | 41 |
| 6 | Sublistas (HU-44,45,46,47) — 13 | Inventario: sugerencias (HU-70,70b,71) — 10 | Grupos de productos (HU-72,73) — 7 | Dashboard resto (HU-38,39,40,41,42) — 17 | Buffer / apoyo a QA | Reconciliación al tachar (HU-76,77) — 13 | 60 |
| 7 | Combinar lista+sublista (HU-36g) — 8 | Inventario resto (HU-71b,71c,71d) — 9 | Grupos resto (HU-74,75,75b) — 8 | Buffer / QA de Household+Dashboard | Buffer / apoyo a QA | Buffer / QA de Recetas | 25 |
| 8 | Listas privadas (HU-48,49,50) — 11 | Buffer / pulido de Inventario | Buffer / pulido de Catálogo | Buffer | Buffer | Buffer | 11 |
| 9-10 | Integración cruzada: modo compra + sublistas + privadas + grupos jugando juntos; cierre de huecos que aparezcan al integrar todo | | | | | | — |
| 11-12 | **Testing y deploy** (no incluido en los 320 pts): pruebas end-to-end, corrección de bugs de integración, deploy, ensayo de presentación | | | | | | — |

Semanas 7-8 quedan livianas a propósito — son el colchón real del proyecto. Si algo de las semanas 1-6 se atrasa (lo más probable: scraping de Daniel o tachado de Marcos, que son los dos componentes más riesgosos), ahí es donde se recupera sin tener que sacrificar Recetas/Planificador/Inventario todavía. Si para la semana 8 el atraso ya comió ese colchón, ahí se activa la lista de corte de arriba, empezando por Grupos.

## Pendiente de confirmar con el equipo

- ~~Reasignar Landing/About/reCAPTCHA~~ y ~~confirmar dueño de Grupos~~ — resuelto arriba (v2 rebalanceada); falta que el equipo lo valide, sobre todo si alguien tiene más experiencia específica en un área que no calce con esta repartición.
- Redactar contenido institucional real (misión, visión, T&C) — no es un HU de código, pero bloquea HU-10 y HU-12 si nadie lo escribe a tiempo. No tiene dueño todavía.
- Validar que Daniel esté de acuerdo con el orden — su pipeline de scraping es la dependencia más larga (semanas 1-3) y bloquea a Marcos (HU-36a, semana 2) y a Roberto (Recetas, semana 3); si se atrasa, se atrasa todo lo demás en cascada.
