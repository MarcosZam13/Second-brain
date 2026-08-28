# Spec Dojo — Sección 8: Mini componentes y escala de estilos base

## Diferencia clave con la sección 4
La sección 4 (theming) define lo que **cambia por tenant** (color, logo, radio de bordes). Esta sección define lo que **es igual para todos los tenants** — la escala de tamaños, espaciados y tipografía, y el catálogo cerrado de componentes que reemplaza los patrones inconsistentes que hoy tiene GymBase (formularios que a veces son modal, a veces fullscreen, a veces nueva pestaña).

## Escala de estilos base (`packages/config/tokens.ts`)

No son colores — son medidas, y no dependen del tenant:

```ts
export const spacing = {
  xs: '4px', sm: '8px', md: '16px', lg: '24px', xl: '32px', '2xl': '48px',
};

export const typography = {
  scale: {
    xs: '12px', sm: '14px', base: '16px', lg: '18px', xl: '22px', '2xl': '28px', '3xl': '36px',
  },
  weight: { regular: 400, medium: 500, semibold: 600, bold: 700 },
  lineHeight: { tight: 1.2, normal: 1.5, relaxed: 1.7 },
};

export const elevation = {
  none: 'none',
  sm: '0 1px 2px rgba(0,0,0,0.08)',
  md: '0 4px 12px rgba(0,0,0,0.12)',
  lg: '0 8px 24px rgba(0,0,0,0.16)',
};

export const breakpoints = {
  mobile: '0px', tablet: '768px', desktop: '1024px',
};
```

Regla dura: ningún componente en `packages/ui` usa un `px` suelto fuera de esta escala. Esto se agrega a la misma lint rule de la sección 4 (que hoy solo bloqueaba hex sueltos) — se extiende para bloquear también valores de spacing fuera del token set.

## Catálogo cerrado de componentes (`packages/ui`)

La regla de producto: **un solo patrón por tipo de interacción**, no tres formas distintas de resolver lo mismo.

### Primitivas de formulario
| Componente | Reemplaza (inconsistencias actuales de GymBase) | Variantes |
|---|---|---|
| `FormField` | Inputs sueltos sin wrapper consistente | text, number, date, select, textarea |
| `FormModal` | El patrón único para creación/edición rápida de un registro | sm, md, lg (ancho) |
| `FormPage` | El patrón único para flujos multi-step o con mucho contenido (ej. crear evento de promoción completo) | — |
| `ConfirmDialog` | Confirmaciones que hoy a veces son alert(), a veces modal custom | destructive, neutral |

**Se elimina como categoría**: Sheet/Drawer ad-hoc. Todo lo que hoy usa ese patrón migra a `FormModal` o `FormPage` según corresponda (regla ya fijada en la conversación anterior sobre convención de formularios).

### Primitivas de estructura
| Componente | Uso |
|---|---|
| `Card` | Contenedor base — clases, contenido, eventos de promoción, retos de sparring |
| `Badge` | Estado (pending/accepted/completed), rango de un miembro, tipo de disciplina |
| `Avatar` | Foto de perfil de miembro, con fallback de iniciales |
| `EmptyState` | Reemplaza pantallas en blanco sin feedback cuando no hay datos (ej. "no tenés retos pendientes") |
| `Tabs` | Navegación entre vistas relacionadas (ej. calendario semanal/mensual según rol) |

### Componentes específicos de dominio (viven en `apps/dojo`, no en `packages/ui`, porque no son genéricos)
| Componente | Historia de usuario que resuelve |
|---|---|
| `RankBadge` | Muestra cinturón/franja con color y nombre — consume `ranks.color_hex` | HU-03, HU-14 |
| `SparringChallengeCard` | Tarjeta de reto con estado y acción disponible según el rol del usuario | HU-05 a HU-09 |
| `RoundScoreInput` | Input de resultado por round, solo habilitado para el challenger | HU-07 |
| `PromotionCriteriaForm` | Formulario de calificación por criterio con validación de `max_score` en vivo | HU-13 |
| `ClassCalendarWeek` / `ClassCalendarMonth` | Las dos vistas de calendario (miembro/admin) | HU-01, HU-04 |
| `PaymentProofUploader` | Subida de comprobante SINPE | HU-17 |

## Regla de composición (evita que `apps/dojo` reinvente primitivas)

Los componentes de dominio **siempre se construyen componiendo primitivas de `packages/ui`**, nunca con HTML/Tailwind crudo por fuera de ellas. Ejemplo — `SparringChallengeCard` es un `Card` + dos `Badge` + `Avatar`, no un `<div>` nuevo con clases sueltas. Esto es lo que en la práctica evita que vuelva a pasar lo de GymBase (una pantalla se ve distinta a otra porque cada una se armó a mano).

## Pendiente
Con esta sección se cierra el paquete completo de 8 documentos. El primer artefacto de código real sería el prompt de Claude Code para arrancar la semana 1 (setup del monorepo + `packages/ui` con este catálogo como base), si querés que lo arme.
