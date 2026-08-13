---
proyecto: Tacha
tema: Flujo de Git, labels de PR y tablero (Jira)
fecha: 2026-08-12
tipo: documentacion
estado: definido por Marcos para arrancar el repo — a presentar al equipo
tags: [gitflow, github, jira, pr-template, tacha]
---

# Flujo de Git, labels de PR y tablero — Tacha

Ver también: [[Proyectos/Tacha/README|README]] · [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] · [[Sistema/tickets|tickets.md]]

Repo de código: `MarcosZam13/tacha` (privado, GitHub). Este documento es lo que se le explica al resto del equipo cuando se una al repo.

## 1. Branching y tickets

**No** se usa el modelo genérico de [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] tal cual — Tacha es el proyecto del curso de Desarrollo Web, y el profesor exige un modelo de ramas específico (documentado en [[Cursos/DesarrolloWeb/apuntes/gitflow-curso|gitflow-curso.md]]). Lo que corre en el repo real es ese modelo, adaptado a kebab-case y con código de ticket para trazabilidad:

```
main                              → producción (equivalente a "Master" del diagrama del profesor)
develop                           → integración de desarrollo, nace de main — rama default del repo
ticket/TACHA-{n}-descripcion      → tarea puntual, nace de develop, vuelve a develop
entregable-{n}                    → una entrega formal del curso (entregable-1, entregable-2...), nace de develop
qa-fix/TACHA-{n}-descripcion      → corrige hallazgos de QA sobre un entregable, nace de entregable-{n}, vuelve a entregable-{n}
hotfix/TACHA-{n}-descripcion      → corrección urgente sobre producción, nace de main, vuelve a main
```

El código de ticket sale de [[Sistema/tickets|tickets.md]] (prefijo `TACHA`, ya registrado) mientras el equipo no tenga Jira operativo; en cuanto Jira esté armado (sección 4), el número de ticket pasa a ser la clave de la historia en Jira (ej. `TACHA-14`) y `tickets.md` deja de ser la fuente para este proyecto — se sigue usando solo para los cursos del vault.

## 2. Labels de PR (estado del branch)

Todo PR lleva exactamente un label de estos cinco, y se actualiza a mano según avanza:

| Label | Significado | Color sugerido |
|---|---|---|
| `in progress` | Se sigue trabajando, no listo para revisión | `#FBCA04` (amarillo) |
| `waiting qa` | Código completo, esperando que QA lo tome | `#0E8A16` (verde) |
| `qa accepted` | QA probó y aprobó — listo para merge | `#0052CC` (azul) |
| `qa denied` | QA encontró problemas — vuelve al autor | `#D93F0B` (naranja) |
| `on hold` | Bloqueado por algo externo (dependencia, decisión pendiente) | `#B60205` (rojo) |

Flujo esperado: `in progress` → `waiting qa` → (`qa accepted` → merge) o (`qa denied` → vuelve a `in progress`). `on hold` puede aplicarse desde cualquier estado.

Ya están creados en el repo (`gh label list` para verificar).

## 3. Plantilla de PR

Vive en `.github/pull_request_template.md` del repo, se autocompleta al abrir cualquier PR:

```markdown
## What does this PR do?


## How should this be manually tested?


## Screenshot


## Developer Notes


## Ticket


## Assignee


## Reviewer

```

Reglas:
- El título del PR sigue el mismo formato de `gitflow-scrum`: `feat(TACHA-14): descripción corta`.
- **Ticket** enlaza a la historia de Jira (o al ticket de `tickets.md` mientras Jira no esté listo).
- **Assignee** = quien hizo el trabajo. **Reviewer** = a quién le toca revisar (rotar entre el equipo, no siempre la misma persona).

## 4. Tablero (Jira) — pendiente de creación manual

No hay integración de Jira disponible en este entorno todavía, así que este paso lo hace alguien del equipo directamente en [jira.com](https://www.atlassian.com/software/jira) (proyecto tipo *Team-managed software*, plantilla Kanban o Scrum). Columnas que reflejan 1:1 los labels de PR de la sección 2:

```
To Do → In Progress → Waiting QA → (QA Denied → vuelve a In Progress) → QA Accepted → Done
```

`On Hold` no es columna — es un estado/flag que se marca sobre la tarjeta sin moverla de columna (evita perder el progreso visual).

Una vez creado el proyecto en Jira:
1. Actualizar esta sección con la URL del proyecto y la clave (ej. `TACHA`).
2. El equipo pasa a escribir historias de usuario y requerimientos ahí, partiendo del documento de producto ([[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] → sección 4, Requerimientos funcionales).
3. Los PRs enlazan la clave de Jira en el campo **Ticket** de la plantilla (sección 3).

## 5. Estado

Repo creado y pusheado: [github.com/MarcosZam13/tacha](https://github.com/MarcosZam13/tacha) (privado). Labels de PR ya creados. Plantilla de PR y `CONTRIBUTING.md` ya en el repo.

## 6. Pendiente

- [ ] Invitar a los 6 compañeros como colaboradores del repo (`gh repo add-collaborator MarcosZam13/tacha {usuario}` o desde GitHub → Settings → Collaborators) — pendiente hasta tener sus usuarios de GitHub
- [ ] Crear el proyecto en Jira y volver a esta nota con la URL/clave
- [ ] Primera reunión de equipo: confirmar o reabrir Next.js/Tailwind (definidos unilateralmente, ver [[Proyectos/Tacha/documentacion-v1#10. Pendientes de definición|sección 10 del documento]]) y cerrar el resto de pendientes
