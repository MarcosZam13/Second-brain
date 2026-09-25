---
name: gitflow-scrum
description: Use this skill whenever creating branches, writing commits, or opening pull requests for any coursework or personal project (Tacha, GymBase, CaneleApp, university team projects). Enforces a Scrum-style Git workflow where every branch, commit, and PR is tied to a requirement/ticket code, so history is traceable and reviewable — exactly what professors and companies check in interviews. Trigger this for any git operation: branch creation, commit messages, PR descriptions, or when the user asks "how should I branch/commit this."
---

# Git Workflow — Scrum-style, requirement-traceable

The goal: **anyone (professor, interviewer, teammate) can look at the branch name or the commit log and know exactly what requirement it maps to, without opening the code.** This is what gets checked in technical interviews and what makes a repo's history actually useful six months later.

## 1. Branching model

Base model: short-lived feature branches off `develop` (or `main` if the project has no staging branch), merged via PR. Avoid long-lived branches — they're the #1 source of painful merge conflicts and the industry has moved away from heavy GitFlow for small teams/solo projects in favor of this leaner version.

```
main        → production / what gets submitted or deployed
develop     → integration branch (only if the course/project requires staged releases)
feature/{TICKET-ID}-short-description
fix/{TICKET-ID}-short-description
qa/{TICKET-ID}-short-description        ← for QA-specific branches when the course asks for them
hotfix/{TICKET-ID}-short-description    ← urgent fix directly off main
```

Examples:
- `feature/TACHA-12-shopping-session-view`
- `fix/GYM-45-timezone-offset-bug`
- `qa/TACHA-12-cart-unification-tests`

Rules:
- One branch = one ticket/requirement. Never mix two unrelated requirements in the same branch.
- Max lifetime: 1-2 days. If it's growing longer, the ticket is probably too big — split it.
- Rebase or sync with `develop`/`main` before opening the PR, not after.

## 1b. Variante: modelo de Entregables (cuando el curso/empresa entrega por hitos)

Algunos cursos/empresas (Tacha, Asistencias TEC) usan un modelo distinto al de arriba: en vez de mergear features directo a `main`/`develop`, cada entrega/hito se congela en su propia rama de integración que pasa por un ciclo de QA antes de llegar a `main`.

```
main                        → versión entregada/en producción
  ↑ merge cuando QA aprueba la entrega
entregable-{N}               → integración de todo lo que va en esa entrega/hito, se corta de develop
  ↑ merge de fixes encontrados en QA de esa entrega
  qa-fix/{TICKET-ID}-...      → sale de entregable-{N}, arregla bugs encontrados al validar esa entrega, vuelve a entregable-{N}
develop                      → integración continua de todo lo que ya está terminado
  ↑ merge cuando el ticket está listo
  ticket/{TICKET-ID}-...      → una HU/tarea, sale de develop, vuelve a develop

hotfix/{TICKET-ID}-...        → sale de main directo (nunca pasa por develop/entregable), arregla algo urgente ya entregado, vuelve a main
```

Reglas de esta variante:
- `ticket/{TICKET-ID}-...` (o `feature/`/`fix/` según lo que pida el curso) sale y vuelve a `develop` — igual que el modelo base.
- Cuando se congela el alcance de una entrega, se corta `entregable-{N}` desde `develop`. De ahí en adelante, bugs encontrados en QA sobre esa entrega van en `qa-fix/{TICKET-ID}-...` cortado de `entregable-{N}`, nunca directo sobre `entregable-{N}`.
- `entregable-{N}` solo mergea a `main` cuando QA la aprueba — eso es lo que "entregar" significa en este modelo.
- `hotfix/*` es la única rama que sale de `main` directo, y es la única excepción a "todo pasa por develop primero" — para algo ya entregado que se rompe en producción y no puede esperar al siguiente ciclo.
- No asumir que este es el modelo del curso/empresa sin confirmarlo — preguntar o revisar qué documenta el profesor/equipo. Ver [[Sistema/aprendizaje/git-workflow-diagrama|git-workflow-diagrama.md]] para la comparación completa contra Gitflow clásico y trunk-based.

## 1c. Labels de estado de PR (van con la variante de Entregables)

Confirmado en Tacha (2026-09-24/25) y empaquetado en `Proyectos/AsistenciasTEC/dev-template/` (`GITFLOW.md` + skill `gitflow`). Si el repo tiene su propia skill de gitflow, esa manda; esto es la versión de referencia.

| Label | Significado | Estado en el tracker |
|---|---|---|
| `in progress` | Se está trabajando | En curso |
| `waiting qa` | Completo, CI en verde, esperando QA | Waiting QA |
| `qa accepted` | QA (otra persona) aprobó: se puede mergear | QA Accepted |
| `qa denied` | QA encontró problemas: vuelve al autor | QA Denied |
| `on hold` | Bloqueado, o esperando que se mergee otra historia | On Hold (en el Jira de Tacha es un **estado**, no un flag; verificar en cada tracker) |

