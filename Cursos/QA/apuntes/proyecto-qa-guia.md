---
curso: QA
tema: Guía del Proyecto — Aprendizaje Basado en Proyectos
fecha: 2026-08-14
tipo: apunte
fuente:
  - _fuentes/QA_guia-proyecto_2026-08-14.pdf
  - _fuentes/QA_proyecto-diapositivas_2026-08-14.pptx
  - _fuentes/QA_proyecto-fases-y-rubricas-oficiales_2026-08-29.pptx
tags: [proyecto, plan-de-pruebas, diario-reflexivo, rubrica, aprendizaje-basado-en-proyectos]
---

# Guía del Proyecto — Aprendizaje Basado en Proyectos

Ver también: [[Cursos/QA/apuntes/calidad-semana-1|Calidad — Semana 1]] · [[Cursos/QA/entregables/plan-del-proyecto|Plan del proyecto]] · [[Cursos/QA/entregables/diario-reflexivo|Diario Reflexivo]] · [[Cursos/QA/entregas]]

> **Actualizado 2026-08-29** con el PPT oficial de esta edición del curso (`QA_proyecto-fases-y-rubricas-oficiales_2026-08-29.pptx`, guardado en `Cursos/QA/_fuentes/`), que trae las rúbricas completas con puntaje por ítem y las semanas de entrega reales — a diferencia del PDF/diapositivas de 2026-08-14, que era la guía institucional genérica de estrategia didáctica (con fechas de calendario de una edición anterior que no aplican acá). Donde el PPT oficial contradice al PDF genérico, **manda el PPT oficial** — se deja indicado en cada sección. El diario reflexivo se excluye de esta nota a propósito: se gestiona aparte en [[Cursos/QA/entregables/diario-reflexivo]] con su propio ritmo quincenal.

**Nota sobre las dos fuentes de semanas dentro del mismo PPT** (para que quede claro a qué se refiere esta nota cuando dice "la tabla de evaluación" o "el diagrama de fases"): ese PowerPoint trae dos diapositivas distintas con información de semanas, y no coinciden entre sí en dos de los cinco entregables.
- **Diapositiva "Evaluación"** (número 6): una tabla con el peso porcentual de cada rubro del curso (tareas, laboratorios, proyecto, examen) y, entre paréntesis, la semana de cada entregable del proyecto. Es la fuente que se usa como principal en esta nota porque es la misma que ya estaba confirmada en [[Cursos/QA/apuntes/calidad-semana-1]].
- **Diapositiva "Fases"** (número 4): un diagrama de flujo (tipo organigrama) que muestra las 5 fases del proyecto una tras otra, con su entregable y su semana de entrega debajo de cada una. Para Proyecto de pruebas + Informe de pruebas y para la Presentación, este diagrama marca una semana más tarde que la tabla de Evaluación.

Si hace falta ver el PPT directamente para entender esta diferencia, está en `Cursos/QA/_fuentes/QA_proyecto-fases-y-rubricas-oficiales_2026-08-29.pptx`.

## Objetivo del proyecto

Experimentar los procesos de calidad del software (planeación, validación, verificación) aplicados a un **repositorio de GitHub que el equipo elige y que cumple los 9 criterios de [[Cursos/QA/apuntes/criterios-seleccion-repositorio-github|Criterios para Seleccionar Proyectos en GitHub]]** (debe ser una aplicación web, mantenimiento activo, login/autenticación, issues activos, popularidad, documentación, buenas prácticas, dependencias claras, accesibilidad), en **equipos de 3 a 4 personas** (confirmado por el PPT oficial — corrige el "hasta 4" que decía esta nota antes), diseñando y ejecutando un plan de pruebas sobre ese repo. Ver candidatos evaluados en [[Cursos/QA/entregables/seleccion-repositorio-proyecto|Selección de repositorio]].

> **Corrección (2026-08-15):** el documento fuente (guía institucional genérica) describe esto como un "proyecto real de software de una empresa" con reunión con contraparte y posible convenio de confidencialidad — eso **no aplica a esta edición del curso**. La versión real es más simple: buscar/elegir un repositorio de GitHub que cumpla los requisitos que pida la profesora y aplicarle los procesos de calidad del curso, sin empresa ni contraparte externa de por medio. Ojo: la rúbrica oficial de Presentación (más abajo) todavía trae textual "resultados relevantes **para la empresa**" — es lenguaje de plantilla institucional que no se actualizó para esta edición basada en repos de GitHub; en la presentación real hay que leerlo como "resultados relevantes para el proyecto/repositorio".

