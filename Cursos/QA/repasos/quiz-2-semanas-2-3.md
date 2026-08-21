---
curso: QA
tema: "Repaso — Quiz 2 (Semanas 2-3: Control de Calidad + Verificación, Validación y Pruebas)"
fecha: 2026-08-21
tipo: repaso
repaso_de:
  - "[[Cursos/QA/apuntes/control-calidad-semana-2]]"
  - "[[Cursos/QA/apuntes/verificacion-validacion-pruebas-semana-3]]"
entrega: 2026-08-26
tags: [control-de-calidad, aseguramiento-calidad, defectos, fallo-error-defecto, costos-de-calidad, verificacion, validacion, pruebas, caso-de-prueba, principios-de-pruebas, qa-vs-testing, repaso]
---

# Repaso — Quiz 2, Semanas 2-3 (QA)

Ver también: [[Cursos/QA/apuntes/control-calidad-semana-2|Apunte — Control de Calidad (Semana 2)]] · [[Cursos/QA/apuntes/verificacion-validacion-pruebas-semana-3|Apunte — V&V y Pruebas (Semana 3)]] · [[Cursos/QA/temario]] · [[Cursos/QA/entregas]]

Repaso para el quiz del 2026-08-26 (miércoles). Cubre semana 2 (control de calidad) y semana 3 (verificación, validación y pruebas) — versión densa para memorizar rápido, más autoevaluación (misma suite que el HTML interactivo). Respuestas ocultas con `<details>` — clic para revelar.

## 1. Control de calidad (Semana 2)

**4 funciones:** Reportes, Pruebas, Auditoría, Monitoreo.

**Control de calidad vs. Aseguramiento de la calidad** — mnemotécnica: *Aseguramiento se enfoca en el proceso. Control se enfoca en el producto.*

| Aspecto | Control de calidad | Aseguramiento de la calidad |
|---|---|---|
| Quién controla | Una sola persona, por inspección post-producción | Todo el negocio, sin responsable único |
| Tasa de rechazo | Se acepta un % (ej. 2%) | Se esperan 0 rechazos |
| Alcance | Termina con la entrega | Incluye distribuidores y postventa |
| Comunicación | Una sola vía | 360° — cultura de calidad total |

**Cadena Fallo → Defecto → Error** (orden de manifestación; la causalidad real es al revés):
- **Error** — lo comete una persona durante el desarrollo (acción humana, resultado incorrecto).
- **Defecto** — se introduce en el producto (causa del fallo; algo que está/no está/no está como debe).
- **Fallo** — ocurre durante el funcionamiento (manifestación visible del defecto).

**Ejemplo clásico:** distracción del programador (causa raíz) → no programa la validación del denominador=0 (**error**) → excepción no manejada queda en el código (**defecto**) → el sistema termina inesperadamente (**fallo**).

**Ciclo de vida del defecto:** `Abierto → Resuelto → Cerrado` (con retorno posible de Cerrado a Abierto). Resoluciones al pasar de Abierto a Resuelto: Arreglado, No se arreglará, Por diseño, Pospuesto, Duplicado, No reproducible.

**Tipos de defecto:** requisitos, diseño, código, documentación, entorno de apoyo.

**Severidad:** Críticos (violan leyes / hacen inservible el producto) · Mayores (disminuyen funcionamiento, el consumidor los nota) · Menores (leve, probablemente no se note).

**Costos de la calidad:** costos de **no conformidad** (anomalías internas: rechazos, mermas, averías; anomalías externas: reclamos, garantías, indemnizaciones) vs. costos de **conformidad** (detección: controles, calibración; prevención: dpto. de calidad, formación, mantenimiento preventivo).

## 2. Verificación y Validación (Semana 3)

| | Verificación | Validación |
|---|---|---|
| Pregunta clave | ¿Se construye el producto **de la manera correcta**? | ¿Se construye **el producto correcto**? |
| Determina | Consistencia/completitud de artefactos intermedios, contra especificación | Corrección del producto final contra las necesidades del usuario |
| La hace | Ingenieros | El usuario |

