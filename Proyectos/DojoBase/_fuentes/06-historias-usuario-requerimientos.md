# Documento de Requerimientos — App Dojo

## 1. Resumen Ejecutivo

Dojo es una aplicación SaaS multi-tenant para academias de artes marciales (multi-disciplina: karate, BJJ, MMA, krav magá, extensible a otras), construida sobre un core compartido con GymBase v2 pero como producto independiente. Resuelve gestión de miembros, clases con asistencia por inscripción, rangos y promociones por disciplina, retos amistosos (sparring) con resultados en tiempo real, historial de peleas oficiales, contenido educativo por carpetas, challenges de gamificación, y cobro de membresías con verificación de comprobantes SINPE vía Onvo. El primer cliente confirmado es Dojo Shoto (4 disciplinas). El onboarding de cada dojo es manual (Marcos configura la organización), no hay registro self-service en esta primera versión.

## 2. Alcance

**Incluido en el MVP (8 semanas):**
- Auth, organizaciones, roles (owner/admin/member) vía JWT
- Multi-disciplina con rangos independientes por arte marcial
- Clases con calendario (semanal para miembro, mensual para admin), cupos, inscripción como mecanismo de asistencia
- Sparring amistoso completo (reto → aceptación → resultado por rounds → historial head-to-head)
- Promociones (eventos, criterios, calificación, portal del miembro)
- Historial de peleas oficiales + feed de próximas peleas
- Contenido por carpetas
- Challenges (asistencia, rutina, peleas amistosas)
- Billing con comprobantes SINPE (revisión de admin, finanzas exclusivas de owner)
- Theming dinámico por tenant
- Notificaciones in-app + push (sparring, promociones, pagos)

**Fuera de alcance del MVP (queda documentado para no perderlo, no se construye ahora):**
- Registro self-service de nuevos dojos (onboarding sigue siendo manual)
- App nativa en Play Store/App Store (PWA-first, arquitectura ya lista para el salto después)
- Torneos como módulo completo de bracket automático (el modelo de datos ya existe en el schema, pero la UI de armado de brackets no entra en las 8 semanas — se prioriza si el tiempo alcanza)

## 3. Historias de Usuario

