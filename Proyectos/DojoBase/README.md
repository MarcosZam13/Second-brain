# DojoBase

Ver también: [[Proyectos/README|Proyectos]] · [[Proyectos/CoreBase/README|CoreBase (plataforma)]] · [[Proyectos/CoreBase/revision-critica-specs|Revisión crítica de los specs]] · [[Proyectos/GymBase/README|GymBase]] · [[Proyectos/DojoBase-Landing/README|DojoBase Landing (proyecto separado)]]

**App:** `apps/dojobase` dentro del monorepo [[Proyectos/CoreBase/README|CoreBase]] (`corebase`).
**Estado:** specs corregidos y cerrados (2026-08-28), con las 7 decisiones aplicadas, y `DESIGN.md` v1.3 listo. En código: **DOJO-7 (disciplinas y rangos)** y **DOJO-8 (clases y asistencia)**, ambos mergeados a `main` — [PR #1](https://github.com/MarcosZam13/CoreBase/pull/1) y [PR #5](https://github.com/MarcosZam13/CoreBase/pull/5). Qué se desvió del plan: [[Proyectos/DojoBase/cierre-dojo-7|cierre-dojo-7.md]] y [[Proyectos/DojoBase/cierre-dojo-8|cierre-dojo-8.md]]. Detalle paso a paso en `corebase/ESTADO.md`. Siguiente módulo: sparring.
**Primer prospecto:** Dojo Shoto — 4 disciplinas (karate, BJJ, MMA, krav magá). **No es un cliente en operación**: GymBase v1 no está en uso y su base está vacía. DojoBase se construye para **venderle el producto terminado**, así que la demo es la venta — tiene que estar presentable, no solo funcional.

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

| Documento | Qué contiene |
|---|---|
| [[Proyectos/DojoBase/documentacion-v1\|documentacion-v1.md]] | Documento de proyecto: resumen ejecutivo, alcance, actores, RF/RNF, modelo de datos, arquitectura, dirección de diseño, plan de trabajo y decisiones técnicas |
| [[Proyectos/DojoBase/historias-usuario\|historias-usuario.md]] | 30 HU con criterios de aceptación, agrupadas en épicas por rol, con tabla de trazabilidad HU → RF |
| [[Proyectos/DojoBase/DESIGN\|DESIGN.md]] | Personalidad, tokens, navegación por rol, 48 pantallas mapeadas a HU, catálogo de componentes, estados obligatorios y prompt por pantalla |
| [[Proyectos/DojoBase/schema-dojo\|schema-dojo.md]] | Schema de la capa vertical: configuración del dojo, disciplinas, rangos, sparring, promociones, peleas oficiales, torneos. Incluye la resolución de los 11 casos borde de la lógica de promociones de v1 |
| [[Proyectos/DojoBase/repaso-gymbase\|repaso-gymbase.md]] | Repaso de los 29 módulos de GymBase v1: qué entra, qué es opcional, qué se descarta y qué faltaba. De acá salieron el cronómetro de sparring y el modelo de comunidad |
| [[Proyectos/DojoBase/cierre-dojo-7\|cierre-dojo-7.md]] | Cierre de DOJO-7 (disciplinas y rangos): qué se desvió del plan original en los 8 pasos, bugs reales encontrados, y la pasada de optimización/code review/QA final |
| [[Proyectos/DojoBase/cierre-dojo-8\|cierre-dojo-8.md]] | Cierre de DOJO-8 (clases y asistencia): primer módulo que toca la capa compartida y `packages/modules`, cinco bugs reales (el más serio: corrimiento de huso horario en series recurrentes) |
| `_fuentes/` | Specs originales sin editar: 06 (HU/requerimientos), 07 (agentes y cronograma), 08b (identidad de marca vs. theming), 09 (prompt de kickoff) |

La capa compartida (auth, tenant, billing, theming, clases, contenido, notificaciones) vive en [[Proyectos/CoreBase/README|CoreBase]] — [[Proyectos/CoreBase/schema|schema.md]] y [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]].

## Pendiente de armar

- ~~`DESIGN.md`~~ — **hecho, v1.3 (2026-08-28)**: 48 pantallas mapeadas a HU, catálogo de componentes y prompts por pantalla. Ver [[Proyectos/DojoBase/DESIGN|DESIGN.md]].
- **Análisis de complejidad y orden de sprints** — estimación por HU y dependencias, como el `analisis-complejidad-viabilidad.md` de Tacha.
- ~~Spike de Realtime~~ — **hecho y aprobado el 2026-08-28**: entrega en 227-280 ms, aislamiento entre organizaciones verificado con prueba negativa. Ver [[Proyectos/CoreBase/realtime|realtime.md]].
- **Paleta definitiva de Dojo Shoto** — el preset actual (blanco/rojo/azul) es provisional y hay que afinarlo con él. Sigue siendo una fila de `tenant_themes`, no un cambio de código.
- ~~Confirmar el sistema de progresión de MMA~~ — **resuelto, no bloqueaba (2026-08-28)**: `progression_style` ya es una elección del dojo por disciplina (HU-00b), no una decisión del sistema. `time_based` es solo el preset que se le sugiere al crear la disciplina; se puede cambiar sin tocar código si no calza.
- **Seed de demo de Dojo Shoto** — sus 4 disciplinas, escalas de cinturones, clases y miembros de ejemplo, para que la demo de venta se vea como su dojo y no como datos genéricos.

## Ticket prefix

`DOJO`. Ver [[Sistema/tickets|tickets.md]] y [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]].