## Las 5 fases (semanas de entrega confirmadas por el PPT oficial)

Marcos confirmó el 2026-08-29 que la semana 5 del curso arrancó el lunes 31 de agosto de 2026, y que el día de clase de QA (y por lo tanto el día de entrega más probable) es el miércoles. Con eso, las semanas de entrega ya tienen fecha puntual:

| Fase | Entregable(s) | Modalidad | Semana de entrega (oficial) | Fecha estimada (miércoles de esa semana) |
|---|---|---|---|---|
| 1. Identificación del problema y definición de objetivos | Plan del proyecto | Equipo (3-4 personas) | **Semana 6** | 2026-09-09 |
| 2. Planeación | Plan de pruebas (≥60 casos de prueba, **3 tipos de prueba distintos**, ver corrección abajo) | Equipo | **Semana 11**. Máximo 10% de las pruebas pueden ser manuales | 2026-10-14 |
| 3. Diseño, Desarrollo y Evaluación | Proyecto de pruebas (código, ≥90% automatizado) | Equipo | **Semana 15** según la tabla de evaluación (el diagrama de fases del mismo PPT dice "Semana 16 y 17" para proyecto de pruebas e informe combinados, no se pudo reconciliar esa diferencia entre ambas fuentes del mismo PPT, confirmar con la profesora si hace falta precisión) | 2026-11-11 |
| 3. (cont.) | Informe de pruebas | Equipo (sumativa) + evaluación entre pares (otro equipo evalúa el informe) | **Semana 16** según la tabla de evaluación | 2026-11-18 |
| 4. Comunicación | Presentación de resultados | Equipo | **Semana 16** según la tabla de evaluación (17 según el diagrama de fases, mismo desfase que la fila anterior). Exposición **en inglés** ante profesora y docente de inglés, parte de la estrategia FUI (Fomento del Uso del Inglés) | 2026-11-18 |
| 5. Reflexión | Diario reflexivo | **Individual**, en paralelo | Semana 2 a Semana 16, entradas cada 2 semanas como mínimo, ver [[Cursos/QA/entregables/diario-reflexivo|nota aparte]], no se profundiza acá | 10 de agosto al 22 de noviembre de 2026 |

**Corrección importante (2026-08-29):** la rúbrica oficial de Plan de pruebas puntúa explícitamente "utilizando 3 tipos diferentes de pruebas" (10 pts) — la guía genérica anterior y el borrador de [[Cursos/QA/entregables/plan-del-proyecto|plan-del-proyecto.md]] decían "≥2 tipos", que ya quedaba corregido a "3" en el resumen de rúbricas más abajo pero no se había propagado a la tabla de fases ni al entregable. Corregido en ambos lugares.

Con la semana 5 confirmada como ancla, la semana 1 del curso habría arrancado el lunes 3 de agosto de 2026, lo cual calza con la evidencia que ya había en el vault (el quiz de la semana 1 se aplicó el 2026-08-12, un miércoles, dentro de la semana 2, revisando contenido de la semana anterior).

## Estructura de documentos exigida — Plan del proyecto (oficial, confirmada por el PPT)

El PPT oficial solo detalla la estructura ítem por ítem para el **Plan del proyecto** (no para Plan de pruebas / Informe de pruebas, que solo traen rúbrica). Orden y contenido exigido:

1. Portada
2. Tabla de contenidos
3. Índice de tablas
4. Introducción
5. **Especificaciones del software** — lista individualizada de hardware y software que usa la aplicación, incluyendo proveedores y versiones
6. **Descripción de requerimientos o historias de usuario** — lista de todos los requerimientos/HU que se van a probar
7. **Problema** — análisis de causas y efectos del problema, se recomienda explícitamente la estrategia de árbol de problemas (ver [[Cursos/QA/apuntes/taller-arbol-problemas-objetivos]])
8. **Objetivos, metas e indicadores** — cada objetivo debe empezar con un verbo en infinitivo
9. **Recursos disponibles**
10. **Cronograma de actividades**
11. **Bibliografía** — con citas en el texto, formato IEEE

