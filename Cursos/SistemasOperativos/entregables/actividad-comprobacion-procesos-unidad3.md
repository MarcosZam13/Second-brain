---
curso: SistemasOperativos
tema: Actividad de Comprobación — Administración de Procesos (Unidad 3)
fecha: 2026-08-27
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3]]"
estado: "borrador — respuestas de fondo completas (armadas con Claude Code, modelo IA-tutor-socrático del curso), falta pasar por revisión propia de Marcos antes de exportar a PDF"
tags: [actividad-comprobacion, unidad3, gestion-procesos, individual]
---

# Actividad de Comprobación — Administración de Procesos

Ver también: [[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3|Instrucciones completas]] · [[Cursos/SistemasOperativos/entregas]]

**Modalidad:** individual · **Valor:** 34 puntos · **Entrega:** documento PDF a TEC Digital (evaluación "Administración de Procesos").

> **Nota sobre uso de IA (2026-08-27):** el `todo-list-semana4.docx` recién subido trae, en su sección de Semana 2, una línea de "sin ayuda de IA" que contradice la política general del curso ya documentada en [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1#Política de uso de IA generativa (aplica a todo el curso)|estructura-sistemas-computo-unidad1.md]] ("el curso no prohíbe el uso de IA generativa... se evalúa su uso crítico, transparente y bien documentado"). Marcos decidió seguir con el modelo de IA-tutor-socrático + bitácora para esta entrega (igual que Semanas 1 y 2) mientras se confirma cuál política aplica realmente — ver bitácora al final.

## Checklist contra la rúbrica

- [x] 1. Análisis de estados de procesos en ejecución real (6 pts) — borrador de Claude Code, falta revisión propia
- [x] 2. Interpretación del Bloque de Control de Procesos — BCP (6 pts) — borrador de Claude Code, falta revisión propia
- [x] 3. Cambio de contexto y su costo (8 pts) — borrador de Claude Code, falta revisión propia
- [x] 4. Estructuras de control del sistema operativo (6 pts) — borrador de Claude Code, falta revisión propia
- [x] 5. Escenario integrador de gestión de procesos (8 pts) — borrador de Claude Code, falta revisión propia
- [ ] Reescribir cada respuesta en palabras propias de Marcos (evidencia de razonamiento propio, mismo criterio de S1/S2)
- [ ] Exportar a PDF y subir a TEC Digital, evaluación "Administración de Procesos"

## Respuestas

*(Borrador armado con Claude Code sobre los enunciados del [[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3|apunte de instrucciones]] — falta la pasada de Marcos a palabras propias antes de entregar.)*

### 1. Análisis de estados de procesos en ejecución real

**Ejecutando → Bloqueado:** ocurre cuando un proceso pide un recurso o dato que no está disponible de inmediato — el navegador se queda sin datos de video en el buffer y tiene que esperar la red, la app de mensajería espera una respuesta del socket, o el proceso de actualización espera a que termine una escritura a disco. En todos esos casos el SO mueve el proceso a Bloqueado en vez de dejarlo consumir CPU haciendo espera activa.

**Bloqueado → Listo:** cuando el evento esperado finalmente ocurre (llegan los datos de red, termina la operación de disco), el SO recibe la interrupción correspondiente y mueve el proceso a Listo — no pasa directo a Ejecutando, tiene que volver a competir por CPU con el planificador.

**Listo → Suspendido:** cuando hay demasiados procesos compitiendo por memoria principal, el SO puede sacar temporalmente de RAM (a disco) al proceso de menor prioridad que esté en Listo — por ejemplo, si la actualización del sistema (baja prioridad) está compitiendo por memoria contra el navegador, el editor y la mensajería, que el usuario está usando activamente en ese momento.

**Bloqueado/Suspendido vs. Listo/Suspendido:** el SO usa **Bloqueado/Suspendido** cuando decide liberar memoria de un proceso que de todas formas está esperando algo — no se pierde nada porque no iba a poder ejecutar pronto (ej. la mensajería esperando respuesta de red por buen rato). Usa **Listo/Suspendido** cuando el proceso sí podría ejecutar ya, pero no hay espacio o prioridad suficiente para mantenerlo en RAM — ej. sacar temporalmente al editor de texto (listo, pero inactivo porque el usuario no lo está usando en ese instante) si de repente se abre otra aplicación de mayor prioridad y hay presión de memoria.

**Decisiones del SO que provocan suspensión:** presión de memoria (RAM llena y hay que hacer espacio), acumulación de procesos activos simultáneos, y decisiones del planificador de CPU que priorizan procesos interactivos (el navegador reproduciendo video, que el usuario nota si falla) sobre procesos de fondo (la actualización del sistema, que puede esperar sin que el usuario lo note).

### 2. Interpretación del BCP

**Información necesaria para reanudar P3:** el BCP debe conservar el contador de programa (PC) en el punto exacto donde P3 se bloqueó, el contenido de sus registros de CPU, el detalle de la operación de E/S pendiente (qué esperaba y su resultado), su prioridad, los punteros a la memoria que tiene asignada, y su estado actual. Con eso el SO puede restaurar el contexto de P3 exactamente como estaba, apenas termine la operación de E/S.

**Qué pasa si se pierde o corrompe el BCP:** P3 no podría reanudarse de forma confiable — un PC corrupto haría que ejecute instrucciones equivocadas, registros perdidos harían que retome con datos incorrectos, y si se pierde la referencia a qué recursos (memoria, archivos abiertos) tenía asignados, el SO podría no liberarlos nunca (fuga de recursos) o liberarlos mientras el proceso todavía los necesita, lo que puede terminar en comportamiento indefinido o en la caída del sistema.

**Por qué es una estructura crítica:** porque es la única fuente de verdad que tiene el SO sobre cada proceso — sin un BCP correcto no hay cambio de contexto confiable, ni planificación, ni contabilidad de recursos. Toda la gestión de multiprogramación depende de que esa información esté siempre íntegra y actualizada.

### 3. Cambio de contexto y su costo

**Qué se guarda:** el contador de programa, todos los registros de CPU (propósito general y de estado), el puntero de pila y la información de memoria (tablas de páginas) del proceso saliente — todo dentro de su BCP.

**Por qué tiene costo aunque no ejecute trabajo útil:** guardar y restaurar registros consume ciclos de CPU por sí solo, y además invalida las cachés (L1/L2) y el TLB, que tenían datos "calientes" del proceso anterior. El proceso entrante arranca con cachés frías, así que sus primeras instrucciones son más lentas mientras se vuelven a poblar — ese tiempo es puro overhead administrativo, no trabajo del programa.

**Cómo afecta un número excesivo de cambios de contexto:** si el CPU cambia de proceso con demasiada frecuencia (quantum muy corto, o demasiadas interrupciones de E/S), pasa más tiempo haciendo el cambio en sí que ejecutando instrucciones reales de esos procesos — el CPU puede parecer ocupado al 100% mientras el trabajo útil real baja.

**Situación donde reducir cambios de contexto mejora el desempeño:** agrupar operaciones de E/S similares (por ejemplo, que el compilador lea bloques más grandes de una vez en vez de generar una interrupción por cada fragmento pequeño de disco leído) reduce cuántas veces ese proceso se bloquea y sufre cambio de contexto, dejándolo correr más tiempo seguido y aprovechando mejor las cachés ya calientes.

### 4. Estructuras de control del sistema operativo

**Cómo interactúan las tablas:** la tabla de procesos referencia, para cada proceso, punteros hacia su entrada en la tabla de memoria (qué páginas/marcos tiene asignados), en la tabla de archivos (qué archivos tiene abiertos y en qué posición) y en la tabla de dispositivos (qué dispositivo de E/S está usando o esperando). El BCP de cada proceso es, en la práctica, el nodo central que conecta esas cuatro tablas.

**Fallos posibles:**
- Tabla de memoria mal actualizada → un proceso podría terminar accediendo (o corrompiendo) memoria de otro proceso.
- Tabla de archivos desincronizada → un proceso podría leer/escribir en la posición equivocada de un archivo, o el sistema podría liberar un archivo que otro proceso sigue usando.
- Tabla de dispositivos mal gestionada → dos procesos podrían recibir acceso simultáneo a un dispositivo que solo soporta una operación a la vez (ej. escribir en la misma zona de disco al mismo tiempo), corrompiendo los datos o generando una condición de carrera.

**Cómo el SO previene inconsistencias:** usando mecanismos de sincronización (locks, semáforos) al modificar estas tablas, validando cada acceso contra los permisos y el estado real del proceso antes de actualizarlas, y tratando la asignación/liberación de recursos como operaciones atómicas, para que un cambio de contexto a mitad de una actualización no deje la tabla en un estado inconsistente.

### 5. Escenario integrador

**Evolución de los estados:** P1 (música) se mantiene alternando Ejecutando/Listo — es liviano y probablemente tratado como interactivo/prioritario. Cuando P2 (compilación) empieza a exigir CPU intensivamente, el planificador tiene que repartir turnos con más frecuencia entre los tres procesos. P3 (descarga) pasa de Ejecutando/Listo a **Bloqueado** en cuanto solicita escribir a disco, hasta que esa operación de E/S termine. Cuando el sistema detecta presión de memoria, decide suspender temporalmente al proceso con menos necesidad inmediata de estar en RAM — probablemente P3, que de todas formas no puede avanzar mientras espera la E/S (**Bloqueado/Suspendido**).

**Estructuras que intervienen:** la tabla de procesos (estados y prioridades), la tabla de memoria (a quién sacar de RAM por presión), la tabla de dispositivos (gestiona la solicitud de disco de P3), y el planificador de CPU (reparte tiempo entre P1 y P2 mientras P2 exige más recursos).

**Problema que podría aparecer:** inanición de P1 — si el planificador prioriza demasiado a P2 por su uso intensivo de CPU, P1 podría no recibir suficiente tiempo de ejecución y la música empezaría a cortarse. También podría darse sobrecarga general de CPU si P2 y la gestión de la presión de memoria compiten al mismo tiempo por recursos.

**Mecanismos para evitarlo o mitigarlo:** planificación con prioridades dinámicas o *aging* (subir gradualmente la prioridad de P1 si lleva tiempo sin recibir CPU, para evitar inanición), y una política de suspensión que priorice sacar de RAM a procesos bloqueados (como P3) antes que a procesos listos e interactivos, para no penalizar la experiencia del usuario con procesos como la música.

## Bitácora de uso de IA

**Proceso general (borrador, revisar y completar con el proceso real de Marcos):** le pedí a Claude Code que armara un primer borrador completo de las 5 respuestas usando los enunciados exactos del apunte de instrucciones, apoyándose en los conceptos de estados de procesos, BCP, cambio de contexto y estructuras de control ya vistos en clase. Falta la pasada real de Marcos: leer cada respuesta, ajustar razonamiento propio, y documentar acá qué cambió respecto al borrador (igual que se hizo en las bitácoras de Semana 1 y 2).
