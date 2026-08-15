---
curso: SistemasOperativos
tema: Preguntas de la Sesión — Semana 2 (IA como Tutor Socrático)
fecha: 2026-08-12
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/historia-componentes-so-unidad2]]"
estado: borrador
tags: [preguntas-analisis, tutor-socratico, bitacora-ia]
---

# Preguntas de la Sesión — Semana 2

Ver también: [[Cursos/SistemasOperativos/apuntes/historia-componentes-so-unidad2]] · [[Cursos/SistemasOperativos/entregas]]

**Entrega:** PDF nombrado `S2_Preguntas_MarcosZamoraSanchez`, antes del inicio de la sesión de Semana 3 — jueves **2026-08-20**.

## Portada

- **Nombre completo:** Marcos Zamora Sánchez
- **Curso:** IC-6600 Principios de Sistemas Operativos
- **Profesor:** Jorge Alfaro Velasco
- **Fecha:** 2026-08-20

## Checklist contra la rúbrica

- [ ] Calidad y corrección conceptual de las respuestas — los 10 bloques y sus incisos (60%)
- [ ] Evidencia de razonamiento propio — palabras propias, no copiadas de la IA (20%)
- [ ] Calidad y honestidad de la Bitácora de uso de IA (20%)
- [ ] Portada (nombre completo, curso, fecha)
- [ ] Respuestas numeradas 1-10 con sus incisos
- [ ] Exportar a PDF con el nombre `S2_Preguntas_MarcosZamoraSanchez.pdf`

## I. Historia, Definición y Objetivos del Sistema Operativo

### 1. Definición y Funciones del SO

¿Qué es un sistema operativo y cuáles son sus funciones principales? Ilustra tu respuesta con al menos un ejemplo de SO actual (de escritorio, móvil o embebido).

Un sistema operativo es lo que le permite al usuario utilizar el hardware de manera óptima y más sencilla, usualmente con interfaz gráfica u otras alternativas que permiten hacer procesos de forma más fácil sin necesidad de tener muchos conocimientos. Además, administra recursos como CPU, memoria y dispositivos: por ejemplo, Windows o Linux se encargan de realizar muchos trabajos de administración que nosotros ni notamos.

### 2. Objetivos: Conveniencia y Eficiencia

¿Cuáles son los objetivos del sistema operativo en términos de conveniencia para el usuario y de eficiencia en la ejecución de programas?

a. ¿Puede un SO maximizar ambos objetivos simultáneamente, o existe una tensión entre ellos? Justifica con un ejemplo.

El sistema operativo busca que el usuario no tenga que preocuparse por muchas de las labores administrativas, y además evita que ocurra algún problema: sin un SO, el usuario podría hacer cosas a nivel de kernel que no siempre son la mejor opción en optimización o en seguridad del dispositivo. Con un SO tenemos una mejor administración y protección de esos recursos, sin que el usuario necesite esos conocimientos ni pueda hacer algo indebido en el sistema eso es la conveniencia. La eficiencia, en cambio, es la administración y optimización de los recursos de cómputo.

a. Sí existe tensión entre ambos objetivos: las protecciones y capas de abstracción que dan conveniencia (llamadas al sistema, verificación de permisos, protección de memoria) cuestan rendimiento comparado con que un programa hablara directo con el hardware sin esos cuidados. Por ejemplo, al abrir varios programas simultáneos con un solo click, el SO se encarga de todo el proceso de forma transparente para el usuario, pero ese manejo (cambios de contexto, verificación de recursos, etc.) tiene un costo de rendimiento que no existiría si el programa corriera solo, sin ninguna de esas protecciones.

## II. Problemas Clásicos que Resuelve un Sistema Operativo

### 3. Gestión de Recursos y Multiprogramación

Describe un ejemplo de cómo un sistema operativo maneja la demanda de recursos cuando múltiples procesos necesitan acceso simultáneo a la memoria.

a. ¿Por qué la multiprogramación es una propiedad deseable en este contexto?

El sistema operativo actúa como un orquestador: revisa qué procesos están activos y qué necesitan para funcionar, y les va dando la memoria y el tiempo de CPU que requieren mientras se ejecutan. Al terminar, sigue administrando esos recursos dándole más o menos prioridad a cada proceso según su turno de ejecución, evitando que un solo proceso acapare todos los recursos del sistema aunque no los necesite, y que se desperdicie el tiempo de otros procesos importantes.