| # | Actor | Quiero | Para qué | Prioridad |
|---|---|---|---|---|
| HU-00 | Admin/Owner | Crear una disciplina (arte marcial) y definir su escala de rangos (cinturones/franjas) | Tener con qué poblar clases, sparring y promociones — prerequisito de todo lo demás | Alta |
| HU-01 | Miembro | Ver mi horario semanal de clases por disciplina | Saber a qué clases puedo asistir esta semana | Alta |
| HU-02 | Miembro | Inscribirme a una clase con cupo disponible | Confirmar mi asistencia (no existe check-in físico/QR; inscribirse marca `attended = true` automáticamente) | Alta |
| HU-02b | Miembro | Cancelar mi inscripción a una clase | Liberar mi cupo si ya no puedo asistir | Alta |
| HU-02c | Admin | Cancelar una clase completa | Avisar a todos los inscritos cuando la clase no se puede dar (instructor ausente, etc.) | Media |
| HU-03 | Miembro | Ver quiénes más están inscritos en una clase, con su rango en esa disciplina | Saber con quién voy a entrenar | Media |
| HU-04 | Admin | Crear clases asignándome a mí mismo u otro admin como instructor, con disciplina, cupo y horario, viendo el mes completo | Planificar la operación del dojo | Alta |
| HU-05 | Miembro | Retar a otro miembro a un sparring amistoso en una disciplina específica | Competir de forma informal dentro del dojo | Alta |
| HU-06 | Miembro (retado) | Aceptar o rechazar un reto de sparring | Decidir si quiero enfrentarme a esa persona | Alta |
| HU-07 | Miembro (challenger) | Cargar resultados round por round de un sparring aceptado | Dejar registro del enfrentamiento | Alta |
| HU-08 | Miembro | Ver mi historial de enfrentamientos contra un compañero específico (ej. "3-1 contra Fulano") | Llevar cuenta de mi rivalidad histórica | Media |
| HU-09 | Miembro | Recibir notificación inmediata (in-app o push) cuando me retan a sparring | Responder a tiempo sin perder la invitación | Alta |
| HU-09b | Miembro (cualquiera) | Cancelar un sparring propio en cualquier estado antes de completarse | Salir de un reto que ya no quiero sostener | Media |
| HU-09c | Sistema | Expirar automáticamente un sparring `pending` sin respuesta o `accepted` sin resultado cargado tras X días | Evitar retos fantasma acumulándose indefinidamente | Media |
| HU-10 | Admin | Registrar una pelea oficial de un miembro con resultado, método y evento | Mantener el historial competitivo del dojo | Alta |
| HU-11 | Miembro | Ver en el dashboard principal las próximas peleas oficiales de mis compañeros | Sentir que hay actividad competitiva real en el dojo | Media |
| HU-12 | Admin | Crear un evento de promoción con criterios de evaluación por disciplina | Organizar exámenes de cinturón/franja de forma estructurada | Alta |
| HU-13 | Admin | Calificar candidatos por criterio y resolver quién es promovido | Decidir ascensos con base en desempeño objetivo | Alta |
| HU-13b | Admin | Reabrir un evento de promoción cerrado sin `passing_score` que dejó candidatos `pending` | Poder resolverlos manualmente después en vez de que queden huérfanos para siempre | Media |
| HU-14 | Miembro | Ver mi propio historial de promociones, mi rango actual por disciplina, y el desglose de mi calificación por criterio en cada evento | Saber en qué punto estoy y por qué, sin depender del admin — **pantalla nueva, no existe hoy en GymBase** | Alta |
| HU-15 | Admin/Owner | Subir contenido organizado en carpetas (técnica, material de examen, etc.) | Compartir recursos educativos con los miembros | Media |
| HU-15b | Miembro | Marcar contenido como favorito | Volver a encontrarlo fácil después (tabla `content_favorites` ya existe en el core, costo bajo) | Baja |
| HU-16 | Admin | Crear challenges de asistencia, rutina o peleas amistosas | Incentivar la participación activa de los miembros | Media |
| HU-16b | Admin/Owner | Definir planes de membresía (nombre, precio, período) | Tener algo a lo cual el miembro pueda suscribirse | Alta |
| HU-16c | Miembro | Elegir un plan de membresía y suscribirme | Activar mi acceso al dojo | Alta |
| HU-17 | Miembro | Subir mi comprobante SINPE para el plan al que me suscribí | Que el admin pueda verificar mi pago | Alta |
| HU-17b | Miembro | Ver el estado (aprobado/rechazado/pendiente) de mi comprobante SINPE | Saber el estado de mi membresía | Alta |
| HU-18 | Admin | Revisar y aprobar/rechazar comprobantes SINPE, sin ver montos agregados | Gestionar pagos sin acceso a información financiera sensible | Alta |
| HU-19 | Owner | Ver dashboard financiero agregado (ingresos, reportes) | Tomar decisiones de negocio sobre el dojo | Alta |
| HU-20 | Miembro | Recibir recordatorio de pago próximo a vencer | No perder mi membresía activa por olvido | Media |
| HU-21 | Owner/Admin | Configurar el tema visual del dojo (colores, logo) | Que la app refleje la identidad de marca del dojo | Media |
| HU-22 | Admin | Invitar a un miembro nuevo a un dojo ya configurado (código de invitación o alta directa) | Incorporar alumnos sin proceso de registro público | Alta |
| HU-23 | Admin/Owner | Agrupar a varios miembros (ej. hermanos) bajo un grupo familiar con plan compartido | Cobrar un solo plan a familias que entrenan juntas, en vez de suscripciones separadas | Media |

## 4. Requerimientos Funcionales (RF)

