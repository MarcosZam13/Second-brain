---
proyecto: Tacha
tema: Módulo de catálogo + web scraping — versión final (Daniel)
fecha: 2026-09-04
tipo: documentacion
responsable: Daniel
estado: "Cerrado — PR #1 'Web scraping core' (MarcosZam13/tacha, seph-25) aprobado por Marcos y mergeado a develop el 2026-09-05 (commit de merge, rama web-scraping-core eliminada). Reemplaza la nota anterior (2026-08-27), que Daniel mismo avisó que estaba desactualizada."
fuente:
  - "AI-Generated Report/reporte-catalogo-scraping.md (repo, rama web-scraping-core)"
  - "AI-Generated Report/referencia-tecnica-catalogo-scraping.md (repo, rama web-scraping-core)"
tags: [documentacion, modelo-datos, scraping, catalogo, supabase, tacha]
---

# Módulo de catálogo + web scraping — versión final (Daniel)

Ver también: [[Proyectos/Tacha/README|README]] · [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] · [[Proyectos/Tacha/historias-usuario|historias-usuario.md]]

> **Estado real de este módulo (2026-09-05, cerrado):** el diseño de abajo (schema, decisiones) está bien y confirmado — el PR lo implementa fiel a esto. Los 5 bugs bloqueantes de la sección 9 fueron corregidos por Daniel (commit `fix(scraping): corregir bugs de QA en pipeline de catálogo`) y verificados en revisión de diff, no solo del resumen de Daniel: precio ahora lee `raw_json->'offer'->>'Price'`, `parse_size_text` sin anclas (`\M` word-boundary, busca el tamaño dentro de `item.nameComplete`), `search_catalog` separado en dos CTEs (`variant_brands`/`variant_prices`) evitando el cross join duplicado, nueva RPC `get_recent_staging` (security definer, columnas whitelisteadas, sin exponer `raw_json`) en vez de abrir RLS de staging, y URLs de Supabase centralizadas en `SUPABASE_URL`. También corrigió 3 bugs adicionales que aparecieron al probar contra datos reales (función no aplicada en Supabase, columna ambigua en `normalize_staging_row`, `json` vs `jsonb` en `search_catalog`) y dejó ticket de seguimiento para el RLS abierto de `household_store_preferences` (bloqueado por el módulo de households de Esteban, no bloqueante para este PR).
>
> **Sprints (2026-09-05):** el plan de sprints real de Tacha (semanal, por HU, no por épica) vive en [[Proyectos/Tacha/analisis-complejidad-viabilidad|analisis-complejidad-viabilidad.md]] — Sprint 1 arranca lunes 2026-09-07, sprint review cada lunes. Daniel terminó su bloque de Semana 1-3 (pipeline + backend de catálogo) antes de tiempo gracias a este PR, así que en Sprint 1 apoya a Marcos con la UI de búsqueda (HU-36a) en vez de repetir trabajo ya hecho.
>
> **Merge (2026-09-05):** el PR va contra `develop`, no `main` — mi primera verificación de "sin conflicto" fue contra `main` por error y dio falso negativo. Contra `develop` sí había conflicto real (`develop` había recibido mientras tanto el UI kit completo de otro módulo): `.gitignore`, `app/constants/index.ts` y `app/layout.tsx` en conflicto add/add. Resuelto con Marcos: `.gitignore` y `layout.tsx` (con fuentes Fraunces/Public Sans del design system) se quedaron con la versión de `develop`; `app/constants/index.ts` se combinó (`scraping.constants` + `stores.constants` + `ui.constants`, sin colisión de nombres). Aprobado, label actualizado a `qa accepted`, mergeado a `develop`, rama `web-scraping-core` eliminada.

Reporte de Daniel (responsable del módulo de web scraping + catálogo, sección 12 de `documentacion-v1.md`). Cubre únicamente las tablas y componentes de ese módulo — no toca `households`, `lists`, `list_items`, `recipes`, `meal_plans`, `purchase_sessions` ni autenticación; esas tablas aparecen solo como referencias externas (FKs).

## 1. Alcance

Solo el módulo de catálogo + scraping. `households`, `lists`, etc. son referencias externas (FKs) cuando el catálogo las necesita.

## 2. Tablas — tal cual las define el documento oficial

### `categories`
Categorías de producto, globales. Referenciada por `product_catalog`.

### `product_catalog` — "producto madre"
`id` (uuid PK) · `name` (ej. "Leche") · `category_id` (FK → `categories`) · `household_id` (nullable — NULL = catálogo global) · `source` (`scraped`/`manual`) · `created_at`.
No incluye marca en su identidad (corrección 2026-08-18 del documento).

