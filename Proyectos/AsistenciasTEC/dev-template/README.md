# Dev process & best-practices template

A self-contained package meant to be copied into any project repo (Next.js/React/TypeScript stack) to fill the gaps a typical starter/base repo leaves open: security review, linked architecture/process/requirements docs, a concrete git branching model, and a PR format. Not tied to any specific project — every project-specific detail is a placeholder to fill in, not invented content.

## What's in here and why

Most starter repos already cover code-level best practices (naming, component architecture, constants, linting, testing) through their own project-specific skills. What's usually still missing is process and security:

| File/folder | What it is | Why it's usually missing |
|---|---|---|
| `ARCHITECTURE.md`, `SCRUM.md`, `USER_STORIES.md` | Templates (structure only, no invented content) for architecture, Scrum process, and user stories as a linked trio | No doc of this kind exists — without it there's nowhere to record decisions or trace a story through to a PR |
| `GITFLOW.md` | A branching model built around milestone-based delivery branches (ticket → develop → release-N → qa-fix → main), PR status labels synced with the tracker (one `in progress` per person, dependent stories `on hold` instead of stacked branches), plus a PR format | Teams that deliver in milestones (not continuous deploy) often improvise this ad hoc, with no written reference |
| `.github/workflows/gitflow.yml` | CI check enforcing `GITFLOW.md`: branch combinations, title format, exactly one status label, one `in progress` PR per author, and a `qa-gate` that stays red until `qa accepted` | Written rules drift; a red check doesn't |
| `.github/PULL_REQUEST_TEMPLATE.md` | The same PR format as a GitHub-native template, pre-filled automatically when opening a PR | Avoids everyone inventing their own PR description format |
| `.claude/agents/security-reviewer.md` | Subagent reviewing auth, role-based access, inputs, and secrets before a PR | Security review is rarely automated even when code-quality review is |
| `.claude/agents/code-reviewer.md` | Subagent reviewing structure/naming/scope against `clean-code-practices`, and checking a PR maps to exactly one ticket | Complements whatever project-specific code skills the repo already has |
| `.claude/agents/qa-checker.md` | Subagent checking test coverage (happy path + negative + boundary) before merge | Closes the QA gap when there's no dedicated QA automation yet |
| `.agents/skills/security-practices/` | TypeScript/Next.js security skill (OWASP-adjacent: auth, RBAC, input validation, secrets, DB rules) used by `security-reviewer` | — |
| `.agents/skills/clean-code-practices/` | General clean-code/repo-structure skill used by `code-reviewer` | — |
| `.agents/skills/qa-testing-practices/` | QA skill (test cases, bug reports, test plans, Page Object Model) used by `qa-checker` | — |
| `.agents/skills/project-structure/` | Folder layout skill: `app/` holds routing only, shared folders (`components/`, `constants/`, `store/`, ...) sit next to it, `@/<folder>` imports, project-relative paths in every agent/docs file, plus a step-by-step procedure to migrate a repo that nested them inside `app/` | Starter repos often drop shared folders inside `app/`, and their agent docs then teach that wrong path to every agent |
| `.agents/skills/gitflow/` | The agent procedure for `GITFLOW.md`: exact commands and checks before any branch, PR, label change, or merge | Agents follow skills they're told to load, not human docs; without it they open PRs with no label or stack branches |
| `.agents/skills/spec-driven-development/` | `specs/SPEC.md` (what/why) + `specs/plan.md` (how) + `specs/tasks.md` (steps), colocated in each feature folder, written before coding and used to validate | Starter repos often ask for a spec but not the plan and task list, which is where decisions and blockers get written down |
| `.agents/skills/code-defense/` | Coach mode: plan one's own sprint stories, build them in explainable steps, write a sprint study guide, and rehearse a code review (explain, navigate, live changes, trick questions) | For teams where each person must defend AI-assisted code they deliver; nothing else prepares for that |
| `.agents/skills/scrum-architecture-docs/` | Skill explaining how to keep `ARCHITECTURE.md`/`SCRUM.md`/`USER_STORIES.md` in sync | — |
| `PROMPT-INTEGRATION.md` | A ready-to-paste prompt for Claude Code, to run once this package is copied into a real repo | Integration (deduplicating against what the repo already has, filling in real context) is a task worth delegating explicitly, not doing silently |

## How to use it

1. Copy every folder/file here to the same relative path at the root of the target repo (`.claude/agents/`, `.agents/skills/`, `.github/`, and the root `.md` files).
2. Open Claude Code in that repo and paste the prompt from `PROMPT-INTEGRATION.md`. It handles deduplicating against skills the repo already has, moving any shared folders out of `app/` and fixing the paths in the repo's existing agent docs (per `project-structure`), registering everything in the repo's own agent contract file (`AGENTS.md`/`CLAUDE.md`, whatever the repo uses), and filling in `ARCHITECTURE.md`/`SCRUM.md`/`USER_STORIES.md` by asking for real project context instead of inventing it.

## Recommended tooling (optional, depends on the project)

- **Database MCP, registered per repo.** If the project's database has an MCP server (Supabase, Postgres, etc.), register it from inside the repo with **local** scope (`claude mcp add --scope local ...`), so it is available whenever Claude Code is opened in that repo, stays private to your machine, and doesn't add a config file to the shared repo. Each person authenticates with their own account (`/mcp` → the server → Authenticate). Use project scope (a committed `.mcp.json`) only if the whole team agrees to share the config.
- **Tracker access for the agent** (Jira, Linear, etc.), so it can create tickets and move them in sync with PR labels as `gitflow` requires.

## What this intentionally does NOT include

- Any code-level skill a project-specific starter repo is likely to already have (component architecture, constants, state-management conventions, linting) — those aren't duplicated here.
- Any project name, team name, or company-specific detail — every placeholder (`{Project Name}`, `{TICKET-ID}`, role names) is generic on purpose so this can be reused across projects.
- Pre-filled `ARCHITECTURE.md`/`SCRUM.md`/`USER_STORIES.md` content — they ship empty (structure only) so nobody accidentally ships invented requirements.
