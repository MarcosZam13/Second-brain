---
proyecto: AsistenciasTEC
tipo: proyecto
fecha_inicio: 2026-09-09
---

# Asistencias TEC

Ver también: [[Proyectos/README|Proyectos]] · [[Proyectos/AsistenciasTEC/backlog|backlog.md]] · [[Sistema/aprendizaje/README|Base de aprendizaje de arquitectura]]

**Contexto:** mentoría/asistencia conseguida con el profesor de Desarrollo Web (tiene su propia empresa de software) — 2026-09-09. Entré con un par de semanas de atraso respecto al resto del equipo, pero el proyecto todavía no avanzó mucho. Distinto de una entrega de curso: la intención explícita del profesor es enseñar arquitectura y buenas prácticas de nivel empresa (SOLID, cómo pensar en TypeScript, manejo de repositorio, hooks, etc.) y va a preguntar sobre el código — no basta con que funcione, hay que poder explicar por qué está hecho así. Nombre de carpeta/prefijo de ticket (`AS`) provisional, tomado del prefijo que ya usa el propio backlog del profesor — confirmar si el proyecto tiene un nombre oficial distinto.

## Qué es

Plataforma para gestionar asistencias (asistentías) de estudiantes del TEC en distintas sedes: estudiantes se postulan a asistencias disponibles (por ámbito: especiales, horas asistente, tutoría, hora estudiante), profesores gestionan sus solicitudes y aceptan postulantes, y un super admin controla el ciclo de vida completo (crear/editar/borrar/habilitar asistencias, aprobar profesores, aprobar/denegar solicitudes de estudiantes). Tres roles: estudiante, profesor, super admin. Detalle completo en [[Proyectos/AsistenciasTEC/backlog|backlog.md]], incluida una lectura crítica de vacíos/contradicciones del backlog original que conviene resolver en el refinamiento antes de estimar sprints.

## Cómo se va a trabajar (distinto al resto de proyectos del vault)

- **Playwright** para testing end-to-end — primera vez que se usa en este vault, no hay skill propio todavía.
- **Jira** para el tablero (igual que Tacha, pero con más disciplina esperada — el profesor evalúa el proceso, no solo el resultado).
- **MCP de Stitch** con un skill que va a compartir el profesor — pendiente de recibir, cuando llegue se documenta acá y se compara contra el uso actual de Stitch en Tacha ([[Proyectos/Tacha/DESIGN|DESIGN.md]]).
- **Git flow real de la empresa del profesor — confirmado 2026-09-16** (diagrama compartido directamente): es el mismo patrón `main`/`develop`/`ticket`/`entregable`/`qa-fix`/`hotfix` que usa Tacha, ver Modelo 3 en [[Sistema/aprendizaje/git-workflow-diagrama|git-workflow-diagrama.md]] y la variante reusable en [[Sistema/skills/gitflow-scrum/SKILL#1b. Variante: modelo de Entregables (cuando el curso/empresa entrega por hitos)|gitflow-scrum §1b]]. Formato de PR pedido: Qué hace / Cómo se testea / Ticket de Jira (link) / Screenshots UI / Screenshots Playwright ([[Sistema/skills/gitflow-scrum/SKILL#4b. PR format variant — Jira + Playwright projects (e.g. Asistencias TEC)|gitflow-scrum §4b]]).
- Programar a mano, entendiendo cada decisión de arquitectura — no aceptar código generado por IA sin poder explicarlo. El profesor va a preguntar.

## Stack

Pendiente de definir con el equipo/profesor. Lenguaje casi seguro TypeScript; el usuario quiere profesionalizarse específicamente en **React** como su lenguaje/framework de especialización a nivel laboral, así que salvo indicación contraria del profesor, este es el proyecto donde más vale la pena invertir en entender la arquitectura a fondo (no solo copiar el patrón de Tacha).

## Dónde está cada cosa

- [[Proyectos/AsistenciasTEC/backlog|backlog.md]] — product backlog completo (31 items, IDs AS-01 a AS-31) convertido de `Sistema/inbox/Backlog.xlsx`, con notas de revisión de vacíos y contradicciones de flujo.
- `_fuentes/Backlog.xlsx` — archivo original tal como lo pasó el profesor/equipo, sin editar (llegó por `Sistema/inbox/`, archivado acá tras convertirlo).
- **Repo real del código:** `C:/Users/luisy/Documents/ProyectosPersonales/Sistema_asistencias/BaseProyectos-main` (remote `comunidadaplicacionesmoviles/Sistema_asistencias` en GitHub), fuera del vault. Es la base que da el profesor (Next.js App Router + React 19 + TypeScript + Redux Toolkit + Tailwind + Storybook + Firebase), ya trae su propio patrón `AGENTS.md` + `.agents/skills/*/SKILL.md` (mismo mecanismo que las skills del vault, pero autocontenido en el repo) con `code-style-standards`, `component-architecture`, `component-standards`, `constants-standards`, `api-mutation-standards`, `redux-store-architecture`, `unit-testing-standards`, `eslint-standards`, `prettier-standards`, `playwright-cli`, `playwright-e2e`. **Pendiente real:** `AGENTS.md` y el README todavía describen el template original ("MediXenter", un producto de salud) sin adaptar a Asistencias TEC — falta actualizar el "Project snapshot" de `AGENTS.md`, y agregarle seguridad + el trío arquitectura/SCRUM/HU (ver abajo).

## Buenas prácticas y agentes

Todo lo que faltaba (seguridad, docs de arquitectura/SCRUM/historias de usuario, gitflow escrito, formato de PR) quedó empaquetado en **[[Proyectos/AsistenciasTEC/dev-template/README|dev-template/]]**, autocontenido, en inglés y genérico a propósito (sin mencionar al profesor, este proyecto, ni otros proyectos del usuario) para poder copiarlo a cualquier repo o compartirlo con el equipo sin contexto de más — ver ese README para el detalle de cada archivo, y `PROMPT-INTEGRATION.md` para el prompt listo para pegarle a Claude Code dentro del repo real. El repo base ya cubre bien "buenas prácticas TS/Next" con sus propias skills (no se duplicaron); el hueco real era seguridad y proceso, cerrado el 2026-09-16.

Origen de cada pieza en el vault (por si hace falta editar la fuente en vez de la copia del template): [[Sistema/skills/security-practices/SKILL|security-practices]], [[Sistema/agents/security-reviewer|security-reviewer]], [[Sistema/skills/scrum-architecture-docs/SKILL|scrum-architecture-docs]], [[Sistema/agents/README|code-reviewer/qa-checker]], [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum §1b/§4b]] — esas siguen en español/con contexto del vault, es la versión genérica en `dev-template/` la que se comparte afuera.

## Aprendizaje asociado

Este proyecto es el disparador de una base de conocimiento nueva y de uso general (no solo para este proyecto): [[Sistema/aprendizaje/README|Sistema/aprendizaje/]], con notas sobre SOLID, arquitectura de TypeScript, diagrama de manejo de repositorio y qué es un hook — los cuatro temas que pidió investigar el profesor. Se sigue ampliando a medida que aparezcan preguntas nuevas de código o de arquitectura.
