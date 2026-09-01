---
curso: QA
tema: "Repaso — Semana 4 (Caso de prueba profundizado, Niveles y Tipos de pruebas)"
fecha: 2026-09-01
tipo: repaso
repaso_de:
  - "[[Cursos/QA/apuntes/pruebas-software-semana-4]]"
entrega: 2026-09-02
tags: [caso-de-prueba, niveles-de-pruebas, pruebas-unitarias, pruebas-de-integracion, pruebas-de-sistema, pruebas-de-aceptacion, pruebas-de-mantenimiento, pruebas-estaticas, pruebas-dinamicas, caja-negra, caja-blanca, repaso]
---

# Repaso — Semana 4 (QA)

Ver también: [[Cursos/QA/apuntes/pruebas-software-semana-4|Apunte completo de la semana]] · [[Cursos/QA/apuntes/verificacion-validacion-pruebas-semana-3|Semana 3 (V&V)]] · [[Cursos/QA/temario]] · [[Cursos/QA/entregas]]

Repaso para el quiz del 2026-09-02 (miércoles). Cubre semana 4: profundización de caso de prueba, niveles de pruebas y tipos de pruebas. Versión densa para memorizar rápido, más autoevaluación. Respuestas ocultas con `<details>` — clic para revelar.

> Nota del apunte original: algunas diapositivas de esta clase eran puramente gráficas (líneas de tiempo "usted está aquí", tipos de pruebas de aceptación). Si el quiz pide precisión visual sobre esas diapositivas, revisar `_fuentes/QA_pruebas-software-semana4_2026-08-27.pptx`.

## 1. Caso de prueba — profundización

**Componentes de un caso de prueba** (ejemplo Mastermind): Acciones/Pasos → Valores de prueba/Entradas → Resultado esperado.

**Plantilla:** Código · Hardware y software (SO, navegador, resolución) · Comentarios · Nombre · Descripción · Encargado · Precondiciones · Pasos · Resultados esperados (Éxito/Fracaso por paso) · Prioridad · Notas.

**Ejemplo trabajado — triángulo:** programa que lee 3 lados y clasifica el triángulo.

| Entrada | Resultado |
|---|---|
| 0, 1, 0 | Error |
| 2, 2, 3 | Isósceles |
| 2, 3, 4 | Escaleno |
| 2, 2, 2 | Equilátero |

Idea clave: al menos un caso por cada resultado posible del programa (más adelante se ven técnicas formales — partición de equivalencias, valores límite).

## 2. Niveles de pruebas

Dividir el esfuerzo de pruebas en fases, típicamente en el orden en que las porciones del sistema quedan listas.

**Unitarias** — probar una función sola con sus casos. Pasos: inspección visual del código → control de errores/excepciones → condiciones y valores límite → bucles y anidaciones → simulación de caminos → comparar resultado obtenido vs. esperado → corregir.

**Integración** — unir las unidades ya desarrolladas; propósito: descubrir defectos en las interconexiones. Responsable ideal: probadores y programadores.

| Técnica | Idea |
|---|---|
| Descendente (top-down) | Baja por la jerarquía desde el módulo principal (controlador); subordinados = dobles de prueba, sustituidos uno a uno |
| Ascendente (bottom-up) | Módulos de bajo nivel se agrupan por subfunción; un driver coordina entradas/salidas; se combina hacia arriba |
| Big Bang | Todo junto de una vez — rápido pero difícil de localizar el defecto |
| Funcional/transaccional | Integra los componentes de una función/transacción a la vez, reemplazando dobles función por función — buen aislamiento de defectos |

**Sistema** — parte del producto ya integrado, verifica el comportamiento global. Normalmente la hace un equipo independiente de pruebas.

**Aceptación** — (diapositiva de tipos era gráfica; categorización estándar ISTQB: aceptación del usuario, operacional, contractual, reglamentaria, más alfa/beta para software masivo — confirmar contra el original si el quiz pide detalle).

