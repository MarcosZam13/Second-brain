---
curso: SistemasOperativos
tema: Unidad 3 — Gestión de Procesos (Semana 4)
fecha: 2026-08-27
tipo: apunte
fuente:
  - _fuentes/SistemasOperativos_todo-list-semana4_2026-08-27.docx
  - _fuentes/SistemasOperativos_actividad-comprobacion-procesos-unidad3_2026-08-27.docx
  - _fuentes/SistemasOperativos_indagatoria-corta-gestion-procesos_2026-08-27.pdf
tags: [unidad3, gestion-procesos, todo-list, actividad-comprobacion, indagatoria-corta]
---

# Unidad 3 — Gestión de Procesos (Semana 4)

Ver también: [[Cursos/SistemasOperativos/temario]] · [[Cursos/SistemasOperativos/entregas]] · [[Cursos/SistemasOperativos/apuntes/indagatoria-curso|Indagatoria del curso]] · [[Cursos/SistemasOperativos/entregables/actividad-comprobacion-procesos-unidad3|Borrador de la Actividad de Comprobación]] · [[Cursos/SistemasOperativos/entregables/indagatoria-corta-gestion-procesos|Borrador de la Indagatoria Corta]]

## Resumen de la unidad (TEC Digital)

Arranca la Unidad 3 — Gestión de Procesos (semanas 4 a 9): kernel, descripción y control de procesos, bloque de control de procesos (BCP), estados, threads, planificación del CPU y sincronización.

## TO-DO List — Semana 4

1. *(Actividad Individual)* **Preguntas de comprobación — Unidad 3** → ver [[Cursos/SistemasOperativos/entregables/actividad-comprobacion-procesos-unidad3|borrador]]. Instrucciones completas más abajo.
2. *(Actividad en Equipos)* **Indagatoria Corta — Análisis de la Gestión de Procesos en un Sistema Operativo** (semanas 3 a 5, presentación en semana 5) → ver [[Cursos/SistemasOperativos/entregables/indagatoria-corta-gestion-procesos|borrador]]. Instrucciones completas más abajo.
3. *(Actividad en Equipos)* **Indagatoria del curso** — avanzar semana a semana indagando los puntos de interés del tema asignado; coordinar con el profesor los puntos a tratar para tener retroalimentación durante la recolección de información, el análisis o el diseño de la presentación. Tema del equipo y trabajo en curso → [[Cursos/SistemasOperativos/apuntes/indagatoria-curso|apunte]] / [[Cursos/SistemasOperativos/entregables/indagatoria-curso|borrador]].

## Actividad de Comprobación — Administración de Procesos (Instrucciones del profesor)

**Curso:** IC6600 — Principios de Sistemas Operativos · **Tema:** Administración de Procesos — Estados, BCP, Cambio de Contexto y Estructuras de Control · **Valor total:** 34 puntos · **Entrega:** documento PDF, subido a TEC Digital en la evaluación "Administración de Procesos".

**Objetivo:** analizar el comportamiento de los procesos en un SO real o hipotético, identificando cómo el sistema gestiona ejecución, suspensión y coordinación de múltiples procesos, y las implicaciones en rendimiento y estabilidad. Se pide interpretar y justificar, no solo describir conceptos.

### 1. Análisis de estados de procesos en ejecución real (6 pts)

Escenario: un computador ejecuta simultáneamente un navegador reproduciendo video, un editor de texto, una app de mensajería y un proceso de actualización del sistema.

- Explicar qué eventos del sistema podrían provocar que un proceso pase de: Ejecutando → Bloqueado; Bloqueado → Listo; Listo → Suspendido.
- Analizar qué situaciones podrían provocar que el SO use los estados Bloqueado/Suspendido y Listo/Suspendido.
- Discutir qué decisiones del SO (gestión de memoria, presión de recursos, planificación del CPU) podrían provocar la suspensión de procesos.

### 2. Interpretación del Bloque de Control de Procesos — BCP (6 pts)

Tabla de procesos con tres procesos activos:

| Proceso | Estado | Prioridad | CPU usada |
|---|---|---|---|
| P1 | Ejecutando | Alta | 25 ms |
| P2 | Listo | Media | 0 ms |
| P3 | Bloqueado | Baja | 10 ms |

- Explicar qué información del BCP es necesaria para que el SO pueda reanudar P3 cuando termine su operación de E/S.
- Discutir qué ocurriría si el SO perdiera o corrompiera parte de la información del BCP de un proceso.
- Analizar por qué el BCP se considera una estructura crítica para la estabilidad del SO.

### 3. Cambio de contexto y su costo (8 pts)

Escenario: el CPU ejecuta un proceso de compilación y ocurre una interrupción para atender una operación de E/S de un dispositivo de almacenamiento.

- Describir qué información del proceso en ejecución debe guardarse durante el cambio de contexto.
- Explicar por qué el cambio de contexto tiene costo computacional aunque no se ejecute trabajo útil.
- Discutir cómo un número excesivo de cambios de contexto afecta el rendimiento.
- Proponer una situación donde reducir cambios de contexto mejore significativamente el desempeño.

### 4. Estructuras de control del sistema operativo (6 pts)

Escenario: un sistema ejecuta múltiples procesos accediendo simultáneamente a memoria, archivos y dispositivos de E/S.

