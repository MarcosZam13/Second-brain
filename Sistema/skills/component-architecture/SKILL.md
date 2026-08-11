---
name: component-architecture
description: Use this skill when building or reviewing UI features in any React/Next.js/Vite project (Tacha, GymBase, CaneleApp, the Desarrollo Web course project). Covers feature-based folder architecture, Spec-Driven Development (write the spec before the code), SOLID mapped to React components, and splitting presentation (.tsx) from logic (use*ViewModel hooks) so returns stay short and readable. Copied and generalized from an enterprise Next.js reference repo the professor shared — see base-proyectos-arquitectura-enterprise for the source analysis.
---

# Component Architecture (feature folders + ViewModel + SDD)

Ver también: [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise|análisis del repo fuente]] · [[Sistema/skills/constants-standards/SKILL|constants-standards]] · [[Sistema/skills/unit-testing-standards/SKILL|unit-testing-standards]] · [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]]

## 1. One feature, one folder

Every UI feature lives in its own kebab-case folder (`components/<feature-name>/` — path root depends on the project: `app/components/` for Next.js App Router, `src/components/` for Vite):

```
<feature-name>/
  FeatureName.tsx              ← thin entry: loading/auth gate → Inner
  FeatureNameInner.tsx         ← optional: composed body
  components/                  ← local mini components (presentation-only)
  hooks/
    useFeatureNameViewModel.ts ← ALL logic: state, effects, handlers, derived data
  models/
    FeatureNameProps.interface.ts
  store/                       ← feature-level shared state, only if actually shared
  constants/                   ← feature-only constants (still follow constants-standards)
  specs/SPEC.md                ← contract for the feature, see §2
  tests/
    FeatureName.page.ts        ← Page Object, see unit-testing-standards
    FeatureName.test.tsx
```

Rules:

- Colocate a feature's hooks/models/tests inside its own folder — don't scatter them into a global `hooks/`, `utils/`, or `store/` dump.
- Promote something to a shared location only after a **second real consumer** needs it — not preemptively.
- Match whatever folder taxonomy the project already has; don't introduce a parallel one (`containers/`, `views/`, `smart/`) alongside an existing convention.

## 2. Spec-Driven Development — specify before you code

Before a new feature or a behavior change (not a pure styling tweak), write `specs/SPEC.md` in the feature folder:

```md
# <Feature / change name>

## Intent
Who is this for, what outcome should they get?

## In scope / Out of scope

## Requirements

## Edge cases & errors

## Constraints
Reuse existing components/constants/store patterns; which skills apply.

## Acceptance criteria
- [ ] …
```

Workflow: **Specify → Plan → Tasks → Implement → Validate.** Implement task by task; before calling the work done, check the result against the acceptance criteria — not against a re-guessed version of the requirement. If requirements change mid-implementation, update the spec first, then the code.

This is the same shape as the AI-agent workflow given in the course: spec written 100% by a human → agent interview to sharpen it → agent builds the component → unit tests → QA. `SPEC.md` is where step 2 (the spec) actually lives instead of staying only in someone's head or a Slack message.

## 3. Presentation vs logic — the ViewModel split

| File | Owns |
|---|---|
| `FeatureName.tsx` | Presentation only: JSX structure, composition, binding ViewModel output to UI |
| `hooks/useFeatureNameViewModel.ts` | Logic: `useState`/reducers, effects, event handlers, derived values, data-fetching orchestration |

- `.tsx` files never contain `useState`/`useEffect`/fetch calls/non-trivial handlers directly.
- Naming: `File.tsx` → `hooks/useFileViewModel.ts`. `.ts` extension unless the hook must return JSX (avoid that).
- Purely presentational components (props → JSX, nothing else) don't need a ViewModel — don't force one.
- Components and hooks are `const` arrow functions with an explicit return type — never `function` declarations.

**Incorrect** — logic embedded in the component:

```tsx
const ShoppingList = ({ householdId }: Props) => {
  const [items, setItems] = useState<Item[]>([]);
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
    fetchItems(householdId).then((data) => {
      setItems(data);
      setIsLoading(false);
    });
  }, [householdId]);

  if (isLoading) return <Spinner />;
  return <ItemGrid items={items} />;
};
```

**Correct** — presentation + ViewModel:

```tsx
// ShoppingList.tsx
const ShoppingList = ({ householdId }: Props) => {
  const { isLoading, items } = useShoppingListViewModel({ householdId });
  if (isLoading) return <Spinner />;
  return <ItemGrid items={items} />;
};
```

```ts
// hooks/useShoppingListViewModel.ts
export const useShoppingListViewModel = ({ householdId }: Props) => {
  const [items, setItems] = useState<Item[]>([]);
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
    fetchItems(householdId).then((data) => {
      setItems(data);
      setIsLoading(false);
    });
  }, [householdId]);

  return { isLoading, items };
};
```

## 4. Keep the main return readable — extract local mini components

The primary `.tsx` return should read top-to-bottom like a page outline. When it grows past one short screenful (distinct visual regions, nested ternaries, repeated card/row markup), extract **local mini components**: presentation-only, feature-private, named by UI region (`ShoppingListToolbar`, `ShoppingListEmptyState`) — never vague (`Part1`, `Helper`). The parent wires ViewModel outputs into minis' props; minis don't re-derive logic themselves. Promote a mini to a shared component only when a second feature needs the same UI.

## 5. SOLID mapped to components, not left abstract

| Principle | Concretely |
|---|---|
| S — Single Responsibility | `.tsx` renders; `use*ViewModel` orchestrates state; dedicated hooks for fetch/validation; a store slice for state actually shared across features |
| O — Open/Closed | Extend via props/composition/variants — never copy-paste an existing feature "with tweaks" |
| L — Liskov | A shared `Button` doesn't secretly navigate + submit + fetch; specialize in the feature layer instead |
| I — Interface Segregation | Small, focused props/ViewModel interfaces; split a hook when different consumers only need a subset of it |
| D — Dependency Inversion | ViewModels depend on existing constants/types/selectors, not hardcoded transport/fetch details spread through JSX |

Preferred patterns, when they fit: **ViewModel** (default for any component with logic), **Composition** (always, over inheritance), **Facade** (a `use*Facade`/thin ViewModel coordinating several feature hooks — fetch + validate + modal), **Container/Inner** (`Feature.tsx` gate + `FeatureInner.tsx` body when loading/auth branches clutter presentation), **Adapter** (map API/DB row shapes into view models inside hooks/utils — never raw payloads in JSX), **Observer/Store** (shared state via whatever the project's single state pattern is — never ad-hoc events or prop drilling once a store exists), **Strategy** (behavior variants via props/constants instead of a big `switch` in JSX), **State** (an explicit union for mutually exclusive UI modes — `idle | loading | error | ready`, wizard steps — instead of several overlapping booleans that can contradict each other).

Forbidden defaults: god component/ViewModel (unrelated responsibilities piled together), cloning a feature folder "with tweaks" instead of reusing/composing, prop drilling when a store already covers the concern, introducing an abstraction before a second real consumer exists, inheritance trees for UI, fetch/mutation logic leaking into `.tsx`.

## 6. Checklist

- [ ] Non-trivial work has `specs/SPEC.md` (or the acceptance criteria the user already gave, persisted there) and was validated against it
- [ ] Feature lives under its own kebab-case folder with colocated `hooks/`, `models/`, `specs/`, `tests/`
- [ ] Main `.tsx` return is a short composition of local minis / shared primitives, not a long monolith
- [ ] No `useState`/`useEffect`/fetch/non-trivial handlers left in `.tsx` — logic lives in `use<Name>ViewModel.ts`
- [ ] Design names an intentional pattern (ViewModel, composition, facade, store, …) — no god components
- [ ] Non-trivial behavior covered by tests per [[Sistema/skills/unit-testing-standards/SKILL|unit-testing-standards]]
