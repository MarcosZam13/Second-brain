---
name: project-structure
description: Use this skill whenever creating a new top-level folder, deciding where a file lives, importing across folders, or writing a path inside an agent/docs file (AGENTS.md, CLAUDE.md, SKILL.md, README, ARCHITECTURE.md). Defines the Next.js App Router layout (app/ holds routing only; shared source folders sit next to app/, not inside it), the import alias rules, the rule that every path in docs is project-relative, and the step-by-step procedure to migrate a repo that nested shared folders inside app/.
---

# Project structure: routing in `app/`, shared code next to it

The standard: **`app/` contains routing and nothing else.** Every shared source folder (components, constants, store, services, types, utils, providers, hooks) sits at the project root, at the same level as `app/`. A developer or agent should be able to tell from a path alone whether a file is a route or reusable code.

Why this matters:

- In the App Router, every folder under `app/` is a potential route segment. Mixing `app/components/` or `app/store/` with route folders makes it impossible to tell at a glance which folders produce URLs and which don't, and it gets worse once route groups like `app/(auth)/login/` appear next to them.
- Agents copy the paths they see in docs. If one skill says `app/components/` and another says `components/`, agents will create files in both places. One layout, written the same way everywhere, prevents that drift.

## 1. Target layout

```
<project root>/
├── app/            Routing only: route groups, page.tsx, layout.tsx,
│                   loading/error/not-found, route handlers, globals.css, favicon
├── components/     Feature folders + shared UI bases
├── constants/      Global constants + barrel constants/index.ts
├── hooks/          Cross-feature hooks (only once a second feature needs one)
├── providers/      App-wide React providers (Redux, theme, session, ...)
├── services/       API / database / third-party service calls
├── store/          State store setup + global slices
├── types/          Shared cross-feature types
├── utils/          Shared cross-feature helpers
├── public/         Static assets
├── AGENTS.md / CLAUDE.md / README.md / ARCHITECTURE.md ...
└── tsconfig.json   "paths": { "@/*": ["./*"] }
```

Only create the folders the project actually needs. If the repo uses `src/`, the same rule applies one level down: `src/app/` is routing only and `src/components/`, `src/store/`, etc. are its siblings (alias `@/*` then points to `./src/*`).

### What is allowed inside `app/`

| Allowed | Not allowed |
|---|---|
| `page.tsx`, `layout.tsx`, `template.tsx`, `loading.tsx`, `error.tsx`, `not-found.tsx` | `components/`, `constants/`, `store/`, `services/`, `utils/`, `types/`, `hooks/`, `providers/` |
| Route groups `(group)/`, dynamic segments `[id]/`, route handlers `route.ts` | Feature UI with its own hooks/models/state |
| `globals.css`, `favicon.ico`, metadata files | Shared helpers "just for now" |
| A thin page-level view model next to the route file, if the project's architecture skill allows it | Anything imported by more than one route |

A route file stays thin: it composes a feature from `components/<feature>/` and passes route params. Page-specific UI still lives in a feature folder under `components/`, not beside the route.

## 2. Import rules

- Cross-folder imports go through the alias: `@/components/button/Button`, `@/constants`, `@/store`, `@/services`, `@/types/...`, `@/utils/...`.
- `@/app/...` is only valid for things that genuinely live in `app/` (and those are rarely imported from elsewhere). `@/app/components`, `@/app/constants`, etc. are always wrong.
- Relative imports (`./`, `../`) are fine for files that belong to the same feature folder. Follow whatever the repo's own code-style skill says for anything beyond that.

## 3. Paths inside agent and docs files

Every path written in `AGENTS.md`, `CLAUDE.md`, IDE bridge files, `.agents/skills/*/SKILL.md`, `README.md`, `ARCHITECTURE.md` and PR templates must be:

1. **Project-relative**, written from the project root: `components/<feature>/`, `constants/index.ts`, `.agents/skills/project-structure/SKILL.md`.
2. **Never absolute or machine-specific**: no `C:\Users\...`, `/home/...`, `~/...`, and no path that includes the name of the folder the repo was cloned into.
3. **Forward slashes only**, even when the team works on Windows.
4. **Consistent with section 1**: a doc must never describe `app/components/` (or any other shared folder under `app/`) as the place for code.

When the layout changes, the docs change in the same PR. A skill that still points at the old path is a bug, because agents will follow it.

## 4. Migrating a repo that nested shared folders inside `app/`

Do this on its own branch/ticket, not mixed with feature work, so the diff is only moves plus path rewrites.

1. **Inventory.** List the folders under `app/` that are not routing (see the table in section 1). Confirm nothing with the same name already exists at the root; if it does, stop and ask how to merge.
2. **Move with history.** `git mv app/<folder> <folder>` for each one, so `git log --follow` keeps working.
3. **Rewrite code imports.** Replace `@/app/<folder>` with `@/<folder>` in every `.ts`/`.tsx`/`.js`/`.jsx`/`.mdx` file. Then search for relative imports from files that stayed in `app/` (e.g. `app/layout.tsx` importing `./providers/...`) and switch them to the alias.
4. **Check config that references paths.** `tsconfig.json` `paths`, Tailwind `@source`/`content` globs, Storybook `stories` globs, test runner roots (Vitest/Jest), Playwright `testDir`, ESLint overrides, `.prettierignore`, CODEOWNERS.
5. **Rewrite the docs.** Search every agent/docs file (section 3) for `app/<folder>` and `@/app/<folder>` and update them. Add or update the repository layout section in the contract file (`AGENTS.md` or equivalent) and ARCHITECTURE.md section 4 so they describe the new layout.
6. **Verify.** A search for `@/app/(components|constants|providers|services|store|types|utils|hooks)` and for `app/(components|constants|...)` in docs must return nothing. Then run the type check (`npx tsc --noEmit`), lint, and `npm run build`. The migration is not done until all three pass.
7. **Warn the team.** Anyone with an open branch that touched the moved folders will get conflicts; mention it in the PR description so they rebase right after the merge.

## 5. Review checklist

- [ ] No shared source folder was created inside `app/` or inside a route group
- [ ] New imports use `@/<folder>/...`, never `@/app/<folder>/...`
- [ ] Route files are thin and delegate UI to `components/<feature>/`
- [ ] Every path added to a doc/skill is project-relative, forward-slashed, and matches the layout above
- [ ] If the layout changed, the contract file and ARCHITECTURE.md section 4 changed in the same PR
