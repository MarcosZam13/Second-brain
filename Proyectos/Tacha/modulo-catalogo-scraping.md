---
proyecto: Tacha
tema: Módulo de catálogo + web scraping — rediseño (Daniel)
fecha: 2026-08-27
tipo: documentacion
responsable: Daniel
estado: "DESACTUALIZADO (2026-08-27, avisado por Daniel) — este reporte no es la versión final, Daniel va a mandar una versión final verificada. La resolución de 5.3 (stores fijo + household_store_preferences) se mantiene como decisión del equipo, pero el resto del contenido de esta nota debe reemplazarse cuando llegue esa versión final — no tratar como fuente de verdad hasta entonces"
fuente: _fuentes/Tacha_reporte-catalogo-scraping_2026-08-27.md
tags: [documentacion, modelo-datos, scraping, catalogo, supabase, tacha]
---

# Módulo de catálogo + web scraping — rediseño (Daniel)

Ver también: [[Proyectos/Tacha/README|README]] · [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] · [[Proyectos/Tacha/historias-usuario|historias-usuario.md]]

> **⚠️ DESACTUALIZADO (2026-08-27):** Daniel avisó que el `.md` que generó este reporte estaba desactualizado y va a mandar una versión final verificada. Cuando llegue, reemplazar el contenido de esta nota (secciones 1-5, 7-8) con la versión final — no usar como referencia de implementación hasta entonces. La **resolución de la sección 6 (stores fijo + `household_store_preferences`)** sí se mantiene como decisión de equipo ya cerrada, independiente de qué tan desactualizado esté el resto del reporte técnico.

Reporte de Daniel (responsable del módulo de web scraping + catálogo, sección 12 de `documentacion-v1.md`), recibido 2026-08-27. Cubre únicamente las tablas y componentes de ese módulo — no toca `households`, `lists`, `list_items`, `recipes`, `meal_plans`, `purchase_sessions` ni autenticación; esas tablas aparecen solo como referencias externas (FKs).

## 1. Objetivo

El schema y las Edge Functions que existían antes en Supabase/el repo se diseñaron antes de tener el documento v2.1 completo y las historias de usuario. Ese trabajo queda obsoleto y no se documenta acá. Este reporte describe lo que se construye de ahora en adelante, usando los nombres de tabla y decisiones de las secciones 6 y 4.5–4.8 de `documentacion-v1.md`, salvo en los puntos donde Daniel detectó un problema real de rendimiento/correctitud — esos quedan marcados aparte con justificación.

## 2. Tablas que se implementan tal cual las define el documento

### `categories`
Categorías de producto, globales. Referenciada por `product_catalog`.

### `product_catalog` — "producto madre"
- `id` (uuid, PK)
- `name` (ej. "Leche")
- `category_id` (FK → `categories`)
- `household_id` (uuid, nullable — NULL = catálogo global, con valor = producto propio de un household)
- `source` (`scraped` | `manual`)
- `created_at`

No incluye marca en su identidad, tal como corrige el documento en 4.5 ("Corrección 2026-08-18").

### `product_catalog_variants` — presentación/tamaño
- `id` (uuid, PK)
- `product_catalog_id` (FK → `product_catalog`)
- `name` (ej. "Leche — caja 1L")
- `base_unit` (`ml` | `g` | `unidad`)
- `base_quantity` (numeric — cantidad normalizada, ej. 1000 para "caja 1L")
- `image_url`
- `created_at`

Es la entidad que se busca y se muestra estilo catálogo (HU-51), y la que participa en la reconciliación de cantidades (4.9.1).

### `product_brands`
- `id` (uuid, PK)
- `product_catalog_variant_id` (FK → `product_catalog_variants`)
- `name` (ej. "Dos Pinos")
- `logo_url`
- `created_at`

Vive como detalle de la variante, no como variante propia — corrección del 2026-08-18 que separa marca de tamaño.

### `product_catalog_staging`
- `id` (uuid, PK)
- `store` (`maxipali` | `walmart` | `masxmenos`)
- `raw_json` (jsonb — payload crudo tal como lo devuelve VTEX)
- `scraped_name`, `scraped_brand`, `scraped_size_text` (texto crudo, previo a normalizar)
- `image_url`
- `status` (`pending` | `matched` | `rejected`)
- `matched_variant_id` (FK nullable → `product_catalog_variants`, se llena cuando el proceso de normalización asigna la fila)
- `matched_brand_id` (FK nullable → `product_brands`)
- `scraped_at`

Cola de revisión entre el dato crudo y el catálogo real — el rol que describe 4.7 ("los datos scrapeados deben pasar por una tabla de staging... antes de insertarse al catálogo real").

