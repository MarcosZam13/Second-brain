# Arquitectura de TypeScript

Ver también: [[Sistema/aprendizaje/README|Aprendizaje]] · [[Sistema/aprendizaje/principios-solid|principios-solid.md]] · [[Sistema/skills/nextjs-enterprise-patterns/SKILL|nextjs-enterprise-patterns]]

"Arquitectura del lenguaje" tiene dos lecturas distintas y vale la pena separarlas — el profesor probablemente pregunta por ambas:

1. **Cómo está construido TypeScript por dentro** (el compilador, el sistema de tipos) — esto es lo que explica *por qué* TS se comporta como se comporta.
2. **Cómo se usa TypeScript para dar forma a la arquitectura de una app** (contratos entre capas, tipos como documentación viva) — esto es lo que se aplica todos los días.

## 1. Qué es TypeScript, en una frase

Un superset de JavaScript que agrega un sistema de tipos **estático y opcional**, que se borra por completo al compilar — en runtime no existe ningún tipo, todo es JavaScript puro. Esto se llama **type erasure**.

```ts
function suma(a: number, b: number): number {
  return a + b;
}
```

compila a:

```js
function suma(a, b) {
  return a + b;
}
```

Ninguna anotación de tipo sobrevive. Consecuencia práctica: **no podés hacer `if (typeof x === MiInterfaz)` en runtime** — las interfaces/types no existen ahí. Si necesitás validar algo en runtime (por ejemplo la respuesta de una API externa, que TypeScript no puede garantizar), hace falta una librería de validación (Zod, io-ts) que sí genera código real.

## 2. El pipeline del compilador (`tsc`)

1. **Parsing** — el código fuente se convierte en un AST (Abstract Syntax Tree), igual que hace cualquier compilador/intérprete.
2. **Binding** — se arma una tabla de símbolos: qué nombre se declaró dónde, en qué scope.
3. **Type checking** — acá pasa la magia: se infiere y verifica el tipo de cada expresión contra las anotaciones y las reglas del lenguaje. Es donde salen los errores rojos del editor.
4. **Emit** — se generan los `.js` (y opcionalmente `.d.ts` con las declaraciones de tipos) borrando toda anotación.

El dato importante: **el type checking y el emit son pasos separados**. Podés tener errores de tipos y aun así `tsc` puede emitir el JavaScript (salvo que actives `noEmitOnError`). Herramientas como esbuild/SWC/Babel solo hacen el paso 4 (mucho más rápido) y delegan el chequeo de tipos a `tsc --noEmit` aparte — así funciona el build rápido de Vite/Next.js con TypeScript.

## 3. Tipado estructural, no nominal

Esta es la diferencia más importante frente a lenguajes como Java o C#. TypeScript compara tipos **por su forma** (qué propiedades tiene), no por su nombre declarado.

```ts
interface Punto { x: number; y: number; }

function imprimir(p: Punto) { console.log(p.x, p.y); }

// Esto compila aunque "Coordenada" nunca dijo "implements Punto":
interface Coordenada { x: number; y: number; }
const c: Coordenada = { x: 1, y: 2 };
imprimir(c); // válido — misma forma
```

Ventaja: menos ceremonia, se pueden combinar tipos de librerías distintas sin herencia explícita. Riesgo: dos tipos con forma parecida pero significado distinto pasan como intercambiables si no se es cuidadoso (por eso a veces se usan *branded types* para forzar distinción nominal cuando hace falta, ej. `UserId` vs `ProductId` que internamente son ambos `string`).

## 4. Inferencia de tipos

TypeScript no obliga a anotar todo — infiere el tipo más específico posible a partir del valor o del contexto:

```ts
let a = 5; // inferido: number
const asistencia = { id: "1", cupos: 10 }; // inferido: { id: string; cupos: number }

function map<T, U>(arr: T[], fn: (item: T) => U): U[] { ... }
map([1, 2, 3], (n) => n.toString()); // T=number, U=string, inferidos por el uso
```

Regla práctica: anotar tipos en **fronteras** (parámetros de función exportada, retorno de una función pública, props de un componente) y dejar que la inferencia trabaje adentro. Anotar todo explícitamente es ruido, no anotar nada en las fronteras es perder el valor del sistema de tipos.

## 5. `interface` vs `type` — cuándo usar cada uno

Ambos describen la forma de un objeto y en la mayoría de los casos son intercambiables. Diferencias reales:

- `interface` se puede **extender** (`extends`) y **declaration merging** (dos `interface` con el mismo nombre se combinan) — útil para tipos que una librería externa puede querer ampliar.
- `type` puede describir **uniones, intersecciones, tipos primitivos con alias, tuplas** — cosas que `interface` no puede.

