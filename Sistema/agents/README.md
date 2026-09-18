# Subagentes — cómo activarlos en un proyecto

Ver también: [[Sistema/CLAUDE|CLAUDE.md]] · [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]] · [[Sistema/skills/qa-testing-practices/SKILL|qa-testing-practices]] · [[Sistema/skills/professional-technical-docs/SKILL|professional-technical-docs]] · [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] · [[Sistema/skills/security-practices/SKILL|security-practices]]

Estas plantillas viven acá como referencia central. Para usarlas en un proyecto real (Tacha, GymBase, CaneleApp, o un repo de un curso):

1. Copiá la(s) plantilla(s) que necesités a `.claude/agents/` dentro del repo del proyecto.
2. Claude Code las detecta automáticamente y las invoca cuando el contexto encaja (o se las podés pedir explícitamente: "usá el subagente qa-checker sobre esto").

## Flujo típico al cerrar un ticket

```
1. Implementás la feature (Claude Code + skill clean-code-practices activo)
2. Antes de abrir el PR:
   → [[Sistema/agents/code-reviewer|code-reviewer]] revisa estructura/naming/scope
   → [[Sistema/agents/qa-checker|qa-checker]] verifica que haya casos de prueba (happy/negativo/límite)
   → [[Sistema/agents/security-reviewer|security-reviewer]] revisa auth/permisos/inputs/secrets si la feature los toca
   → [[Sistema/agents/docs-writer|docs-writer]] actualiza README/docs si hace falta
3. Abrís el PR siguiendo el formato de gitflow-scrum
```

Podés pedirle a Claude Code que los corra en paralelo ("revisá esto con code-reviewer, qa-checker, security-reviewer y docs-writer antes de que abra el PR") — cada uno trabaja en su propio contexto y te devuelve su reporte por separado. `security-reviewer` vale la pena correrlo siempre que la feature toque login, permisos por rol, un formulario nuevo, o variables de entorno — no en cada PR trivial.

## Agregar un nuevo subagente

Mismo patrón que un skill: un archivo `.md` con frontmatter (`name`, `description`, `tools`) y el system prompt del subagente. Mantenerlo enfocado en una sola responsabilidad — no armar un subagente que "hace de todo".
