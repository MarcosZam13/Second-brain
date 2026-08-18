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
**Estado real (actualizado 2026-08-17):** este diario está atado a las fases del proyecto (ver [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]]). El proyecto **ya arrancó** — el equipo eligió repositorio el 2026-08-17: [firefly-iii/firefly-iii](https://github.com/firefly-iii/firefly-iii) (ver [[Cursos/QA/entregables/seleccion-repositorio-proyecto]]).

**Formato definitivo (confirmado con Marcos 2026-08-18, lo pidió el profesor):** el profesor aclaró que quiere algo **sencillo y corto — una página por apartado, contando contenido e imagen**. Se reemplazan las 5 preguntas fijas (a-e) por **3 apartados cortos con título propio** dentro de cada entrada quincenal: Semana 1, Semana 2, y Avance del proyecto. Cada apartado lleva: reflexión breve, una autocrítica real (no genérica), una referencia, y un apoyo visual. Este es el único formato válido de aquí en adelante — el formato de 5 preguntas queda archivado abajo por si hace falta consultarlo, pero no se usa para nuevas entradas.

## Formato por entrada (machote vigente)

### Entrada {N} — Semanas {X}-{Y}

#### {Emoji + título divertido} — Semana {X}

Reflexión corta (qué se enseñó/entendí) + autocrítica + referencia + apoyo visual.

#### {Emoji + título divertido} — Semana {Y}

Reflexión corta + autocrítica + referencia + apoyo visual.

#### {Emoji + título divertido} — Avance del proyecto

Qué se hizo en el proyecto + autocrítica + habilidades sociales + apoyo visual.

## Checklist contra la rúbrica

**Rúbrica confirmada 2026-08-18** (imagen recibida del profesor, archivada en `Cursos/QA/_fuentes/QA_diario-reflexivo-rubrica_2026-08-18.png` — coincide con los criterios ya listados abajo; 100 pts totales).

- [ ] Formato: documento organizado, con índice, márgenes, interlineado consistente, un "titular" por apartado (10 pts) — los 3 apartados de la Entrada 1 ya tienen título propio y son cortos (1 página c/u); falta maquetar el documento final (índice, márgenes) al exportar
- [x] Redacción: sin errores gramaticales/ortográficos, lenguaje comprensible (10 pts) — revisada, sin errores
- [~] Esfuerzo y regularidad: entradas quincenales puntuales, mínimo 8 en total (10 pts) — 1 de 8 entradas hecha (Semanas 1-2), a tiempo; se completa a medida que avanza el curso
- [x] Apropiación de aprendizaje: reflexión autocrítica real, no genérica (30 pts) — cada uno de los 3 apartados tiene su propia autocrítica corta y específica
- [x] Búsqueda de información complementaria: citas/referencias de calidad cuando aplique (20 pts) — 1 referencia real por apartado (Crosby; Leveson & Turner sobre Therac-25; comparación de candidatos del proyecto)
- [x] Apoyo visual: imágenes, diagramas, capturas, etc. (15 pts) — diagrama de evolución, tabla QA vs QC, tabla de candidatos evaluados; convertir a imagen real (no solo texto/tabla markdown) al exportar
- [ ] Accesibilidad: publicado y accesible para profesora y compañeros (5 pts) — falta elegir plataforma y publicar
- [ ] Enlace publicado en TEC-Digital antes de semana 6

## Formato por entrada (machote)

### Entrada {N} — Semanas {X}-{Y}: {título/"titular" de la entrada}

**a. ¿Qué he hecho? ¿Qué pasos he seguido?**

**b. ¿Cuáles dificultades se han presentado? ¿Cómo las he superado?**

**c. ¿Qué he aprendido? ¿Cómo se relaciona con mi contexto?**

**d. ¿Cómo he contribuido al progreso del grupo?**

**e. ¿Qué habilidades sociales he puesto en práctica?**

## Entrada 1 — Semanas 1-2

### 🧵 La calidad no es un rumor — Semana 1

Esta semana le puse nombre a algo que ya venía haciendo sin saberlo. Vimos qué es la calidad y su aseguramiento: cómo evolucionó el concepto (de lo artesanal a la mejora continua), y las visiones de Crosby, Juran, Deming, Ishikawa e ISO 9000. Resultó que ya aplicaba aseguramiento de calidad en mis proyectos, solo que de forma intuitiva, sin el marco teórico para nombrarlo o hacerlo consciente.

**Autocrítica:** mi actitud ha sido intuitiva, no deliberada — sé "hacer las cosas bien" por costumbre, pero no tengo el hábito de verificarlo contra criterios explícitos. Ni siquiera le aplico control de calidad a mi propio hábito de estudio: sigo dejando el repaso para el final de la semana.

**Referencia:** Crosby, P. B. (1979). *Quality Is Free: The Art of Making Quality Certain*. McGraw-Hill.

**Apoyo visual:**
```
Artesanal → Industrialización → Control final → Control en proceso → Control en diseño → Mejora continua
```
*Evolución del concepto de calidad (6 etapas). Convertir en infografía/imagen al exportar.*

### 💥 Cuando un bug cuesta vidas — Semana 2

Vimos control de calidad: se enfoca en el producto (el aseguramiento se enfoca en el proceso), sus 4 funciones (reportes, pruebas, auditoría, monitoreo), y casos reales como Boeing 737 MAX y Therac-25, donde un control de calidad ausente o mal diseñado costó vidas humanas, no solo dinero.

**Autocrítica:** siempre esperaba a que una funcionalidad estuviera "terminada" para recién ahí hacerle QA — un hábito reactivo que estos casos me mostraron que puede ser peligroso, no solo ineficiente. Es el mismo patrón que reconozco en mi forma de estudiar: reviso todo al final, no en el camino.

**Referencia:** Leveson, N., & Turner, C. S. (1993). An investigation of the Therac-25 accidents. *IEEE Computer, 26*(7), 18–41.

**Apoyo visual:**

| Aspecto | Control de calidad | Aseguramiento de la calidad |
|---|---|---|
| Enfoque | Producto | Proceso |
| Responsable | Una persona/rol de inspección | Todo el equipo |
| Tasa de rechazo | Se acepta un % de fallo | Se espera 0 rechazos |
| Momento | Al final (post-producción) | Desde el diseño |

### 🎯 Elegimos rival: bienvenido, Firefly III — Avance del proyecto

El equipo ya arrancó: evaluamos 3 repositorios candidatos (Documenso, Chatwoot, Firefly III) contra los 9 criterios del curso y elegimos **Firefly III**, un gestor de finanzas personales open source. Yo lideré la comparación de candidatos y después mapeé sus módulos principales contra el código fuente real (no solo el README) para dejarle al equipo una base sólida para el Plan de pruebas.

**Autocrítica:** me costó no dejarme llevar por el repo más popular (Chatwoot, con la comunidad más grande) — tuve que recordarme evaluar contra los criterios reales del curso, no contra qué se veía más "impresionante" a simple vista.

**Habilidades sociales:** comunicación con el equipo para coordinar la decisión, y capacidad de síntesis para presentar la comparación de forma que la decisión fuera fácil de tomar en grupo.

**Apoyo visual:**

| Candidato | Stack | Veredicto |
|---|---|---|
| Documenso | Next.js/TypeScript | Descartado — el equipo prefirió algo sin dependencias externas |
| Chatwoot | Rails + Vue | Descartado — stack local más pesado (Postgres + Redis + Sidekiq) |
| **Firefly III** | Laravel + Vue | **Elegido** — CRUD financiero con reglas de negocio, sin servicios externos |

## Versión anterior de la Entrada 1 (formato de 5 preguntas, archivada 2026-08-18)

> Reemplazada por los 3 apartados de arriba a pedido del profesor (formato más corto). Se conserva por si hace falta consultar el detalle original — no es el formato que se va a entregar.

<details>
<summary>Entrada 1 — formato antiguo (a-e)</summary>

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

</details>

## Pendiente

- [x] Respuestas reales de Marcos a las 5 preguntas de la Entrada 1 — actualizadas 2026-08-17 con la decisión de repositorio (Firefly III)
- [x] Reescribir Entrada 1 al formato corto de 3 apartados (Semana 1, Semana 2, Avance de proyecto) que pidió el profesor, con autocrítica/referencia/apoyo visual en cada uno (2026-08-18)
- [ ] Elegir la plataforma donde se va a publicar el diario (debe ser accesible para profesora y compañeros)
- [ ] Al exportar: agregar índice y verificar márgenes/interlineado; convertir la tabla/diagrama de cada apartado en imagen real
- [ ] Publicar el enlace en TEC-Digital antes de semana 6
- [ ] Confirmar si la evaluación entre pares del Informe de pruebas también aplica al Diario (la guía no lo aclara — parece que no)
- [ ] Confirmar con la profesora/TEC-Digital la fecha real de la primera entrada, ya que depende de que arranque el proyecto (ver corrección arriba)
