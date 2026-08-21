---
curso: QA
tema: Plantillas — Ficha de Caso de Prueba y Ficha de Defecto
fecha: 2026-08-21
tipo: apunte
fuente:
  - _fuentes/QA_plantillas-fichas-caso-prueba-defectos_2026-08-21.docx
  - _fuentes/QA_ejemplo-caso-prueba_2026-08-21.webp
tags: [plantillas, caso-de-prueba, defectos, ficha, plan-de-pruebas]
---

# Plantillas — Ficha de Caso de Prueba y Ficha de Defecto

Ver también: [[Cursos/QA/temario]] · [[Cursos/QA/entregas]] · [[Cursos/QA/apuntes/verificacion-validacion-pruebas-semana-3|Verificación, Validación y Pruebas — Semana 3]] · [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]]

> Plantillas oficiales entregadas por la cátedra para documentar cada caso de prueba y cada defecto del plan de pruebas (Fase 2 del proyecto, ≥60 casos de prueba). **Son la referencia a seguir** — el ejemplo de la sección de abajo es solo ilustrativo del concepto, no reemplaza estos campos.

## Ficha de Caso de Prueba

| Campo | Descripción |
|---|---|
| Código | Identificador único del caso de prueba |
| Hardware y software | Entorno de ejecución |
| Sistema operativo | — |
| Navegador | — |
| Resolución | — |
| Comentarios | — |
| Nombre | Nombre descriptivo del caso |
| Descripción | Qué se está probando |
| Encargado | Quién ejecuta/documenta el caso |
| Precondiciones | Hasta 3 condiciones previas necesarias para ejecutar el caso |
| Pasos | Hasta 6 pasos de ejecución, en orden |
| Resultados esperados | Qué debería ocurrir si el caso pasa |
| Éxito | Criterio de éxito |
| Fracaso | Criterio de fracaso |
| Prioridad | — |
| Notas | — |

## Ficha de Defecto

| Campo | Descripción |
|---|---|
| Código | Identificador único del defecto |
| Hardware y software | Entorno donde se encontró |
| Sistema operativo | — |
| Navegador | — |
| Resolución | — |
| Comentarios | — |
| Nombre | Nombre descriptivo del defecto |
| Descripción | Qué falla |
| Encargado | Quién lo reporta/documenta |
| Precondiciones | Hasta 3 condiciones previas para reproducirlo |
| Pasos | Hasta 6 pasos para reproducirlo |
| Resultado esperado | Qué debería pasar |
| Resultado obtenido | Qué pasó realmente |
| Prioridad | — |
| Severidad | Ver clasificación crítica/mayor/menor en [[Cursos/QA/apuntes/control-calidad-semana-2#defectos-clasificación-por-severidad\|Control de Calidad — Semana 2]] |
| Notas | — |

## Ejemplo aplicado (referencia externa, formato distinto)

Ejemplo de ficha de caso de prueba tipo Guru99 (login bancario), usado como ilustración del concepto — no es la plantilla oficial del curso, tiene menos/otros campos:

- **Test Case ID:** BU_001 · **Descripción:** Test the Login Functionality in Banking
- **Created By:** Mark · **Reviewed By:** Bill · **Versión:** 2.1
- **QA Tester's Log:** review comments from Bill incorporated in version 2.1
- **Tester's Name:** Mark · **Date Tested:** 1-Jan-2025 · **Resultado:** Pass
- **Prerequisites:** acceso al navegador Chrome
- **Test Data:** Userid = mg12345, Pass = df12@434c
- **Test Scenario:** verificar que al ingresar usuario y contraseña válidos el cliente puede iniciar sesión
- **Pasos:**

| Step # | Step Details | Expected Results | Actual Results | Pass/Fail/Not executed/Suspended |
|---|---|---|---|---|
| 1 | Navegar a http://demo.guru99.com | El sitio debería abrir | Como se esperaba | Pass |
| 2 | Ingresar usuario y contraseña | Las credenciales pueden ingresarse | Como se esperaba | Pass |
| 3 | Clic en Submit | El cliente queda logueado | Como se esperaba | Pass |

Sirve para ver el concepto de "ficha completa" (metadatos + precondiciones + pasos + resultado esperado/obtenido + veredicto) aplicado a un caso real — al documentar el plan de pruebas del proyecto (Firefly III) usar la plantilla oficial de arriba, no esta estructura.