Por ejemplo, si tengo el navegador descargando un archivo grande, un editor de video renderizando algo y música sonando de fondo: mientras el navegador espera a que lleguen más datos por la red (no está usando la CPU en ese instante), el SO le da ese tiempo de CPU al editor de video, que sí lo necesita porque exige mucho procesamiento, en vez de dejar la CPU inactiva esperando a que termine la descarga.

a. La multiprogramación es deseable porque, si solo hubiera un proceso cargado a la vez, la CPU quedaría inactiva cada vez que ese proceso tuviera que esperar algo (como en el ejemplo de la descarga). Al tener varios procesos cargados en memoria simultáneamente, el SO puede aprovechar esos tiempos de espera dándole la CPU a otro proceso que sí tiene trabajo pendiente como el editor de video mientras el navegador espera la red  optimizando así el uso de CPU y memoria en vez de desperdiciarlos.

### 4. Comunicación entre Procesos

¿Cómo sabe un proceso en ejecución que otro proceso ha terminado, y cómo maneja el SO esta comunicación?

Un proceso no está pendiente de lo que hacen los demás procesos todo el tiempo, porque eso sería una pérdida de recursos (estar preguntando constantemente si el otro ya terminó). En cambio, si un proceso depende de que otro termine, se bloquea/duerme en ese punto no antes, no hace espera activa y el SO lo saca de la fila de ejecución mientras tanto. El otro proceso sigue trabajando normalmente, y cuando termina, genera una interrupción/llamada al sistema que le avisa al SO. El SO, mediante un semáforo, le indica al proceso que estaba dormido que despierte, y ya con el otro proceso terminado, este puede continuar su trabajo.

### 5. Bloqueo Mutuo (Deadlock)

Explica qué es un deadlock y cómo puede ocurrir en un sistema operativo. Proporciona un ejemplo propio, distinto al visto en clase.

Un deadlock (bloqueo mutuo) ocurre cuando el SO no puede asignarle un recurso a un proceso porque ese recurso está en manos de otro proceso que, a su vez, está esperando un recurso que tiene el primero. Cada uno ya tiene algo agarrado y no lo suelta hasta terminar su tarea, pero no puede terminar sin lo que le falta quedan en un círculo cerrado del que ninguno sale por sí solo.

Ejemplo propio: Proceso 1 bloquea `reportes.txt` para leerlo (lo tiene agarrado); después, para anotar que ya lo leyó, necesita también escribir en `logs.txt`. Proceso 2 bloquea `logs.txt` para escribir en él (lo tiene agarrado); pero para saber qué anotar, necesita leer `reportes.txt`. Proceso 1 tiene `reportes.txt` y pide `logs.txt`; Proceso 2 tiene `logs.txt` y pide `reportes.txt`. Ninguno suelta lo que tiene porque no ha terminado, y ninguno consigue lo que le falta porque el otro lo tiene bloqueado → deadlock.

## III. Componentes del Sistema Operativo

### 6. Componentes del SO y Conexión con Unidad 1

Enumera y describe brevemente los componentes principales de un sistema operativo moderno.

a. Para al menos dos de ellos, indica un ejemplo tecnológico actual.
b. Explica cómo se relacionan al menos dos de esos componentes con un concepto visto en la Unidad 1 (por ejemplo, la jerarquía de memoria, el cómputo heterogéneo CPU/GPU/NPU, o los modos kernel/usuario).

Un sistema operativo moderno se compone de varios gestores/módulos internos:

- **Gestor de Procesos:** es el encargado de crear y destruir procesos, además de planificar, sincronizar y comunicar entre ellos.
- **Gestor de Memoria:** es el encargado de asignar y liberar memoria, y de manejar paginación y memoria virtual.
- **Gestor de E/S:** es el encargado de coordinar drivers y dispositivos.
- **Sistema de Archivos:** es el encargado de organizar archivos, directorios y permisos.
- **Subsistema de Red:** se encarga de los protocolos, las interfaces y el firewall en la red.
- **Seguridad y Protección:** se encarga de la autenticación, el control de acceso y el cifrado.

a. Dos ejemplos tecnológicos actuales:
- **Administrador de Tareas de Windows** : ejemplo de **Gestor de Procesos**: permite ver la información del CPU, los procesos y su consumo; tiene interacción directa con el consumo del CPU para poder visualizarlo.
- **Explorador de archivos**: ejemplo de **Sistema de Archivos**: permite mover archivos entre carpetas (hay movimiento en la memoria/almacenamiento del dispositivo), además de editar o eliminar archivos.

