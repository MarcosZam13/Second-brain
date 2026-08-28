---
curso: SistemasOperativos
tema: Indagatoria del curso — plan para el equipo (Grupo 3, Tema 10)
fecha: 2026-08-27
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/indagatoria-curso]]"
estado: borrador — para coordinar con el equipo, versión simple sin wikilinks
tags: [indagatoria, ia, planificacion, scheduling, trabajo-grupal]
---

# Indagatoria del curso — IA y Gestión de Recursos (Grupo 3, Tema 10)

*Versión simple para compartir con el equipo y repartir el trabajo — sin referencias al vault. La versión completa con contexto/links vive en `indagatoria-curso.md` del repo de apuntes de Marcos.*

## El tema, en corto

Nos tocó investigar cómo se usa **inteligencia artificial / machine learning para optimizar la planificación (scheduling) de un sistema operativo** — en vez de las reglas fijas de siempre (Round Robin, MLFQ, CFS/EEVDF), un modelo que aprende a predecir carga y decide cómo repartir CPU con esa predicción.

**Nivel de dificultad:** alto (lo dice el mismo enunciado del profesor).

**Lo que pide puntual el tema:**
- Comparar contra las heurísticas clásicas de planificación (ventajas y riesgos, no solo describir).
- Analizar **al menos un caso real documentado** — no es solo teoría.

## Qué hay que entregar y cuándo

- **Peso:** 10% de la nota final.
- **Formato:** documento escrito + exposición **en inglés**.
- **Fecha:** semana 6 (jueves 2026-09-10), con posible extensión a semana 7 (2026-09-17).
- El profesor pide avanzar **semana a semana** desde ya (vamos en semana 4) y coordinar con él los puntos antes de profundizar, para tener retroalimentación a tiempo.

## Estructura del documento (8 piezas)

1. Introducción — qué es scheduling en un SO y por qué es un punto de entrada natural para ML.
2. Heurísticas clásicas (línea base) — Round Robin, MLFQ, CFS/EEVDF: cómo deciden, qué límites tienen.
3. Planificación adaptativa con ML — qué se predice, qué modelo se usa, con qué datos se entrena.
4. Predicción de carga — técnicas (series de tiempo, aprendizaje por refuerzo) y cómo alimentan la decisión.
5. Ventajas frente a lo clásico — adaptabilidad, mejor uso de recursos bajo carga variable.
6. Riesgos/desventajas — costo computacional del propio modelo, falta de explicabilidad, decisiones malas ante datos que el modelo nunca vio.
7. Caso real documentado — elegir uno: **autoscaling en Kubernetes (HPA/VPA) o Borg de Google**, o un **scheduler basado en eBPF** (`sched_ext` del kernel Linux).
8. Conclusiones + Referencias.

## Propuesta de división (a confirmar en equipo)

Pensada para un equipo de hasta 3 personas — ajustar según quiénes somos realmente:

- **Bloque A — Fundamentos (piezas 1-2):** introducción + heurísticas clásicas. Es la parte más "de repaso del curso", buena para arrancar rápido.
- **Bloque B — El enfoque de IA (piezas 3-6):** planificación adaptativa, predicción de carga, ventajas y riesgos. Es el corazón del tema — la parte más pesada de investigar.
- **Bloque C — Caso real + cierre (piezas 7-8):** elegir y documentar el caso real, más conclusiones/referencias, y ensamblar/traducir el documento final al inglés.

*(Quién toma qué bloque queda pendiente de decidir en equipo — cualquiera puede ajustarse según quién le tenga más ganas a cuál parte.)*

## Siguientes pasos

1. **Repartir los 3 bloques** en la próxima conversación de equipo (esta semana, antes del lunes si se puede).
2. **Elegir el caso real** a documentar (Kubernetes/Borg vs. eBPF) — condiciona qué tan técnico puede ser el Bloque C, mejor decidirlo temprano.
3. Coordinar con el profesor el alcance exacto de los puntos de interés (pide el curso, parte del modelo de avance semana a semana).
4. Definir una fecha de sincronización para juntar los 3 bloques antes de traducir/pulir el documento final.
