# Spec Dojo — Sección 4: Theming dinámico por tenant

## Punto de partida: lo que ya funciona no se descarta

`dojo-shoto/theme.config.ts` ya prueba en producción que el patrón de tokens dinámicos por tenant es viable — Dojo Shoto corre hoy con blanco/rojo/azul sin tocar código. El objetivo de esta sección no es inventar el mecanismo, es **moverlo del nivel de "config de feature flags dentro de un producto único" al nivel de "paquete core que cualquier app del monorepo consume"**, y cerrar el hueco de hardcoding que señaló la auditoría (colores/spacing embebidos directo en componentes en vez de referenciar tokens).

## Contrato del paquete `packages/core/design-tokens`

```ts
// packages/core/design-tokens/types.ts
export interface TenantTheme {
  orgId: string;
  colors: {
    primary: string;       // hex
    secondary: string;
    accent: string;
    background: string;
    surface: string;
    textPrimary: string;
    textMuted: string;
  };
  typography?: {
    headingFont?: string;  // opcional: si el tenant no define, usa default del vertical
    bodyFont?: string;
  };
  logoUrl?: string;
  radius?: 'sharp' | 'soft' | 'rounded';  // control simple de personalidad visual sin exponer CSS crudo
}
```

Esto reemplaza la config estática de `theme.config.ts` por un registro almacenado en base de datos, no en archivo:

```sql
-- [core] tabla nueva
tenant_themes (
  org_id uuid references organizations primary key,
  colors jsonb not null,
  typography jsonb,
  logo_url text,
  radius text check (radius in ('sharp','soft','rounded')) default 'soft',
  updated_at timestamptz default now()
)
```

**Por qué pasa de archivo a tabla:** un `theme.config.ts` por tenant significa un deploy por cada dojo nuevo que se onboardea. Con la tabla, onboardear un dojo nuevo es una fila, no un PR.

## Cómo se inyecta en runtime (Next.js, ambas apps)

```ts
// packages/core/design-tokens/apply-theme.ts
export function themeToCssVars(theme: TenantTheme): Record<string, string> {
  return {
    '--color-primary': theme.colors.primary,
    '--color-secondary': theme.colors.secondary,
    '--color-accent': theme.colors.accent,
    '--color-background': theme.colors.background,
    '--color-surface': theme.colors.surface,
    '--color-text-primary': theme.colors.textPrimary,
    '--color-text-muted': theme.colors.textMuted,
    '--radius-base': theme.radius === 'sharp' ? '2px' : theme.radius === 'rounded' ? '16px' : '8px',
  };
}
```

Se aplica en el layout raíz de cada app (`apps/dojo/app/layout.tsx`), leyendo `tenant_themes` por `org_id` del JWT y seteando las variables inline en el `<html>` antes del primer render (evita flash de tema por defecto):

```tsx
// apps/dojo/app/layout.tsx
const theme = await getThemeForOrg(orgId); // server component, una sola query
const cssVars = themeToCssVars(theme);

return (
  <html style={cssVars as React.CSSProperties}>
    <body>{children}</body>
  </html>
)
```

## Regla dura para `packages/ui` (resuelve el hallazgo de hardcoding de la auditoría)

Ningún componente en `packages/ui` puede usar un hex, un color de Tailwind por defecto (`bg-blue-500`), o un valor de spacing fijo sin pasar por una variable CSS. Se aplica vía:

1. **Config de Tailwind compartida** (`packages/config/tailwind.config.ts`) que mapea los colores del theme a clases utilitarias:
```ts
colors: {
  primary: 'var(--color-primary)',
  secondary: 'var(--color-secondary)',
  accent: 'var(--color-accent)',
  surface: 'var(--color-surface)',
}
```
Así `bg-primary` en cualquier componente de `packages/ui` resuelve al color del tenant activo automáticamente, sin que el componente sepa que existe theming.

2. **Lint rule** en `packages/config/eslint` que bloquea hex literals (`/#[0-9a-fA-F]{3,8}/`) dentro de `packages/ui/**` y `apps/*/src/components/**` — esto es lo que evita que el problema de GymBase (colores sueltos en JSX) se repita en el código nuevo. Se agrega como regla custom simple, no depende de un plugin externo.

## Qué pasa con los 4 dojos/gimnasios que ya usan colores distintos hoy

Migración de `theme.config.ts` existente (Dojo Shoto) a fila en `tenant_themes`: es un insert único, no requiere cambio de producto de su lado — se hace como parte del onboarding técnico, no del roadmap de features.

## Qué NO entra en esta capa (para no repetir el error de sobre-generalizar)

- **Layout/estructura de página** no es theming — eso es decisión de UI por vertical (Dojo puede necesitar una pantalla de "próximas peleas" en el dashboard que GymBase no tiene). Theming es solo color, tipografía, logo y radio de bordes. Confundir esto fue parte de por qué GymBase terminó con lógica de vertical mezclada en componentes "genéricos".

## Pendiente para la siguiente sección
Sección 5 (última técnica antes de pasar a historias de usuario/requerimientos): el módulo de notificaciones compartido — cómo se generaliza `NotificationBell.tsx` para servir tanto al feed de sparring en tiempo real como al futuro push de GymBase, sin acoplarlo a un vertical.
