---
curso: SistemasOperativos
tema: Unidad 1 — Estructura de los Sistemas de Cómputo (Semana 1)
fecha: 2026-08-07
tipo: apunte
fuente:
  - _fuentes/SistemasOperativos_estructura-sistemas-computo-unidad1_2026-08-07.png
  - _fuentes/SistemasOperativos_todo-list-semana1_2026-08-07.docx
  - _fuentes/SistemasOperativos_preguntas-semana1-principios-so_2026-08-09.pdf
tags: [unidad1, estructura-sistemas-computo, todo-list, actividad-equipos, computo-heterogeneo, preguntas-analisis, tutor-socratico]
---

# Unidad 1 — Estructura de los Sistemas de Cómputo (Semana 1)

Ver también: [[Cursos/SistemasOperativos/temario]] · [[Cursos/SistemasOperativos/entregas]]

## Resumen de la unidad (TEC Digital)

Base sobre la que se construyen los SO: la estructura de los sistemas de cómputo. Cómo interactúan procesador, memoria y dispositivos de entrada/salida (E/S), y cómo el SO gestiona esos recursos. Se introduce el **cómputo heterogéneo (CPU, GPU y NPU)** como tendencia que atraviesa el resto del curso, conectando la arquitectura clásica con las cargas de trabajo de Inteligencia Artificial. Este conocimiento es la base para analizar decisiones de diseño e implementación de SO modernos.

## Recursos de la semana (TEC Digital)

- **Presentación de la semana** — procesador, memoria, entrada/salida, interrupciones y cómputo heterogéneo (CPU, GPU, NPU). Introducción técnica y visual a la arquitectura básica de un sistema de cómputo; incluye actividad con simulador interactivo del ciclo de instrucción.
- **Preguntas de la sesión e indicaciones** *(Actividad Individual)* — preguntas de análisis sobre ciclo de instrucción, memoria y jerarquía, E/S y gestión de recursos del SO. Incluye el modelo de uso de IA como tutor socrático: se debe documentar en una bitácora cómo se utilizó la IA para razonar cada respuesta.
- **Grupos de trabajo y temas de indagatoria** — grupos formados para la Indagatoria; cada equipo trabaja un tema actual vinculado a tecnologías relacionadas con SO. Presentación en semana 6.
- **Actividad en Equipos — Solución basada en Principios de los Sistemas Operativos** *(Semanas 1–3, detallada abajo).*

## Política de uso de IA generativa (aplica a todo el curso)

El curso **no prohíbe** el uso de IA generativa; se evalúa su uso crítico, transparente y bien documentado. Entregar respuestas copiadas directamente de una IA sin la bitácora correspondiente, o sin evidencia de razonamiento propio, se considera **entrega incompleta** y afecta el criterio "Evidencia de razonamiento propio". Este modelo se mantiene y amplía en las siguientes unidades (Indagatoria, Proyectos Programados).

## Preguntas de la sesión — Semana 1 (Actividad Individual, IA como Tutor Socrático)

**Entrega:** PDF nombrado `S1_Preguntas_NombreApellido1Apellido2`, antes del inicio de la sesión de Semana 2 (jueves **2026-08-13**), según TEC Digital.

**Objetivo:** afianzar los conceptos de la Semana 1 (arquitectura básica, SO como intermediario, ciclo de instrucción, interrupciones, DMA, cómputo heterogéneo) mediante preguntas de análisis, usando IA como tutor socrático (que ayude a razonar sin dar la respuesta final) en vez de sustituto del razonamiento propio.

### Instrucciones

1. Consultar un chat de IA en modo tutor socrático antes de responder cada pregunta (ej.: *"Ayúdame a entender por qué el modo Kernel necesita restringir el acceso al hardware, sin darme la respuesta completa"*).
2. Responder cada pregunta e inciso con palabras propias, sin copiar/parafrasear literalmente lo que entregó la IA.
3. Agregar al final un apartado **"Bitácora de uso de IA"** (3-5 líneas por pregunta en que se usó): qué se preguntó, qué se obtuvo, y qué se validó/ajustó/descartó y por qué.
4. Si no se usó IA en alguna pregunta, indicarlo brevemente ("No fue necesario, resuelto con el material de clase").

### Preguntas de análisis

Los bloques II y IV profundizan en lo visto en clase; los bloques I y III incluyen incisos "de anticipación" (pipeline, planificación, ISA) que no requieren dominio aún, solo razonar con lo visto hasta ahora.

