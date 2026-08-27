---
curso: SistemasOperativos
tema: Indagatoria del curso — tema de actualidad asignado al equipo
fecha: 2026-08-27
tipo: apunte
tags: [indagatoria, tema-actualidad, ia, planificacion, scheduling]
---

# Indagatoria del curso — tema asignado

Ver también: [[Cursos/SistemasOperativos/temario]] · [[Cursos/SistemasOperativos/entregas]] · [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1|Unidad 1 (formación de equipos y asignación de temas)]] · [[Cursos/SistemasOperativos/entregables/indagatoria-curso|Borrador de la Indagatoria]]

> No hay documento fuente para esta nota — el tema fue asignado por formulario en semana 1 y confirmado por el usuario en conversación (2026-08-27), no llegó como PDF al inbox.

## Datos generales de la Indagatoria (según temario/programa)

- **Peso:** 10% de la nota final.
- **Entrega:** documento escrito + exposición de resultados **en inglés**.
- **Fecha:** presentación semana 6 (2026-09-10), con posible extensión a semana 7 (2026-09-17).
- **Modalidad de avance:** semana a semana desde que se asignó el tema (semana 1) — coordinar con el profesor los puntos a tratar para recibir retroalimentación durante la recolección de información, el análisis o el diseño de la presentación.
- **Evaluación:** rúbrica analítica (documento + exposición).

## Tema asignado al equipo

**Grupo 3 · Tema #10 — Inteligencia Artificial y Gestión de Recursos**

- **Enfoque:** uso de aprendizaje automático para optimizar la planificación (scheduling) del sistema operativo.
- **Subtemas:** planificación adaptativa, predicción de carga.
- **Nivel de dificultad:** alto.
- **Requisito específico del tema:** evaluar ventajas y riesgos frente a heurísticas clásicas de planificación; analizar al menos un caso real documentado (ej. autoscaling en Kubernetes/Borg, o schedulers basados en eBPF).

## Puntos de interés a indagar (borrador de alcance, a validar con el profesor)

- Heurísticas clásicas de planificación (Round Robin, MLFQ, CFS) como línea base de comparación.
- Cómo se aplica ML a la planificación: qué se predice (carga, duración de ráfagas, prioridades), qué modelo/algoritmo se usa, con qué datos se entrena.
- Predicción de carga: técnicas usadas (series de tiempo, aprendizaje por refuerzo) y su impacto en decisiones de scheduling.
- Ventajas frente a heurísticas clásicas: adaptabilidad a patrones de carga cambiantes, mejor uso de recursos bajo carga variable.
- Riesgos/desventajas: costo computacional del propio modelo, falta de determinismo/explicabilidad, riesgo de decisiones subóptimas ante datos no vistos (out-of-distribution), complejidad de debugging.
- Caso real a documentar (elegir uno): autoscaling en Kubernetes (Horizontal Pod Autoscaler / Vertical Pod Autoscaler) o el sistema Borg de Google; alternativamente, algún scheduler basado en eBPF (ej. `sched_ext` en el kernel Linux) que permita políticas de planificación programables/asistidas por datos.

## Próximos pasos

1. Confirmar con el profesor el alcance exacto de los puntos de interés antes de profundizar (parte del modelo de trabajo semana a semana que pide la actividad).
2. Elegir el caso real a documentar en detalle (Kubernetes/Borg vs. eBPF scheduler) — condiciona qué tan técnico puede ser el análisis práctico.
3. Ir llenando [[Cursos/SistemasOperativos/entregables/indagatoria-curso|el borrador]] semana a semana, no dejarlo para el final.
