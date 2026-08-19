---
curso: SistemasOperativos
tema: Actividad en Equipos — Solución basada en Principios de los SO (Semanas 1-3)
fecha: 2026-08-12
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]]"
estado: borrador
fuente:
  - _fuentes/SistemasOperativos_actividad-equipos-fase1-3-documento_2026-08-18.docx
  - _fuentes/SistemasOperativos_actividad-equipos-diagrama-bloques_2026-08-18.jpeg
  - _fuentes/SistemasOperativos_actividad-equipos-distribucion-guion_2026-08-18.jpeg
  - _fuentes/SistemasOperativos_actividad-equipos-presentacion-final_2026-08-18.pdf
tags: [actividad-equipos, trabajo-grupal, fase1]
---

# Actividad en Equipos — Solución basada en Principios de los SO

Ver también: [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]] · [[Cursos/SistemasOperativos/entregas]] · [[Cursos/SistemasOperativos/entregables/guion-presentacion-actividad-equipos|Guión de la presentación]]

**Entrega (Fase 4 — presentación):** 2026-08-20 (inicio semana 3), ~5 min por grupo.
**Estado actual:** Fases 1-3 completas (documento del equipo + diagrama + slides de la presentación ya armados por Mario/Joseph). Falta cerrar el guión de exposición — ver [[Cursos/SistemasOperativos/entregables/guion-presentacion-actividad-equipos|guión]] para el reparto por diapositiva y el texto de cada parte.

## Checklist contra la rúbrica

- [x] Identificación del Problema — claridad, relevancia, justificación (10%)
- [x] Originalidad de la Solución — creatividad, innovación, justificación (20%)
- [x] Integración de Componentes del SO — coherencia, funcionalidad, eficiencia (25%)
- [x] Diseño Preliminar — claridad, estructura, viabilidad (20%)
- [ ] Presentación de la Propuesta — claridad, organización, comunicación (15%) — pendiente ensayar guión
- [ ] Reflexión sobre el Aprendizaje — profundidad, conexión, autoevaluación (10%) — falta decidir qué punto dice Marcos

## Opciones de problema en evaluación (pendiente decisión del equipo)

### 1. Condiciones de carrera en un sistema de reservas concurrente ⭐ recomendada
**Principio de SO:** concurrencia y sincronización.
**Problema:** múltiples usuarios reservando el mismo recurso (asiento/boleto) al mismo tiempo sin control de acceso, generando ventas duplicadas.
**Por qué funciona:** diagrama de bloques simple (mutex/semáforo), da pie a hablar de deadlock/starvation como desafíos técnicos, ejemplo real conocido (venta de boletos).

### 2. Inanición (starvation) en una cola de impresión o tickets de soporte con prioridades
**Principio de SO:** gestión de procesos / planificación del CPU.
**Problema:** trabajos de baja prioridad nunca se ejecutan porque siempre llegan trabajos de mayor prioridad.
**Por qué funciona:** se conecta con planificación del CPU (semanas 4-6 del curso), buen diagrama de estados de proceso.

### 3. Inconsistencia de datos en un sistema de archivos sincronizado entre varios dispositivos (mini Dropbox)
**Principio de SO:** sistemas de archivos distribuidos.
**Problema:** conflictos de versión cuando el mismo archivo se edita desde dos dispositivos sin conexión simultánea.
**Por qué funciona:** es la opción más distinta al ejemplo del profesor (mejor nota en originalidad); permite hablar de réplica y versionado.

### 4. Escalación de privilegios en un sistema multiusuario embebido (ej. dispositivo IoT compartido)
**Principio de SO:** seguridad en gestión de procesos.
**Problema:** un usuario sin privilegios logra ejecutar acciones reservadas a administrador por falta de aislamiento entre procesos.
**Por qué funciona:** conecta con lo de NX/DEP ya trabajado en las Preguntas de Sesión Semana 1 — reutilizable ese razonamiento.

## Fase 1 — Identificación del Problema (una vez elegido)

*(borrador con la opción 1 — pendiente de confirmar con el resto del equipo)*

- **Problema elegido:** condiciones de carrera en la venta de boletos de un concierto. Varios usuarios intentan comprar el mismo asiento (o el mismo boleto general con cupo limitado) al mismo tiempo, desde distintos dispositivos, y el sistema debe garantizar que solo una compra tenga éxito por unidad disponible.
- **Justificación (por qué requiere principios de SO):** si dos procesos/hilos leen la disponibilidad, la ven libre y confirman la compra antes de que el otro actualice el dato, se produce sobreventa — dos personas "compran" el mismo boleto. Esto es un caso clásico de condición de carrera sobre un recurso compartido, y solo se resuelve con mecanismos de sincronización (exclusión mutua) que el curso cubre en concurrencia; no es un problema que se arregle a nivel de interfaz o de lógica de negocio.
- **Componentes del SO involucrados:**
  - Gestión de procesos/hilos — cada solicitud de compra concurrente se modela como un proceso o hilo compitiendo por el mismo recurso.
  - Sincronización (mutex/semáforo) — protege la sección crítica "verificar disponibilidad + reservar boleto" para que se ejecute como una operación atómica.
  - Memoria/recurso compartido — la tabla de disponibilidad de boletos es el dato compartido que hay que proteger.
  - (a explorar en Fase 2) comunicación entre procesos, si el diseño contempla varios servidores de venta en paralelo.
