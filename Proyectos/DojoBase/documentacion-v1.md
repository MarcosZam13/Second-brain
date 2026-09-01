---
proyecto: DojoBase
tema: Documento de proyecto — requerimientos, alcance, arquitectura y plan
fecha: 2026-08-28
tipo: documentacion
estado: v1.0 — reemplaza al spec 06, con las 7 decisiones del 2026-08-28 ya aplicadas
tags: [dojobase, requerimientos, producto, saas]
---

# DojoBase — Documento de proyecto (v1.0)

Ver también: [[Proyectos/DojoBase/README|README]] · [[Proyectos/DojoBase/historias-usuario|historias-usuario.md]] · [[Proyectos/DojoBase/schema-dojo|schema-dojo.md]] · [[Proyectos/CoreBase/arquitectura|arquitectura.md]] · [[Proyectos/CoreBase/schema|schema.md]] · [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]] · [[Proyectos/CoreBase/revision-critica-specs|Revisión crítica]]

> Reemplaza a `_fuentes/06-historias-usuario-requerimientos.md`, que mezclaba documento de producto e historias de usuario en un solo archivo y sin criterios de aceptación. Acá se separan, como en Tacha: este documento es la fuente de los **requerimientos**; [[Proyectos/DojoBase/historias-usuario|historias-usuario.md]] es el desglose de trabajo en épicas/HU/CA.

## 1. Resumen ejecutivo

DojoBase es una aplicación SaaS multi-tenant para academias de artes marciales, multi-disciplina (karate, BJJ, MMA, krav magá, extensible sin cambios de schema). Se construye sobre [[Proyectos/CoreBase/README|CoreBase]] como producto independiente, con su propia app, su propia base de datos y su propia identidad comercial.

Resuelve: gestión de miembros, clases con asistencia por inscripción, rangos y promociones independientes por disciplina, retos amistosos de sparring con resultado por rounds e historial cruzado, historial de peleas oficiales con feed de próximas peleas, contenido educativo por carpetas, challenges de gamificación, y cobro de membresías con verificación de comprobantes SINPE.

**Primer prospecto:** Dojo Shoto, 4 disciplinas. **No es un cliente en operación** — GymBase v1 no está en uso. DojoBase se construye para vendérselo terminado, lo que significa que **la demo es la venta**: el producto tiene que estar presentable el día que se le muestra, no solo funcional. El onboarding de cada dojo es manual (lo configura el equipo), sin registro público self-service en esta versión.

### 1.1 Por qué existe este proyecto

GymBase v1 ya hace casi todo lo que este documento describe — pero no está en uso, y tal como está no es vendible. Lo que hay que resolver para que lo sea:

1. **Un producto que se vea como un producto.** v1 tiene 618 colores hex sueltos, cinco patrones de presentación de formularios, dos arquitecturas de formulario conviviendo y tres implementaciones de modal. Se nota entre pantallas, y se nota el día de la demo.
2. **Onboardear un dojo nuevo sin un deploy.** Hoy cada cliente es una carpeta `clients/gymbase/<tenant>/theme.config.ts` y un build con una variable de entorno. Un dojo nuevo es un PR. Con `tenant_themes` en tabla y el tenant resuelto por JWT, es un insert — y se puede configurar delante del cliente.
3. **Un core reutilizable.** Auth, tenant, roles, billing, theming y UI que sirvan para el siguiente producto sin arrastrar nada de gimnasios ni de dojos.

Lo que sí se conserva de v1 es el **conocimiento de negocio**: qué funciones necesita un dojo de verdad, y cómo se comportan los casos borde. Eso ya pasó por uso real y por la retroalimentación del sensei, y es el activo que evita redescubrirlo.

Criterio para priorizar: primero lo que hace el producto **presentable y onboardeable**, después el porte de funcionalidad.

## 2. Alcance

### 2.1 Incluido en el MVP