### `product_prices`
- `id` (bigserial, PK)
- `product_catalog_variant_id` (FK → `product_catalog_variants`)
- `product_brand_id` (FK → `product_brands`)
- `store` (`maxipali` | `walmart` | `masxmenos`)
- `price`, `list_price`
- `is_available`
- `source` (`scraped` | `manual`)
- `captured_at`

Precio granular por variante+marca+súper+fecha, tal como especifica 4.5 y 4.8: "el scraping sigue siendo granular por marca, el catálogo solo agrega esa granularidad para mostrar un rango".

### `stores`
- `id` (uuid, PK)
- `name`

Ver sección 5.3 — resuelta 2026-08-27 (sección 6 de esta nota): tabla fija de 3 filas sembradas, sin `household_id`.

## 3. Tablas de soporte técnico (no están en el documento — detalle de implementación)

Existían en el diseño anterior y se mantienen porque resuelven un problema puramente de infraestructura (evitar golpear VTEX en cada búsqueda), no un concepto de negocio:

- **`search_cache`** (`store`, `normalized_query`, `staging_ids[]`, `cached_at`) — cache-first con TTL para no repetir la misma búsqueda contra VTEX dentro de una ventana de 6 horas.
- **`search_log`** (`store`, `query`, `source`, `result_count`, `searched_at`) — auditoría de qué se buscó y si vino de cache o en vivo.

Ambas quedan bloqueadas por RLS sin políticas (solo `service_role`/Edge Functions las tocan) — decisión de seguridad que se mantiene del diseño anterior.

## 4. Desviaciones respecto al documento — con justificación técnica

Propuestas de cambio a `documentacion-v1.md`, no decisiones unilaterales — para que el equipo las revise en la próxima iteración.

### 4.1 `product_catalog_staging` con `status` + FKs de match explícitas

**Documento dice:** "Datos crudos obtenidos por scraping... antes de normalizar/deduplicar hacia `product_catalog` / `product_catalog_variants` / `product_brands`."

**Se propone:** agregar explícitamente `status` y `matched_variant_id`/`matched_brand_id` como columnas de staging, en vez de dejarlas implícitas.

**Justificación:** sin un campo de estado explícito, el proceso de normalización necesitaría un `LEFT JOIN` contra `product_catalog_variants` para inferir qué filas ya se revisaron, en vez de un filtro directo `where status = 'pending'`. No es un cambio de modelo, completa un detalle que el documento deja abierto a propósito.

### 4.2 Índice de búsqueda difusa (`pg_trgm`) sobre `product_catalog.name`

**Documento dice:** no menciona mecanismo de búsqueda a nivel de base de datos.

**Se propone:** extensión `pg_trgm` + índice GIN sobre `product_catalog.name`, para tolerar errores de tipeo (HU-51, 4.2.1: "resultados en tiempo real").

**Justificación:** sin este índice, una búsqueda por texto en una tabla que va a crecer (cientos/miles de productos entre 3 súpers) termina en `seq scan` con `ILIKE`, que no escala ni tolera errores de tipeo. Es una decisión de rendimiento pura — no cambia campos ni relaciones.

### 4.3 `stores` — resuelto, ver sección 6 de esta nota

### 4.4 Ingesta vía Edge Functions (Deno), no directamente vía PostgREST + RPC

**Documento dice (sección 7):** "Backend / API: Supabase (Postgres) vía PostgREST + funciones RPC — confirmado por todo el equipo."

**Se propone:** las 3 funciones de ingesta (una por tienda) siguen siendo Edge Functions de Deno que llaman a la API pública de VTEX y escriben en `product_catalog_staging`/`product_prices`. El resto de la app (frontend leyendo el catálogo ya normalizado) consume todo vía PostgREST + RPC, sin Edge Function de por medio.

**Justificación:** "PostgREST + RPC" describe cómo el frontend habla con la base de datos para CRUD sobre datos que ya viven en Postgres — no está pensado para llamadas HTTP salientes a un servicio de terceros (VTEX). Postgres puede hacerlo vía `pg_net`/`http`, pero son más frágiles para reintentos, timeouts largos y parseo de un JSON externo que cambia de estructura por categoría. Una Edge Function con runtime JS normal resuelve esto más simple, y es el mecanismo que la propia documentación de Supabase recomienda para integrar APIs externas. No es una desviación del backend general — es una elección acotada a la única pieza que habla con un servicio externo.

**Para el equipo:** dejar explícito en la sección 7 algo como "Edge Functions se usan exclusivamente para la ingesta de scraping (llamadas HTTP salientes a VTEX); todo lo demás pasa por PostgREST + RPC".