- Explicar cómo interactúan: tabla de procesos, tabla de memoria, tabla de archivos, tabla de dispositivos.
- Analizar qué fallos podrían ocurrir si: la tabla de memoria se actualiza incorrectamente / la tabla de archivos pierde sincronización con los procesos / la tabla de dispositivos gestiona mal las operaciones de E/S.
- Discutir cómo el SO previene inconsistencias en estas estructuras.

### 5. Escenario integrador de gestión de procesos (8 pts)

Escenario: P1 reproduce música, P2 compila un programa, P3 descarga archivos de Internet. Durante la ejecución: P2 comienza a usar intensivamente el CPU; P3 solicita acceso a disco para guardar lo descargado; el sistema detecta presión de memoria y decide suspender temporalmente un proceso.

- Describir cómo evolucionan los estados de los procesos durante estos eventos.
- Explicar qué estructuras del SO intervienen en cada transición.
- Analizar qué problema de gestión de recursos podría aparecer (ej. inanición, sobrecarga de CPU, interbloqueo).
- Proponer mecanismos del SO que podrían evitar o mitigar ese problema.

## Indagatoria Corta — Análisis de la Gestión de Procesos en un Sistema Operativo (Instrucciones del profesor)

**Modalidad:** actividad de aprendizaje en equipo, semanas 3 a 5. **Presentación en clase:** semana 5, con demostración del SO indagado.

**Objetivo:** investigar, instalar y analizar cómo un SO específico gestiona los procesos, probando de manera práctica la distribución/sistema elegido y contrastando sus características con otro SO.

### Entregables generales

- Documento escrito (PDF) con los resultados de la indagatoria.
- Presentación para la clase.
- Demostración del SO indagado (mostrando resultados mediante el uso del sistema).

### 1. Selección e instalación del SO

Un solo SO por equipo, de la lista del documento de Equipos de Trabajo: Ubuntu, Debian, Mint, Fedora, OpenSUSE, Manjaro, Arch, Solus, KaliLinux, FreeBSD, RedHat, Windows, Android, iOS. Debe instalarse y probarse (máquina real o virtual), con evidencia práctica de uso.

### 2. Estructura del informe

- **Introducción:** descripción general del SO e importancia de la gestión de procesos en ese entorno.
- **Componentes principales de la gestión de procesos:** rol del kernel, tablas de procesos, colas de planificación, herramientas de monitoreo (`ps`, `top`, `htop`, `systemctl`, etc.).
- **Creación y finalización de procesos:** mecanismos de creación (`fork`, `exec`, `systemd`) y finalización (`kill`, `exit`, señales).
- **Planificación de procesos:** algoritmos implementados (CFS, Round Robin, MLFQ), parámetros de configuración e impacto en el rendimiento.
- **Sincronización y comunicación entre procesos:** métodos disponibles (semáforos, mutexes, pipes, sockets) con ejemplos de uso.
- **Gestión en sistemas multiprocesador y virtualizados:** planificación/sincronización en entornos multiprocesador; experiencia en VM o contenedores.
- **Comparación con otro SO:** contrastar al menos un aspecto técnico o práctico con un SO distinto.
- **Análisis crítico:** fortalezas y debilidades del sistema en la gestión de procesos.
- **Conclusiones:** síntesis de hallazgos y aprendizajes.
- **Referencias:** bibliografía académica (Stallings, Tanenbaum, Silberschatz, OSTEP, documentación oficial).

### 3. Análisis de experiencia de usuario (apartado adicional)

Entre 3 y 5 ventajas claras del sistema (ej. estabilidad, seguridad, facilidad de uso, disponibilidad de software) y entre 3 y 5 desventajas frente a sistemas similares (ej. complejidad de instalación, curva de aprendizaje, consumo de recursos, limitaciones de compatibilidad).

### Pistas por SO (orientadoras, del profesor)

- **Ubuntu/Debian/Mint:** uso de systemd; herramientas `top`, `htop`.
- **Fedora/RedHat:** integración con SELinux, enfoque en seguridad de procesos.
- **Arch/Manjaro:** flexibilidad para personalizar parámetros del scheduler (CFS).
- **OpenSUSE:** herramienta YaST para administración de procesos y servicios.
- **FreeBSD:** diferencias frente a Linux en el modelo de kernel; usa `rc.d` en lugar de systemd.
- **Windows:** herramientas gráficas (Task Manager, Process Explorer), planificador con colas de prioridad.
- **Android/iOS:** gestión de procesos ligada a optimización de batería y recursos móviles.

### Rúbrica de evaluación

| Categoría | % | Descripción |
|---|---|---|
| Introducción y descripción del sistema | 10% | Presentación clara del SO y relevancia de la gestión de procesos. |
| Descripción técnica de la gestión de procesos | 20% | Detalle de componentes y mecanismos, incluyendo herramientas propias de la distribución. |
| Evidencia práctica (instalación y pruebas) | 15% | Ejemplos documentados con capturas, comandos o experimentos simples. |
| Planificación de procesos y políticas | 15% | Análisis de algoritmos de planificación y parámetros de configuración. |
| Sincronización y comunicación | 10% | Explicación de los métodos utilizados y ejemplos en la práctica. |
| Comparación con otro sistema | 10% | Contraste con otro SO en al menos un aspecto relevante. |
| Análisis crítico y conclusiones | 10% | Reflexión sobre fortalezas, debilidades e impacto en el rendimiento. |
| Análisis de experiencia de usuario | 5% | Ventajas y desventajas generales desde la perspectiva del usuario. |
| Calidad del documento/presentación y referencias | 5% | Claridad, organización, recursos visuales y bibliografía confiable. |
