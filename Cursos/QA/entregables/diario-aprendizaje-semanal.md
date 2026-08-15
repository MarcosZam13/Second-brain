---
curso: QA
tema: Diario de Aprendizaje Semanal (carpeta de Drive compartida con la profesora)
fecha: 2026-08-15
tipo: entregable
entregable_de: "asignación verbal de la profesora — sin documento/PDF de rúbrica todavía"
estado: borrador
tags: [diario-aprendizaje, drive, reflexion-semanal, distinto-del-diario-reflexivo-de-proyecto]
---

# Diario de Aprendizaje Semanal

Ver también: [[Cursos/QA/temario]] · [[Cursos/QA/apuntes/calidad-semana-1|Calidad — Semana 1]] · [[Cursos/QA/apuntes/control-calidad-semana-2|Control de Calidad — Semana 2]] · [[Cursos/QA/entregables/diario-reflexivo|Diario Reflexivo del Proyecto]] (documento distinto, no confundir) · [[Cursos/QA/entregas]]

> **No es el mismo entregable que [[Cursos/QA/entregables/diario-reflexivo|el Diario Reflexivo del Proyecto]]** (ese es sobre las 5 preguntas fijas del proyecto en equipo, quincenal, y todavía no arranca porque el proyecto no ha empezado). Este es un diario **personal, semanal**, sobre la experiencia de aprendizaje del curso en sí — contenido de clase, qué se enseñó, qué se entendió y qué no — nada que ver con el proyecto. Es lo mismo que se está haciendo con este vault, pero en un documento aparte enfocado en la experiencia semanal con la materia, para compartir con la profesora.

## Formato y logística

- **Medio:** carpeta de Google Drive compartida con la profesora.
- **Estructura:** una subcarpeta por semana (`Semana 1`, `Semana 2`, `Semana 3`, ...), cada una con un PDF de esa semana.
- **Contenido de cada PDF:** qué se enseñó esa semana, qué entendí, qué no entendí, y qué aprendí — reflexión personal sobre el contenido y la experiencia de la clase, no un resumen técnico (eso ya está en los apuntes de cada semana).
- **Nombre de archivo sugerido (a confirmar con la profesora si pide uno específico):** `S{n}_DiarioAprendizaje_MarcosZamoraSanchez.pdf`.

## Pendiente

- [ ] Crear la carpeta de Drive con la estructura de subcarpetas por semana
- [ ] Compartir la carpeta con la profesora (permiso de lectura/comentario)
- [ ] Confirmar si hay una fecha límite específica de entrega/publicación del enlace, o si es continuo semana a semana
- [ ] Marcos revisa y personaliza las entradas de abajo antes de exportarlas a PDF — son un borrador inicial, no una entrega final tal cual
- [ ] Exportar Semana 1 y Semana 2 a PDF y subirlas a Drive una vez creada la carpeta

## Semana 1 (2026-08-07) — Calidad: definición y evolución del concepto

**¿Qué se enseñó?**

Arrancamos con la presentación del curso (objetivos, cronograma, cómo se reparte la nota — 50% es el proyecto). Después entramos al contenido: qué es calidad según distintos autores (Crosby, Juran, Deming, Ishikawa) y la norma ISO 9000, la diferencia entre características y requisitos, y las 6 etapas de la evolución del concepto de calidad (artesanal → industrialización → control final → control en el proceso → control en diseño → mejora continua). Cerramos con las definiciones de calidad de software (IEEE 610, Pressman, ISO 8402) y qué es el Aseguramiento de la Calidad del Software (SQA) y sus beneficios. También hicimos la actividad de "¿qué tiene más calidad?" en clase.

**¿Qué entendí?**

Me quedó claro que calidad no es "qué tan bueno es algo" en un sentido subjetivo, sino qué tan bien cumple con los requerimientos que se le pidieron — la actividad de clase lo dejó bastante claro, porque dos productos distintos pueden tener la misma calidad si ambos cumplen lo suyo. También entendí bien la lógica de la evolución histórica: se pasó de no importar la calidad en absoluto (solo producir rápido) a que la calidad se piense desde el diseño mismo del producto, no solo al final.

**¿Qué no entendí bien / qué me generó dudas?**

Al principio me costó ver la diferencia entre la etapa de "control en el proceso" y "control en diseño" — ambas suenan a que se está previniendo en vez de solo inspeccionar al final, y tuve que releerlo para notar que la diferencia está en si el problema viene de un punto específico del proceso de producción o del diseño/especificación en sí.

**¿Qué aprendí (más allá del contenido)?**

Me sirvió para darme cuenta de que en mis propios proyectos (universitarios y personales) normalmente pienso en "calidad" de forma más intuitiva, sin tener tan claro el marco de las distintas visiones (Crosby vs. Deming, etc.) ni pensar en la calidad desde la fase de diseño explícitamente.

## Semana 2 (2026-08-12) — Control de Calidad

**¿Qué se enseñó?**

Vimos varios casos reales de fallas de software (Boeing 737 MAX, Fujitsu Horizon, Knight Capital, Therac-25, CrowdStrike, Samsung Galaxy Note 7) para entender el costo real de no tener un buen control de calidad. Después la definición formal de control de calidad, sus 4 funciones (reportes, pruebas, auditoría, monitoreo), y la diferencia entre control de calidad y aseguramiento de la calidad (el control se enfoca en el producto, el aseguramiento en el proceso). También vimos la cadena fallo → defecto → error, los tipos de defectos y su clasificación por severidad, y los costos de calidad (conformidad vs. no conformidad). Hicimos la actividad de la torre de globos en clase.

**¿Qué entendí?**

La distinción control vs. aseguramiento me quedó clara con la regla mnemotécnica que dieron en clase ("aseguramiento = proceso, control = producto"). También entendí bien la cadena de causalidad: un error lo comete una persona durante el desarrollo, ese error introduce un defecto en el producto, y el defecto se manifiesta como un fallo cuando el sistema se está usando.

**¿Qué no entendí bien / qué me generó dudas?**

La pregunta de examen que vimos en clase (sobre el programador que se distrae por una llamada y programa mal un límite superior) me hizo dar cuenta de que al principio confundía "defecto" con "fallo" — pensé que el fallo era la respuesta correcta, cuando en realidad la lógica mal codificada que queda en el producto es el defecto, y el fallo sería el momento en que el sistema efectivamente se comporta mal por ese defecto.

**¿Qué aprendí (más allá del contenido)?**

Los casos reales (sobre todo Therac-25 y Boeing) me dejaron claro que el control de calidad no es un trámite burocrático, sino algo con consecuencias serias cuando se hace mal o no se hace. También conecta con lo de la semana 1: si el diseño ya contempla la calidad desde el inicio, se reduce el riesgo de este tipo de fallas graves más adelante.