- Auth, organizaciones y roles (owner/admin/member) resueltos por JWT claim
- Invitación y alta de miembros por parte del admin
- Multi-disciplina con rangos y franjas independientes por arte marcial
- Clases: calendario semanal para el miembro y mensual para el admin, **series recurrentes**, cupos, lista de espera, inscripción como mecanismo de asistencia, corrección de no-show, cancelación de inscripción y de clase completa, clases privadas por plan
- Sparring amistoso completo: reto → aceptación → **sesión con cronómetro por rounds y descanso** → resultado → confirmación del rival → historial head-to-head → expiración automática
- Promociones: eventos, criterios ponderados, calificación, resolución, reapertura, y **portal del miembro** con desglose por criterio
- Historial de peleas oficiales + feed de próximas peleas
- Contenido en carpetas anidadas, con gating por plan y favoritos
- Challenges de asistencia, rutina y peleas amistosas
- Billing: planes, suscripción, comprobante SINPE, revisión por admin, dashboard financiero exclusivo del owner, recordatorios de vencimiento
- Grupos familiares con plan por integrante
- Ficha completa del alumno con generación de ficha para torneo
- Mediciones corporales como módulo opcional por dojo
- Theming dinámico por tenant
- Notificaciones en tres canales — in-app en tiempo real, push y **correo** — con preferencias por tipo de evento
- Anuncios del dojo con comentarios y reacciones
- Kiosco de proyección de torneos en tiempo real
- Exportaciones de reportes en CSV, Excel y PDF
- Página pública del dojo, editable desde la app
- PWA instalable

### 2.2 Fuera de alcance (documentado para no perderlo)

- **Registro self-service de nuevos dojos** — el alta sigue siendo manual (RF-19).
- **App nativa en tiendas** — PWA primero. La arquitectura queda lista para el salto (tenant por JWT, sin dependencia de middleware de framework).
- **Torneos con bracket automático** — el modelo de datos entra, la UI de armado de brackets no. Es lo primero que se prioriza si sobra tiempo, y lo primero que se cae si falta.
- **Todo el perfil de gimnasio de fitness**: check-in por QR, métricas de salud/InBody, fotos de progreso, inventario, ventas, POS y marketplace. Eso es GymBase v2.

### 2.2b Pendiente legal, no técnico

**La facturación electrónica de Costa Rica no se hace hasta que esté la inscripción ante Hacienda**
(decisión del 2026-08-28). Es requisito legal para facturar, no una feature opcional, pero no tiene
sentido construirla antes del trámite. Va en el mismo paquete que la activación del cobro
automático por pasarela, que depende de lo mismo.

La política de privacidad y los términos viven en el landing page, no dentro de la app.

### 2.3 Orden de recorte si el cronograma se atrasa

Decidido de antemano para no improvisarlo bajo presión: **torneos → grupos familiares → challenges**, en ese orden.

## 3. Actores

| Actor | Alcance |
|---|---|
| **Miembro** | Su información, sus clases, sus retos, su historial de rangos y promociones, su membresía y sus pagos |
| **Admin** | Gestión operativa completa: miembros, clases (es también el instructor), contenido, promociones, peleas oficiales, aprobación de comprobantes. Sin acceso a reportes de ingresos |
| **Owner** | Todo lo de admin + dashboard financiero agregado + conexión de pagos + configuración del tema |

**Los tres son la misma persona con más o menos sombreros, no tres audiencias.** En un dojo el sensei entrena, tiene su cinturón y paga su mensualidad como cualquier alumno — GymBase v1 lo confirmó con `admins_pay` y `staff_as_members` en Dojo Shoto. Por eso los roles acumulan y la app es una sola; el detalle de diseño está en la sección 3.5 de [[Proyectos/DojoBase/DESIGN|DESIGN.md]].

**El instructor no es una entidad ni un flag separado**: es un admin de la organización asignado a una clase. Evita modelar una entidad nueva sin ganar nada — todo admin ya tiene los permisos operativos para dar clase.

## 4. Requerimientos funcionales

