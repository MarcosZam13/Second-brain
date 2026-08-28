# DojoBase

Ver también: [[Proyectos/README|Proyectos]] · [[Proyectos/MemberBase/README|MemberBase (plataforma)]] · [[Proyectos/MemberBase/revision-critica-specs|Revisión crítica de los specs]] · [[Proyectos/GymBase/README|GymBase]]

**App:** `apps/dojobase` dentro del monorepo [[Proyectos/MemberBase/README|MemberBase]].
**Estado:** specs cerrados y revisados (2026-08-28). Pendientes 7 decisiones antes de escribir la primera migración.
**Primer cliente:** Dojo Shoto — **ya en producción sobre GymBase v1**, con 4 disciplinas (karate, BJJ, MMA, krav magá). Esto hace que DojoBase sea una *migración de un cliente vivo*, no un lanzamiento desde cero (ver A1 de la revisión crítica).

## Qué es

SaaS multi-tenant para academias de artes marciales. Multi-disciplina con rango independiente por arte, clases con asistencia por inscripción, retos de sparring amistoso con resultado por rounds e historial head-to-head, promociones de cinturón con rúbrica, historial de peleas oficiales con feed de "próximas peleas", contenido por carpetas, challenges, y cobro de membresías con comprobante SINPE.

23 historias de usuario, 22 RF, 6 RNF — detalle en `_fuentes/06-historias-usuario-requerimientos.md`.

## El objetivo de negocio real

Dojo Shoto ya tiene todo esto funcionando en GymBase v1. Lo que **no** se puede hacer hoy y es lo que vuelve el producto vendible: onboardear un dojo nuevo sin un deploy ni un PR (hoy cada cliente es una carpeta `clients/gymbase/<tenant>/` + un build con `NEXT_PUBLIC_GYM_CLIENT`).

Por eso el producto mínimo vendible es:

1. Resolución de tenant en runtime vía JWT claim (spec 3) — hoy es un header custom resuelto contra `.gymbase.app` hardcodeado.
2. `tenant_themes` en tabla (spec 4) — onboardear pasa de un deploy a un insert.
3. Alta de organización + invitación de miembros (HU-22, RF-19/20) — hoy manual, y ni siquiera está en el schema.

Todo lo demás (sparring, promociones, peleas, contenido) ya existe en GymBase y es **porte con limpieza**, no diseño nuevo.

## Dónde está cada cosa

- `_fuentes/06-historias-usuario-requerimientos.md` — documento de requerimientos con el formato de Tacha: resumen ejecutivo, alcance, 23 HU, RF/RNF, decisiones técnicas.
- `_fuentes/07-agentes-cronograma.md` — modelo de 1 orquestador + 4 subagentes (UI, QA, seguridad OWASP, documentación) y cronograma de 8 semanas.
- `_fuentes/08b-identidad-marca-vs-theming.md` — separación entre la identidad de marca de DojoBase (landing, paleta fija void/crimson/amber/paper, Anton + Space Grotesk) y el theming dinámico por tenant (colores del dojo). Incluye qué cruza de la landing a la app y con qué reglas.
- `_fuentes/09-prompt-kickoff-semana1-core.md` — prompt de arranque de la semana 1 (subagentes + CoreBase).

## Pendiente de armar

- **`DESIGN.md`** — el equivalente al de [[Proyectos/Tacha/DESIGN|Tacha]]: personalidad, navegación por rol (miembro / admin / owner), inventario de pantallas mapeado a HU, estados vacíos/carga/error y prompt por pantalla. Es el artefacto que falta para que "mejorar la UI" no termine siendo improvisación pantalla por pantalla (ver F de la revisión crítica).
- **`documentacion-v1.md` y `historias-usuario.md`** curados — hoy viven mezclados en el spec 06; conviene separarlos como en Tacha (documento de proyecto vs. HU/CA numeradas) una vez cerradas las 7 decisiones, porque varias las cambian.
- **Cierre de schema contra HU** — el spec 2 cubre ~70% de lo que las HU exigen (ver C de la revisión crítica).
- **Plan de migración de datos de Dojo Shoto** — no existe en ningún spec y es bloqueante del corte.

## Ticket prefix

`DOJO`. Ver [[Sistema/tickets|tickets.md]] y [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]].