Esto reemplaza la descripción genérica que tenía antes esta nota ("portada, TOC, índice, introducción, cuerpo específico, conclusiones, referencias, anexos") — la lista oficial de arriba **no incluye conclusiones ni anexos como ítems separados**, aunque no está de más dejarlos si sobra tiempo, ya que no restan puntos y el PDF genérico sí los pedía. Bibliografía: mínimo 3 fuentes, publicadas en los últimos 5 años, de bases indexadas del TEC (Scopus, ISI Web of Science, IEEE Xplore, Engineering Village).

Para Plan de pruebas e Informe de pruebas, sin lista de estructura oficial explícita, se sigue asumiendo el esqueleto genérico (portada, TOC, índice de tablas, introducción, cuerpo, conclusiones, referencias) hasta que aparezca una fuente más específica — las rúbricas de ambos sí puntúan "tabla de contenidos" y "conclusiones" como ítems propios, así que esos dos sí aplican ahí aunque no aparezcan en el Plan del proyecto.

## Formato IEEE vs. APA — resuelto

Confirmado por las rúbricas oficiales (antes era una duda pendiente marcada como "inconsistencia del documento fuente, verificar con la profesora"):

- **Plan del proyecto:** IEEE.
- **Plan de pruebas:** IEEE.
- **Informe de pruebas:** **APA** (distinto a los otros dos — confirmado, no es error del documento).

## Rúbricas oficiales completas (puntaje por ítem, cada una sobre 100)

### Plan del proyecto

| Criterio | Puntaje |
|---|---|
| Contiene todas las partes, organizado como se solicita | 5 |
| Introducción explica con pertinencia de qué trata el documento | 5 |
| Se especifica con precisión el hardware y software del sistema | 15 |
| Están debidamente definidos los requerimientos del sistema | 25 |
| Expone un problema social real, contextualizado integralmente (social, educativo, político, económico) | 10 |
| Determina las partes del problema, sus características y factores | 15 |
| Objetivo general claro, consistente con el problema, redactado con verbo infinitivo | 15 |
| Objetivos específicos consistentes con la sistematización del problema, operacionalizan el objetivo general | 25 |
| Se identifican adecuadamente los recursos disponibles | 10 |
| Cronograma de trabajo planteado correctamente | 10 |
| Mínimo 3 fuentes de consulta, no mayores a un quinquenio | 2.5 |
| Referencias en formato IEEE, relevantes | 2.5 |
| Citas bibliográficas correctas, respeta derechos de autor | — (sin puntaje propio en la tabla) |
| Formato estándar en todo el documento | 5 |
| Reglas gramaticales y de acentuación correctas | 5 |
| Redacción con concordancia, coherencia y precisión | 5 |
| **Total** | **100** |

### Plan de pruebas

| Criterio | Puntaje |
|---|---|
| Contiene todas las partes, organizado como se solicita | 5 |
| Tabla de contenidos enlista capítulos/divisiones/subdivisiones con número de página | 5 |
| Introducción explica con pertinencia de qué trata el documento | 5 |
| Introducción presenta con precisión los objetivos del plan de pruebas (verbos infinitivos) | 5 |
| Técnicas de prueba bien definidas para casos de prueba correctos | 20 |
| Estrategia de pruebas bien planificada, **utilizando 3 tipos diferentes de pruebas** | 10 |
| Al menos 60 casos de prueba, válidos e inválidos | 20 |
| Usa el formato proporcionado para cada caso de prueba | 5 |
| Conclusiones guardan correspondencia con el resto del documento | 5 |
| Mínimo 3 fuentes de consulta, no mayores a un quinquenio | 2.5 |
| Referencias en formato IEEE, relevantes | 2.5 |
| Citas bibliográficas correctas, respeta derechos de autor | — |
| Formato estándar en todo el documento | 5 |
| Reglas gramaticales y de acentuación correctas | 5 |
| Redacción con concordancia, coherencia y claridad | 5 |
| **Total** | **100** |

### Proyecto de pruebas (código)

| Criterio | Puntaje |
|---|---|
| Cada método de prueba tiene únicamente un assert/expect | 10 |
| Nombra correctamente los métodos de prueba | 10 |
| Usa los métodos pre/post en las clases de prueba eficientemente | 10 |
| Las pruebas automáticas funcionan correctamente | 25 |
| Todas las pruebas definidas se ejecutan de manera simultánea | 10 |
| Las pruebas automatizadas corresponden al plan de pruebas definido | 15 |
| Al menos el 90% de los casos de prueba están automatizados | 20 |
| **Total** | **100** |

