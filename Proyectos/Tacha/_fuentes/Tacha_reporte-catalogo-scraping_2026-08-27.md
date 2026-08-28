---
módulo: Web scraping + catálogo
responsable: Daniel
fuente: documentacion-v1_for claude.md (v2.1, estado confirmado por el equipo 2026-08-16/2026-08-18) + Tacha_historias-usuario-v2.2.docx (autoridad final en caso de conflicto)
fecha: 2026-08-27
estado: Propuesta de rediseño — pendiente de implementar en Supabase
---

# Rediseño del catálogo y el scraping — alineación con el documento v2.1

## 1. Objetivo de este reporte

El schema y las Edge Functions que existen hoy (en Supabase y en este repo) fueron diseñados antes de tener el documento v2.1 y las historias de usuario completas. Ese trabajo anterior queda obsoleto y no se documenta acá — no aporta trazabilidad hacia adelante.

Este reporte describe **lo que se va a construir de ahora en adelante**: el modelo de datos y la arquitectura de scraping, usando exactamente los nombres de tabla y las decisiones de la sección 6 y 4.5–4.8 del documento del equipo, salvo en los puntos donde detecto un problema real de rendimiento o de correctitud técnica. Esos puntos quedan marcados aparte, con justificación, para que el equipo los revise y decida si actualizan el documento oficial.

## 2. Alcance

Este documento cubre únicamente las tablas y componentes del módulo de **web scraping + catálogo** (asignado a Daniel, sección 12 del documento). No toca `households`, `lists`, `list_items`, `recipes`, `meal_plans`, `purchase_sessions`, autenticación, ni ningún otro módulo — esas tablas se mencionan solo como referencias externas (FKs) cuando el catálogo las necesita.

## 3. Tablas que se implementan tal cual las define el documento

Estas tablas se crean con el mismo nombre y el mismo propósito conceptual que la sección 6 del documento. Se listan con su estructura propuesta a nivel de columnas — el detalle exacto de tipos se resuelve en el `schema.sql` cuando se implemente.

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

Vive como detalle de la variante, no como variante propia — es la corrección del 2026-08-18 que separa marca de tamaño.

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

Cola de revisión entre el dato crudo y el catálogo real — exactamente el rol que describe 4.7 ("los datos scrapeados deben pasar por una tabla de staging... antes de insertarse al catálogo real").

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
- `household_id` (nullable, según 6)

Ver sección 5.3 más abajo — esta es una de las tablas donde encontré un problema real que requiere validación del equipo antes de implementarla como está descrita.

## 4. Tablas de soporte técnico (no están en el documento, pero no son parte del modelo de negocio)

Estas dos tablas existían en el diseño anterior y se mantienen porque resuelven un problema puramente de infraestructura (evitar golpear VTEX en cada búsqueda), no un concepto de negocio — el documento no las necesita mencionar porque son un detalle de implementación del pipeline de scraping, no del catálogo que ve el usuario.

- **`search_cache`** (`store`, `normalized_query`, `staging_ids[]`, `cached_at`) — cache-first con TTL para no repetir la misma búsqueda contra VTEX dentro de una ventana de 6 horas.
- **`search_log`** (`store`, `query`, `source`, `result_count`, `searched_at`) — auditoría de qué se buscó y si vino de cache o en vivo.

Ambas quedan bloqueadas por RLS sin políticas (solo `service_role`/Edge Functions las tocan), igual que en el diseño anterior — eso sí es una decisión de seguridad correcta y se mantiene.

## 5. Desviaciones respecto al documento — con justificación técnica

Todo lo de esta sección es **una propuesta de cambio al documento**, no una decisión unilateral tomada. Se marca así para que el equipo la revise en la próxima iteración de `documentacion-v1_for claude.md`.

### 5.1 `product_catalog_staging` normalizado en 3 tablas (`raw_json` + campos de match), no una tabla plana

**Lo que dice el documento:** "Datos crudos obtenidos por scraping (marca + tamaño + súper + URL de imagen)... antes de normalizar/deduplicar hacia `product_catalog` / `product_catalog_variants` / `product_brands`."

**Lo que se propone:** exactamente eso, pero agregando explícitamente las columnas `status` y `matched_variant_id`/`matched_brand_id` como parte del staging, en vez de dejarlas implícitas.

**Justificación:** sin un campo de estado explícito, no hay forma barata de que el proceso de normalización sepa qué filas de staging ya se revisaron y cuáles siguen pendientes — obligaría a hacer un `LEFT JOIN` contra `product_catalog_variants` para inferirlo cada vez, en vez de un filtro directo `where status = 'pending'`. Esto no es un cambio de modelo, es completar el detalle de implementación que el documento deja abierto a propósito ("antes de insertarse... " sin especificar cómo se rastrea el progreso).

