---
tipo: spec
sistema: Hermes
estado: listo-para-implementar
fecha: 2026-08-09
---

# Spec — Check-in diario de sesión de trabajo (22:00, Hermes)

Ver también: [[Sistema/proyecto-segundo-cerebro|Diseño completo del sistema]] (sección 9) · [[Sistema/skills/document-intake/SKILL|document-intake]] (mismo formato de spec para Hermes)

Este documento es para pasarlo tal cual a la sesión de Claude Code que corre dentro de la Raspberry Pi, en el repo de Hermes. No requiere tocar el vault ni Claude Code de la compu — todo el trabajo va en el código/config de Hermes.

## Objetivo

El usuario planea un día de trabajo agrupando varios entregables ("mañana quiero avanzar X, Y y Z"). Sin intervención suya, Hermes le escribe a las 22:00 preguntando qué completó, marca en Todoist lo que confirme, y deja constancia del avance parcial de lo que no terminó — para que la próxima vez que abra el vault, la pregunta "¿qué me falta de X?" tenga una respuesta concreta que leer, no que reconstruir de memoria.

## Modelo de datos: la "tarea de sesión"

Una tarea de Todoist por día de trabajo planeado, con una subtarea por cada entregable que el usuario dijo que iba a tocar. La subtarea es un puntero al entregable real (mismo nombre/tema), **no reemplaza su fecha de vencimiento real** — esa vive en su propia tarea de Todoist, sin tocar.

- **Título de la tarea padre:** `Sesión — {YYYY-MM-DD}`.
- **Label fijo:** `sesion-diaria` (crearlo si no existe) — es lo que el cron usa para encontrar la tarea de hoy, más confiable que hacer match por título.
- **Subtareas:** una por entregable, contenido libre (ej. `Avanzar: Estadística — reporte de regresión`).

**Cómo se crea (v1, alcance de esta spec):** a mano, en Todoist o pidiéndoselo a Hermes en una conversación normal ("armame la sesión de mañana con estos 3: ..."). No hace falta lógica nueva de reconocimiento de intención en Hermes para v1 — simplemente cuando el usuario da esa instrucción explícita, Hermes crea la tarea padre + subtareas con el label `sesion-diaria` usando su acceso directo a Todoist (ya lo tiene, ver `proyecto-segundo-cerebro.md` sección 3, "escribe directo a Todoist para tareas simples"). Reconocer automáticamente frases más ambiguas ("quiero hacer 3 cosas mañana") queda fuera de esta spec — es un fast-follow si el flujo manual se siente bien en la práctica.

## El cron

**Trigger:** todos los días a las 22:00, zona horaria `America/Costa_Rica` (UTC-6, sin horario de verano).

**Implementación:** decisión de quien lo construya, según lo que ya tenga el framework de Hermes Agent — cron del sistema operativo (`crontab -e` en la Pi) llamando a un script que reusa los clientes de Telegram/Todoist ya inicializados de Hermes, o el scheduler propio del framework si tiene uno. No asumir cuál sin revisar el código actual de Hermes.

### Paso 1 — Buscar la sesión de hoy

Query a Todoist: tarea con label `sesion-diaria` y fecha de hoy.

- **No existe ninguna** → no hacer nada. No hay que molestar al usuario en días sin sesión planeada.
- **Existe pero sin subtareas** → no hacer nada (caso mal formado, no debería pasar si se creó siguiendo el modelo de arriba).
- **Existe y todas las subtareas ya están completas** → cerrar la tarea padre si sigue abierta, no enviar check-in (no hay nada que preguntar).
- **Existe con subtareas pendientes** → seguir a Paso 2.

### Paso 2 — Preguntar por Telegram

Mensaje al chat del usuario (Hermes ya tiene el `chat_id` configurado):

```
🌙 Check-in de las 22:00 — tu sesión de hoy tenía pendiente:
1. {subtarea 1}
2. {subtarea 2}
3. {subtarea 3}

¿Cuáles completaste? Respondé con los números o contame en texto libre.
```

Guardar un estado corto ("esperando respuesta de check-in, sesión {fecha}, subtareas {ids}") para que el próximo mensaje del usuario se interprete como respuesta a esto y no como una instrucción nueva. Ese estado expira solo — si no hay respuesta antes de la medianoche (o el margen que el framework maneje mejor para esto), se descarta sin reintentar. No hacer follow-up insistente; una sola pregunta por noche.

### Paso 3 — Procesar la respuesta

Para cada subtarea que el usuario confirme como completada:
- Marcarla como hecha en Todoist directamente (mismo patrón de bajo riesgo que Hermes ya usa para tareas simples — no necesita PR).

Para cada subtarea que **no** se confirme como completada:
- Preguntar en una línea qué se avanzó (si no vino ya en la respuesta): *"¿qué avanzaste de {tema}?"*.
- Con esa respuesta, abrir un PR al vault que **agrega** una entrada con fecha al final de `Cursos/{curso}/entregables/{tema}.md` (crear un apartado `## Notas de progreso` si no existe todavía). Agregar tal cual lo que dijo el usuario, sin interpretar ni reescribir — eso es trabajo de Claude Code en la próxima sesión, no de Hermes (ver "Qué NO hace" en `proyecto-segundo-cerebro.md` sección 3). Si no se puede determinar el `{curso}`/`{tema}` con confianza a partir del contenido de la subtarea, dejarlo en el PR con una nota `<!-- revisar: no se pudo mapear a un entregable existente -->` en vez de adivinar la ruta.

Si al final todas las subtareas quedaron completas, cerrar también la tarea padre.

### Paso 4 — Confirmar

Un mensaje corto por resultado, mismo estilo que el resto de confirmaciones de Hermes:

```
✅ Marcado: {subtarea 1}
📝 PR abierto con tu avance de {subtarea 2} — lo reviso en la próxima sesión de Claude Code
⏳ {subtarea 3} sigue pendiente
```

## Casos borde

- **Más de una tarea con label `sesion-diaria` en el mismo día:** usar la primera encontrada, no debería pasar si la creación sigue el modelo de arriba (una sola por día).
- **Usuario reporta progreso antes de las 22:00, sin que Hermes pregunte:** fuera de alcance de esta spec — es conversación normal de Hermes. Si ya completó todo antes del cron, el Paso 1 lo detecta y no manda check-in.
- **Falla de red/API a las 22:00 en punto:** un reintento simple (ej. a los 10 minutos) es razonable; no se necesita cola de reintentos sofisticada para este volumen (una corrida por día).

## Lo que falta decidir con el código real de Hermes

Esto no se puede resolver desde el vault — depende de cómo esté armado Hermes Agent hoy:

1. Mecanismo de scheduling disponible (cron de SO vs. scheduler del framework).
2. Dónde persiste Hermes estado conversacional de corta duración hoy (para el "esperando respuesta de check-in") — ¿hay algo ya armado, o hay que agregarlo?
3. Cómo Hermes decide a qué `entregable.md` mapea una subtarea cuando el nombre no calza exacto con un archivo existente (regla mínima sugerida arriba: si no hay match claro, dejar nota en el PR en vez de adivinar).