- **RF-01**: El sistema debe permitir múltiples disciplinas por organización, cada una con su propio sistema de rangos independiente.
- **RF-02**: Un miembro debe poder tener rangos distintos y simultáneos en cada disciplina que practique.
- **RF-02b**: Cada rango debe soportar acumulación de franjas (`stripes`) antes de ascender al siguiente rango; el umbral de franjas necesarias para ascenso (`stripes_to_promote`) se define por rango, no es fijo global.
- **RF-03**: La inscripción a una clase es el único mecanismo de asistencia (no existe check-in físico/QR); el campo `attended` se marca `true` automáticamente al confirmarse la inscripción, sin paso intermedio de verificación.
- **RF-03b**: Un miembro debe poder cancelar su propia inscripción, liberando el cupo. Un admin debe poder cancelar la clase completa (`is_cancelled`), lo que dispara notificación a todos los inscritos.
- **RF-04**: El calendario de clases debe mostrarse en vista semanal para miembros y vista mensual para administradores. El instructor de una clase es siempre un usuario con rol `admin` de la organización — no se modela como entidad ni flag separado.
- **RF-05**: Un reto de sparring debe estar siempre asociado a una disciplina marcial específica.
- **RF-06**: El flujo de sparring sigue el orden: creación (challenger) → aceptación/rechazo (rival) → carga de resultados por round (challenger) → cierre con ganador calculado.
- **RF-06b**: Cualquiera de los dos participantes puede cancelar un sparring propio antes de que se complete. Un sparring `pending` sin respuesta o `accepted` sin resultado cargado por más de X días (configurable, default sugerido 14 días) expira automáticamente a `cancelled`.
- **RF-07**: El sistema debe calcular y exponer un historial agregado de enfrentamientos (head-to-head) entre cualquier par de miembros que hayan tenido sparrings completados.
- **RF-08**: Las notificaciones de sparring deben entregarse in-app en tiempo real si el usuario está activo, y por push si no lo está.
- **RF-09**: El registro de peleas oficiales es exclusivo de admin/owner; el miembro solo tiene lectura.
- **RF-10**: Las peleas con estado "próxima" (`upcoming`) deben ser visibles para toda la organización en el dashboard principal, independientemente de la configuración de privacidad del miembro.
- **RF-11**: Un evento de promoción puede cerrarse sin puntaje de aprobación definido, sin bloquear el flujo; los candidatos quedan `pending` y el evento puede reabrirse posteriormente por un admin para resolverlos manualmente (no quedan huérfanos de forma permanente).
- **RF-11b**: El puntaje de cada criterio de promoción debe validarse del lado del servidor contra el `max_score` real de ese criterio específico — nunca contra un rango fijo genérico (ej. 0-100).
- **RF-12**: El miembro debe poder consultar su propio historial de promociones, incluyendo el desglose de su calificación por criterio en cada evento en que participó, sin intervención de un admin.
- **RF-13**: El sistema de contenido debe organizarse en estructura de carpetas configurable por admin/owner.
- **RF-14**: Los challenges deben soportar al menos tres tipos: asistencia, cumplimiento de rutina, y participación en peleas amistosas.
- **RF-15**: Un admin puede aprobar o rechazar comprobantes de pago SINPE, pero no puede acceder a reportes de ingresos agregados.
- **RF-16**: Solo el rol owner tiene acceso al dashboard financiero agregado y a la configuración de conexión de pagos (Onvo).
- **RF-17**: El sistema debe enviar recordatorios de pago próximos a vencer vía notificación push/in-app.
- **RF-18**: Cada organización debe poder configurar su propio tema visual (colores, logo, tipografía, estilo de bordes) sin requerir cambios de código.
- **RF-19**: El alta de una nueva organización (dojo) es un proceso manual realizado por el equipo de desarrollo, no un flujo de autoregistro.
- **RF-20**: Un admin debe poder invitar miembros nuevos a una organización ya existente (vía código de invitación o alta directa), sin flujo de registro público abierto.
- **RF-21**: El sistema debe soportar grupos familiares (`family_groups`) con un plan de membresía compartido entre varios miembros de una misma organización.
- **RF-22**: El flujo completo de billing incluye: definición de planes por admin/owner, elección de plan y suscripción por el miembro, subida de comprobante SINPE por el miembro, y revisión (aprobar/rechazar) por admin.

