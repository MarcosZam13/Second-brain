---
curso: QA
tema: Pruebas de Software — Semana 4
fecha: 2026-08-27
tipo: apunte
fuente: _fuentes/QA_pruebas-software-semana4_2026-08-27.pptx
tags: [pruebas, caso-de-prueba, niveles-de-pruebas, pruebas-de-integracion, pruebas-unitarias, pruebas-de-sistema, pruebas-de-aceptacion, pruebas-de-mantenimiento, pruebas-estaticas, pruebas-dinamicas, caja-negra, caja-blanca]
---

# Pruebas de Software — Semana 4

Aseguramiento de la calidad del software, II Semestre 2026. Elaborado por Marlen Treviño (mtrevino@itcr.ac.cr).

Ver también: [[Cursos/QA/temario]] · [[Cursos/QA/entregas]] · [[Cursos/QA/apuntes/verificacion-validacion-pruebas-semana-3|Verificación, Validación y Pruebas — Semana 3]] · [[Cursos/QA/apuntes/plantillas-fichas-caso-prueba-defectos|Plantillas — Ficha de Caso de Prueba y Defecto]]

> Nota de extracción: varias diapositivas de esta clase son diagramas puramente gráficos (sin texto extraíble del `.pptx` — íconos, líneas de tiempo "usted está aquí" repetidas en cada nivel de prueba, y la diapositiva de "Pruebas de aceptación: Tipos"). Si hace falta precisión visual para examen, revisar el original archivado en `_fuentes/`.

## Agenda

- Caso de prueba (profundización de la semana 3)
- Niveles de pruebas
- Tipos de pruebas

## Caso de prueba — profundización

### Componentes de un caso de prueba (ejemplo: juego tipo Mastermind)

- **Acciones/Pasos:** configurar partida → el sistema muestra un formulario con los valores configurables (número de colores, número de pinzas/pegs, número de turnos máximo) → el jugador introduce los valores → el sistema comprueba (hay que hacer la comprobación y tomar evidencia en cada paso que sea necesario).
- **Valores de prueba/Entradas (configuración de ejemplo):** número de colores = 6, número de pinzas = 4, número de turnos = 10.
- **Resultado esperado:** se define contra esa configuración de entrada.

### Plantilla de caso de prueba

Campos: Código · Hardware y software (sistema operativo, navegador, resolución — via tags) · Comentarios · Nombre · Descripción · Encargado · Precondiciones · Pasos · Resultados esperados (por paso: Éxito / Fracaso) · Prioridad · Notas.

Ver el detalle de fichas ya elaborado en [[Cursos/QA/apuntes/plantillas-fichas-caso-prueba-defectos|plantillas-fichas-caso-prueba-defectos.md]] — mismos campos, no se duplica acá.

### Ejemplo trabajado en clase — triángulo

Un programa lee tres números enteros interpretados como los lados de un triángulo, y determina si es escaleno (lados desiguales), isósceles (dos lados iguales) o equilátero (tres lados iguales).

Casos de prueba propuestos para cubrir cada resultado posible del programa:

| Entrada (lado1, lado2, lado3) | Resultado esperado |
|---|---|
| 0, 1, 0 | Error |
| 2, 2, 3 | Isósceles |
| 2, 3, 4 | Escaleno |
| 2, 2, 2 | Equilátero |

**Por qué estos casos:** al menos se prueba un caso por cada respuesta posible del programa (error, escaleno, isósceles, equilátero) — la clase adelanta que más adelante se ven técnicas formales para elegir casos "interesantes" (partición de equivalencias, valores límite, ver más abajo).

## Niveles de pruebas

Una manera de adecuar las actividades de pruebas al proyecto es dividir el esfuerzo total en una secuencia de fases o niveles, organizados a menudo por el orden en que las porciones del sistema quedan listas para probar.

### Pruebas unitarias

*"Cuando probamos una función sola con sus casos, estamos haciendo Unit Testing"* (nota de clase).

Pasos: inspección visual del código (u otro medio) para revisar la lógica del módulo → control de errores y excepciones → revisión de condiciones y valores límite → prueba de bucles y sus anidaciones → simulación de caminos y alternativas posibles → evaluación de resultados obtenidos vs. esperados → corrección del módulo hasta su correcto funcionamiento.

### Pruebas de integración

Una vez desarrolladas las unidades, la siguiente fase es unirlas para crear el sistema. Propósito principal: descubrir defectos de las interconexiones y de la interacción entre sistemas o componentes integrados. Responsable ideal: tanto probadores como programadores.

**Técnicas:**