**Modelos del ciclo de vida (orden de aparición histórica y su relación con pruebas):**
- **Cascada** — pruebas solo al final → defectos caros de corregir.
- **V** — integra V&V en cada fase; rama izquierda = especificar, rama derecha = comprobar contra la izquierda.
- **Incremental** — se prueba cada incremento a medida que se agrega funcionalidad.
- **Prototipos** — arranca con requisitos, prototipo evaluado por el cliente, refina iterativamente.
- **XP** — diseño/codificación incremental; "probar" valida requisitos; "escuchar" al cliente.
- **Scrum** — 3 pilares: Transparencia, Adaptación, Inspección.

## 3. Caso de prueba y proceso de pruebas

**Caso de prueba:** conjunto de entradas, condiciones de ejecución y resultados esperados para un objetivo/condición de prueba particular. Ciclo de vida: **Nuevo → Automatizado → Ejecutado**, siempre asociado a un requerimiento.

**Salidas del proceso de pruebas:** producto probado, planes de prueba, informes de prueba, elementos de prueba (scripts, datos).

**Sistema de pruebas — componentes:** Equipo, Procesos, Entorno, Recursos (se relacionan entre sí: el equipo determina el uso del entorno, crea los procesos, y equipo/recursos se implementan y operan mutuamente).

**Atributos deseables del sistema de pruebas:** Funcional, Fiable, Robusto, Eficiente, Portable, Útil.

## 4. Los 7 principios de las pruebas (orden importa para el quiz)

1. Las pruebas revelan la presencia de defectos, **no** su ausencia.
2. Imposibilidad de pruebas exhaustivas (caminos casi infinitos).
3. Beneficios de las pruebas tempranas (defecto más barato cuanto antes se encuentra).
4. Agrupamiento de defectos (Pareto 20/80 — MVS 38%/4% módulos, IMS 57%/7% módulos).
5. Paradoja del pesticida (hay que variar técnicas de prueba).
6. Las pruebas deben adaptarse a necesidades específicas (contexto define el riesgo).
7. Falacia de la ausencia de errores (pocos defectos ≠ satisfacción del cliente — cita de **Dijkstra**: "el testing puede probar la presencia de errores, pero no la ausencia de ellos").

## 5. Código de ética y QA vs Testing

**Código de ética (7 principios):** Público, Cliente y empleador, Producto, Juicio, Profesión, Colegas, Uno mismo.

**QA vs Testing:** QA (Quality Assurance) ⊃ Quality Control ⊃ Testing — Testing es el círculo más interno, QA es el marco completo (procedimientos, auditorías, métricas, mejora continua).

## 6. Autoevaluación — suite de casos de prueba

**Automatizados** (opción múltiple, autocalificados en el HTML):

<details>
<summary><strong>TC-01</strong> — ¿Cuáles son las 4 funciones del control de calidad?</summary>

Reportes, Pruebas, Auditoría, Monitoreo.
</details>

<details>
<summary><strong>TC-02</strong> — Según la mnemotécnica de clase, ¿en qué se enfoca el Aseguramiento de la calidad y en qué se enfoca el Control de calidad?</summary>

Aseguramiento se enfoca en el **proceso**. Control se enfoca en el **producto**.
</details>

<details>
<summary><strong>TC-03</strong> — En la cadena error → defecto → fallo, ¿cuál de los tres "se introduce en el producto durante su desarrollo"?</summary>

El defecto.
</details>

<details>
<summary><strong>TC-04</strong> — ¿Cuáles son los 3 estados del ciclo de vida de un defecto?</summary>

Abierto → Resuelto → Cerrado.
</details>

<details>
<summary><strong>TC-05</strong> — ¿Cuál es la pregunta clave de la Verificación y cuál la de la Validación?</summary>

Verificación: ¿se está construyendo el producto de la manera correcta? Validación: ¿se está construyendo el producto correcto?
</details>

<details>
<summary><strong>TC-06</strong> — ¿Cuáles son los 3 pilares de Scrum mencionados como parte de V&V en el ciclo de vida?</summary>

Transparencia, Adaptación, Inspección.
</details>

<details>
<summary><strong>TC-07</strong> — ¿Cuáles son los 3 estados del ciclo de vida de un caso de prueba?</summary>

Nuevo → Automatizado → Ejecutado.
</details>

<details>
<summary><strong>TC-08</strong> — ¿Cuáles son los 4 componentes del sistema de pruebas?</summary>

Equipo, Procesos, Entorno, Recursos.
</details>

<details>
<summary><strong>TC-09</strong> — Según el primer principio de las pruebas, ¿qué revelan las pruebas y qué NO pueden probar?</summary>

