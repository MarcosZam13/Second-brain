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

### 2.1. Archivo de contexto acompañante (cuando hay algo que decir más allá de curso/tema)

El nombre de archivo solo transporta curso+tema+fecha. Si el usuario le da a Hermes por Telegram **instrucciones o contexto adicional** al subir un documento — "esto ya está escrito, solo archivalo tal cual", "el segundo PDF es de Seguridad, el tercero de QA", "esto reemplaza la nota vieja de tal tema", "es un borrador, no lo proceses como apunte del profesor" — ese contexto se pierde en cuanto termina la conversación de Telegram, porque quien procesa el inbox después (yo en una sesión, o la Claude Code Routine que corre sola cada 6h) no tiene memoria de ese chat.

Por eso: cuando Hermes reciba contexto que no sea simplemente "este es el curso/tema", debe escribirlo en un archivo de texto acompañante, mismo nombre base que el documento, extensión `.contexto.txt`:

```
Seguridad_criptografia-simetrica_2026-08-07.pdf
Seguridad_criptografia-simetrica_2026-08-07.contexto.txt   ← solo si hubo algo que decir
```

Contenido: el texto tal cual lo escribió el usuario (o un resumen fiel si vino por audio/transcripción), sin reformatear. Si no hay nada más allá de curso/tema, **no crear el archivo** — no generar ruido innecesario en el inbox.

Quien procese el documento (yo o la Routine) debe buscar y leer este archivo antes de clasificar, y borrarlo junto con el original al archivar (no queda huérfano en el inbox, y su contenido relevante debe reflejarse en el frontmatter/cuerpo de la nota resultante o en la decisión tomada).

Para varios documentos subidos juntos en un mismo mensaje de Telegram (ej. 5 archivos de 5 cursos distintos): cada uno debe llevar su propio nombre con curso/tema correcto — eso ya alcanza para distinguirlos sin necesidad de `.contexto.txt`, salvo que además haya alguna instrucción especial sobre alguno de ellos en particular.

## 3. Qué hace Claude Code cuando encuentra algo en `Sistema/inbox/`

1. Leer el documento y el nombre de archivo para identificar curso y tema. Buscar si existe un archivo `{mismo-nombre}.contexto.txt` junto al documento (ver punto 2.1) y leerlo antes de seguir — puede cambiar cómo se clasifica o procesa el documento.
2. Buscar primero si ya existe una nota relacionada en `Cursos/{curso}/apuntes/` o `examenes/` (regla general del vault: no duplicar).
3. Decidir destino: `apuntes/` (contenido de estudio general) vs `examenes/` (material específico de examen) según el contenido, no según la carpeta de origen.
4. Extraer y estructurar el contenido en un `.md` limpio (aplicar `professional-technical-docs` para el estilo de escritura), con el frontmatter del punto 4.
5. Enlazar la nota con `[[wikilinks]]` — no es para que Hermes busque mejor (busca por contenido/embeddings vía ChromaDB, no camina el grafo), es para orden y navegación en Obsidian:
   - Siempre enlazar a `temario.md` y `entregas.md` del mismo curso.
   - Usar el path completo desde la raíz del vault (`[[Cursos/{curso}/temario]]`, `[[Cursos/{curso}/entregas]]`) — `temario.md`/`entregas.md` se repiten en cada curso, así que el nombre corto sería ambiguo.
   - Si el tema se cruza con otra nota ya existente (mismo concepto en otro curso, o una nota previa del mismo curso), enlazarla también.