```ts
type Estado = "abierta" | "cerrada" | "pendiente"; // union — interface no puede hacer esto
type ConId<T> = T & { id: string };                 // intersección
interface Asistencia { id: string; titulo: string; estado: Estado; } // forma de objeto extensible
```

Convención común (y razonable): `interface` para formas de objeto/contratos públicos que alguien podría extender, `type` para todo lo demás (uniones, utilidades, alias).

## 6. Union types + discriminated unions (el patrón más subestimado)

Modelar estados imposibles como *imposibles de representar*, no solo como "no debería pasar":

```ts
// Mal: estados que pueden combinarse de formas inválidas (loading=true Y data presente a la vez)
interface EstadoCarga<T> {
  loading: boolean;
  data?: T;
  error?: string;
}
```

```ts
// Bien: discriminated union — solo un estado es posible a la vez, y TypeScript
// obliga a manejar cada caso (narrowing automático por el campo "status").
type EstadoCarga<T> =
  | { status: "loading" }
  | { status: "success"; data: T }
  | { status: "error"; error: string };

function render(estado: EstadoCarga<Asistencia[]>) {
  switch (estado.status) {
    case "loading": return "Cargando...";
    case "success": return estado.data.length; // TS sabe que acá existe .data
    case "error": return estado.error;          // TS sabe que acá existe .error
  }
}
```

Esto elimina de raíz una categoría entera de bugs ("¿por qué se ve el spinner Y el error al mismo tiempo?").

## 7. Genéricos

Una función/tipo genérico es una plantilla que preserva la relación entre tipos de entrada y salida, en vez de perderla con `any`.

```ts
// Mal: se pierde toda la información de tipo.
function primero(arr: any[]): any { return arr[0]; }

// Bien: el tipo de salida está ligado al tipo de entrada.
function primero<T>(arr: T[]): T | undefined { return arr[0]; }

const asistencias: Asistencia[] = [...];
const a = primero(asistencias); // TS sabe que "a" es Asistencia | undefined, no any
```

## 8. Utility types que se usan todo el tiempo

`Partial<T>` (todas las props opcionales — útil para un `update()` parcial), `Pick<T, K>` / `Omit<T, K>` (subconjunto de campos — útil para DTOs), `Record<K, V>` (mapa tipado), `ReturnType<typeof fn>` (extraer el tipo de retorno sin repetirlo a mano). Todos son transformaciones del sistema de tipos, cero código en runtime.

## 9. `strict` mode y por qué importa

`tsconfig.json` con `"strict": true` activa (entre otras) `strictNullChecks` — sin esto, `null`/`undefined` son asignables a cualquier tipo, lo que anula buena parte del valor de tener tipos. Cualquier proyecto nuevo (incluido Asistencias TEC) debería arrancar con `strict: true` desde el primer commit — activarlo después sobre un codebase grande es mucho más doloroso.

## 10. Cómo esto da forma a la arquitectura de una app

Los tipos son el **contrato entre capas** — es la aplicación práctica de [[Sistema/aprendizaje/principios-solid#D — Dependency Inversion Principle (Inversión de Dependencias)|DIP]] a TypeScript concretamente:

- **Tipos de dominio** (`Asistencia`, `Usuario`) — la forma real del negocio, viven en el core, no dependen de la API ni de la UI.
- **DTOs / tipos de API** — la forma exacta de lo que responde el backend, puede diferir del tipo de dominio (fechas como string ISO, campos snake_case) y se mapea explícitamente al tipo de dominio en la capa de acceso a datos.
- **Props de componentes** — el contrato de la UI, normalmente un subconjunto del tipo de dominio (ver [[Sistema/aprendizaje/principios-solid#I — Interface Segregation Principle (Segregación de Interfaces)|ISP]]).

Separar estos tres evita el error típico: que un cambio en la respuesta de la API rompa 20 componentes porque todos importaban el tipo de la API directamente en vez de un tipo de dominio estable.

## Si el profesor pregunta...

- **"¿Qué pasa con los tipos cuando compila?"** → Desaparecen por completo (type erasure); en runtime es JavaScript puro, por eso no se puede validar un tipo en runtime sin una librería aparte (Zod, etc.).
- **"¿Por qué este objeto es válido si nunca dijo que implementaba esa interfaz?"** → Tipado estructural: TS compara la forma, no el nombre declarado.
- **"¿Por qué usaste `type` acá y `interface` allá?"** → `type` para uniones/intersecciones, `interface` para contratos de objeto extensibles.
- **"¿Por qué modelaste el estado así (con `status: "loading" | "success" | "error"`) en vez de banderas booleanas?"** → Discriminated union: hace que los estados inválidos sean irrepresentables, no solo "poco probables".
