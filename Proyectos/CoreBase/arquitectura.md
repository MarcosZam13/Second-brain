---
proyecto: CoreBase
tema: Arquitectura de la plataforma — monorepo, capas, stack y operación
fecha: 2026-08-28
tipo: documentacion
estado: v1.0 — decisiones cerradas, reemplaza al spec 01 de `_fuentes/`
tags: [corebase, dojobase, gymbase, arquitectura, monorepo]
---

# Arquitectura — CoreBase

Ver también: [[Proyectos/CoreBase/README|README]] · [[Proyectos/CoreBase/revision-critica-specs|Revisión crítica de los specs]] · [[Proyectos/CoreBase/schema|schema.md]] · [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]] · [[Proyectos/DojoBase/README|DojoBase]] · [[Proyectos/GymBase/README|GymBase v1]]

> Este documento reemplaza a `_fuentes/01-spec-arquitectura-general.md`. El spec original asumía evolucionar sobre GymBase; la decisión del 2026-08-28 es **construir desde cero**, lo que cambia varias piezas. El spec queda en `_fuentes/` como registro histórico.

## 1. Decisión de fondo: se construye desde cero

**Qué se descarta:** evolucionar el repo `Gymbase`, reusar su proyecto de Supabase, y el enfoque de feature flags sobre un producto único (`clients/gymbase/<tenant>/theme.config.ts`).

**Por qué:** GymBase v1 funciona pero **no está en uso** — no hay clientes operando sobre él. Llegó a donde está acumulando: 618 colores hex sueltos, 5 patrones de presentación de formularios, 2 arquitecturas de formulario conviviendo, 3 implementaciones distintas de modal, sin separación de dominio ni a nivel de carpetas, y con la resolución de tenant atada a un header custom contra un dominio hardcodeado. Cada una de esas cosas se arrastra si se parte del código existente. Es un proyecto personal sin usuarios que dependan de nada de esto todavía — el costo de empezar limpio es tiempo, y el retorno es un producto consistente, con mini-componentes reales y cero hardcoding, que es exactamente lo que hace la diferencia entre "funciona" y "vendible".

**Qué NO significa "desde cero":** no se tira el conocimiento. GymBase v1 es la **fuente de especificación**: su lógica de negocio ya pasó por el uso real y por la retroalimentación del sensei de Dojo Shoto (fórmula de ascensos, máquina de estados de sparring, flujo de comprobantes SINPE, recurrencia de clases, cálculo de asistencia por disciplina). Esa validación es el activo que se conserva. La lógica se **lee, se entiende y se reescribe limpia** — nunca se copia y pega. Los tres documentos de extracción del repo viejo (`auditoria-gymbase.md`, `extraccion-tecnica-dojo.md`, `logica-promociones.md`) existen precisamente para eso.

**Regla operativa:** cuando haya que implementar algo que GymBase ya resuelve, el orden es (1) leer cómo lo resuelve hoy y por qué, (2) decidir si esa decisión sigue siendo correcta, (3) escribirlo de nuevo contra el design system y el schema nuevos. Nunca (1) copiar el archivo, (2) adaptarlo.

## 2. Nombres — uno por cosa

Cuatro nombres circulaban para tres cosas (`memberbase`, CoreBase, DojoBase, `@memberbase/gymbase`). Queda así:

| Nombre | Qué es |
|---|---|
| **CoreBase** | La plataforma. El repo/monorepo (`corebase`), el scope npm (`@corebase/*`), la capa compartida, la organización y el proyecto de Supabase. |
| **DojoBase** | Producto vendible #1 — academias de artes marciales. `apps/dojobase`. |
| **GymBase** | Producto vendible #2 — gimnasios de fitness. `apps/gymbase`, se construye después. GymBase **v1** es el legacy archivado en otro repo, sin uso. |

Se descarta **MemberBase**: era el nombre interno de GymBase v1 y arrastra justamente la confusión "un producto para gyms y dojos a la vez" que este proyecto está resolviendo.

## 3. Estructura del monorepo

