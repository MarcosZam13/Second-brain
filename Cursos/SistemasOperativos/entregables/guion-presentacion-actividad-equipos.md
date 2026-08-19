---
curso: SistemasOperativos
tema: Guión de presentación — Actividad en Equipos (Sala de Espera Virtual)
fecha: 2026-08-18
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/entregables/actividad-equipos-principios-so]]"
estado: borrador
fuente:
  - _fuentes/SistemasOperativos_actividad-equipos-presentacion-final_2026-08-18.pdf
  - _fuentes/SistemasOperativos_actividad-equipos-distribucion-guion_2026-08-18.jpeg
tags: [actividad-equipos, trabajo-grupal, guion, presentacion]
---

# Guión — Sala de Espera Virtual

Ver también: [[Cursos/SistemasOperativos/entregables/actividad-equipos-principios-so|Actividad en Equipos (documento completo)]] · [[Cursos/SistemasOperativos/entregas]]

**Entrega:** 2026-08-20 (inicio semana 3), ~5 min totales por grupo (slides ya armados, ver PDF en `_fuentes/`).
**Pendiente:** cerrar qué punto de la Fase 5 (reflexión) dice Marcos — abajo están los 3 borrados para elegir. **La parte fija de Marcos es la diapositiva 4 (Desafíos técnicos).**

Borrador de las 6 partes, para ensayar como equipo. Ajustar tono/tiempo según cómo suene en voz alta — los tiempos de la tabla son los que puso el equipo en la distribución.

## 1. Portada (0:15 — Mario)

> "Buenas, somos el equipo de Sistemas Operativos: Marcos Zamora, Mario Rojas y Joseph Fonseca. Les vamos a presentar 'Sala de Espera Virtual', una solución de sincronización de procesos para evitar la sobreventa de boletos, usando colas, semáforos, mutex y balanceo de carga."

## 2. Problema + Solución (1:15 — Mario)

> "El problema es clásico: varios usuarios intentan comprar el mismo boleto al mismo tiempo. Si dos procesos leen la disponibilidad, la ven libre y confirman antes de que el otro actualice el dato, se produce sobreventa — eso es una condición de carrera, y solo se resuelve con sincronización, no arreglando la interfaz.
>
> Nuestra solución serializa el acceso en dos niveles. Primero, una cola FIFO: la 'sala de espera virtual'. Cada compra entra a la cola y un grupo de workers la va procesando una por una, como hace Ticketmaster. Segundo, la sección crítica: verificar, reservar y descontar es una operación atómica, protegida con un semáforo contador de N unidades, no un mutex binario, porque hay varios boletos disponibles, no uno solo.
>
> A eso le sumamos dos cosas más: un balanceador de carga que reparte las solicitudes entre los workers en paralelo — igual que un planificador de CPU — y procesamiento asíncrono para todo lo que no es crítico, como el correo o el PDF del boleto, que se dispara después de confirmada la venta para no competir por el semáforo."

## 3. Diagrama de bloques (1:30 — Joseph)

> "Así se ve el flujo completo. Las solicitudes de los usuarios llegan al balanceador de carga, que las reparte hacia la cola FIFO compartida — la sala de espera. De ahí, los hilos worker —1, 2 hasta N— van sacando solicitudes y las llevan a la sección crítica del sistema operativo, donde un semáforo contador y un mutex de asiento protegen la verificación y reserva en memoria.
>
> Si la reserva se confirma, se dispara una tarea asíncrona en segundo plano: procesamiento del pago, generación del boleto en QR o PDF, y el correo de confirmación. Si se rechaza —porque ya se agotó o el asiento está ocupado— se le notifica el error al cliente de inmediato.
>
> Y por debajo de todo esto corre un monitor de timeout: si alguien reserva pero no paga en 5 minutos, libera el mutex y hace signal sobre el semáforo, para que ese cupo vuelva a estar disponible."

## 4. Desafíos técnicos (1:00 — Marcos)

*(borrador de trabajo — esta es la parte de Marcos, ajustar libremente)*

> "Diseñar esto también significa pensar en qué puede salir mal. Identificamos tres desafíos técnicos.
>
> El primero es starvation: una solicitud que entra tarde a la cola podría quedarse esperando mucho si el sistema le da prioridad a los reintentos por encima de las solicitudes nuevas. Lo evitamos respetando estrictamente el orden FIFO, sin prioridades — el que llegó primero, se atiende primero, sin excepciones.
>
> El segundo son las reservas colgadas: si alguien gana el semáforo, reserva el boleto, pero nunca completa el pago, ese boleto queda bloqueado para siempre. Por eso existe el monitor de timeout que mencionó Joseph — a los 5 minutos sin pago, libera el semáforo automáticamente con signal, y el boleto vuelve a estar disponible para otro usuario.
>
> Y el tercero es un deadlock potencial. Con un solo recurso compartido —el inventario— no hay deadlock clásico. Pero si a futuro el diseño agrega un segundo recurso, por ejemplo bloquear el asiento y bloquear el método de pago por separado, ahí sí hay riesgo de espera circular. La mitigación es simple: pedir siempre los recursos en el mismo orden. Lo dejamos identificado desde ya, aunque no se implemente en esta versión, porque demuestra que pensamos el diseño más allá del camino feliz."

## 5. Reflexión sobre el aprendizaje (0:45 total — Mario, Marcos, Joseph, un punto cada uno)

*(sin asignar todavía — 3 versiones borrador, elegir una para Marcos y confirmar quién dice las otras dos)*

**Punto A — Concurrencia real**
> "Para mí lo que más me quedó de este trabajo es que la exclusión mutua no es opcional. Sin semáforos ni mutex, un sistema con usuarios simultáneos no truena de forma obvia — falla en silencio, con sobreventa, y eso sale caro."

**Punto B — Los componentes del SO trabajan juntos**
> "Lo que aprendimos armando esto es que los componentes del sistema operativo no se usan por separado. Procesos, sincronización, comunicación entre procesos, memoria y planificación tuvieron que integrarse todos a la vez para que la solución funcionara — igual que en un sistema real."

**Punto C — Pensar en fallos, no solo en el camino feliz**
> "Lo que más nos costó no fue el caso donde todo sale bien, sino los casos donde algo falla: starvation, reservas colgadas, deadlock. Tuvimos que diseñar la recuperación de esos casos antes de siquiera pensar en escribir código, y esa fue la parte que más nos hizo pensar como si esto fuera un sistema real."

## 6. Cierre (0:15 — Mario)

> "Con eso resolvemos la condición de carrera sin perder disponibilidad bajo picos de tráfico. Muchas gracias, quedamos atentos a preguntas."

---

## Próximos pasos

- [ ] Elegir cuál de los 3 puntos de reflexión dice Marcos (y confirmar con Mario/Joseph los otros dos).
- [ ] Ensayar en voz alta contra el tiempo real (objetivo: ~5 min todo el equipo).
- [ ] Ajustar el texto de la diapositiva 4 (Marcos) a como suene natural al practicarlo.
