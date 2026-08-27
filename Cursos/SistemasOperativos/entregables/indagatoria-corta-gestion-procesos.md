---
curso: SistemasOperativos
tema: Indagatoria Corta — Análisis de la Gestión de Procesos en un Sistema Operativo
fecha: 2026-08-27
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3]]"
estado: borrador
tags: [indagatoria-corta, unidad3, gestion-procesos, trabajo-grupal]
---

# Indagatoria Corta — Gestión de Procesos en un Sistema Operativo

Ver también: [[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3|Instrucciones completas]] · [[Cursos/SistemasOperativos/entregas]]

**Modalidad:** en equipo (semanas 3–5) · **Presentación:** semana 5 (2026-09-03), con demostración del SO indagado.

## Sistema operativo seleccionado

**Arch Linux**, instalado/probado a través de dos variantes: **CachyOS** y **Omarchy**.

- **CachyOS** — distribución basada en Arch orientada a rendimiento: kernel parcheado, y como diferencial más relevante para esta indagatoria, permite elegir/usar schedulers alternativos al CFS por defecto (ej. **BORE**, y soporte de **sched-ext**). Da contenido directo para el apartado de "Planificación de procesos y políticas" (15%) — se puede comparar el comportamiento del scheduler de CachyOS contra el CFS estándar de un Arch vanilla o de otra distro.
- **Omarchy** — instalador/configuración opinionada de Arch + Hyprland (de DHH); útil sobre todo para el apartado de "Análisis de experiencia de usuario" (facilidad de instalación/configuración vs. Arch vanilla) y como punto de comparación práctico entre dos formas distintas de llegar al mismo sistema base.

**Ángulo sugerido para "Comparación con otro sistema operativo" (10%):** contrastar el scheduler por defecto de CachyOS (BORE/sched-ext) contra el CFS de un Arch/Ubuntu estándar — es el aspecto técnico más fuerte que ofrece esta elección y conecta directo con la rúbrica de planificación.

## Checklist contra la rúbrica

- [ ] Introducción y descripción del sistema (10%)
- [ ] Descripción técnica de la gestión de procesos — kernel, tablas, colas, herramientas (20%)
- [ ] Evidencia práctica — instalación y pruebas documentadas (15%)
- [ ] Planificación de procesos y políticas (15%)
- [ ] Sincronización y comunicación entre procesos (10%)
- [ ] Comparación con otro sistema operativo (10%)
- [ ] Análisis crítico y conclusiones (10%)
- [ ] Análisis de experiencia de usuario — 3-5 ventajas y 3-5 desventajas (5%)
- [ ] Calidad del documento/presentación y referencias (5%)

## Borrador del informe

*(pendiente — arrancar una vez el equipo confirme el SO a indagar)*
