---
curso: SistemasOperativos
entregas_pendientes:
  - {fecha: "2026-08-20", entregable: "Actividad en Equipos — Solución basada en Principios de los SO (presentación final)", peso: "parte del 40% actividades de aprendizaje"}
  - {fecha: "2026-09-03", entregable: "Preguntas de Comprobación — Unidad 3 (Administración de Procesos)", peso: "parte del 40% actividades de aprendizaje"}
  - {fecha: "2026-09-03", entregable: "Indagatoria Corta — Gestión de Procesos en Arch Linux (CachyOS/Omarchy)", peso: "parte del 40% actividades de aprendizaje"}
  - {fecha: "2026-09-17", entregable: "Indagatoria — presentación (documento + exposición en inglés)", peso: "10%"}
  - {fecha: "2026-09-24", entregable: "I Prueba de Curso", peso: "parte del 20%"}
  - {fecha: "2026-10-01", entregable: "I Proyecto Programado — plataforma distribuida de procesamiento multimedia por casos (v2.0)", peso: "parte del 30%"}
  - {fecha: "2026-11-01", entregable: "Consigna Unidad 5 — Gestión de Entrada y Salida (USB/SATA/PCIe)", peso: "parte del 40% actividades de aprendizaje"}
  - {fecha: "2026-11-05", entregable: "II Proyecto Programado — exposición prototipo procesamiento distribuido", peso: "parte del 30%"}
  - {fecha: "2026-11-19", entregable: "II Prueba de Curso", peso: "parte del 20%"}
---

# Entregas y fechas

Ver también: [[Cursos/SistemasOperativos/temario]]

> Clases los jueves. Semana 1 = jueves **2026-08-06** (confirmado por el usuario). El resto de las fechas se calculó a partir de ahí, una semana de clase = jueves a jueves; cuando el programa solo daba "último día de la semana" (Unidad 5), se usó el domingo de esa semana ISO (lunes–domingo).
>
> Las 8 fechas de abajo ya están sincronizadas como tareas en Todoist (labels `sistemasoperativos` + `universidad`); la de 2026-08-13 también está en Google Calendar (evento de día completo).

| Fecha | Entregable | Peso | Estado |
|---|---|---|---|
| 2026-08-13 (semana 2) | [[Cursos/SistemasOperativos/entregables/preguntas-sesion-semana1-principios-so\|Preguntas de la Sesión — Semana 1]] (IA como Tutor Socrático, individual) | parte del 40% (actividades de aprendizaje) | entregado |
| 2026-08-20 (semana 3) | [[Cursos/SistemasOperativos/entregables/preguntas-sesion-semana2-historia-componentes-so\|Preguntas de la Sesión — Semana 2]] (IA como Tutor Socrático, individual) | parte del 40% (actividades de aprendizaje) | entregado |
| 2026-08-20 (semana 3) | [[Cursos/SistemasOperativos/entregables/actividad-equipos-principios-so\|Actividad en Equipos]] — solución basada en Principios de los SO (presentación final) | parte del 40% (actividades de aprendizaje) | documento y slides listos — falta cerrar el [[Cursos/SistemasOperativos/entregables/guion-presentacion-actividad-equipos\|guión]] (punto de reflexión de Marcos) y ensayar |
| 2026-09-03 (semana 5) | [[Cursos/SistemasOperativos/entregables/actividad-comprobacion-procesos-unidad3\|Actividad de Comprobación]] — Administración de Procesos (Unidad 3, individual, 34 pts) | parte del 40% (actividades de aprendizaje) | borrador — respuestas de fondo listas, falta revisión propia de Marcos |
| 2026-09-10 (semana 6, jueves) | [[Cursos/SistemasOperativos/entregables/indagatoria-corta-gestion-procesos\|Indagatoria Corta]] — Gestión de Procesos en Arch Linux (CachyOS/Omarchy; documento + presentación + demo) | parte del 40% (actividades de aprendizaje) | documento completo y exportado a Word (2026-09-07); [[Cursos/SistemasOperativos/entregables/guion-indagatoria-corta-gestion-procesos\|guión de la exposición]] listo — falta pegar la salida de comandos de CachyOS, las 2 capturas de Omarchy y la revisión de Joseph |
| 2026-09-17 (semana 7) | [[Cursos/SistemasOperativos/entregables/indagatoria-curso-documento-en\|Indagatoria del curso]] — presentación (documento + exposición **en inglés**); movida de semana 6 para no encimarse con la Indagatoria Corta | 10% | Bloque A (fundamentos) listo — faltan Bloque B (enfoque de IA), Bloque C (caso real + cierre) y estudiar para exponerla |
| 2026-09-24 (semana 8) | I Prueba de Curso | parte del 20% | pendiente — poco material visto todavía; Marcos va a mandar lo que han cubierto en clase para armar el repaso |
| 2026-10-01 (semana 9) | [[Cursos/SistemasOperativos/apuntes/proyecto-programado-1-plataforma-multimedia\|I Proyecto Programado]] — plataforma distribuida de procesamiento multimedia por casos (v2.0) | parte del 30% | **Rol A hecho y probado (2026-09-17); repo en GitHub (`MarcosZam13/plataforma-multimedia`) con proceso de equipo completo (2026-09-18).** PR #1 de Joseph (Rol C: dataset, reporter de recursos, dashboard, prioridad de colas, base compartida por Postgres para las 3 máquinas) revisado por Marcos (Rol A) y mergeado a `main` 2026-09-22 — 2 bugs reales corregidos en la revisión (prioridad sin cota en `app/schemas.py`, `/resultados` roto para sub-tareas de metadata) más `pool_pre_ping` en el engine de Postgres. Pendiente: correr el smoke test completo (`demo_client.py` contra Redis+worker+coordinador) antes de la integración de 3 máquinas — no se pudo verificar en la revisión por falta de Docker Desktop levantado. Mario (Rol B, ffmpeg real) puede arrancar ya contra `main` |
| 2026-11-01 (fin semana 13) | [[Cursos/SistemasOperativos/apuntes/gestion-entrada-salida-unidad5\|Consigna Unidad 5]] — Gestión de Entrada y Salida (USB, SATA, PCIe) | parte del 40% (actividades de aprendizaje) | pendiente |
| 2026-11-05 (semana 14) | II Proyecto Programado — exposición del prototipo de procesamiento distribuido | parte del 30% | pendiente |
| 2026-11-19 (semana 16) | II Prueba de Curso | parte del 20% | pendiente |

**Referencia — asignación (no es entrega en sí):** el I Proyecto Programado se asigna en semana 5 (2026-09-03).

<!--
Cuando agregues una fecha aquí, pedile a Claude Code:
"sincronizá las entregas de este curso al calendario"
-->
