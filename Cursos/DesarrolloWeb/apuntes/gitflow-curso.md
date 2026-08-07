---
curso: DesarrolloWeb
tema: Flujo de git exigido por el profesor
fecha: 2026-08-07
tipo: apunte
fuente: _fuentes/DesarrolloWeb_gitflow-curso_2026-08-07.png
tags: [gitflow, git, ramas, entregables, qa, hotfix]
---

# Flujo de git exigido por el profesor — Desarrollo Web

Ver también: [[Cursos/DesarrolloWeb/temario]] · [[Cursos/DesarrolloWeb/apuntes/introduccion-desarrollo-web]]

> **Importante:** este es el flujo de ramas que el profesor exige para el **proyecto del curso** (repositorio del cliente/proyecto de Desarrollo Web) — no tiene relación con [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]], que es la convención interna de *este vault* para versionar las notas de estudio. No mezclar ambos flujos.

## Ramas del diagrama

| Rama | Rol |
|---|---|
| `Master` | Rama principal / producción del proyecto |
| `Develop` | Rama de integración de desarrollo |
| `Ticket 1` (y sucesivos `Ticket N`) | Rama de trabajo para una tarea/ticket puntual |
| `Entregable 1` (y sucesivos `Entregable N`) | Rama de una entrega formal del curso |
| `QA Fix` | Rama para corregir hallazgos de QA sobre un entregable |
| `Hotfix` | Rama para corrección urgente directa sobre producción |

## Flujo (según el diagrama)

1. **`Develop` nace de `Master`.**
2. Cada tarea se trabaja en su propia rama **`Ticket N`**, creada desde `Develop`; al terminar, `Ticket N` se fusiona de vuelta a `Develop`.
3. Cuando toca preparar una entrega, `Develop` fusiona/da origen a **`Entregable N`**.
4. Si QA encuentra problemas en `Entregable N`, se crea **`QA Fix`** desde esa rama; al corregir, `QA Fix` se fusiona de vuelta a `Entregable N`.
5. El `Entregable N` ya corregido y aprobado se fusiona a **`Master`**.
6. Si aparece un problema urgente ya en producción, se crea **`Hotfix`** desde `Master`; al corregirlo, `Hotfix` se fusiona de vuelta a `Master`.

```
Hotfix ⇄ Master ⇄ Develop ⇄ Ticket N
                    ↓
              Entregable N ⇄ QA Fix
```

## Notas de aplicación

- Dos entregas están previstas durante el curso (ver [[Cursos/DesarrolloWeb/apuntes/introduccion-desarrollo-web]]), por lo que en la práctica habrá al menos `Entregable 1` y `Entregable 2`.
- El diagrama no detalla convención de nombres de rama/commit (ej. prefijo de ticket) — si el profesor la especifica más adelante, documentarla aquí.