- **Descendente (top-down):** se integra moviéndose hacia abajo por la jerarquía de control, desde el módulo principal — primero en profundidad o primero en anchura. El módulo principal actúa como controlador; sus subordinados se reemplazan por módulos simulados (dobles de prueba) que se van sustituyendo uno a la vez por los componentes reales, en profundidad.
- **Ascendente (bottom-up):** los módulos de niveles bajos se combinan en grupos que cubren una subfunción específica; se escribe un módulo controlador (driver) que coordina entradas/salidas de los casos de prueba; se prueba el grupo; los controladores se reemplazan y los grupos se combinan hacia arriba en la estructura del programa.
- **Big Bang:** se prueba todo junto de una vez ("produciendo una explosión") — rápido, pero difícil de localizar dónde está el defecto. Pregunta retórica de la clase: *¿por qué esperar hasta que todo el código esté escrito para iniciar la integración?*
- **Funcional o transaccional:** integra el conjunto de componentes necesario para implementar una función o transacción individual, y repite el proceso reemplazando dobles de prueba por el siguiente conjunto de componentes función por función. Buen aislamiento de defectos, porque puede encontrar defectos de integración respecto al orden de los riesgos.

### Pruebas de sistema

Toman como punto de partida el producto ya integrado y probado, para verificar el comportamiento global del sistema. Normalmente las lleva a cabo un equipo independiente de técnicos especializados en pruebas.

### Pruebas de aceptación

*(Diapositiva "Tipos" es gráfica, sin texto extraíble — la categorización estándar del temario ISTQB que sigue este curso es: aceptación del usuario, aceptación operacional, aceptación contractual y aceptación reglamentaria, más las pruebas alfa/beta para software de mercado masivo. Confirmar contra la diapositiva original o los apuntes de clase si se necesita precisión para el examen.)*

### Pruebas de mantenimiento

Comprueban los defectos introducidos durante el desarrollo de cambios ya en producción. Requieren pruebas de regresión para asegurar que los cambios no afecten funcionalidades anteriores — acá la automatización se vuelve muy relevante.

## Tipos de pruebas

*Nota de clase:* la relación entre niveles y tipos de pruebas no son conceptos diferidos — un tipo de prueba se encuentra dentro de un nivel específico, no aislado de los niveles de la sección anterior.

**Trade-off temprano/tardío:** las pruebas tempranas son más económicas; las más tardías son más costosas. Las pruebas relacionadas con el cambio (regresión y confirmación) pueden ser de caja blanca, caja negra o basadas en la experiencia — no son un tipo aparte, cruzan a los tres.

### Pruebas estáticas

No ejecutan el código.

**Ventajas:** el esfuerzo de re-trabajo se reduce sustancialmente mientras la productividad de desarrollo probablemente aumenta; la evaluación en equipo agrega intercambio de información entre participantes; contribuyen a un aumento en la conciencia sobre temas de calidad.

**Defectos típicos que detectan:** referencia a una variable con valor no definido, variables nunca utilizadas, violaciones de estándares de programación, vulnerabilidades de seguridad, violaciones de sintaxis de código.

**Tipos:**
- **Revisiones:** análisis de un documento (especificaciones de requisitos, diseño de sistemas, código, planes y casos de prueba) con el objetivo de encontrar y eliminar errores.
- **Análisis estático:** busca defectos sin ejecutar el código, una vez que el código ya está escrito; encuentra defectos en el código fuente y en los modelos del software; se apoya en analizadores estáticos (herramientas de software para procesar código fuente).

### Pruebas dinámicas

Ejecutan el software: introducen valores de entrada y examinan la salida comparándola con los resultados esperados.

**Basadas en la especificación (caja negra):** tratan el software como una caja con entradas y salidas, sin conocimiento de su estructura interna; los casos de prueba se obtienen directamente de las especificaciones o de otros modelos de lo que el sistema debería hacer.
Técnicas: partición de equivalencias, análisis de valores límite, pruebas de casos de uso, diagramas de transición de estados, tablas de decisión, algoritmo de pares (pairwise).

**Basadas en la estructura (caja blanca):** se derivan del conocimiento de la estructura e implementación del software — el evaluador conoce el diseño y el código; buscan mejorar la eficiencia o la estructura del código.
Técnicas: cobertura de sentencias, cobertura de ramas/decisión, cobertura de condición (simple, múltiple, etc.), cobertura de caminos.

**Basadas en la experiencia:** se usan cuando no hay especificación adecuada para derivar casos, o no hay tiempo suficiente para ejecutar el paquete de pruebas completo. Usan la experiencia de usuarios y técnicos de pruebas para determinar las áreas más importantes de un sistema y ejercitarlas de forma consistente con el uso esperado.

### Pruebas estáticas vs. pruebas dinámicas — comparación

| Aspecto | Estáticas | Dinámicas |
|---|---|---|
| Qué se prueba | Productos de trabajo: documentos de requerimientos, casos de prueba, planes de prueba, código | El código mientras está en ejecución |
| Enfoque sobre defectos | Prevención de defectos | Detección de defectos |
| Ciclo de vida | Pueden realizarse desde las primeras etapas | Se realizan cuando el código ya está desplegado en un ambiente de pruebas |
| Técnicas | Revisión técnica, inspección, revisión de código | Pruebas funcionales y no funcionales |

## Actividades de clase

- **Caso de prueba en sistema** — práctica pendiente/en vivo con la herramienta configurada la semana 3 (Jira + TCMS).
- **Actividad de "Niveles de pruebas"** — dinámica en clase, sin contenido textual extraíble de la diapositiva.
- **Ejercicio: Caja Negra vs Caja Blanca** — comparación práctica de ambos enfoques.
