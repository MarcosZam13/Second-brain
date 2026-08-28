# MemberBase

Ver también: [[Proyectos/README|Proyectos]] · [[Proyectos/DojoBase/README|DojoBase]] · [[Proyectos/GymBase/README|GymBase]] · [[Proyectos/MemberBase/revision-critica-specs|Revisión crítica de los specs]]

**Repo:** `ProyectosPersonales/Gymbase` (a renombrar a `memberbase`) — monorepo Turborepo + pnpm.
**Estado:** specs 1-9 cerrados y revisados (2026-08-28), pendientes 7 decisiones antes del kickoff de código.

## Qué es

MemberBase es **la plataforma**, no un producto. Es el monorepo y la capa compartida sobre la que corren dos productos vendibles distintos, cada uno con su propio nicho, su propia app y su propia identidad comercial:

| Pieza | Qué es | Estado |
|---|---|---|
| **CoreBase** | La capa compartida: `packages/core` (auth/tenant/billing/design-tokens), `packages/ui` (primitivas), `packages/shared-modules` (rutinas, clases, contenido, notificaciones), `packages/config`. No es un producto ni un paquete npm — es el nombre humano del conjunto. | A construir (semana 1) |
| **DojoBase** | `apps/dojobase` — SaaS para academias de artes marciales. **Es la prioridad.** | A construir |
| **GymBase v2** | `apps/gymbase` — SaaS para gimnasios de fitness. Migra al core *después* de DojoBase. | v1 en producción hoy |

## Por qué se parte en dos productos

GymBase v1 resuelve "dojo vs gym" con feature flags sobre un único código (`clients/gymbase/<tenant>/theme.config.ts`). Funciona — Dojo Shoto corre en producción así — pero es exactamente el patrón que generó la deuda actual: un solo código ramificándose por condicionales de vertical, sin separación de dominio ni a nivel de carpetas.

La decisión (spec 1) es dos apps sobre un core compartido, con la **regla de las 3 capas** para saber dónde vive cada cosa nueva:

1. **Core** — sin configuración de negocio. Auth, tenant, billing, tokens de diseño.
2. **Shared-module** — misma tabla/UI, comportamiento configurable por vertical. Pregunta de decisión: *si cambio el comportamiento en DojoBase, ¿necesita GymBase enterarse?* Si no, es shared-module.
3. **Vertical puro** — vive solo dentro de su app. Sparring, rangos, promociones, torneos.

## Regla dura del monorepo

`apps/dojobase` **no puede importar nada de `apps/gymbase`**. El código viaja `apps/gymbase` → `packages/*` → `apps/dojobase` solo por porte explícito con limpieza, nunca por import directo. Sin esta regla la deuda de GymBase v1 (618 hex sueltos, 5 patrones de formulario, 2 arquitecturas de formulario) se cuela en el producto nuevo el primer día.

## Dónde está cada cosa

- [[Proyectos/MemberBase/revision-critica-specs|revision-critica-specs.md]] — **leer primero.** Revisión de los 9 specs contra el código real: 4 bloqueantes de SQL, gaps de schema vs. historias de usuario, y las 7 decisiones pendientes.
- `_fuentes/` — los specs originales tal como se escribieron, sin editar:
  - `01-spec-arquitectura-general.md` — monorepo, regla de las 3 capas, roles owner/admin.
  - `02-spec-schema-database.md` — schema tabla por tabla, etiquetado `[core]`/`[shared]`/`[dojo]`.
  - `03-spec-jwt-rls.md` — tenant vía JWT claim, helpers, RLS por tabla, matriz de acceso.
  - `04-spec-theming.md` — `tenant_themes` en tabla, inyección de CSS vars, lint rule anti-hex.
  - `05-spec-notificaciones.md` — módulo compartido Realtime + Web Push, contrato `emitNotification`.
  - `08-spec-componentes-estilos.md` — escala de estilos base y catálogo cerrado de `packages/ui`.

Los specs 06 (HU/requerimientos), 07 (agentes y cronograma), 08b (identidad de marca) y 09 (prompt de kickoff) son específicos de DojoBase y viven en [[Proyectos/DojoBase/README|DojoBase/_fuentes/]].

## Contexto técnico de GymBase v1 (la base de la que se porta)

No vive en este vault — está dentro del repo, para no desactualizarse en dos lugares:

- `Context/_CONTEXTO-IA.md` — arquitectura, stack, patrones, feature flags, tablas, rutas completas.
- `Context/_ESTADO-ACTUAL.md` — estado módulo por módulo.
- `auditoria-gymbase.md` — qué es reutilizable, qué es deuda, qué es vertical puro.
- `extraccion-tecnica-dojo.md` — schema SQL completo + código de funciones/hooks + inventario de componentes.
- `logica-promociones.md` — fórmula de cálculo de ascensos y sus 11 casos borde.

## Ticket prefix

`MB` para trabajo transversal de plataforma/CoreBase, `DOJO` para DojoBase, `GYM` para GymBase. Ver [[Sistema/tickets|tickets.md]] y [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]].
