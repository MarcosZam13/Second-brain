---
curso: SistemasOperativos
tema: Preguntas de la Sesión — Semana 1 (IA como Tutor Socrático)
fecha: 2026-08-09
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]]"
estado: borrador
tags: [preguntas-analisis, tutor-socratico, bitacora-ia]
---

# Preguntas de la Sesión — Semana 1

Ver también: [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]] · [[Cursos/SistemasOperativos/entregas]]

**Entrega:** PDF nombrado `S1_Preguntas_NombreApellido1Apellido2`, antes del inicio de la sesión de Semana 2 — jueves **2026-08-13**.

## Checklist contra la rúbrica

- [ ] Calidad y corrección conceptual de las 10 respuestas e incisos (60%)
- [ ] Evidencia de razonamiento propio — palabras propias, no copiadas de la IA (20%)
- [ ] Bitácora de uso de IA — 3-5 líneas por pregunta usada, o nota de "no fue necesario" (20%)
- [ ] Portada (nombre completo, curso, fecha) y respuestas numeradas 1-10 con sus incisos
- [ ] Exportar a PDF con el nombre de archivo indicado

## I. Ciclo de Instrucción y Procesador

### 1. Decodificación y Diseño del Procesador

a. ¿Es viable eliminar la etapa de decodificación con instrucciones simples de formato fijo?
b. Comparar implicaciones en CISC vs. RISC.
c. Impacto en complejidad del hardware, rol del compilador, consumo energético, diseño del SO.
d. Escenario concreto donde sería o no recomendable, justificado técnicamente.
e. ¿Simplifica realmente el sistema o solo redistribuye la complejidad?

**Respuesta:** _(pendiente)_

### 2. Contador de Programa (PC), Bifurcaciones y Pipeline *(de anticipación)*

a. ¿Por qué el PC no siempre se incrementa linealmente?
b. Impacto de una predicción de salto incorrecta en el rendimiento.
c. Relación con cambios de contexto, planificación por quantum y sistemas multitarea intensivos.
d. Escenario con múltiples procesos generando muchas bifurcaciones — ¿cómo afecta el desempeño global?
e. ¿El diseño del hardware condiciona indirectamente las políticas de planificación del SO?

**Respuesta:** _(pendiente)_

### 3. Longitud del Set de Instrucciones (ISA) *(de anticipación)*

a. Comparar ISA amplio (A) vs. reducido (B) en rendimiento, consumo, tamaño de código, paralelización.
b. Influencia del diseño del ISA en llamadas al sistema, portabilidad del kernel, compatibilidad hacia atrás.
c. ¿Cuál es más adecuada para un SO de propósito general vs. un sistema embebido de tiempo real?
d. Justificar críticamente la elección.

**Respuesta:** _(pendiente)_

## II. Memoria y Jerarquía de Almacenamiento

### 4. Separación de Memoria de Instrucciones y Datos

a. Explicar desde Harvard vs. Von Neumann.
b. Impacto en seguridad (ejecución de código malicioso), rendimiento, concurrencia.
c. Escenario donde esta separación prevenga una vulnerabilidad específica.
d. ¿Es una decisión puramente arquitectónica o también estratégica del SO?

**Respuesta:** _(pendiente)_

### 5. Jerarquía de Memoria en Sistemas Embebidos

a. ¿Por qué podría eliminarse caché/memoria virtual en un sistema embebido?
b. Impacto en predictibilidad, latencia, complejidad del SO.
c. Comparar con el modelo tradicional de jerarquía multinivel.
d. ¿Esta simplificación mejora o limita la escalabilidad?

**Respuesta:** _(pendiente)_

### 6. Memoria Caché y Localidad

a. Principios de localidad temporal y espacial.
b. Cómo influyen en el diseño de la memoria caché.
c. Relación con page faults, algoritmos de reemplazo, afinidad de procesos.
d. Escenario donde un mal diseño de acceso a memoria degrade el rendimiento global.

**Respuesta:** _(pendiente)_

## E/S y Acceso a Datos

### 7. DMA y Contención del Bus

a. Cuellos de botella cuando múltiples dispositivos usan DMA simultáneamente.
b. Cómo el SO puede mitigar la contención del bus.
c. Relación con planificación de I/O y priorización.
d. Estrategia de optimización para un servidor de alto tráfico.

**Respuesta:** _(pendiente)_

### 8. Modos de Transferencia de Datos

a. Eficiencia de E/S programada, por interrupciones y DMA en entornos multitarea.
b. En qué escenario es más adecuado cada mecanismo.
c. Sistema híbrido que combine mecanismos según el tipo de carga.
d. Justificar técnicamente el diseño.

**Respuesta:** _(pendiente)_

## IV. Sistemas Operativos y Gestión de Recursos

### 9. Recuperación del control del CPU

a. Mecanismos que lo permiten (interrupciones, timer, modo kernel).
b. Cómo el cambio de contexto impacta el rendimiento.
c. Relación con el algoritmo de planificación.
d. Escenario donde un mal manejo del timer genere injusticia en la asignación de CPU.

**Respuesta:** _(pendiente)_

### 10. Interrupciones de Hardware vs. Software

a. Comparar desde sincronización y control.
b. Ventajas y desventajas en la gestión de procesos.
c. Escenarios donde el SO preferiría una sobre otra.
d. ¿Es una más determinista que la otra?

**Respuesta:** _(pendiente)_

## Bitácora de uso de IA

_(por pregunta usada: qué se preguntó, qué se obtuvo, qué se validó/ajustó/descartó y por qué — o "No fue necesario, resuelto con el material de clase")_

1.
2.
3.
4.
5.
6.
7.
8.
9.
10.
