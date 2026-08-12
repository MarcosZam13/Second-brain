---
curso: SistemasOperativos
tema: Actividad en Equipos — Solución basada en Principios de los SO (Semanas 1-3)
fecha: 2026-08-12
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]]"
estado: borrador
tags: [actividad-equipos, trabajo-grupal, fase1]
---

# Actividad en Equipos — Solución basada en Principios de los SO

Ver también: [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]] · [[Cursos/SistemasOperativos/entregas]]

**Entrega (Fase 4 — presentación):** 2026-08-20 (inicio semana 3), ~5 min por grupo.
**Estado actual:** esperando qué problema eligen los compañeros de equipo. Roles (líder/investigador/documentador) todavía sin asignar.

## Checklist contra la rúbrica

- [ ] Identificación del Problema — claridad, relevancia, justificación (10%)
- [ ] Originalidad de la Solución — creatividad, innovación, justificación (20%)
- [ ] Integración de Componentes del SO — coherencia, funcionalidad, eficiencia (25%)
- [ ] Diseño Preliminar — claridad, estructura, viabilidad (20%)
- [ ] Presentación de la Propuesta — claridad, organización, comunicación (15%)
- [ ] Reflexión sobre el Aprendizaje — profundidad, conexión, autoevaluación (10%)

## Opciones de problema en evaluación (pendiente decisión del equipo)

### 1. Condiciones de carrera en un sistema de reservas concurrente ⭐ recomendada
**Principio de SO:** concurrencia y sincronización.
**Problema:** múltiples usuarios reservando el mismo recurso (asiento/boleto) al mismo tiempo sin control de acceso, generando ventas duplicadas.
**Por qué funciona:** diagrama de bloques simple (mutex/semáforo), da pie a hablar de deadlock/starvation como desafíos técnicos, ejemplo real conocido (venta de boletos).

### 2. Inanición (starvation) en una cola de impresión o tickets de soporte con prioridades
**Principio de SO:** gestión de procesos / planificación del CPU.
**Problema:** trabajos de baja prioridad nunca se ejecutan porque siempre llegan trabajos de mayor prioridad.
**Por qué funciona:** se conecta con planificación del CPU (semanas 4-6 del curso), buen diagrama de estados de proceso.

### 3. Inconsistencia de datos en un sistema de archivos sincronizado entre varios dispositivos (mini Dropbox)
**Principio de SO:** sistemas de archivos distribuidos.
**Problema:** conflictos de versión cuando el mismo archivo se edita desde dos dispositivos sin conexión simultánea.
**Por qué funciona:** es la opción más distinta al ejemplo del profesor (mejor nota en originalidad); permite hablar de réplica y versionado.

### 4. Escalación de privilegios en un sistema multiusuario embebido (ej. dispositivo IoT compartido)
**Principio de SO:** seguridad en gestión de procesos.
**Problema:** un usuario sin privilegios logra ejecutar acciones reservadas a administrador por falta de aislamiento entre procesos.
**Por qué funciona:** conecta con lo de NX/DEP ya trabajado en las Preguntas de Sesión Semana 1 — reutilizable ese razonamiento.

## Fase 1 — Identificación del Problema (una vez elegido)

*(completar cuando el equipo decida)*

- **Problema elegido:**
- **Justificación (por qué requiere principios de SO):**
- **Componentes del SO involucrados:**
- **Roles del equipo:** líder — / investigador — / documentador —

## Fase 2 — Conceptualización de la Solución (semana 2)

*(pendiente)*

## Fase 3 — Diseño Preliminar (semana 2)

*(pendiente — diagrama de bloques, algoritmos/procesos, recursos necesarios)*

## Fase 4 — Presentación de la Propuesta (semana 3, entrega 2026-08-20)

*(pendiente)*
