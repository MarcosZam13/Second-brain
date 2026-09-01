---
curso: QA
tema: Reparto de trabajo — Fase 1 (cierre) y Fase 2 (Plan de pruebas)
fecha: 2026-09-01
tipo: entregable
entregable_de: "[[Cursos/QA/entregables/plan-del-proyecto]]"
estado: borrador
tags: [proyecto, firefly-iii, fase1, fase2, reparto, equipo]
---

# Reparto de trabajo — Fase 1 (cierre) y Fase 2 (Plan de pruebas)

Ver también: [[Cursos/QA/entregables/plan-del-proyecto|Plan del proyecto]] · [[Cursos/QA/entregables/mapeo-modulos-firefly-iii|Mapeo de módulos — Firefly III]] · [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]] · [[Cursos/QA/entregas]]

Equipo de 3 personas. Nota para compartir tal cual con el equipo — quién hace qué, en qué orden.

## Fase 1 — cerrar el Plan del proyecto (entrega miércoles 2026-09-09)

El contenido de los 11 ítems oficiales ya está en borrador completo. Falta esto antes de entregar:

| Pendiente | Responsable | Detalle |
|---|---|---|
| Tercera fuente bibliográfica | **Persona 1** | Falta confirmar autoría — buscar en Scopus, IEEE Xplore, ISI Web of Science o Engineering Village, sobre privacidad de datos financieros o adopción de software autohospedado. No mayor a un quinquenio, formato IEEE |
| Portada + tabla de contenidos + índice de tablas | **Persona 2** | Formato del documento, sin contenido nuevo que redactar |
| Árbol de problemas → diagrama visual | **Persona 3** | El contenido (causas/efectos) ya está redactado en texto en el Plan del proyecto, sección "Problema" — solo falta pasarlo a diagrama |
| Revisión y validación de todo el contenido | **Los 3** | Última pasada en equipo antes de entregar, no se divide |

Fuente completa: [[Cursos/QA/entregables/plan-del-proyecto|plan-del-proyecto.md]].

## Fase 2 — Plan de pruebas (entrega miércoles 2026-10-14, semana 11)

Requisitos de la rúbrica oficial: **≥60 casos de prueba**, **3 tipos de prueba distintos**, máx. 10% manuales, formato de ficha dado por la profesora. Según el cronograma del Plan del proyecto, arranca en semana 7 (14 de septiembre).

División por los 6 módulos de alta prioridad ([[Cursos/QA/entregables/mapeo-modulos-firefly-iii|mapeo de módulos]]), 2 por persona:

| Persona | Módulos | Enfoque de casos | Técnica de prueba sugerida |
|---|---|---|---|
| **1** | Auth + Profile (2FA) | Credenciales inválidas, fuerza bruta, sesión expirada, 2FA, borrado de cuenta (destructivo) | Partición de equivalencias |
| **2** | Transaction + Category | Transaction es el módulo más denso (doble entrada contable, cálculo de saldo) — se empareja con Category, que es CRUD simple/filtrado, para balancear la carga | Valores límite |
| **3** | Account + Budget | Cuentas (saldo negativo, cuenta sin moneda asignada) + presupuestos (cálculo de disponible, fechas/períodos) | Tablas de decisión |

Con estos 6 módulos alcanza para los 60+ casos sin tocar los de media/baja prioridad (Bill, Recurring, Rule/RuleGroup, PiggyBank, TransactionCurrency, etc.) — quedan disponibles si a alguien le faltan casos para llegar a su cuota (~20 por persona).

Las 3 técnicas sugeridas (una por persona) ya cubren el requisito de "3 tipos diferentes de pruebas" de forma natural entre el equipo, sin que nadie tenga que forzar una técnica que no le calza a su módulo.

## Pendiente

- [ ] Persona 1: tercera fuente bibliográfica
- [ ] Persona 2: portada + TOC + índice de tablas
- [ ] Persona 3: diagrama del árbol de problemas
- [ ] Los 3: revisión final del Plan del proyecto antes del 2026-09-09
- [ ] Confirmar entre el equipo si esta división de módulos para Fase 2 queda así o se ajusta
