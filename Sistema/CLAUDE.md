# Vault — Marcos

Este vault es la fuente de verdad para universidad y proyectos personales. Reglas para navegarlo:

## Estructura

- `/Cursos/{curso}/temario.md` — contenido del curso
- `/Cursos/{curso}/entregas.md` — fechas y estado de entregables (tabla)
- `/Cursos/{curso}/apuntes/` — notas de estudio
- `/Cursos/{curso}/examenes/` — material específico de examen
- `/Proyectos/{GymBase|Tacha|CaneleApp}/` — contexto y documentación de cada proyecto
- `/Sistema/skills/` — skills reusables (clean-code-practices, gitflow-scrum, y los que se agreguen)
- `/Sistema/tickets.md` — registro único de prefijos de ticket por curso/proyecto y último número usado (ver `gitflow-scrum`)

## Cómo responder

1. Si la pregunta es sobre un curso o examen específico, buscar SOLO dentro de esa carpeta de `/Cursos/{curso}/` — no mezclar contenido de otros cursos salvo que se pida explícitamente comparar. Usar `Sistema/skills/course-study-helper/SKILL.md`.
2. Si es sobre un proyecto, usar solo `/Proyectos/{proyecto}/` como contexto — no mezclar stacks entre proyectos.
3. Para cualquier tarea de código, aplicar `Sistema/skills/clean-code-practices/SKILL.md`.
4. Para cualquier tarea de diseño de UI/UX, aplicar `Sistema/skills/enterprise-ui-ux-design/SKILL.md`.
5. Para QA, test cases o bug reports, aplicar `Sistema/skills/qa-testing-practices/SKILL.md`.
6. Para documentación técnica (README, docs, comentarios), aplicar `Sistema/skills/professional-technical-docs/SKILL.md`.
7. Para cualquier operación de git (branch, commit, PR), aplicar `Sistema/skills/gitflow-scrum/SKILL.md` — el código de ticket sale siempre de `Sistema/tickets.md`, nunca se inventa mirando el log.
8. Antes de crear una nota nueva, buscar si ya existe algo relacionado — no duplicar.
8.1. Si aparece un documento nuevo en `Sistema/inbox/` (PDF, doc, foto de apuntes, propio o subido por Hermes), aplicar `Sistema/skills/document-intake/SKILL.md` para convertirlo en nota(s) del curso correspondiente.
9. Nunca borrar notas — si algo queda obsoleto, moverlo a una carpeta `_archivo/` dentro del curso/proyecto correspondiente.
10. Al agregar una fecha de entrega nueva en `entregas.md`, ofrecer sincronizarla al calendario (MCP de Google Calendar ya conectado) o a Todoist (MCP ya conectado) según corresponda.
11. Para tareas grandes (cerrar un ticket, preparar un PR), considerar usar los subagentes en `Sistema/agents/` (code-reviewer, qa-checker, docs-writer) en vez de hacer todo en una sola pasada — ver `Sistema/agents/README.md`.

## Convención de commits/PRs para este vault

Si el vault mismo se versiona con Git (recomendado), usar el mismo formato de `gitflow-scrum`: `docs(CURSO-n): agregar apuntes de unidad 3`.