### 4.5 Normalización staging → catálogo como función invocada explícitamente, no trigger automático

**Documento dice (sección 6, "Reglas de negocio"):** "deben vivir en la base de datos (funciones/triggers), no en el cliente... Normalización/deduplicación de productos scrapeados antes de pasar de staging al catálogo real."

**Se propone:** la decisión de si una fila de staging hace match con una variante/marca existente (`pg_trgm` `similarity()` + coincidencia de categoría y tamaño) se resuelve en una función SQL (respeta la sección 6 al pie de la letra). Lo que se ejecuta *fuera* de un trigger automático es el disparo de esa función: en vez de que insertar en `product_catalog_staging` dispare el match automáticamente, se ejecuta como paso separado (llamado por la misma Edge Function de ingesta, o por un job programado).

**Justificación:** un trigger `AFTER INSERT` que ejecuta `similarity()` contra toda la tabla de variantes en medio de la transacción de inserción hace más lento cada insert en lote (potencialmente cientos de filas por búsqueda) y complica el manejo de errores — si el matching falla, no debería hacer rollback de la inserción del dato crudo. Separar "guardar lo crudo" de "intentar hacer match" es más seguro y no cambia el resultado final ni el modelo — la función sigue viviendo en la base de datos, solo que no se dispara vía trigger.

## 5. Tabla resumen de desviaciones

| Punto | Documento dice | Se propone | Motivo |
|---|---|---|---|
| Staging | Tabla de datos crudos, sin detalle de columnas | Agregar `status` + FKs de match explícitas | Sin esto no hay forma barata de saber qué falta revisar |
| Búsqueda | No especifica mecanismo | Índice `pg_trgm` sobre `product_catalog.name` | Tolerar errores de tipeo sin `seq scan` |
| `stores` | "por household", sin más detalle | Fija a 3 filas sembradas + tabla puente de preferencias | El scraper solo cubre 3 cadenas; alta arbitraria no tiene datos detrás |
| Ingesta | Todo vía PostgREST + RPC | Edge Functions solo para llamadas HTTP salientes a VTEX | RPC/PostgREST no está pensado para llamar APIs externas |
| Matching staging→catálogo | Función/trigger en la base de datos | Función en la base de datos, invocada explícitamente (no por trigger automático) | Evitar que el matching bloquee o falle la inserción del dato crudo |

## 6. Resolución del equipo — `stores` (2026-08-27)

**Pregunta de Daniel:** ¿la intención real de "por household" en la sección 6 de `documentacion-v1.md` era que cada household pueda elegir cuáles de las 3 tiendas soportadas seguir/mostrar (ej. un household que nunca compra en Walmart puede ocultarla), o que el household defina tiendas propias arbitrarias?

**Respuesta del equipo (Marcos, 2026-08-27):** lo primero — cada household puede seleccionar cuál(es) de las 3 tiendas quiere seguir (las 3, una o varias). No está en el alcance del proyecto scrapear otras webs por ahora.

**Consecuencia para el schema:** `stores` queda como tabla fija de 3 filas sembradas (MaxiPali, Walmart CR, MasXMenos), sin `household_id`. Se agrega la tabla puente `household_store_preferences`:

- `household_id` (FK → `households`)
- `store_id` (FK → `stores`)
- `visible` (boolean)
- PK compuesta (`household_id`, `store_id`)