### Disciplinas y rangos
- **RF-01** — Múltiples disciplinas por organización, cada una con su sistema de rangos independiente.
- **RF-02** — Un miembro puede tener rangos distintos y simultáneos en cada disciplina que practique. `member_ranks` es la única fuente de verdad; no existe rango "general" almacenado.
- **RF-02b** ▲ — **Cada disciplina define cómo se progresa en ella**, entre tres estilos: ascenso directo de un rango al siguiente (karate, krav magá), acumulación de franjas dentro del rango (BJJ), o progresión por tiempo y participación sin escalera de rangos (MMA). El sistema no asume franjas para todas.
- **RF-02c** ▲ — Cada disciplina define también cómo se representa el grado: cinturón, parche o nivel, o ninguna insignia. Es una decisión independiente del estilo de progresión.
- **RF-02d** ▲ — Un rango puede exigir tiempo mínimo en el rango actual y asistencia mínima acumulada antes de habilitar el ascenso.
- **RNF-06 / RF-01b** — Incorporar una disciplina nueva no requiere cambios de schema: es configuración por fila, incluido su estilo de progresión.

### Clases y asistencia
- **RF-03** — La inscripción a una clase es el mecanismo de asistencia; no existe check-in físico ni QR. Al confirmarse la inscripción, la asistencia se marca como presente.
- **RF-03b** ▲ — **El instructor puede corregir la asistencia después de la clase** (marcar no-show). La asistencia sin verificar y la ausencia se distinguen de la presencia confirmada, y **solo la presencia cuenta para la ventana de elegibilidad de promociones**.
- **RF-03c** — El miembro puede cancelar su inscripción liberando el cupo, respetando la antelación mínima configurada. El admin puede cancelar la clase completa, lo que notifica a todos los inscritos.
- **RF-04** — Calendario en vista semanal para miembros y mensual para administradores. El instructor de una clase es siempre un admin de la organización.
- **RF-04b** — Una clase puede restringirse a planes de membresía específicos (clase privada).

### Sparring
- **RF-05** — Todo reto de sparring está asociado a una disciplina específica.
- **RF-05b** ▲ — Un reto define cantidad de rounds, duración de round y descanso. La app provee una **sesión con cronómetro** que recorre round, carga de resultado, descanso y resumen.
- **RF-05c** ▲ — El cronómetro se calcula contra un instante de inicio, de modo que **sigue siendo correcto con la pantalla apagada o la app en segundo plano**, y avisa por sonido y vibración al faltar 10 segundos y al terminar el round.
- **RF-06** — Flujo: creación (challenger) → aceptación o rechazo (rival) → carga de resultados por round (challenger) → cierre con ganador calculado.
- **RF-06a** ▲ — La carga de puntaje se hace con botones de valor directo por peleador, con deshacer de la última anotación. Los valores disponibles se configuran por disciplina (por defecto 1 a 4).
- **RF-06b** ▲ — **El rival confirma el resultado cargado.** El historial head-to-head cuenta únicamente enfrentamientos confirmados; los no confirmados se muestran como pendientes en el detalle del reto.
- **RF-06c** — Cualquiera de los dos participantes puede cancelar un sparring antes de completarse. Un reto `pending` sin respuesta, o `accepted` sin resultado, expira automáticamente tras el plazo configurado (default 14 días).
- **RF-07** — El sistema expone el historial agregado de enfrentamientos entre cualquier par de miembros con sparrings completados y confirmados.
- **RF-08** — Las notificaciones de sparring se entregan in-app en tiempo real y por push.

### Peleas oficiales
- **RF-09** — El registro de peleas oficiales es exclusivo de admin/owner; el miembro solo lee.
- **RF-10** ▲ — Las peleas `upcoming` son visibles para toda la organización en el dashboard, **independientemente de la privacidad del miembro**. Los resultados (`win`/`loss`/`draw`) son **privados por defecto** y entran al feed solo si el miembro los publica.

### Promociones
- **RF-11** — Un evento puede cerrarse sin puntaje de aprobación definido; los candidatos quedan pendientes y **el evento puede reabrirse** para resolverlos manualmente. Ningún candidato queda huérfano de forma permanente.
- **RF-11b** — El puntaje de cada criterio se valida en el servidor contra el `max_score` **real de ese criterio**, nunca contra un rango fijo genérico.
- **RF-11c** ▲ — **Un candidato con criterios sin calificar se marca como evaluación incompleta**, y la resolución automática lo excluye en vez de aprobarlo sobre una base parcial más favorable. El admin puede resolverlo a mano, viendo el aviso.
- **RF-11d** ▲ — **Un candidato ya resuelto no admite edición de puntajes.** Para corregir hay que revertir la decisión primero, de modo que el puntaje final almacenado y el mostrado nunca divergen.
- **RF-11e** — Eliminar un criterio o retirar un candidato solo es posible con el evento en borrador, validado en el servidor.
- **RF-12** — El miembro consulta su propio historial de promociones, su rango actual por disciplina y el desglose de su calificación por criterio, sin intervención de un admin.
- **RF-12b** — El ascenso solo modifica el rango de la disciplina evaluada; no altera rangos ni franjas de otras disciplinas del miembro.