6. Archivar el original: moverlo a `Cursos/{curso}/_fuentes/{nombre-original}` (nunca se borra, regla general del vault — carpeta con prefijo `_` igual que `_archivo/`).
7. Commit siguiendo `gitflow-scrum`: `docs({CURSO-CODE}-n): agregar apuntes de {tema}` — un commit por documento procesado, no bundlear varios. El código de ticket sale de `Sistema/tickets.md` (nunca inventar uno mirando el log); actualizar ahí el "Último usado" en el mismo commit. Excepción: cuando varios documentos alimentan exclusivamente los mismos `temario.md`/`entregas.md` del curso (ej. programa + cronograma subidos juntos), está bien agruparlos en un solo commit — el criterio es "un commit por unidad de contenido resultante", no literalmente un PDF por commit.
8. Si el PDF pesa más de ~50MB, avisar al usuario antes de commitear (podría necesitar compresión o tratamiento aparte) en vez de subirlo sin más.
9. **Documentos casi-duplicados → una sola nota.** Si varios PDFs del mismo lote comparten formato y estructura casi idénticos y solo cambia el contenido puntual (ej. tres "reportes audiovisuales" con la misma rúbrica pero distinto documental/preguntas cada uno), no crear un `.md` por PDF — combinarlos en una sola nota con una sección por documento, y un solo `fuente:` en el frontmatter como lista (YAML array) apuntando a los PDFs archivados. Esto evita repetir la misma rúbrica/estructura 3 veces y mantiene el principio de "no duplicar" del vault. Señal para aplicar esto: si al escribir la segunda nota estás copiando la mayoría de la estructura de la primera, parar y fusionar.

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

Cuando una nota se arma a partir de más de un PDF (varios documentos combinados por el punto 9, o un `temario.md`/`entregas.md` alimentado por programa+cronograma), `fuente:` es una lista YAML en vez de un string único:

```yaml
fuente:
  - _fuentes/Seguridad_reporte-1_2026-08-07.pdf
  - _fuentes/Seguridad_reporte-2_2026-08-07.pdf
```

## 5. Qué hace Hermes (spec para pasarle tal cual)

Hermes **no genera el `.md` final** — eso lo hace Claude Code en la siguiente sesión. El rol de Hermes es solo relay, de bajo riesgo:

1. Recibe el archivo por Telegram junto con curso/tema (preguntarle al usuario si no los dio).
2. Lo renombra siguiendo la convención del punto 2.
3. Lo sube directo a `Sistema/inbox/{nombre-convención}` vía la API de GitHub (Contents API), **no** haciendo `git add`/`commit` del PDF en el clon local — así el blob del archivo nunca ocupa espacio en la Pi, solo transita por HTTP.
4. Si el usuario dio algo más que curso/tema (instrucciones, aclaraciones, "esto reemplaza tal nota", etc.), subir también `{nombre-convención}.contexto.txt` con ese texto, por la misma API de Contents (mismo criterio que el PDF: no toca disco más de lo necesario, es un string corto). Ver punto 2.1 del skill de `document-intake` — no crear este archivo si no hay nada que decir más allá de curso/tema.
5. **Borra el archivo temporal local inmediatamente después de confirmar el upload** — la Pi tiene muy poco espacio libre, así que nunca debe quedar un documento sin subir "por si acaso".
6. Confirma al usuario: `"📄 Subido a inbox: Seguridad_criptografia-simetrica_2026-08-07.pdf ✅ — Claude Code lo procesa en la próxima sesión."` (agregar "con contexto ✅" si también subió el `.contexto.txt`).

## 6. El clon local de Hermes en la Pi

Hermes sí mantiene un clon local del repo (para leer notas y responder preguntas), separado de la subida de PDFs del punto anterior. Para que ese clon no crezca sin control con el archivo de fuentes:

- Configurar `git sparse-checkout` (modo `--no-cone`) excluyendo `Cursos/*/_fuentes/` — Hermes no necesita los PDFs originales localmente, solo el texto de `apuntes/`, `entregas.md`, `temario.md`, etc.
- Preferir un clon shallow (`--depth 1`) ya que Hermes no necesita historial, solo el estado actual.
- `git pull` normal alcanza para mantenerlo al día; no requiere traer los PDFs archivados aunque el repo remoto los tenga.

## 7. Reglas generales

- Nunca borrar el original — se archiva en `_fuentes/`, igual que las notas obsoletas van a `_archivo/`.
- Un documento = un commit, con código de ticket del curso (`SEG`, `QA`, `WEB`, etc., mismo criterio de `gitflow-scrum`).
- Si el mismo tema ya tiene nota, actualizar esa nota en vez de crear una duplicada — anexar la fuente nueva al frontmatter si aporta algo distinto.