Aplicado ya a [[Proyectos/Tacha/documentacion-v1#6. Modelo de datos (resumen conceptual)|documentacion-v1.md, sección 6]].

## 7. Próximo paso

1. ~~El equipo revisa la sección 5.3 (`stores`)~~ — resuelto, ver sección 6 de esta nota.
2. Implementar `schema.sql` nuevo (reemplaza el actual por completo) con las tablas de las secciones 2 y 3, RLS incluida, más `household_store_preferences`.
3. Reescribir las Edge Functions de ingesta para escribir en `product_catalog_staging` en vez de directamente en un catálogo final.
4. Construir la función de matching (staging → `product_catalog_variants`/`product_brands`) como paso siguiente, separado de este reporte.

## 8. Diagrama del modelo — DBML para dbdiagram.io

Pegar directamente en [dbdiagram.io](https://dbdiagram.io) (botón "Import" o reemplazar el contenido del editor). Cubre las tablas de este módulo (catálogo + scraping) más `household_store_preferences` (resolución de 5.3); `categories`, `households` y `stores` aparecen como tablas de referencia mínimas para que las relaciones se vean completas — su definición real vive en otros módulos.

```dbml
// Tacha — Módulo de catálogo + web scraping
// Alineado a documentacion-v1.md, sección 6 — incluye resolución de 5.3 (2026-08-27)
// Tablas marcadas [ref-externa] pertenecen a otro módulo, se listan solo para las FKs

Table categories {
  id uuid [pk]
  name text [not null]

  Note: 'Ref-externa: categorías globales de producto'
}

Table households {
  id uuid [pk]
  name text

  Note: 'Ref-externa: hogar/familia, definida en el módulo de auth/households'
}

Table product_catalog {
  id uuid [pk]
  name text [not null, note: 'ej. "Leche" — producto madre, sin marca en su identidad']
  category_id uuid [ref: > categories.id]
  household_id uuid [ref: > households.id, note: 'NULL = catálogo global']
  source text [not null, note: 'scraped | manual']
  created_at timestamptz [not null, default: `now()`]
}

Table product_catalog_variants {
  id uuid [pk]
  product_catalog_id uuid [not null, ref: > product_catalog.id]
  name text [not null, note: 'ej. "Leche — caja 1L"']
  base_unit text [not null, note: 'ml | g | unidad']
  base_quantity numeric [not null, note: 'cantidad normalizada, ej. 1000']
  image_url text
  created_at timestamptz [not null, default: `now()`]
}

Table product_brands {
  id uuid [pk]
  product_catalog_variant_id uuid [not null, ref: > product_catalog_variants.id]
  name text [not null, note: 'ej. "Dos Pinos"']
  logo_url text
  created_at timestamptz [not null, default: `now()`]
}

Table stores {
  id uuid [pk]
  name text [not null, note: 'maxipali | walmart | masxmenos — 3 filas fijas sembradas']

  Note: 'Fija a 3 filas, sin household_id — resolución de 5.3 (2026-08-27)'
}

Table household_store_preferences {
  household_id uuid [not null, ref: > households.id]
  store_id uuid [not null, ref: > stores.id]
  visible boolean [not null, default: true]

  indexes {
    (household_id, store_id) [pk]
  }

  Note: 'Qué tiendas del catálogo fijo sigue/muestra cada household — resolución de 5.3 (2026-08-27)'
}

Table product_catalog_staging {
  id uuid [pk]
  store_id uuid [not null, ref: > stores.id]
  raw_json jsonb [not null, note: 'payload crudo de VTEX']
  scraped_name text
  scraped_brand text
  scraped_size_text text
  image_url text
  status text [not null, default: 'pending', note: 'pending | matched | rejected']
  matched_variant_id uuid [ref: > product_catalog_variants.id]
  matched_brand_id uuid [ref: > product_brands.id]
  scraped_at timestamptz [not null, default: `now()`]
}

Table product_prices {
  id bigint [pk, increment]
  product_catalog_variant_id uuid [not null, ref: > product_catalog_variants.id]
  product_brand_id uuid [not null, ref: > product_brands.id]
  store_id uuid [not null, ref: > stores.id]
  price numeric [not null]
  list_price numeric
  is_available boolean [not null, default: true]
  source text [not null, note: 'scraped | manual']
  captured_at timestamptz [not null, default: `now()`]

  indexes {
    (product_catalog_variant_id, store_id, captured_at) [name: 'idx_prices_variant_store_latest']
  }
}

Table search_cache {
  store_id uuid [not null, ref: > stores.id]
  normalized_query text [not null]
  staging_ids uuid[] [not null]
  cached_at timestamptz [not null, default: `now()`]

  indexes {
    (store_id, normalized_query) [pk]
  }
}

Table search_log {
  id bigint [pk, increment]
  store_id uuid [not null, ref: > stores.id]
  query text [not null]
  source text [not null, note: 'cache | live | stale-cache']
  result_count integer [not null, default: 0]
  searched_at timestamptz [not null, default: `now()`]
}
```

**Notas para leer el diagrama una vez importado:**
- Las líneas de `categories` y `households` van a aparecer con muy pocas columnas — es intencional, son solo el ancla para las FKs; sus columnas reales están definidas en otros módulos del equipo.
- `stores` usa un `id` uuid en vez de un `store: text check(...)` — sigue siendo tabla real (no enum) para no perder flexibilidad de nombre/logo por tienda, pero fija a 3 filas sembradas, sin `household_id`.
- `household_store_preferences` es la tabla puente que resuelve 5.3 — sin fila para un `(household, store)` se asume `visible = true` por defecto, o se siembra una fila por cada household×store al crear el household (decisión de implementación, no bloquea el schema).
- `product_catalog_staging.matched_variant_id`/`matched_brand_id` son nullable — quedan vacíos mientras `status = 'pending'`.
