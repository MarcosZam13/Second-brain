---
proyecto: Tacha
tema: Documento de Proyecto — v1.0 (Propuesta formal)
fecha: 2026-08-09
tipo: documentacion
estado: stack + DB confirmados por todo el equipo en reunión del 2026-08-16, pendiente de confirmación del profesor — resto de decisiones de esa reunión incorporadas, ver sección 10
fuente: _fuentes/Tacha_documentacion-v1_2026-08-09.docx
tags: [documentacion, propuesta, requerimientos, arquitectura, tacha]
---

# Documento de Proyecto — Tacha

Ver también: [[Proyectos/Tacha/README|README]] · [[Proyectos/README|Proyectos]] · [[Proyectos/Tacha/DESIGN|DESIGN.md]]

**Estado:** Propuesta formal — v1.0 · **Curso:** Introducción al Desarrollo Web · **Equipo:** 6 integrantes · **Última actualización:** 2026-08-18 (decisiones de la reunión de equipo del 2026-08-16)

> Reunión de equipo completa el domingo 2026-08-16 (~2.5h): se confirmó el stack y la base de datos (sección 7) — queda pendiente solo la confirmación del profesor. Se cerraron varias de las preguntas de la [[#10. Pendientes de definición|sección 10]] original; el resto de definiciones nuevas quedan en esa misma sección.

## 1. Resumen ejecutivo

Tacha es una aplicación web para que un grupo de usuarios (familias, o grupos de amigos) administre listas de compras de forma colaborativa, con seguimiento de gastos y datos reales de productos/precios obtenidos mediante web scraping de sitios de supermercados. Es un proyecto de equipo para el curso de Introducción al Desarrollo Web, con énfasis en:

- Colaboración en tiempo real sobre listas compartidas (familiares o privadas).
- Finanzas domésticas: dashboard de gasto por producto, categoría, supermercado y periodo.
- Datos reales: catálogo de productos y precios poblado por scraping de sitios oficiales de supermercados costarricenses, no solo entrada manual.
- Planificación de comidas: un planificador semanal que conecta recetas, quién cocina cada día, y qué falta comprar.
- Accesibilidad desde cualquier dispositivo: web responsive, instalable como PWA, sin depender de tiendas de aplicaciones.

## 2. Objetivos del producto

- Permitir que un grupo (familia o amigos) coordine compras compartidas sin duplicar esfuerzo.
- Dar visibilidad financiera real: cuánto se gasta, dónde, en qué, y quién compró qué.
- Demostrar un pipeline de datos real (web scraping → base de datos → producto) como parte central del proyecto, no como añadido.
- Ofrecer una experiencia web responsive de calidad profesional, utilizable cómodamente tanto en desktop como en celular, sin necesitar una app nativa.
- Facilitar la planificación de comidas semanales conectada directamente con las listas de compra.

## 3. Alcance del proyecto (v1)

| Feature | Incluido | Notas |
|---|---|---|
| Gestión de usuarios, familias y perfiles | Sí | Auth + creación/pertenencia a household — **pertenecer a un household es opcional**, ver [[#4.1 Gestión de usuarios, familias y perfiles]] |
| Lista general con dashboard financiero | Sí | Gasto por día/producto/categoría/súper/persona; existe también para un usuario sin household (uso solo) |
| Sublistas por fecha (calendario) | Sí | Estado: pendiente / completada / cancelada; fusión opcional con la general; también disponible sin household |
| Listas privadas (no familiares) | Sí | Independientes del household siempre, con invitados propios (ver [[#4.4 Listas privadas (independientes del household)]]) |
| Catálogo de productos y categorías | Sí | Poblado inicialmente por web scraping; con imagen, marca y variantes de tamaño (ver [[#4.5 Catálogo de productos y categorías]]) |
| Web scraping de productos/precios | Sí — prioridad alta | Motor central del proyecto, ver [[#4.7 Web scraping — motor de datos (prioridad alta del proyecto)]] |
| Sugerencias de dónde comprar | Sí | Basado en precios obtenidos por scraping + historial propio |
| Historial de compras | Sí | Sesiones de compra por household/súper/día, edición rápida (ver [[#4.6 Historial de compras]]) |
| Recetas y planificador semanal de comidas | Sí | Ver [[#4.9 Recetas y planificador semanal de comidas]] |
| Inventario doméstico | Sí — opcional, no obligatorio | Decidido en reunión 2026-08-16: se ofrece como herramienta, nunca se le exige al usuario. Ver [[#4.10 Inventario doméstico]] |
| Geolocalización / geofencing | Fuera de alcance | Descartado por complejidad para el contexto del curso |

### Roadmap post-curso (opcional, si el equipo decide continuar)

- Notificaciones push web
- Versión de app nativa/instalable más avanzada
- Inventario doméstico completo, si el enfoque ligero valida bien con usuarios reales

## 4. Requerimientos funcionales detallados

### 4.1 Gestión de usuarios, familias y perfiles

- Autenticación de usuarios (Supabase Auth).
- **Decisión 2026-08-16: pertenecer a un household es opcional.** La app es completamente usable sin estar asociado a ninguna familia — un usuario solo tiene su propia lista general y sus sublistas por fecha, además de las listas privadas (que ya eran independientes del household). Ver implicación de modelo de datos en [[#6. Modelo de datos (resumen conceptual)]].
- Un usuario puede pertenecer a uno o más households (familias), cada uno con su propio rol (admin/miembro) — pero no está obligado a pertenecer a ninguno para usar el resto de la app.
- Perfil básico: nombre, foto opcional, household(s) a los que pertenece (puede ser ninguno).
- Solo el admin de un household invita nuevos miembros.
- Pendiente de decidir (no cerrado el 2026-08-16): qué pasa con las listas de un usuario que empezó solo cuando se une o crea un household después — ¿se ofrecen para asociar retroactivamente, o quedan siempre personales y las de household se crean aparte? Ver [[#10. Pendientes de definición]].

### 4.2 Lista general y dashboard financiero

- **Los 3 tipos de lista (general, sublista por fecha, privada) existen siempre; solo la general y la sublista por fecha se asocian a un household, y únicamente si el usuario pertenece a uno** (decisión 2026-08-16). Sin household, esas dos siguen existiendo pero son personales (`household_id` nulo, `owner_id` = el usuario). Las listas privadas nunca se asocian a un household — ver [[#4.4 Listas privadas (independientes del household)]].
- Lista general infinita por household (o personal si no hay household), con productos organizados por categoría — el orden por categoría se prioriza para que reproduzca un recorrido lógico de compra (ver [[#4.5 Catálogo de productos y categorías]]).
- Catálogo de productos seleccionable con autocompletado (no texto libre exacto), cada producto con categoría asignada; posibilidad de crear producto nuevo con su categoría si no existe.
- Etiqueta de tamaño por item (ej. "1L", "paquete de 12"), específica de cada instancia en la lista — corresponde a una variante del catálogo, ver [[#4.5 Catálogo de productos y categorías]].
- Unificación automática de cantidades cuando dos o más miembros agregan el mismo producto **con la misma unidad/tamaño** a la misma lista, con desglose de quién pidió cuánto. Cuando la unificación cruza recetas o el plan semanal (tamaños/unidades no directamente comparables, ej. litros vs. caja), no se sigue esta regla automática — se aplica la reconciliación asistida de la [[#4.9 Recetas y planificador semanal de comidas|sección 4.9]].
- Tachado con registro de: quién compró, dónde, cuándo, cantidad — se distingue cantidad pedida de cantidad realmente comprada. La edición de qué se compró (cantidad/tamaño real) tiene que ser rápida, sin fricción, porque alimenta directamente las finanzas (ver [[#4.6 Historial de compras]]).
- Dashboard financiero: gasto total por día/semana/mes, desglose por categoría de producto, desglose por supermercado, desglose por persona (quién ha comprado más/gastado más), y productos específicos más comprados o más costosos. El usuario debe ver siempre presente el aviso de que los precios son estimados (ver [[#4.6 Historial de compras]]).

### 4.3 Sublistas por fecha (con calendario)

- Vista de calendario para crear y visualizar listas asociadas a una fecha (viaje, evento familiar).
- Cada sublista tiene su propio total de gasto, independiente del total general.
- Estado de la sublista: pendiente, completada (todos los items comprados), o cancelada (el usuario puede cancelar explícitamente una sublista que ya no se va a comprar, sin que cuente como pendiente eternamente ni se borre el registro).
- Sesión de compra combinada (opcional): al iniciar una compra desde una sublista, se puede fusionar visualmente con la lista general — agrupando por producto en tres bloques (solo en general / repetidos en ambas, como filas independientes por lista / solo en la sublista), sin fusionar los registros de datos. Cada fila conserva su propia lista de origen, cantidad y estado.

### 4.4 Listas privadas (independientes del household)

Una lista privada:

- La crea cualquier usuario individual, no está atada a ningún household.
- El creador invita a quien quiera (amigos, compañeros de viaje) por correo o link — los invitados no necesitan ser miembros de ningún household del creador, ni familiares entre sí.
- Vive en una vista de calendario separada ("Mis listas privadas").
- Tiene la misma lógica de tachado, unificación de cantidades y estado (pendiente/completada/cancelada) que las sublistas familiares — se reutiliza el mismo motor de listas, solo cambia el modelo de quién tiene acceso.
- Implicación de arquitectura: el acceso a una lista no puede resolverse solo por pertenencia a un household. Se necesita una tabla de colaboradores por lista, independiente de los miembros del household (ver [[#6. Modelo de datos (resumen conceptual)]]).

### 4.5 Catálogo de productos y categorías

- Catálogo global compartido entre todos los usuarios + productos propios por household (si un household necesita algo muy específico que no está en el catálogo global).
- El catálogo global se puebla principalmente mediante el pipeline de web scraping ([[#4.7 Web scraping — motor de datos (prioridad alta del proyecto)|sección 4.7]]); el ingreso manual queda como fallback/complemento.
- **Decisión 2026-08-16 — catálogo estilo Uber Eats:** buscar "leche" debe mostrar tarjetas con foto, nombre, marca y las distintas presentaciones/tamaños disponibles (caja 1L, caja 200ml, galón, etc.), no una sola fila de texto. Cada combinación producto+marca+tamaño es una variante propia del catálogo, no una anotación libre — ver [[#6. Modelo de datos (resumen conceptual)]] para la tabla de variantes.
- Implicación directa para el scraping (sección 4.7): el pipeline debe capturar también la URL de imagen del producto, no solo nombre/precio/categoría — riesgo a validar con quien lidere ese módulo, ya que no todos los sitios de supermercados exponen imágenes igual de fácil.
- Búsqueda y navegación priorizan categoría por encima de todo: filtro/browse por categoría como primer nivel, y las listas se ordenan y agrupan por categoría (no alfabético ni por fecha de agregado) para que el usuario pueda recorrer la tienda en un orden lógico al comprar.

### 4.6 Historial de compras

- Sesiones de compra agrupadas por household + supermercado + día, con total editable (no se captura precio por item individual) — **confirmado en la reunión 2026-08-16** como la mejor solución práctica: pedir precio por producto sería más exacto para el desglose por categoría, pero es demasiada fricción; el total editable a mano es el balance elegido, aceptando que introduce una desviación entre el total real y el desglose por categoría/producto que se muestra en el dashboard.
- El historial se puede ver y filtrar por día, semana o mes, mostrando el total gastado de ese periodo — y ese total (igual que el de cada sesión individual) es editable directamente, sin tener que entrar producto por producto, porque el usuario suele terminar gastando distinto de lo que la app calculó.
- Editar qué se compró realmente (cantidad y tamaño/variante, ej. "1 galón" en vez de "2 cajas pequeñas") tiene que ser rápido y de baja fricción en el momento del tachado — esta distinción sí importa para las finanzas aunque no se capture precio por item.
- Si una sesión queda sin total ingresado por un tiempo, se recuerda al usuario; si se ignora, queda visible en el historial como "sin total", editable en cualquier momento.
- **Aviso obligatorio y siempre visible al usuario:** los precios no son fijos ni garantizados — Tacha no está asociado a ningún supermercado, los precios del catálogo vienen de scraping y pueden no coincidir con lo que se cobra en caja. Debe quedar claro en el dashboard y cerca de cualquier precio sugerido.
- Alimenta directamente el dashboard financiero de la [[#4.2 Lista general y dashboard financiero|sección 4.2]].

### 4.7 Web scraping — motor de datos (prioridad alta del proyecto)

- Objetivo: extraer de sitios oficiales de supermercados costarricenses (a definir cuáles son técnicamente viables de scrapear) nombre de producto, categoría, precio y supermercado.
- Este pipeline alimenta: el catálogo de productos ([[#4.5 Catálogo de productos y categorías|4.5]]) y los datos de precio usados en las sugerencias de dónde comprar ([[#4.8 Sugerencias de dónde comprar|4.8]]).
- Consideraciones a resolver como equipo antes de implementar:
  - Revisar robots.txt y términos de servicio de cada sitio antes de scrapear — documentar la decisión por cada supermercado incluido.
  - Frecuencia de actualización (scraping bajo demanda vs. programado) y dónde corre (script periódico, función serverless, etc.).
  - Los datos scrapeados deben pasar por una tabla de "staging" y un proceso de normalización/deduplicación antes de insertarse al catálogo real, para no ensuciarlo con productos duplicados o mal categorizados.
  - Es razonable que este componente sea el que más tiempo de desarrollo tome del equipo — vale la pena asignarlo a quien tenga más experiencia con scraping/backend.

### 4.8 Sugerencias de dónde comprar

- A partir de los precios obtenidos por scraping, sugerir el supermercado más barato para los productos pendientes de una lista.
- Complementa el historial propio de compra: si el usuario ya tiene el hábito de comprar cierto producto en cierto lugar, se muestran ambas señales (precio de mercado vs. hábito personal).

### 4.9 Recetas y planificador semanal de comidas

- Recetas: ingredientes ligados al catálogo de productos, porciones base, botón de "Agregar receta a lista" que aplica la lógica de unificación de cantidades de la [[#4.2 Lista general y dashboard financiero|sección 4.2]].
- Planificador semanal: vista de calendario (semana actual + próxima) donde cada día tiene hasta 3 espacios (desayuno / almuerzo / cena), y cada espacio se asigna a:
  - Una receta del catálogo de recetas del household
  - Quién cocina ese día (un miembro del household)
  - Un multiplicador de porciones (si ese día son más o menos personas de lo habitual)
- "Agregar semana a la lista": botón que recorre todas las recetas planificadas de la semana y las agrega de una sola vez a la lista general (o a una lista de fecha específica), aplicando la misma unificación de cantidades — si el lunes y el miércoles ambos usan cebolla, se suman en un solo item, no se duplican.
- Vista de "qué falta": al ver el plan de la semana, cada receta muestra qué ingredientes ya están comprados/en casa vs. cuáles faltan.
- Con el plan semanal armado, la sugerencia de dónde comprar ([[#4.8 Sugerencias de dónde comprar|4.8]]) puede anticiparse a lo que se va a necesitar, no solo reaccionar a lo que ya está en la lista.

> Nota de alcance: el planificador semanal es un módulo grande — vale la pena asignarlo como módulo propio en el reparto de trabajo del equipo ([[#12. Propuesta de división de trabajo (borrador, a confirmar en equipo)|sección 12]]), separado del módulo de "recetas" simple.

### 4.9.1 Reconciliación de cantidades al combinar listas (decisión 2026-08-16)

Problema discutido en la reunión: al agregar una receta o el plan semanal completo a la lista general, las cantidades no siempre se pueden sumar de forma automática y confiable. Con unidades sueltas (ej. "3 cebollas") la suma es trivial. Con productos por volumen/peso que existen en múltiples presentaciones (ej. leche: caja de 1L, caja de 200ml, galón de 3.78L) la app **no puede decidir bien por el usuario** — si ya tiene apuntada 1 caja pequeña y la receta necesita 2 litros más el plan semanal, la decisión de comprar otra caja pequeña vs. un galón (más barato por litro) depende de matices que la app no conoce con certeza.

**Decisión del equipo: la app calcula el déficit, el usuario elige la presentación.** No se intenta adivinar ni auto-convertir a la presentación "óptima". Flujo:

1. Todo producto por volumen/peso normaliza su cantidad a una unidad base (ml, g) en el catálogo, independientemente de en qué presentación se vende — ver `product_catalog_variants` en [[#6. Modelo de datos (resumen conceptual)]].
2. Al combinar (receta → lista, semana → lista, o sublista → general), se suma en unidad base y se compara contra lo que el usuario ya tenía apuntado en esa lista para el mismo producto.
3. Se le muestra al usuario una vista de comparación, no un merge silencioso: "Ya tenías apuntado: 1 caja pequeña (1L). La receta necesita: 2L más. Elegí qué agregar" — con las presentaciones existentes del producto en el catálogo como opciones (otra caja pequeña, un galón, etc.), idealmente ordenadas por precio por unidad si hay datos de scraping disponibles ([[#4.8 Sugerencias de dónde comprar|4.8]]).
4. Cuando la cantidad no cae exacta en una presentación empacada (ej. necesita 2.5 unidades de un paquete), la sugerencia redondea hacia arriba a la presentación completa más cercana — nunca hacia abajo, para no dejar al usuario corto.
5. La reconciliación se reutiliza para el mismo tipo de combinación de la [[#4.3 Sublistas por fecha (con calendario)|sección 4.3]] (fusión de sublista con la general), no solo para recetas.

Esto convierte un problema de cálculo que "no siempre puede salir bien" en una decisión asistida: la app hace el trabajo aritmético, la persona decide el matiz de compra.

### 4.10 Inventario doméstico

**Decisión 2026-08-16: se incluye en v1 como función opcional, nunca obligatoria.** Se identificó como idea valiosa pero con un problema de UX real: pedirle al usuario que registre manualmente fechas de vencimiento o cantidades exactas de cada producto en casa es tedioso y probablemente no se usaría de forma consistente — el equipo no quiere que el usuario sienta que tiene que mantenerlo al día para que el resto de la app funcione. Se dan las herramientas, pero ninguna otra funcionalidad (listas, recetas, finanzas) depende de que el inventario esté completo o actualizado.

Enfoque recomendado para reducir la fricción (a validar con el equipo, especialmente con quien lidera este módulo — ver [[#12. Propuesta de división de trabajo (borrador, a confirmar en equipo)|sección 12]]): **combinar los dos enfoques ligeros en vez de elegir uno solo.**

- **Inferencia pasiva como motor:** a partir del historial de compras + una "vida útil típica" por categoría (lácteos ~1 semana, enlatados ~meses, etc.), la app estima en silencio qué probablemente ya se acabó — sin pedir fechas de vencimiento reales ni cantidades exactas.
- **Registro binario ligero como única interacción del usuario:** esa inferencia se expone como una sugerencia de un toque ("¿Se te acabó la leche?") sobre productos ya comprados antes, en vez de una pantalla de inventario separada que hay que mantener. Un toque confirma (se agrega a la lista) o descarta (se pospone la estimación); nunca hay que ingresar cantidad ni fecha a mano.
- Esto evita construir dos features (inventario "de verdad" + sugerencias pasivas) cuando una sola, bien diseñada, cubre el caso de uso sin pedirle disciplina de registro al usuario.
- Descartarlo del todo sigue siendo una opción de respaldo si el enfoque combinado no alcanza a diseñarse/construirse bien en el tiempo del curso — pero la decisión actual del equipo es incluirlo, no dejarlo pendiente.

## 5. Requerimientos no funcionales

- Colaboración en tiempo real: los cambios hechos por un miembro (agregar, tachar, editar) deben reflejarse en los dispositivos de los demás sin refrescar manualmente.
- Responsive real: la misma aplicación debe verse y funcionar bien en desktop y en móvil — un diseño adaptado con los mismos componentes reorganizados, no una versión "recortada".
- PWA instalable: manifest + service worker, para que el usuario pueda instalar la app desde el navegador sin pasar por una tienda de apps.
- Separación clara entre datos de household y datos de listas privadas a nivel de permisos — un fallo aquí sería un problema serio de privacidad.
- Escalabilidad del modelo de datos, sin requerir migraciones destructivas para las features del roadmap futuro.

## 6. Modelo de datos (resumen conceptual)

> Nota de control de acceso: la lógica de "¿puede este usuario ver/editar esta lista?" no es solo pertenencia a un household — se vuelve una función general que revisa, según el caso: `owner_id` (dueño directo, incluye el caso de usuario sin household), membresía de household (si `lists.household_id` no es nulo), o membresía en `list_collaborators` (listas privadas). Con la decisión 2026-08-16 de permitir uso sin household, `owner_id` deja de ser exclusivo de listas privadas y pasa a estar siempre presente en `lists`.

| Entidad | Descripción |
|---|---|
| `households` | Hogar/familia, contenedor raíz |
| `household_members` | Perfiles con rol (admin/miembro) dentro de un household |
| `categories` | Categorías de productos, globales |
| `product_catalog` | Producto "base" con nombre, marca y categoría; `household_id` nullable (NULL = catálogo global, con valor = producto propio) |
| `product_catalog_variants` | **Nueva (2026-08-16):** presentación/tamaño concreto de un producto (ej. "leche entera — caja 1L", "leche entera — galón"), con `base_unit` (ml/g/unidad) y `base_quantity` normalizada — es lo que se busca y muestra estilo catálogo con imagen (ver [[#4.5 Catálogo de productos y categorías|4.5]]), y lo que hace posible la reconciliación de cantidades de la [[#4.9.1 Reconciliación de cantidades al combinar listas (decisión 2026-08-16)|sección 4.9.1]] |
| `product_catalog_staging` | Datos crudos obtenidos por scraping (incluye URL de imagen), antes de normalizar/deduplicar hacia `product_catalog` / `product_catalog_variants` |
| `product_prices` | Precio de una variante de producto en un supermercado en una fecha dada, obtenido por scraping — alimenta las sugerencias de dónde comprar y el ordenamiento por precio-por-unidad de la reconciliación |
| `stores` | Catálogo de supermercados por household |
| `lists` | Lista general, sublista por fecha, o lista privada (`type`: general / date / private); `status`: active / completed / cancelled; `owner_id` siempre presente (dueño individual); `household_id` **nullable** — NULL cuando el usuario no pertenece a household o la lista es privada, con valor solo para listas `general`/`date` de un usuario en un household (decisión 2026-08-16, ver [[#4.1 Gestión de usuarios, familias y perfiles|4.1]] y [[#4.2 Lista general y dashboard financiero|4.2]]) |
| `list_items` | Item dentro de una lista, referenciando una `product_catalog_variants`, con `quantity_requested`, `quantity_bought`, estado, quién compró, dónde y cuándo |
| `list_collaborators` | Control de acceso a listas privadas — independiente de `household_members`. Columnas: `list_id`, `user_id` (o email de invitado), `invited_at`, `accepted_at` |
| `purchase_sessions` | Agrupa compras por household + supermercado + día, con total editable |
| `recipes` | Receta con porciones base |
| `recipe_ingredients` | Ingrediente de una receta, ligado al catálogo de productos |
| `meal_plans` | Planificador semanal: `household_id`, `date`, `meal_type` (desayuno/almuerzo/cena), `recipe_id`, `assigned_cook` (FK a `household_members`), `servings_multiplier`. Tabla propia, no anotación sobre `lists`, porque un día puede tener hasta 3 comidas independientes. |

Reglas de negocio que deben vivir en la base de datos (funciones/triggers), no en el cliente:

- Merge automático de cantidades solo cuando el producto duplicado en una lista es exactamente la misma variante (mismo `product_catalog_variants.id`) — no hay merge automático entre variantes distintas del mismo producto base, eso pasa por la reconciliación asistida de la [[#4.9.1 Reconciliación de cantidades al combinar listas (decisión 2026-08-16)|sección 4.9.1]].
- Auto-completado de sublista/lista privada cuando todos sus items están comprados.
- Asignación/reutilización de sesión de compra activa por household + store + día.
- Normalización/deduplicación de productos scrapeados antes de pasar de staging al catálogo real (incluye asignar cada fila de staging a un `product_catalog` + `product_catalog_variants` correspondiente).

## 7. Arquitectura técnica propuesta

| Capa | Elección | Justificación |
|---|---|---|
| Frontend | React + Next.js — **confirmado por todo el equipo el 2026-08-16** (propuesto inicialmente por Marcos para destrabar la creación del repo) | Next.js aporta SSR/routing robusto y suele ser lo esperado en cursos de desarrollo web. |
| Responsive/PWA | CSS responsive (Flexbox/Grid) + `manifest.json` + service worker (Workbox o plugin nativo del framework elegido) | Requerimiento no funcional central |
| Backend / API | Supabase (Postgres) vía PostgREST + funciones RPC — **confirmado por todo el equipo el 2026-08-16** | Complejidad justa para el modelo de datos; RLS para separar datos por household y por lista privada |
| Tiempo real | Supabase Realtime | Necesario para el tachado colaborativo instantáneo |
| Estado remoto en cliente | TanStack Query | Cache, invalidación y optimistic updates |
| Auth | Supabase Auth | — |
| Estilos | Tailwind CSS — **confirmado por todo el equipo el 2026-08-16** | Curva de aprendizaje más pareja para un equipo de 6 con niveles distintos de experiencia; más estándar y documentado que alternativas pensadas para compatibilidad nativa, que aquí no se necesita al ser 100% web |
| Web scraping | Node.js (Puppeteer/Playwright) o Python (BeautifulSoup/Scrapy) — pendiente de decisión del equipo, según quién lo implemente | Es el componente de mayor riesgo técnico del proyecto, vale la pena decidirlo temprano |

> Nota de decisión explícita: se descartó GraphQL (Hasura o pg_graphql) como capa de API. El modelo de datos es jerárquico y no tiene el problema de over/under-fetching que GraphQL resuelve; PostgREST + RPC de Postgres cubre la necesidad con menor complejidad operativa.

## 8. Referencias de producto (research de mercado)

Apps de lista de compras analizadas como referencia de patrones de UX (no de identidad visual, que es propia del equipo):

- **AnyList:** resuelve bien el catálogo con autocompletado y agrupación automática por categoría/pasillo.
- **Bring!:** identidad visual fuerte con ilustraciones planas y colores vivos diferenciados por categoría.
- **OurGroceries:** checkboxes grandes y táctiles, separación visual clara entre pendiente y comprado sin ocultar lo tachado.

**Conclusión de research:** la sincronización en tiempo real y la organización por categoría son, según fuentes de mercado, los factores que más determinan si un grupo confía o abandona este tipo de apps.

## 9. Dirección de diseño (UI/UX)

**Personalidad:** cálida y hogareña, evocando apps de cocina/familia — sin caer en lo infantil ni en el look genérico de fintech. Identidad visual construida desde cero para este proyecto.

**Tipografía:**
- Títulos: Fraunces (serif cálida, variable font).
- Cuerpo de texto: Public Sans.

**Paleta — Modo claro:**

| Uso | Color | Hex |
|---|---|---|
| Fondo base | Crema cálido | `#FBF6EE` |
| Superficie / cards | Blanco con borde sutil | `#FFFFFF` / borde `#E8DFD0` |
| Acento principal | Teal profundo | `#0E7C7B` |
| Acento secundario | Terracota | `#D97B4F` |
| Texto principal | Marrón casi negro | `#2B2420` |
| Texto secundario | Marrón grisáceo | `#8A7F70` |

**Paleta — Modo oscuro:**

| Uso | Color | Hex |
|---|---|---|
| Fondo base | Marrón muy oscuro (no negro puro) | `#1C1815` |
| Superficie / cards | — | `#26211C` |
| Acento principal | Teal claro/vibrante | `#3EC6C1` |
| Acento secundario | Terracota claro | `#E89A6C` |
| Texto principal | Crema claro | `#F5EFE6` |
| Texto secundario | — | `#B5A997` |

**Principios de UI aplicados:**
- Un solo color de acento saturado (teal) para acciones y estados activos; el terracota se reserva para etiquetas contextuales, nunca compite con el acento principal.
- Ambos modos (claro/oscuro) reciben el mismo nivel de cuidado.
- Checkboxes cuadrados redondeados (no circulares).
- Iconografía consistente estilo outline — sin emojis.
- Micro-interacciones intencionales: animación de check al marcar un item, animación de tachado progresivo.
- Espacio negativo generoso y agrupación clara por categoría.

**Adaptaciones responsive:**
- Desktop: navegación lateral fija (sidebar) con las secciones principales (General, Fechas, Listas privadas, Finanzas, Recetas, Historial).
- Mobile web: tabs inferiores, más usable en pantallas angostas que un sidebar.
- El dashboard financiero y el planificador semanal tienen su propio diseño de pantalla con gráficos y grillas, adaptado a cada tamaño (ver [[Proyectos/Tacha/mockups/mockup-web-v2.html|mockup]]).

**Mockups de referencia:** prototipo interactivo (HTML) cubriendo vistas desktop y mobile web de: lista general con dashboard, finanzas completas, listas privadas con calendario y estados, y planificador semanal de comidas. Ver [[Proyectos/Tacha/mockups/mockup-web-v2.html|mockups/mockup-web-v2.html]] — v2, todavía por mejorar según el propio equipo.

## 10. Pendientes de definición

- ~~Framework de React definitivo (Next.js vs. Vite)~~ — **Next.js**, confirmado por todo el equipo en la reunión 2026-08-16.
- ~~Librería de estilos definitiva~~ — **Tailwind CSS**, confirmado el 2026-08-16.
- ~~Base de datos~~ — **Supabase**, confirmado por todo el equipo el 2026-08-16.
- ~~Enfoque del inventario doméstico~~ — **incluido en v1, opcional** (sección 4.10), decidido el 2026-08-16; el diseño de detalle del enfoque combinado propuesto sigue abierto.
- **Confirmación del profesor** sobre stack + DB — el equipo ya decidió, falta la aprobación formal del curso antes de tratarlo como cerrado.
- Herramienta de web scraping (Node/Puppeteer vs. Python) y quién del equipo lo lidera — Daniel lidera el módulo (sección 12), falta la decisión técnica puntual.
- Qué supermercados costarricenses son técnicamente viables de scrapear (revisar robots.txt de cada uno), y si esos sitios exponen imagen de producto de forma consistente (nuevo requisito del catálogo, sección 4.5) — riesgo a validar temprano con Daniel.
- Qué pasa con las listas personales de un usuario que se une a un household después de haber usado la app solo (sección 4.1) — ¿se ofrecen para asociar, o quedan separadas siempre?
- Nombre/ícono de la app — se propone mantener "Tacha" salvo que el equipo completo prefiera cambiarlo.

## 11. Próximos pasos inmediatos

- Confirmación del profesor sobre stack y base de datos (sección 7)
- Generación de interfaz de alta fidelidad con Stitch AI a partir de [[Proyectos/Tacha/DESIGN|DESIGN.md]], sobre los requerimientos ya cerrados en este documento
- Diseñar el schema SQL completo (tablas + RLS + funciones de negocio), incorporando `product_catalog_variants` y `lists.household_id` nullable (sección 6)
- Cerrar el resto de la [[#10. Pendientes de definición|sección 10]] (scraping técnico, supermercados viables, listas solo → household)
- Corregir el mockup (`mockups/mockup-web-v2.html`) y la nueva generación de Stitch contra los requerimientos cerrados en este documento

## 12. División de trabajo

Definida en la reunión de equipo del 2026-08-16 — reemplaza el borrador anterior.

| Integrante | Módulo | Alcance |
|---|---|---|
| Daniel | Web scraping + catálogo | Terminar el pipeline de scraping y el catálogo (productos, variantes, imágenes) — el módulo de mayor riesgo técnico |
| Melany | Diseño UI + inventario | Sistema de componentes/diseño visual e implementación del inventario doméstico opcional (sección 4.10) |
| Laura | Dashboard financiero | Gráficos y agregaciones de gasto (sección 4.2, 4.6) |
| Esteban | Auth, households, perfiles | Login, creación/invitación de miembros, roles (sección 4.1) |
| Roberto | Recetas y planificador semanal | Recetas, calendario de comidas, conexión con listas (sección 4.9) |
| Marcos | Listas y PWA | Lista general, sublistas, listas privadas, tachado, PWA/responsive (secciones 4.2–4.4) |
