# Principios SOLID

Ver también: [[Sistema/aprendizaje/README|Aprendizaje]] · [[Sistema/aprendizaje/que-es-un-hook|que-es-un-hook.md]] · [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]]

Cinco reglas de diseño orientado a objetos (Robert C. Martin, años 2000) para que el código sea fácil de cambiar sin romper cosas que no deberían romperse. Nacieron pensando en clases, pero en un mundo de React/TypeScript con funciones, componentes y hooks siguen aplicando — solo cambia el vocabulario ("clase" → "componente", "hook" o "módulo").

**Por qué importan y no son solo teoría:** todos apuntan al mismo problema — *acoplamiento*. Código acoplado es código donde tocar una cosa obliga a tocar otras cinco. SOLID es una checklist para detectar acoplamiento antes de que duela.

## S — Single Responsibility Principle (Responsabilidad Única)

Una clase/función/componente debe tener **una sola razón para cambiar**.

No es "una función debe hacer una sola cosa" en sentido literal (eso es más una regla de tamaño) — es que si dos motivos de negocio distintos pueden forzar un cambio en el mismo archivo, ese archivo tiene dos responsabilidades mezcladas.

```tsx
// Mal: este componente cambia si cambia el diseño de la tarjeta
// Y si cambia la lógica de negocio de "quién puede postularse"
// Y si cambia cómo se llama a la API.
function AsistenciaCard({ asistencia }: { asistencia: Asistencia }) {
  const [loading, setLoading] = useState(false);

  async function postularse() {
    setLoading(true);
    const res = await fetch(`/api/asistencias/${asistencia.id}/postular`, { method: "POST" });
    if (!res.ok) throw new Error("No se pudo postular");
    setLoading(false);
  }

  const puedePostularse =
    asistencia.estado === "abierta" &&
    asistencia.cuposDisponibles > 0 &&
    !asistencia.yaPostulado;

  return (
    <div className="card">
      <h3>{asistencia.titulo}</h3>
      {puedePostularse && <button onClick={postularse} disabled={loading}>Postularme</button>}
    </div>
  );
}
```

```tsx
// Bien: cada pieza tiene un solo motivo para cambiar.
// Reglas de negocio, aparte:
function puedePostularse(asistencia: Asistencia): boolean {
  return asistencia.estado === "abierta" && asistencia.cuposDisponibles > 0 && !asistencia.yaPostulado;
}

// Acceso a datos, aparte (además reutilizable en otros componentes):
function usePostularseAAsistencia(asistenciaId: string) {
  const [loading, setLoading] = useState(false);
  async function postularse() {
    setLoading(true);
    try {
      const res = await fetch(`/api/asistencias/${asistenciaId}/postular`, { method: "POST" });
      if (!res.ok) throw new Error("No se pudo postular");
    } finally {
      setLoading(false);
    }
  }
  return { postularse, loading };
}

// El componente solo compone y renderiza:
function AsistenciaCard({ asistencia }: { asistencia: Asistencia }) {
  const { postularse, loading } = usePostularseAAsistencia(asistencia.id);
  return (
    <div className="card">
      <h3>{asistencia.titulo}</h3>
      {puedePostularse(asistencia) && (
        <button onClick={postularse} disabled={loading}>Postularme</button>
      )}
    </div>
  );
}
```

Si mañana la regla de "quién puede postularse" cambia (por ejemplo, `AS-13` del backlog de Asistencias TEC agrega requisitos de cumplimiento), se toca `puedePostularse` y nada más — no hay que releer JSX para encontrar la lógica de negocio escondida ahí adentro.

## O — Open/Closed Principle (Abierto/Cerrado)

El código debe estar **abierto a extensión, cerrado a modificación**: agregar un comportamiento nuevo no debería requerir editar código que ya funciona y ya se probó.

```ts
// Mal: cada canal de notificación nuevo obliga a tocar esta función y su switch.
function notificar(tipo: "email" | "sms" | "push", mensaje: string) {
  if (tipo === "email") enviarEmail(mensaje);
  if (tipo === "sms") enviarSms(mensaje);
  if (tipo === "push") enviarPush(mensaje);
}
```

```ts
// Bien: agregar un canal nuevo es agregar un objeto que cumple el contrato,
// no editar la función que ya funcionaba.
interface CanalNotificacion {
  enviar(mensaje: string): Promise<void>;
}

class CanalEmail implements CanalNotificacion {
  async enviar(mensaje: string) { /* ... */ }
}

class CanalPush implements CanalNotificacion {
  async enviar(mensaje: string) { /* ... */ }
}

async function notificar(canales: CanalNotificacion[], mensaje: string) {
  await Promise.all(canales.map((c) => c.enviar(mensaje)));
}
```

