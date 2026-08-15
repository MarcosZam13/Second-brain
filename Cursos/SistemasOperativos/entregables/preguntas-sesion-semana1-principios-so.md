---
curso: SistemasOperativos
tema: Preguntas de la Sesión — Semana 1 (IA como Tutor Socrático)
fecha: 2026-08-09
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]]"
estado: entregado
tags: [preguntas-analisis, tutor-socratico, bitacora-ia]
---

# Preguntas de la Sesión — Semana 1

Ver también: [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]] · [[Cursos/SistemasOperativos/entregas]]

**Entrega:** PDF nombrado `S1_Preguntas_MarcosZamoraSanchez`, antes del inicio de la sesión de Semana 2 — jueves **2026-08-13**.

## Portada

- **Nombre completo:** Marcos Zamora Sánchez
- **Curso:** IC-6600 Principios de Sistemas Operativos
- **Profesor:** Jorge Alfaro Velasco
- **Fecha:** 2026-08-13

## Checklist contra la rúbrica

- [ ] Calidad y corrección conceptual de las 10 respuestas e incisos (60%) — faltan 3 puntos puntuales, ver abajo
- [x] Evidencia de razonamiento propio — palabras propias, no copiadas de la IA (20%)
- [x] Bitácora de uso de IA — 3-5 líneas por pregunta usada, o nota de "no fue necesario" (20%)
- [x] Portada (nombre completo, curso, fecha) — contenido listo, ver arriba
- [ ] Respuestas numeradas 1-10 con sus incisos (ya están así en este borrador, verificar al pasar a PDF)
- [ ] Exportar a PDF con el nombre `S1_Preguntas_MarcosZamoraSanchez.pdf`

**Últimos 3 pendientes de corrección conceptual:**
- [ ] 1(a) — línea ~30, todavía describe decodificación como "traducir lo que el SO tiene que hacer" en vez de opcode+operandos → señales de control.
- [ ] 1(c) — línea ~34, la frase sobre qué se simplifica en el hardware sigue sin ser clara.
- [ ] 3(a) — línea ~56, falta cubrir el aspecto de paralelización que pide la consigna.

## I. Ciclo de Instrucción y Procesador

### 1. Decodificación y Diseño del Procesador

a. ¿Es viable eliminar la etapa de decodificación con instrucciones simples de formato fijo?
Se puede llegar a simplificar el hecho de hacer instrucciones simples con un formato fijo, pero no es viable eliminar la etapa de decodificación, ya que es el que le traduce exactamente el SO qué tiene que hacer en lenguaje máquina.

b. Comparar implicaciones en CISC vs. RISC.
Básicamente el RISC se basa en instrucciones más simples y uniformes, mientras que el CISC son instrucciones más complejas y de una longitud variable.

c. Impacto en complejidad del hardware, rol del compilador, consumo energético, diseño del SO.
El hardware es el más sencillo a nivel de complejidad, ya que se encarga que recibir o enviar procesos, en cambio por ejemplo el compilador sería el más complejo y el que hace más cosa, ya que tiene que descomponer operaciones, dar orden, etc. Luego la energía normalmente depende de cuántas instrucciones se estén ejecutando o cuáles instrucciones extras se necesitan para resolver algo. Y el diseño del SO también tiene su complejidad ya que necesita instrucciones atómicas, y llevar una buena sincronización u orden para evitar el riesgo de la condición de carrera.

d. Escenario concreto donde sería o no recomendable, justificado técnicamente.
Si vemos el escenario por ejemplo de un sistema multitarea intensivo conviene más instrucciones simples y rápidas en vez de complejas ya que necesitamos que se hagan muchas instrucciones a la vez, pero si hay que cuidar y se necesitan instrucciones atómicas para evitar problemas de condición de carrera.

e. ¿Simplifica realmente el sistema o solo redistribuye la complejidad?
La complejidad se redistribuye entre el compilador y el kernel, no llega a desaparecer.

### 2. Contador de Programa (PC), Bifurcaciones y Pipeline *(de anticipación)*

a. ¿Por qué el PC no siempre se incrementa linealmente?
El PC no siempre avanza en línea recta porque el programa mismo no es lineal: los ifs, loops, llamadas a función e interrupciones obligan a saltar a otra dirección de memoria.

b. Impacto de una predicción de salto incorrecta en el rendimiento.
Cuando el pipeline predice mal, ya venía adelantando instrucciones que no correspondían, entonces hay que botarlas todas que a eso se le conoce como flush y hay que arrancar de nuevo desde la dirección correcta, lo que desperdicia ciclos de reloj.

c. Relación con cambios de contexto, planificación por quantum y sistemas multitarea intensivos.
Se relaciona porque cada cambio de contexto también rompe el historial de saltos que el hardware venía prediciendo para ese proceso. Con quantum corto hay más cambios de contexto, entonces se paga más seguido esa penalización.

