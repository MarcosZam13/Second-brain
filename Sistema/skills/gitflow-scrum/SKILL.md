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

## 2. Ticket/requirement codes

Every piece of work needs a code before a branch exists. If the professor/team doesn't provide a ticketing system, define a lightweight convention per project up front, e.g.:

- `TACHA-{n}` for Tacha
- `GYM-{n}` for GymBase
- `{COURSE-ACRONYM}-{n}` for university projects (e.g. `WEB-03` for requirement 3 of the web dev course)

Keep a simple table in the repo (`docs/requirements.md` or the project's vault page) mapping code → requirement description → status. This is what makes the branch/commit codes meaningful instead of arbitrary numbers.

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
- PR merges only into `develop`/`main` — never work-in-progress branch into another WIP branch.
- Even working solo, open the PR anyway before merging — it's the checkpoint where Claude Code (or a teammate) reviews before it lands. This is also the habit that transfers directly to a job.
- Squash-merge when the branch has messy intermediate commits; keep them separate when each commit is independently meaningful.

## 5. QA-specific flow (when the course/project calls for it)

- `qa/{TICKET-ID}-...` branches hold test plans, test cases, or QA scripts tied to the same ticket as the feature they're validating.
- Link the QA branch/PR back to the feature PR it covers.
- Bug found during QA → new ticket (`fix/{TICKET-ID}`), not a silent patch onto the original feature branch after merge.

## 6. Applying this in practice

When asked to help with git operations under this skill:
1. Ask for (or infer from context) the ticket/requirement code before naming a branch or writing a commit — don't invent branches without one.
2. Default to the short-lived branch model above unless the user explicitly says the course requires full GitFlow with `release/*` branches — in that case, follow the required model but still enforce the ticket-code and commit-message conventions on top of it.
3. When reviewing a PR, check first that the title/commits map cleanly to one ticket — flag scope creep before line-level comments.