**Mantenimiento** — comprueba defectos introducidos por cambios ya en producción; requiere pruebas de regresión (automatización muy relevante acá).

## 3. Tipos de pruebas

*Niveles y tipos no son conceptos aislados* — un tipo vive dentro de un nivel específico.

**Trade-off:** pruebas tempranas = más económicas; tardías = más costosas. Regresión y confirmación cruzan los tres tipos (caja blanca, negra, basada en experiencia) — no son un tipo aparte.

**Estáticas** — no ejecutan el código.
- Ventajas: reduce re-trabajo, aumenta productividad, evaluación en equipo intercambia información, sube la conciencia de calidad.
- Detecta: variables no definidas o nunca usadas, violaciones de estándares/sintaxis, vulnerabilidades de seguridad.
- Tipos: **Revisiones** (análisis de documentos: requisitos, diseño, código, planes/casos de prueba) y **Análisis estático** (busca defectos sin ejecutar, con analizadores estáticos).

**Dinámicas** — ejecutan el software, comparan salida real vs. esperada.
- **Caja negra (basadas en especificación):** sin conocer la estructura interna, casos derivados de la especificación. Técnicas: partición de equivalencias, valores límite, casos de uso, transición de estados, tablas de decisión, pairwise.
- **Caja blanca (basadas en estructura):** el evaluador conoce diseño y código; busca mejorar eficiencia/estructura. Técnicas: cobertura de sentencias, ramas/decisión, condición, caminos.
- **Basadas en experiencia:** cuando no hay especificación adecuada o falta tiempo; usan experiencia de usuarios/técnicos para priorizar áreas.

| Aspecto | Estáticas | Dinámicas |
|---|---|---|
| Qué se prueba | Documentos y código (sin ejecutar) | Código en ejecución |
| Enfoque | Prevención de defectos | Detección de defectos |
| Ciclo de vida | Desde etapas tempranas | Cuando ya está en ambiente de pruebas |
| Técnicas | Revisión técnica, inspección, revisión de código | Pruebas funcionales y no funcionales |

## 4. Autoevaluación — suite de casos de prueba

**Automatizados** (opción múltiple / respuesta corta):

<details>
<summary><strong>TC-01</strong> — ¿Cuáles son los 3 componentes de un caso de prueba?</summary>

Acciones/Pasos, Valores de prueba/Entradas, Resultado esperado.
</details>

<details>
<summary><strong>TC-02</strong> — En el ejemplo del triángulo, ¿qué resultado esperado corresponde a la entrada (2, 2, 3)?</summary>

Isósceles.
</details>

<details>
<summary><strong>TC-03</strong> — ¿Cuál es el propósito principal de las pruebas de integración?</summary>

Descubrir defectos de las interconexiones y de la interacción entre sistemas o componentes integrados.
</details>

<details>
<summary><strong>TC-04</strong> — ¿Cómo se llama la técnica de integración en la que "se prueba todo junto de una vez" y por qué es riesgosa?</summary>

Big Bang — es rápida, pero difícil de localizar dónde está el defecto.
</details>

<details>
<summary><strong>TC-05</strong> — En la integración descendente (top-down), ¿qué reemplaza inicialmente a los módulos subordinados?</summary>

Módulos simulados / dobles de prueba, que se van sustituyendo uno a la vez por los componentes reales.
</details>

<details>
<summary><strong>TC-06</strong> — ¿Quién lleva a cabo típicamente las pruebas de sistema?</summary>

Un equipo independiente de técnicos especializados en pruebas.
</details>

<details>
<summary><strong>TC-07</strong> — ¿Qué tipo de pruebas de mantenimiento aseguran que los cambios no afecten funcionalidades anteriores?</summary>

Pruebas de regresión.
</details>

<details>
<summary><strong>TC-08</strong> — ¿Las pruebas estáticas ejecutan el código? ¿Cuál es su enfoque respecto a los defectos?</summary>

