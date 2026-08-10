---
curso: QA
tema: Repaso — Semana 1 (Definición y evolución del concepto de calidad)
fecha: 2026-08-10
tipo: repaso
repaso_de: "[[Cursos/QA/apuntes/calidad-semana-1]]"
entrega: 2026-08-12
tags: [calidad, aseguramiento-calidad, definicion-calidad, evolucion-calidad, sqa, repaso]
---

# Repaso — Calidad, Semana 1

Ver también: [[Cursos/QA/apuntes/calidad-semana-1|Apunte completo de la semana]] · [[Cursos/QA/temario]] · [[Cursos/QA/entregas]]

Repaso para el quiz del 2026-08-12. Versión resumida del apunte para memorizar rápido, más un set de preguntas de autoevaluación (misma suite que el HTML interactivo). Respuestas ocultas con `<details>` — hacé clic para revelar.

## 1. Definiciones de calidad por autor

| Autor | Definición |
|---|---|
| Crosby | Cumplimiento de los requerimientos; sistema = prevención; estándar = cero defectos |
| Juran | Ausencia de defectos y adecuación al uso |
| Deming | Grado perceptible de uniformidad y fiabilidad a bajo costo, adecuado a las necesidades del cliente |
| Ishikawa | Diseñar, producir y ofrecer un producto/servicio útil, al mejor precio, que satisfaga siempre al cliente |
| ISO 9000 | Grado en que un conjunto de características inherentes cumple con los requisitos |

**Idea clave (actividad "¿qué tiene más calidad?"):** dos productos pueden tener la misma calidad si ambos cumplen sus propios requerimientos — la calidad se valida contra especificaciones, no comparando a simple vista.

## 2. Características vs. requisitos

- **Características** = propiedades del producto/servicio (ej. servicios: rapidez, honestidad, puntualidad, flexibilidad, cortesía, efectividad).
- **Requisitos** = cómo tienen que ser esas características, incluyendo los obligatorios (seguridad, legales).

## 3. Evolución del concepto de calidad — 6 etapas (orden importa)

| # | Etapa | Idea central |
|---|---|---|
| 1 | Artesanal | Productor y usuario coinciden; control implícito en el proceso |
| 2 | Industrialización | Calidad sustituida por producción: importa cantidad y tiempo, no calidad |
| 3 | Control final | *Calidad = Control de Calidad = Control Final* — el cliente recibe según especificación |
| 4 | Control en el proceso | *Calidad = Prevención = Ausencia de defectos* — inspección durante el proceso, no solo al final |
| 5 | Control en diseño | *Calidad = Gestión de Calidad* — el problema puede estar en el diseño, no en materia prima/proceso |
| 6 | Mejora continua | Excelencia vía mejora continua, gestión que alinea cliente-diseño-fabricación |

## 4. Calidad de software — 3 definiciones

- **IEEE Std. 610-1990:** grado con el que un sistema, componente o proceso cumple los requerimientos especificados y las necesidades/expectativas del cliente.
- **Pressman (1992):** concordancia con requisitos funcionales y no funcionales explícitos, estándares de desarrollo documentados, y características implícitas esperadas de software profesional.
- **ISO 8402 (UNE 66-001-92):** conjunto de características de una entidad que le confieren su aptitud para satisfacer necesidades expresadas e implícitas.

## 5. SQA — Aseguramiento de la Calidad del Software

**Definición:** conjunto de actividades (facilitación, entrenamiento, medición, análisis) para dar confianza de que los procesos están establecidos y mejoran continuamente, produciendo software que cumple requerimientos y está listo para usarse.

**6 beneficios:**
1. Detección temprana de problemas
2. Estándares de trabajo (codificación, documentación) que uniformizan el proceso
3. Verifica que objetivos individuales estén alineados con los de la organización
4. Recomienda métodos de trabajo ajustados a la naturaleza del producto
5. Evita costos innecesarios (ej. mantenimiento correctivo)
6. Planea la calidad — no es automática, hay que construirla e implantarla

## 6. Autoevaluación — suite de casos de prueba

**Automatizados** (opción múltiple, autocalificados en el HTML):

<details>
<summary><strong>TC-01</strong> — ¿Qué autor define calidad como "cumplimiento de los requerimientos", con el estándar de cero defectos?</summary>

Crosby.
</details>

<details>
<summary><strong>TC-02</strong> — ¿Qué autor define calidad como "ausencia de defectos y adecuación al uso"?</summary>

Juran.
</details>

<details>
<summary><strong>TC-03</strong> — ¿Qué etapa viene inmediatamente después de "Control final"?</summary>

Control en el proceso.
</details>

<details>
<summary><strong>TC-04</strong> — ¿A qué etapa corresponde la fórmula "Calidad = Gestión de Calidad"?</summary>

Control en diseño.
</details>

<details>
<summary><strong>TC-05</strong> — ¿Cuál de las 3 definiciones de calidad de software es la de IEEE Std. 610-1990?</summary>

"Grado con el que un sistema, componente o proceso cumple los requerimientos especificados y las necesidades o expectativas del cliente/usuario."
</details>

**Manuales** (recordar y explicar, autocalificados por vos):

<details>
<summary><strong>TC-06</strong> — Explicá con tus palabras la diferencia entre las definiciones de Crosby y Juran.</summary>

Crosby pone el foco en el cumplimiento estricto de requerimientos con cero defectos como estándar (prevención). Juran habla de ausencia de defectos, pero agrega explícitamente la "adecuación al uso" — que el producto sirva para lo que el usuario lo necesita, no solo que cumpla la especificación al pie de la letra.
</details>

<details>
<summary><strong>TC-07</strong> — ¿Por qué en la etapa de Industrialización se sustituye "calidad" por "producción"?</summary>

Porque el foco pasa a ser hacer mucho y rápido — importa la cantidad producida y el tiempo, no si el producto cumple con lo que el cliente necesita.
</details>

<details>
<summary><strong>TC-08</strong> — Nombrá al menos 3 de los 6 beneficios del SQA.</summary>

Ver lista completa en la sección 5 arriba (detección temprana, estándares de trabajo, alineación de objetivos, métodos ajustados al producto, evitar costos innecesarios, planear la calidad).
</details>

<details>
<summary><strong>TC-09</strong> — ¿Qué significa la actividad "¿qué tiene más calidad?" vista en clase?</summary>

Que la calidad no se compara a simple vista entre dos productos — se valida probando cada uno contra sus propias especificaciones. Dos productos distintos pueden tener la misma calidad si ambos cumplen lo que prometían.
</details>

<details>
<summary><strong>TC-10</strong> — Diferencia entre características y requisitos, con un ejemplo de cada uno.</summary>

Características son las propiedades del producto/servicio (ej. puntualidad de un servicio). Requisitos son cómo tienen que ser esas características (ej. "el servicio debe entregarse en menos de 24h") — incluyen los obligatorios como seguridad y legales.
</details>
