---
name: clean-code-practices
description: Use this skill whenever writing, reviewing, or restructuring code for any project (university coursework or personal/commercial projects like GymBase, Tacha, CaneleApp). Covers naming conventions, function/module design, design patterns, repository structure, and scalability practices so that any future developer (including a stranger who has never seen the codebase) can understand and extend it without asking questions. Trigger this for any non-trivial code generation, code review, refactor, or "how should I structure this" question — not just when the user explicitly asks for "clean code."
---

# Clean Code & Repository Practices

The standard: **someone with zero context should be able to open this repo, read the structure, and understand what's going on within 5 minutes — without asking Marcos anything.** This is the bar interviewers and future teammates actually use when they open a candidate's code.

For Next.js/React/TypeScript projects specifically (the Desarrollo Web course project, GymBase, Tacha, CaneleApp), also apply [[Sistema/skills/nextjs-enterprise-patterns/SKILL|nextjs-enterprise-patterns]] and its companions ([[Sistema/skills/component-architecture/SKILL|component-architecture]], [[Sistema/skills/constants-standards/SKILL|constants-standards]], [[Sistema/skills/unit-testing-standards/SKILL|unit-testing-standards]]) on top of this — they cover feature-based architecture, ViewModel separation, magic-number/string elimination, and Page-Object-Model testing that this generic skill doesn't go into.

## 1. Naming

- Names say what something IS or DOES, never how it's implemented. `getActiveUsers()`, not `loopUsersAndFilter()`.
- Booleans read as yes/no questions: `isLoading`, `hasPermission`, `canEdit`.
- No abbreviations unless they're domain-standard (`id`, `url` are fine; `usrCfg` is not). Concrete forbidden list — any developer reading the code should never have to trace back to a declaration to know what it means:

  | Avoid | Use instead |
  |---|---|
  | `err` | `error` |
  | `res` | `response` |
  | `req` | `request` |
  | `cb` | `callback` |
  | `ctx` | `context` |
  | `val` | `value` |
  | `idx` | `index` (`i` is fine for a plain loop counter) |
  | `msg` | `message` |
  | `evt` | `event` |
  | `data` alone | prefix with domain: `patientData`, `shoppingItems` |

- Consistent vocabulary across the whole codebase: pick one term (`fetch` vs `get` vs `retrieve`) and use it everywhere — mixing them makes readers think there's a semantic difference when there isn't.
- File names match their default export/main content: `UserCard.tsx` exports `UserCard`.

## 2. Functions and modules

- One function does one thing. If you need "and" to describe it, split it.
- Prefer pure functions (same input → same output, no hidden side effects) wherever business logic lives; isolate side effects (DB calls, API calls, file I/O) at the edges.
- Keep functions short enough to see on one screen. If a function needs a scroll to read, it's usually doing too much.
- Guard clauses over nested if/else — return early instead of wrapping the "happy path" in three levels of indentation.
- Avoid magic numbers/strings — name them as constants with intent (`MAX_RETRIES = 3`, not a bare `3` in the middle of logic).

## 3. Design patterns — use when they solve a real problem, not by default

| Pattern | Use it when |
|---|---|
| Repository pattern | You need to swap or mock the data source (Supabase today, something else tomorrow) without touching business logic |
| Strategy | You have several interchangeable algorithms/behaviors selected at runtime (e.g. different pricing rules per gym plan) |
| Factory | Object creation has enough branching logic that it deserves its own function/class |
| Observer / pub-sub | Multiple parts of the app need to react to the same event (e.g. Realtime updates in Tacha) |
| Adapter | Wrapping a third-party API/SDK so the rest of the app doesn't depend on its exact shape |
| Singleton | Rare — mostly for things like a single DB connection instance. Overused pattern; avoid reaching for it by default |

Rule of thumb: **don't introduce a pattern to look sophisticated.** Introduce it when removing it would make the code harder to change. If you're not sure, write the simple version first — patterns emerge when duplication or branching complexity actually shows up.

## 4. Repository structure — the part that determines if someone "gets lost"

A stranger should be able to predict where a file lives without searching. Baseline for a web/mobile project (adapt names, keep the logic):

```
repo/
├── README.md                 ← what this is, how to run it, how to deploy it. Always first thing anyone opens.
├── docs/                      ← architecture decisions, data model, diagrams
│   └── architecture.md
├── src/
│   ├── app/ or pages/         ← routes only, thin — no business logic here
│   ├── components/            ← UI, organized by domain when it grows (components/gym/, components/shopping-list/)
│   ├── features/ or modules/  ← business logic grouped by domain, not by technical layer
│   ├── lib/ or services/      ← API clients, third-party wrappers, pure utility functions
│   ├── hooks/                 ← reusable stateful logic (React/RN)
│   ├── types/                 ← shared TypeScript types
│   └── config/                ← env, constants
├── supabase/ or db/
│   ├── migrations/            ← numbered, one migration = one reviewable change
│   └── seed.sql
├── tests/                     ← mirrors src/ structure
└── .github/workflows/         ← CI/CD
```

Key structural rules:
- **Group by domain/feature, not by technical type**, once the project grows past a handful of files. `features/payments/` beats scattering payment logic across `components/`, `hooks/`, `utils/` with no shared folder.
- **Routes/pages stay thin.** They call into `features/` or `services/` — they don't contain business logic themselves. This is what makes a codebase navigable: logic lives in exactly one predictable place.
- **No orphan files at the root.** Every file's location should be inferable from what it does.
- **A new migration file per schema change**, sequential and named descriptively (`003_add_purchase_sessions.sql`), never edited after being applied.

## 5. Documentation that isn't decoration

- **README.md is mandatory** and answers, in order: what this is, how to run it locally, how to deploy it, where the main entry points are.
- Comments explain **why**, never **what** — the code already says what it does. `// retrying because the gateway sandbox drops connections after 30s` is useful; `// loop through users` is noise.
- Document decisions that aren't obvious from the code itself (why Supabase over Firebase, why this data model over an alternative) in `docs/architecture.md`, not scattered in comments.
- Every public function/API in a library or shared module gets a docstring: purpose, params, return, and edge cases — not a restatement of the signature.

## 6. Scalability checklist (apply proportionally — don't over-engineer a class project)

- Business logic doesn't know about the UI framework or the specific DB client directly — go through an abstraction (service/repository layer) so swapping either later doesn't cascade.
- Environment-specific values live in env vars/config, never hardcoded.
- Error handling is consistent across the app (one error-shape convention), not ad hoc per file.
- New features should be addable without modifying unrelated files — if adding one thing means touching code in five unrelated places, the structure needs revisiting.

## 7. Applying this in practice

When asked to write or review code with this skill active:
1. Check naming and function size first — these are the cheapest fixes with the highest readability payoff.
2. Check whether the file is in the right place per the structure above; suggest a move if not.
3. Only suggest a design pattern if there's a concrete duplication/complexity problem it solves — name the problem, not just the pattern.
4. If reviewing an existing repo, flag structural issues before line-level nitpicks — structure is what determines whether someone gets lost.
