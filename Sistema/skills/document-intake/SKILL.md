---
name: document-intake
description: Use this skill whenever a new document (PDF, DOCX, image of notes/slides) shows up in Sistema/inbox/ — dropped there directly by the user or relayed by Hermes from Telegram — and needs to become a structured note inside /Cursos/{curso}/. Also read this before telling Hermes how to relay documents, since it defines the shared filename convention, storage rules, and frontmatter schema both systems rely on.
---

# Document intake — de PDF/doc suelto a nota estructurada del curso

Objetivo: cualquier documento que entra al sistema (por el usuario en Claude Code, o por Hermes desde Telegram) sigue **la misma convención de nombre y termina en el mismo lugar**, para que después se pueda buscar de forma confiable — ya sea yo leyendo el vault o Hermes contestando "¿qué tengo de X tema?" desde el celular.

## 1. Zona de entrada única

`Sistema/inbox/` es el único punto de entrada para documentos crudos (PDF, DOCX, fotos de pizarra/apuntes). Nadie escribe directo a `/Cursos/{curso}/apuntes/` sin pasar por acá primero.

## 2. Convención de nombre (obligatoria)

```
{Curso}_{tema-en-kebab-case}_{YYYY-MM-DD}.{ext}
```

- `{Curso}` — debe coincidir EXACTO con el nombre de carpeta en `/Cursos/`: `Estadistica`, `DesarrolloWeb`, `CompuYSociedad`, `SistemasOperativos`, `QA`, `Seguridad`, `Seminario`. Si el curso no existe todavía como carpeta, preguntar antes de inventar una.
- `{tema-en-kebab-case}` — minúsculas, sin tildes, espacios reemplazados por guiones. Ej: `criptografia-simetrica`.
- `{YYYY-MM-DD}` — fecha en que se recibe el documento (no la fecha de la clase, salvo que el usuario la especifique).

Ejemplo: `Seguridad_criptografia-simetrica_2026-08-07.pdf`

Esta convención es la que el usuario usa al soltar un archivo manualmente, y la misma que Hermes debe aplicar al renombrar lo que recibe por Telegram antes de subirlo.

## 3. Qué hace Claude Code cuando encuentra algo en `Sistema/inbox/`

1. Leer el documento y el nombre de archivo para identificar curso y tema.
2. Buscar primero si ya existe una nota relacionada en `Cursos/{curso}/apuntes/` o `examenes/` (regla general del vault: no duplicar).
3. Decidir destino: `apuntes/` (contenido de estudio general) vs `examenes/` (material específico de examen) según el contenido, no según la carpeta de origen.
4. Extraer y estructurar el contenido en un `.md` limpio (aplicar `professional-technical-docs` para el estilo de escritura), con el frontmatter del punto 4.
5. Archivar el original: moverlo a `Cursos/{curso}/_fuentes/{nombre-original}` (nunca se borra, regla general del vault — carpeta con prefijo `_` igual que `_archivo/`).
6. Commit siguiendo `gitflow-scrum`: `docs({CURSO-CODE}-n): agregar apuntes de {tema}` — un commit por documento procesado, no bundlear varios.
7. Si el PDF pesa más de ~50MB, avisar al usuario antes de commitear (podría necesitar compresión o tratamiento aparte) en vez de subirlo sin más.

## 4. Frontmatter estándar en los `.md` generados

```yaml
---
curso: Seguridad
tema: Criptografía Simétrica
fecha: 2026-08-07
tipo: apunte # o "examen"
fuente: _fuentes/Seguridad_criptografia-simetrica_2026-08-07.pdf
tags: [criptografia, seguridad]
---
```

Este frontmatter es lo que permite buscar/filtrar después, tanto a mí como a Hermes (vía la API de GitHub, filtrando por curso/tema/tags en vez de tener que leer todo el vault).

## 5. Qué hace Hermes (spec para pasarle tal cual)

Hermes **no genera el `.md` final** — eso lo hace Claude Code en la siguiente sesión. El rol de Hermes es solo relay, de bajo riesgo:

1. Recibe el archivo por Telegram junto con curso/tema (preguntarle al usuario si no los dio).
2. Lo renombra siguiendo la convención del punto 2.
3. Lo sube directo a `Sistema/inbox/{nombre-convención}` vía la API de GitHub (no clona el repo), en un commit o PR según ya tenga configurado.
4. **Borra el archivo temporal local inmediatamente después de confirmar el push** — la Pi no tiene espacio para acumular archivos, así que nunca debe quedar un documento sin subir "por si acaso".
5. Confirma al usuario: `"📄 Subido a inbox: Seguridad_criptografia-simetrica_2026-08-07.pdf ✅ — Claude Code lo procesa en la próxima sesión."`

## 6. Reglas generales

- Nunca borrar el original — se archiva en `_fuentes/`, igual que las notas obsoletas van a `_archivo/`.
- Un documento = un commit, con código de ticket del curso (`SEG`, `QA`, `WEB`, etc., mismo criterio de `gitflow-scrum`).
- Si el mismo tema ya tiene nota, actualizar esa nota en vez de crear una duplicada — anexar la fuente nueva al frontmatter si aporta algo distinto.