- **Roles del equipo:** líder — Marcos Zamora / investigador — Mario Rojas / documentador — Joseph Fonseca

## Fase 2 — Conceptualización de la Solución (semana 2)

*(borrador con la opción 1 — idea para llevar a clase, pendiente de discutir con el equipo)*

### Idea general

En vez de dejar que todas las solicitudes de compra compitan libremente por el mismo boleto (que es lo que provoca la condición de carrera), la solución serializa el acceso en dos niveles:

1. **Cola de solicitudes ("sala de espera virtual"):** cada intento de compra entra a una cola FIFO en lugar de intentar reservar directamente. Un grupo reducido de "hilos trabajadores" va tomando solicitudes de la cola y las procesa una por una contra el recurso compartido. Esto es lo mismo que hacen sistemas reales de venta de entradas (Ticketmaster y similares) para evitar que miles de solicitudes simultáneas colapsen el recurso — es el elemento de originalidad de la propuesta, y conecta directo con planificación de procesos (la cola se comporta como una cola de listos, los trabajadores como el CPU atendiendo turnos).
2. **Sección crítica protegida:** dentro de cada trabajador, la operación "verificar disponibilidad → reservar boleto → descontar del inventario" se ejecuta como bloque atómico usando un **semáforo contador** inicializado en la cantidad de boletos disponibles (no un mutex simple, porque no es un recurso binario sino *N* unidades). Cada compra exitosa hace `wait()`/`P()` sobre el semáforo; si llega a 0, las siguientes solicitudes de la cola reciben "agotado" en vez de bloquearse indefinidamente.
3. **Balanceo de cargas (sugerencia del profesor, tras revisión):** en vez de un único grupo de trabajadores atendiendo toda la cola, la cantidad de trabajadores activos por componente se reparte/escala según la carga entrante — un balanceador distribuye las solicitudes entrantes entre varias instancias de "trabajador" en paralelo, en lugar de que todas compitan por sacar de una sola cola servida por un número fijo de hilos. Refuerza el argumento de "Integración de Componentes del SO" (rúbrica) porque conecta directamente con planificación de procesos: el balanceador decide a qué trabajador asignar cada solicitud, de forma similar a cómo un planificador de CPU reparte procesos entre núcleos.
4. **Procesos asíncronos para trabajo no crítico (idea propia, a proponer al equipo):** todo lo que no es indispensable para completar la compra en sí (ej. envío de confirmación por correo, generación del boleto/PDF, notificaciones) se saca de la ruta crítica y se dispara como proceso asíncrono *después* de que la venta ya se confirmó — no bloquea al trabajador ni compite por el semáforo del inventario durante el pico de tráfico. Esto reduce la carga sobre el recurso compartido justo cuando más contención hay, y es coherente con el patrón real de sistemas de venta de boletos (la confirmación llega unos segundos/minutos después de la compra, no en el mismo instante).

### Por qué resuelve el problema de Fase 1

- Elimina la condición de carrera: nunca hay dos trabajadores modificando el inventario al mismo tiempo sin protección, porque el semáforo obliga a que la lectura+escritura del contador sea atómica.
- Evita la sobreventa incluso bajo picos de tráfico, porque el cuello de botella se mueve a la cola (que sí puede crecer) en vez de al recurso compartido (que no puede volverse inconsistente).

### Desafíos técnicos adicionales a mencionar (rúbrica: "Integración de Componentes del SO")

- **Starvation:** una solicitud que entra tarde a la cola podría esperar mucho si el sistema prioriza reintentos de solicitudes fallidas por encima de las nuevas — mitigarlo respetando estrictamente el orden FIFO, sin prioridades.
- **Reservas "colgadas":** si un usuario gana el semáforo (reserva el boleto) pero no completa el pago, ese boleto queda bloqueado. Se resuelve con un **timeout de reserva** (ej. 5 minutos): si no hay confirmación de pago, el proceso libera el semáforo (`signal()`/`V()`) automáticamente para que otro usuario pueda comprarlo.
- **Deadlock:** con un solo recurso compartido (el inventario) no hay deadlock clásico de recursos múltiples, pero si el diseño final agrega un segundo recurso (ej. bloqueo de asiento + bloqueo de método de pago), habría que pedir ambos siempre en el mismo orden para evitar espera circular — vale la pena mencionarlo aunque no se implemente, para mostrar que se identificó el riesgo.

### Componentes del SO que integra (mapeo directo)