### Informe de pruebas (referencias en APA)

| Criterio | Puntaje |
|---|---|
| Contiene todas las partes, organizado como se solicita | 5 |
| Tabla de contenidos enlista capítulos/divisiones/subdivisiones con número de página | 5 |
| Introducción explica con precisión y pertinencia de qué trata el documento | 5 |
| Introducción presenta claramente los objetivos (verbos infinitivos) | 5 |
| Analiza correctamente la información recopilada, con tablas y gráficos comentados | 25 |
| Realiza valoraciones/juicios rigurosos sobre la información obtenida | 10 |
| Expone los hallazgos de forma clara, rigurosa y coherente | 7.5 |
| Reflexiones personales reconocen los conceptos éticos del ingeniero en computación respecto a calidad de software | 5 |
| Resultados con correspondencia a la estrategia de pruebas del plan de pruebas | 25 |
| Se describen todos los defectos encontrados durante la ejecución | 20 |
| Usa el formato proporcionado para definir los defectos | 5 |
| Mínimo 3 fuentes de consulta, no mayores a un quinquenio | 2.5 |
| Referencias en formato **APA**, relevantes | 2.5 |
| Citas bibliográficas correctas, respeta derechos de autor | 2.5 |
| Formato estándar en todo el documento | 5 |
| Reglas gramaticales y de acentuación correctas | 5 |
| Redacción con concordancia, coherencia y claridad | 5 |
| **Total** | **100** |

### Presentación de proyecto

No trae el split "contenido 60 + inglés 40" que decía esta nota antes — es una sola tabla de 100 pts que mezcla forma/inglés y contenido:

| Criterio | Puntaje |
|---|---|
| Tono y velocidad de voz pertinentes | 5 |
| Pronuncia con claridad y fluidez | 5 |
| Vocabulario amplio, sin muletillas | 2.5 |
| Postura corporal correcta | 5 |
| Información claramente relacionada con el tema | 5 |
| Resultados relevantes "para la empresa" (leer como: para el proyecto/repo) | 15 |
| Amplio dominio de los contenidos | 10 |
| Temática organizada correctamente | 2.5 |
| Duración ajustada al tiempo pactado | 5 |
| Diseño y elementos visuales atractivos y relacionados | 5 |
| Comienzo llamativo, concluye con la idea principal | 5 |
| Presentación personal formal y correcta | 15 |
| Trabajo cooperativo visible entre integrantes | 10 |
| Responde de forma acertada a las consultas | 10 |
| **Total** | **100** |

## Evaluación del proyecto (peso real sobre el curso — confirmado, coincide con `calidad-semana-1.md`)

| Entregable | Peso sobre el curso | Semana de entrega |
|---|---|---|
| Planificación del proyecto (Plan del proyecto) | 5% | Semana 6 |
| Plan de pruebas | 10% | Semana 11 |
| Proyecto de pruebas | 15% | Semana 15 |
| Informe de pruebas | 10% | Semana 16 |
| Presentación (inglés) | 5% | Semana 16 |
| Diario reflexivo | 5% | Semana 2 a 16, quincenal |
| Tareas y quices | 20% | — |
| Laboratorios (3) | 15% | — |
| Examen I | 15% | — |
| **Total** | **100%** | |

*(Esta tabla ya no es una guía institucional genérica de 60 puntos internos — es el desglose real de esta edición, tomado directo de la diapositiva "Evaluación" del PPT oficial, y coincide exactamente con lo ya registrado en [[Cursos/QA/apuntes/calidad-semana-1|calidad-semana-1.md]].)*

## Logística mencionada en la guía genérica (sin confirmar para esta edición)

- Foro en TEC-Digital abierto de semana 1 a semana 16 para consultas del proyecto.
- Grupo de WhatsApp del curso desde el inicio del semestre.
- Reunión corta con la profesora a media planeación para revisar avances (en la plantilla de ejemplo, semana 9).
- Revisión preliminar del diario reflexivo por la profesora a mitad de curso (en la plantilla de ejemplo, semana 10), con retroalimentación por correo.
- Evaluación entre pares: cada estudiante evalúa el informe de pruebas de un equipo distinto al propio.
