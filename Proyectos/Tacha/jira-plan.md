---
proyecto: Tacha
tema: "Plan de Jira — 22 épicas, recorte a 10 semanas"
fecha: 2026-09-04
tipo: documentacion
estado: 22 épicas creadas en Jira (SCRUM-1 a SCRUM-22, proyecto "Equipo Dinamita" en tacha.atlassian.net). Falta desglosar HU individuales como Historias dentro de cada épica.
tags: [tacha, jira, planificacion]
---

# Plan de Jira — Tacha

Ver también: [[Proyectos/Tacha/historias-usuario|historias-usuario.md]] (fuente de las 22 épicas) · [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]]

Board: https://tacha.atlassian.net/jira/software/projects/SCRUM/boards/1 (proyecto "Equipo Dinamita", key SCRUM).

> **Este documento es de nivel épica, no el plan de sprints.** El plan real de sprints (semana a semana, por HU individual, no por épica) ya existía en [[Proyectos/Tacha/analisis-complejidad-viabilidad|analisis-complejidad-viabilidad.md]] (2026-08-21) — 93 HU en Fibonacci, dueño por HU, 8 sprints de 1 semana + semanas 9-10 integración + 11-12 testing/deploy. Ese documento decía "pendiente de repartir en JIRA" y nunca se hizo — lo pasé por alto dos veces (al escribir esta nota el 2026-09-04, y de nuevo el 2026-09-05 al empezar a crear sprints desde cero). **Antes de tocar sprints o asignaciones semanales en Tacha, leer ese documento primero, no este.** Este archivo sigue sirviendo para la lista de corte por prioridad Highest/Low a nivel de épica (sección "Cómo se recortó el alcance").
>
> Ya existen 94 issues tipo Historia en Jira (SCRUM-23+), no solo las 22 épicas — falta mapear los códigos HU-xx del documento de complejidad a esas keys de Jira.
>
> **Actualización 2026-09-05: hecho.** Las 93 HU del documento de complejidad ya están en Jira con Sprint (customfield_10020) + dueño real (assignee) + puntos Fibonacci (customfield_10016, "Story point estimate"). Sprints 1-7 poblados (fechas 7 sep - 26 oct 2026), Sprint 8-9 vacíos a propósito (colchón/integración, igual que el plan original). Los IDs de sprint en este Jira no son correlativos desde 1: Sprint 1 = ID 1, pero Sprint 2 = ID 34 (después secuencial: 34-39 para Sprints 2-7). Si se necesita tocar sprints de nuevo, verificar el ID real vía JQL `sprint = N` antes de escribir — no asumir.

## Supuesto de fecha (marcar si está mal)

No hay fecha de entrega final de Tacha cargada en `Cursos/DesarrolloWeb/entregas.md` (vacío). Para priorizar asumí **~10 semanas desde el 2026-09-04**, en línea con el cierre de los otros cursos (Seguridad 2026-11-09, SO 2026-11-19) → objetivo implícito **mediados de noviembre 2026**. Confirmar la fecha real con el profesor/programa del curso y ajustar el orden de sprints si es distinta.

## Cómo se recortó el alcance

No se eliminó ninguna épica ni el área de nadie — las 22 épicas de historias-usuario.md están todas creadas. El recorte es de **prioridad dentro del área de cada persona**: cada quien tiene 1-2 épicas "Highest/High" (su entregable mínimo garantizado) y el resto en "Medium/Low/Lowest" (lo que suma si alcanza el tiempo). Así nadie se queda sin nada si el semestre aprieta, pero tampoco se promete todo el desglose original.

| Prioridad | Significado |
|---|---|
| Highest | Sin esto no hay demo — bloquea todo lo demás |
| High | Necesario para que el producto se sienta completo |
| Medium | Suma valor real, no bloquea nada crítico |
| Low / Lowest | Candidato a cortar primero si el tiempo aprieta |

## Épicas por owner (según asignación real del equipo)

**Esteban** (auth/households/profiles) — SCRUM-4 Registro manual (Highest), SCRUM-6 Login (Highest), SCRUM-8 Perfil y sesión (High), SCRUM-9 Grupo familiar (High), SCRUM-7 Recuperación de contraseña (Medium), SCRUM-5 Registro Google/Facebook (Low — depende de credenciales OAuth aún pendientes).

**Marcos** (lists + PWA) — SCRUM-10 Lista general (Highest, el loop core), SCRUM-12 Sublistas por fecha (Medium), SCRUM-13 Listas privadas (Medium), SCRUM-20 Configuración (Low), SCRUM-21 Grupos de productos (Low).

**Daniel** (scraping + catálogo) — SCRUM-14 Catálogo de productos y categorías (Highest — backend ya en PR #1 "web-scraping-core", falta la UI), SCRUM-15 Mis productos personalizados (Low).

**Laura** (dashboard financiero) — SCRUM-11 Dashboard financiero (High, arrancar solo con gasto total + por categoría), SCRUM-16 Historial de compras (Medium).

**Roberto** (recetas + planificador) — SCRUM-17 Recetas (Medium, CRUD + agregar a lista es su mínimo), SCRUM-18 Planificador semanal (Low), SCRUM-22 Reconciliación "¿Qué hiciste?" (Lowest, depende de que existan Recetas/Planificador).

**Melany** (UI + inventario) — SCRUM-19 Inventario doméstico (Low — si el tiempo aprieta, volver a la versión pre-2026-08-19 de solo sugerencias pasivas sin pantalla de vencimientos).

**Sin owner fijo (landing pública)** — SCRUM-1 Página de inicio (High), SCRUM-2 Footer (Medium), SCRUM-3 About (Low). Repartir en la próxima reunión de equipo; son de bajo esfuerzo individual, buen candidato para quien vaya más adelantado con su módulo principal.

## Pendiente

- Desglosar las HU/CA de cada épica como issues tipo "Historia" dentro de Jira (el texto completo ya está listo en historias-usuario.md, formato v2.2 "listo para importar a JIRA") — no se hizo en esta pasada por volumen (90+ HU), quedó a nivel de épica solamente.
- Asignar las épicas a las cuentas de Jira reales de cada integrante (se dejaron sin `assignee`, solo con label del nombre, porque no se verificaron sus account IDs).
- Confirmar la fecha de entrega real y, si difiere mucho de mediados de noviembre, revisar el orden de prioridad de arriba.
