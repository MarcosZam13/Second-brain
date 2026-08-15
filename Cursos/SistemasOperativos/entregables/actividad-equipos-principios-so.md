---
curso: SistemasOperativos
tema: Actividad en Equipos — Solución basada en Principios de los SO (Semanas 1-3)
fecha: 2026-08-12
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]]"
estado: borrador
tags: [actividad-equipos, trabajo-grupal, fase1]
---

# Actividad en Equipos — Solución basada en Principios de los SO

Ver también: [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]] · [[Cursos/SistemasOperativos/entregas]]

**Entrega (Fase 4 — presentación):** 2026-08-20 (inicio semana 3), ~5 min por grupo.
**Estado actual:** propuesta (opción 1 — condiciones de carrera, venta de boletos de concierto) revisada por el profesor, quien sugirió agregar balanceo de cargas al diseño. Roles del equipo ya asignados.

## Checklist contra la rúbrica

- [ ] Identificación del Problema — claridad, relevancia, justificación (10%)
- [ ] Originalidad de la Solución — creatividad, innovación, justificación (20%)
- [ ] Integración de Componentes del SO — coherencia, funcionalidad, eficiencia (25%)
- [ ] Diseño Preliminar — claridad, estructura, viabilidad (20%)
- [ ] Presentación de la Propuesta — claridad, organización, comunicación (15%)
- [ ] Reflexión sobre el Aprendizaje — profundidad, conexión, autoevaluación (10%)

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

*(pendiente — diagrama de bloques, algoritmos/procesos, recursos necesarios)*

## Fase 4 — Presentación de la Propuesta (semana 3, entrega 2026-08-20)

*(pendiente)*
