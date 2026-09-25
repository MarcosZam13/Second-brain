---
name: spec-driven-development
description: Specify before coding. Every new feature or non-trivial behavior change gets three colocated files in the feature folder, `specs/SPEC.md` (what and why), `specs/plan.md` (how), and `specs/tasks.md` (ordered steps), written before implementation and used to validate the result. Use when starting a feature, a story, or a behavior change, and when reviewing whether finished work matches what was agreed.
---

# Spec-Driven Development: SPEC, plan, tasks

If the repo already has its own architecture skill that defines specs, that skill wins; this one only fills what it leaves out (usually `plan.md` and `tasks.md`).

## When

Required for: new features or feature folders, behavior changes (flows, validation, permissions, data loading), new data wiring (tables, endpoints, state), refactors that change user-visible behavior. Skip for purely visual tweaks with no behavior change.

## Where

Colocated with the feature, never in a global docs folder:

```
components/<feature>/specs/
  SPEC.md    what and why (the contract)
  plan.md    how: files, data, flow, decisions
  tasks.md   ordered implementation steps
```

The three files ship in the same PR as the feature's code.

## Flow: Specify → Plan → Tasks → Implement → Validate

### 1. `SPEC.md`: what and why

No implementation detail unless it is a hard constraint.

```md
# <Feature / change name>

Stories: <ticket links>

## Intent
Who is this for and what outcome should they get?

## In scope
## Out of scope (and why)
## Requirements
## Edge cases and errors
## Constraints
Skills that apply; existing components/services/state to reuse.

## Acceptance criteria
- [ ] (copied from the story, one checkbox each, grouped by story if several)
```

### 2. `plan.md`: how

Derived from the spec plus the repo's skills. Contains:

- **Files**: tree of files to create or touch, one line of responsibility each.
- **Data**: tables, columns, access rules, endpoints/RPCs used or created. Write down anything that still has to be verified against the real database or API, instead of assuming it.
- **Flow**: the path of one user action through the files.
- **Decisions**: table `Decision | Alternative | Why this one`. The "why" names a concrete consequence ("two tabs adding at once don't duplicate rows"), never "best practice".
- **New dependencies**, with the reason.

### 3. `tasks.md`: ordered steps

- A checklist of small units, in build order (constants → types → data → logic → presentation → route is a good default).
- Mark blocked tasks and what they are waiting on (access, another story, a decision).
- If the feature spans several tickets, group tasks by ticket; each ticket is still its own branch and PR (see `GITFLOW.md`).

### 4. Implement

Task by task, ticking `tasks.md` as you go.

### 5. Validate

Against the acceptance criteria in `SPEC.md`, not against a reinterpreted version of the request. If requirements change midway, update `SPEC.md` first (and `plan.md` if the how changes), then the code.

## Review checklist

- [ ] `SPEC.md`, `plan.md`, and `tasks.md` exist in the feature's `specs/` folder
- [ ] Out-of-scope items say why
- [ ] `plan.md` has a decisions table with concrete reasons
- [ ] Every acceptance criterion in `SPEC.md` is checked and was verified, not assumed