### Perfil del alumno y mediciones
- **RF-12c** ▲ — El sistema mantiene una **ficha completa del alumno** con los datos que exige una inscripción a torneo: identificación, fecha de nacimiento, contacto de emergencia, tipo de sangre, datos del tutor si es menor, federación, seguro deportivo y categoría de peso.
- **RF-12d** ▲ — El sistema **señala los campos faltantes** de la ficha antes de que hagan falta, y puede **generar la ficha lista para inscripción** combinando datos personales, rango vigente por disciplina, peso más reciente y récord competitivo.
- **RF-12e** ▲ — El registro de mediciones corporales (peso, estatura, porcentaje de grasa y de masa muscular, más métricas extendidas) es un **módulo opcional que cada organización activa o no**. Cuando está activo, el peso más reciente alimenta la ficha de competencia.
- **RF-12f** ▲ — La disponibilidad de cada módulo opcional se resuelve por configuración de la organización, sin despliegues ni ramas de código por cliente.

### Clases recurrentes
- **RF-04c** ▲ — Una clase puede crearse como **serie recurrente** con días, hora y fecha de fin. Editar la serie afecta solo a las ocurrencias futuras que no se hayan editado aparte; cancelar una ocurrencia no rompe la serie; eliminar la serie nunca borra ocurrencias pasadas con asistencia registrada.

### Comunidad
- **RF-13c** ▲ — El dojo publica anuncios con portada, categoría y opción de fijarlos; los miembros comentan y reaccionan. **Publicar es exclusivo de admin y owner** — es un tablón de anuncios, no un foro abierto. El admin puede ocultar un comentario sin borrarlo.

### Contenido y challenges
- **RF-13** — Contenido organizado en carpetas anidadas configurables por admin/owner, con visibilidad por plan de membresía.
- **RF-13b** — El miembro puede marcar contenido como favorito.
- **RF-14** — Challenges de al menos tres tipos: asistencia, cumplimiento de rutina y participación en peleas amistosas.

### Billing
- **RF-15** ▲ — **El admin puede aprobar o rechazar comprobantes de pago y ve el monto de la fila que revisa** (el comprobante SINPE lo muestra en la imagen), **pero no accede a reportes ni dashboards de ingresos agregados**.
- **RF-16** — Solo el owner accede al dashboard financiero agregado y a la configuración de conexión de pagos.
- **RF-17** ▲ — El sistema notifica en tres canales — in-app, push y **correo** — según el tipo de evento, sin duplicar envíos. Los avisos de **pago** (por vencer, vencido, comprobante aprobado o rechazado) y el **resultado de promoción** van siempre por correo: un push se ignora y no llega si el alumno desinstaló la app.
- **RF-17b** ▲ — El miembro elige qué canales quiere para cada tipo de evento. Sin esa opción, la única salida de alguien saturado es bloquear las notificaciones del navegador, y ahí pierde también las que le importan.
- **RF-17c** ▲ — Existe un recordatorio de clase próxima con antelación configurable por clase.
- **RF-18** — Cada organización configura su tema visual (colores, logo, tipografía, radio de bordes) sin cambios de código.
- **RF-18b** ▲ — Al crear una disciplina, el sistema ofrece **escalas de rangos precargadas** editables, para no cargar veinte cinturones a mano.
- **RF-18c** ▲ — El dojo tiene una **página pública editable desde la app** (historia, instructores, programas, logros, ubicación). Editable desde la app, no por código: de lo contrario cada dojo nuevo vuelve a ser un despliegue.
- **RF-18d** ▲ — Los reportes del owner se exportan en CSV, Excel y PDF.
- **RF-18e** ▲ — La política de privacidad y los términos de servicio viven en la **landing page** (repo propio `dojobase-landing`, ver [[Proyectos/DojoBase-Landing/README|DojoBase Landing]]), y la app enlaza a ellos. Siguen siendo bloqueantes del primer cobro.
- **RF-22** — El flujo de billing completo: definición de planes por admin/owner → elección y suscripción por el miembro → subida de comprobante → revisión por admin, con motivo visible en caso de rechazo.
- **RF-22b** — El modo de cobro es configuración por organización. El MVP opera en **comprobante SINPE manual**; el cobro automático por pasarela (ONVO, modelo de marketplace) queda modelado y se activa por configuración, sin cambios de código ni de historial. Ver [[Proyectos/CoreBase/billing-onvo|billing-onvo.md]].
- **RF-21** — Grupos familiares con plan por integrante, cobrados como unidad.

