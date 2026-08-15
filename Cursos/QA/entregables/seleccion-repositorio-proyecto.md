---
curso: QA
tema: Selección de repositorio — candidatos evaluados
fecha: 2026-08-15
tipo: entregable
entregable_de: "[[Cursos/QA/apuntes/criterios-seleccion-repositorio-github]]"
estado: borrador
tags: [proyecto, seleccion-repositorio, github, fase1]
---

# Selección de repositorio — candidatos evaluados

Ver también: [[Cursos/QA/apuntes/criterios-seleccion-repositorio-github|Criterios para Seleccionar Proyectos en GitHub]] · [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]] · [[Cursos/QA/entregables/diario-reflexivo|Diario Reflexivo del Proyecto]] · [[Cursos/QA/entregas]]

**Estado:** exploración inicial hecha con Claude Code (`gh` CLI + GitHub API), verificando datos en vivo el 2026-08-15. Falta decisión final del equipo — esto es un punto de partida, no la elección cerrada.

## Metodología

Se consultó la API de GitHub (estrellas, forks, issues abiertos, `pushedAt`, tamaño del repo, licencia, commits recientes y top contribuidores) para varios candidatos conocidos de código abierto que encajan con las tecnologías sugeridas por el profesor (React/Angular/Vue, Django/Flask, Spring Boot, Rails, Laravel). No se verificó en detalle cada criterio (ej. accesibilidad WCAG puntual, ESLint/PEP8 exacto) — eso requiere clonar y revisar el repo elegido antes de comprometerse.

## Candidatos recomendados

| Repo | Stack | ⭐ Stars | Forks | Issues abiertos | Último push | Auth | Docker | Notas |
|---|---|---|---|---|---|---|---|---|
| **[documenso/documenso](https://github.com/documenso/documenso)** | Next.js/TypeScript (React) + Prisma/Postgres | 14,484 | 3,061 | 253 | 2026-08-15 (mismo día) | Login/registro + 2FA + OAuth (NextAuth) | Sí, con healthcheck documentado | Tamaño moderado (repo único, no monorepo gigante), commit reciente de traducción al polaco → cumple el criterio 9 (múltiples idiomas) de forma concreta. Contribuidores humanos bien repartidos (top 5 entre 273-1145 contribuciones) |
| **[chatwoot/chatwoot](https://github.com/chatwoot/chatwoot)** | Ruby on Rails + Vue | 35,894 | 8,617 | 1,337 | 2026-08-14 | Login de agentes + widget de cliente | Sí | Comunidad enorme y muy activa (PRs mergeados a diario), pero stack local más pesado (Postgres + Redis + Sidekiq) — más setup |
| **[firefly-iii/firefly-iii](https://github.com/firefly-iii/firefly-iii)** | Laravel/PHP + Vue (islas) | 24,322 | 2,250 | 161 | 2026-08-15 (mismo día) | Login/registro + 2FA, también actúa como proveedor OAuth | Sí, `docker-compose` oficial | API documentada con OpenAPI/Swagger. Ojo: el mantenimiento está muy concentrado en un solo desarrollador (20,800 commits vs. 131 del siguiente humano) — la comunidad de PRs es menor que en los otros dos |

## Descartados en la exploración

- **BookStackApp/BookStack** (PHP/Laravel) — la descripción del repo en GitHub dice *"NOW MANAGED ON CODEBERG"* y muestra 0 issues abiertos: el proyecto se mudó de plataforma, así que ya no cumple el criterio 3 (historial de bugs gestionado activamente en GitHub).
- **calcom/cal.com** y **novuhq/novu** — cumplen los criterios técnicos (stack, auth, docs, comunidad enorme) pero son monorepos muy grandes (1.1 GB y ~490 MB, decenas de paquetes) — riesgo alto de fricción para "ejecutar localmente sin problemas" en el tiempo de un proyecto de curso.

## Recomendación

**Documenso** como primera opción: tamaño más manejable que Chatwoot, stack moderno (React/Next.js, cubierto por el criterio 1), auth real y testeable, Docker documentado, actividad reciente verificada el mismo día de esta búsqueda, y el criterio de idiomas (9) queda cubierto de forma explícita. Chatwoot es la alternativa si el equipo prefiere Ruby on Rails o quiere una comunidad todavía más grande. Firefly III es viable pero pesa más el riesgo de "un solo mantenedor" si hace falta interactuar con el proyecto real (ej. reportar algo) — aunque para el propósito del curso (aplicar QA sobre el código ya existente) no debería ser un problema real.

## Pendiente

- [ ] Decisión final del equipo (Marcos, Mario, Joseph, + integrante que falte) — esta lista es punto de partida, no la elección cerrada
- [ ] Clonar el repo elegido y confirmar que corre localmente sin problemas (criterio explícito del PDF)
- [ ] Revisar en detalle accesibilidad (WCAG/ARIA) y estándares de codificación (ESLint/PEP8 según stack) del repo elegido
- [ ] Una vez elegido, actualizar [[Cursos/QA/apuntes/proyecto-qa-guia]] y [[Cursos/QA/entregables/diario-reflexivo]] con el repo final