### 5.2 Índice de búsqueda difusa (`pg_trgm`) sobre `product_catalog.name`

**Lo que dice el documento:** no menciona mecanismo de búsqueda a nivel de base de datos.

**Lo que se propone:** extensión `pg_trgm` de Postgres + índice GIN sobre `product_catalog.name`, para tolerar errores de tipeo del usuario en la barra de búsqueda (HU-51, 4.2.1: "resultados en tiempo real").

**Justificación técnica:** sin este índice, una búsqueda por texto en una tabla que va a crecer (cientos o miles de productos madre entre 3 súpers) termina en un `seq scan` con `ILIKE`, que no escala y no tolera errores de tipeo. Es una decisión de rendimiento pura, no cambia ningún campo ni relación del modelo — es agregar un índice, no una tabla nueva.

### 5.3 `stores` — se propone dejarla fija a 3 filas sembradas (seed), no una tabla libremente editable por household

**Lo que dice el documento (sección 6):** "`stores` — Catálogo de supermercados por household."

**Problema detectado:** el pipeline de scraping de este módulo apunta específicamente a tres cadenas (MaxiPali, Walmart CR, MasXMenos), todas sobre la misma plataforma VTEX, con URLs y lógica de scraping fijas por cadena. Si `stores` es una tabla que cada household puede poblar libremente, no queda claro qué pasa si un household agrega una tienda que el scraper no soporta — quedaría una fila de `stores` sin ningún dato de `product_prices` real detrás, o el sistema tendría que rechazar altas arbitrarias con una validación que el documento no describe.

**Lo que se propone:** `stores` existe como tabla (no un simple CHECK constraint, para no perder la flexibilidad de mostrar nombre/logo por tienda), pero se siembra con exactamente 3 filas fijas (maxipali, walmart, masxmenos) y no se expone ninguna función para que un household inserte una fila nueva — al menos hasta que el pipeline de scraping soporte una tienda adicional.

**Para el equipo:** esto necesita una respuesta explícita — ¿la intención real de "por household" en la sección 6 era que cada household pueda elegir cuáles de las 3 tiendas soportadas seguir/mostrar (ej. un household que nunca compra en Walmart puede ocultarla), o era literalmente que el household defina tiendas propias arbitrarias? Si es lo primero, el modelo correcto es una tabla puente `household_store_preferences` (household_id, store_id, visible boolean) y `stores` se mantiene como catálogo fijo de 3 — eso sí es compatible 1:1 con lo construido acá. Si es lo segundo, ese alcance queda fuera de este módulo tal como está definido hoy, porque el scraper no puede generar datos para una tienda arbitraria.

### 5.4 Ingesta vía Edge Functions (Deno), no directamente vía PostgREST + RPC

**Lo que dice el documento (sección 7):** "Backend / API: Supabase (Postgres) vía PostgREST + funciones RPC — confirmado por todo el equipo."

**Lo que se propone:** las 3 funciones de ingesta (una por tienda) siguen siendo Edge Functions de Deno que llaman a la API pública de VTEX y escriben en `product_catalog_staging`/`product_prices`. El resto de la app (frontend leyendo el catálogo ya normalizado) sí consume todo vía PostgREST + RPC, sin ninguna Edge Function de por medio.

**Justificación técnica:** "PostgREST + RPC" describe cómo el frontend le habla a la base de datos para operaciones CRUD sobre datos que ya viven en Postgres — no es un mecanismo diseñado para hacer llamadas HTTP salientes a un servicio de terceros (VTEX). Postgres puede hacer eso mediante extensiones como `pg_net`/`http`, pero son más frágiles para este caso: no manejan bien reintentos, timeouts largos, ni parseo de un JSON externo con la forma de VTEX (que además cambia de estructura por categoría de producto). Una Edge Function con un runtime de JavaScript normal resuelve esto de forma mucho más simple y es, de hecho, el mecanismo que la propia documentación de Supabase recomienda para integrar APIs externas. Esta no es una desviación del backend general del proyecto — es una elección de implementación acotada a la única pieza que necesita hablar con un servicio externo (VTEX), y todo lo demás sigue el patrón confirmado.

**Para el equipo:** vale la pena dejar esto explícito por escrito en la sección 7, agregando una línea del tipo "Edge Functions se usan exclusivamente para la ingesta de scraping (llamadas HTTP salientes a VTEX); todo lo demás pasa por PostgREST + RPC" — para que no quede ambiguo para el resto del equipo si alguien revisa el código y ve una carpeta `supabase/functions/`.