### Vistas por rol
- **RF-23** — Los roles **acumulan**: instructor es alumno más operación, y dueño es instructor más negocio. La aplicación es una sola y la navegación suma secciones según el rol; no hay portales separados. El inicio de un miembro del staff es su inicio personal, con un bloque de gestión debajo.
- **RF-23b** — El staff puede mirar la app como la ve un alumno. Es una preferencia de interfaz y **no altera permisos**: el rol real se conserva y el servidor responde según él.

### Alta y acceso
- **RF-19** — El alta de una organización nueva es un proceso manual del equipo, no un autoregistro.
- **RF-20** — Un admin invita miembros a una organización existente por código de invitación o alta directa, sin registro público abierto.

## 5. Requerimientos no funcionales

- **RNF-01** — Toda mutación de estado sensible (promociones, resultados de sparring, decisiones de pago) se valida en el servidor. Ocultar un control en la UI no es un control de acceso.
- **RNF-02** — La resolución de tenant funciona vía JWT claims, sin depender de middleware de un framework específico, para permitir portabilidad futura a mobile nativo.
- **RNF-03** — Ningún componente de UI compartido contiene colores ni medidas hardcodeadas; todo resuelve contra tokens del tenant activo. Se verifica con regla de lint en CI, no por convención.
- **RNF-04** — Prácticas OWASP 2025 para aplicaciones web multi-tenant con datos sensibles. Toda tabla nueva nace con RLS habilitada y policy de aislamiento por organización.
- **RNF-05** — PWA instalable, sin dependencia de tienda de aplicaciones para el lanzamiento.
- **RNF-06** — Incorporar disciplinas nuevas es configuración por fila, no por columna ni por migración.
- **RNF-07b** ▲ — **Ninguna regla de negocio depende del tiempo real.** Cupos, estados y permisos se validan siempre en el servidor; el vivo es una mejora de percepción. Toda pantalla en vivo tiene que ser correcta sin él, y todo canal reporta su estado de conexión en vez de fallar en silencio — que es exactamente cómo GymBase v1 pasó un año con el tiempo real roto sin un solo error en consola.
- **RNF-07** ▲ — La app prioriza ligereza sobre impacto visual: sin scroll-jacking, sin parallax de capas, sin animaciones de más de 400 ms en flujos de uso diario. Debe funcionar bien en mobile de gama media con conexión inestable.
- **RNF-08** ▲ — Un solo patrón por tipo de interacción. Todo formulario es `FormModal`, `FormPage` o `ConfirmDialog`; Sheet/Drawer no existe como categoría. Toda arquitectura de formulario es React Hook Form + Zod.

## 6. Modelo de datos

Repartido en dos documentos según la capa:

- **Core y módulos compartidos** — [[Proyectos/CoreBase/schema|CoreBase/schema.md]]: identidad, organizaciones, invitaciones, theming, billing, grupos familiares, notificaciones, clases, contenido, rutinas, challenges.
- **Vertical** — [[Proyectos/DojoBase/schema-dojo|schema-dojo.md]]: configuración del dojo, disciplinas, rangos, sparring, promociones, peleas oficiales, torneos. Incluye la resolución de los 11 casos borde de la lógica de promociones de v1.

