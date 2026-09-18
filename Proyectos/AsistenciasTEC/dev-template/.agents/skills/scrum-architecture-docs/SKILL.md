---
name: scrum-architecture-docs
description: Use this skill when maintaining ARCHITECTURE.md, SCRUM.md, and USER_STORIES.md as a linked set. Defines how the three documents cross-reference each other so a reader gets full context — what the system is, how the team works, and what's being built — without duplicating content across files. Trigger this whenever an epic/story/sprint decision needs to be reflected in more than one of these files.
---

# Architecture + Scrum + User Stories — one linked document set

The problem this solves: architecture context, process (how the team works), and requirements (what's being built) are three different concerns that constantly get tangled into one bloated doc, or split with no cross-links so nobody can find anything. Keep them separate, keep them short, and make every cross-reference explicit.

The three files (`ARCHITECTURE.md`, `SCRUM.md`, `USER_STORIES.md`) live at the repo root — see those files directly for the current content and template structure.

## 1. Division of responsibility

| Doc | Answers | Does NOT contain |
|---|---|---|
| `ARCHITECTURE.md` | What is this system, how is it built, why these decisions | Sprint dates, individual story text |
| `SCRUM.md` | How the team works: roles, epics, sprints, Definition of Done, ceremonies | Detailed acceptance criteria, architecture rationale |
| `USER_STORIES.md` | Every user story + acceptance criteria, grouped by epic | Architecture decisions, sprint scheduling |

If content could go in two files, it lives in exactly one and the other links to it — never duplicate a paragraph across files, since they'll drift out of sync within a sprint.

## 2. Writing ARCHITECTURE.md §6 (decisions)

Document the **decision and the alternative rejected**, not just the structure the code already shows — the code already shows structure. Example: "why this field is nullable instead of a separate table," not "here is the folder layout."

## 3. Writing USER_STORIES.md

Use plain language: `As a {role}, I want {action}, so that {benefit}.` with Gherkin-lite acceptance criteria (`Given..., when..., then...`). No database field names or component-token jargon — this document also gets read by non-technical stakeholders.

## 4. Keeping the three in sync

- A new epic goes in `SCRUM.md` first (it needs a sprint/priority home) — then its stories get written in `USER_STORIES.md` referencing that epic's name exactly.
- An architecture decision that changes because of a specific story (e.g. a new role, a new entity) updates `ARCHITECTURE.md` §6 in the same PR that implements the story — don't let section 6 lag behind product decisions.
- Every story that reaches "Done" in `SCRUM.md`'s sprint table should have a ticket ID — if it doesn't, the traceability chain (story → ticket → branch → PR → commit, see `GITFLOW.md`) breaks.

## 5. Applying this in practice

1. If a section in any of the three files is still a placeholder, don't invent content (stack, roles, epics) that hasn't actually been confirmed by the team/stakeholders.
2. When a new epic or major scope decision lands, update `SCRUM.md`'s epic table before writing stories for it.
3. When writing a story, check whether it implies an architecture decision not yet in `ARCHITECTURE.md` §6 — flag it rather than silently leaving the doc stale.
4. Cross-reference `clean-code-practices` for repo structure conventions the architecture doc should reflect accurately, and `GITFLOW.md` for how stories map to ticket codes.
