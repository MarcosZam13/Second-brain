---
name: unit-testing-standards
description: Use this skill when writing, updating, or reviewing unit/component tests for a React/Next.js/Vite project (Tacha, GymBase, CaneleApp, the Desarrollo Web course project). Covers Vitest + Testing Library + the Page Object Model (POM) so UI tests stay readable and don't scatter raw queries across the suite. Copied and generalized from an enterprise Next.js reference repo the professor shared — see base-proyectos-arquitectura-enterprise for the source analysis. Cross-references qa-testing-practices for the QA-artifact side (test plans, bug reports) of the same work.
---

# Unit Testing Standards — Page Object Model

Ver también: [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise|análisis del repo fuente]] · [[Sistema/skills/component-architecture/SKILL|component-architecture]] · [[Sistema/skills/qa-testing-practices/SKILL|qa-testing-practices]]

Always use the **Page Object Model (POM)** for UI/component interaction tests. Tests must not scatter raw `screen.getBy*` / `fireEvent` calls throughout the suite — queries and user actions live in a Page Object; specs assert behavior through that API.

## 1. Tooling

| Layer | Package |
|---|---|
| Runner | Vitest |
| Component render | `@testing-library/react` |
| Interactions | `@testing-library/user-event` |
| DOM matchers | `@testing-library/jest-dom` |

Prefer Testing Library's accessible queries over shallow-rendering/implementation-detail APIs.

## 2. Feature-colocated test layout

Tests live inside the feature folder, matching [[Sistema/skills/component-architecture/SKILL|component-architecture]]:

```
<feature-name>/
  FeatureName.tsx
  hooks/useFeatureNameViewModel.ts
  tests/
    FeatureName.page.ts              ← Page Object (POM)
    FeatureName.test.tsx             ← component/integration tests
    useFeatureNameViewModel.test.ts  ← optional pure ViewModel tests (no POM needed)
  specs/SPEC.md                      ← acceptance criteria to map into tests
```

Don't create a global `tests/page-objects/` dump for feature-specific UI. Shared test helpers (a `renderWithProviders`) can live under a top-level `test-utils/` once a second feature needs the same setup.

## 3. Page Object rules

A Page Object:

- Encapsulates **how** to find elements (roles, labels — `data-testid` only when unavoidable)
- Encapsulates **user actions** (`fillEmail`, `submit`, `openConfirmModal`)
- Exposes **readable queries** for assertions (`getErrorMessage()`, `isSubmitDisabled()`)
- Does **not** contain `expect` calls — specs own assertions
- Does **not** contain business/product logic — only a UI interaction API

Naming: `FeatureName.page.ts`, factory `createFeatureNamePage` (arrow function).

**Incorrect** — raw queries inline in every test:

```tsx
it("submits the form", async () => {
  const user = userEvent.setup();
  render(<ShoppingListForm {...props} />);
  await user.type(screen.getByLabelText("Item name"), "Milk");
  await user.click(screen.getByRole("button", { name: "Add" }));
  expect(screen.getByText("Added")).toBeInTheDocument();
});
```

**Correct** — Page Object + thin spec:

```ts
// tests/ShoppingListForm.page.ts
export const createShoppingListFormPage = () => {
  const user = userEvent.setup();

  const getItemInput = () => screen.getByLabelText(/item name/i);
  const getAddButton = () => screen.getByRole("button", { name: /add/i });
  const getConfirmation = () => screen.getByText(/added/i);

  const fillItemName = async (name: string) => {
    await user.type(getItemInput(), name);
  };

  const submit = async () => {
    await user.click(getAddButton());
  };

  return { fillItemName, submit, getConfirmation };
};
```

```tsx
// tests/ShoppingListForm.test.tsx
describe("ShoppingListForm", () => {
  it("adds an item and shows confirmation", async () => {
    render(<ShoppingListForm {...props} />);
    const page = createShoppingListFormPage();

    await page.fillItemName("Milk");
    await page.submit();

    expect(page.getConfirmation()).toBeInTheDocument();
  });
});
```

One Page Object per screen/feature under test. A reused child widget can have its own `*.page.ts` if it's exercised across multiple parent tests; otherwise keep its actions on the parent Page Object.

## 4. What to unit test

| Target | How | POM? |
|---|---|---|
| Feature UI (`.tsx`) | Render + interact via Page Object | Yes |
| ViewModel hooks | `renderHook` / direct calls; mock APIs/store | No |
| Pure utils / mappers | Direct function tests | No |
| Store/reducer logic | Feed actions → assert state | No |

Prefer testing behavior tied to `specs/SPEC.md` acceptance criteria over snapshotting large DOM trees.

## 5. Component test guidelines

- Wrap with whatever providers the feature needs (store `Provider`, query client, auth mocks) via a shared render helper once one exists.
- Mock network/backend/realtime calls at the boundary — no real I/O in unit tests.
- Assert on **outcomes** (visible text, disabled state, callback invoked), not implementation details (internal state, unrelated CSS class strings).
- Deterministic tests: no real timers/network; use fake timers for debounce/timeout behavior, sourced from [[Sistema/skills/constants-standards/SKILL|constants]] rather than a re-typed magic number.

## 6. Arrange · Act · Assert

1. **Arrange** — render the feature (build the Page Object)
2. **Act** — call Page Object actions
3. **Assert** — `expect` on Page Object queries or mocked dependencies

One act per test. Name tests by behavior (`"disables submit while saving"`), not by mechanics (`"click button"`).

## 7. SDD + testing

When [[Sistema/skills/component-architecture/SKILL|component-architecture]]'s SDD applies: map each `specs/SPEC.md` acceptance criterion to at least one test name, implement/adjust the Page Object as the UI stabilizes, and run the feature's tests before considering the work done.

## 8. Checklist

- [ ] Tests colocated under the feature's `tests/` folder
- [ ] UI tests go through a `*.page.ts` Page Object — no duplicated raw queries across specs
- [ ] Page Object has no `expect` calls; specs own assertions
- [ ] Queries prefer roles/labels over `data-testid`
- [ ] ViewModel/pure logic tested without forcing a POM
- [ ] External I/O mocked; no real network/backend in unit tests
- [ ] Acceptance criteria from `specs/SPEC.md` covered where applicable
