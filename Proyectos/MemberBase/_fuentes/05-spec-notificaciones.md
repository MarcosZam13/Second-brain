# Spec Dojo — Sección 5: Módulo de notificaciones compartido

## Punto de partida
Ya existe `NotificationBell.tsx` (Realtime) y `web-push` como dependencia (push). El objetivo es generalizar esto a `packages/shared-modules/notifications`, para que Dojo lo consuma primero (sparring, resultado de promoción, feed de peleas próximas) y GymBase v2 lo reutilice después sin reescribir nada.

## Por qué es shared-module y no core
El mecanismo (Realtime + Web Push) es genérico, pero **qué dispara una notificación y cómo se redacta** es distinto por vertical — Dojo notifica retos de sparring, GymBase notificará vencimiento de membresía. Aplicando la regla de la sección 1: si cambio qué dispara una notificación en Dojo, ¿GymBase se entera? No. Por eso el motor va en shared-modules, no en core.

## Modelo de datos

```sql
-- [shared] tabla genérica de notificaciones in-app
notifications (
  id uuid primary key default gen_random_uuid(),
  org_id uuid references organizations,
  recipient_id uuid references profiles not null,
  type text not null,              -- 'sparring_challenge_received', 'promotion_result', 'fight_upcoming', etc.
  payload jsonb not null,          -- datos específicos del evento (challenge_id, event_id, etc.)
  read_at timestamptz,
  created_at timestamptz default now()
)

-- [core, ya existe] push_subscriptions — con el fix de org_id de la sección 3
push_subscriptions (
  id uuid primary key default gen_random_uuid(),
  member_id uuid references profiles not null,
  org_id uuid references organizations not null,
  endpoint text not null,
  keys jsonb not null,
  created_at timestamptz default now()
)
```

## Contrato del emisor (server-side, un solo punto de entrada)

```ts
// packages/shared-modules/notifications/emit.ts
export async function emitNotification(params: {
  orgId: string;
  recipientId: string;
  type: NotificationType;   // enum específico por app, extensible
  payload: Record<string, unknown>;
}) {
  // 1. Inserta en `notifications` (fuente de verdad in-app)
  // 2. Dispara Realtime (el insert ya lo hace vía postgres_changes, no requiere paso extra)
  // 3. Si el destinatario no tiene sesión activa (heurística: sin conexión Realtime abierta), dispara Web Push
}
```

Este es el único lugar del código que sabe cómo notificar — el server action de `sparring_challenges` (al crear un reto) y el de `promotion_candidates` (al resolver el resultado) solo llaman `emitNotification(...)`, no conocen Realtime ni Web Push directamente. Esto es lo que te permite agregar GymBase después sin tocar el motor.

## Comportamiento específico de Dojo (confirmado en la conversación de negocio)

- **Reto de sparring recibido**: `type: 'sparring_challenge_received'`. Si el destinatario está dentro de la app, aparece como modal/toast inmediato (suscripción Realtime activa en el layout raíz de `apps/dojo`); si no, push. Persiste además en la sección de retos amistosos como pendiente — no desaparece solo por mostrarse una vez.
- **Feed de "próximas peleas"**: no es una notificación 1 a 1, es una consulta directa a `member_fights where result='upcoming'` en el dashboard (sección 2) — no pasa por esta tabla de notificaciones, es informativo pasivo para toda la org, no push individual.
- **Resultado de promoción**: `type: 'promotion_result'`, se dispara cuando `promotion_candidates.status` cambia a `promoted`/`not_promoted` — este es el enganche directo con el portal del miembro (hallazgo §9): la notificación lo lleva a ver su propio historial, que ya quedó habilitado por RLS en la sección 3.

## Componente de UI compartido

```tsx
// packages/ui/NotificationBell.tsx — generalizado desde el original
// Recibe un mapa de "renderers" por tipo, inyectado por cada app:
<NotificationBell
  renderers={{
    sparring_challenge_received: (payload) => <SparringChallengeToast data={payload} />,
    promotion_result: (payload) => <PromotionResultToast data={payload} />,
  }}
/>
```
El componente base (badge, dropdown, marcar como leído) es 100% compartido; cada app solo registra cómo se ve cada tipo de notificación propio.

## Pendiente
Con esto se cierra la parte de arquitectura/schema/RLS/theming/notificaciones (secciones 1-5). El siguiente bloque de trabajo es documentación de producto: historias de usuario y requerimientos con el formato de Tacha (Resumen Ejecutivo → Alcance → Historias de Usuario → RF/RNF → Decisiones Técnicas), y después el plan de agentes + cronograma de 8 semanas.
