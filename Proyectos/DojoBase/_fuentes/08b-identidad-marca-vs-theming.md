# Spec Dojo — Sección 8b: Identidad de marca (landing) vs. theming de tenant (app)

Esta sección existe para que ningún agente confunda estas dos capas al implementar. Son decisiones distintas, con dueños distintos, y mezclarlas rompe el principio de theming dinámico de la sección 4.

## Capa 1 — Identidad de marca de DojoBase (el producto en sí)
**Vive en**: el landing page de marketing (`dojobase-hero-real-art.html` y evoluciones futuras), fuera del monorepo de la app o en una app de marketing separada dentro del monorepo (`apps/marketing`, no consume `packages/ui`).
**Paleta**: `--void`, `--crimson`, `--amber`, `--paper` — fija, no depende de tenant.
**Tipografía**: Anton (display) + Space Grotesk (cuerpo).
**Animación**: scroll-driven, GSAP + ScrollTrigger, parallax de capas, efectos de impacto — libre de restricciones de peso porque se visita una sola vez por decisión de compra.
**Regla para agentes**: nada de este archivo se importa ni se referencia desde `apps/dojo` o `packages/ui`. Es un artefacto de marketing independiente.

## Capa 2 — Theming dinámico por tenant (definido en sección 4)
**Vive en**: `tenant_themes` (tabla), consumido por `apps/dojo` en runtime.
**Paleta**: variable, definida por cada dojo (ej. Dojo Shoto = blanco/rojo/azul).
**Regla para agentes**: todo color en `packages/ui` y en componentes de dominio resuelve contra `var(--color-*)`, nunca contra los hex de la Capa 1.

## Capa 3 — Lo que SÍ cruza de la landing a la app (con reglas explícitas, no libre)

| Elemento tomado de la landing | Dónde se usa en la app | Regla de uso |
|---|---|---|
| Tipografía Anton | Momentos de alto impacto emocional puntuales: modal de "¡Promovido!", resultado de sparring ganado, título del feed de próximas peleas | Máximo 3-4 puntos de uso en toda la app. Nunca en formularios, tablas, ni texto de cuerpo — ahí siempre la tipografía base del theme (liviana, legible). |
| Micro-animación tipo "flash/pulso" | Confirmación de logro: reto aceptado, ascenso de franja, resultado cargado | CSS transitions/keyframes nativas o Framer Motion liviano — nunca GSAP/ScrollTrigger completo. Duración corta (<400ms), sin scroll-jacking. |
| Paleta oscura de alto contraste | Disponible como **preset opcional** dentro de `tenant_themes`, no como default | Un dojo con identidad más "combate" (MMA, krav magá) puede elegirlo; Dojo Shoto usa su propia paleta blanco/rojo/azul igual. |

## Regla de rendimiento (no negociable, para el agente de UI y el de QA)
La app (`apps/dojo`) prioriza ligereza sobre impacto visual: sin scroll-jacking, sin parallax de capas múltiples, sin animaciones de más de 400-500ms en flujos de uso diario (inscribirse a clase, cargar resultado). El objetivo de la app es que funcione bien en mobile de gama media y con conexión inestable — el objetivo del landing es impresionar una sola vez. El agente de QA debe señalar cualquier componente que se acerque al peso/complejidad de la landing como hallazgo a revisar, no aprobarlo por default.

## Para la demo a Dojo Shoto
Si se quiere mostrar coherencia de marca en la primera demo, el tema por defecto puede tomar prestado el lenguaje de Anton + paleta oscura de la Capa 1 — pero se implementa como una fila más de `tenant_themes` (preset "DojoBase default"), no como hardcoding. En cuanto Dojo Shoto confirme su propia paleta (blanco/rojo/azul), es un cambio de fila, no de código.
