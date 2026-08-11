---
name: nextjs-enterprise-patterns
description: Router + remaining conventions for Next.js/React/Vite projects (Tacha, GymBase, CaneleApp, the Desarrollo Web course project) that don't warrant their own skill file — component reuse-first, Nullable typing, shared client state (framework-agnostic), typed data-mutation pattern, and a mechanical lint/format baseline. Points to component-architecture, constants-standards, and unit-testing-standards for the larger topics. Extracted and generalized from an enterprise Next.js reference repo the professor shared — see base-proyectos-arquitectura-enterprise for the source analysis.
---

# Next.js/React Enterprise Patterns

Ver también: [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise|análisis completo del repo fuente]] · [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]]

This is the entry point for React/Next.js/Vite-specific conventions in this vault. The three heaviest topics have their own skill — load them when they apply:

| Skill | Use when |
|---|---|
| [[Sistema/skills/component-architecture/SKILL|component-architecture]] | Building/reviewing any UI feature: folder structure, Spec-Driven Development, ViewModel split, SOLID/patterns |
| [[Sistema/skills/constants-standards/SKILL|constants-standards]] | A hard-coded string or magic number is about to land in a diff |
| [[Sistema/skills/unit-testing-standards/SKILL|unit-testing-standards]] | Writing or reviewing component/unit tests |

This skill covers what's left: reuse-first component search, nullable typing, shared state, the data-mutation pattern, and the mechanical style baseline.

## 1. Reuse before building — component decision gate

Before writing a raw `<button>`, `<img>`, `<section>`, a custom spinner, or a one-off modal/table: search the project's shared component library first. Compose/configure (props, `className`, variants, children) over cloning; extend a thin wrapper over the shared base before writing from scratch; only build new **on top of** existing primitives, never as a native-HTML duplicate.

If a new component looks like a UI primitive (button/input/modal/spinner-shaped), give it a Storybook-style story or an isolated dev page once the project has one set up — components reviewed in isolation catch more visual bugs than components only ever seen inside a full page.

## 2. Nullable types are explicit, not ad hoc `| null`

Centralize semantic nullable utility types instead of repeating `T | null | undefined` everywhere:

```ts
type Nullable<T> = T | null | undefined;   // not yet resolved either way
type NullableRef<T> = T | null;            // refs, "definitely absent"
type NullableUndefined<T> = T | undefined; // optional, never explicitly null
```

Communicates intent (can this be intentionally cleared vs. simply not loaded yet?) instead of a generic `| null` repeated everywhere with no distinction.

## 3. Shared client state — pick one pattern and enforce it

Whatever the project has decided on (Redux Toolkit, Zustand, TanStack Query + a thin UI store, Context for truly static values) **is the only pattern for that kind of state** — don't let a second one creep in ad hoc mid-project. Two kinds of state need two different answers, and mixing them up is the most common state-management mistake:

- **Server state** (data that lives in a database and can go stale): a query/cache library — TanStack Query is the natural fit with Supabase or any REST/RPC backend. Don't hand-roll `useEffect` + `useState` fetch logic once a query library is in the project; that's exactly the pattern it exists to replace.
- **Client-only shared state** (UI mode, current household selected, modal open/closed across components): a store (Redux Toolkit slice, Zustand store, or equivalent). Colocate feature-owned state near the feature; only promote to a global store slice once truly cross-feature.

If using Redux Toolkit specifically: slice colocated in the feature's `store/` folder, a separate `*State.interface.ts`, registered once in the root store, consumed only through the store's barrel export (never importing a slice file directly), reducers named `set<Field>`, actions exported as `<feature>Actions`.

## 4. Typed data-mutation pattern

Regardless of backend (Supabase RPC, a REST route, Firebase functions) or client library (TanStack Query, a custom fetch hook), keep the same shape:

1. Explicit `Payload` and `Response` interfaces per operation, not `unknown`/`any`.
2. The mutation hook/function is generic over both: `useMutation<Response, Error, Payload>(...)`, or the project's equivalent.
3. Errors have a typed shape (`MutationError` or similar) handled explicitly — no silent `catch {}`.

```ts
export interface AddListItemPayload {
  listId: string;
  productId: string;
  quantity: number;
}

export interface AddListItemResponse {
  itemId: string;
}
```

Keep these interfaces in one predictable place (e.g. `types/mutations/` or colocated per feature, matching whatever the project already does) rather than inlined at each call site.

## 5. Mechanical style baseline

- Arrow-function components/hooks with explicit return types — never `function` declarations for components/hooks (see [[Sistema/skills/component-architecture/SKILL|component-architecture]] §3).
- No abbreviations: `error` not `err`, `response` not `res`, `request` not `req`, `callback` not `cb`, `context` not `ctx`, `event` not `evt`; a bare `data` variable is banned — prefix with domain (`householdData`, `shoppingItems`). See the forbidden-abbreviations table in [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]].
- Lint/format baseline worth adopting on a new project: `no-console`, `no-var`, `prefer-const`, `eqeqeq`, `consistent-return`, `no-shadow`, `default-param-last`, double quotes, semicolons required. A tight Prettier `printWidth` (e.g. 60-80) with one JSX attribute per line keeps diffs easy to review even if it looks verbose in the editor.

## Applying this when a real repo starts (e.g. Tacha)

1. Set up the same agent-skill routing this vault uses: a root `AGENTS.md` (contract + catalog) with thin bridge files per tool (`CLAUDE.md`, `.cursor/rules/`, `.github/copilot-instructions.md` if the team uses those) — never copy skill content into the bridges, only point at the skill files. This is the meta-pattern the source repo itself uses; see [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise#1. El patrón meta: contrato de agentes cross-IDE|the source note]] for the exact layout.
2. Copy in the skills that apply as-is (component-architecture, constants-standards, unit-testing-standards) and adapt §§3-4 above to whatever state/backend the team actually picked.
3. New feature → start with `component-architecture` §2 (SDD spec) before touching code.
4. Any literal string/number → `constants-standards` before it lands in the diff.
5. Non-trivial behavior → tests per `unit-testing-standards` before considering the task done.

Cross-reference: [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]] stays the generic, stack-agnostic baseline (naming, function size, repo structure, when to reach for a design pattern). This skill and its three companions add the React/Next.js-specific layer on top — apply both.
