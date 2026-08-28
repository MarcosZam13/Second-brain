---
proyecto: CoreBase
tema: Billing — modelo de cobro, ONVO Pay y camino del MVP a pagos automáticos
fecha: 2026-08-28
tipo: documentacion
estado: v1.0 — investigación de ONVO cerrada, modelo de datos validado
tags: [corebase, billing, onvo, pagos, sinpe]
---

# Billing — modelo de cobro y ONVO Pay

Ver también: [[Proyectos/CoreBase/schema|schema.md]] · [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]] · [[Proyectos/CoreBase/arquitectura|arquitectura.md]] · [[Proyectos/DojoBase/documentacion-v1|DojoBase — documentación]]

> Cierra la pregunta abierta E6 de la [[Proyectos/CoreBase/revision-critica-specs|revisión crítica]]: *¿ONVO soporta conexión por comercio, o exige contrato de agregador?* **Sí lo soporta**, con un modelo de marketplace tipo Stripe Connect. El modelo de datos del spec era correcto; queda enriquecido con los campos reales de la API.

## 1. La respuesta corta

ONVO tiene un producto de **marketplace** en el que una plataforma (CoreBase) crea y administra *connected accounts* para cada comercio (cada dojo/gym), y enruta los cobros a la cuenta correcta. La plataforma se queda con una comisión configurable, o con una tarifa fija semanal, o ambas.

Esto valida `org_payment_connections` tal como estaba diseñada. Lo que cambia es que ahora se conocen los campos y estados reales, en vez de suponerlos.

## 2. Cómo funciona el modelo de marketplace

| Pieza | Cómo opera |
|---|---|
| **Claves de API** | **Siempre las de la cuenta primaria** (la de CoreBase). ONVO no emite claves por comercio conectado — la plataforma es el único que habla con la API |
| **Alta de un comercio** | `POST /v1/connected-accounts` con `businessName` (1-50 caracteres) y opcionalmente `marketplaceAppFee` (porcentaje 0-100, dos decimales) |
| **Identificador** | La respuesta trae un `id` inmutable (ej. `cl502zv0d0127ebdp3zt27651`) que la plataforma guarda y usa para enrutar |
| **Onboarding** | La creación devuelve un `onboardingUrl` **alojado por ONVO**. El dueño del dojo lo abre, hace su KYC y registra el IBAN donde quiere sus liquidaciones. El enlace vence a los 7 días y se regenera con `POST /v1/connected-accounts/{id}/onboarding-link` |
| **Enrutar un cobro** | Se crea el payment intent con las claves de la plataforma más el atributo **`onBehalfOf`** = id de la cuenta conectada. ONVO aplica la división de comisiones automáticamente |
| **Comisión de la plataforma** | `marketplaceAppFee` (porcentaje por transacción) y/o tarifa fija semanal vía `POST /v1/connected-accounts/{id}/weekly-fees` — `marketplaceWeeklyFeeEnabled`, `marketplaceWeeklyFeeAmount` (entero en unidades menores), `marketplaceWeeklyFeeCurrency` (USD, CRC, GTQ, PEN) |

**Estados de una cuenta conectada:** `pending_onboarding`, `awaiting_approval`, `active`, `inactive`, `temporally_suspended`, `permanently_suspended`, `deleted`.

### La tarifa semanal fija es el hallazgo más útil

Para un SaaS, cobrarle al dojo una mensualidad por usar DojoBase es un problema aparte del de cobrarle al alumno su membresía. `marketplaceWeeklyFee` resuelve el primero **dentro del mismo sistema**: ONVO puede retener una tarifa fija semanal de las liquidaciones del dojo. No hay que montar un segundo mecanismo de cobro para el propio SaaS.

### Otros recursos de la API que sirven después

`Subscriptions` ("Cargos Recurrentes"), `Products`, `Prices`, `Invoices` ("Renovaciones"), `Checkout Sessions`, `Coupons` y **SINPE Móvil como método de pago nativo**. Es decir: el día que el cobro sea automático, la membresía recurrente del alumno también puede vivir en ONVO en vez de reimplementarse.

### Costos de referencia (verificar al contratar)

Tarjeta 3.9% + $0.25 · SINPE 1.5% · transferencia SINPE con IBAN 1.5% + $0.50. El SINPE nativo sale considerablemente más barato que la tarjeta, lo cual importa en un mercado donde el alumno paga por SINPE Móvil de todos modos.

## 3. Qué hace falta del lado del negocio