Reglas:
- **La PR se abre al empezar la historia, no al terminarla.** Cada historia propia del sprint tiene PR desde el inicio: con la SPEC, o con un commit vacío (`git commit --allow-empty`). Así el equipo ve en GitHub quién trabaja en qué.
- **Exactamente un label**, puesto en el mismo `gh pr create --label ...`. Los labels se reemplazan, nunca se acumulan.
- **Una sola PR `in progress` por persona.** Las demás en `on hold`, `waiting qa`, `qa accepted` o `qa denied`. Revisar con `gh pr list --author "@me" --state open` antes de abrir o retomar una.
- **No apilar ramas.** Si B depende de A sin mergear, B nace igual de `develop` y queda `on hold`; cuando A se mergea, B se rebasea sobre `develop` y pasa a `in progress`.
- **Label y tarjeta siempre coinciden:** cada cambio de label va con su transición en el tracker en el mismo momento.
- **Solo se mergea con `qa accepted`**, puesto por alguien que no es el autor. Un agente nunca se pone `qa accepted` a sí mismo ni mergea sin que se lo pidan.
- Idealmente un check de CI lo hace cumplir (ramas, título, un label, una `in progress` por autor, y un `qa-gate` en rojo hasta `qa accepted`): ver `.github/workflows/gitflow.yml` del repo de Tacha o del `dev-template`.

## 2. Ticket/requirement codes

Every piece of work needs a code before a branch exists. `Sistema/tickets.md` is the single source of truth for which prefix belongs to which course/project and what the next free number is — check it before naming a branch or writing a commit, and update the "Último usado" column in the same commit that consumes the number. Never invent or guess a number by re-reading git log; the table is authoritative (log is only the fallback if the table has drifted).

If a course/project doesn't have a row yet in `Sistema/tickets.md`, add one first (3-5 letter prefix derived from the folder name) instead of picking an ad-hoc code.

## 3. Commit messages

Format:
```
{type}({TICKET-ID}): short imperative description

[optional body: why, not what]
```

Types: `feat`, `fix`, `docs`, `refactor`, `test`, `chore`, `style`, `perf`.

Examples:
```
feat(TACHA-12): add store selector to active shopping mode
fix(GYM-45): correct UTC to Costa Rica offset in payment timestamps
docs(WEB-03): add architecture diagram for milestone 2
```

Rules:
- Imperative mood ("add", not "added" or "adds").
- Subject line ≤ 72 chars. If you need more, put it in the body.
- One logical change per commit — don't bundle an unrelated fix into a feature commit "while you're at it."
- Never commit with messages like "fix stuff" or "wip" on a branch that's about to be reviewed — squash or rewrite before opening the PR if needed.

## 4. Pull requests

Every PR title mirrors the commit convention: `feat(TACHA-12): shopping session view`.

PR description template:
```markdown
## Ticket
{TICKET-ID} — link or reference to the requirement

## What changed
- 

## Why
(only if not obvious from the ticket)

## How to test
1. 

## Screenshots (if UI)
```

Rules:
- PR merges only into `develop`/`main` (or `entregable-{N}` under the variant in §1b) — never work-in-progress branch into another WIP branch.
- Even working solo, open the PR anyway before merging — it's the checkpoint where Claude Code (or a teammate) reviews before it lands. This is also the habit that transfers directly to a job.
- Squash-merge when the branch has messy intermediate commits; keep them separate when each commit is independently meaningful.

### 4b. PR format variant — Jira + Playwright projects (e.g. Asistencias TEC)

When the project tracks work in Jira and tests with Playwright, use this format instead of the generic one above — it's what gets checked against the ticket and the QA evidence directly:

```markdown
## Qué hace


## Cómo se testea


## Ticket de Jira
(link)

## Screenshots UI


## Screenshots Playwright

```

Rules specific to this variant:
- "Cómo se testea" gives manual repro steps even if Playwright tests exist — a reviewer without the branch checked out should be able to verify from the description alone.
- "Screenshots Playwright" means evidence from the actual test run (trace viewer screenshot, report, or terminal output showing pass), not a UI screenshot duplicated under a different heading.
- The Jira link is the ticket, never a paraphrase of it — the PR title still carries the ticket code per §3's commit convention.

## 5. QA-specific flow (when the course/project calls for it)

- `qa/{TICKET-ID}-...` branches hold test plans, test cases, or QA scripts tied to the same ticket as the feature they're validating.
- Link the QA branch/PR back to the feature PR it covers.
- Bug found during QA → new ticket (`fix/{TICKET-ID}`), not a silent patch onto the original feature branch after merge.

## 6. Applying this in practice

When asked to help with git operations under this skill:
1. Ask for (or infer from context) the ticket/requirement code before naming a branch or writing a commit — don't invent branches without one.
   In a repo using the Entregables variant, also apply §1c before opening or relabeling any PR: open it when the story starts, exactly one label, at most one `in progress` per person, tracker in sync.
2. Default to the short-lived branch model above unless the user explicitly says the course requires full GitFlow with `release/*` branches — in that case, follow the required model but still enforce the ticket-code and commit-message conventions on top of it.
3. When reviewing a PR, check first that the title/commits map cleanly to one ticket — flag scope creep before line-level comments.