### 5.5 Normalización de staging → catálogo como función/proceso explícito, ejecutado por un cron/Edge Function, no como trigger de base de datos

**Lo que dice el documento (sección 6, "Reglas de negocio"):** "deben vivir en la base de datos (funciones/triggers), no en el cliente... Normalización/deduplicación de productos scrapeados antes de pasar de staging al catálogo real."

**Lo que se propone:** la decisión de si una fila de staging hace match con una variante/marca existente (usando `pg_trgm` `similarity()` + coincidencia de categoría y tamaño) se resuelve en una función SQL (`sql`/`plpgsql`, vive en Postgres, invocable por RPC) — eso sí respeta la sección 6 al pie de la letra. Lo que se propone ejecutar *fuera* de un trigger automático es el disparo de esa función: en vez de que insertar una fila en `product_catalog_staging` dispare el intento de match automáticamente, se ejecuta como un paso separado (llamado por la misma Edge Function de ingesta, inmediatamente después de insertar el staging, o por un job programado).

**Justificación técnica:** un trigger `AFTER INSERT` que ejecuta `similarity()` contra toda la tabla de variantes en medio de la transacción de inserción hace más lento cada insert de scraping (que ya inserta en lote, potencialmente cientos de filas por búsqueda) y complica el manejo de errores — si el matching falla, no debería hacer rollback de la inserción del dato crudo. Separar "guardar lo crudo" de "intentar hacer match" en dos pasos (segundo paso invocado explícitamente, no automático) es más seguro y no cambia el resultado final ni el modelo de datos — la función de matching sigue viviendo en la base de datos, tal como pide el documento, solo que no se dispara vía trigger.

## 6. Tabla resumen de desviaciones (para revisión rápida del equipo)

| Punto | Documento dice | Se propone | Motivo |
|---|---|---|---|
| Staging | Tabla de datos crudos, sin detalle de columnas | Agregar `status` + FKs de match explícitas | Sin esto no hay forma barata de saber qué falta revisar |
| Búsqueda | No especifica mecanismo | Índice `pg_trgm` sobre `product_catalog.name` | Tolerar errores de tipeo sin `seq scan` |
| `stores` | "por household", sin más detalle | Fija a 3 filas sembradas + posible tabla puente de preferencias | El scraper solo cubre 3 cadenas; alta arbitraria no tiene datos detrás |
| Ingesta | Todo vía PostgREST + RPC | Edge Functions solo para llamadas HTTP salientes a VTEX | RPC/PostgREST no está pensado para llamar APIs externas |
| Matching staging→catálogo | Función/trigger en la base de datos | Función en la base de datos, invocada explícitamente (no por trigger automático) | Evitar que el matching bloquee o falle la inserción del dato crudo |

## 7. Próximo paso propuesto

1. El equipo revisa la sección 5 de este reporte, en particular 5.3 (`stores`) que necesita una respuesta concreta antes de fijar el schema.
2. Con eso resuelto, se implementa el `schema.sql` nuevo (reemplazando por completo el actual) con las tablas de la sección 3 y 4, RLS incluida.
3. Se reescriben las Edge Functions de ingesta para escribir en `product_catalog_staging` en vez de directamente en un catálogo final.
4. Se construye la función de matching (staging → `product_catalog_variants`/`product_brands`) como paso siguiente, separado de este reporte.

## 8. Diagrama del modelo — DBML para dbdiagram.io

Pegar el siguiente bloque directamente en [dbdiagram.io](https://dbdiagram.io) (botón "Import" o simplemente reemplazar el contenido del editor). Cubre únicamente las tablas de este módulo (catálogo + scraping); `categories`, `households` y `stores` aparecen como tablas de referencia externas mínimas para que las relaciones se vean completas, pero su definición real vive en otros módulos.

```dbml
// Tacha — Módulo de catálogo + web scraping
// Alineado a documentacion-v1_for claude.md v2.1, sección 6
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
  name text [not null, note: 'maxipali | walmart | masxmenos — 3 filas fijas sembradas, ver sección 5.3 del reporte']
  household_id uuid [ref: > households.id, note: 'nullable — ver sección 5.3, pendiente de confirmar alcance real con el equipo']
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
- `stores` usa un `id` uuid en vez del `store: text check(...)` que se usaba en el diseño anterior — esto es necesario para que `household_id` (sección 5.3) tenga sentido como tabla real en vez de un enum fijo; si el equipo confirma que `stores` debe ser fija a 3 filas sin variación por household, se simplifica de vuelta a un `check` constraint y se elimina esa FK.
- `product_catalog_staging.matched_variant_id`/`matched_brand_id` son nullable — quedan vacíos mientras `status = 'pending'`.
