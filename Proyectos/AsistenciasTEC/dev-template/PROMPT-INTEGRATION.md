# Integration prompt — paste into Claude Code inside the target repo

Usage: copy this package's contents (`ARCHITECTURE.md`, `SCRUM.md`, `USER_STORIES.md`, `GITFLOW.md`, `.github/`, `.claude/`, `.agents/`) to the root of the real project repo, open Claude Code there, and paste the prompt below as-is (fill in the `{}` placeholders first).

---

I just copied a dev-process/best-practices package into the root of this repo: `ARCHITECTURE.md`, `SCRUM.md`, `USER_STORIES.md`, `GITFLOW.md`, `.github/PULL_REQUEST_TEMPLATE.md`, `.github/workflows/gitflow.yml`, `.claude/agents/{security-reviewer,code-reviewer,qa-checker}.md`, and `.agents/skills/{security-practices,clean-code-practices,qa-testing-practices,scrum-architecture-docs,project-structure,gitflow,spec-driven-development,code-defense}/SKILL.md`. This repo is for **{project name}** ({one-sentence description of what the project is}). If this repo already has its own agent contract file (`AGENTS.md`, `CLAUDE.md`, or similar) with a skill catalog, I need you to integrate the new material into it without duplicating what's already there, and get the process docs ready to fill in with real project context.

Do this in order, without committing or pushing anything yet — I want to review the diff first:

1. **Read first.** Read the repo's existing agent contract file (`AGENTS.md`/`CLAUDE.md`, whichever it uses) and every `.agents/skills/*/SKILL.md` that already existed before I copied anything, so you know what's already covered.

2. **Deduplicate.** The skills I just copied (`clean-code-practices`, `qa-testing-practices`) are generic versions from another source — the repo may already cover most of that ground with more specific skills (naming/component conventions, constants, state management, unit-testing standards, end-to-end testing). Decide what to do in each case: if a copied skill is purely redundant, delete it and update `.claude/agents/code-reviewer.md`/`qa-checker.md` to reference the repo's real skills instead of the generic one. If it adds something the repo doesn't have (e.g. bug-report or test-plan templates), keep only that part, not the whole file. `spec-driven-development` often overlaps with an existing component-architecture skill that already asks for `specs/SPEC.md`: in that case keep the repo's skill as the source of truth and merge in only what it lacks (usually `plan.md` and `tasks.md`), then delete the copied one. `security-practices`, `scrum-architecture-docs`, `project-structure`, `gitflow` and `code-defense` should be genuinely new — if any has an equivalent already, flag it before touching it.

   Also check **declared vs. real**: for every library, pattern or tool the contract file or its skills say the project uses (a data-fetching library, a state store, a test runner), confirm it is actually in `package.json` and used in the code. List every mismatch for me; don't silently build on either version.

3. **Fix the folder layout (`project-structure`).** Read `.agents/skills/project-structure/SKILL.md`. Then:
   - List every folder under `app/` that is not routing (e.g. `app/components`, `app/constants`, `app/providers`, `app/services`, `app/store`, `app/types`, `app/utils`, `app/hooks`). Show me the list before moving anything.
   - After I confirm, follow section 4 of that skill exactly: `git mv` each folder to the project root, rewrite `@/app/<folder>` imports to `@/<folder>`, check config files that reference paths, and run the type check, lint and build. Report the result of each one; if something fails, stop and show me the error instead of patching around it.
   - Rewrite every path in the repo's **existing** agent/docs files (`AGENTS.md`, `CLAUDE.md`, IDE bridge files, every pre-existing `.agents/skills/*/SKILL.md` and its `references/`, `README.md`) so none of them describes shared code under `app/`. Only change the paths, not the rules around them. All paths must be project-relative with forward slashes (no absolute or machine paths).
   - Add a short **Repository layout** section to the contract file (the tree from `project-structure` section 1, trimmed to the folders this repo really has) and a line saying all paths in docs are project-relative.
   - If the repo has no shared folders nested in `app/`, skip the move and just confirm the docs already match the layout.

4. **Register in the contract file.** Add a row for every skill that survives step 2 to the skill catalog in the repo's agent contract file — if it's not registered there, agents won't load it automatically.

5. **Update the "project snapshot"/project description** in the contract file with the real details I confirm below. **Don't invent** product name, stack, or roles I haven't given you explicitly — ask if something's unclear instead of assuming.

6. **Don't fill `ARCHITECTURE.md`/`SCRUM.md`/`USER_STORIES.md` with invented content.** They ship with structure/placeholders only, on purpose. Ask me for the real details (roles, confirmed stack, epics, sprints, user stories) and build the content with me, section by section — don't generate a fictional backlog just to "complete" the document.

7. **Confirm `.github/PULL_REQUEST_TEMPLATE.md` is in the right place** for GitHub to pre-fill it automatically on a new PR, and that the three subagents in `.claude/agents/` have valid frontmatter (`name`/`description`/`tools`).

8. **Wire up the git workflow.**
   - Set `TICKET_PREFIX` in `.github/workflows/gitflow.yml` to the tracker prefix I give below. If the repo already has a workflow doing some of these checks, merge instead of duplicating.
   - If the milestone branches in this team are not called `release-{N}` (e.g. `entregable-{N}`, `milestone-{N}`), rename them consistently in `GITFLOW.md`, `.agents/skills/gitflow/SKILL.md` and the workflow.
   - Show me the `gh label create` commands for the five status labels (`in progress`, `waiting qa`, `qa accepted`, `qa denied`, `on hold`) that don't exist yet; run them only after I confirm.
   - Ask me how the tracker models each state (especially whether "On Hold" is a real status or just a flag on the card) and make the label table in `GITFLOW.md` say exactly that.
   - Remind me to make the `gitflow` and `qa-gate` checks required in branch protection for `develop` and `main` (that's a repo setting, not a file).

9. When done, summarize: what got registered in the contract file, what got deleted/merged as redundant, the declared-vs-real mismatches, which folders moved and which doc paths got rewritten (plus the type check/lint/build results), what's pending for the git workflow, and what questions are still open to finish filling in `ARCHITECTURE.md`/`SCRUM.md`/`USER_STORIES.md`.

General rules: don't delete anything in the repo that didn't come from this package without asking me first, don't touch `.agents/skills/` that already existed except to remove exact duplicates or rewrite paths per step 3, and follow whatever pattern the repo's own contract file already defines (it's the source of truth; IDE-specific bridge files just point to it).

**Project context to fill in before pasting:**
- Project name:
- One-sentence description:
- Confirmed stack (if different from what the repo already has):
- Roles in the system:
- Ticket tracker in use (Jira, Linear, GitHub Issues, etc.) and ticket prefix:
- Name of the milestone/delivery branches (default `release-{N}`):
- Database and backend services in use (so the right MCP/tooling can be suggested, never assumed):