La seguridad de acceso (JWT, helpers, RLS por tabla, matriz de acceso) está en [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]].

## 7. Arquitectura

Detalle completo en [[Proyectos/CoreBase/arquitectura|CoreBase/arquitectura.md]]. En una línea: monorepo `corebase` (Turborepo + pnpm) con `apps/dojobase` sobre `packages/core`, `packages/ui`, `packages/modules` y `packages/config`; Next.js App Router + Supabase; tenant y rol por JWT claim; theming por tabla; un proyecto de Supabase por producto.

Las dos reglas que sostienen la separación y se verifican en CI: `packages/core` y `packages/ui` no pueden nombrar nada de un vertical, y una app nunca importa de otra app.

## 8. Dirección de diseño

Dos capas que no se mezclan (ver `_fuentes/08b-identidad-marca-vs-theming.md`):

- **Identidad de DojoBase** — la marca del producto: landing de venta, paleta fija de alto contraste, tipografía de display, animación libre. Vive en el repo `dojobase-landing` (ver [[Proyectos/DojoBase-Landing/README|DojoBase Landing]]) y **no se importa desde la app**.
- **Theming del tenant** — los colores del dojo, en `tenant_themes`. Todo color de la app resuelve contra `var(--color-*)`, nunca contra la paleta de la marca.

Lo que sí cruza de la marca a la app, con reglas: la tipografía de display en **máximo 3 o 4 momentos de alto impacto** (modal de "¡Promovido!", resultado de sparring ganado, título del feed de próximas peleas) y nunca en formularios ni tablas; micro-animaciones de confirmación de logro, cortas y nativas; y la paleta oscura como **preset opcional** de `tenant_themes`, no como default.

**Pendiente y bloqueante de la UI:** falta el `DESIGN.md` — inventario de pantallas por rol, navegación, estados y prompt por pantalla, con el formato del de [[Proyectos/Tacha/DESIGN|Tacha]]. Sin él, "mejorar la UI" vuelve a ser improvisación pantalla por pantalla, que es exactamente cómo v1 llegó a tener cinco patrones de formulario.

## 9. Plan de trabajo

El cronograma de 8 semanas del spec 07 se reordena en cuatro bloques, priorizando lo que hace el producto vendible antes que el porte de funcionalidad:

| Bloque | Foco | Entregable |
|---|---|---|
| **0 — Fundación** | Monorepo, CoreBase (auth/tenant/JWT/RLS/billing), design system con tokens y catálogo cerrado de componentes, `DESIGN.md` | Login con claim de org y rol, `packages/ui` verificado con dos temas distintos, tests de RLS de la matriz de acceso |
| **1 — Lo vendible** | Theming por tenant, alta de organización, invitación de miembros, disciplinas y rangos | **Un dojo nuevo se onboardea sin un deploy.** Es el hito de negocio |
| **2 — Porte de funcionalidad** | Clases y asistencia → sparring completo → promociones y portal del miembro → billing → contenido y challenges → peleas oficiales y grupos familiares | Paridad con lo que Dojo Shoto usa hoy, reescrito limpio |
| **3 — Venta** | Seed de demo con los datos de Dojo Shoto (disciplinas, cinturones, clases de ejemplo), hardening OWASP completo, landing de venta | Demo lista para presentar y cerrar el primer cliente |

Las semanas 3 y 4 del cronograma original (disciplinas/rangos y clases) siguen siendo **bloqueantes de casi todo lo posterior**: sparring, promociones y peleas dependen de que existan disciplinas y rangos. No conviene adelantar sparring si esa base no cerró limpio.

**GymBase v1 no se toca en absoluto** — está archivado, sin uso y sin datos. No hay migración, no hay corte y no hay dos productos que mantener.

**Modelo de agentes** (spec 07): un orquestador que mantiene el contexto completo y delega, más subagentes de contexto acotado — UI/componentes, QA/testing contra RF como criterios de aceptación, seguridad OWASP que revisa **antes de mergear** y no como auditoría final, y documentación que cierra cada tarea con el `CLAUDE.md` del paquete que tocó.

## 10. Decisiones técnicas clave

