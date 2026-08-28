---
proyecto: CoreBase
tema: Realtime — por qué falló en GymBase v1 y cómo se construye acá
fecha: 2026-08-28
tipo: analisis
estado: diagnóstico cerrado · spike CORRIDO Y APROBADO el 2026-08-28
tags: [corebase, realtime, supabase, arquitectura]
---

# Realtime — diagnóstico y plan

Ver también: [[Proyectos/CoreBase/arquitectura|arquitectura.md]] · [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]] · [[Proyectos/CoreBase/schema|schema.md]] · [[Proyectos/DojoBase/repaso-gymbase|repaso-gymbase.md]]

> En GymBase v1 el tiempo real **nunca funcionó**: los retos de sparring y las notificaciones no aparecían, había que recargar la página. Este documento explica por qué, y define qué se hace distinto — incluida la prueba que hay que correr **antes** de que ninguna funcionalidad dependa de esto.

## 1. Lo que estaba bien

Conviene descartar primero las causas habituales, porque en v1 **ninguna aplica**:

- Las tablas **sí** estaban en la publicación (`ALTER PUBLICATION supabase_realtime ADD TABLE member_sparrings, notifications`).
- **Sí** tenían `REPLICA IDENTITY FULL`, que es lo que hace falta para filtrar por columnas que no son la llave primaria.
- El código de suscripción **es correcto**: canal por usuario, `postgres_changes`, filtro por columna existente.

O sea: no fue un descuido de configuración. Es algo más de fondo.

## 2. La causa: el RLS de v1 es inalcanzable desde Realtime

Antes de emitir un cambio, el servidor de Realtime **asume la identidad de cada cliente suscrito y corre una consulta interna** para ver si las policies de RLS le permitirían ver esa fila. Si no, no le manda nada.

Y acá está el problema. En GymBase, casi todas las policies pasan por:

```sql
get_user_org_id()  →  current_setting('request.headers')->>'x-org-id'
```

Ese header lo inyecta el **middleware de Next.js** en cada petición HTTP. Pero **una conexión de Realtime es un WebSocket contra el servidor de Supabase: no pasa por el middleware de Next.js**. En la comprobación interna de Realtime, `request.headers` no existe, `get_user_org_id()` devuelve `NULL`, y **toda policy org-scoped deniega**.

Resultado: Realtime evalúa, decide que ese usuario no puede ver la fila, y **no emite nada**. Sin error, sin advertencia, sin nada en consola. Exactamente el síntoma: "nunca me salían los retos".

Es la misma trampa que la auditoría original ya había marcado como el acoplamiento oculto crítico del proyecto — *"sin replicar exactamente ese mecanismo, cualquier app nueva verá cómo Supabase deniega todo silenciosamente"*. Lo que no se había notado es que **Realtime es justamente una de esas "apps nuevas"**: es un cliente que no puede replicar el middleware.

### La causa secundaria, para las notificaciones

`notifications` es la excepción: su policy es `user_id = auth.uid()`, sin org. Esa sí podría funcionar. Que tampoco anduviera apunta al segundo problema clásico: **el socket se conecta antes de que la sesión esté cargada**, y se autentica con la clave anónima. Ahí `auth.uid()` es `NULL`, la policy deniega igual, y el canal **no se vuelve a suscribir solo** cuando el token aparece.

### Y el detalle que lo volvió invisible

En v1 el código llama `.subscribe()` **sin callback de estado**. La librería avisa cuando un canal entra en `CHANNEL_ERROR` o `TIMED_OUT`, pero si nadie escucha, un canal que jamás se suscribió se ve idéntico a uno suscrito sin novedades. Un año de "no funciona" sin un solo mensaje de error.

## 3. Qué cambia en CoreBase

### La decisión de JWT ya arregla la causa principal

`public.org_id()` lee `auth.jwt()`, no un header HTTP. La comprobación interna de Realtime **sí lleva el JWT del suscriptor**, así que la policy resuelve igual que en una consulta normal. Mover el tenant al claim no era solo por portabilidad a mobile: **también es lo que hace posible el tiempo real**.

Es un buen ejemplo de por qué valía la pena reescribir en vez de portar: el bug no estaba en el código de Realtime, estaba en el mecanismo de tenant que lo rodeaba.

### Broadcast desde la base, no `postgres_changes`

Para los flujos que importan (retos de sparring, resultado de promoción, marcador proyectado) se usa **Broadcast desde la base**: un trigger llama `realtime.broadcast_changes()` y publica en un canal privado, con autorización por policy sobre `realtime.messages`.

Tres razones:

1. **La autorización es explícita y testeable.** Una policy sobre `realtime.messages` dice quién puede escuchar qué canal. Con `postgres_changes`, la autorización es una impersonación implícita por fila que, cuando falla, **falla en silencio** — que es exactamente cómo llegamos acá.
2. **Es lo que Supabase recomienda** para la mayoría de los casos, y lo que escala: `postgres_changes` tiene límites a partir de unos 3.000 suscriptores concurrentes sobre el mismo cambio.
3. **Se elige qué se emite.** Un cambio en la fila no tiene por qué mandar la fila entera: al proyector del torneo le mandás el marcador, no el registro completo.

`postgres_changes` queda para lo simple y poco sensible, si hace falta.

### Nunca más un canal mudo

Regla de código, no de buena voluntad:

