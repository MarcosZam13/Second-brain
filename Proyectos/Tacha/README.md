# Tacha

Ver también: [[Proyectos/README|Proyectos]] · [[Proyectos/Tacha/documentacion-v1|Documentación v1]]

**Curso:** Introducción al Desarrollo Web · **Equipo:** 6 integrantes · **Estado:** propuesta formal v1.0, pendiente de revisión por el equipo.

## Qué es

App web colaborativa de listas de compras para grupos (familias o amigos): listas compartidas con tachado en tiempo real, dashboard financiero, catálogo de productos/precios poblado por web scraping de supermercados costarricenses, y un planificador semanal de comidas conectado a las listas. Ver el detalle completo en [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]].

## Stack (propuesto, con piezas aún pendientes de decisión del equipo)

React (Next.js vs. Vite, sin decidir) · Supabase (Postgres + Auth + Realtime + RLS) vía PostgREST/RPC · TanStack Query · Tailwind CSS (recomendado, sin confirmar) · PWA instalable. Detalle y justificación en la [[Proyectos/Tacha/documentacion-v1#7. Arquitectura técnica propuesta|sección 7 de la documentación]].

## Pendiente antes de empezar a codear

Ver [[Proyectos/Tacha/documentacion-v1#10. Pendientes de definición|sección 10 de la documentación]] — framework definitivo, librería de estilos, herramienta de scraping y quién la lidera, qué supermercados son viables de scrapear, y el enfoque del inventario doméstico. Estas son decisiones de equipo, no unilaterales (proyecto de 6 personas).

## Dónde está cada cosa

- [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] — documento de proyecto completo (resumen, requerimientos funcionales/no funcionales, modelo de datos, arquitectura, dirección de diseño, división de trabajo).
- `mockups/mockup-web-v2.html` — prototipo HTML interactivo (desktop + mobile web, modo claro/oscuro). v2, el propio equipo lo marca como "por mejorar mucho" — se espera que evolucione una vez estén cerrados los requerimientos.
- `_fuentes/` — el `.docx` original tal como lo entregó el equipo, sin editar.