```
corebase/                          → repo nuevo, Turborepo + pnpm workspaces
├── apps/
│   ├── dojobase/                  → Next.js. Primera y única app hasta que cierre
│   ├── gymbase/                   → v2, después de DojoBase
│   └── marketing/                 → landings de venta (DojoBase, GymBase). NO consume packages/ui
├── packages/
│   ├── core/                      → @corebase/core — subpath exports, un solo paquete
│   │   ├── auth/                  → tenant y rol vía JWT, sesión, guards de server action
│   │   ├── tenant/                → organización activa, invitaciones, membresía de org
│   │   ├── billing/               → planes, suscripciones, comprobantes, conexión de pagos
│   │   ├── theming/               → contrato de tokens por tenant y su aplicación
│   │   └── db/                    → tipos generados de Supabase + cliente tipado
│   ├── ui/                        → @corebase/ui — primitivas. Cero conocimiento de negocio
│   ├── modules/                   → @corebase/modules — shared-modules parametrizables
│   │   ├── classes/               → clases, cupos, reservas, asistencia
│   │   ├── content/               → contenido por carpetas con gating por plan
│   │   ├── routines/              → rutinas y ejercicios
│   │   ├── challenges/            → retos y gamificación
│   │   └── notifications/         → motor Realtime + Web Push
│   └── config/                    → @corebase/config — eslint, tsconfig, tailwind, tokens base
├── supabase/
│   ├── migrations/                → migraciones de core + modules (comunes a todo producto)
│   └── seed/                      → datos de demo
├── turbo.json
└── pnpm-workspace.yaml            → apps/* y packages/*
```

Las migraciones **específicas de un vertical** viven en su app (`apps/dojobase/supabase/migrations/`), no en la raíz. La raíz es lo que cualquier producto CoreBase necesita.

### 3.1 Por qué `packages/core` es un solo paquete y no tres

El spec original proponía `packages/core/{auth,billing,design-tokens}` como paquetes separados. Tres paquetes = tres `package.json`, tres `tsconfig`, tres builds y dependencias cruzadas que resolver, para un proyecto de una persona. Un `@corebase/core` con subpath exports (`import { requireRole } from '@corebase/core/auth'`) da la misma separación conceptual y la misma disciplina de importación, con un décimo del wiring. Si algún día duele, se parte — hoy no duele.

### 3.2 La regla de las 3 capas

Para decidir dónde vive algo nuevo:

1. **Core** (`packages/core`) — sin ninguna configuración de negocio. Identidad, tenant, roles, billing, tokens de theming. Prueba: *¿esto sería idéntico si el producto fuera una escuela de música?* Si sí, es core.
2. **Module** (`packages/modules`) — misma tabla y misma UI, comportamiento configurable por vertical. Prueba: *si cambio el comportamiento en DojoBase, ¿necesito que GymBase se entere?* Si no, es module.
3. **Vertical puro** (`apps/dojobase`) — sparring, rangos, promociones, peleas oficiales, torneos. Todo lo que tiene lógica de disciplina marcial.

**Regla dura anti-fuga:** `packages/core` y `packages/ui` no pueden contener las palabras `dojo`, `gym`, `rank`, `belt`, `sparring`, `martial` en ningún identificador ni ruta. Se verifica con un test de lint en CI — no es un acuerdo de buena voluntad, es una regla ejecutable. Esta es la prueba real de que CoreBase sirve para un tercer producto que no sea ninguno de los dos.

**Regla dura anti-import:** una app nunca importa de otra app. `apps/dojobase` no conoce la existencia de `apps/gymbase`.

## 4. Stack

Se conserva el de GymBase v1 (está probado, es moderno, y ya hay skills escritas para él), con los ajustes que la revisión dejó:

| Capa | Elección | Nota |
|---|---|---|
| Framework | Next.js (App Router, TypeScript strict) | Server Actions como capa de mutación |
| Backend | Supabase — Postgres 17 + Auth + Storage + Realtime + RLS | Proyecto `CoreBase` (`pzyvvotltgipehsywqpi`) |
| Estilos | Tailwind CSS v4 + tokens en CSS vars | Sin shadcn copiado adentro: primitivas propias en `@corebase/ui` sobre Base UI |
| Formularios | **React Hook Form + Zod, único patrón** | Se elimina de raíz la coexistencia con `useState` manual de v1 |
| Estado servidor | TanStack Query donde haga falta cliente | La mayoría resuelve con Server Components |
| Animación | CSS transitions + Framer Motion liviano | Máx. 400ms en flujos diarios (regla del spec 08b) |
| Monorepo | pnpm workspaces + Turborepo | |
| Tests | Vitest (unit) + Playwright (e2e) | Ver §7 |
| PWA | Instalable desde el día uno (RNF-05) | Sin tienda de apps en el MVP |