### `product_catalog_variants` — presentación/tamaño
`id` · `product_catalog_id` (FK) · `name` (ej. "Leche — caja 1L") · `base_unit` (`ml`/`g`/`unidad`) · `base_quantity` (numeric) · `image_url` · `created_at`.
Es la entidad que se busca/muestra (HU-51) y participa en la reconciliación de cantidades (4.9.1).

### `product_brands`
`id` · `product_catalog_variant_id` (FK) · `name` (ej. "Dos Pinos") · `logo_url` · `created_at`. Detalle de la variante, no variante propia.

### `product_catalog_staging`
`id` · `store_id` (FK → `stores`) · `raw_json` (jsonb, `{ product, item, offer }` tal como responde VTEX) · `scraped_name`/`scraped_brand`/`scraped_size_text` · `image_url` · `status` (`pending`/`matched`/`rejected`) · `matched_variant_id`/`matched_brand_id` (FK nullable) · `scraped_at`. Cola de revisión entre el dato crudo y el catálogo real (4.7).

### `product_prices`
`id` (bigserial) · `product_catalog_variant_id` (FK) · `product_brand_id` (FK) · `store_id` (FK) · `price` · `list_price` · `is_available` · `source` · `captured_at`. Vista `latest_prices`: último precio por (variant, brand, store).

### `stores` — fija, sembrada, no editable en runtime
`id` (uuid) · `slug` (unique, `maxipali`/`walmart`/`masxmenos`) · `display_name` · `base_url` (endpoint VTEX de esa tienda). Exactamente 3 filas — el scraper solo cubre esas 3 cadenas, no está en el roadmap agregar más.

### `household_store_preferences` — tabla puente
`household_id` (FK → `households`, real cuando ese módulo exista) · `store_id` (FK → `stores`) · `visible` (boolean, default `true`) · PK compuesta (`household_id`, `store_id`).
Sin fila para un `(household, store)` dado ⇒ se asume `visible = true`. Regla de lectura estándar para cualquier módulo:
```sql
select s.* from stores s
left join household_store_preferences hsp
  on hsp.store_id = s.id and hsp.household_id = :household_id
where coalesce(hsp.visible, true) = true;
```
RLS de esta tabla es **temporal** (`using(true)` en insert/update/delete) porque el módulo `households` de Esteban todavía no existe en Supabase — cuando exista, hay que reemplazar por policy que verifique membresía real (TODO ya anotado en `schema.sql`). Hasta entonces, cualquiera con la anon key puede reescribir preferencias de cualquier household — no es RLS mal implementado, es un placeholder consciente a cerrar apenas exista auth.

### `search_cache` / `search_log` — infraestructura, no negocio
`search_cache` (store_id, normalized_query, staging_ids[], cached_at) — cache-first, TTL 6h. `search_log` (store_id, query, source, result_count, searched_at) — auditoría de búsquedas. Ambas bloqueadas por RLS sin policies (solo `service_role`).

## 3. Desviaciones respecto al documento — ya justificadas y sin objeción del equipo

| Punto | Documento dice | Se implementó | Motivo |
|---|---|---|---|
| Staging | Tabla de datos crudos, sin detalle de columnas | `status` + FKs de match explícitas | Filtro directo `where status='pending'` en vez de LEFT JOIN para inferir progreso |
| Búsqueda | No especifica mecanismo | Índice `pg_trgm`/GIN sobre `product_catalog.name` | Tolerar errores de tipeo sin `seq scan` |
| `stores` | "por household", ambiguo | Fija a 3 filas + `household_store_preferences` | Resuelto 2026-08-27 (Marcos): elegir cuáles de las 3 seguir, no tiendas propias |
| Ingesta | Todo vía PostgREST + RPC | Edge Functions solo para llamadas HTTP salientes a VTEX | RPC/PostgREST no está pensado para llamar APIs externas; recomendación oficial de Supabase |
| Matching staging→catálogo | Función/trigger en la base de datos | Función SQL invocada explícitamente (no trigger automático) | Evitar que el matching bloquee/falle la inserción del dato crudo en batch |

Ninguna de estas contradice `documentacion-v1.md` sección 6 — la sección 6 ya está actualizada con esta resolución (ver la fila `stores`/`household_store_preferences` ahí).

## 4. Los dos "lados" del sistema (para cualquiera que toque este módulo)

**Lado A — Ingesta (Edge Functions).** Al buscar "leche", una Edge Function le pregunta a VTEX y guarda el resultado crudo en `product_catalog_staging`. Datos tal como los devuelve el súper, sin normalizar.