Revelan la presencia de defectos, pero no pueden probar su ausencia.
</details>

<details>
<summary><strong>TC-10</strong> — ¿Cómo se relacionan QA, Quality Control y Testing entre sí (de más amplio a más específico)?</summary>

QA ⊃ Quality Control ⊃ Testing (Testing es el círculo más interno, contenido dentro de Quality Control, contenido dentro de QA).
</details>

**Manuales** (recordar y explicar, autocalificados por vos):

<details>
<summary><strong>TC-11</strong> — Explicá el ejemplo del teléfono/programador visto en clase (distracción → error → defecto → fallo) con tus propias palabras.</summary>

La distracción (causa raíz) hace que el programador olvide validar el límite superior de una variable (**error**, acción humana). Esa lógica mal codificada que queda en el sistema es el **defecto**. Cuando en pruebas de sistema se observa que se aceptan valores inválidos, eso es el **fallo** — la manifestación visible del defecto durante la ejecución.
</details>

<details>
<summary><strong>TC-12</strong> — Nombrá los 5 tipos de defecto vistos en clase, con un ejemplo de cada uno.</summary>

Requisitos (descripción incorrecta de cómo se comunica con software externo), Diseño (algoritmos, estructuras de datos mal definidas), Código (errores de lógica/sintaxis), Documentación (manuales incorrectos), Entorno de apoyo (herramientas de desarrollo/pruebas defectuosas).
</details>

<details>
<summary><strong>TC-13</strong> — Diferenciá costos de conformidad y costos de no conformidad, con un ejemplo de cada uno.</summary>

Conformidad = lo que se gasta para evitar/detectar defectos (ej. mantenimiento preventivo, formación). No conformidad = lo que se pierde por los defectos ya ocurridos (ej. garantías, reclamos de clientes, rechazos de producción).
</details>

<details>
<summary><strong>TC-14</strong> — Elegí dos modelos de ciclo de vida (de cascada, V, incremental, prototipos, XP) y explicá cómo cambia el momento en que se prueban las funcionalidades entre ambos.</summary>

Ej. cascada vs. modelo en V: en cascada las pruebas se hacen solo al final, cuando ya está todo construido, por lo que los defectos se detectan tarde y son caros de corregir. En el modelo en V, cada fase de especificación (rama izquierda) tiene su contraparte de prueba (rama derecha), así que las pruebas empiezan mucho antes en el ciclo de vida.
</details>

<details>
<summary><strong>TC-15</strong> — Explicá con tus palabras la metáfora de la huerta/gusanos picudos y a qué principio de las pruebas corresponde.</summary>

Corresponde al principio "las pruebas revelan la presencia de defectos, pero no pueden probar su ausencia". Si ves hojas comidas, sabés que hay insectos — pero no verlos no significa que no los haya, solo que no los detectaste. Igual con el software: encontrar defectos confirma que existen, pero no encontrarlos no garantiza que el sistema esté libre de ellos.
</details>

<details>
<summary><strong>TC-16</strong> — Explicá la "paradoja del pesticida" y qué se recomienda hacer al respecto.</summary>

Así como un pesticida deja de ser eficaz contra los mismos insectos con el tiempo (y nunca cubre a todos), repetir las mismas pruebas una y otra vez las vuelve menos eficaces para encontrar defectos nuevos. Se recomienda variar las técnicas de prueba (ej. agregar pruebas de seguridad o rendimiento) para seguir encontrando defectos distintos.
</details>

<details>
<summary><strong>TC-17</strong> — Nombrá al menos 4 de los 7 principios del código de ética de las pruebas.</summary>

Cualquier 4 de: Público, Cliente y empleador, Producto, Juicio, Profesión, Colegas, Uno mismo (ver detalle de cada uno en el apunte completo de semana 3).
</details>

<details>
<summary><strong>TC-18</strong> — ¿Qué significa la "falacia de la ausencia de errores" y qué cita de Dijkstra se relaciona con este principio?</summary>

Que encontrar y corregir muchos errores no garantiza la satisfacción del cliente — muchos productos con pocos defectos han fracasado en el mercado igual, porque un proyecto exitoso equilibra características, cronograma, presupuesto y calidad, no solo ausencia de bugs. Cita: "El testing puede probar la presencia de errores, pero no la ausencia de ellos."
</details>