**Decisión de formularios (cierra el hallazgo de los 5 patrones):** un solo patrón por tipo de interacción, definido en el design system —
`FormModal` para crear/editar un registro simple, `FormPage` para flujos multi-paso o con mucho contenido, `ConfirmDialog` para confirmaciones. **Se elimina Sheet/Drawer como categoría.** Cualquier formulario nuevo cae en uno de esos tres o no se mergea.

## 5. Multi-tenancy y resolución de tenant

El cambio de fondo respecto a v1: el tenant y el rol dejan de resolverse por un header HTTP inyectado por middleware contra un hostname hardcodeado, y pasan a ser **claims del JWT**, calculados al emitir el token.

Esto elimina la dependencia de Next.js middleware (cualquier cliente futuro — mobile con Expo, una Edge Function, un script — lee el claim directo), y es lo que hace que onboardear un dojo nuevo sea un insert y no un deploy. El detalle completo del mecanismo, los helpers y las policies está en [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]].

Piezas que el spec original no cubría y quedan definidas ahí: dónde vive la organización activa (`profiles.active_org_id`), el TTL del token, y qué hacer con el desfase de rol tras una degradación.

## 6. Proyectos de Supabase — uno por producto

**CoreBase no es una base de datos.** Es un conjunto de migraciones y de código que se *aplica* a la base de cada producto. Cada producto vendible tiene su propio proyecto de Supabase:

| Producto | Proyecto Supabase | Estado |
|---|---|---|
| DojoBase | `pzyvvotltgipehsywqpi` (hoy llamado "CoreBase", org `CoreBase`, us-east-2, PG 17.6) | Vacío, listo |
| GymBase v2 | A crear cuando arranque | — |
| GymBase v1 (legacy) | `vwkxrjnxfjfzobzzoagj` (otra cuenta, us-west-2) | Vacío, sin uso. Queda solo como respaldo |

**Pendiente menor:** el proyecto se llama "CoreBase" pero va a contener los datos de DojoBase. Conviene renombrarlo a `dojobase` desde el dashboard antes de la primera migración, para que en seis meses no haya duda de qué base es cuál. Es un cambio de nombre, no afecta el ref ni las URLs.

Un dojo y un gimnasio no comparten base: mezclarlos recrearía exactamente el acoplamiento del que se está saliendo.

**Nota de región:** us-east-2 (Ohio). El proyecto de Vercel debe fijar región `cle1` para quedar junto a la base — v1 aprendió esto por el lado caro (`perf(vercel): fijar región de funciones en pdx1`).

## 7. Operación — lo que ningún spec cubría

### Testing

- **Vitest** para la lógica pura, que es donde vale: fórmula de cálculo de ascensos, resolución del ganador de sparring por rounds, ventana de asistencia, cálculo del próximo período de una suscripción. Estas son funciones puras compartidas — una sola implementación, importada por cliente y servidor, con tests.
- **Playwright** para los flujos con estado, no para CRUD: reto de sparring completo, evaluación y cierre de un evento de promoción, subida y aprobación de comprobante.
- **Tests de RLS**: un archivo por tabla sensible que se autentique como `member`, `admin` y `owner` y verifique la matriz de acceso. Esto es lo que evita que una migración futura abra un hueco en silencio.
- Los tests se escriben contra **RF específicos como criterio de aceptación**, no genéricos — es el encargo del agente de QA.

### CI

GitHub Actions con: typecheck, lint (incluye las reglas anti-hex y anti-vertical de §3.2), Vitest, y build de todas las apps. Playwright en PR a `main`.

### Entornos y deploy

Un proyecto de Vercel por app. `apps/dojobase` con dominio propio; `apps/marketing` separado. Variables de entorno por app, nunca compartidas entre productos.

### Cobro

El MVP cobra por comprobante SINPE manual. ONVO Pay (marketplace con cuentas conectadas) queda modelado y listo para activarse cuando la inscripción ante Hacienda esté hecha — ver [[Proyectos/CoreBase/billing-onvo|billing-onvo.md]]. El modo de cobro es una fila de configuración por organización, no una rama de código.

