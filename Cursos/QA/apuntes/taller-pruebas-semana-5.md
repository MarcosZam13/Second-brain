---
curso: QA
tema: Taller de Pruebas — SauceDemo (Semana 5)
fecha: 2026-09-12
tipo: apunte
fuente: _fuentes/QA_taller-pruebas-semana-5_2026-09-12.pptx
tags: [taller, caso-de-prueba, pruebas-funcionales, qatlas, trazabilidad, reporte-de-defectos]
---

# Taller de Pruebas — SauceDemo (Semana 5)

Aseguramiento de la calidad del software, II Semestre 2026. Taller práctico grupal.

Ver también: [[Cursos/QA/temario]] · [[Cursos/QA/entregas]] · [[Cursos/QA/apuntes/pruebas-software-semana-4|Pruebas de Software — Semana 4]] · [[Cursos/QA/apuntes/plantillas-fichas-caso-prueba-defectos|Plantillas — Ficha de Caso de Prueba y Defecto]] · [[Cursos/QA/entregables/diario-reflexivo|Diario Reflexivo]]

## Contexto del taller

- **Escenario:** el grupo 50 de Aseguramiento de la Calidad del Software es "contratado" por la empresa DemoShop para dar servicio de testing y determinar si una funcionalidad está lista para producción.
- **Duración:** 3 horas. **Modalidad:** grupos de 3 estudiantes. **Tipo:** testing funcional manual de aplicación web.
- **Aplicación bajo prueba:** [SauceDemo](https://www.saucedemo.com/) — sitio de comercio electrónico de práctica.
- **Ambiente de prueba:** usuario `standard_user` / contraseña `secret_sauce`. Navegadores: Chrome, Firefox o Edge.
- **Evidencia:** cada ejecución (y cada paso relevante) debe incluir captura de pantalla.
- **Objetivo general:** analizar un requerimiento, identificar condiciones de prueba, diseñar casos de prueba, ejecutarlos, recopilar evidencia, determinar el resultado y reportar defectos.

## El ciclo de diseño de casos de prueba

```
REQUERIMIENTO → ANÁLISIS → CONDICIONES DE PRUEBA
       ↓
CASOS DE PRUEBA → DATOS DE PRUEBA → EJECUCIÓN
       ↓
EVIDENCIA → PASS / FAIL / BLOCKED
       ↓
REPORTE DE DEFECTO
```

## Fase 1 — Analizar requisitos

Para cada requerimiento se deben identificar sus **condiciones de prueba** (escenarios). Ejemplo trabajado en clase (`REQ-LOGIN-003`):

- Condición 1: username vacío
- Condición 2: password vacío
- Condición 3: username y password vacíos

## Fase 2 — Crear casos de prueba

Estructura de caso de prueba usada en **QAtlas** (herramienta del profesor para digitalizar y reportar):

| Campo | Descripción |
|---|---|
| Test Case ID | Identificador único |
| Requirement ID | Requerimiento asociado |
| Title | Nombre del caso |
| Priority | High / Medium / Low |
| Preconditions | Condiciones previas |
| Test Data | Datos utilizados |
| Steps | Pasos |
| Expected Result | Resultado esperado |

**Ejemplo trabajado:**

| Campo | Valor |
|---|---|
| Requirement | REQ-LOGIN-001 |
| Title | Login con credenciales válidas |
| Priority | High |
| Preconditions | Usuario registrado |
| Data | `standard_user` / `secret_sauce` |
| Steps | Abrir aplicación → introducir username → introducir password → Login |
| Expected | Se muestra la página de productos |

### Regla de oro

**El resultado esperado se define antes de ejecutar la prueba.**

Evitar el flujo inverso: Ejecutar → ver qué pasó → recién ahí escribir el "Expected Result". Hacerlo al revés acomoda el resultado esperado a lo que ya se observó, en vez de exigirle a la aplicación cumplir algo definido de antemano.

## Fase 3 — Diseñar pruebas negativas

Para cada requerimiento, identificar situaciones válidas **e** inválidas cuando aplique. Ejemplo (Login):

- **Válido:** `standard_user` / `secret_sauce`
- **Inválido:** `standard_user` / `contraseña_incorrecta`

## Fase 4 — Ejecución

*"Dejen de ser diseñadores de pruebas. Ahora son testers."* Cada grupo intercambia sus casos con otro grupo para ejecutarlos (evita que quien diseñó el caso también lo ejecute, reduciendo sesgo).

Campos que se completan en esta fase: **Actual Result** (lo que realmente ocurrió), **Status** (Pass/Fail/Blocked), **Evidence** (screenshot).

### Definición de resultados

- **PASS:** Expected = Actual.
- **FAIL:** Expected ≠ Actual.
- **BLOCKED:** el caso no puede ejecutarse por un impedimento (ej. la aplicación no permite iniciar sesión).

### Evidencia

Una captura debe demostrar el resultado de la prueba, y de preferencia el paso a paso completo, para que tenga valor real para el equipo de desarrollo al reproducir el problema.

## Fase 5 — Encontrar defectos

Cuando Expected ≠ Actual, se debe crear un defecto (bug report).

## Trazabilidad

Es importante poder entregar una tabla que conecte requerimiento → caso de prueba → resultado → defecto:

| Requirement | Test Case | Result | Bug |
|---|---|---|---|
| REQ-LOGIN-001 | TC-LOGIN-001 | PASS | — |
| REQ-LOGIN-002 | TC-LOGIN-002 | PASS | — |
| REQ-PRODUCT-001 | TC-PRODUCT-001 | FAIL | BUG-001 |
| REQ-CART-001 | TC-CART-001 | PASS | — |
| REQ-CHECKOUT-001 | TC-CHECKOUT-001 | PASS | — |

## Cierre

Generación de informes y gráficos del proyecto directamente en QAtlas, a partir de los casos, ejecuciones y defectos cargados durante el taller.