b. Dos conexiones con Unidad 1:
- **Gestor de Memoria/jerarquía de memoria:** cuando la RAM no alcanza, el gestor de memoria usa memoria virtual/swap, moviendo páginas entre RAM y disco/SSD la misma jerarquía (registros, caché, RAM, SSD) vista en Unidad 1.
- **Gestor de Procesos/modo kernel/usuario:** el gestor de procesos necesita ejecutar en modo kernel para hacer cambios de contexto y reprogramar el timer, cosas que un programa en modo usuario no puede tocar directamente.

## IV. Llamadas al Sistema, Modo Dual y Protección por Hardware

### 7. Llamadas al Sistema

Describe el proceso de una llamada al sistema y cómo se manejan los parámetros en diferentes métodos.

Una llamada al sistema es la forma en que un programa en modo usuario le pide al SO hacer algo que no puede hacer directamente, como escribir en disco. El programa prepara los parámetros, ejecuta una instrucción especial (trap`/`syscall) que genera una interrupción de software, y el CPU pasa de modo usuario a modo kernel. El SO revisa qué llamada se pidió (usando un número de llamada como índice en una tabla), la ejecuta con sus privilegios, y regresa el resultado al programa, devolviéndolo a modo usuario.

Los parámetros se pueden pasar de varias formas: directo en registros (rápido pero limitado), guardados en un bloque de memoria pasando solo la dirección (sin límite real de tamaño), o metidos en una pila. Lo común es combinar registros para parámetros simples y memoria para estructuras más grandes.

### 8. Modo Dual de Operación

¿Qué es el modo dual de operación en un sistema operativo y por qué es importante para la seguridad y la eficiencia?

a. Relaciona tu respuesta con lo visto sobre los modos kernel/usuario en la Unidad 1: ¿qué profundiza esta unidad que no se había visto antes?

El modo dual es cuando el CPU puede trabajar en modo usuario (donde corren los programas normales, con acceso restringido) o modo kernel (donde corre el SO con acceso completo al hardware). Un bit indica en qué modo se está, y ciertas instrucciones solo se pueden ejecutar en modo kernel; si un programa en modo usuario las intenta, el hardware genera una excepción y el SO toma el control.

Es importante para la seguridad porque evita que un programa toque recursos que no le corresponden sin pasar por el SO, y para la eficiencia porque el chequeo lo hace el hardware, no el software, así que es prácticamente gratis en tiempo de ejecución.

a. Lo que profundiza esta unidad es el mecanismo concreto de la transición entre modos: en Unidad 1 vimos que existen los dos modos y qué puede hacer cada uno, pero acá se ve la instrucción de trap/syscall, el cambio de contexto y la tabla de llamadas al sistema que conecta ese cambio con el proceso completo de una llamada al sistema.

### 9. Protección por Hardware

¿Cómo asegura un sistema operativo que un programa no afecte negativamente a otro en términos de protección por hardware? Considera al menos dos de los tres mecanismos vistos en clase (E/S, memoria, CPU).

**Memoria:** cada proceso tiene su propio espacio de direcciones (registros base/límite o tablas de páginas). Si un proceso intenta acceder fuera de su rango, el hardware genera una excepción antes de que el acceso ocurra, así que un proceso no puede leer ni corromper la memoria de otro.

**CPU:** el mecanismo principal es el timer de interrupción. El SO le da a cada proceso un quantum de tiempo; cuando se acaba, el timer interrumpe y devuelve el control al SO sin importar si el proceso quería seguir. Esto evita que un proceso (por ejemplo, con un bucle infinito) acapare la CPU y deje a los demás sin recursos.

Se complementan: uno evita que un proceso dañe a otro, el otro evita que un proceso monopolice el tiempo de ejecución.

## V. Aplicación

### 10. Escenario de Bloqueo Mutuo

Considera un sistema con tres procesos (P1, P2, P3) y dos recursos (R1, R2), donde: P1 tiene asignado R1 y solicita R2; P2 tiene asignado R2 y solicita R1; P3 no ha solicitado ningún recurso todavía.

a. Determina si existe una condición de bloqueo mutuo en este escenario, justificando tu respuesta con el patrón de espera circular visto en clase.
b. Propón, en tus propias palabras, al menos una estrategia que el sistema operativo podría aplicar para evitar que esta situación llegue a bloquear el sistema. No se requiere pseudocódigo ni un algoritmo formal — esos se verán en unidades posteriores.
c. ¿Cambiaría tu respuesta al inciso (a) si P3 también solicitara R1? Explica por qué.

