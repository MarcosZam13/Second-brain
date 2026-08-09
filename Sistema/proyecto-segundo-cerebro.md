# Segundo Cerebro + Hermes
### Sistema personal de organización académica, proyectos y workflow de desarrollo

Ver también: [[Sistema/CLAUDE|CLAUDE.md (reglas de navegación)]] · [[Sistema/tickets|Registro de tickets]] · [[Sistema/skills/document-intake/SKILL|document-intake]] · [[Dashboard]]

---

## 1. El problema

Información repartida sin punto central: temarios de 7 cursos, fechas de entrega, documentación de GymBase/Tacha/CaneleApp, estilo de código y de escritura que hay que re-explicar cada vez. No hay fricción para *guardar* (uso Claude, notas sueltas), pero sí para *encontrar* y para *actuar* (recordar entregas, aplicar mi propio estilo sin reinventarlo).

**Principio de diseño (2026):** un segundo cerebro dejó de ser un archivo que se busca — es una base de conocimiento que un agente **consulta y sobre la que escribe**. Si el agente no puede escribir de vuelta (tareas creadas, notas archivadas, fechas sincronizadas), es solo un archivo caro. Eso define toda la arquitectura de abajo.

---

## 2. Arquitectura general — 3 niveles de acceso

Un malentendido común (y que vale la pena tener clarísimo): **esto no es un solo "agente" corriendo siempre.** Son tres niveles distintos, cada uno activo en momentos distintos:

| Nivel | Cuándo está activo | Qué puede hacer |
|---|---|---|
| **Claude Code** (tu compu) | Solo cuando vos abrís la carpeta del vault | Lee/escribe el vault completo, aplica skills, programa, hace commits/PRs reales, orquesta subagentes |
| **Claude app** (celular/web) | Cuando querés, sin Hermes | Ve GitHub/Calendario/Todoist vía MCP y responde — pero NO tiene el vault como contexto local a menos que se lo pegués |
| **Hermes** (Telegram, corre 24/7 en la Pi) | Siempre disponible | Captura rápida, clasifica, toca Todoist/Calendario directo para cosas simples, prepara PRs al vault para que Claude Code los revise |

```
┌─────────────────────────────────────────────────────────────┐
│                         CAPTURA                              │
│  Hermes (Raspberry Pi, Telegram) — corre 24/7                │
│  → disponible siempre, sin necesitar la compu                │
│  → recibe texto/archivos, clasifica, escribe tareas simples   │
│    directo a Todoist/Calendario, prepara PR para el vault     │
└───────────────────────┬───────────────────────────────────────┘
                         │ abre PR (no escribe directo)
                         ▼
┌─────────────────────────────────────────────────────────────┐
│                    VAULT (fuente de verdad)                  │
│  Obsidian + Git, estructurado por curso/proyecto              │
│  /Cursos/{QA,Seguridad,Seminario,CompuYSociedad,              │
│           DesarrolloWeb,Estadistica,SO}/                      │
│  /Proyectos/{GymBase,Tacha,CaneleApp}/                        │
│  /Sistema/CLAUDE.md, /Sistema/skills/                         │
└───────────────────────┬───────────────────────────────────────┘
                         │ lee/revisa/mergea PRs/organiza
                         ▼
┌─────────────────────────────────────────────────────────────┐
│                  CEREBRO PRINCIPAL                            │
│  Claude Code (tu compu, solo cuando lo abrís)                 │
│  Usa skills propios + MCP (GitHub, Calendar, Todoist)          │
│  Revisa y mergea lo que dejó Hermes, programa, documenta,      │
│  orquesta subagentes para tareas grandes                       │
└─────────────────────────────────────────────────────────────┘
```

**Por qué separar Hermes de Claude Code:** no siempre vas a tener la compu a mano, pero sí el celular. Hermes no necesita ser potente — solo necesita *no perder nada* y dejarlo bien clasificado para que el cerebro principal lo procese después. Esto evita el error típico de querer meterle demasiada inteligencia a la parte de captura.

**Por qué Hermes abre PR en vez de escribir directo al vault:** un modelo barato clasificando en caliente se va a equivocar de vez en cuando. El PR es el checkpoint — Claude Code (o vos manualmente en GitHub) lo revisa antes de que entre "sucio" a la fuente de verdad.

---

## 3. Hermes — especificación

**Rol:** agente ligero de captura, corriendo 24/7 en la Raspberry Pi (ya tenés la Pi 4 configurada de COMPDES, mismo patrón que usaste con OpenClaw).

**Interfaz:** bot de Telegram (más simple de armar que WhatsApp Business API, sin costos ni aprobación de Meta). Le escribís texto o audio en cualquier momento.