d. Escenario con múltiples procesos generando muchas bifurcaciones — ¿cómo afecta el desempeño global?
Si hay muchos procesos generando bifurcaciones , el encargado de predecir tiene que volver a aprenderse el patrón de cada proceso cada vez que retoma, lo cual baja la tasa de aciertos y el rendimiento del sistema aunque cada proceso individual no sea complejo.

e. ¿El diseño del hardware condiciona indirectamente las políticas de planificación del SO?
Sí, el hardware condiciona la planificación: si cambiar de proceso sale caro para el pipeline, el SO va a preferir quantums más largos o reducir cambios de contexto innecesarios.

### 3. Longitud del Set de Instrucciones (ISA) *(de anticipación)*

a. Comparar ISA amplio (A) vs. reducido (B) en rendimiento, consumo, tamaño de código, paralelización.
El reducido (B) suele ser más rápido por instrucción y consume menos energía por ser hardware más simple, pero necesita más instrucciones para hacer lo mismo, entonces el código pesa más. El amplio (A) genera código más compacto porque una instrucción hace más trabajo.

b. Influencia del diseño del ISA en llamadas al sistema, portabilidad del kernel, compatibilidad hacia atrás.
El ISA influye en las syscalls porque estas dependen de instrucciones específicas para pasar de modo usuario a kernel , entonces entre más simple el ISA, más predecible ese mecanismo. Hablando de portabilidad, un kernel pensado para un ISA reducido es más fácil de portar. Y en compatibilidad, los ISA complejos como x86 arrastran instrucciones viejas por años.

c. ¿Cuál es más adecuada para un SO de propósito general vs. un sistema embebido de tiempo real?
Un SO de propósito general se beneficia más de un ISA amplio porque necesita flexibilidad para correr de todo. En cambio un sistema embebido de tiempo real se beneficia más de uno reducido porque necesita predictibilidad y bajo consumo.

d. Justificar críticamente la elección.
Para tiempo real elegiría el reducido, porque ahí importa más que cada instrucción tarde un tiempo constante y no que haga muchas cosas complejas un retraso inesperado es peor que ser lento pero constante. Y para lo cotidiano elegiría mejor el ISA amplio.


### II. Memoria y Jerarquía de Almacenamiento

#### 4. Separación de Memoria de Instrucciones y Datos

a. Explicar desde Harvard vs. Von Neumann.  
Von Neumann usa una sola memoria y un solo bus para instrucciones y datos, lo cual simplifica el diseño pero puede generar cuello de botella. En cambio Harvard las separa físicamente, entonces se puede leer instrucción y dato al mismo tiempo, lo que acelera la ejecución.

b. Impacto en seguridad, rendimiento y concurrencia.  
En seguridad ayuda a prevenir que un atacante meta código malicioso en una zona de datos como el stack y lo ejecute, ya que esa zona no está pensada para ejecutarse. Hablando del rendimiento se elimina la contención de acceder a instrucción y dato en el mismo ciclo. Y en concurrencia facilita que varias unidades del procesador accedan a memoria sin bloquearse entre sí.

c. Escenario donde esta separación prevenga una vulnerabilidad.  
Un caso típico es un buffer overflow (Aquí la IA me ayudó a sacar el ejemplo), donde el atacante mete código ejecutable en el stack esperando que el CPU lo ejecute. Con protecciones como NX/DEP, que se apoyan en esta separación, esa zona se marca como no ejecutable y el ataque no funciona.

d. ¿Decisión puramente arquitectónica o también estratégica para el SO?  
Empieza siendo una decisión de hardware, pero termina siendo estratégica para el SO también, porque este se apoya en esa separación para implementar mecanismos de seguridad como DEP/NX.

#### 5. Jerarquía de Memoria en Sistemas Embebidos

a. ¿Por qué se eliminarían niveles de caché o memoria virtual?  
Se elimina para ganar predictibilidad, ya que en vez de tener tiempos de acceso variables (a veces hit, a veces miss) se prefiere que todo acceso tarde siempre lo mismo, algo que es crítico en sistemas de tiempo real.

b. Impacto en predictibilidad, latencia y complejidad del SO.  
La predictibilidad mejora bastante porque cada acceso tiene un tiempo fijo conocido. La latencia puede subir en promedio ya que sin caché todo va directo a memoria principal que es más lenta. Y la complejidad del SO baja porque ya no hay que manejar tablas de páginas ni page faults.

c. Comparar con el modelo tradicional multinivel.  
El modelo multinivel tradicional prioriza el rendimiento promedio aprovechando la localidad de los programas, aceptando esa variabilidad. El modelo simplificado del embebido en cambio prioriza la consistencia por encima de la velocidad promedio.

