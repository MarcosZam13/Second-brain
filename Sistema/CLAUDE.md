# Vault — Marcos

Este vault es la fuente de verdad para universidad y proyectos personales. Reglas para navegarlo.

Ver también: [[Dashboard]] · [[Sistema/proyecto-segundo-cerebro|Diseño completo del sistema]] · [[Sistema/tickets|Registro de tickets]] · [[Cursos/README|Cursos]] · [[Proyectos/README|Proyectos]]

## Estructura

- `/Cursos/{curso}/temario.md` — contenido del curso
- `/Cursos/{curso}/entregas.md` — fechas y estado de entregables (tabla)
- `/Cursos/{curso}/apuntes/` — notas de estudio e instrucciones/rúbricas del profesor
- `/Cursos/{curso}/examenes/` — material específico de examen
- `/Cursos/{curso}/entregables/` — tus propios borradores/respuestas de tareas (diario, reportes, proyectos) — separado de `apuntes/`, que es material del profesor, no tuyo
- `/Cursos/{curso}/repasos/` — notas de repaso para quices/exámenes, sintetizadas por Claude Code a partir de `apuntes/` (no material original del profesor, por eso separado de `apuntes/`) — ver [[Sistema/skills/quiz-repaso/SKILL|quiz-repaso]]
- `/Proyectos/{GymBase|Tacha|CaneleApp}/` — contexto y documentación de cada proyecto
- `/Sistema/skills/` — skills reusables (clean-code-practices, gitflow-scrum, y los que se agreguen)
- `/Sistema/tickets.md` — registro único de prefijos de ticket por curso/proyecto y último número usado (ver `gitflow-scrum`)

**Regla de navegación:** toda carpeta nueva de primer nivel (`Cursos/`, `Proyectos/`) tiene una nota `README.md` que sirve de hub — cualquier curso/proyecto nuevo se agrega ahí como wikilink apenas se crea su carpeta, no después. Esto es lo que mantiene el graph view de Obsidian navegable en vez de lleno de notas aisladas.

## Cómo responder

1. Si la pregunta es sobre un curso o examen específico, buscar SOLO dentro de esa carpeta de `/Cursos/{curso}/` — no mezclar contenido de otros cursos salvo que se pida explícitamente comparar. Usar [[Sistema/skills/course-study-helper/SKILL|course-study-helper]]. Si es para repasar un quiz/examen que se repite periódicamente y el usuario quiere el repaso guardado + una suite interactiva, aplicar [[Sistema/skills/quiz-repaso/SKILL|quiz-repaso]] en su lugar.
2. Si es sobre un proyecto, usar solo `/Proyectos/{proyecto}/` como contexto — no mezclar stacks entre proyectos.
3. Para cualquier tarea de código, aplicar [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]].
4. Para cualquier tarea de diseño de UI/UX, aplicar [[Sistema/skills/enterprise-ui-ux-design/SKILL|enterprise-ui-ux-design]].
5. Para QA, test cases o bug reports, aplicar [[Sistema/skills/qa-testing-practices/SKILL|qa-testing-practices]].
6. Para documentación técnica (README, docs, comentarios), aplicar [[Sistema/skills/professional-technical-docs/SKILL|professional-technical-docs]].
7. Para cualquier operación de git (branch, commit, PR), aplicar [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] — el código de ticket sale siempre de [[Sistema/tickets|tickets.md]], nunca se inventa mirando el log.
8. Antes de crear una nota nueva, buscar si ya existe algo relacionado — no duplicar.
8.1. Si aparece un documento nuevo en `Sistema/inbox/` (PDF, doc, foto de apuntes, propio o subido por Hermes), aplicar [[Sistema/skills/document-intake/SKILL|document-intake]] para convertirlo en nota(s) del curso correspondiente.
8.1.1. Si aparece `Sistema/inbox/checkin-{fecha}-revisar.md` (lo deja el cron de las 22:00 de Hermes cuando no pudo mapear el avance de una subtarea de sesión a un entregable existente), seguir la sección "Qué hacer si aparece..." de [[Sistema/hermes-checkin-22h-spec|hermes-checkin-22h-spec.md]] — no es un documento para `document-intake`, es un archivo de enrutamiento efímero que se borra tras incorporar su contenido a `Cursos/{curso}/entregables/{tema}.md`.
8.2. Si el usuario pide ayuda para trabajar en una tarea específica (ir respondiendo un reporte, escribiendo una entrada de diario, avanzando un proyecto), el resultado va a `Cursos/{curso}/entregables/{tema-en-kebab-case}.md` — nunca en `apuntes/`, que es material del profesor. Antes de empezar, buscar si ya existe la nota de instrucciones/rúbrica en `apuntes/` y usarla como referencia de qué se está evaluando. Frontmatter: `curso`, `tema`, `fecha`, `tipo: entregable`, `entregable_de` (wikilink a la nota de instrucciones si existe), `estado: borrador` o `entregado`, `tags`. Ir marcando contra la rúbrica qué está cubierto y qué falta a medida que se avanza, no solo al final.
9. Nunca borrar notas — si algo queda obsoleto, moverlo a una carpeta `_archivo/` dentro del curso/proyecto correspondiente.
10. Al agregar una fecha de entrega nueva en `entregas.md`, ofrecer sincronizarla al calendario (MCP de Google Calendar ya conectado) o a Todoist (MCP ya conectado) según corresponda. Actualizar también el frontmatter del mismo `entregas.md` (`curso: {nombre}` + `entregas_pendientes`, agregar/quitar/marcar entregado) para que [[Dashboard]] (Dataview) se mantenga al día — si ese curso todavía no tiene el bloque, crearlo. El campo `curso` es obligatorio (todos los `entregas.md` se llaman igual, sin ese campo Dataview no los puede distinguir en la tabla).
11. Para tareas grandes (cerrar un ticket, preparar un PR), considerar usar los subagentes en `Sistema/agents/` (code-reviewer, qa-checker, docs-writer) en vez de hacer todo en una sola pasada — ver [[Sistema/agents/README|agents/README]].

## Convención de commits/PRs para este vault

Si el vault mismo se versiona con Git (recomendado), usar el mismo formato de `gitflow-scrum`: `docs(CURSO-n): agregar apuntes de unidad 3`.
