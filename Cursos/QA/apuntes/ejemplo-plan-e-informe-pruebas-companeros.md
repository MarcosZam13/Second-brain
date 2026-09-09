---
curso: QA
tema: "Ejemplo real de Fase 2 (Plan de pruebas) y Fase 3 (Informe de pruebas) — proyecto de compañeros del semestre pasado"
fecha: 2026-09-09
tipo: apunte
fuente:
  - _fuentes/QA_ejemplo-plan-de-pruebas-companeros_2026-09-09.pdf
  - _fuentes/QA_ejemplo-informe-de-pruebas-companeros_2026-09-09.docx
tags: [proyecto, fase2, fase3, plan-de-pruebas, informe-de-pruebas, ejemplo, guia]
---

# Ejemplo real de Fase 2 y Fase 3 — proyecto de compañeros del semestre pasado

Ver también: [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]] · [[Cursos/QA/entregables/plan-del-proyecto|Nuestro Plan del proyecto — Fase 1]] · [[Cursos/QA/entregas]]

**Qué es:** el Plan de pruebas (Fase 2, entregado 2026-05-07) y el Informe de pruebas (Fase 3, entregado 2026-06-11) de un equipo de un semestre anterior — Sebastián Josué Sandí Blanco, Mario Andrés Rojas Varela y Esteban Rodríguez Salas — sobre una tienda virtual de perfumes (React + Spring Boot + PostgreSQL). Sirve como referencia de estructura y nivel de detalle esperado para nuestras propias Fase 2 y Fase 3 sobre Firefly III, no como plantilla a copiar literal (el contenido técnico es de otro sistema).

## Fase 2 — Plan de pruebas: estructura que siguieron

1. **Introducción** — sistema bajo prueba, objetivo del plan, problema central que justifica la estrategia (acá: riesgo de incumplir tiempos de respuesta bajo alta concurrencia).
2. **Estrategia de pruebas** — tabla de tipos de prueba seleccionados (funcional/caja negra, rendimiento y carga, unitaria/caja blanca) con **descripción + justificación** de cada uno, atada a requerimientos concretos (ej. "R-02 a R-04 fijan tiempos de respuesta máximos → por eso pruebas de rendimiento").
3. **Entregables de las pruebas** y **herramientas** — una herramienta por tipo de prueba, cada una justificada contra el stack real: JUnit 5 + Mockito (unitarias backend), Cypress (funcional E2E frontend+API), Apache JMeter (rendimiento: carga, estrés, pico/spike, resistencia/soak).
4. **Criterios de evaluación** — umbral numérico explícito de cuándo se considera "completada" cada categoría de prueba (ej. cobertura ≥80% con JaCoCo en unitarias; ≥90% de casos Cypress pasando en funcionales) y un criterio general de cierre del plan completo.
5. **Casos de prueba** — antes de listarlos, una sección de **técnica de pruebas** que nombra y justifica cada técnica de diseño usada por tipo de componente: clases de equivalencia (formularios), valores límite (rangos numéricos/longitud), tablas de decisión (combinaciones de filtros), cobertura de sentencias/condiciones/decisiones y complejidad ciclomática (código, caja blanca), pruebas basadas en la experiencia (rendimiento). Después, **62 casos de prueba** en fichas individuales (CPU/GPU/RAM/SO/navegador del entorno, descripción, encargado, precondiciones, tipo, herramientas, datos de entrada, pasos con resultado esperado/obtenido, estado, evidencia) — 37 funcionales (TC-F), 15 unitarias (TC-U), 10 de rendimiento (TC-P).
6. **Conclusiones + referencias bibliográficas** (formato IEEE numerado [1][2][3]).

## Fase 3 — Informe de pruebas: estructura que siguieron

1. **Introducción** — mismo sistema, aclara que el objetivo es *encontrar defectos*, no corregirlos.
2. **Resultados** — distribución de casos por tipo y por módulo (conteos/gráficos), antes de entrar al detalle.
3. **Por cada módulo:** tabla de casos ejecutados (ID/Nombre/Datos de entrada/Resultado esperado/**Resultado:** Pasa, Falla, o **"Pasa pero tiene fallas ocultas"**) + un párrafo de **"Observaciones y hallazgos"** que explica el contexto detrás de cada resultado no trivial — incluyendo cuándo tuvieron que aislar frontend de backend con `cy.intercept()` porque el backend real fallaba, dejándolo documentado en vez de ocultarlo.
4. **Defectos** — tabla separada con ID propio (`DEF-F01`, `DEF-U01`, `DEF-P01`...) distinto del ID del caso de prueba que lo detectó, más Descripción, Comportamiento esperado, **Severidad** (Baja/Media/Alta/Crítica) y **Tipo** (Funcional, Limitación del sistema, Limitación de diseño, Defecto de configuración de ambiente...). Un defecto de rendimiento real que encontraron: el envío síncrono de correo por SMTP de Gmail bajo carga concurrente disparaba rate limiting y tumbaba el endpoint de órdenes (87.57% de error) — documentado como defecto de arquitectura, no solo "la prueba falló".
5. **Evaluación** — lectura crítica de conjunto: cuántos defectos por severidad, qué se prioriza corregir ya vs. qué se cierra como limitación de la herramienta de prueba (no del sistema).
6. **Recomendaciones** — una por cada defecto relevante, con la causa raíz y el cambio de diseño propuesto (ej. desacoplar el envío de correo con una cola asíncrona en vez de "arreglar el bug").
7. **Referencias bibliográficas** (formato IEEE).

## Qué vale la pena copiar para nuestro proyecto (Firefly III)

- La ficha de caso de prueba con **datos reales del entorno de quien ejecuta** (CPU/GPU/RAM/SO/navegador) — da trazabilidad real de dónde se corrió cada prueba.
- Separar **ID de caso de prueba** (`TC-F01`) de **ID de defecto** (`DEF-F01`) — un caso de prueba "pasa" y aun así puede revelar un defecto (columna "Pasa pero tiene fallas ocultas").
- La sección de "Observaciones y hallazgos" por módulo — es donde vive el criterio profesional, no en la tabla de resultados.
- Justificar cada herramienta/técnica contra el stack y los requerimientos concretos, no solo nombrarla.
- La distinción explícita en "Evaluación" entre defecto real del sistema vs. limitación de la herramienta de prueba (ej. Cypress perdiendo contexto en un redirect a un dominio externo de OAuth).

## Diferencias a tener en cuenta

- Nuestro repo es Firefly III (Laravel/PHP + Vue), no React/Spring Boot — las herramientas de este ejemplo (JUnit+Mockito, JMeter) aplican distinto stack; ver [[Cursos/QA/apuntes/proyecto-qa-guia]] para la guía oficial de esta edición del curso y confirmar qué exige realmente la rúbrica antes de copiar la estructura de herramientas.
- Este ejemplo usa IEEE para referencias; nuestra Fase 1 usa el formato que pida la guía oficial — confirmar antes de mezclar estilos entre fases.