d. ¿Mejora o limita la escalabilidad?  
Limita la escalabilidad para programas grandes o varios procesos pesados, pero mejora la escalabilidad en el sentido de que el sistema se comporta igual sin importar la carga, que es justo lo que se necesita en control industrial o automotriz por ejemplo.

#### 6. Memoria Caché y Localidad

a. Explicar localidad temporal y espacial.  
La localidad temporal es cuando un dato usado recientemente es probable que se vuelva a usar pronto. La localidad espacial es cuando un dato cercano a uno accedido es probable que también se use pronto.

b. Cómo influyen en el diseño de la caché.  
Por la temporal la caché guarda lo usado recientemente esperando que se vuelva a pedir. Por la espacial trae bloques completos de memoria y no solo el dato pedido, para aprovechar que probablemente van a pedirse los datos vecinos.

c. Relación con page faults, algoritmos de reemplazo y afinidad de procesos.  
Se relaciona con page faults porque el mismo principio de localidad se usa para decidir qué páginas mantener en RAM. Los algoritmos de reemplazo como LRU (Least Recently Used) están basados directamente en localidad temporal, sacando lo menos usado recientemente. Y la afinidad de procesos existe para no perder el calentamiento de la caché de ese núcleo.

d. Escenario de mal diseño de acceso a memoria.  
Un mal diseño sería recorrer una matriz grande por columnas en vez de por filas en un lenguaje donde la memoria se guarda por filas, ya que cada acceso saltaría a una zona distinta de memoria, rompiendo la localidad espacial y generando muchos cache misses aunque el algoritmo en sí sea correcto.

### III. E/S y Acceso a Datos

#### 7. DMA y Contención del Bus

a. Posibles cuellos de botella.  
El cuello de botella principal es el bus de memoria, ya que si varios dispositivos hacen DMA (_direct memory access_) al mismo tiempo todos van a pelear por el mismo canal de acceso, generando esperas incluso con el CPU libre.

b. Cómo puede el SO mitigar la contención del bus.  
El SO puede mitigar esto priorizando qué dispositivos tienen acceso primero con colas de prioridad, agrupando transferencias, o usando ventanas de tiempo para que no todos transfieran en el mismo instante.

c. Relación con planificación de I/O y priorización.  
Se relaciona directamente con la planificación de I/O, ya que el SO decide qué solicitudes atender primero según prioridad, tipo de dispositivo o urgencia, para minimizar el impacto de la contención del bus.

d. Estrategia para un servidor de alto tráfico.  
Una estrategia sería priorizar el DMA de red por encima de transferencias de disco menos urgentes, o distribuir las transferencias en distintos controladores o buses si el hardware lo permite, para que no todo el tráfico pase por un único canal.

#### 8. Modos de Transferencia de Datos

a. Eficiencia en entornos multitarea.  
En multitarea la E/S programada es la menos eficiente porque el CPU se queda esperando activamente. Las interrupciones son mejores porque liberan al CPU mientras espera. Y el DMA es el más eficiente para transferencias grandes ya que casi ni necesita al CPU para mover los datos.

b. En qué escenario es más adecuado cada mecanismo.  
La E/S programada sirve para dispositivos muy simples donde no vale la pena el overhead de una interrupción. Las interrupciones son ideales para eventos esporádicos como teclado o mouse. Y el DMA es mejor para transferencias grandes y continuas como disco o red.

c. Sistema híbrido combinando mecanismos.  
Un sistema híbrido podría usar interrupciones para dispositivos de baja frecuencia y DMA para transferencias masivas, dejando la E/S programada solo para casos muy puntuales donde no se justifique el overhead de una interrupción.

d. Justificar técnicamente el diseño.  
Esto se justifica porque cada mecanismo tiene un costo distinto, interrumpir tiene overhead de cambio de contexto y el DMA tiene overhead de configuración inicial pero es más eficiente en volumen. Entonces usar el mecanismo correcto según el tipo de carga optimiza el uso del CPU en vez de aplicar una sola solución para todo.

### IV. Sistemas Operativos y Gestión de Recursos

#### 9. Recuperación del Control del CPU

a. Mecanismos que lo permiten.  
Los mecanismos son las interrupciones de hardware, donde el timer manda una señal periódica, el modo kernel que permite ejecutar código privilegiado tras esa interrupción, y el planificador que decide qué hacer después.

b. Impacto del cambio de contexto en el rendimiento.  
El cambio de contexto impacta el rendimiento porque guardar y restaurar el estado de un proceso como registros y PC toma tiempo que no se usa en trabajo útil, entonces entre más frecuente el cambio más overhead hay, aunque también hay más capacidad de respuesta.

