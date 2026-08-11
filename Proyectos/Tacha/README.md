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

## Buenas prácticas — skills a aplicar una vez arranque el repo de código

Cuando el equipo cierre stack y arranque el repo real de Tacha (repo aparte, no vive en este vault), aplicar:

- [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]] siempre.
- [[Sistema/skills/component-architecture/SKILL|component-architecture]], [[Sistema/skills/constants-standards/SKILL|constants-standards]] y [[Sistema/skills/unit-testing-standards/SKILL|unit-testing-standards]] — se aplican tal cual, son agnósticas de si el equipo termina en Next.js o Vite, y de Supabase vs. cualquier otro backend.
- [[Sistema/skills/nextjs-enterprise-patterns/SKILL|nextjs-enterprise-patterns]] §3-4 (estado compartido y mutaciones tipadas) — la parte de esa nota que sí depende del stack: como Tacha usa TanStack Query (no Redux) y Supabase (no Firebase), adaptar los ejemplos al equivalente de TanStack (`useMutation`/`useQuery` tipados) en vez de copiar los de Redux/`useApiMutation` literalmente.
- [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] para branches/commits/PRs — prefijo `TACHA` ya registrado en [[Sistema/tickets|tickets.md]].
- Considerar replicar el patrón de enrutamiento de agentes del repo fuente (`AGENTS.md` raíz + `.agents/skills/` + puentes finos por herramienta) directamente en el repo de Tacha, para que cualquiera del equipo de 6 que use Claude Code/Cursor/Copilot tenga las mismas convenciones sin tener que leer este vault — ver [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise#1. El patrón meta: contrato de agentes cross-IDE|el patrón exacto]].

Contexto completo del repo de referencia usado para armar estos skills: [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise|base-proyectos-arquitectura-enterprise]].
