---
curso: SistemasOperativos
tema: Programa del curso IC-6600 — Principios de Sistemas Operativos
fecha: 2026-08-07
tipo: apunte
fuente:
  - _fuentes/SistemasOperativos_programa-curso_2026-08-07.pdf
  - _fuentes/SistemasOperativos_unidades-tematicas_2026-08-07.png
tags: [programa, ic6600, temario, unidades]
---

# Temario — Principios de Sistemas Operativos (IC-6600)

Ver también: [[Cursos/SistemasOperativos/entregas]]

**Profesor:** Jorge Alfaro Velasco
**Vigencia:** II Semestre 2026 · Escuela de Ingeniería en Computación, Campus Tecnológico Local San Carlos

## Datos generales

- **Código:** IC-6600 · Seminario · 4 créditos · 4h clase/semana + 8h extraclase/semana
- **Ubicación:** 6to semestre — Bachillerato de Ingeniería en Computación
- **Requisito:** IC-5701 Compiladores e Intérpretes
- **Es requisito de:** IC-7602 Redes
- **Asistencia obligatoria** — más de 2 ausencias implica perder el curso; una ausencia a lección pierde el valor de las prácticas de ese día.
- **Suficiencia / reconocimiento:** no aplican.

## Descripción y objetivos

Reseña de qué son los SO, sus características y funciones, con discusión de los fundamentos de diseño y tendencias actuales. Busca que el estudiante desarrolle criterio propio sobre las decisiones de diseño de un SO y el contexto en que opera.

**Objetivos específicos:** conocer el funcionamiento de los SO, resolver sus problemas clásicos, valorar implementaciones modernas, argumentar soluciones alternativas y aplicar esos criterios a problemas similares de programación.

## Unidades didácticas (TEC Digital)

- **Unidad 1** — Introducción a los Sistemas de Cómputo (S1) → [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1|apunte]]
- **Unidad 2** — Historia y componentes de los Sistemas Operativos (S2) → [[Cursos/SistemasOperativos/apuntes/historia-componentes-so-unidad2|apunte]]
- **Unidad 3** — Gestión de Procesos (S3–S9)
- **Unidad 4** — Gestión de Memoria (S10–S11)
- **Unidad 5** — Gestión de Entrada y Salida (S12–S13) → [[Cursos/SistemasOperativos/apuntes/gestion-entrada-salida-unidad5|apunte]]
- **Unidad 6** — Sistema de Archivos (S14–S15) → [[Cursos/SistemasOperativos/apuntes/sistema-archivos-unidad6|apunte]]

## Contenidos oficiales del programa (bloques i–vii)

i. **Conceptos Básicos** — Introducción, Historia, Componentes, Llamadas al Sistema
ii. **Administración de Procesos** — Conceptos, Comunicación entre procesos, Threads, Planificación del CPU, Sincronización, Bloqueos, Paralelismo
iii. **Administración de Memoria** — Segmentación, Paginación, Memoria Virtual
iv. **Administración de Información** — Métodos de Acceso, Protección, Métodos de Asignación, Recuperación, Unidades de almacenamiento
v. **Administración de Dispositivos** — Hardware, Interfaz, Desempeño
vi. **Sistemas Distribuidos** — Estructura de Redes, Comunicación Distribuida, Coordinación Distribuida, Sistema de Archivos Distribuido
vii. **Protección y Seguridad** — Accesos, Autenticación, Cifrado

## Evaluación (ponderación oficial)

| # | Rubro | % | Fecha aproximada |
|---|---|---|---|
| 1 | Indagatoria (trabajo colaborativo, tema de actualidad) | 10% | Semana 2–6 (exposición semana 6–7) |
| 2 | Proyectos Programados (2) | 30% | Semanas 5 y 9 |
| 3 | Pruebas de curso (2) | 20% | Semana 8 y 16 |
| N | Actividades de aprendizaje (pruebas cortas, ejercicios, tareas, trabajos grupales/individuales) | 40% | Todo el semestre |
| | **Total** | **100%** | |

**Reglas de evaluación:**
- Tareas, investigaciones y pruebas cortas se entregan en la fecha y lugar indicados (laboratorio); no se reciben por correo ni fuera de plazo.
- Las pruebas cortas se aplican sin previo aviso, solo en la lección asignada.
- Los proyectos no se aceptan si se entregan después de la fecha establecida.
- La Indagatoria se evalúa con rúbrica analítica: documento escrito + exposición de resultados **en inglés**.

## Matriz de congruencia — resumen semanal

| Semana | Tema / objetivo | Evaluación asociada |
|---|---|---|
| 1 | Estructura de los sistemas de cómputo — arquitectura básica, SO como intermediario, interrupciones/DMA, SSD/NVMe | Asignación de temas de Indagatoria |
| 2–3 | Conceptos básicos del SO (introducción, historia, componentes, llamadas al sistema); ciclo de ejecución de instrucciones | — |
| 4 | Gestión de Procesos 1/3 — Kernel, descripción y control, estados de proceso | — |
| 5 | Gestión de Procesos 2/3 — bloque de control de procesos | Foro control de procesos · asignación I Proyecto Programado |
| 6 | Gestión de Procesos 3/3 — threads, planificación del CPU, algoritmos de planificación | Mapa mental estados de procesos |
| 6–7 | — | Presentación Indagatorias |
| 8 | — | **I Prueba de Curso** |
| 9 | Concurrencia de procesos | Trabajo colaborativo: prototipo de administración de procesos por colas (I Proyecto Programado) |
| 10–11 | Gestión de Memoria — particiones fijas/variables, políticas de asignación/sustitución, paginación y segmentación | Trabajo colaborativo: prototipo de procesamiento distribuido (II Proyecto Programado) |
| 12–13 | Gestión de E/S — hardware, interfaz, desempeño, planificación de disco, SSD | Presentación II avance del proyecto de investigación |
| 14 | Sistemas Distribuidos — estructura de redes, comunicación y coordinación distribuida, sistema de archivos distribuido | Exposición del prototipo de procesamiento distribuido |
| 15 | Gestión de Información (archivos) — métodos de acceso, protección, asignación, recuperación | Presentación propuesta final del proyecto de investigación |
| 16 | — | **II Prueba de Curso** |

## Bibliografía

**Principal:**
- Tanenbaum, A. y Bos, H. *Modern Operating Systems*, 5th ed., Pearson, 2023.
- Stallings, W. *Operating Systems: Internals and Design Principles*, 9th ed., Pearson, 2018.
- Silberschatz, A.; Galvin, P.; Gagne, G. *Operating System Concepts*, 10th ed., Wiley, 2018.

**Complementaria:**
- Vitillo, R. *Understanding Distributed Systems*, 2.0.0, 2022.
- van Steen, M. y Tanenbaum, A. *Distributed Systems*, 4th ed., 2023.
- Kleppmann, M. *Designing Data-Intensive Applications*, 1st ed., O'Reilly, 2017.
- Arpaci-Dusseau, R. y Arpaci-Dusseau, A. *Operating Systems: Three Easy Pieces*, 2018. (http://www.ostep.org)