c. Relación con el algoritmo de planificación.  
Se relaciona directamente porque es la interrupción del timer la que le da al planificador la oportunidad de decidir si el proceso actual sigue corriendo o le toca el turno a otro, según la política que se use, como Round Robin o prioridades.

d. Escenario de mal manejo del timer.  
Si el timer está mal configurado, por ejemplo con un quantum muy largo, un proceso podría acaparar el CPU mucho más tiempo del debido, generando injusticia para los demás procesos que están esperando.

#### 10. Interrupciones de Hardware vs. Software

a. Comparar desde sincronización y control.  
Las interrupciones de hardware son asíncronas, pueden pasar en cualquier momento sin depender de lo que esté haciendo el programa. Las de software como las syscalls son síncronas, ya que ocurren porque el programa mismo las provoca en un punto específico de su ejecución.

b. Ventajas y desventajas en la gestión de procesos.  
Las de hardware permiten reaccionar a eventos externos sin que el programa tenga que cooperar, pero pueden interrumpir en momentos inconvenientes. Las de software dan más control porque el programa decide cuándo pedir algo al kernel, pero dependen de que el programa efectivamente la genere.

c. En qué escenarios el SO preferiría una sobre otra.  
El SO preferiría una interrupción de hardware cuando necesita garantizar que va a recuperar el control sin depender del programa, como con el timer. Y preferiría una de software cuando el programa necesita explícitamente un servicio del kernel, como abrir un archivo o pedir memoria.

d. ¿Cuál es más determinista?  
La de software es más determinista porque ocurre en un punto exacto y conocido del programa. La de hardware es menos determinista porque puede llegar en cualquier momento sin relación con lo que el programa está haciendo en ese instante.


## Bitácora de uso de IA

### Proceso general

Para el uso de IA lo que hice fue lo siguiente:
- Le pedí a la IA que me explicara de qué trataba la pregunta y los conceptos involucrados, ya que no lo habíamos visto en clase o no lo había entendido del todo bien.
- Con esa base, redacté mi propia respuesta según de lo que yo me acuerdo y maso menos conozco.
- Le pedí a la IA que revisara mi respuesta y validara si estaba correcta o si le faltaba algo.
- Ajusté según esa retroalimentación.

Básicamente intenté usar a la IA como un profesor que me fuera explicando y guiando en este proceso de aprendizaje mientras respondía las preguntas de esta tarea. Lo hice con Claude Code, dentro de un proyecto tipo "second brain" que uso para estudiar.

### Notas específicas por pregunta

- **Pregunta 1 (Decodificación y Diseño del Procesador):** acá tuve la corrección más importante — al principio confundí lo que hace la etapa de decodificación con lo que hace el compilador (pensaba que decodificación "traduce" acciones del SO a lenguaje máquina). La IA me hizo pensar en qué momento del proceso el programa ya es código máquina puro, y ahí caí en que decodificación lee opcode + operandos y genera señales de control, no traduce desde más arriba.
- **Pregunta 4 (Separación de Memoria de Instrucciones y Datos):** para el inciso (c) le pedí a la IA un ejemplo concreto de vulnerabilidad que la separación de memoria previene, porque no se me ocurría uno de ahí salió el ejemplo de buffer overflow y protecciones NX/DEP.
- **Preguntas 2, 3, 5-10:** seguí el proceso general de arriba, planteé mi respuesta primero con lo que ya sabía o lo que saqué del apunte de clase, y usé la IA para validar que el razonamiento estuviera bien encaminado, sin que aparecieran correcciones de fondo como en la pregunta 1 fueron más que todo ayudas para aprenderme los conceptos.

### Conceptos y acrónimos que me ayudaron a entender

- **CISC** (*Complex Instruction Set Computer*) — instrucciones complejas y de longitud variable, decodificación más pesada.
- **RISC** (*Reduced Instruction Set Computer*) — instrucciones simples y uniformes, decodificación más liviana, más carga en el compilador.
- **ISA** (*Instruction Set Architecture*) — el conjunto de instrucciones que un procesador entiende.
- **PC** (*Program Counter*) — registro que guarda la dirección de la siguiente instrucción a ejecutar.
- **DMA** (*Direct Memory Access*) — mecanismo que permite a un dispositivo transferir datos hacia/desde memoria sin ocupar al CPU en cada byte.
- **NX/DEP** (*No-eXecute* / *Data Execution Prevention*) — protección que marca zonas de memoria (como el stack) como no ejecutables, para frenar ataques tipo buffer overflow.
- **LRU** (*Least Recently Used*) — algoritmo de reemplazo de caché/páginas que descarta primero lo que no se ha usado en más tiempo.

![[Pasted image 20260809131200.png|700]]

Ejemplo gráfico de cómo fue el proceso. 