Para ser la cuenta primaria del marketplace hay que estar **inscrito ante Hacienda** (persona física con actividad económica o persona jurídica) y tener cuenta bancaria a ese nombre — es el requisito estándar de cualquier afiliación de comercio en Costa Rica, no algo particular de ONVO. Los requisitos específicos de ONVO conviene confirmarlos directamente con ellos al momento de contratar; su documentación pública no detalla criterios de aprobación ni KYC del marketplace.

**Esto es lo único que bloquea los pagos automáticos, y es trámite, no desarrollo.**

## 4. Decisión: el MVP cobra manual, con el enchufe ya puesto

El MVP **no integra ONVO**. Cobra por comprobante SINPE manual, que es como opera hoy en la práctica: el alumno transfiere al SINPE del dojo, sube la foto del comprobante, el admin lo aprueba.

Razones:

1. La integración depende de un trámite de Hacienda que todavía no está hecho — no se bloquea el producto por eso.
2. Un dojo pequeño puede no querer la comisión: el comprobante manual le cuesta 0%. Que sea **opcional por dojo** es una ventaja comercial, no una limitación.
3. El flujo manual hay que tenerlo igual como respaldo (un pago que falla, un alumno que paga en efectivo).

Pero el schema y el código quedan **listos para el enchufe**, de modo que activarlo sea configuración y no una refactorización:

```sql
org_payment_connections (
  org_id              uuid primary key references organizations on delete cascade,
  provider            text not null default 'onvo' check (provider in ('onvo')),
  provider_account_id text,                    -- id de la cuenta conectada de ONVO
  status              text not null default 'not_connected'
                      check (status in ('not_connected','pending_onboarding','awaiting_approval',
                                        'active','inactive','suspended','disconnected')),
  app_fee_percent     numeric(5,2),            -- marketplaceAppFee
  onboarding_url      text,                    -- vence a los 7 días
  onboarding_expires_at timestamptz,
  connected_at        timestamptz,
  updated_at          timestamptz default now()
)
```

Los estados replican los de ONVO más `not_connected`, que es el estado de todo dojo en el MVP.

**El modo de cobro es una propiedad de la organización**, no del código:

```sql
-- en dojo_org_settings (o su equivalente por vertical)
payment_mode text not null default 'manual_sinpe'
  check (payment_mode in ('manual_sinpe','onvo'))
```

Con `manual_sinpe` el miembro ve los datos SINPE del dojo y sube su comprobante. Con `onvo` ve un botón de pago. **La misma pantalla, la misma tabla `payment_proofs`, dos caminos** — porque un pago aprobado por ONVO se registra igual como comprobante verificado, con `proof_url` apuntando al recibo del proveedor en vez de a una foto.

Eso es lo que hace que activar ONVO no toque el historial, ni los reportes financieros del owner, ni la lógica de vencimiento de membresías.

## 5. Cómo se ve la activación cuando llegue

1. El owner entra a la configuración de pagos de su dojo y toca "conectar pagos automáticos".
2. El servidor llama `POST /v1/connected-accounts` con el nombre del dojo y la comisión pactada, guarda el `provider_account_id` y redirige al `onboardingUrl`.
3. El dueño del dojo completa el KYC y su IBAN en la página de ONVO.
4. Un webhook (o un chequeo del estado de la cuenta) mueve `status` a `active`, y `payment_mode` puede pasar a `onvo`.
5. A partir de ahí, cada cobro se crea con `onBehalfOf` y la liquidación llega a la cuenta del dojo.

**Nada de esto entra al MVP.** Está escrito para que cuando entre, sea una feature de dos días y no un rediseño.

## 6. Lo que hay que confirmar con ONVO antes de integrar

- Requisitos y tiempos de aprobación para habilitar el marketplace en la cuenta primaria.
- Si la comisión de la plataforma puede ser 0% (para un dojo que solo quiere la pasarela sin pagar comisión a CoreBase).
- Webhooks disponibles para el cambio de estado de una cuenta conectada y para el resultado de un cobro.
- Comportamiento de reembolsos y contracargos en el modelo de marketplace.
- Si `Subscriptions` funciona con `onBehalfOf`, que es lo que determina si la membresía recurrente puede vivir en ONVO o hay que seguir manejándola en la app.

## Fuentes

- [ONVO Docs — Marketplaces](https://docs.onvopay.com/en/payments/marketplaces)
- [ONVO Docs — API](https://docs.onvopay.com/en/api)
- [ONVO Pay — sitio oficial](https://onvopay.com/)