| Componente | Rol en la solución |
|---|---|
| Gestión de procesos/hilos | trabajadores que consumen la cola de solicitudes |
| Sincronización | semáforo contador sobre el inventario de boletos |
| Comunicación entre procesos | cola FIFO compartida entre productor (solicitudes) y consumidores (trabajadores) |
| Gestión de memoria | tabla de inventario como recurso compartido en memoria |
| Planificación/balanceo de cargas | balanceador que reparte solicitudes entrantes entre trabajadores en paralelo, escalando su número según la carga |
| Procesamiento asíncrono | tareas no críticas (confirmación, generación de boleto) se disparan después de confirmada la venta, fuera de la ruta crítica del semáforo |

## Fase 3 — Diseño Preliminar (semana 2)

![[SistemasOperativos_actividad-equipos-diagrama-bloques_2026-08-18.jpeg]]

**Flujo:** Usuarios/clientes (solicitudes concurrentes) → Balanceador de carga → Cola FIFO compartida (IPC, "sala de espera virtual") → Hilos Worker 1..N → Sección crítica (semáforo contador + mutex de asiento) → dos salidas: reserva confirmada (tarea asíncrona: pago, boleto QR/PDF, correo) o rechazado (agotado/ocupado, notificación de error inmediata). Un monitor de timeout recorre las reservas y libera el semáforo (`signal()`) si no hay pago en 5 min.

### Algoritmos y procesos clave del software

**Hilo Trabajador (Worker Thread) — reserva atómica**
1. Extracción: consume una solicitud de la cola FIFO (IPC).
2. Semáforo contador: `wait()` sobre el semáforo de inventario global. Si está en 0 → "Agotado". Si es >0 → decrementa 1 y avanza.
3. Mutex de asiento: `lock()` sobre la celda de memoria del asiento específico.
   - Si está libre: cambia estado a `RESERVADO`, guarda timestamp, `unlock()`, confirma al usuario y dispara el pago asíncrono.
   - Si está ocupado: `unlock()`, `signal()` sobre el semáforo (devuelve el cupo) y notifica "Ocupado".

**Monitor de Timeout — guardián de recursos**
- Bucle periódico: recorre la memoria RAM cada N segundos.
- Expiración: si un asiento está `RESERVADO` por más de 5 minutos sin pago, `lock()` → estado a `LIBRE` → `unlock()` → `signal()` sobre el semáforo global para reactivar esa entrada.

**Proceso asíncrono — liberación de la ruta crítica**
- En segundo plano: procesa el pago con la pasarela bancaria, genera la entrada en PDF/QR y envía la confirmación por correo, fuera de la sección crítica, para no bloquear el inventario en memoria.

### Recursos necesarios

| Categoría | Recurso / herramienta | Función / justificación en el SO |
|---|---|---|
| Lenguaje de programación | C/C++ (o Python con `multiprocessing`) | Manejo nativo de primitivas de sincronización y memoria compartida del SO |
| Bibliotecas del SO | `pthread.h` (POSIX Threads) | Creación y administración del pool de hilos trabajadores |
| Bibliotecas del SO | `semaphore.h` | Control atómico de los semáforos contadores de inventario |
| Bibliotecas del SO | `time.h` / `sys/time.h` | Timestamps para el monitoreo y liberación por timeout |
| Middleware / IPC | Redis o RabbitMQ | Cola FIFO compartida, desacopla el tráfico entrante de los hilos de procesamiento |
| Herramientas de desarrollo | GCC / VS Code / Docker | Compilación, depuración y simulación del entorno distribuido en contenedores |
| Hardware requerido | Procesador multicore (4+ núcleos) | Ejecución paralela real de los hilos trabajadores |
| Hardware requerido | RAM de alta velocidad | Tabla de estado de asientos en memoria, lecturas/escrituras atómicas de baja latencia |

## Fase 4 — Presentación de la Propuesta (semana 3, entrega 2026-08-20)

Slides ya armados por el equipo (título "Sala de Espera Virtual"): 1) portada, 2) problema + solución (4 pasos), 3) diagrama de bloques, 4) desafíos técnicos (starvation / reservas colgadas / deadlock potencial, cada uno con mitigación — mismo contenido de Fase 2), 5) reflexión sobre el aprendizaje (3 puntos), 6) cierre/preguntas.

**Reparto de la exposición** (de la distribución del equipo, con el cambio ya anotado: Marcos toma *Desafíos técnicos* en vez de *Diagrama de bloques*):

| # | Diapositiva | Tiempo | Quién |
|---|---|---|---|
| 1 | Portada | 0:15 | Mario |
| 2 | Problema + Solución | 1:15 | Mario |
| 3 | Diagrama de bloques | 1:30 | Joseph |
| 4 | Desafíos técnicos | 1:00 | **Marcos** |
| 5 | Reflexión (un punto c/u) | 0:45 | Mario, Marcos, Joseph |
| 6 | Cierre | 0:15 | Mario |

Guión con el texto de cada parte (todas las voces, mientras se decide cuál de los 3 puntos de reflexión dice Marcos): [[Cursos/SistemasOperativos/entregables/guion-presentacion-actividad-equipos|guion-presentacion-actividad-equipos.md]]