| Decisión | Alternativas | Elegida | Razón |
|---|---|---|---|
| Punto de partida | Evolucionar GymBase v1, construir desde cero | **Desde cero** | v1 arrastra 618 hex sueltos, 5 patrones de formulario y 3 de modal. Es proyecto personal: el costo de empezar limpio es tiempo, y compra consistencia real |
| Arquitectura de producto | Feature flags sobre app única, apps separadas sobre core | **Apps sobre core** | Los flags ya están construidos y funcionan, pero perpetúan el patrón que generó la deuda |
| Resolución de tenant | Header custom + middleware, JWT claim | **JWT claim** | Elimina dependencia de framework y habilita mobile sin rediseño. Costo aceptado: desfase de rol hasta el refresh, mitigado con TTL corto y verificación en vivo para finanzas |
| Base de datos | Una compartida entre productos, una por producto | **Una por producto** | Mezclar dojos y gimnasios recrea el acoplamiento del que se sale |
| Rango del miembro | Columna denormalizada, tabla por disciplina | **Tabla por disciplina** | La denormalizada de v1 se desincronizaba y su resincronización borraba franjas de disciplinas ajenas |
| Theming | Archivo de config por tenant, tabla | **Tabla** | Onboardear pasa de requerir un deploy a requerir un insert. Es el hito de negocio |
| Visibilidad de finanzas | Admin con vista agregada, admin ciego a montos, **admin sin reportes** | **Sin reportes** | Ciego a montos no era exigible: el comprobante SINPE muestra el monto en la imagen que el admin debe revisar. Se prefiere un control real y honesto a uno declarativo |
| Validación de puntaje | Constraint de DB, validación de aplicación | **Aplicación** | Deja abierto el puntaje bonus sin migración |
| Concepto de instructor | Flag nuevo, tabla propia, admin existente | **Admin existente** | No modela una entidad sin ganar nada |
| Progresión de rangos | Franjas para todas las disciplinas, **estilo configurable por disciplina** | **Configurable** | Solo BJJ usa franjas; karate asciende directo y MMA no usa cinturones. Asumir un solo modelo le inventa a la escuela un sistema que no tiene |
| Mediciones corporales | Fuera de alcance (perfil de gimnasio), **módulo opcional** | **Módulo opcional** | Un dojo también las quiere: la categoría de peso para competir depende del peso actual |
| Feature flags | Config de build por cliente (v1), **filas de módulos por organización** | **Filas por organización** | Los flags de v1 ramificaban lógica de negocio y exigían un despliegue por cliente. Estos solo prenden o apagan un módulo que ya vive aislado |
| Comunidad | Foro abierto, **tablón de anuncios con comentarios** | **Tablón** | Un foro libre exige moderación, reportes y reglas de convivencia — tres funciones fuera de alcance. Un dojo usa el canal para avisar, no para debatir |
| Marcador de sparring | Formulario posterior, **sesión con cronómetro** | **Sesión con cronómetro** | v1 ya lo resuelve así y ningún spec lo había recogido: se anota durante el round, no después |
| Proyección de torneo | Polling cada 15 s (v1), **Realtime** | **Realtime** | Un marcador proyectado que tarda 15 segundos en actualizarse se nota desde el otro lado del gimnasio |
| Asistencia | Solo inscripción, inscripción + no-show corregible | **Inscripción + no-show** | La elegibilidad para ascender de cinturón se calcula sobre asistencia; sin corrección, se infla. En un dojo el cinturón es la reputación de la escuela |
| Resultado de sparring | Auto-reportado por el challenger, **confirmado por el rival** | **Confirmado** | El head-to-head es social; un marcador de una sola parte no sobrevive al primer conflicto |
| Historial de peleas | Público por default, **privado por default** | **Privado** | El feed social se sostiene con `upcoming` siempre visible; el resultado es del miembro |
| Expiración de sparring | Sin expiración, automática por tiempo | **Automática** | Evita acumulación de retos fantasma. Un solo job diario para esto, recordatorios de pago y expiración de suscripciones |
| Notificación push | Heurística de sesión activa, insertar y pushear siempre | **Siempre, con dedupe en cliente** | La heurística requiere Realtime Presence: infra completa para un comportamiento que se resuelve marcando leída |
