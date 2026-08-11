---
curso: DesarrolloWeb
tema: Análisis del repo base "BaseProyectos" del profesor (arquitectura enterprise Next.js)
fecha: 2026-08-11
tipo: apunte
fuente: "repo local compartido por el profesor — C:\Users\luisy\Documents\Uni\web\pruebagit\BaseProyectos (git, no versionado en este vault)"
tags: [nextjs, react, arquitectura, agentes-ia, viewmodel, redux, constants, testing, buenas-practicas]
---

# BaseProyectos — arquitectura enterprise del profesor (Desarrollo Web)

Ver también: [[Cursos/DesarrolloWeb/apuntes/introduccion-desarrollo-web]] · [[Cursos/DesarrolloWeb/apuntes/gitflow-curso]] · [[Sistema/skills/nextjs-enterprise-patterns/SKILL|skill nextjs-enterprise-patterns]] · [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]]

## Qué es

El profesor de Desarrollo Web compartió un repo (`BaseProyectos`, proyecto "MediXenter" — historial clínico para centros médicos) que usa como base real a nivel empresarial: un Next.js 16 / React 19 / TypeScript con Redux Toolkit, Tailwind, Storybook y Firebase, pero lo valioso no es el dominio (salud) sino **cómo está gobernado el código**: un sistema de *skills* para agentes de IA que codifica sus convenciones como reglas ejecutables, no como wiki que nadie lee.

Coincide 1:1 con lo dado en clase en [[Cursos/DesarrolloWeb/apuntes/introduccion-desarrollo-web|introducción al curso]] (stack HTML5/JS/React/Next.js, Firebase, GitHub) y con el flujo de agentes de IA mencionado ahí (Spec → entrevista con agente → crear componente → unit testing → QA) — este repo es la forma concreta de esa metodología, aplicada en producción.

## 1. El patrón meta: contrato de agentes cross-IDE

Esto es lo más reutilizable de todo el repo, independiente del stack:

```
AGENTS.md                          ← contrato único, fuente de verdad + catálogo de skills
.agents/skills/<nombre>/SKILL.md   ← estándares detallados, un archivo por tema
CLAUDE.md                          ← puente: "@AGENTS.md" + nada más
.cursor/rules/skills.mdc           ← puente: mismo texto, alwaysApply: true
.github/copilot-instructions.md    ← puente: mismo texto en prosa
```

Regla de oro del repo: **"si un skill y cualquier otro doc no coinciden, gana el skill. Nunca copiar contenido del skill a los archivos puente."** Cada IDE/agente (Claude Code, Cursor, Copilot) lee su propio archivo de entrada, pero todos apuntan al mismo lugar — cero duplicación, cero desincronización entre herramientas.

**Por qué importa para este vault:** es el mismo problema que resuelve `Sistema/CLAUDE.md` + `Sistema/skills/`, pero con un matiz que vale la pena copiar: ellos fuerzan explícitamente "antes de programar, escaneá el catálogo de skills y abrí cada uno que aplique" como protocolo obligatorio (§ "Mandatory skill protocol" de `AGENTS.md`), con checklist de verificación al final de cada skill. Si algún proyecto de este vault (GymBase, Tacha) crece y se trabaja también desde Cursor o Copilot además de Claude Code, este patrón de puentes finos es directamente portable.

## 2. Rol por defecto exigido al agente

`AGENTS.md` fija un "bar" de calidad no negociable en cada prompt, aunque el usuario no lo pida: actuar como *elite senior Next.js/React/TypeScript engineer*, nunca regresar a patrones junior o "tutorial-style". Define explícitamente una lista de **defaults junior prohibidos**: UI tipada con strings sueltos cuando existen constantes/uniones, prop drilling cuando ya hay Redux, librerías/wrappers innecesarios para un one-liner, refactors amplios no pedidos, explicar con relleno en vez de entregar el cambio.

Esto es una técnica de prompting de sistema reutilizable: en vez de pedir "buen código" cada vez, se fija una sola vez el estándar y una lista negativa concreta de qué NO hacer.

## 3. Arquitectura de features (lo más denso del repo)

Cada feature de UI vive en **una sola carpeta** bajo `app/components/<feature-kebab-case>/`, con una estructura fija:

```
app/components/patient-form/
  PatientForm.tsx              ← entrada delgada: gate de loading/auth → Inner
  PatientFormInner.tsx         ← composición del cuerpo (opcional)
  components/                  ← mini componentes locales de esa feature
  hooks/
    usePatientFormViewModel.ts ← TODA la lógica (estado, efectos, handlers)
  models/
    PatientFormProps.interface.ts
    PatientFormViewModel.interface.ts
  store/                       ← slice Redux de la feature (si necesita estado compartido)
  constants/                   ← constantes solo de esta feature
  specs/SPEC.md                ← contrato de la feature (ver §4)
  tests/
    PatientForm.page.ts        ← Page Object
    PatientForm.test.tsx
```

Reglas dominantes:

