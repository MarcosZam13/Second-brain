# Tacha

Ver también: [[Proyectos/README|Proyectos]] · [[Proyectos/Tacha/documentacion-v1|Documentación v1]] · [[Proyectos/Tacha/DESIGN|DESIGN.md]]

**Curso:** Introducción al Desarrollo Web · **Equipo:** 6 integrantes · **Estado:** stack (Next.js, Tailwind, Supabase) y DB confirmados por todo el equipo en reunión del 2026-08-16, pendiente confirmación del profesor; repo de código ya creado (`MarcosZam13/tacha`, privado); resto de pendientes en [[Proyectos/Tacha/documentacion-v1#10. Pendientes de definición|sección 10 del documento]].

## Qué es

App web colaborativa de listas de compras para grupos (familias o amigos): listas compartidas con tachado en tiempo real, dashboard financiero, catálogo de productos/precios poblado por web scraping de supermercados costarricenses, y un planificador semanal de comidas conectado a las listas. Ver el detalle completo en [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]].

## Stack

Next.js · Supabase (Postgres + Auth + Realtime + RLS) vía PostgREST/RPC · TanStack Query · Tailwind CSS · PWA instalable. Next.js y Tailwind se definieron unilateralmente (Marcos) solo para poder crear el repo y arrancar la colaboración — quedan sujetos a confirmación en la primera reunión de equipo. Detalle y justificación en la [[Proyectos/Tacha/documentacion-v1#7. Arquitectura técnica propuesta|sección 7 de la documentación]].

## Pendiente antes de empezar a codear

Ver [[Proyectos/Tacha/documentacion-v1#10. Pendientes de definición|sección 10 de la documentación]] — herramienta de scraping y quién la lidera, qué supermercados son viables de scrapear, y el enfoque del inventario doméstico. Estas son decisiones de equipo, no unilaterales (proyecto de 6 personas).

## Repositorio de código

`MarcosZam13/tacha` (privado) — ver [[Proyectos/Tacha/flujo-git-tablero|flujo-git-tablero.md]] para el detalle de branches, labels de PR y el tablero (Jira) que lo acompaña. Compañeros pendientes de invitar como colaboradores.

## Dónde está cada cosa

- [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] — documento de proyecto completo (resumen, requerimientos funcionales/no funcionales, modelo de datos, arquitectura, dirección de diseño, división de trabajo).
- [[Proyectos/Tacha/DESIGN|DESIGN.md]] — guía de diseño (personalidad, tokens, inventario de pantallas, prompts listos) para generar interfaz en Stitch AI.
- `mockups/mockup-web-v2.html` — prototipo HTML interactivo (desktop + mobile web, modo claro/oscuro). v2, el propio equipo lo marca como "por mejorar mucho" — se espera que evolucione una vez estén cerrados los requerimientos.
- `_fuentes/` — el `.docx` original tal como lo entregó el equipo, sin editar.

## Sistema de agentes del repo de código — ya montado

El repo (`MarcosZam13/tacha`) ya tiene `AGENTS.md` en la raíz + `.agents/skills/` (component-architecture, constants-standards, unit-testing-standards, nextjs-enterprise-patterns, clean-code-practices, adaptados de [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise|base-proyectos-arquitectura-enterprise]] a este stack) + puentes finos (`CLAUDE.md`, `.cursor/rules/skills.mdc`, `.github/copilot-instructions.md`) para que cualquiera del equipo de 6, use el agente de IA que use, tenga las mismas convenciones sin leer este vault. Patrón fuente: [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise#1. El patrón meta: contrato de agentes cross-IDE|el patrón exacto]].

[[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] **no** aplica tal cual acá — el repo sigue el modelo de ramas que exige el profesor (`main`/`develop`/`ticket`/`entregable`/`qa-fix`/`hotfix`), documentado en [[Proyectos/Tacha/flujo-git-tablero|flujo-git-tablero.md]] y en `CONTRIBUTING.md` del repo. Prefijo de ticket `TACHA` ya registrado en [[Sistema/tickets|tickets.md]].
