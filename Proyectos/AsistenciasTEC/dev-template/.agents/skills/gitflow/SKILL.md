---
name: gitflow
description: Mandatory before ANY git or GitHub operation in this repo (create a branch, commit, push, open or edit a PR, change a label, merge, close a milestone). Turns GITFLOW.md into the exact commands and checks an agent must run, so PRs never open without a label, never stack on another ticket branch, and never leave the author with two PRs in progress.
---

# Gitflow for agents

The model (branches, labels, tracker states, PR format) is defined in `GITFLOW.md`; read it once per session before the first git operation. This skill is the procedure. If they disagree, fix `GITFLOW.md` and this skill in the same PR.

## Before creating a branch

1. The ticket exists in the tracker. Never invent a ticket ID; if there is none, ask the person to create it (or create it if you have tracker access and they asked you to).
2. The branch name and base come from the table in `GITFLOW.md`. A ticket branch always starts from an updated `develop`:
   ```bash
   git checkout develop && git pull && git checkout -b ticket/{TICKET-ID}-short-description
   ```
3. If the story depends on another story that is not merged into `develop` yet: **don't** branch from the other ticket branch. Tell the person the story goes `on hold` until the other one merges.
4. Uncommitted work from another ticket is committed on its own branch first (or left untouched); it never travels into the new branch.

## Before opening a PR (or moving one to `in progress`)

```bash
gh pr list --author "@me" --state open --json number,title,labels
```

- If another PR of the same person is `in progress`, it must move to `waiting qa` (complete) or `on hold` (paused) first, with its tracker transition. Ask before changing someone's PR state.
- Open with the label in the same command, and the base from `GITFLOW.md`:
  ```bash
  gh pr create --base develop --label "waiting qa" --title "{type}({TICKET-ID}): description" --body-file pr.md
  ```
  `waiting qa` if the code is complete and type check/lint/build pass; otherwise `in progress`.
- The body follows `.github/PULL_REQUEST_TEMPLATE.md` completely, with the real ticket link.
- Move the ticket in the tracker to the status matching the label, right away.

## Changing state

```bash
gh pr edit {number} --remove-label "in progress" --add-label "waiting qa"
```

One label replaces the other, and the tracker transition happens at the same moment.

## Merging

Only with `qa accepted` set by someone other than the author. An agent never sets `qa accepted` on its own work and never merges unless a person explicitly asks.

## Checklist before reporting a git operation as done

- [ ] Branch has an allowed prefix and a ticket ID that exists in the tracker
- [ ] Branch started from the base `GITFLOW.md` says (ticket branches: updated `develop`)
- [ ] PR targets the right base and has exactly one status label
- [ ] The author has at most one PR `in progress`
- [ ] Tracker status matches the label
- [ ] CI checks were looked at after pushing (`gh pr checks {number}`), and anything red other than `qa-gate` is reported