### Jobs programados

Tres necesidades vencen por tiempo y ninguna tenía mecanismo asignado: expiración de sparrings sin resolver (RF-06b), recordatorios de pago próximo a vencer (RF-17) y expiración de suscripciones. Se resuelven con **un solo job diario de `pg_cron`** definido como pieza de CoreBase, no con tres mecanismos distintos.

### Tiempo real

En GymBase v1 nunca funcionó, y la causa era estructural: su RLS depende de un header HTTP que el
middleware de Next.js inyecta, y **una conexión de Realtime no pasa por ese middleware** — así que
la comprobación interna de Realtime denegaba todo, en silencio. Mover el tenant al claim del JWT
arregla eso de raíz. El diagnóstico completo, la decisión de usar Broadcast desde la base y el
**spike que hay que correr antes de construir nada encima** están en
[[Proyectos/CoreBase/realtime|realtime.md]].

### Observabilidad

Errores de servidor y de cliente a un solo destino desde el día uno. Sin esto, el primer bug reportado por el sensei se depura a ciegas.

### Datos de demo

Un seed que levante una organización completa (disciplinas, rangos, miembros, clases, un evento de promoción a medio calificar) — es lo que permite demostrar el producto sin cargar datos a mano y lo que hace usable el entorno de desarrollo.

## 8. Roles

Tres roles reales, sin colapso. En v1, `get_user_role()` devolvía `admin` para los owners, lo que dejaba rama muerta en toda policy `= ANY(['admin','owner'])`.

| Rol | Alcance |
|---|---|
| `member` | Su propia información, lo público de su organización |
| `admin` | Gestión operativa completa: miembros, clases, contenido, promociones, aprobación de comprobantes |
| `owner` | Todo lo de `admin` + finanzas (reportes de ingresos) + conexión de pagos + cambios de plan |

El claim de rol del JWT distingue los tres explícitamente; ninguna policy puede tratar `admin` y `owner` como sinónimos.

## 9. Multi-disciplina

Se mantiene el patrón ya validado con uso real, con la corrección de la doble fuente de verdad:

- Una organización tiene N disciplinas (`UNIQUE(org_id, name)`).
- Un miembro tiene un rango **independiente por disciplina** (`member_ranks`), y esa es la **única** fuente de verdad. Se descarta la columna denormalizada `current_rank_id` de v1, que coexistía y se desincronizaba sin trigger que las mantuviera juntas.
- Sparring, promociones, peleas y torneos siempre se asocian a una disciplina específica, nunca a un rango "general" del miembro.

## 10. Correcciones de v1 que entran directo al diseño

No se debaten — son bugs conocidos del código actual que no se replican:

- El puntaje de un criterio de promoción se valida en servidor contra el `max_score` real de ese criterio, no contra un rango fijo 0-100.
- La fórmula de cálculo de ascenso es **una función pura compartida**, importada por cliente (preview en vivo) y servidor (resolución). Nunca duplicada.
- Toda mutación de estado valida el estado actual en el servidor. Ocultar un botón en la UI no es un control de acceso (RNF-01).
- Resincronizar el rango tras un ascenso toca solo la disciplina afectada, no resetea franjas de las otras.
- Sin funciones en el schema `auth` de Supabase (reservado, se sobrescribe en upgrades) — todo en `public`, con `execute` revocado a `anon` donde corresponda.
- Sin `CREATE POLICY` sobre vistas — Postgres no lo soporta. Ver [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]].
- Nombres de tabla sin prefijo de vertical heredado (`scheduled_classes`, no `gym_scheduled_classes`).

## 11. Qué pasa con GymBase v1

Nada. **No está en uso, no tiene clientes operando y su base de datos está vacía** — queda archivado como respaldo y como fuente de especificación. No se le agregan features, no se le hacen fixes, y no hay migración de datos que planificar.

Esto simplifica el proyecto de forma importante respecto de lo que asumían los specs: no hay corte, no hay ventana de riesgo con un cliente, y no hay dos productos que mantener en paralelo. Toda la atención va a DojoBase, y el objetivo es que esté **listo para vender**, con Dojo Shoto como primer prospecto.