**I. Ciclo de Instrucción y Procesador**

1. **Decodificación y diseño del procesador** — viabilidad de eliminar la etapa de decodificación con instrucciones simples de formato fijo; comparar CISC vs. RISC; impacto en hardware/compilador/consumo/diseño del SO; escenario donde sería o no recomendable; ¿simplifica o solo redistribuye la complejidad?
2. **Contador de Programa (PC), bifurcaciones y pipeline** *(de anticipación)* — por qué el PC no siempre se incrementa linealmente; impacto de una predicción de salto incorrecta; relación con cambios de contexto, planificación por quantum y sistemas multitarea intensivos; ¿el hardware condiciona las políticas de planificación del SO?
3. **Longitud del set de instrucciones (ISA)** *(de anticipación)* — comparar ISA amplio vs. reducido en rendimiento/consumo/tamaño de código/paralelización; influencia en llamadas al sistema, portabilidad del kernel y compatibilidad; ¿cuál es más adecuado para un SO de propósito general vs. un sistema embebido de tiempo real?

**II. Memoria y Jerarquía de Almacenamiento**

4. **Separación de memoria de instrucciones y datos** — Harvard vs. Von Neumann; impacto en seguridad (código malicioso), rendimiento y concurrencia; escenario donde previene una vulnerabilidad; ¿decisión arquitectónica o también estratégica del SO?
5. **Jerarquía de memoria en sistemas embebidos** — por qué se eliminan niveles de caché/memoria virtual; impacto en predictibilidad, latencia y complejidad del SO; comparación con el modelo tradicional multinivel; ¿mejora o limita la escalabilidad?
6. **Memoria caché y localidad** — principios de localidad temporal y espacial; su influencia en el diseño de la caché; relación con page faults, algoritmos de reemplazo y afinidad de procesos; escenario de mal diseño que degrade el rendimiento.

**E/S y Acceso a Datos**

7. **DMA y contención del bus** — cuellos de botella con múltiples dispositivos usando DMA simultáneamente; cómo el SO mitiga la contención; relación con planificación de I/O y priorización; estrategia de optimización para un servidor de alto tráfico.
8. **Modos de transferencia de datos** — comparar E/S programada, por interrupciones y DMA en entornos multitarea; escenario adecuado para cada mecanismo; diseño de un sistema híbrido combinándolos según carga.

**IV. Sistemas Operativos y Gestión de Recursos**

9. **Recuperación del control del CPU** — mecanismos (interrupciones, timer, modo kernel); impacto del cambio de contexto en el rendimiento; relación con el algoritmo de planificación; escenario donde un mal manejo del timer genere injusticia en la asignación de CPU.
10. **Interrupciones de hardware vs. software** — comparar sincronización y control; ventajas/desventajas en gestión de procesos; escenarios donde el SO preferiría una sobre otra; ¿cuál es más determinista?

### Formato de entrega y evaluación

Portada breve (nombre completo, curso, fecha); respuestas numeradas 1-10 con sus incisos; apartado final de Bitácora de uso de IA claramente identificado.

| Criterio | Peso |
|---|---|
| Calidad y corrección conceptual de las respuestas (10 bloques e incisos) | 60% |
| Evidencia de razonamiento propio (palabras propias, no copiadas de la IA) | 20% |
| Calidad y honestidad de la Bitácora de uso de IA | 20% |

El curso no prohíbe IA generativa; se evalúa su uso crítico, transparente y documentado — entregar respuestas copiadas sin bitácora o sin evidencia de razonamiento propio se considera entrega incompleta. Este modelo de trabajo con IA se mantiene y amplía en unidades posteriores (Indagatoria, Proyectos Programados).

## TO-DO List — Semana 1

