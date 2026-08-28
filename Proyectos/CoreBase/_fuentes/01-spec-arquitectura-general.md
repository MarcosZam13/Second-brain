# Spec Dojo — Sección 1: Arquitectura general

## Decisión confirmada
Monorepo Turborepo con dos apps (Dojo primero, GymBase v2 después) consumiendo un core compartido. Se descarta el enfoque de feature flags sobre un producto único (ya probado en `dojo-shoto/theme.config.ts`) porque perpetúa el patrón que generó la deuda técnica actual: un solo código ramificándose por condicionales de vertical.

## Estructura de carpetas

```
memberbase/
├── apps/
│   ├── dojo/                    → Next.js app, primera en construirse
│   └── gymbase/                 → v2, migra después
├── packages/
│   ├── core/
│   │   ├── auth/                → resolución de tenant vía JWT, roles
│   │   ├── billing/             → membresías, pagos, Onvo (conexión por comercio)
│   │   └── design-tokens/       → contrato de theming dinámico
│   ├── shared-modules/
│   │   ├── routines/            → tabla + UI parametrizable
│   │   ├── classes/              → tabla + UI parametrizable
│   │   ├── content/              → contenido por carpetas
│   │   └── notifications/        → shell genérico (extraído de NotificationBell.tsx)
│   ├── ui/                       → primitivas: Button, FormField, Modal (wrapper único), Select
│   └── config/                   → eslint, tsconfig, tailwind compartidos
└── turbo.json
```

## Regla de las 3 capas (para decidir dónde vive algo nuevo)

1. **Core** — sin configuración de negocio. Auth, tenant, billing, tokens de diseño.
2. **Shared-modules** — misma tabla/UI, comportamiento configurable por vertical (rutinas, clases, contenido). Pregunta de decisión: *si cambio el comportamiento en Dojo, ¿necesito que GymBase se entere?* Si no, es shared-module.
3. **Vertical puro** — vive solo dentro de `apps/dojo`. Sparring, rangos, promociones, torneos con lógica de disciplina marcial.

## Corrección de roles (confirmado por vos)
`owner` deja de colapsar a `admin`. En el core:
- `admin`: gestión operativa completa (miembros, clases, contenido, promociones).
- `owner`: todo lo de `admin` + vista de finanzas (dashboards de ingresos, reportes) + cambios de plan/facturación.
- El JWT claim de rol debe distinguir ambos explícitamente — ninguna policy puede tratarlos como sinónimos.

## Multi-disciplina (confirmado: Dojo Shoto maneja karate, BJJ, MMA, krav magá)
Se mantiene el patrón ya validado en producción:
- `organizations` → 1 a muchas `martial_arts` (ya soportado hoy, `UNIQUE(org_id, name)`).
- Un miembro tiene un rango independiente por disciplina — fuente única de verdad, sin la columna denormalizada `current_rank_id` que hoy coexiste y se desincroniza.
- Sparring, promociones y torneos siempre se asocian a una disciplina específica, nunca a un rango "general" del miembro.

## Corrección de bugs heredados que entran directo al spec (no se debaten)
- Validación de `score` de promociones contra `criteria.max_score` real, en servidor — no un rango fijo 0-100.
- Fórmula de cálculo de promoción como función pura compartida (un solo lugar), no duplicada cliente/servidor.
- Todas las mutaciones de estado (promociones, sparring) validan el estado actual en el server action, no solo ocultan botones en la UI.
- Resincronización de rango tras un ascenso solo resetea franjas de la disciplina afectada, no todas las disciplinas del miembro.

## Pendiente para la siguiente sección
La sección 2 (Schema de base de datos) va a detallar tabla por tabla qué se porta tal cual, qué se corrige, y qué se descarta — incluyendo la decisión sobre `ranks.presets` (hoy en `theme.config.ts`) vs. `gym_ranks` como fuente única de verdad para los colores/nombres de cinturones.