## 5. Requerimientos No Funcionales (RNF)

- **RNF-01**: Toda mutación de estado sensible (promociones, resultados de sparring) debe validarse en el servidor, no depender solo de la ocultación de UI.
- **RNF-02**: El mecanismo de resolución de tenant (organización activa) debe funcionar vía JWT claims, sin depender de middleware específico de un framework, para permitir portabilidad futura a mobile nativo.
- **RNF-03**: Ningún componente de UI compartido debe contener valores de color hardcodeados; todo color debe resolver contra variables de tema del tenant activo.
- **RNF-04**: El sistema debe seguir las prácticas de seguridad OWASP 2025 aplicables a aplicaciones web con datos sensibles multi-tenant (control de acceso, gestión de sesión, validación de entrada del lado servidor).
- **RNF-05**: La app debe funcionar como PWA instalable, sin dependencia de tienda de aplicaciones para el lanzamiento inicial.
- **RNF-06**: El sistema debe soportar la incorporación de nuevas disciplinas marciales sin requerir cambios de schema (configuración por fila, no por columna).

## 6. Decisiones Técnicas Clave

| Decisión | Alternativas consideradas | Elegida | Razón |
|---|---|---|---|
| Arquitectura de producto | (A) Feature flags sobre app única, (B) Apps separadas sobre core compartido | B | A ya está probado en producción (Dojo Shoto) pero perpetúa el patrón que generó la deuda técnica actual |
| Resolución de tenant | Header custom + middleware (actual), JWT claim | JWT claim | Elimina dependencia de framework específico, habilita mobile nativo futuro sin rediseño |
| Rango del miembro | Columna denormalizada `current_rank_id`, tabla `member_ranks` por disciplina | `member_ranks` | Multi-disciplina confirmada hace que un solo rango denormalizado sea insuficiente e inconsistente |
| Theming | Archivo de config por tenant (actual), tabla `tenant_themes` | Tabla | Onboardear un dojo nuevo pasa de requerir deploy a requerir un insert |
| Validación de puntaje de promoción | Constraint de base de datos, validación de aplicación | Aplicación | Deja flexibilidad para puntaje bonus a futuro sin migración de schema |
| Visibilidad de finanzas | Admin con vista agregada, admin sin ningún acceso económico | Sin acceso | El rol admin en un dojo se limita a operación (aprobar comprobantes), owner concentra toda visibilidad financiera |
| Concepto de instructor | Flag `is_instructor` nuevo, tabla propia de instructores, instructor = admin existente | Instructor = admin | Evita modelar una entidad nueva; todo admin ya tiene permisos operativos suficientes para dar clase |
| Tablas de clases/cupos (`gym_scheduled_classes` y relacionadas) | Mantener catalogadas como vertical-gym puro, reclasificar como shared-module | Shared-module | La propia función `get_promotion_candidate_stats` ya las consume con JOIN por `martial_art_id` en producción — son híbridas de facto, la auditoría original las catalogó mal |
| Expiración de sparring sin resolución | Sin expiración (queda documentado como conocido), expiración automática por tiempo | Expiración automática | Evita acumulación indefinida de retos fantasma sin intervención manual |
| Grupos familiares | Fuera de alcance para Dojo, incluido con historia propia | Incluido | Aplica a hermanos entrenando en el mismo dojo bajo un plan compartido |

## Pendiente
Con historias de usuario y requerimientos cerrados, el siguiente bloque es la definición de agentes (UI, QA/testing, seguridad OWASP 2025, documentación) y el cronograma de trabajo por semanas con manejo de ventanas de contexto.
