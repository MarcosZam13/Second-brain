---
curso: SistemasOperativos
tema: Actividad de Comprobación — Administración de Procesos (Unidad 3)
fecha: 2026-08-27
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3]]"
estado: "borrador — las 5 preguntas respondidas con apoyo de Claude Code (1-3 en modo tutor socrático completo, 4-5 con apoyo más ligero); falta pasada final de Marcos antes de exportar a PDF"
tags: [actividad-comprobacion, unidad3, gestion-procesos, individual]
---

# Actividad de Comprobación — Administración de Procesos

Ver también: [[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3|Instrucciones completas]] · [[Cursos/SistemasOperativos/entregas]]

**Modalidad:** individual · **Valor:** 34 puntos · **Entrega:** documento PDF a TEC Digital (evaluación "Administración de Procesos").

> **Nota sobre uso de IA (2026-08-27):** el `todo-list-semana4.docx` recién subido trae, en su sección de Semana 2, una línea de "sin ayuda de IA" que contradice la política general del curso ya documentada en [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1#Política de uso de IA generativa (aplica a todo el curso)|estructura-sistemas-computo-unidad1.md]] ("el curso no prohíbe el uso de IA generativa... se evalúa su uso crítico, transparente y bien documentado"). Marcos decidió seguir con el modelo de IA-tutor-socrático + bitácora para esta entrega (igual que Semanas 1 y 2) mientras se confirma cuál política aplica realmente — ver bitácora al final.

## Checklist contra la rúbrica

- [x] 1. Análisis de estados de procesos en ejecución real (6 pts) — respondida por Marcos, sesión tutor socrático con Claude Code
- [x] 2. Interpretación del Bloque de Control de Procesos — BCP (6 pts) — respondida por Marcos, sesión tutor socrático con Claude Code
- [x] 3. Cambio de contexto y su costo (8 pts) — respondida por Marcos, sesión tutor socrático con Claude Code
- [x] 4. Estructuras de control del sistema operativo (6 pts) — respondida por Marcos con apoyo de Claude Code
- [x] 5. Escenario integrador de gestión de procesos (8 pts) — respondida por Marcos con apoyo de Claude Code
- [ ] Exportar a PDF y subir a TEC Digital, evaluación "Administración de Procesos"

## Respuestas

*(Preguntas 1-3: respondidas por Marcos en sesión de tutor socrático con Claude Code, él responde primero, la IA señala qué falta o está mal sin dar la respuesta completa, y así hasta cerrar cada pregunta. Preguntas 4-5: Marcos pidió contexto y ayuda para entender mejor los conceptos antes de responder, sin el mismo detalle de ida y vuelta.)*

### 1. Análisis de estados de procesos en ejecución real

Escenario: un computador ejecuta simultáneamente un navegador reproduciendo video, un editor de texto, una app de mensajería y un proceso de actualización del sistema.

- Explicar qué eventos del sistema podrían provocar que un proceso pase de: Ejecutando → Bloqueado; Bloqueado → Listo; Listo → Suspendido.
- Analizar qué situaciones podrían provocar que el SO use los estados Bloqueado/Suspendido y Listo/Suspendido.
- Discutir qué decisiones del SO (gestión de memoria, presión de recursos, planificación del CPU) podrían provocar la suspensión de procesos.

Ejecutando → Bloqueado ocurre cuando un proceso necesita algo externo para seguir funcionando y no lo tiene disponible en el momento. Por ejemplo, el navegador reproduciendo video se bloquea si se queda sin acceso a la red, porque está esperando la conexión para seguir recibiendo datos.

Bloqueado → Listo: cuando eso que esperaba (la conexión, en el ejemplo) vuelve a estar disponible, el proceso no pasa directo a Ejecutando, pasa a Listo, porque ahora tiene que competir de nuevo por CPU. Que haya dejado de estar bloqueado no significa que se ejecute automático: el SO tiene que revisar cuándo le toca turno.

Listo → Suspendido pasa cuando el SO no tiene memoria suficiente para mantener en RAM a todos los procesos activos y decide sacar temporalmente a uno para priorizar otros.

La diferencia entre Bloqueado/Suspendido y Listo/Suspendido: si el SO tiene que elegir a quién sacar de RAM por falta de memoria entre un proceso Bloqueado (esperando algo externo, como la red) y uno Listo (que ya podría ejecutar), conviene sacar primero al Bloqueado, porque no pierde nada ya que de todas formas no iba a poder ejecutar mientras espera. El proceso Listo, en cambio, si se suspende sí pierde la oportunidad de ejecutar en ese momento, algo así como la diferencia entre un proceso de segundo plano que el usuario no va a notar de inmediato, y uno que el usuario sí percibe si se detiene.

Decisiones del SO que provocan suspensión: la presión de memoria (RAM llena, muchos procesos activos compitiendo) obliga al SO a suspender procesos; además, el planificador de CPU prioriza los procesos con los que el usuario interactúa directamente (como el video) sobre los procesos de fondo (como la actualización), así que estos últimos son los primeros candidatos a quedar en espera sin que el usuario se vea afectado.

### 2. Interpretación del BCP

Tabla de procesos con tres procesos activos:

| Proceso | Estado | Prioridad | CPU usada |
|---|---|---|---|
| P1 | Ejecutando | Alta | 25 ms |
| P2 | Listo | Media | 0 ms |
| P3 | Bloqueado | Baja | 10 ms |

- Explicar qué información del BCP es necesaria para que el SO pueda reanudar P3 cuando termine su operación de E/S.
- Discutir qué ocurriría si el SO perdiera o corrompiera parte de la información del BCP de un proceso.
- Analizar por qué el BCP se considera una estructura crítica para la estabilidad del SO.

Para reanudar a P3 exactamente donde se quedó, el SO necesita del BCP: los registros de CPU (los valores con los que estaba trabajando), el contador de programa (la instrucción exacta en la que quedó) y la información de E/S (qué dispositivo estaba usando y qué esperaba de él). Con esas tres piezas, el SO puede cambiar el estado del proceso y reanudar su ejecución tal como estaba.

Si se corrompe el contador de programa, P3 ejecutaría instrucciones erróneas. Si se pierden los registros, retomaría usando datos equivocados. Y si el SO pierde la referencia a qué memoria o archivos tenía asignados P3, esos recursos podrían quedar atrapados sin liberarse nunca (fuga de recursos), o el SO podría dárselos por error a otro proceso mientras P3 todavía los necesita, corrompiendo datos.

El BCP se considera una estructura crítica porque no es solo información de un proceso individual, es la infraestructura que usa el SO para hacer cambio de contexto, planificación de CPU y gestión de recursos en general. Si el BCP falla no es solo que un proceso deje de funcionar, el problema se propaga y puede afectar la capacidad del SO de administrar a todos los demás procesos de forma confiable, generando caos a nivel de todo el sistema.

### 3. Cambio de contexto y su costo

Escenario: el CPU ejecuta un proceso de compilación y ocurre una interrupción para atender una operación de E/S de un dispositivo de almacenamiento.

- Describir qué información del proceso en ejecución debe guardarse durante el cambio de contexto.
- Explicar por qué el cambio de contexto tiene costo computacional aunque no se ejecute trabajo útil.
- Discutir cómo un número excesivo de cambios de contexto afecta el rendimiento.
- Proponer una situación donde reducir cambios de contexto mejore significativamente el desempeño.

Durante el cambio de contexto se guardan los registros de CPU (los datos con los que estaba trabajando el proceso), el contador de programa (la instrucción exacta en la que quedó), el puntero de pila (para no perder el rastro de sus variables locales y a qué funciones llamó) y la información de la memoria que tiene asignada. Sin el puntero de pila y la memoria, el proceso no sabría qué datos usar ni a qué funciones volver cuando lo retomen.

Tiene costo computacional aunque no se ejecute trabajo útil porque copiar registros y contador consume ciclos reales de CPU, y ese tiempo no avanza ni el proceso de compilación ni la operación de E/S (esa la resuelve el controlador de disco, no el CPU). Mientras el CPU se dedica a esta administración, otros procesos con trabajo pendiente, quizás más importante, tienen que esperar.

Un número excesivo de cambios de contexto hace que el CPU pase más tiempo cambiando de proceso que ejecutando instrucciones útiles de esos procesos.

Una situación donde reducir cambios de contexto mejora el desempeño: en el escenario del proceso de compilación, si en vez de generar una interrupción de E/S por cada fragmento pequeño leído del disco se leyeran bloques más grandes de una vez, el proceso se bloquearía menos veces, habría menos cambios de contexto, y se priorizarían mejor las instrucciones realmente importantes del programa.

### 4. Estructuras de control del sistema operativo

Escenario: un sistema ejecuta múltiples procesos accediendo simultáneamente a memoria, archivos y dispositivos de E/S.

- Explicar cómo interactúan: tabla de procesos, tabla de memoria, tabla de archivos, tabla de dispositivos.
- Analizar qué fallos podrían ocurrir si: la tabla de memoria se actualiza incorrectamente / la tabla de archivos pierde sincronización con los procesos / la tabla de dispositivos gestiona mal las operaciones de E/S.
- Discutir cómo el SO previene inconsistencias en estas estructuras.

La tabla de procesos es la que conecta a las otras tres: para cada proceso guarda punteros hacia su entrada en la tabla de memoria (qué páginas o marcos tiene asignados), en la tabla de archivos (qué archivos tiene abiertos y en qué posición) y en la tabla de dispositivos (qué dispositivo de E/S está usando o esperando). El BCP de cada proceso es, en la práctica, el nodo central que une esas cuatro tablas.

Si la tabla de memoria se actualiza mal, un proceso podría terminar accediendo o corrompiendo la memoria de otro. Si la tabla de archivos pierde sincronización, un proceso podría leer o escribir en la posición equivocada de un archivo, o el sistema podría liberar un archivo que otro proceso todavía está usando. Si la tabla de dispositivos gestiona mal las operaciones de E/S, dos procesos podrían terminar con acceso simultáneo a un dispositivo que solo soporta una operación a la vez, como escribir en la misma zona de disco al mismo tiempo, corrompiendo los datos o generando una condición de carrera.

El SO previene estas inconsistencias usando mecanismos de sincronización, como locks o semáforos, cada vez que se modifican estas tablas. También valida cada acceso contra los permisos y el estado real del proceso antes de actualizarlas, y trata la asignación o liberación de recursos como operaciones atómicas, para que un cambio de contexto a mitad de una actualización no deje la tabla en un estado inconsistente.

### 5. Escenario integrador

Escenario: P1 reproduce música, P2 compila un programa, P3 descarga archivos de Internet. Durante la ejecución: P2 comienza a usar intensivamente el CPU; P3 solicita acceso a disco para guardar lo descargado; el sistema detecta presión de memoria y decide suspender temporalmente un proceso.

- Describir cómo evolucionan los estados de los procesos durante estos eventos.
- Explicar qué estructuras del SO intervienen en cada transición.
- Analizar qué problema de gestión de recursos podría aparecer (ej. inanición, sobrecarga de CPU, interbloqueo).
- Proponer mecanismos del SO que podrían evitar o mitigar ese problema.

P1 se mantiene alternando entre Ejecutando y Listo durante todo el escenario, porque es liviano y el SO lo trata como un proceso interactivo prioritario. Cuando P2 empieza a exigir CPU intensivamente, el planificador tiene que repartir turnos con más frecuencia entre los tres procesos. P3 pasa de Ejecutando o Listo a Bloqueado en cuanto solicita escribir a disco, y se queda ahí hasta que esa operación de E/S termine. Cuando el sistema detecta presión de memoria, decide suspender temporalmente al proceso con menos necesidad inmediata de estar en RAM, que probablemente sea P3, porque de todas formas no puede avanzar mientras espera la E/S (queda en Bloqueado/Suspendido).

Las estructuras que intervienen son la tabla de procesos, para llevar estados y prioridades; la tabla de memoria, para decidir a quién sacar de RAM por la presión; la tabla de dispositivos, para gestionar la solicitud de disco de P3; y el planificador de CPU, para repartir el tiempo entre P1 y P2 mientras P2 exige más recursos.

El problema que podría aparecer es inanición de P1: si el planificador prioriza demasiado a P2 por su uso intensivo de CPU, P1 podría no recibir suficiente tiempo de ejecución y la música empezaría a cortarse. También podría darse sobrecarga general de CPU si P2 y la gestión de la presión de memoria compiten al mismo tiempo por recursos.

Para evitarlo o mitigarlo, el SO podría usar planificación con prioridades dinámicas o aging, subiendo gradualmente la prioridad de P1 si lleva tiempo sin recibir CPU, y aplicar una política de suspensión que priorice sacar de RAM a procesos bloqueados como P3 antes que a procesos listos e interactivos, para no afectar la experiencia del usuario con procesos como la música.

## Bitácora de uso de IA

### Proceso general

Para las preguntas 1-3 respondí en un chat con Claude Code en modo tutor socrático, igual que en las Semanas 1 y 2: primero intenté responder cada pregunta con lo que ya sabía, la IA me señalaba qué faltaba o qué estaba mal sin darme la respuesta completa, y yo ajustaba hasta cerrar cada pregunta. Para las preguntas 4 y 5 le pedí a la IA que me diera contexto y me ayudara a entender mejor cómo funcionan los estados de los procesos y las tablas del SO antes de responder, sin el mismo detalle de ida y vuelta que en las primeras tres.

### Notas específicas por pregunta

- **Pregunta 1:** confundí varias transiciones de estado al inicio (pensé que Listo → Suspendido era por pausar el video, no por presión de memoria) y etiqueté mal una de ellas. Con las preguntas guía de la IA llegué solo a la distinción correcta entre Bloqueado/Suspendido y Listo/Suspendido.
- **Pregunta 2:** no tenía claro qué era el BCP, pedí que me lo explicaran antes de responder. Mi primera lista de qué se necesita para reanudar un proceso, y mi explicación de por qué el BCP es crítico, quedaron incompletas; las completé con las preguntas guía de la IA.
- **Pregunta 3:** también pedí que me explicaran qué es un cambio de contexto. Tuve una confusión importante (pensé que ese tiempo avanzaba la operación de E/S) que la IA me ayudó a corregir, y completé con ayuda la lista de qué información se guarda durante el cambio.
- **Pregunta 4:** pedí contexto de la pregunta y ayuda para entender mejor cómo interactúan las tablas del SO (procesos, memoria, archivos, dispositivos) antes de responder.
- **Pregunta 5:** igual pedí contexto y ayuda para entender mejor cómo evolucionan los estados de los procesos en un escenario con varios eventos simultáneos, antes de responder.
