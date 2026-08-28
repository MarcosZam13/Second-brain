# Prompt para Claude Code — Semana 1: Setup de subagentes + CoreBase

## Contexto
Voy a construir un monorepo Turborepo con tres piezas diferenciadas: **CoreBase** (el paquete base compartido, sin lógica de ningún vertical), y dos apps que lo consumen — **DojoBase** (primera en construirse) y **GymBase v2** (después). Te voy a adjuntar 9 documentos de spec ya cerrados:
1. Arquitectura general
2. Schema de base de datos
3. JWT/RLS detallado
4. Theming dinámico
5. Notificaciones compartidas
6. Historias de usuario y requerimientos
7. Agentes y cronograma de 8 semanas
8. Mini componentes y escala de estilos base
8b. Identidad de marca (landing) vs. theming de tenant

Esta semana (semana 1 del cronograma de la sección 7) tiene dos entregables: (A) configurar los subagentes de trabajo, (B) construir **CoreBase** (`packages/core`) funcional.

## Parte A — Crear los subagentes en `.claude/agents/`

Basándote en las descripciones de la sección 7 del documento de agentes, creá estos 4 archivos:

- `.claude/agents/ui-agent.md` — agente de desarrollo UI/componentes, con contexto de la sección 4 (theming) y sección 8 (componentes/estilos) como su system prompt base. Debe rechazar cualquier hex hardcodeado o valor de spacing fuera de los tokens definidos.
- `.claude/agents/qa-agent.md` — agente de QA/testing, con foco en escribir tests contra RF específicos como criterios de aceptación, no tests genéricos.
- `.claude/agents/security-agent.md` — agente de seguridad OWASP 2025, con foco explícito en: control de acceso roto (validar server-side, no solo UI oculta), exposición de datos financieros (verificar que `admin` nunca alcance `financial_summary` ni `org_payment_connections`), y el fix de `push_subscriptions` con scoping de `org_id`.
- `.claude/agents/docs-agent.md` — agente de documentación, mantiene un `CLAUDE.md` por paquete/app, documenta decisiones que se desvíen del spec original.

Cada archivo debe tener el formato estándar de subagente de Claude Code (frontmatter con nombre/descripción + system prompt en el cuerpo). Si no conocés el formato exacto, buscá la documentación oficial de subagentes de Claude Code antes de crear los archivos.

## Parte B — Construir CoreBase (`packages/core`)

Usando la sección 1 (arquitectura), sección 2 (schema — solo las tablas `[core]`) y sección 3 (JWT/RLS) como fuente de verdad:

1. Estructura de carpetas del monorepo tal como está en la sección 1.
2. Migraciones SQL de las tablas core: `profiles`, `organizations`, `org_members`, `membership_plans`, `subscriptions`, `payment_proofs`, `org_payment_connections`, `tenant_themes`.
3. Las funciones helper de JWT (`auth.org_id()`, `auth.role_in_org()`, `auth.is_admin_or_owner()`, `auth.is_owner()`) y el hook `custom_access_token_hook()` activado según la sección 3.
4. Las policies RLS del patrón base + las específicas de billing (owner-only) de la sección 3.
5. La vista `financial_summary` con su policy exclusiva de owner.

No implementes todavía nada de `shared-modules` ni de las apps (DojoBase/GymBase v2) — esta semana es solo CoreBase.

## Al finalizar
Pedile al `docs-agent` que genere el primer `CLAUDE.md` de CoreBase documentando lo construido, y al `security-agent` que revise las policies RLS contra el checklist de la sección 7 antes de dar la semana por cerrada.
