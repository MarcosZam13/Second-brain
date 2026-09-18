---
name: scrum-architecture-docs
description: Use this skill when creating or maintaining a project's ARCHITECTURE.md, SCRUM.md, and HU.md as a linked set (Asistencias TEC, or any team/company project that needs architecture context tied to the Scrum process). Defines how the three documents cross-reference each other so a reader gets full context — what the system is, how the team works, and what's being built — without duplicating content across files. Trigger this when setting up a new project's planning docs, or when an épica/HU/sprint decision needs to be reflected in more than one of these files.
---

# Architecture + SCRUM + HU — one linked document set

The problem this solves: architecture context, process (how the team works), and requirements (what's being built) are three different concerns that constantly get tangled into one bloated doc, or split with no cross-links so nobody can find anything. Keep them separate, keep them short, and make every cross-reference explicit.

## 1. Division of responsibility

| Doc | Answers | Does NOT contain |
|---|---|---|
| `ARCHITECTURE.md` | What is this system, how is it built, why these decisions | Sprint dates, individual HU text |
| `SCRUM.md` | How the team works: roles, épicas, sprints, Definition of Done, ceremonies | Detailed acceptance criteria, architecture rationale |
| `HU.md` | Every user story + acceptance criteria, grouped by épica | Architecture decisions, sprint scheduling |

If content could go in two files, it lives in exactly one and the other links to it — never duplicate a paragraph across files, since they'll drift out of sync within a sprint.

## 2. ARCHITECTURE.md template

```markdown
# Arquitectura — {Proyecto}

Ver también: [[SCRUM.md]] · [[HU.md]]

## 1. Qué es
(1-2 párrafos: qué hace el sistema, para quién, en qué contexto — no genérico, específico a este proyecto)

## 2. Roles y flujos principales
| Rol | Puede hacer |
|---|---|


## 3. Stack
| Capa | Tecnología | Por qué |
|---|---|---|


## 4. Estructura del repositorio
(mapa real de carpetas del repo, no un ejemplo genérico — actualizar cuando cambie)

## 5. Modelo de datos (alto nivel)
(entidades principales y relaciones — no el schema completo, eso vive en migraciones/código)

## 6. Decisiones de arquitectura y por qué
| Decisión | Alternativa descartada | Por qué |
|---|---|---|


## 7. Cómo se conecta con el proceso
Cada épica de [[SCRUM.md]] se descompone en HU/CA en [[HU.md]]; cada HU es trazable a un ticket (ver `gitflow-scrum` y `tickets.md`).

## 8. Riesgos / preguntas abiertas
```

Follow `professional-technical-docs` §3 for how to write section 6 — document the **decision and the alternative rejected**, not just the structure the code already shows.

## 3. SCRUM.md template

```markdown
# SCRUM — {Proyecto}

Ver también: [[ARCHITECTURE.md]] · [[HU.md]] · `tickets.md`

## Roles del equipo
| Persona | Rol (PO / Scrum Master / dev / QA) |
|---|---|


## Épicas
| ID | Nombre | HUs | Estado |
|---|---|---|---|


## Sprints
| Sprint | Fechas | Objetivo | HUs planificadas | Estado |
|---|---|---|---|---|


## Definition of Done
- [ ] Código implementado y sigue las skills de buenas prácticas del repo
- [ ] Tests (unitarios + al menos un caso E2E si la HU toca un flujo de usuario)
- [ ] PR abierto con el formato acordado y aprobado
- [ ] QA validó happy path + al menos un caso negativo/límite
- [ ] Documentación (README/ARCHITECTURE.md) actualizada si la HU cambia una decisión de arquitectura

## Ceremonias
(cadencia real acordada con el equipo/profesor — daily, review, retro — no una plantilla genérica de libro)
```

## 4. HU.md template

```markdown
# Historias de Usuario — {Proyecto}

Ver también: [[ARCHITECTURE.md]] · [[SCRUM.md]]

## Convención
`Como {rol}, quiero {acción}, para {beneficio}.`
Criterios de aceptación en Gherkin-lite: `Dado..., cuando..., entonces...`

Escribir en lenguaje neutral, sin nombres de campos de base de datos ni jerga de componentes — estos documentos también los puede leer alguien no técnico (profesor, product owner).

## {Nombre de la épica}

### HU-{n}: {título corto}
**Historia:** Como..., quiero..., para...
**Criterios de aceptación:**
- Dado..., cuando..., entonces...
**Ticket:** {PREFIJO}-{n}
**Sprint:**
**Estado:**
```

## 5. Keeping the three in sync

- A new épica goes in `SCRUM.md` first (it needs a sprint/priority home) — then its HUs get written in `HU.md` referencing that épica's name exactly.
- An architecture decision that changes because of a specific HU (e.g. a new role, a new entity) updates `ARCHITECTURE.md` §6 in the same PR that implements the HU — don't let section 6 lag behind product decisions (this is the exact failure mode that happened in Tacha's data-model section, tracked as a known risk).
- Every HU that reaches "Done" in `SCRUM.md`'s sprint table should have a ticket ID from `tickets.md` (see `gitflow-scrum`) — if it doesn't, the traceability chain (HU → ticket → branch → PR → commit) breaks.

## 6. Applying this in practice

1. If the project doesn't have these three files yet, create them from the templates above with placeholders only — don't invent content (stack, roles, épicas) that hasn't actually been confirmed by the professor/team/backlog.
2. When a new épica or major scope decision lands, update `SCRUM.md`'s épica table before writing HUs for it.
3. When writing a HU, check whether it implies an architecture decision not yet in `ARCHITECTURE.md` §6 — flag it rather than silently leaving the doc stale.
4. Cross-reference `professional-technical-docs` for writing voice/quality on the prose sections, and `gitflow-scrum` for how HUs map to ticket codes.
