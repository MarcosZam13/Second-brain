---
proyecto: Tacha
tema: Análisis de complejidad, importancia y viabilidad (12 semanas, 6 personas + IA)
fecha: 2026-08-21
tipo: documentacion
estado: primera pasada — complejidad (Fibonacci) e importancia (opinión propia, desde cero) por HU, con encargado propuesto. Pendiente de revisar en equipo antes de repartir sprints en JIRA
tags: [complejidad, viabilidad, planificacion, jira, tacha]
---

# Análisis de complejidad, importancia y viabilidad — Tacha

Ver también: [[Proyectos/Tacha/historias-usuario|historias-usuario.md]] (v2.2) · [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] · [[Proyectos/Tacha/README|README]]

Complejidad en escala Fibonacci (1, 2, 3, 5, 8, 13 — puntos relativos, no horas: 1-2 = medio día con IA, 3-5 = 1-3 días, 8 = 3-5 días con casos borde reales, 13 = una semana o más / componente de infraestructura). Importancia es **opinión propia construida desde cero** (no reutiliza las prioridades Alta/Media/Baja de pantallas de DESIGN.md): Crítica (el producto no es Tacha sin esto) / Alta (se espera en cualquier versión decente) / Media (aporta valor real, se puede diferir sin romper nada) / Baja (agradable, prescindible con poca pérdida). Encargado sigue [[Proyectos/Tacha/documentacion-v1#12. División de trabajo|documentacion-v1.md sección 12]] donde ya estaba asignado; donde no había dueño (Landing/Auth extendida, Grupos, Configuración) propongo uno — a confirmar en equipo.

## Resumen — puntos de complejidad por persona

| Encargado | Puntos totales | # de HU | Módulo principal |
|---|---|---|---|
| **Esteban** | **89** | 28 | Auth completo (manual + social + recuperación) + Perfil + Household + Configuración |
| **Marcos** | 75 | 19 | Lista general (tachado), Sublistas, Listas privadas, Grupos |
| **Daniel** | 39 + infra scraping (13) | 8 | Catálogo + pipeline de scraping (subestimado por conteo de HU) |
| **Roberto** | 48 | 10 | Recetas, Planificador, Reconciliación al tachar |
| **Laura** | 32 | 11 | Dashboard financiero + Historial de compras |
| **Melany** | 37 | 18 | Landing/Footer/About + Inventario doméstico (más diseño UI de las 22 pantallas, transversal, no puntuable como HU) |

**Esteban queda con casi el doble de puntos que cualquier otra persona** — es la [[Proyectos/Tacha/README|consecuencia directa]] de que Landing/About/Auth-extendida (sección 4.12) se agregó el 18/08, después de la división de trabajo del 16/08, y nadie la reasignó. Ver recomendación al final.

## Landing, Footer, About (rol Visitante)

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-01 | Barra de navegación | 1 | Alta | Melany |
| HU-02 | Sección principal (Hero) | 2 | Alta | Melany |
| HU-03 | Información introductoria | 1 | Media | Melany |
| HU-04 | Consultar información ampliada | 2 | Baja | Melany |
| HU-05 | Testimonios | 2 | Baja | Melany |
| HU-06 | Formulario de contacto (reCAPTCHA) | 5 | Media | Esteban |
| HU-07 | Demo de uso | 3 | Baja | Melany |
| HU-08 | Información del pie de página | 1 | Alta | Melany |
| HU-09 | Redes sociales | 1 | Baja | Melany |
| HU-10 | Términos y condiciones | 2 | Media | Melany |
| HU-11 | Logotipo | 1 | Baja | Melany |
| HU-12 | Misión y visión | 1 | Media | Melany |
| HU-13 | Información de la organización | 1 | Media | Melany |
| HU-14 | Contacto desde About (reCAPTCHA) | 3 | Baja | Esteban |

## Registro, login y recuperación (rol Visitante)

| HU | Nombre | Complejidad | Importancia | Encargado |
|---|---|---|---|---|
| HU-14b | Registro con datos básicos | 3 | Crítica | Esteban |
| HU-15 | Validar coincidencia de contraseña | 2 | Alta | Esteban |
| HU-16 | Feedback de seguridad de contraseña | 3 | Media | Esteban |
| HU-17 | Verificación de correo electrónico | 5 | Alta | Esteban |
| HU-18 | Aceptación de T&C | 1 | Alta | Esteban |
| HU-19 | Registro mediante proveedor externo (Google/Facebook) | 5 | Media | Esteban |
| HU-20 | Completar datos faltantes tras registro social | 3 | Media | Esteban |
| HU-21 | Aceptación T&C en registro social | 2 | Media | Esteban |
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
| HU-33 | Crear link de invitación al household | 3 | Crítica | Esteban |
| HU-34 | Unirse a un household por link | 3 | Crítica | Esteban |
| HU-34b | Decidir qué hacer con mi lista al unirme | 5 | Alta | Esteban |
| HU-34c | Salir de mi household | 5 | Alta | Esteban |
| HU-35 | Consultar familiares del household | 2 | Alta | Esteban |
| HU-36 | Eliminar un familiar del household | 3 | Media | Esteban |

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
| HU-72 | Ver "Mis grupos" | 2 | Baja | Marcos |
| HU-73 | Crear un grupo de productos | 5 | Baja | Marcos |
| HU-74 | Agregar un grupo a la lista | 3 | Baja | Marcos |
| HU-75 | Editar un grupo existente | 3 | Baja | Marcos |
| HU-75b | Eliminar un grupo | 2 | Baja | Marcos |
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

## Pendiente de confirmar con el equipo

- Reasignar Landing/About/reCAPTCHA (dejé HU-06 y HU-14 con Esteban por el reCAPTCHA, el resto con Melany) — o decidir otra repartición; Esteban queda con 89 puntos, casi el doble que cualquier otro.
- Confirmar dueño de Grupos de productos (documentacion-v1.md ya dice que necesita coordinación Marcos+Daniel — lo dejé con Marcos por vivir del lado de listas).
- Redactar contenido institucional real (misión, visión, T&C) — no es un HU de código, pero bloquea HU-10 y HU-12 si nadie lo escribe a tiempo.