1. **Formar Equipos de Trabajo** (máximo 3 integrantes) usando el link de grupos — se aprovecha para asignar también los temas de Indagatoria y Exposición. Los temas seleccionados por cada grupo se confirman de manera definitiva en semana 2.
2. **Instalar lenguajes de programación** necesarios para las prácticas (Python, Java, C#, entre otros).
3. *(Actividad Individual)* Revisar la presentación de la semana, participar en clase en el simulador interactivo del ciclo de instrucción, y desarrollar las preguntas de análisis junto con la bitácora de uso de IA.
4. *(Actividad en Equipos)* Iniciar la Actividad en Equipos: conceptualizar una solución tecnológica basada en principios de los SO (Fase 1: Identificación del Problema). Se trabaja durante las semanas 1 a 3.

## Actividad en Equipos — Solución basada en Principios de los Sistemas Operativos

**Objetivo:** fomentar la habilidad de conceptualizar y diseñar soluciones tecnológicas que integren los principios de los SO (gestión de recursos, procesos, memoria, sistemas de archivos, entre otros).

### a. Formación de equipos (Semana 1)

Mismos equipos del curso; cada equipo asigna roles (líder, investigador, documentador) para distribuir tareas.

### b. Contexto (Semana 1)

Diseñar una solución tecnológica que aborde un problema relacionado con Principios de los SO: gestión de procesos, memoria, sistemas de archivos, concurrencia, sincronización o sistemas distribuidos. El problema puede ser real o hipotético, pero debe estar claramente definido y justificado. La identificación del problema se hace en semana 1, en interacción con el profesor — es fundamental para avanzar en las semanas 2 y 3.

### c. Fases

**Fase 1 — Identificación del Problema (Semana 1)**
Identificar un problema o necesidad relacionado con SO o sistemas de software avanzados, claro y específico, justificando por qué requiere una solución que integre principios de SO. Ejemplos dados por el profesor:
- Optimización de la gestión de memoria en un SO.
- Mejora de la concurrencia y sincronización en un sistema multiproceso.
- Diseño de un sistema de archivos distribuido.
- Mejora de la seguridad en la gestión de procesos.

**Fase 2 — Conceptualización de la Solución (Semana 2)**
Debe incluir: descripción general del sistema propuesto, componentes del SO que se modificarán/mejorarán (procesos, memoria, archivos, etc.), tecnologías y software a utilizar, hardware necesario (si aplica), y explicación de cómo esos componentes trabajan juntos para resolver el problema.

**Fase 3 — Diseño Preliminar (Semana 2)**
Diagrama de bloques de la interacción entre componentes del SO y otros sistemas, descripción de algoritmos/procesos a implementar, lista de recursos necesarios (herramientas, bibliotecas, etc.).

> Las Fases 2 y 3 se trabajan en semana 2, en clase y como actividad extraclase; el trabajo en clase se evalúa como Aprendizaje Individual, por lo que todos los miembros del equipo deben participar.

**Fase 4 — Presentación de la Propuesta (Semana 3)**
Presentación y/o informe escrito con: explicación clara del problema y la solución, diagrama de bloques y componentes clave del diseño, discusión de desafíos técnicos de la implementación, y reflexión sobre cómo la actividad ayudó a comprender la importancia de los SO en el diseño de soluciones. Presentación al inicio de la semana 3, ~5 minutos por grupo. Valoración individual y grupal.

### d. Evaluación

| Criterio | Peso |
|---|---|
| Identificación del Problema (claridad, relevancia, justificación) | 10% |
| Originalidad de la Solución (creatividad, innovación, justificación) | 20% |
| Integración de Componentes del SO (coherencia, funcionalidad, eficiencia) | 25% |
| Diseño Preliminar (claridad, estructura, viabilidad) | 20% |
| Presentación de la Propuesta (claridad, organización, comunicación) | 15% |
| Reflexión sobre el Aprendizaje (profundidad, conexión, autoevaluación) | 10% |

### e. Recursos adicionales

Consultar material del curso (gestión de procesos, memoria, sistemas de archivos, concurrencia, sincronización, sistemas distribuidos) y ejemplos de proyectos similares en línea.

**Ejemplo de referencia dado por el profesor (sin desarrollar):**
- **Problema:** optimización de la gestión de memoria en un SO para aplicaciones de alto rendimiento.
- **Solución propuesta:** sistema de gestión de memoria con paginación y segmentación dinámica.
- **Componentes del SO:** módulo de gestión de memoria; algoritmos de reemplazo de páginas (LRU, FIFO).
- **Tecnologías:** C para los algoritmos; herramientas de simulación de memoria.
- **Hardware:** procesadores multinúcleo; RAM de alta velocidad.
- **Diagrama de bloques:** interacción entre módulo de gestión de memoria, hardware y aplicaciones de usuario.
- **Flujo de datos:** gestión de páginas de memoria y optimización de acceso.
- **Seguridad:** evitar fugas de memoria y accesos no autorizados.
- **Escalabilidad y mantenimiento:** planes a futuro.
