---
tipo: spec
sistema: Hermes
estado: implementado
fecha: 2026-08-09
fecha_implementacion: 2026-08-09
---

# Spec — Check-in diario de sesión de trabajo (22:00, Hermes)

Ver también: [[Sistema/proyecto-segundo-cerebro|Diseño completo del sistema]] (sección 9) · [[Sistema/skills/document-intake/SKILL|document-intake]] (mismo formato de spec para Hermes)

Este documento es para pasarlo tal cual a la sesión de Claude Code que corre dentro de la Raspberry Pi, en el repo de Hermes. No requiere tocar el vault ni Claude Code de la compu — todo el trabajo va en el código/config de Hermes.

> **Implementado el 2026-08-09** por la sesión de Claude Code de la Pi. El resto del documento queda como diseño original de referencia; la sección [Estado de implementación](#estado-de-implementación-2026-08-09) al final tiene lo que realmente se construyó, incluyendo dos desvíos respecto a esta spec.

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

> **Nota de implementación:** `filter=@sesion-diaria` (sintaxis de filtro de Todoist) es ignorado en silencio por la API real con el token en uso — devuelve las 24 tareas sin filtrar, sin error. Usar los parámetros `label=` y `parent_id=` directos en vez de `filter=`; probados en vivo, sí filtran correctamente.

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

## Estado de implementación (2026-08-09)

Las 3 preguntas abiertas, resueltas contra el código real de Hermes:

1. **Scheduling** → Hermes tiene scheduler propio, confirmado en `cron/scheduler.py` del repo. (El archivo `hermes-already-has-routines.md` que había en la raíz del repo es contenido de marketing, no documentación técnica — no usarlo como referencia.) Cron registrado: `checkin-22h`, `0 22 * * *`, `--deliver telegram:6044624584`. Sobrevivió un restart del servicio en la prueba.
2. **Estado conversacional corto** → no había nada reusable, se construyó desde cero: `~/.hermes/state/checkin_pending.json` + un plugin nuevo `checkin-followup` sobre el hook documentado `pre_gateway_dispatch` (acción `rewrite`), que intercepta el próximo mensaje del chat mientras hay un check-in pendiente y se lo reescribe al agente con instrucciones exactas de qué está respondiendo.
3. **Mapeo subtarea → entregable** → si el archivo no existe o el curso/tema no está claro, el flujo **no** crea el `.md` estructurado ni adivina la ruta — cae a un archivo de revisión en `Sistema/inbox/checkin-{fecha}-revisar.md` con un comentario `<!-- revisar -->`. Esto no estaba en la spec original, fue una decisión de la implementación (ver sección siguiente) — coherente con que crear notas estructuradas en `entregables/` es trabajo de Claude Code, no de Hermes.

**Desvíos respecto a esta spec (documentados para quien la lea después):**
- El filtro `label=`/`parent_id=` en vez de `filter=` (ver nota en Paso 1) — hallazgo no previsto, la API se comporta distinto a lo asumido.
- El fallback a `Sistema/inbox/checkin-{fecha}-revisar.md` para mapeos ambiguos (punto 3 arriba) — la spec original solo decía "dejar nota en el PR", la implementación fue un paso más conservador: ni siquiera abre el PR si no está seguro del destino, deja el archivo crudo en el inbox para que Claude Code lo triage en la próxima sesión.

**Archivos nuevos en el repo de Hermes:**
- `~/.hermes/scripts/{todoist-close-task.sh, todoist-create-session.sh, checkin_daily.py, checkin_state.py}`
- `~/.hermes/plugins/checkin-followup/{plugin.yaml, __init__.py}` (agregado a `plugins.enabled` en `config.yaml`)
- `SOUL.md` sección 6 — crear la tarea de sesión a pedido por conversación (cubre el "v1" de creación manual descrito arriba en "Cómo se crea").

**Verificado en vivo antes de dar por cerrado:** dry-run de `checkin_daily.py` sin sesión creada hoy → silencio correcto (no manda mensaje); `checkin_state.py show/resolve/clear` funcionando; `todoist-create-session.sh` probado contra Todoist real y limpiado después; plugin cargado (`hermes plugins list` → enabled, sin errores en logs); cron sobrevivió el restart del servicio. Próxima corrida real: hoy, 22:00 (zona horaria del sistema ya es Costa Rica, no hizo falta configurarla aparte).

## Incidente 2026-08-09 (primera corrida real) y fixes del 2026-08-10

La primera corrida real del cron (2026-08-09, 22:00) tuvo 3 fallas, encontradas revisando `~/.hermes/logs/agent.log` y la base de mensajes contra el estado real de Todoist/git, no confiando en la confirmación que el propio modelo mandó por Telegram (que reportó éxito en los 3 casos, siendo 2 de esos 3 falsos):

1. **ID de subtarea mal transcrito al cerrarla en Todoist.** El modelo mezcló el prefijo del ID de una subtarea con el sufijo de otra al armar el comando de cierre → Todoist devolvió 404 → la subtarea no se cerró, pero el mensaje de confirmación dijo "✅ Marcado" igual (no revisó el resultado del tool call). Recurrencia del patrón de alucinación de IDs ya visto antes con modelos chicos. Mitigado con la nota explícita "no inventes IDs" ya existente en el template — sigue siendo un riesgo inherente a que un modelo transcriba IDs de memoria en vez de copiarlos; ver punto 3 del extended abajo para cómo se reduce further en el flujo de entrega.
2. **`checkin_state.py` (Python) invocado con `bash` en vez del intérprete del venv**, las 4 veces del turno, pese a que las instrucciones daban el comando exacto con la ruta completa al venv — el modelo generalizó el patrón `bash <script>` que usan el resto de scripts del turno (`.sh`) y lo aplicó también al `.py`. Resultado: `~/.hermes/state/checkin_pending.json` nunca se actualizó (`resolved` quedó en `false` para las 3 subtareas pase lo que pasara en Todoist). Fix: en vez de reforzar la instrucción (ya había fallado reforzada), se eliminó el caso especial — `~/.hermes/scripts/checkin-state.sh` es ahora un wrapper bash de una línea sobre `checkin_state.py`, así que **todos** los scripts del flujo se invocan igual (`bash <ruta>`), sin ninguna excepción que el modelo pueda aplanar mal.
3. **PR del avance nunca se abrió** — el `git commit` falló con `Author identity unknown` (nunca se había configurado `user.name`/`user.email` en el clone del vault en el Pi, porque hasta esa noche nunca se había hecho un commit desde ahí). El archivo quedó `git add`eado pero no commiteado ni pusheado, y el bot igual dijo "📝 PR abierto". Fix: `git config` local (no `--global`) en `~/.hermes/vault`, mismo autor que usa Marcos en sus commits (`MarcosZam13` + su email noreply de GitHub), para no romper la convención de historial existente.

**Extensión 2026-08-10 — "entregué" cierra también la tarea real, no solo el tracker del día:** hasta acá el check-in solo marcaba la subtarea `Avanzar: X` bajo `Sesión — {fecha}` (un tracker interno), nunca la tarea real de Todoist con la fecha de entrega real puesta por el profesor — a propósito, según el diseño original (sección "Modelo de datos" arriba). Marcos pidió agregar que decir explícitamente que **entregó** (no solo que terminó) cierre también esa tarea real.

Implementación, deliberadamente sin dejar que el modelo adivine ningún ID nuevo (dado el punto 1 de arriba):
- `~/.hermes/scripts/todoist-match-entregable.py` — matching determinístico en código, no en el modelo: adivina el label del curso por palabras clave en el texto libre del entregable, y entre las tareas reales abiertas con ese label elige la de vencimiento más próximo (heurística validada contra los 3 casos reales del 2026-08-09: video de CompuYSociedad, "SO que vence el jueves", reporte audiovisual de Seminario — los tres calzaron con la tarea real correcta).
- `todoist-create-session.sh` corre ese matcher al crear cada subtarea y, si hay match, guarda el ID de la tarea real en el campo `description` de la subtarea (`entregable_task_id:<id>`) — el modelo nunca lo escribe, solo lo copia de ahí en el momento del check-in.
- `checkin_daily.py` lee ese `description` al armar `checkin_pending.json` y lo propaga como campo `entregable_task_id` por subtarea (`null` si no hubo match).
- El plugin `checkin-followup` lista esa tarea vinculada junto a cada subtarea en las instrucciones reescritas, y agrega un paso que cierra la tarea real con `todoist-close-task.sh` (el mismo script ya existente, sin uno nuevo) **solo** si el usuario usó lenguaje explícito de entrega ("lo entregué", "lo mandé", "lo subí", "está entregado") — decir solo que está listo/terminado/hecho no alcanza, sigue sin tocar la tarea real.

**Verificado en vivo:** matcher probado contra Todoist real con los 3 textos reales de anoche (los 3 calzaron); sesión de prueba creada con fecha descartable (2099-01-01) para confirmar que `description` queda bien escrito en la subtarea real, y borrada después; subtarea de Sistemas Operativos de la corrida del 2026-08-09 cerrada a mano con el ID correcto; PR del avance pendiente abierto ([#2](https://github.com/MarcosZam13/Second-brain/pull/2)); servicio reiniciado, plugin sigue cargando sin errores (`hermes plugins list` → enabled).

## Qué hacer si aparece `Sistema/inbox/checkin-{fecha}-revisar.md`

Este archivo nuevo lo deja Hermes cuando el check-in de las 22:00 recibe avance de una subtarea que no pudo mapear con confianza a un `Cursos/{curso}/entregables/{tema}.md` existente. Al encontrarlo en el inbox:

1. Leerlo — trae la fecha, la subtarea original y lo que el usuario reportó como avance, tal cual lo escribió (sin interpretar de parte de Hermes).
2. Decidir el curso/tema real (preguntarle al usuario si no es obvio) y buscar si ya existe el entregable correspondiente.
3. Agregar el avance a la sección `## Notas de progreso` de ese `entregable.md` (crearla si no existe), igual que haría el flujo normal del check-in cuando sí logra mapear.
4. Borrar `checkin-{fecha}-revisar.md` del inbox una vez incorporado — es un archivo de enrutamiento efímero, no una fuente que deba archivarse en `_fuentes/` (mismo criterio que los `.contexto.txt` de `document-intake`).