En React esto se ve todo el tiempo como **composición vía props/children** en vez de meter un `if` nuevo dentro de un componente ya existente cada vez que aparece un caso especial.

## L — Liskov Substitution Principle (Sustitución de Liskov)

Si `B` es un subtipo de `A`, cualquier código que funcione con `A` debe seguir funcionando si le pasás un `B`, sin sorpresas.

El ejemplo clásico: un `Cuadrado extends Rectangulo` que fuerza `alto === ancho` rompe el contrato de `Rectangulo` (setear el ancho no debería cambiar el alto). El código que espera un `Rectangulo` genérico se comporta distinto sin razón aparente.

En TypeScript aparece menos con herencia de clases (React no usa herencia para componentes) y más en **contratos de interfaz/tipos**: si una función espera `{ id: string; nombre: string }`, cualquier objeto que "extienda" ese tipo no debería cambiar el significado de `id` o `nombre` (por ejemplo, que `id` pase de ser único a ser opcional en un subtipo rompe todo el código que asumía que siempre existe).

## I — Interface Segregation Principle (Segregación de Interfaces)

Mejor muchas interfaces chicas y específicas que una interfaz gigante que todos implementan a medias.

```ts
// Mal: una interfaz "todo en uno" para todos los roles del backlog de Asistencias TEC.
interface Usuario {
  verPerfil(): void;
  editarPerfil(): void;
  postularseAAsistencia(id: string): void; // solo aplica a estudiante
  aceptarPostulante(id: string): void;      // solo aplica a profesor
  crearAsistencia(): void;                  // solo aplica a super admin
}
```

```ts
// Bien: cada rol depende solo de lo que usa.
interface PerfilUsuario {
  verPerfil(): void;
  editarPerfil(): void;
}
interface AccionesEstudiante {
  postularseAAsistencia(id: string): void;
}
interface AccionesProfesor {
  aceptarPostulante(id: string): void;
}
interface AccionesSuperAdmin {
  crearAsistencia(): void;
}
```

Con `props` de componentes pasa igual: un componente que recibe un objeto `props` gigante con 15 campos, de los cuales solo usa 3, está acoplado a cosas que no le importan — cualquier cambio en los otros 12 puede romper su tipado sin necesidad.

## D — Dependency Inversion Principle (Inversión de Dependencias)

Los módulos de alto nivel (reglas de negocio) no deben depender de módulos de bajo nivel (detalles de implementación como "esto habla con Postgres" o "esto llama a este endpoint"). Ambos deben depender de una **abstracción**.

```ts
// Mal: la lógica de negocio conoce el detalle de implementación (fetch, la URL exacta).
async function obtenerAsistenciasDisponibles() {
  const res = await fetch("https://api.asistencias.tec.ac.cr/v1/asistencias?estado=abierta");
  return res.json();
}
```

```ts
// Bien: la lógica de negocio depende de un contrato, no de fetch ni de una URL.
interface AsistenciasRepository {
  obtenerDisponibles(): Promise<Asistencia[]>;
}

class AsistenciasApiRepository implements AsistenciasRepository {
  async obtenerDisponibles() {
    const res = await fetch("https://api.asistencias.tec.ac.cr/v1/asistencias?estado=abierta");
    return res.json();
  }
}

// El componente/hook recibe la abstracción, no la implementación concreta:
function useAsistenciasDisponibles(repo: AsistenciasRepository) {
  return useQuery(["asistencias"], () => repo.obtenerDisponibles());
}
```

Esto es lo que hace posible **testear sin pegarle a la API real** (le pasás un `repo` falso en el test — clave para Playwright/tests de integración) y lo que hace posible cambiar de backend sin tocar la lógica de negocio.

## Si el profesor pregunta...

- **"¿Por qué separaste esto en dos archivos/funciones?"** → SRP: cada uno cambia por un motivo distinto (regla de negocio vs. UI vs. acceso a datos).
- **"¿Por qué no metiste un `if` más acá?"** → OCP: agregar un caso no debería tocar código que ya funciona; se extiende con una pieza nueva, no editando la existente.
- **"¿Cómo testeás esto sin llamar a la API real?"** → DIP: la lógica depende de una interfaz/contrato, así que en el test le inyectás una implementación falsa (mock/stub) que cumple el mismo contrato.
- **"¿Por qué esta interfaz/props es tan chica?"** → ISP: nadie debería depender de campos/métodos que no usa.