**Lado B — Catálogo normalizado.** Lo que el resto de la app debe consultar es `product_catalog` + `product_catalog_variants` + `product_brands`. El proceso que convierte staging → catálogo normalizado es `normalize_staging_row`/`normalize_pending_staging` (spec 3 del PR) — **existe en el PR pero tiene bugs, ver sección 9.**

## 5. Cómo probar la ingesta

```
POST https://ifvwumejbfpowxlkjfiu.supabase.co/functions/v1/ingest-maxipali
Headers: Authorization: Bearer <anon-key>, Content-Type: application/json
Body: { "query": "leche" }
```
Funciones: `ingest-maxipali`, `ingest-walmart`, `ingest-masxmenos`. Respuesta esperada: `{ source: "live"|"cache", store, query, stagedCount }`.

## 6. Convenciones que cualquier código nuevo de este módulo debe respetar

- Nombres de tabla/columna exactos, alineados a `documentacion-v1.md` sección 6.
- Ninguna Edge Function nueva de scraping escribe directo a `product_catalog`/`variants`/`brands` — todo pasa primero por `product_catalog_staging`.
- `source: scraped | manual` es el discriminador — nunca una tabla paralela tipo `custom_products`.
- Las 3 tiendas están fijas — ningún código inserta una 4ª fila en `stores` sin decisión explícita del equipo.

## 7. Próximo paso (según el propio Daniel, dentro del PR)

1. ✅ `schema.sql` con las tablas de este reporte, RLS incluida.
2. ✅ Edge Functions de ingesta escribiendo en `product_catalog_staging`.
3. ✅ Función de matching (`normalize_staging_row`) — construida en el PR, **pero con bugs, no usable con datos reales todavía** (sección 9).
4. Pendiente: RLS real de `household_store_preferences` cuando exista el módulo de households (Esteban).

## 8. Diagrama del modelo — DBML para dbdiagram.io

```dbml
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
  name text [not null]
  base_unit text [not null, note: 'ml | g | unidad']
  base_quantity numeric [not null]
  image_url text
  created_at timestamptz [not null, default: `now()`]
}

Table product_brands {
  id uuid [pk]
  product_catalog_variant_id uuid [not null, ref: > product_catalog_variants.id]
  name text [not null]
  logo_url text
  created_at timestamptz [not null, default: `now()`]
}

Table stores {
  id uuid [pk]
  slug text [not null, unique, note: 'maxipali | walmart | masxmenos']
  display_name text [not null]
  base_url text [not null]
}

Table household_store_preferences {
  household_id uuid [not null, ref: > households.id]
  store_id uuid [not null, ref: > stores.id]
  visible boolean [not null, default: true]
  indexes { (household_id, store_id) [pk] }
}

Table product_catalog_staging {
  id uuid [pk]
  store_id uuid [not null, ref: > stores.id]
  raw_json jsonb [not null]
  scraped_name text
  scraped_brand text
  scraped_size_text text
  image_url text
  status text [not null, default: 'pending']
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
  source text [not null]
  captured_at timestamptz [not null, default: `now()`]
}
```

## 9. Bugs reales en la implementación del PR (encontrados en revisión, 2026-09-04 — el diseño de arriba está bien, la ejecución no)

Ya avisado a Daniel. Dejar acá porque afecta a cualquiera que construya sobre este módulo mientras no esté arreglado:

1. **Extracción de precio siempre falla.** El código guarda `raw_json.offer` = el `commertialOffer` real de VTEX, cuyo campo de precio es `Price` (confirmado en `types.ts`, con nota explícita del propio Daniel de haber verificado el nombre real del campo contra la API). Pero `normalize_staging_row` busca `raw_json->'offer'->>'spotPrice'`, que no existe — toda fila se rechaza por "no se pudo extraer precio".
2. **El parseo de tamaño nunca matchea.** `parse_size_text` usa regex ancladas (`^...$`) que esperan un token puro ("1 litro"), pero se le pasa `item.nameComplete` completo (ej. "Leche Entera Dos Pinos 1 Litro") — nunca matchea, la fila se rechaza por tamaño no parseable.
3. Consecuencia de 1+2: el propio criterio de aceptación de Daniel en el PR ("matched > 0, rejected = 0") es **imposible** con datos reales de scraping — solo pasa con las filas de prueba sembradas a mano.
4. `search_catalog` (RPC de lectura) hace `cross join stores` antes del `group by` — con 2 marcas × 3 tiendas devuelve marcas duplicadas en vez de agrupadas.
5. URL de Supabase hardcodeada en 3 archivos del frontend en vez de env var.

No bloquea el diseño del modelo de datos (sección 2-3 de esta nota siguen siendo la referencia correcta) — bloquea que el pipeline end-to-end funcione con datos reales hoy.