- **Todo `.subscribe()` lleva callback de estado**, y `CHANNEL_ERROR` o `TIMED_OUT` se reportan al monitoreo de errores. Un canal que no conecta tiene que doler.
- La UI muestra el estado de conexión donde importa (el marcador proyectado dice si perdió el vivo), en vez de mostrar datos viejos como si fueran actuales.
- **Toda pantalla en vivo funciona sin el vivo.** Realtime acelera la actualización; no es el único camino por el que llegan los datos. Si el canal cae, un refresco periódico suave mantiene la pantalla correcta. Es lo que evita que un problema de infraestructura se vea como un producto roto.
- Los canales se suscriben **después** de que la sesión está lista, y se vuelven a suscribir al refrescarse el token.

## 4. El spike — corrido y aprobado (2026-08-28)

**Resultado: pasa.** Tres corridas seguidas contra el proyecto nuevo, con dos usuarios reales de dos organizaciones distintas:

| Criterio | Objetivo | Medido |
|---|---|---|
| Entrega en vivo | < 1 s | **227 · 236 · 280 ms** |
| Aislamiento entre organizaciones | cero fugas | **0 mensajes** recibidos por el usuario de la otra organización |
| Rechazo del canal ajeno | explícito, no silencioso | `CHANNEL_ERROR` con el motivo: *"Unauthorized: You do not have permissions to read from this Channel topic"* |
| Reconexión tras corte de red | automática | canal de vuelta en `joined` |

Más 10 pruebas de RLS con claims simulados, todas correctas — incluida la del **claim falsificado**: alguien que se declare `owner` en su token no pasa `is_owner_live()`, que consulta la tabla.

El contraste con v1 es el punto: allá el fallo era **silencioso**; acá el rechazo trae motivo. Esa diferencia es la que convierte un año de "no sé por qué no anda" en un mensaje de error.

La prueba quedó como test reejecutable en `tests/realtime/` del repo, con su andamiaje y su rollback.

### Un detalle que costó descartar

En una corrida apareció un `CHANNEL_ERROR` inicial que se resolvía solo. La sospecha era la carrera entre el socket y el token — la segunda causa del fallo de v1 — pero se reprodujo cinco veces seguidas sin fallar, así que no era eso: es el **arranque en frío** del contenedor de Realtime la primera vez que el proyecto lo usa.

De ahí sale una regla para el código de la app: **un `CHANNEL_ERROR` seguido de `SUBSCRIBED` es un canal sano.** Hay que mirar la secuencia de estados, no el primero. Quedarse con el primero hace ver como roto algo que funciona; ignorar el callback, como hacía v1, hace ver como sano algo que nunca conectó.

### Cómo se corrió



Se corrió sobre la capa de identidad recién migrada (las migraciones 001-004), porque el aislamiento no se puede probar sin organizaciones ni membresías.

Objetivo: probar de punta a punta, en el proyecto nuevo, que un cambio hecho por un usuario le llega a otro en menos de un segundo, y que a quien no debe verlo no le llega.

1. Tabla mínima `spike_events (id, org_id, recipient_id, payload)` con RLS igual al patrón real (`org_id = public.org_id()`).
2. El hook `custom_access_token_hook` activo, con `org_id` y `role` en el claim.
3. Trigger con `realtime.broadcast_changes()` a un canal privado por usuario, más la policy de `realtime.messages`.
4. Dos navegadores, dos usuarios de la misma organización. Uno inserta, el otro tiene que verlo sin recargar.
5. **La prueba negativa es la que importa**: un tercer usuario de **otra** organización no debe recibir nada. Si recibe, el aislamiento está roto y eso es peor que no tener tiempo real.
6. Repetir con `postgres_changes` para comparar, y medir latencia real en los dos.
7. Probar los casos feos: token vencido y refrescado, red caída y recuperada, pestaña en segundo plano y de vuelta.

**Criterio de aceptación:** entrega en menos de 1 s en el 95 % de los casos, cero fugas entre organizaciones, y reconexión automática tras 30 s sin red.

**El plan B, que ya no hace falta**: si el spike hubiera fallado, no era pelearse con Supabase: es aceptar que las pantallas se actualicen por refresco periódico corto y avisar por push, y dejar el vivo solo para el marcador proyectado, que es donde de verdad se nota. Se decide con los números del spike, no antes.

## 5. Dónde se usa, en orden de necesidad

| Pantalla | Por qué | Si no hay vivo |
|---|---|---|
| Proyección del torneo en TV | Se ve desde el otro lado del gimnasio. En v1 refrescaba cada 15 s y se notaba | Es la que más lo justifica: acá el plan B es refresco de 3 s, no de 15 |
| Reto de sparring recibido | Hay que responder en el momento | Push + la lista de retos al entrar |
| Marcador de sparring, para el rival | Ve el puntaje mientras el challenger lo carga | Ve el resultado al final |
| Campana de notificaciones | Comodidad | Se actualiza al navegar |
| Cupos de una clase | Evita inscribirse a algo que se acaba de llenar | El servidor rechaza igual al reservar: el vivo es cortesía, no control |

**Ninguna regla de negocio depende de Realtime.** Los cupos, los estados y los permisos se validan siempre en el servidor. El tiempo real es una mejora de percepción — si se cae, la app sigue siendo correcta, solo se siente más lenta. Esa separación es lo que permite lanzar aunque el spike salga regular.

## Fuentes

- [Supabase Docs — Postgres Changes](https://supabase.com/docs/guides/realtime/postgres-changes)
- [Supabase Docs — Broadcast](https://supabase.com/docs/guides/realtime/broadcast)
- [Supabase — Realtime: Broadcast from Database](https://supabase.com/blog/realtime-broadcast-from-database)
- [Supabase Docs — Row Level Security](https://supabase.com/docs/guides/database/postgres/row-level-security)