a. Sí existe deadlock entre P1 y P2. El grafo de espera queda: P1 → R2 → P2 → R1 → P1, cerrando el ciclo. Cada uno tiene algo que el otro necesita y espera algo que el otro tiene, sin poder avanzar ni soltar nada. P3 no participa porque no ha pedido recursos, así que no afecta esta condición.

b. Una estrategia es exigir que cada proceso pida de una vez todos los recursos que va a necesitar antes de empezar a ejecutar, en vez de ir pidiéndolos por partes. Así se rompe la condición de "retener y esperar": o se le da todo o no se le da nada, pero nunca queda a medias bloqueando a otro proceso.

c. Sí cambiaría en el efecto, aunque el ciclo entre P1 y P2 se mantiene igual. Ahora P3 también quedaría esperando R1, que está en manos de P1 (atrapado en el ciclo), así que P3 se bloquearía indirectamente sin ser parte del ciclo circular. El deadlock original sigue igual, pero ahora tiene un efecto en cadena sobre un tercer proceso.

## Bitácora de uso de IA

### Proceso general

Fui respondiendo cada pregunta en un chat con Claude Code, dentro del mismo proyecto de "second brain" que uso para estudiar. En cada pregunta primero traté de responder con lo que ya sabía o recordaba del apunte de clase; cuando a mi respuesta le faltaba algo respecto a lo que pedía la consigna (un elemento, un ejemplo, una precisión conceptual), la IA me lo señalaba sin darme la respuesta completa, y yo ajustaba mi propia respuesta. En las preguntas donde no tenía ni idea de por dónde empezar, le pedí que me explicara el concepto general antes de intentar responder.

### Notas específicas por pregunta

- **Pregunta 1:** mi primera respuesta solo cubría la parte de "conveniencia" (interfaz fácil de usar); la IA me hizo notar que me faltaba la función de administración de recursos y un ejemplo concreto de SO actual, así que agregué ambas cosas.
- **Pregunta 2 (inciso a):** al principio dije que un SO sí puede maximizar conveniencia y eficiencia al mismo tiempo, sin tensión entre ellas. La IA me hizo pensar en si las capas de protección/abstracción que dan conveniencia (llamadas al sistema, verificación de permisos) tienen costo de rendimiento, y ahí caí en que sí hay tensión — corregí mi conclusión y el ejemplo.
- **Pregunta 3:** no tenía muy claro el concepto de multiprogramación; le pedí a la IA que me lo explicara sin darme la respuesta final. Con eso armé mi propia descripción del SO como "orquestador" de recursos, pero me faltaba el ejemplo concreto que pedía la consigna — la IA me guio con un escenario (navegador descargando + editor de video + música) y yo completé la lógica de qué proceso aprovecha el tiempo de espera del otro.
- **Pregunta 4:** tampoco sabía cómo explicar la comunicación entre procesos. Mi primera intuición (que un proceso no está pendiente de los demás todo el tiempo) era correcta, pero me faltaba el mecanismo; con ayuda de la IA llegué a la idea de semáforos y bloqueo/despertar, y tuve que corregir el orden de quién se bloquea (el proceso que depende del otro, no el que termina su trabajo).
- **Pregunta 5:** pedí contexto sobre qué es un deadlock porque no me acordaba bien del concepto. Con la explicación armé mi propio ejemplo (dos procesos, dos archivos: `reportes.txt` y `logs.txt`), ajustando el orden de quién agarra qué primero para que quedara el mismo patrón de espera circular que R1/R2 visto en clase.

- **Pregunta 6:** al principio confundí los "componentes del SO" con componentes de hardware (CPU, GPU, RAM, etc.); la IA me hizo notar la diferencia entre lo visto en Unidad 1 (hardware) y lo que pedía esta pregunta (los módulos internos del SO). También intenté pegar la lista de componentes casi tal cual me la explicó la IA, y me señaló que eso contaba como copia directa, así que la reformulé con mis propias palabras. Para el inciso (b), corregí un error mío (pensé que el gestor de memoria usa la VRAM cuando falta RAM) por el concepto correcto de memoria virtual/swap.
- **Preguntas 7-9:** le pedí a la IA que me ayudara a entender mejor el contexto de cada una y algunos procesos más complejos que no tenía del todo claros (el mecanismo interno de una llamada al sistema, la transición entre modos, y los mecanismos de protección por hardware).
- **Pregunta 10:** la IA me ayudó a armar el grafo de espera (P1→R2→P2→R1→P1) y a entender bien la condición de deadlock para poder razonar los tres incisos del escenario.
