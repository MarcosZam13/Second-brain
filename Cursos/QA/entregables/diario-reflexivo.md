---
curso: QA
tema: Diario Reflexivo (bitácora) — Proyecto
fecha: 2026-08-14
tipo: entregable
entregable_de: "[[Cursos/QA/apuntes/proyecto-qa-guia]]"
estado: borrador
tags: [diario-reflexivo, bitacora, proyecto, reflexion]
---

# Diario Reflexivo (bitácora) — Proyecto de QA

Ver también: [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]] · [[Cursos/QA/apuntes/calidad-semana-1|Calidad — Semana 1]] · [[Cursos/QA/apuntes/control-calidad-semana-2|Control de Calidad — Semana 2]] · [[Cursos/QA/entregas]]

**Peso:** 5% (parte del Proyecto, 50% del curso).
**Modalidad:** individual, en paralelo al resto de fases del proyecto en equipo.
**Formato:** documento digital publicado en un sitio accesible (plataforma libre — Word/Drive/blog/Notion, etc.), visible para la profesora y el resto de estudiantes desde la semana 1. El enlace debe quedar publicado en TEC-Digital antes de la semana 6.
**Cadencia real (corregida):** entradas **quincenales**, no semanales — cada entrada cubre **dos semanas**. Se requieren mínimo **8 entradas** en total a lo largo del curso (16 semanas ÷ 2).
**Estado real (actualizado 2026-08-17):** este diario está atado a las fases del proyecto (ver [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]]). El proyecto **ya arrancó** — el equipo eligió repositorio el 2026-08-17: [firefly-iii/firefly-iii](https://github.com/firefly-iii/firefly-iii) (ver [[Cursos/QA/entregables/seleccion-repositorio-proyecto]]). La Entrada 1 de abajo ya está redactada y actualizada con esa decisión — sigue pendiente confirmar con la profesora/TEC-Digital la fecha real de entrega de la primera entrada. No confundir con el [[Cursos/QA/entregables/diario-aprendizaje-semanal|Diario de aprendizaje semanal]], que es un documento distinto (carpeta de Drive compartida con la profesora, una entrada por semana sobre lo aprendido en clase) y sí está activo desde ya.

## Preguntas fijas que debe responder cada entrada (obligatorias, las 5)

a. ¿Qué he hecho? ¿Qué pasos he seguido?
b. ¿Cuáles dificultades se han presentado? ¿Cómo las he superado?
c. ¿Qué he aprendido? ¿Cómo se relaciona con mi contexto?
d. ¿Cómo he contribuido al progreso del grupo?
e. ¿Qué habilidades sociales he puesto en práctica?

No es un resumen técnico de contenido (eso ya está en los apuntes de cada semana) — es una reflexión personal y autocrítica sobre el propio proceso de aprendizaje, con diálogo hacia experiencias propias.

## Checklist contra la rúbrica

- [ ] Formato: documento organizado, con índice, márgenes, interlineado consistente, un "titular" por entrada (10 pts)
- [ ] Redacción: sin errores gramaticales/ortográficos, lenguaje comprensible (10 pts)
- [ ] Esfuerzo y regularidad: entradas quincenales puntuales, mínimo 8 en total (10 pts)
- [ ] Apropiación de aprendizaje: reflexión autocrítica real, no genérica (30 pts — el criterio de mayor peso)
- [ ] Búsqueda de información complementaria: citas/referencias de calidad cuando aplique (20 pts)
- [ ] Apoyo visual: imágenes, diagramas, capturas, etc. (15 pts)
- [ ] Accesibilidad: publicado y accesible para profesora y compañeros (5 pts)
- [ ] Enlace publicado en TEC-Digital antes de semana 6

## Formato por entrada (machote)

### Entrada {N} — Semanas {X}-{Y}: {título/"titular" de la entrada}

**a. ¿Qué he hecho? ¿Qué pasos he seguido?**

**b. ¿Cuáles dificultades se han presentado? ¿Cómo las he superado?**

**c. ¿Qué he aprendido? ¿Cómo se relaciona con mi contexto?**

**d. ¿Cómo he contribuido al progreso del grupo?**

**e. ¿Qué habilidades sociales he puesto en práctica?**

> **Nota (2026-08-15):** las partes de contenido de curso (no de proyecto/equipo) de la Entrada 1 de abajo se reutilizaron, divididas por semana, en el [[Cursos/QA/entregables/diario-aprendizaje-semanal|Diario de Aprendizaje Semanal]] — fue una confusión inicial entre ambos documentos. Esta entrada de acá sigue siendo válida para este diario (queda para cuando arranque el proyecto), no se borró nada.

## Entrada 1 — Semanas 1-2: Fundamentos de calidad y arranque del proyecto

**a. ¿Qué he hecho? ¿Qué pasos he seguido?**

En estas dos semanas estudié qué es la calidad y el aseguramiento de la calidad: vimos cómo ha evolucionado el concepto tanto en la vida cotidiana como en el software, las distintas visiones de autores como Crosby, Juran, Deming e Ishikawa, y el estándar ISO 9000. También vimos específicamente qué es el control de calidad, su diferencia con el aseguramiento (el control se enfoca en el producto, el aseguramiento en el proceso), las 4 funciones del control de calidad (reportes, pruebas, auditoría, monitoreo), y varios casos reales de fallas de software (Boeing 737 MAX, Therac-25, Knight Capital, entre otros) que muestran la importancia de tener un buen proceso de calidad. Además, hicimos actividades prácticas en clase como la de "¿qué tiene más calidad?" y la torre de globos, que ayudan a aplicar estos conceptos de forma más concreta.

Del lado del proyecto, ya formamos el equipo de trabajo y elegimos el repositorio de GitHub sobre el que vamos a trabajar: Firefly III, un gestor de finanzas personales open source. Ya empecé a mapear sus módulos principales y a armar un primer borrador del Plan del proyecto (Fase 1) con los objetivos y requerimientos que se derivan de ese mapeo.

**b. ¿Cuáles dificultades se han presentado? ¿Cómo las he superado?**

La principal dificultad fue encontrar un repositorio de GitHub que cumpliera con todos los requisitos del curso (mantenimiento activo, login/autenticación, issues activos, buenas prácticas, etc.) sin quedar en algo demasiado grande o pesado de levantar localmente para el tiempo que tenemos. La superamos evaluando varios candidatos contra los criterios uno por uno en vez de guiarnos solo por popularidad, y terminamos decidiéndonos por uno con un alcance más manejable. En cuanto al contenido del curso, hasta ahora todo ha estado relativamente fácil; el reto más que nada es acostumbrarme a estudiar todas las semanas de forma constante.

**c. ¿Qué he aprendido? ¿Cómo se relaciona con mi contexto?**

He aprendido qué es calidad, control de calidad y aseguramiento de la calidad, su historia, sus procesos y sus beneficios. En mis proyectos personales y universitarios ya venía aplicando algo de aseguramiento de la calidad en cada etapa del proceso, pero no había pensado en el control de calidad desde el diseño — siempre esperaba a que una funcionalidad estuviera terminada para recién ahí hacerle QA. Aplicar bien el control de calidad desde antes puede ser interesante y me puede ahorrar tiempo de desarrollo más adelante.

**d. ¿Cómo he contribuido al progreso del grupo?**

Investigué y evalué candidatos de repositorio contra los 9 criterios del curso, armé una comparación con la información encontrada (estrellas, actividad, stack, facilidad de instalación) y se la compartí al equipo para apoyar la decisión final. Ya elegido el repositorio, adelanté el mapeo de sus módulos y un primer borrador del Plan del proyecto para que el equipo tenga un punto de partida que revisar en vez de empezar desde cero.

**e. ¿Qué habilidades sociales he puesto en práctica?**

Comunicación con el equipo para coordinar la búsqueda y decisión del repositorio, y capacidad de síntesis para presentarles la comparación de candidatos de forma que la decisión fuera fácil de tomar en grupo.

## Pendiente

- [x] Respuestas reales de Marcos a las 5 preguntas de la Entrada 1 — actualizadas 2026-08-17 con la decisión de repositorio (Firefly III)
- [ ] Elegir la plataforma donde se va a publicar el diario (debe ser accesible para profesora y compañeros)
- [ ] Publicar el enlace en TEC-Digital antes de semana 6
- [ ] Confirmar si la evaluación entre pares del Informe de pruebas también aplica al Diario (la guía no lo aclara — parece que no)
- [ ] Confirmar con la profesora/TEC-Digital la fecha real de la primera entrada, ya que depende de que arranque el proyecto (ver corrección arriba)
