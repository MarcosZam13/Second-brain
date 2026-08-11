---
name: quiz-repaso
description: Use this skill whenever the user has an upcoming quiz/exam for a course that repeats regularly (e.g. a weekly quiz) and wants a repaso to study from. Produces two artifacts from the same content — a Markdown study note saved in the vault, and an interactive self-test HTML page published as a Claude Artifact — so the material is both durable (vault) and usable for active recall (interactive). Trigger on "ayúdame a repasar/estudiar para el quiz de X", "armame un repaso", or when course-study-helper's exam-prep mode is invoked for a recurring quiz specifically.
---

# Quiz repaso — nota de estudio + suite interactiva

Ver también: [[Sistema/skills/course-study-helper/SKILL|course-study-helper]] (scoping general de estudio) · [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] · [[Sistema/CLAUDE|CLAUDE.md]]

Nace de un pedido explícito del usuario (2026-08-10): para QA va a haber quiz todas las semanas, y quiere repetir siempre el mismo patrón en vez de reexplicarlo cada vez. Aplica a cualquier curso con evaluaciones recurrentes, no solo QA.

## Cuándo usarlo

El usuario pide ayuda para repasar/estudiar de cara a un quiz o examen de un curso — especialmente si ya se estableció que ese curso tiene evaluaciones periódicas (ej. quiz semanal). Para preguntas de estudio puntuales sin evaluación cercana, `course-study-helper` solo (sin generar los dos artefactos de este skill) puede alcanzar.

## Qué se entrega

**1. Nota `.md` en el vault** — `Cursos/{curso}/repasos/{tema-en-kebab-case}.md`

- Carpeta nueva `repasos/` dentro del curso, hermana de `apuntes/`/`entregables/`/`examenes/` — separada de `apuntes/` porque el repaso es contenido derivado/sintetizado por Claude Code, no material original del profesor.
- Frontmatter: `curso`, `tema` ("Repaso — {alcance}"), `fecha`, `tipo: repaso`, `repaso_de` (wikilink al apunte fuente), `entrega` (fecha del quiz), `tags` (heredar los del apunte fuente + `repaso`).
- Contenido: resumen denso de lo que hay que memorizar (tablas, listas — no repetir el apunte completo, solo lo accionable para repasar rápido) + una sección de autoevaluación con preguntas dentro de `<details><summary>` (Obsidian las renderiza como spoiler plegable) — misma suite de preguntas que el HTML, para que quede utilizable sin abrir el artifact.

**2. HTML interactivo publicado como Artifact**

- Antes de escribirlo, cargar el skill `artifact-design` para calibrar el tratamiento (esto es una herramienta de estudio personal — tratamiento utilitario pulido, no landing page editorial).
- Basar la identidad visual (paleta, tipografía, concepto de layout) en el contenido real del repaso, no en una plantilla genérica — buscar una metáfora propia del tema/curso en vez de reusar el mismo layout de quiz siempre. Para QA en particular ya se estableció el concepto "quiz como suite de pruebas" (casos TC-01, TC-02…, automatizados = opción múltiple, manuales = recordar-y-autocalificar, resumen tipo reporte de pruebas con tasa de PASS) — reusar ese concepto para QA, pero para otro curso hay que pensar una metáfora propia de esa disciplina en vez de copiar la de QA.
- Mezclar preguntas autocalificadas (opción múltiple con feedback inmediato) y preguntas de recordar-y-explicar (revelar respuesta, el usuario se autocalifica) — el estudio activo funciona mejor que solo releer.
- Publicar con `Artifact`, favicon de un emoji acorde al tema, `title`/`description` describiendo el repaso puntual (curso + alcance + fecha del quiz).
- No hace falta declarar `capabilities` — es una página estática con estado solo en memoria de la sesión del navegador, no necesita persistencia entre visitas.

## Flujo

1. Confirmar el curso y el alcance del quiz (qué semana/tema) si no es obvio — igual que el paso 1 de `course-study-helper`.
2. Leer el/los apunte(s) fuente en `Cursos/{curso}/apuntes/` relevantes al alcance.
3. Escribir la nota `.md` en `Cursos/{curso}/repasos/` (ver estructura arriba).
4. Diseñar y publicar el HTML interactivo con la misma suite de preguntas que la nota (ver sección de diseño arriba).
5. **Enlazar el repaso desde los dos lugares que otros sistemas consultan, no solo crearlo aislado:**
   - En `Cursos/{curso}/entregas.md`, la fila de esa entrega debe apuntar al repaso (`Cursos/{curso}/repasos/{tema}`), no al apunte fuente — `entregas.md` es el índice que Hermes y otros sistemas externos leen para "qué hay que hacer", así que si el link no se actualiza, el contenido de estudio queda invisible para ellos aunque el archivo exista.
   - En el apunte fuente (`repaso_de`), agregar un link de vuelta al repaso en su línea "Ver también" — navegación en las dos direcciones, no solo repaso → apunte.
   - Este paso se saltó la primera vez que se usó este skill (QA, Semana 1, 2026-08-10) y causó que Hermes no encontrara el repaso al preguntársele por el quiz un día antes — no repetir el error.
6. Commitear la nota `.md` + los links actualizados (el HTML vive en Claude, no en el repo) siguiendo `gitflow-scrum` — branch/PR con el código de ticket del curso (`Sistema/tickets.md`), no `VAULT` (el ticket `VAULT` es para cambios al sistema del vault mismo, como este skill).
7. Pasar el link del artifact al usuario.

## Repetición semanal

Cuando el usuario pida el repaso de la semana siguiente del mismo curso, repetir el flujo completo con el apunte nuevo — no reusar/actualizar el HTML de la semana anterior (cada semana es contenido distinto, mejor un artifact nuevo que uno mutando). Sí mantener la misma carpeta `repasos/` y el mismo criterio de nombre (`{tema-en-kebab-case}.md`, ej. `calidad-semana-2.md`).
