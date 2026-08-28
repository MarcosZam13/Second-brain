# CoreBase

Ver también: [[Proyectos/README|Proyectos]] · [[Proyectos/DojoBase/README|DojoBase]] · [[Proyectos/GymBase/README|GymBase v1]]

**Repo:** `corebase` — monorepo nuevo, a crear en `ProyectosPersonales/`.
**Supabase:** org `CoreBase` · proyecto `pzyvvotltgipehsywqpi` (us-east-2, PG 17.6) — vacío, será la base de DojoBase.
**Estado:** specs corregidos y cerrados (2026-08-28). Siguiente paso: documentación de producto de DojoBase, después kickoff de código.

## Qué es

CoreBase es **la plataforma**, no un producto. Es el monorepo y la capa compartida sobre la que corren productos vendibles independientes, cada uno con su nicho, su app y su identidad comercial propia:

| Pieza | Qué es | Estado |
|---|---|---|
| **CoreBase** | La capa compartida y reutilizable: `packages/core` (auth, tenant, billing, theming), `packages/ui` (primitivas), `packages/modules` (clases, contenido, rutinas, challenges, notificaciones), `packages/config`. Sin conocimiento de ningún vertical. | A construir |
| **DojoBase** | `apps/dojobase` — SaaS para academias de artes marciales. **Es la prioridad.** | A construir |
| **GymBase v2** | `apps/gymbase` — SaaS para gimnasios de fitness. Migra al core *después* de DojoBase. | v1 en producción en otro repo |

## Las tres decisiones que definen el proyecto

1. **Se construye desde cero.** No se evoluciona el repo de GymBase v1. GymBase queda como *fuente de especificación* — la lógica de negocio está validada en producción y se lee, se entiende y se reescribe limpia; nunca se copia. Esto es lo que garantiza mini-componentes reales, cero hardcoding y un solo patrón por interacción desde el día uno.
2. **Dos productos sobre un core, no un producto con feature flags.** El enfoque de v1 (`clients/gymbase/<tenant>/theme.config.ts` con 30 flags) funciona pero es exactamente lo que generó la deuda: un código ramificándose por condicionales de vertical.
3. **Un proyecto de Supabase por producto.** CoreBase no es una base de datos: es un conjunto de migraciones y código que se *aplica* a la base de cada producto.

## Las dos reglas duras del monorepo

- **Anti-fuga:** `packages/core` y `packages/ui` no pueden contener `dojo`, `gym`, `rank`, `belt`, `sparring` ni `martial` en ningún identificador ni ruta. Se verifica en CI — es una regla ejecutable, no un acuerdo de buena voluntad. Es la prueba de que CoreBase sirve para un tercer producto que no sea ninguno de los dos.
- **Anti-import:** una app nunca importa de otra app.

## Documentos

| Documento | Qué contiene |
|---|---|
| [[Proyectos/CoreBase/arquitectura\|arquitectura.md]] | Monorepo, nombres, regla de las 3 capas, stack, multi-tenancy, proyectos de Supabase, y toda la operación que ningún spec cubría (testing, CI, deploy, jobs, observabilidad, seed) |
| [[Proyectos/CoreBase/schema\|schema.md]] | Schema de la capa core y de los módulos compartidos, corregido y completado contra las historias de usuario |
| [[Proyectos/CoreBase/seguridad-jwt-rls\|seguridad-jwt-rls.md]] | Tenant vía JWT, helpers, RLS por tabla, matriz de acceso y checklist OWASP por PR. Corrige los 4 bloqueantes de SQL del spec original |
| [[Proyectos/CoreBase/revision-critica-specs\|revision-critica-specs.md]] | El análisis que fundamenta todo lo anterior: qué estaba roto en los specs, qué faltaba, y las 7 decisiones ya tomadas |
| `_fuentes/` | Los 9 specs originales sin editar, como registro histórico |

## Contexto técnico de GymBase v1

No vive en este vault — está dentro de su repo, para no desactualizarse en dos lugares. Es la fuente de la que se lee la lógica de negocio ya validada:

- `Context/_CONTEXTO-IA.md` — arquitectura, stack, patrones, feature flags, tablas, rutas completas.
- `auditoria-gymbase.md` — qué es reutilizable, qué es deuda, qué es vertical puro.
- `extraccion-tecnica-dojo.md` — schema SQL completo, código de funciones y hooks, inventario de componentes.
- `logica-promociones.md` — fórmula de cálculo de ascensos y sus 11 casos borde.

## Ticket prefix

`MB` para trabajo transversal de plataforma/CoreBase, `DOJO` para DojoBase, `GYM` para GymBase. Ver [[Sistema/tickets|tickets.md]] y [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]].
