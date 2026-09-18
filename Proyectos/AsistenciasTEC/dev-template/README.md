# Dev process & best-practices template

A self-contained package meant to be copied into any project repo (Next.js/React/TypeScript stack) to fill the gaps a typical starter/base repo leaves open: security review, linked architecture/process/requirements docs, a concrete git branching model, and a PR format. Not tied to any specific project — every project-specific detail is a placeholder to fill in, not invented content.

## What's in here and why

Most starter repos already cover code-level best practices (naming, component architecture, constants, linting, testing) through their own project-specific skills. What's usually still missing is process and security:

| File/folder | What it is | Why it's usually missing |
|---|---|---|
| `ARCHITECTURE.md`, `SCRUM.md`, `USER_STORIES.md` | Templates (structure only, no invented content) for architecture, Scrum process, and user stories as a linked trio | No doc of this kind exists — without it there's nowhere to record decisions or trace a story through to a PR |
| `GITFLOW.md` | A branching model built around milestone-based delivery branches (ticket → develop → release-N → qa-fix → main), plus a PR format | Teams that deliver in milestones (not continuous deploy) often improvise this ad hoc, with no written reference |
| `.github/PULL_REQUEST_TEMPLATE.md` | The same PR format as a GitHub-native template, pre-filled automatically when opening a PR | Avoids everyone inventing their own PR description format |
| `.claude/agents/security-reviewer.md` | Subagent reviewing auth, role-based access, inputs, and secrets before a PR | Security review is rarely automated even when code-quality review is |
| `.claude/agents/code-reviewer.md` | Subagent reviewing structure/naming/scope against `clean-code-practices`, and checking a PR maps to exactly one ticket | Complements whatever project-specific code skills the repo already has |
| `.claude/agents/qa-checker.md` | Subagent checking test coverage (happy path + negative + boundary) before merge | Closes the QA gap when there's no dedicated QA automation yet |
| `.agents/skills/security-practices/` | TypeScript/Next.js security skill (OWASP-adjacent: auth, RBAC, input validation, secrets, DB rules) used by `security-reviewer` | — |
| `.agents/skills/clean-code-practices/` | General clean-code/repo-structure skill used by `code-reviewer` | — |
| `.agents/skills/qa-testing-practices/` | QA skill (test cases, bug reports, test plans, Page Object Model) used by `qa-checker` | — |
| `.agents/skills/scrum-architecture-docs/` | Skill explaining how to keep `ARCHITECTURE.md`/`SCRUM.md`/`USER_STORIES.md` in sync | — |
| `PROMPT-INTEGRATION.md` | A ready-to-paste prompt for Claude Code, to run once this package is copied into a real repo | Integration (deduplicating against what the repo already has, filling in real context) is a task worth delegating explicitly, not doing silently |

## How to use it

1. Copy every folder/file here to the same relative path at the root of the target repo (`.claude/agents/`, `.agents/skills/`, `.github/`, and the root `.md` files).
2. Open Claude Code in that repo and paste the prompt from `PROMPT-INTEGRATION.md`. It handles deduplicating against skills the repo already has, registering everything in the repo's own agent contract file (`AGENTS.md`/`CLAUDE.md`, whatever the repo uses), and filling in `ARCHITECTURE.md`/`SCRUM.md`/`USER_STORIES.md` by asking for real project context instead of inventing it.

## What this intentionally does NOT include

- Any code-level skill a project-specific starter repo is likely to already have (component architecture, constants, state-management conventions, linting) — those aren't duplicated here.
- Any project name, team name, or company-specific detail — every placeholder (`{Project Name}`, `{TICKET-ID}`, role names) is generic on purpose so this can be reused across projects.
- Pre-filled `ARCHITECTURE.md`/`SCRUM.md`/`USER_STORIES.md` content — they ship empty (structure only) so nobody accidentally ships invented requirements.
