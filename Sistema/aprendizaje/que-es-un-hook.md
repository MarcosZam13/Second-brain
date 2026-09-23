# Qué es un hook (React)

Ver también: [[Sistema/aprendizaje/README|Aprendizaje]] · [[Sistema/aprendizaje/principios-solid#S — Single Responsibility Principle (Responsabilidad Única)|SRP]] · [[Sistema/skills/component-architecture/SKILL|component-architecture]] · [[Proyectos/Tacha/README|Tacha]] (fuente de los ejemplos de abajo)

## La definición corta

Un hook es una función que empieza con `use` y le permite a un componente de función "engancharse" (*hook into*) a features de React — estado, ciclo de vida, contexto — que antes solo existían en componentes de clase. Existen desde React 16.8 (2019).

## Por qué existen (el problema que resuelven)

Antes de hooks, un componente de función era **sin estado por definición** — solo recibía props y devolvía JSX, no había forma de que "recordara" nada entre renders. Cualquier componente que necesitara estado tenía que ser una clase (`this.state`, `componentDidMount`, `componentDidUpdate`).

Los problemas reales que esto generaba:

1. **Lógica repetida entre componentes de clase** solo se podía compartir con patrones incómodos (render props, higher-order components) que anidaban componentes hasta hacer el árbol ilegible ("wrapper hell").
2. **Lógica relacionada quedaba separada por método de ciclo de vida** — la suscripción a un evento se armaba en `componentDidMount` y se limpiaba en `componentWillUnmount`, dos lugares distintos del archivo para una sola idea.
3. **`this` en JavaScript es una fuente constante de bugs** (el binding de `this` en callbacks de clases).

Los hooks resuelven los tres a la vez: permiten que una función normal tenga estado propio, agrupan la lógica relacionada en un solo lugar (efecto + su limpieza, juntos), y se pueden extraer y reutilizar como funciones normales (hooks personalizados) sin herencia ni wrappers.

## El modelo mental correcto (y tres confusiones comunes al empezar)

**La analogía que funciona:** React es como la recepción de un hotel, y cada componente montado en pantalla es un huésped con una libreta a su nombre en el mostrador. Mientras el huésped esté hospedado (el componente esté en pantalla), la recepción le guarda lo que le pida (`useState`) y se lo devuelve igual en cada visita a su cuarto (cada render). Si el huésped se va (el componente se desmonta) o recargás la página, la libreta se tira.

Tres cosas que **no** es, aunque tienten como comparación:

1. **No es "como una cookie".** Una cookie sobrevive a que cierres el navegador y se manda al servidor. El estado de `useState` vive solo mientras el componente está montado — un F5 lo borra. Para que algo sobreviva de verdad (el "tachado" de un producto, por ejemplo) hace falta guardarlo en la base de datos aparte, no solo en `useState`.
2. **`useEffect` no espera a que "cargue toda la app".** Corre después de que **ese componente puntual** terminó de pintarse, no en un momento global. Cada componente tiene sus propios efectos, ligados a su propio render.
3. **Un hook no "orquesta" a otros hooks en un orden que él decide.** "Hook" es solo el nombre de cualquier función que empieza con `use` (`useState`, `useEffect`, o una tuya). El orden en que se ejecutan lo definís vos, al escribirlos uno después del otro en el cuerpo del componente — React solo exige que ese orden sea siempre el mismo entre renders.

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

## Ejemplos completos, con el vocabulario de Tacha

Cheat sheet de cada hook común, en palabras simples + un ejemplo ligado al dominio de Tacha (household, lista de compras, tachar producto, dashboard de gasto).

**`useState`** — "acordate de este valor entre pantallazos". El caso más literal del nombre del proyecto: tachar un producto.
```tsx
function ItemLista({ producto }: { producto: ProductoLista }) {
  const [tachado, setTachado] = useState(producto.comprado);
  return (
    <div onClick={() => setTachado(!tachado)} className={tachado ? "tachado" : ""}>
      {producto.nombre}
    </div>
  );
}
```

**`useEffect`** — "cuando termines de pintar, hacé esto" (algo que no es puro dibujo: pedir datos, suscribirte, un timer).
```tsx
function PantallaListaCompras({ listaId }: { listaId: string }) {
  const [productos, setProductos] = useState<ProductoLista[]>([]);
  useEffect(() => {
    fetch(`/api/listas/${listaId}/productos`).then((r) => r.json()).then(setProductos);
  }, [listaId]); // se repite solo si listaId cambia (household ↔ lista privada)
  return <ul>{productos.map((p) => <ItemLista key={p.id} producto={p} />)}</ul>;
}
```

**`useRef`** — "guardame un valor entre pantallazos, pero que cambiarlo NO repinte nada".
```tsx
const inputBusquedaProductoRef = useRef<HTMLInputElement>(null);
// más adelante: inputBusquedaProductoRef.current?.focus()
```

**`useMemo`** — "no recalcules esto en cada render, solo si cambian estas dependencias".
```tsx
const gastoTotal = useMemo(
  () => productos.reduce((acc, p) => acc + p.precio, 0),
  [productos]
); // total del dashboard financiero, recalcula solo si productos cambió
```

**`useCallback`** — como `useMemo` pero para funciones: "no crees una función nueva en cada render, solo si cambian las dependencias".
```tsx
const tacharProducto = useCallback((id: string) => {
  setProductos((prev) => prev.map((p) => (p.id === id ? { ...p, comprado: !p.comprado } : p)));
}, []);
```

**`useContext`** — "leeme un valor que alguien más arriba del árbol dejó disponible, sin pasarlo por props en cada nivel".
```tsx
const { household } = useContext(HouseholdContext); // el household activo, disponible en cualquier componente hijo
```

**`useReducer`** — como `useState` pero para estado con varias acciones posibles (ej. los pasos de "modo compra": elegir súper → tachar → confirmar).
```tsx
const [estado, dispatch] = useReducer(reducerModoCompra, { paso: "elegir-super" });
dispatch({ tipo: "producto-tachado", id: "123" });
```

**Hook personalizado (`useAlgo`)** — una función propia que junta varios de los de arriba, para reusar la misma lógica en más de un componente (ej. tanto en "Mi lista" como en la lista del household).
```tsx
function useListaDeCompras(listaId: string) {
  const [productos, setProductos] = useState<ProductoLista[]>([]);
  const [cargando, setCargando] = useState(true);

  useEffect(() => {
    let cancelado = false;
    setCargando(true);
    fetch(`/api/listas/${listaId}/productos`)
      .then((r) => r.json())
      .then((data) => { if (!cancelado) setProductos(data); })
      .finally(() => { if (!cancelado) setCargando(false); });
    return () => { cancelado = true; };
  }, [listaId]);

  function tacharProducto(productoId: string) {
    setProductos((prev) => prev.map((p) => (p.id === productoId ? { ...p, comprado: !p.comprado } : p)));
    fetch(`/api/listas/${listaId}/productos/${productoId}/tachar`, { method: "PATCH" });
  }

  return { productos, cargando, tacharProducto };
}
```
El componente que lo usa queda liviano, sin saber nada de `fetch`:
```tsx
function PantallaListaCompras({ listaId }: { listaId: string }) {
  const { productos, cargando, tacharProducto } = useListaDeCompras(listaId);
  if (cargando) return <p>Cargando...</p>;
  return <ul>{productos.map((p) => <li key={p.id} onClick={() => tacharProducto(p.id)}>{p.nombre}</li>)}</ul>;
}
```

## Errores comunes

- **"Stale closure"**: un `useEffect`/callback captura una variable del render en que se creó y no ve el valor actualizado, porque le faltó esa variable en el array de dependencias. La regla práctica: si el linter de `exhaustive-deps` se queja, casi siempre tiene razón — silenciarlo suele esconder este bug.
- **Hooks condicionales** (ver regla 1 arriba) — el error más directo de "por qué me tira este warning de React".
- **Confundir `useMemo`/`useCallback` con optimización obligatoria**: son para evitar recálculos/re-renders costosos medidos, no un reflejo automático en cada línea — usarlos sin necesidad agrega complejidad sin beneficio real.

## Si el profesor pregunta...

- **"¿Por qué no podés poner ese `useState` dentro del `if`?"** → Porque React identifica cada hook por su posición en una lista interna del componente, no por nombre; saltearlo condicionalmente desalinea todos los hooks siguientes.
- **"¿Qué diferencia hay entre `useEffect` y solo poner el código directo en el cuerpo del componente?"** → El cuerpo corre en cada render de forma síncrona (debe ser puro); `useEffect` corre después de pintar la pantalla y es el lugar correcto para sincronizar con algo externo (red, DOM, timers), con una función de limpieza opcional.
- **"¿Por qué armaste un hook personalizado en vez de poner esa lógica directo en el componente?"** → Para separar responsabilidad (lógica con estado vs. renderizado) y poder reutilizarla/testearla aparte — aplicación directa de SRP.