No lo ejecutan. Su enfoque es la prevención de defectos (a diferencia de las dinámicas, que se enfocan en detección).
</details>

<details>
<summary><strong>TC-09</strong> — Nombrá los 2 tipos de pruebas estáticas vistos en clase.</summary>

Revisiones y Análisis estático.
</details>

<details>
<summary><strong>TC-10</strong> — ¿Qué diferencia a las pruebas de caja negra de las de caja blanca?</summary>

Caja negra: se basan en la especificación, sin conocer la estructura interna. Caja blanca: se derivan del conocimiento de la estructura e implementación (diseño y código).
</details>

**Manuales** (recordar y explicar, autocalificados por vos):

<details>
<summary><strong>TC-11</strong> — Explicá con tus palabras los 7 pasos de las pruebas unitarias, en orden.</summary>

Inspección visual del código para revisar la lógica del módulo → control de errores y excepciones → revisión de condiciones y valores límite → prueba de bucles y sus anidaciones → simulación de caminos y alternativas posibles → evaluación de resultados obtenidos vs. esperados → corrección del módulo hasta su correcto funcionamiento.
</details>

<details>
<summary><strong>TC-12</strong> — Diferenciá la técnica de integración ascendente (bottom-up) de la descendente (top-down).</summary>

Descendente: se integra bajando por la jerarquía de control desde el módulo principal, que actúa como controlador, sustituyendo sus subordinados (dobles de prueba) uno a la vez. Ascendente: se parte de los módulos de niveles bajos, agrupados por subfunción, con un driver que coordina entradas/salidas; se prueba el grupo y se combina hacia arriba en la estructura del programa.
</details>

<details>
<summary><strong>TC-13</strong> — ¿Por qué se dice que la técnica funcional/transaccional da "buen aislamiento de defectos"?</summary>

Porque integra los componentes necesarios para una función o transacción a la vez, reemplazando dobles de prueba por el siguiente conjunto función por función — así puede encontrar defectos de integración respecto al orden de los riesgos, en lugar de mezclar todo de golpe como el Big Bang.
</details>

<details>
<summary><strong>TC-14</strong> — Explicá el trade-off temprano/tardío en pruebas y cómo se relaciona con las pruebas de regresión y confirmación.</summary>

Las pruebas tempranas son más económicas (defectos más baratos de corregir cuanto antes se detectan); las tardías son más costosas. Las pruebas de regresión y confirmación no son un tipo aparte — pueden ser de caja blanca, caja negra o basadas en experiencia, y cruzan los tres enfoques según qué se esté verificando tras un cambio.
</details>

<details>
<summary><strong>TC-15</strong> — Nombrá al menos 4 técnicas de pruebas de caja negra y 4 de caja blanca.</summary>

Caja negra: partición de equivalencias, análisis de valores límite, pruebas de casos de uso, diagramas de transición de estados, tablas de decisión, pairwise (cualquiera 4). Caja blanca: cobertura de sentencias, cobertura de ramas/decisión, cobertura de condición (simple/múltiple), cobertura de caminos.
</details>

<details>
<summary><strong>TC-16</strong> — ¿Cuándo se recomienda usar pruebas basadas en la experiencia en lugar de basadas en especificación o estructura?</summary>

Cuando no hay una especificación adecuada para derivar casos de prueba, o no hay tiempo suficiente para ejecutar el paquete de pruebas completo — se usa la experiencia de usuarios y técnicos de pruebas para priorizar las áreas más importantes del sistema.
</details>

<details>
<summary><strong>TC-17</strong> — Completá la tabla comparativa de pruebas estáticas vs. dinámicas: qué se prueba, enfoque, ciclo de vida y técnicas de cada una.</summary>

Ver tabla completa en la sección 3 arriba: Estáticas = documentos/código sin ejecutar, prevención, desde etapas tempranas, revisión técnica/inspección/revisión de código. Dinámicas = código en ejecución, detección, cuando ya está en ambiente de pruebas, pruebas funcionales y no funcionales.
</details>