**Qué SÍ hace:**
- Recibe texto, audio o **archivos** (apuntes, PDFs de un curso, fotos de pizarra) por Telegram.
- Responde preguntas puntuales sobre un curso o proyecto usando el vault como contexto (lectura directa, sin necesitar PR).
- Clasifica con un modelo barato (GPT-4.1 mini u otro vía OpenRouter, como ya hiciste en el taller) a qué carpeta del vault pertenece: curso, proyecto, o "inbox" si no está claro.
- Para información nueva que se agrega al vault (apuntes, decisiones de proyecto): **abre un PR**, nunca escribe directo — queda pendiente de revisión por Claude Code.
- Para tareas simples y fechas: escribe **directo** a Todoist/Calendario (esto no necesita revisión, es de bajo riesgo y alta frecuencia).
- Responde "¿qué tengo pendiente?" leyendo Todoist/Calendario en el momento.
- Confirma cada acción con un mensaje corto: "PR abierto: Seguridad/apuntes-unidad3 ✅" o "Tarea creada en Todoist ✅".
- Si el usuario da contexto/instrucciones más allá de curso+tema al subir un documento, lo sube como archivo `.contexto.txt` acompañante junto al documento — necesario porque ahora el procesamiento del inbox lo puede hacer una Claude Code Routine que corre horas después, sin memoria de la conversación de Telegram (ver punto 2.1 de `Sistema/skills/document-intake/SKILL.md` para el detalle exacto).

**Qué NO hace (a propósito):**
- No razona profundo, no genera código, no escribe documentación larga. Eso es trabajo de Claude Code cuando te sentás a la compu.
- No mergea sus propios PRs — eso lo aprueba Claude Code (o vos) en la siguiente sesión.
- No reemplaza el vault — es solo la puerta de entrada.

