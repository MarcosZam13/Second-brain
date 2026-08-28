# Tacha

Ver también: [[Proyectos/README|Proyectos]] · [[Proyectos/Tacha/documentacion-v1|Documentación v1]] · [[Proyectos/Tacha/DESIGN|DESIGN.md]]

**Curso:** Introducción al Desarrollo Web · **Equipo:** 6 integrantes · **Estado:** stack (Next.js, Tailwind, Supabase) y DB confirmados por todo el equipo en reunión del 2026-08-16, pendiente confirmación del profesor; repo de código ya creado (`MarcosZam13/tacha`, privado); resto de pendientes en [[Proyectos/Tacha/documentacion-v1#10. Pendientes de definición|sección 10 del documento]].

## Qué es

App web colaborativa de listas de compras para grupos (familias o amigos): listas compartidas con tachado en tiempo real, dashboard financiero, catálogo de productos/precios poblado por web scraping de supermercados costarricenses, y un planificador semanal de comidas conectado a las listas. Ver el detalle completo en [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]].

## Stack

Next.js · Supabase (Postgres + Auth + Realtime + RLS) vía PostgREST/RPC · TanStack Query · Tailwind CSS · PWA instalable. Next.js y Tailwind se propusieron unilateralmente (Marcos) para poder crear el repo y arrancar la colaboración, y quedaron **confirmados por todo el equipo en la reunión del 2026-08-16** junto con el resto del stack. Detalle y justificación en la [[Proyectos/Tacha/documentacion-v1#7. Arquitectura técnica propuesta|sección 7 de la documentación]].

## Pendiente antes de empezar a codear

Ver [[Proyectos/Tacha/documentacion-v1#10. Pendientes de definición|sección 10 de la documentación]] — herramienta de scraping y quién la lidera, qué supermercados son viables de scrapear, y el enfoque del inventario doméstico. Estas son decisiones de equipo, no unilaterales (proyecto de 6 personas).

## Repositorio de código

`MarcosZam13/tacha` (privado) — ver [[Proyectos/Tacha/flujo-git-tablero|flujo-git-tablero.md]] para el detalle de branches, labels de PR y el tablero (Jira) que lo acompaña. Compañeros pendientes de invitar como colaboradores.

## Dónde está cada cosa

- [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] — documento de proyecto completo, ahora en v2.2 (resumen, requerimientos funcionales/no funcionales, modelo de datos, arquitectura, dirección de diseño, división de trabajo).
- `Tacha_documentacion-v2.1.docx` — versión Word de `documentacion-v1.md`, para compartir con el equipo/profesor fuera de Obsidian/GitHub. **Desactualizada** respecto al contenido actual (v2.2) — pendiente regenerar. El nombre de archivo lleva el número de versión del contenido, no el de la nota (`documentacion-v1.md` mantiene su nombre de archivo original en el vault por las wikilinks).
- [[Proyectos/Tacha/historias-usuario|historias-usuario.md]] — historias de usuario y criterios de aceptación (v2.2, completo y numerado — todos los módulos del alcance v1 desglosados, con síntesis de flujo de usuario al final), desglosando los requerimientos de `documentacion-v1.md` en épicas/HU/CA. Lista para importar a JIRA.
- `Tacha_historias-usuario-v2.2.docx` — versión Word de `historias-usuario.md` sin referencias a otros archivos del vault (sin wikilinks, sin menciones a DESIGN.md/documentacion-v1.md), para pasarle al equipo tal cual.
- [[Proyectos/Tacha/analisis-complejidad-viabilidad|analisis-complejidad-viabilidad.md]] — complejidad (Fibonacci), importancia y encargado rebalanceado por HU, más plan de 10 sprints de 1 semana respetando dependencias. Versión interactiva (tabla + sprints) publicada como Artifact, compartible con el equipo desde su menú de compartir.
- [[Proyectos/Tacha/DESIGN|DESIGN.md]] — guía de diseño (personalidad, tokens, navegación, inventario de las 22 pantallas del alcance v1, componentes, estados y un prompt listo por pantalla) para generar interfaz en Stitch AI.
- [[Proyectos/Tacha/modulo-catalogo-scraping|modulo-catalogo-scraping.md]] — rediseño del schema de catálogo + web scraping (Daniel, 2026-08-27), con la resolución de la ambigüedad de `stores`/`household_store_preferences` y diagrama DBML listo para dbdiagram.io.
- `mockups/mockup-web-v2.html` — prototipo HTML interactivo (desktop + mobile web, modo claro/oscuro). v2, el propio equipo lo marca como "por mejorar mucho" — se espera que evolucione una vez estén cerrados los requerimientos.
- `_fuentes/` — el `.docx` original tal como lo entregó el equipo, sin editar.

## Sistema de agentes del repo de código — ya montado

El repo (`MarcosZam13/tacha`) ya tiene `AGENTS.md` en la raíz + `.agents/skills/` (component-architecture, constants-standards, unit-testing-standards, nextjs-enterprise-patterns, clean-code-practices, adaptados de [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise|base-proyectos-arquitectura-enterprise]] a este stack) + puentes finos (`CLAUDE.md`, `.cursor/rules/skills.mdc`, `.github/copilot-instructions.md`) para que cualquiera del equipo de 6, use el agente de IA que use, tenga las mismas convenciones sin leer este vault. Patrón fuente: [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise#1. El patrón meta: contrato de agentes cross-IDE|el patrón exacto]].

[[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] **no** aplica tal cual acá — el repo sigue el modelo de ramas que exige el profesor (`main`/`develop`/`ticket`/`entregable`/`qa-fix`/`hotfix`), documentado en [[Proyectos/Tacha/flujo-git-tablero|flujo-git-tablero.md]] y en `CONTRIBUTING.md` del repo. Prefijo de ticket `TACHA` ya registrado en [[Sistema/tickets|tickets.md]].
