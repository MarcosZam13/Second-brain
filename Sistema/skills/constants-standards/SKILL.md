---
name: constants-standards
description: Use this skill whenever a component, hook, or business logic in any project (Tacha, GymBase, CaneleApp, the Desarrollo Web course project) would introduce a hard-coded string literal or magic number. Single source of truth for replacing those with named constants, and for creating/naming/structuring/typing the constants files themselves. Copied and generalized from an enterprise Next.js reference repo the professor shared — see base-proyectos-arquitectura-enterprise for the source analysis.
---

# Constants Standards — no magic strings or numbers

Ver también: [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise|análisis del repo fuente]] · [[Sistema/skills/component-architecture/SKILL|component-architecture]]

## 1. Replace hard-coded literals with constants

Never use a raw string or unexplained numeric literal in components, hooks, or business logic when a constant exists — or should exist. This isn't just style: a typo in a repeated raw string (`"pendign"` vs `"pending"`) compiles fine and fails silently at runtime; a typo in a constant reference fails at compile time.

**Incorrect:**

```ts
if (status === "pending") { ... }
const debounceMs = 300;
```

**Correct:**

```ts
import { LIST_STATUS, TIMEOUT_MS } from "@/constants";

if (status === LIST_STATUS.PENDING) { ... }
const debounceMs = TIMEOUT_MS.DEBOUNCE.SEARCH;
```

**Allowed exceptions** (don't invent a constant for these): `0`/`1`/`-1` as index, increment, or "none" sentinel; loop bounds tied directly to `array.length`; utility classes already covering the value (Tailwind spacing/sizing).

## 2. `as const` on every constant object

```ts
// Incorrect — widens to `string`, mutable
export const LIST_STATUS = {
  PENDING: "pending",
};

// Correct — literal types, frozen shape
export const LIST_STATUS = {
  PENDING: "pending",
} as const;
```

## 3. Alphabetical keys within each object

Keeps the object scannable, prevents silent duplicate entries, and produces clean diffs.

```ts
// Correct
export const LIST_STATUS = {
  CANCELLED: "cancelled",
  COMPLETED: "completed",
  PENDING: "pending",
} as const;
```

## 4. One semantic domain per object — no mega-object

Don't build a single flat `CONSTANTS` or `STRINGS` object covering the whole app. Split by domain so consumers import only what they need:

```ts
// Incorrect
export const APP = { LIST_PENDING: "pending", BUTTON_PRIMARY: "primary", TOAST_ERROR_MS: 8000 };

// Correct
export const LIST_STATUS = { PENDING: "pending" } as const;
export const BUTTON_VARIANT = { PRIMARY: "primary" } as const;
export const TOAST_TIMEOUT_MS = { ERROR: 8000 } as const;
```

## 5. Keys are `SCREAMING_SNAKE_CASE` and describe meaning

Never abbreviate a key unless the value itself is abbreviated, and numeric keys describe **meaning**, never the digit:

```ts
// Incorrect
export const TIME = { LH: 23, DEBOUNCE_MS: 300 };

// Correct
export const TIME = {
  LAST_HOUR: 23,
} as const;

export const TIMEOUT_MS = {
  DEBOUNCE: { SEARCH: 300 },
} as const;
```

## 6. Export from one barrel

Every constant gets re-exported from a single `constants/index.ts` (or the project's equivalent). Never leave a shared domain value as a local `const x = 300` inside a component — if it's used more than once, or if a typo in it would be a real bug, it belongs in `constants/`.

## 7. Derive types with `typeof` + `keyof`, never hand-write a union

```ts
// Incorrect — desyncs from the object over time
export type ListStatusType = "pending" | "completed" | "cancelled";

// Correct
export const LIST_STATUS = {
  CANCELLED: "cancelled",
  COMPLETED: "completed",
  PENDING: "pending",
} as const;

export type ListStatusType = (typeof LIST_STATUS)[keyof typeof LIST_STATUS];
```

## 8. Magic numbers — nested grouping for related values

When centralizing numeric literals (timeouts, sizes, limits), nest by subdomain instead of collapsing into one flat object; keep alphabetical order at every nesting level:

```ts
export const TIMEOUT_MS = {
  DEBOUNCE: {
    SEARCH: 300,
    SELECT: 150,
  },
  POLLING: {
    SHORT: 5_000,
    STANDARD: 30_000,
  },
  TOAST: {
    ERROR: 8_000,
    SUCCESS: 4_000,
  },
} as const;
```

Include the unit in the object or key name when ambiguity is possible (`TIMEOUT_MS`, `MAX_FILE_SIZE_BYTES`) — never leave a bare number where the unit has to be guessed from context.

## Applying this in practice

1. See a raw string/number about to land in a diff → check if a constant already covers it (search first, don't duplicate).
2. If none fits, extend the nearest matching domain object, or create a new one following §§2–8.
3. Re-export from the barrel.
4. Never introduce a second flat "misc constants" file — every value gets a home in a semantic domain.