**Stack sugerido:** [Hermes Agent](https://github.com) (framework de Nous Research, Python, self-improving skills + memoria episódica vía ChromaDB) en vez de armarlo desde cero o usar OpenClaw. Decisión tomada tras comparar ambos — ver nota abajo. Corre como servicio en la Pi, con conexiones directas a Telegram, GitHub API, Todoist API y Google Calendar API (no hereda los MCP de Claude.ai — ver sección de conexiones de Hermes).

> **Por qué Hermes Agent y no OpenClaw:** Hermes tiene skills auto-mejorables (encaja directo con el sistema de skills del vault), memoria episódica con retrieval semántico (ideal para buscar capturas pasadas por significado), es Python-nativo (mismo stack que el resto del proyecto), model-agnostic, y open source MIT. OpenClaw gana en comunidad/ecosistema de plugins, pero eso no es relevante para un agente personal chico y enfocado como este. Si el proyecto se convierte en producto (StudyBase) más adelante, ahí sí vale la pena reevaluar OpenClaw por su ecosistema.

---

## 4. El vault (Obsidian + Git)

Estructura base:

```
/Cursos/
  QA/temario.md, entregas.md, apuntes/, examenes/
  Seguridad/...
  Seminario/...
  CompuYSociedad/...
  DesarrolloWeb/...
  Estadistica/...
  SistemasOperativos/...
/Proyectos/
  GymBase/  (ya existe, se integra)
  Tacha/
  CaneleApp/
/Sistema/
  CLAUDE.md          ← cómo navegar todo esto
  skills/
  inbox/             ← lo que cae de Hermes sin clasificar del todo
```

Cada `curso/entregas.md` tiene fechas parseadas del syllabus. Un skill se encarga de sincronizarlas al calendario cuando se lo pedís explícitamente ("sincronizá las entregas de Seguridad").

---

## 5. Skills para Claude Code (tu estilo, reusable en todo)

Estos son los que arman tu "librería de agentes". Cada uno vive en `/Sistema/skills/` dentro del vault y se arma con el `skill-creator`.

| Skill | Qué resuelve | Estado |
|---|---|---|
| `clean-code-practices` | Naming, diseño de funciones, cuándo usar patrones de diseño, estructura de repo escalable, en inglés | ✅ Hecho |
| `gitflow-scrum` | Branches/commits/PRs con código de ticket, trazabilidad completa requerimiento → código | ✅ Hecho |
| `enterprise-ui-ux-design` | Buen diseño visual, cómo evitar la estética genérica de IA, principios de UX a nivel empresa | ✅ Hecho |
| `qa-testing-practices` | Test cases, bug reports y test plans estilo empresa | ✅ Hecho |
| `professional-technical-docs` | READMEs, docs de arquitectura y comentarios que no "suenan a IA" | ✅ Hecho |
| `course-study-helper` | Responde/quiz sobre el material de un curso específico, sin mezclar cursos | ✅ Hecho |
| `document-intake` | Convierte PDFs/docs sueltos (míos o subidos por Hermes) en notas `.md` estructuradas, con convención de nombre y frontmatter compartido para búsqueda | ✅ Hecho |
| `proyecto-{nombre}` | Contexto aislado por proyecto para no mezclar stacks (GymBase ≠ Tacha ≠ CaneleApp) | Pendiente — se arma cuando se cargue contenido real |

**Orquestación (subagentes):** en `/Sistema/agents/` hay 3 plantillas de subagentes listas para copiar a `.claude/agents/` en cualquier repo de proyecto:

| Subagente | Aplica el skill | Cuándo se usa |
|---|---|---|
| `code-reviewer` | `clean-code-practices` + `gitflow-scrum` | Antes de abrir un PR |
| `qa-checker` | `qa-testing-practices` | Verificar cobertura de test cases antes de merge |
| `docs-writer` | `professional-technical-docs` | Después de mergear una feature |

Es nativo de Claude Code (no necesita OpenCode ni herramientas externas) — se definen como archivos Markdown con frontmatter, y Claude Code los invoca solo o a pedido ("revisá esto con code-reviewer, qa-checker y docs-writer").

---

## 6. Gitflow del curso — qué dice la evidencia 2026

Lo que encontré, resumido:

- **GitFlow clásico** (main/develop/feature/release/hotfix) tiene sentido para software versionado con releases programados y equipos grandes — pero para un equipo chico (1-5 personas) o un proyecto universitario, la mayoría de guías 2026 coinciden en que es **más ceremonia de la que se necesita**, y las ramas de larga duración generan más conflictos, no menos.
- **Trunk-Based Development / GitHub Flow** (rama principal + ramas cortas de 1-2 días, PRs frecuentes) es lo que dominan equipos ágiles chicos y proyectos nuevos en 2026, siempre que haya CI decente.
- Punto de consenso: **no es una decisión técnica, es una decisión de cultura de release** — cuánto confiás en tus tests y tu pipeline determina si podés vivir con ramas cortas.

**Recomendación práctica para vos:** si el profesor pide Gitflow completo, seguilo tal cual para la nota — pero podés *documentar* en tu propio repo (y en el skill `gitflow-web`) una versión mejorada:
- Ramas `feature/*` con vida máxima de 1-2 días (no dejarlas creciendo).
- Commits semánticos (`feat:`, `fix:`, `docs:`) — esto además te sirve para automatizar changelogs con Claude Code.
- PR obligatorio hacia `develop` aunque estés solo, para que Claude Code pueda revisar antes de mergear.
- Si el proyecto real de la clase termina siendo continuo (como Tacha o GymBase), proponé migrar a GitHub Flow después de la entrega — es defendible con las fuentes que ya tenés.

Esto también te da contenido real para el "cómo mejorarlo" que pide el profesor, con argumentos de la industria y no solo intuición.

---

## 7. Herramientas y costos

| Pieza | Herramienta | Costo |
|---|---|---|
| Vault | Obsidian | Gratis |
| Versionado del vault | Git + GitHub (repo privado) | Gratis |
| Cerebro principal | Claude Code | Incluido en plan Pro ($20/mes) que ya tenés |
| Tareas | Todoist (MCP) | ✅ Conectado — plan gratis alcanza para uso personal |
| Calendario | MCP de Google Calendar | Pendiente de conectar — gratis |
| Hermes | Telegram Bot API + Python en la Pi | Gratis |
| Clasificación en Hermes | API de Anthropic o OpenRouter (modelo barato) | Centavos al mes |
| Hosting Hermes | Raspberry Pi (ya la tenés) | $0 adicional |

Todo el sistema corre prácticamente gratis además de la suscripción de Claude que ya pagás.

---

## 8. Roadmap

| Fase | Qué se arma | Estado |
|---|---|---|
| 1 | Estructura del vault + `CLAUDE.md` raíz | ✅ Hecho |
| 1 | Skills `clean-code-practices` + `gitflow-scrum` | ✅ Hecho |
| 1 | Conectar Todoist (MCP) | ✅ Hecho y probado (lectura + escritura) |
| 2 | Conectar Google Calendar (MCP) | ✅ Hecho y probado (creación de evento) |
| 2 | Skills `enterprise-ui-ux-design`, `qa-testing-practices`, `professional-technical-docs`, `course-study-helper` | ✅ Hecho |
| 2 | Subagentes de orquestación (`code-reviewer`, `qa-checker`, `docs-writer`) | ✅ Hecho |
| 3 | Decisión de framework para Hermes (Hermes Agent vs OpenClaw) | ✅ Decidido — Hermes Agent |
| 3 | Setup real de Hermes en la Raspberry Pi | ✅ Hecho (2026-08-07) — corriendo 24/7, ruteo por SOUL.md + scripts fijos, modelo gpt-4.1-mini vía OpenRouter. Detalle completo del stack pendiente de reporte del propio Hermes |
| 4 | Cargar temarios/apuntes/fechas reales de los 7 cursos al vault | En progreso — Seminario y Estadística ya cargados |
| 4 | Automatizar `document-intake` con Claude Code Routine (`vault-inbox-intake`, cron cada 6h, sin tocar Hermes) | ✅ Hecho (2026-08-07) — revisa `Sistema/inbox/` y abre PR, nunca mergea sola. Corre 100% en la nube de Anthropic (no en la compu ni la Pi), sale del pool de uso del plan Pro. Frecuencia bajada de cada hora a cada 6h para no toparse con el tope diario de corridas de Routines (no confirmado el número exacto para Pro — revisar en claude.ai/settings/usage si hace falta ajustar) |
| 5 | Sesiones de trabajo diarias con check-in proactivo de Hermes (22:00) — ver sección 9 | 📋 Spec lista (2026-08-09) — pendiente de implementar en el repo de Hermes |
| 6 (futuro) | Evaluar si esto se convierte en producto — "StudyBase" | post-semestre |

Multiplataforma: todo lo construido (vault, Git, Claude Code, Hermes Agent) corre igual en Windows y Linux — nada queda atado a un solo sistema operativo salvo la Raspberry Pi (que ya es Linux).

---

## 9. Sesiones de trabajo diarias — diseño (pendiente de implementar)

**Problema que resuelve:** hoy no hay forma de decir "mañana quiero avanzar estos 3 entregables" y que el sistema (a) recuerde el plan, (b) registre qué se completó de verdad aunque sea parcial, y (c) empuje a cerrar el día en vez de depender de que el usuario se acuerde de reportar solo.

**Idea original del usuario (2026-08-09):** una sola tarea que, al marcarse como completada, marca en cascada las entregas reales correspondientes (cada una con su propia fecha). Si algo queda incompleto, que el sistema guarde el avance para retomarlo después preguntando "¿qué me falta de X?". Y que a las 10pm el agente pregunte proactivamente qué se completó y qué no.

**Por qué se ajustó el modelo:** la cascada "padre completo → hijos completos" no sostiene el caso de completar solo 2 de 3 — invertir la relación (hijo completo → eso es lo que se marca) es más robusto y es además el comportamiento nativo de subtareas en Todoist.

**Diseño resultante — 3 piezas, todas ya con infraestructura parcial:**

1. **Tarea de sesión con subtareas (Todoist).** Al planear el día se crea una tarea "Sesión — {fecha}" con una subtarea por cada entregable que se va a tocar (subtarea = puntero al entregable real, no lo reemplaza — el entregable real conserva su propia fecha de vencimiento). Cada subtarea se marca de forma independiente según lo que efectivamente se complete; la tarea padre nunca se auto-completa sola.
2. **Progreso parcial persistido (`Cursos/{curso}/entregables/*.md`).** Ya existe la convención (`estado: borrador`/`entregado` + checklist contra la rúbrica, ver regla 8.2 de `Sistema/CLAUDE.md`) — el hueco real es que solo se llena si el avance pasó por una sesión de Claude Code. Falta el hábito de, al cerrar una sesión (aunque quede a medias), pedir explícitamente actualizar el entregable con el estado real para que "¿qué me falta de X?" tenga algo concreto que leer.
3. **Check-in proactivo a las 22:00 (Hermes, no Claude Code).** Claude Code solo corre cuando se abre el vault, así que el ping periódico tiene que vivir en Hermes (ya corre 24/7 en la Pi con Telegram + Todoist directo). Sería un cron nuevo: a las 22:00 Hermes pregunta por Telegram qué de la sesión del día se completó, y con la respuesta marca las subtareas correspondientes en Todoist — mismo patrón de bajo riesgo que ya usa para tareas simples (ver sección 3, "Qué SÍ hace").

**Spec lista para implementar:** [[Sistema/hermes-checkin-22h-spec|hermes-checkin-22h-spec.md]] (2026-08-09) — cubre el modelo de la tarea de sesión, el flujo completo del cron de las 22:00 y qué queda por decidir con el código real de Hermes (mecanismo de scheduling, persistencia de estado conversacional corto, mapeo subtarea → entregable). Pendiente de que la sesión de Claude Code en la Raspberry Pi la implemente en el repo de Hermes — no toca este vault.

---

## 10. Por qué esto no es solo para vos

El diseño (vault versionado + agente ligero de captura + agente pesado de razonamiento + skills como "estilo empaquetado") es agnóstico a que seas vos o cualquier estudiante/dev independiente con muchos proyectos en paralelo. Es exactamente el tipo de problema que ya resolvés comercialmente (núcleo genérico + verticales). Documentarlo bien desde ahora dejaría el camino armado para ofrecerlo como plantilla o como el siguiente producto de tu línea.