- **`.tsx` = presentación pura.** Nunca `useState`/`useEffect`/fetch/handlers no triviales ahí. Toda esa lógica va al hook `use<Nombre>ViewModel.ts` (patrón ViewModel/Presentación).
- **El `return` principal se mantiene corto** — un "outline" de composición, no un muro de 200 líneas. Cuando crece (regiones distintas, ternarios anidados, bloques repetidos), se extraen **mini componentes locales** (`PatientFormToolbar`, `PatientFormEmptyState`) — presentación pura también, sin lógica propia.
- **Nunca crear un componente base paralelo.** Antes de escribir `<button>`, `<img>`, un spinner o un modal a mano, hay que buscar en el catálogo de primitivos compartidos (`Button`, `Modal`, `FormField`, `Spinner`, `Section`...) y componer/extender, no clonar.
- Un feature nuevo no se scatterea entre `app/hooks/`, `app/store/`, `app/components/` sueltos — todo colocalizado salvo que un segundo consumidor real lo necesite compartido (regla del segundo consumidor antes de promover algo a "shared").

Ejemplo real visto en el repo (`app/components/button/Button.tsx`): componente presentacional envuelto en `memo`, con la clase calculada en un util aparte (`getButtonClassName`) — nada de lógica de negocio dentro del `.tsx`, todo es props → JSX.

## 4. Spec-Driven Development (SDD) — obligatorio antes de codear

Antes de una feature nueva o un cambio de comportamiento no trivial, hay que **especificar primero**: crear/actualizar `specs/SPEC.md` dentro de la carpeta de la feature (intención, alcance, requisitos, edge cases, criterios de aceptación) — recién ahí se deriva un plan técnico y se implementa tarea por tarea. Al final se valida el resultado contra los criterios de aceptación del spec, no contra lo que "se entendió" del pedido.

Único atajo permitido: cambios puramente presentacionales sin cambio de comportamiento (ej. solo `className`) pueden saltarse el spec completo.

Esto es exactamente el flujo de agentes de IA que dio el profesor en clase (ver introducción al curso: "escribir la Spec 100% humano → entrevista con agente → crear componente → testing → QA") — `SPEC.md` es el artefacto formal de ese paso 2.

## 5. SOLID mapeado a componentes React (no abstracto)

La tabla del repo traduce cada letra de SOLID a algo concreto en este stack en vez de quedarse en teoría:

| Principio | Cómo se aplica acá |
|---|---|
| S — Single Responsibility | `.tsx` renderiza; `use*ViewModel` orquesta estado; hooks dedicados para fetch/validación; slice Redux para estado compartido |
| O — Open/Closed | Se extiende por props/composición/variantes — nunca copy-paste de un componente base con retoques |
| L — Liskov | Un `Button` no puede "secretamente" navegar Y hacer submit Y hacer fetch — eso se especializa en la capa de feature |
| I — Interface Segregation | Props/ViewModel chicos y enfocados; separar hooks cuando distintos consumidores solo necesitan un subconjunto |
| D — Dependency Inversion | Las ViewModels dependen de constantes/tipos/selectores/mutations ya existentes, no de detalles de transporte hardcodeados en el JSX |

Patrones preferidos y cuándo: ViewModel/Presentación (default con lógica), Composición (siempre, en vez de herencia), Facade (`use*Facade` que coordina varios hooks), Container/Inner (`Feature.tsx` + `FeatureInner.tsx` cuando el gate de loading/auth ensucia la presentación), Factory (config-driven UI vía `FieldFactory`, no un segundo sistema de factory), Adapter (mapear DTOs de API a view models, nunca payload crudo en JSX), Observer/Store (Redux, nunca eventos ad-hoc), Strategy (variantes por props/constantes en vez de `switch` gigante en JSX), Decorator (wrappers como `PrivateRoute` o gates de permiso sin tocar el core del componente), State (modelar modos mutuamente excluyentes como unión explícita — `idle | loading | error | ready` — en vez de banderas booleanas sueltas que se pisan entre sí).

Anti-patrones marcados explícitamente como prohibidos: god component/ViewModel, copiar una feature "con retoques" en vez de reusar, prop drilling cuando ya hay Redux, abstracción prematura sin un segundo consumidor real, árboles de herencia para UI React, lógica de fetch/mutación filtrada dentro del `.tsx`.

## 6. Constantes: cero strings/números mágicos

Regla dura: ningún literal string o número sin explicar en componentes/hooks/lógica de negocio. Todo bajo `@/app/constants`, con convenciones estrictas:

- `as const` en todo objeto de constantes (evita mutación, habilita inferencia literal).
- Claves ordenadas alfabéticamente dentro de cada objeto (diffs limpios, evita duplicados).
- Un objeto por dominio semántico — nunca un `NUMBERS`/`STRINGS` mega-objeto plano para toda la app.
- Claves en `SCREAMING_SNAKE_CASE` que describen el **significado**, nunca el dígito (`DEBOUNCE.SEARCH`, no `THREE_HUNDRED`).
- Tipos derivados con `typeof`/`keyof` del objeto, nunca una unión escrita a mano que se desincroniza:

```ts
export const BROWSER_EVENTS = {
  CLICK: "click",
  SCROLL: "scroll",
} as const;

export type BrowserEventType =
  (typeof BROWSER_EVENTS)[keyof typeof BROWSER_EVENTS];
```

- Excepciones permitidas (no crear constante para esto): `0`/`1`/`-1` como índice o sentinela, límites de loop atados directo al length de un array, utilidades Tailwind ya expresadas como clases.
- Todo se re-exporta desde `app/constants/index.ts` (barrel único) — nunca queda un `const debounceMs = 300` local en un componente para un valor de dominio compartido.

## 7. Estado compartido: Redux Toolkit, sin alternativas

El repo es tajante: **Redux Toolkit es el único patrón de estado de cliente compartido — nada de Context API ni Zustand para estado de feature.** Cada slice compartido de una feature vive colocalizado en `app/components/<feature>/store/`, con una interfaz de estado separada del archivo del slice, registro en `app/store/index.ts`, y consumo siempre vía `@/app/store` (nunca importando el slice directo). Convención de nombres fija: `set<Campo>` para reducers, `<feature>Actions` para el objeto de acciones exportado.

## 8. Tipos nullable explícitos

Nunca `T | null` o `T | undefined` sueltos en interfaces — tipos utilitarios semánticos centralizados: `Nullable<T>` (`T | null | undefined`), `NullableRef<T>` (`T | null`), `NullableUndefined<T>` (`T | undefined`). Comunica intención (¿puede no estar seteado nunca vs. todavía no cargó?) en vez de un `| null` genérico repetido por todo el codebase.

## 9. Testing: Page Object Model obligatorio

Ningún `screen.getBy*`/`fireEvent` suelto dentro de los tests. Cada feature con UI tiene un `*.page.ts` (Page Object: dónde están los elementos + acciones de usuario + queries de lectura, **sin** `expect` adentro) y el `.test.tsx` solo hace Arrange → Act (vía el Page Object) → Assert. Tests colocalizados en `tests/` dentro de la carpeta de la feature, no en un `tests/page-objects/` global. ViewModels puros se testean directo con `renderHook`, sin necesitar POM.

## 10. Estilo de código — lo mecánico

- Componentes y hooks **siempre** `const` + arrow function, nunca `function` — con tipo de retorno explícito (`JSX.Element`, o interfaz nombrada para hooks).
- Nombres descriptivos completos, tabla explícita de abreviaciones prohibidas: `err`→`error`, `res`→`response`, `req`→`request`, `cb`→`callback`, `ctx`→`context`, `evt`→`event`, `data` solo (sin prefijo de dominio) también prohibido — siempre `patientData`, `appointmentList`, etc.
- ESLint del repo refuerza bastante de esto a nivel de máquina: `no-console`, `no-var`, `prefer-const`, `eqeqeq`, `no-else-return`, `no-lonely-if`, `consistent-return`, `no-shadow`, `default-param-last`, comillas dobles, punto y coma obligatorio. Prettier con `printWidth: 60` y `singleAttributePerLine: true` — fuerza JSX con un atributo por línea, ilegible de otra forma pero muy fácil de diffear en PR.

## Cómo se está aplicando esto en la práctica

El repo real no cumple el 100% de su propio estándar (ej. `useContactForm.ts` mezcla algo de lógica de validación con efectos de sincronización de idioma en vez de un ViewModel más fino) — normal en cualquier codebase real. El valor de la nota no es "este repo es perfecto", es la **codificación explícita y ejecutable por agentes** de las reglas, algo que la mayoría de equipos deja como conocimiento tácito.

## Qué se llevó al vault como skills reutilizables

Todo lo de arriba que no depende del dominio salud/MediXenter quedó extraído y adaptado a 4 skills propios, aplicables a cualquier proyecto React/Next.js/Vite de este vault (el proyecto del curso — Tacha —, GymBase, CaneleApp):

- [[Sistema/skills/component-architecture/SKILL|component-architecture]] — feature folders, ViewModel, SDD, SOLID/patrones, mini componentes (§§3-5 de esta nota).
- [[Sistema/skills/constants-standards/SKILL|constants-standards]] — cero strings/números mágicos (§6 de esta nota).
- [[Sistema/skills/unit-testing-standards/SKILL|unit-testing-standards]] — Page Object Model para tests de UI (§9 de esta nota); el mismo patrón también se sumó como sección nueva a [[Sistema/skills/qa-testing-practices/SKILL|qa-testing-practices]] para automatización de test cases en general.
- [[Sistema/skills/nextjs-enterprise-patterns/SKILL|nextjs-enterprise-patterns]] — quedó como router hacia los tres de arriba, más lo que no ameritaba skill propio: reuso de componentes existentes antes de crear uno nuevo, tipos Nullable (§8), estado compartido (§7, generalizado — ver nota abajo) y estilo mecánico (§10).

Se referencian desde [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]] (que también ganó una tabla concreta de abreviaciones prohibidas a partir de esta lectura) para proyectos que sean específicamente Next.js/React. Contexto de aplicación real en [[Proyectos/Tacha/README|Tacha]], el proyecto del curso.
