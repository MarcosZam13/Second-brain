# Qué es un hook (React)

Ver también: [[Sistema/aprendizaje/README|Aprendizaje]] · [[Sistema/aprendizaje/principios-solid#S — Single Responsibility Principle (Responsabilidad Única)|SRP]] · [[Sistema/skills/component-architecture/SKILL|component-architecture]]

## La definición corta

Un hook es una función que empieza con `use` y le permite a un componente de función "engancharse" (*hook into*) a features de React — estado, ciclo de vida, contexto — que antes solo existían en componentes de clase. Existen desde React 16.8 (2019).

## Por qué existen (el problema que resuelven)

Antes de hooks, un componente de función era **sin estado por definición** — solo recibía props y devolvía JSX, no había forma de que "recordara" nada entre renders. Cualquier componente que necesitara estado tenía que ser una clase (`this.state`, `componentDidMount`, `componentDidUpdate`).

Los problemas reales que esto generaba:

1. **Lógica repetida entre componentes de clase** solo se podía compartir con patrones incómodos (render props, higher-order components) que anidaban componentes hasta hacer el árbol ilegible ("wrapper hell").
2. **Lógica relacionada quedaba separada por método de ciclo de vida** — la suscripción a un evento se armaba en `componentDidMount` y se limpiaba en `componentWillUnmount`, dos lugares distintos del archivo para una sola idea.
3. **`this` en JavaScript es una fuente constante de bugs** (el binding de `this` en callbacks de clases).

Los hooks resuelven los tres a la vez: permiten que una función normal tenga estado propio, agrupan la lógica relacionada en un solo lugar (efecto + su limpieza, juntos), y se pueden extraer y reutilizar como funciones normales (hooks personalizados) sin herencia ni wrappers.

## Cómo funcionan por dentro (la parte que sorprende)

Un componente de función se **vuelve a ejecutar por completo en cada render** — no hay una instancia persistente como en una clase. Entonces, ¿dónde "vive" el estado entre un render y el siguiente?

React mantiene, por cada instancia de componente montado, una **lista enlazada de hooks** en su estructura interna (el "fiber" de ese componente). Cada llamada a `useState`/`useEffect`/etc. en el cuerpo del componente corresponde a **una posición en esa lista**, identificada por el **orden en que se llama**, no por nombre.

```tsx
function Perfil() {
  const [nombre, setNombre] = useState("");   // posición 0 en la lista de hooks
  const [editando, setEditando] = useState(false); // posición 1
  useEffect(() => { /* ... */ }, [nombre]);   // posición 2
  // ...
}
```

En el siguiente render, React vuelve a recorrer el cuerpo de la función y **asocia cada llamada a `useState`/`useEffect` con la posición que le toca en esa misma lista**, en el mismo orden. Así es como `useState` "recuerda" su valor: no lo busca por nombre de variable, lo busca por posición en la lista.

**Esto explica por qué existen las Reglas de los Hooks:**

1. **Solo llamar hooks en el nivel superior** de la función — nunca dentro de un `if`, un `for`, o una función anidada. Si un hook se saltea condicionalmente en un render, se desalinea la posición de todos los hooks que vienen después, y React les asigna el estado equivocado (o crashea).
2. **Solo llamar hooks desde componentes de función o desde otros hooks personalizados** — nunca desde una función JavaScript normal, porque solo los componentes tienen esa lista enlazada asociada.

```tsx
// Mal — viola la regla 1: el orden de hooks cambia entre renders
function Componente({ mostrarExtra }: { mostrarExtra: boolean }) {
  const [a, setA] = useState(0);
  if (mostrarExtra) {
    const [b, setB] = useState(0); // a veces existe, a veces no → desalinea todo lo de abajo
  }
  const [c, setC] = useState(0);
}
```

## Los hooks que se usan todo el tiempo

| Hook | Para qué |
|---|---|
| `useState` | Estado local que, al cambiar, dispara un re-render |
| `useEffect` | Sincronizar el componente con algo externo (fetch, suscripción, timer) — corre después de que React pintó la pantalla |
| `useRef` | Guardar un valor que persiste entre renders **sin** disparar re-render al cambiar (ej. referencia a un elemento DOM, o un "flag" mutable) |
| `useMemo` | Cachear el resultado de un cálculo costoso, recalculando solo si sus dependencias cambian |
| `useCallback` | Cachear la *identidad* de una función entre renders (evita que un hijo memoizado con `React.memo` se re-renderice porque recibió una función "nueva" aunque haga lo mismo) |
| `useReducer` | Estado con lógica de transición más compleja que un simple `setState` (varias acciones posibles, estado derivado de la acción anterior) |
| `useContext` | Leer un valor provisto más arriba en el árbol sin pasarlo por props en cada nivel ("prop drilling") |

## Hooks personalizados — la aplicación directa de SRP

Un hook personalizado es simplemente una función que empieza con `use` y llama a otros hooks adentro. Su valor real: **extraer lógica con estado fuera del componente**, para que el componente se quede solo con la responsabilidad de renderizar (ver [[Sistema/aprendizaje/principios-solid#S — Single Responsibility Principle (Responsabilidad Única)|SRP en principios-solid.md]], que usa justo este ejemplo con `usePostularseAAsistencia`).

```tsx
function useAsistenciasDisponibles(sede: string) {
  const [asistencias, setAsistencias] = useState<Asistencia[]>([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    let cancelado = false;
    setLoading(true);
    fetch(`/api/asistencias?sede=${sede}`)
      .then((r) => r.json())
      .then((data) => { if (!cancelado) setAsistencias(data); })
      .finally(() => { if (!cancelado) setLoading(false); });
    return () => { cancelado = true; }; // limpieza: evita setear estado de un componente ya desmontado
  }, [sede]);

  return { asistencias, loading };
}
```

Cualquier componente que necesite la lista de asistencias por sede llama a este hook — la lógica de fetch/estado vive en un solo lugar, testeable aparte del JSX.

## Errores comunes

- **"Stale closure"**: un `useEffect`/callback captura una variable del render en que se creó y no ve el valor actualizado, porque le faltó esa variable en el array de dependencias. La regla práctica: si el linter de `exhaustive-deps` se queja, casi siempre tiene razón — silenciarlo suele esconder este bug.
- **Hooks condicionales** (ver regla 1 arriba) — el error más directo de "por qué me tira este warning de React".
- **Confundir `useMemo`/`useCallback` con optimización obligatoria**: son para evitar recálculos/re-renders costosos medidos, no un reflejo automático en cada línea — usarlos sin necesidad agrega complejidad sin beneficio real.

## Si el profesor pregunta...

- **"¿Por qué no podés poner ese `useState` dentro del `if`?"** → Porque React identifica cada hook por su posición en una lista interna del componente, no por nombre; saltearlo condicionalmente desalinea todos los hooks siguientes.
- **"¿Qué diferencia hay entre `useEffect` y solo poner el código directo en el cuerpo del componente?"** → El cuerpo corre en cada render de forma síncrona (debe ser puro); `useEffect` corre después de pintar la pantalla y es el lugar correcto para sincronizar con algo externo (red, DOM, timers), con una función de limpieza opcional.
- **"¿Por qué armaste un hook personalizado en vez de poner esa lógica directo en el componente?"** → Para separar responsabilidad (lógica con estado vs. renderizado) y poder reutilizarla/testearla aparte — aplicación directa de SRP.
