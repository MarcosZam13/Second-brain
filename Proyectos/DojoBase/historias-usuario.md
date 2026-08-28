---
proyecto: DojoBase
tema: Historias de usuario y criterios de aceptación
fecha: 2026-08-28
tipo: documentacion
estado: v1.0 — 30 HU con CA, agrupadas en épicas por rol. Numeración heredada del spec 06 para no romper trazabilidad; HU-24 en adelante son nuevas
tags: [dojobase, historias-usuario, requerimientos]
---

# Historias de Usuario — DojoBase (v1.0)

Ver también: [[Proyectos/DojoBase/README|README]] · [[Proyectos/DojoBase/documentacion-v1|documentacion-v1.md]] · [[Proyectos/DojoBase/schema-dojo|schema-dojo.md]] · [[Proyectos/CoreBase/schema|CoreBase/schema.md]] · [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]]

> Desglose de los requerimientos de [[Proyectos/DojoBase/documentacion-v1|documentacion-v1.md]] en épicas, historias de usuario (HU) y criterios de aceptación (CA). El spec original (`_fuentes/06`) tenía las HU en una tabla, sin CA — sin criterios explícitos el agente de QA no tiene contra qué escribir tests, que es justamente su encargo.
>
> **Numeración:** se conserva la del spec 06 (HU-00 a HU-23, con sufijos) para no romper las referencias de los documentos de schema. **HU-24 en adelante son nuevas**, salidas de este desglose y de la revisión crítica.
>
> Los CA marcados **[servidor]** deben verificarse llamando directamente al server action o a la base, no solo por la UI — son los que RNF-01 exige y los que el agente de seguridad revisa.

## Roles

- **Miembro** — alumno del dojo.
- **Admin** — gestión operativa. **Es también el instructor**: no existe una entidad ni un flag de instructor aparte.
- **Owner** — todo lo de admin, más finanzas y configuración de la organización.
- **Sistema** — comportamiento automático sin actor humano (jobs programados).

---

## Rol: Acceso y organización

### Epic: Autenticación y pertenencia

**HU-22: Invitar a un miembro nuevo**
Como admin, quiero invitar a una persona a mi dojo por código de invitación o alta directa, para incorporar alumnos sin abrir un registro público.
- CA-01: El admin puede generar una invitación con rol y vencimiento, y obtener un código o enlace para compartir.
- CA-02: El admin puede dar de alta directamente a un miembro indicando su correo, quedando la invitación pendiente de que la persona la acepte.
- CA-03: Una invitación aceptada no puede volver a usarse.
- CA-04: Una invitación vencida no permite el alta y muestra el motivo.
- CA-05 **[servidor]**: Aceptar una invitación crea la membresía con el rol indicado en la invitación, nunca con uno superior al enviado.

**HU-24: Aceptar una invitación** *(nueva)*
Como persona invitada, quiero aceptar la invitación y quedar registrada en el dojo, para poder empezar a usar la app.
- CA-01: Al abrir el enlace, si no tengo cuenta se me ofrece crearla; si ya tengo, iniciar sesión.
- CA-02: Al completar el proceso quedo como miembro activo de esa organización y esa organización queda como mi organización activa.
- CA-03: Si ya pertenezco a esa organización, se me informa y no se duplica la membresía.

**HU-25: Iniciar sesión y trabajar en el dojo correcto** *(nueva)*
Como usuario que puede pertenecer a más de una organización, quiero que la app sepa siempre en cuál estoy trabajando, para no ver datos mezclados.
- CA-01: Al iniciar sesión, los datos que veo corresponden únicamente a mi organización activa.
- CA-02: Si pertenezco a varias, puedo cambiar de organización activa y toda la app refleja el cambio sin necesidad de volver a iniciar sesión.
- CA-03 **[servidor]**: Tras cambiar de organización, ninguna consulta devuelve datos de la organización anterior.
- CA-04: Si no pertenezco a ninguna organización activa, veo una pantalla que lo explica, no una pantalla en blanco ni un error.

**HU-26: Un cambio de rol surte efecto** *(nueva)*
Como owner, quiero que al cambiar el rol de alguien el cambio se aplique cuanto antes, para que un permiso retirado deje de funcionar.
- CA-01: Tras cambiar el rol de un usuario, su sesión refleja el rol nuevo sin que tenga que cerrar sesión.
- CA-02 **[servidor]**: Retirar el rol de owner impide inmediatamente el acceso al resumen financiero y a la conexión de pagos, sin esperar al vencimiento del token.
- CA-03: Una organización no puede quedarse sin ningún owner.

---

## Rol: Admin — configuración del dojo

### Epic: Disciplinas y rangos

**HU-00: Crear una disciplina y su escala de rangos**
Como admin, quiero crear una disciplina y definir su escala completa de rangos, para tener con qué poblar clases, sparring y promociones.
- CA-01: Puedo crear una disciplina con nombre y color; el nombre es único dentro del dojo.
- CA-02: Puedo definir los rangos de esa disciplina con nombre, nivel de progresión, color (y color secundario para cinturones bicolor) y cantidad de franjas necesarias para ascender.
- CA-03: Dos rangos de la misma disciplina no pueden compartir nivel.
- CA-04: Puedo reordenar los rangos y el orden se refleja en toda la app.
- CA-05: Puedo desactivar una disciplina sin borrar su historial de rangos, clases ni peleas.
- CA-06: Agregar una disciplina nueva no requiere ningún cambio de código ni migración.

**HU-27: Asignar el rango de un miembro por disciplina** *(nueva)*
Como admin, quiero asignar o corregir el rango y las franjas de un miembro en una disciplina, para reflejar su nivel real.
- CA-01: Puedo asignar un rango por cada disciplina que el miembro practica, de forma independiente.
- CA-02: Puedo ajustar la cantidad de franjas dentro del rango actual.
- CA-03 **[servidor]**: Cambiar el rango en una disciplina no modifica el rango ni las franjas del miembro en ninguna otra disciplina.
- CA-04: El cambio queda registrado con fecha.

### Epic: Miembros

**HU-28: Gestionar los miembros del dojo** *(nueva)*
Como admin, quiero ver y administrar a los miembros, para llevar la operación diaria.
- CA-01: Veo la lista de miembros con su rango por disciplina y el estado de su membresía.
- CA-02: Puedo buscar y filtrar por disciplina, rango y estado de membresía.
- CA-03: Puedo abrir la ficha de un miembro y ver su historial de clases, promociones, peleas y pagos.
- CA-04: Puedo suspender a un miembro sin borrar su historial, y reactivarlo después.

---

## Rol: Miembro y Admin — clases

### Epic: Calendario y clases

**HU-01: Ver mi horario semanal**
Como miembro, quiero ver mi horario semanal de clases por disciplina, para saber a qué puedo asistir esta semana.
- CA-01: Veo la semana actual con las clases de mi dojo, cada una con disciplina, hora, instructor y cupo disponible.
- CA-02: Puedo navegar a semanas anteriores y siguientes.
- CA-03: Las clases privadas para las que no califico por mi plan no aparecen.
- CA-04: Una clase cancelada se muestra claramente como cancelada, no desaparece.
- CA-05: Si no hay clases en la semana, veo un estado vacío con explicación, no una pantalla en blanco.

**HU-02: Inscribirme a una clase**
Como miembro, quiero inscribirme a una clase con cupo disponible, para confirmar mi asistencia.
- CA-01: Puedo inscribirme si hay cupo y la clase no está cancelada.
- CA-02: Al inscribirme, mi asistencia queda registrada como presente.
- CA-03 **[servidor]**: No puedo inscribirme dos veces a la misma clase.
- CA-04 **[servidor]**: No puedo inscribirme a una clase que ya empezó o que empieza dentro de la antelación mínima configurada.
- CA-05: Si la clase está llena, entro en lista de espera y se me informa mi posición.
- CA-06 **[servidor]**: No puedo inscribirme a una clase privada para la que mi plan no califica.

**HU-02b: Cancelar mi inscripción**
Como miembro, quiero cancelar mi inscripción, para liberar mi cupo si ya no puedo asistir.
- CA-01: Puedo cancelar mientras falte más que la antelación mínima configurada.
- CA-02: Al cancelar, el cupo se libera y la primera persona en lista de espera pasa a confirmada.
- CA-03 **[servidor]**: Cancelar fuera de plazo se rechaza en el servidor, con el motivo.
- CA-04: Mi asistencia deja de contar para esa clase.

**HU-02c: Cancelar una clase completa**
Como admin, quiero cancelar una clase, para avisar a todos los inscritos cuando no se puede dar.
- CA-01: Puedo cancelar indicando un motivo.
- CA-02: Todos los inscritos reciben notificación con el motivo.
- CA-03: La clase queda marcada como cancelada y no admite inscripciones nuevas.
- CA-04: La asistencia de esa clase no cuenta para promociones ni challenges.

**HU-03: Ver quiénes van a la clase**
Como miembro, quiero ver quiénes más están inscritos y con qué rango, para saber con quién voy a entrenar.
- CA-01: Veo la lista de inscritos con su nombre, foto y rango **en la disciplina de esa clase**.
- CA-02: El instructor aparece identificado como tal, con su rango.
- CA-03: Si aún no hay inscritos, veo un estado vacío.

**HU-04: Crear y planificar clases**
Como admin, quiero crear clases con disciplina, instructor, cupo y horario, viendo el mes completo, para planificar la operación del dojo.
- CA-01: Puedo crear una clase indicando disciplina, tipo, instructor, fecha, hora de inicio y fin, y cupo.
- CA-02: El instructor solo puede ser un admin de la organización.
- CA-03: Puedo crear una serie recurrente y editarla o eliminarla como serie o como ocurrencia individual.
- CA-04: Veo el calendario en vista mensual, con la ocupación de cada clase.
- CA-05: Puedo marcar una clase como privada y restringirla a planes específicos.

**HU-04b: Corregir la asistencia después de la clase** *(nueva — decisión 5)*
Como instructor, quiero marcar quién realmente no llegó, para que la asistencia registrada sea la real.
- CA-01: Después de la hora de la clase, puedo marcar a cualquier inscrito como ausente, y revertirlo.
- CA-02: La lista distingue tres estados: presente, ausente y sin verificar.
- CA-03 **[servidor]**: Solo la asistencia **presente** cuenta para la ventana de elegibilidad de promociones y para los challenges de asistencia.
- CA-04: El miembro ve en su historial si una clase quedó marcada como ausencia.

---

## Rol: Miembro — sparring

### Epic: Retos amistosos

**HU-05: Retar a un compañero**
Como miembro, quiero retar a otro miembro a un sparring en una disciplina específica, para competir de forma informal dentro del dojo.
- CA-01: Elijo rival y disciplina, y opcionalmente propongo fecha.
- CA-02 **[servidor]**: No puedo retarme a mí mismo.
- CA-03 **[servidor]**: No puedo retar a alguien de otra organización.
- CA-04: El reto queda pendiente y aparece en mi lista de retos.
- CA-05: El rival recibe notificación inmediata (HU-09).

**HU-06: Aceptar o rechazar un reto**
Como miembro retado, quiero aceptar o rechazar, para decidir si me enfrento a esa persona.
- CA-01: Veo el reto con quién me reta, en qué disciplina, su rango en esa disciplina, y la fecha propuesta.
- CA-02: Puedo aceptar o rechazar, y el retador recibe notificación de mi respuesta.
- CA-03 **[servidor]**: Solo el rival puede responder, y solo mientras el reto esté pendiente.
- CA-04: Un reto rechazado queda en el historial como rechazado; no desaparece sin dejar rastro.

**HU-07: Cargar el resultado round por round**
Como retador, quiero cargar los resultados por round del sparring aceptado, para dejar registro del enfrentamiento.
- CA-01: Puedo agregar rounds con puntaje para ambos y una nota opcional.
- CA-02 **[servidor]**: Solo el retador puede cargar rounds, y solo si el reto está aceptado.
- CA-03: Al cerrar el reto, el ganador se calcula automáticamente a partir de la suma de los rounds.
- CA-04 **[servidor]**: El cálculo del ganador usa la misma función que el preview que veo en pantalla — el resultado mostrado y el guardado nunca difieren.
- CA-05: Un empate en la suma de rounds es un resultado válido y se guarda como tal.

**HU-07b: Confirmar el resultado** *(nueva — decisión 4)*
Como miembro retado, quiero confirmar o disputar el resultado que cargó mi rival, para que el historial refleje lo que realmente pasó.
- CA-01: Cuando el retador cierra el reto, recibo una notificación para confirmar el resultado.
- CA-02: Puedo confirmarlo, y el enfrentamiento pasa a contar en el historial cruzado.
- CA-03: Mientras no lo confirme, el reto se muestra como "pendiente de confirmación" y **no cuenta** en el historial cruzado.
- CA-04 **[servidor]**: Solo el rival puede confirmar, y solo sobre un reto completado.
- CA-05: Puedo dejar una nota si no estoy de acuerdo, visible para ambos y para el staff.

**HU-08: Ver mi historial contra un compañero**
Como miembro, quiero ver mi historial de enfrentamientos contra un compañero, para llevar cuenta de la rivalidad.
- CA-01: Veo el marcador acumulado por disciplina contra cada rival con el que tuve sparrings.
- CA-02: Solo se cuentan enfrentamientos completados **y confirmados**.
- CA-03: Puedo abrir el detalle de cada enfrentamiento y ver los rounds.
- CA-04 **[servidor]**: No puedo ver el historial cruzado de dos miembros en el que no participo.

**HU-09: Recibir el reto al momento**
Como miembro, quiero enterarme inmediatamente cuando me retan, para responder a tiempo.
- CA-01: Si estoy usando la app, el reto aparece como aviso inmediato sin recargar.
- CA-02: Si no estoy, recibo una notificación push.
- CA-03: El reto persiste en mi lista de retos pendientes — no desaparece por haberse mostrado una vez.
- CA-04: Si recibí el aviso in-app, la notificación push no vuelve a llamar la atención sobre lo mismo una vez que la marqué leída.

**HU-09b: Cancelar un sparring propio**
Como miembro, quiero cancelar un sparring en el que participo antes de que se complete, para salir de un reto que ya no quiero sostener.
- CA-01: Cualquiera de los dos participantes puede cancelar mientras el reto esté pendiente o aceptado.
- CA-02: El otro participante recibe notificación.
- CA-03 **[servidor]**: Un reto completado no se puede cancelar.

**HU-09c: Expiración automática de retos fantasma**
Como sistema, quiero expirar los sparrings sin resolver, para evitar que se acumulen indefinidamente.
- CA-01: Un reto pendiente sin respuesta por más del plazo configurado pasa a cancelado.
- CA-02: Un reto aceptado sin resultado cargado por más del plazo configurado pasa a cancelado.
- CA-03: El plazo es configurable por dojo, con 14 días por defecto.
- CA-04: Ambos participantes ven que el reto expiró, con ese motivo y no como una cancelación manual.

---

## Rol: Miembro y Admin — peleas oficiales

### Epic: Historial competitivo

**HU-10: Registrar una pelea oficial**
Como admin, quiero registrar una pelea oficial de un miembro con resultado, método y evento, para mantener el historial competitivo del dojo.
- CA-01: Puedo registrar una pelea indicando miembro, disciplina, rival (nombre libre o miembro del dojo), evento, fecha, resultado y método.
- CA-02: Puedo registrar una pelea futura con resultado "próxima" y completarla después.
- CA-03 **[servidor]**: Solo admin y owner pueden crear, editar o eliminar peleas oficiales.
- CA-04: El miembro ve la pelea en su historial apenas se registra.

**HU-11: Ver quién está compitiendo**
Como miembro, quiero ver en el dashboard las próximas peleas de mis compañeros, para sentir que hay actividad competitiva real en el dojo.
- CA-01: El dashboard muestra las peleas próximas de toda la organización con fecha futura, ordenadas por fecha.
- CA-02: Cada una muestra quién pelea, en qué disciplina, contra quién y en qué evento.
- CA-03: Las peleas próximas son visibles para toda la organización **independientemente de la privacidad del miembro**.
- CA-04: Si no hay peleas próximas, el feed muestra un estado vacío, no se esconde.

**HU-11b: Decidir si publico mi resultado** *(nueva — decisión 6)*
Como miembro, quiero decidir si el resultado de mi pelea se ve en el feed del dojo, para tener control sobre mi historial.
- CA-01: Mis resultados son privados por defecto: solo yo y el staff los vemos.
- CA-02: Puedo publicar un resultado y entonces aparece en el feed de la organización.
- CA-03: Puedo despublicarlo después.
- CA-04 **[servidor]**: Otro miembro no puede leer mis resultados no publicados por ninguna vía.

---

## Rol: Admin y Miembro — promociones

### Epic: Eventos de ascenso

**HU-12: Crear un evento de promoción**
Como admin, quiero crear un evento de promoción con criterios de evaluación por disciplina, para organizar exámenes de forma estructurada.
- CA-01: Puedo crear un evento indicando disciplina, nombre, fecha, y si otorga rango o franja.
- CA-02: Puedo definir criterios con nombre, puntaje máximo y peso.
- CA-03: Puedo fijar un rango objetivo, o dejarlo dinámico para que cada candidato ascienda al siguiente de su propia escala — **y la app dice explícitamente cuál de los dos comportamientos está activo**.
- CA-04: Puedo definir una nota mínima de aprobación, o dejarla sin definir.
- CA-05: Puedo configurar la ventana de asistencia que se considera para la elegibilidad.
- CA-06 **[servidor]**: Solo se pueden eliminar criterios o retirar candidatos con el evento en borrador.

**HU-12b: Postular candidatos** *(nueva)*
Como admin, quiero postular a los miembros que se van a evaluar, para armar la lista del examen.
- CA-01: Puedo agregar candidatos entre los miembros que practican esa disciplina.
- CA-02: La app me muestra su asistencia dentro de la ventana configurada, para decidir con datos.
- CA-03: Al postular se guarda el rango con el que el candidato se presenta.
- CA-04 **[servidor]**: Un mismo miembro no puede estar dos veces en el mismo evento.

**HU-13: Calificar y resolver**
Como admin, quiero calificar candidatos por criterio y resolver quién asciende, para decidir con base en desempeño objetivo.
- CA-01: Veo una grilla de candidatos por criterio y puedo cargar puntajes, con el puntaje final recalculándose en vivo.
- CA-02 **[servidor]**: Un puntaje se valida contra el puntaje máximo **de ese criterio**, no contra un rango fijo.
- CA-03: Un candidato con criterios sin calificar se marca visiblemente como **evaluación incompleta**.
- CA-04 **[servidor]**: La resolución automática por nota mínima **excluye** a los candidatos con evaluación incompleta en vez de aprobarlos sobre base parcial.
- CA-05: Puedo resolver a un candidato manualmente como promovido o no promovido, incluso si su evaluación está incompleta, viendo el aviso.
- CA-06 **[servidor]**: Un candidato ya resuelto no admite edición de puntajes; para corregir hay que revertir la decisión primero.
- CA-07 **[servidor]**: Promover a un candidato actualiza su rango o sus franjas **solo en la disciplina del evento**.
- CA-08: Cuando un miembro llega al tope de franjas de su rango, la app lo muestra como "listo para ascender" y explica por qué el botón de franja está deshabilitado.
- CA-09: El candidato recibe notificación del resultado.

**HU-13b: Reabrir un evento cerrado**
Como admin, quiero reabrir un evento cerrado que dejó candidatos sin resolver, para resolverlos después en vez de que queden huérfanos.
- CA-01: Un evento completado puede volver al estado activo.
- CA-02: Al reabrirlo puedo resolver los candidatos que quedaron pendientes.
- CA-03: Cerrar un evento sin nota mínima definida es válido y no requiere confirmación especial.
- CA-04: La reapertura queda registrada con quién y cuándo.

**HU-14: Ver mi propio progreso** — *pantalla nueva, no existe en GymBase v1*
Como miembro, quiero ver mi historial de promociones, mi rango actual por disciplina y el desglose de mi calificación por criterio, para saber en qué punto estoy y por qué, sin depender del admin.
- CA-01: Veo mi rango y mis franjas actuales en cada disciplina que practico.
- CA-02: Veo la lista de eventos de promoción en los que participé, con su resultado.
- CA-03: Al abrir un evento veo **mi puntaje por cada criterio**, el máximo de cada uno y mi puntaje final.
- CA-04: Veo cuánto me falta de asistencia o de franjas para el siguiente rango, si el dojo lo tiene configurado.
- CA-05 **[servidor]**: Accedo a esto sin intervención de un admin, y no puedo ver el desglose de ningún otro miembro.
- CA-06: La notificación de resultado de promoción me lleva directo a esta pantalla.

---

## Rol: Miembro — contenido, retos y comunidad

### Epic: Contenido

**HU-15: Publicar contenido en carpetas**
Como admin u owner, quiero subir contenido organizado en carpetas, para compartir recursos educativos con los miembros.
- CA-01: Puedo crear carpetas y subcarpetas, renombrarlas y reordenarlas.
- CA-02: Puedo publicar contenido con título, cuerpo y material adjunto dentro de una carpeta.
- CA-03: Puedo restringir un contenido a uno o varios planes de membresía.
- CA-04: Puedo dejar contenido sin publicar mientras lo preparo.
- CA-05 **[servidor]**: Un miembro cuyo plan no califica no puede acceder al contenido restringido por ninguna vía.

**HU-15b: Marcar contenido como favorito**
Como miembro, quiero marcar contenido como favorito, para volver a encontrarlo fácil.
- CA-01: Puedo marcar y desmarcar un contenido como favorito.
- CA-02: Tengo una vista con solo mis favoritos.
- CA-03: Si pierdo acceso a un contenido por cambio de plan, deja de aparecer en mis favoritos.

### Epic: Challenges

**HU-16: Crear challenges**
Como admin, quiero crear retos de asistencia, rutina o peleas amistosas, para incentivar la participación de los miembros.
- CA-01: Puedo crear un reto con nombre, descripción, tipo, meta, y fechas de inicio y fin.
- CA-02: Los miembros ven los retos activos y su progreso.
- CA-03: El progreso de un reto de asistencia cuenta solo la asistencia **presente**.
- CA-04: Puedo cerrar un reto y ver quiénes lo completaron.

---

## Rol: Miembro, Admin y Owner — membresías y pagos

### Epic: Planes y suscripción

**HU-16b: Definir planes de membresía**
Como admin u owner, quiero definir los planes con nombre, precio y período, para tener a qué suscribir a los miembros.
- CA-01: Puedo crear, editar y desactivar planes con nombre, descripción, precio y período mensual o anual.
- CA-02: Puedo marcar un plan como recomendado y se destaca en la vista del miembro.
- CA-03: Desactivar un plan no afecta a las suscripciones vigentes.

**HU-16c: Suscribirme a un plan**
Como miembro, quiero elegir un plan y suscribirme, para activar mi acceso al dojo.
- CA-01: Veo los planes activos con su precio y período.
- CA-02: Al elegir uno, mi suscripción queda creada a la espera del pago.
- CA-03: Veo claramente el estado de mi membresía y hasta cuándo está vigente.

**HU-17: Subir mi comprobante SINPE**
Como miembro, quiero subir mi comprobante, para que el admin verifique mi pago.
- CA-01: Veo el número y el nombre SINPE del dojo para hacer la transferencia.
- CA-02: Puedo adjuntar la imagen del comprobante e indicar el monto.
- CA-03: Si no indico el monto, se toma el del plan al que estoy suscrito.
- CA-04 **[servidor]**: No puedo crear un comprobante ya aprobado, ni aprobar el mío.
- CA-05 **[servidor]**: No puedo ver el comprobante de otro miembro.

**HU-17b: Ver el estado de mi comprobante**
Como miembro, quiero ver si mi comprobante fue aprobado o rechazado, para saber el estado de mi membresía.
- CA-01: Veo el estado de cada comprobante que subí.
- CA-02: Si fue rechazado, veo el motivo que dejó el admin.
- CA-03: Al aprobarse, mi membresía se extiende y lo veo reflejado de inmediato.

**HU-18: Revisar comprobantes**
Como admin, quiero aprobar o rechazar comprobantes, para gestionar los pagos.
- CA-01: Veo los comprobantes pendientes con el miembro, el plan, el monto y la imagen.
- CA-02: Puedo aprobar o rechazar; al rechazar debo indicar un motivo.
- CA-03: Al aprobar, el nuevo período se encola **desde el vencimiento de la suscripción vigente**, no desde hoy.
- CA-04: Queda registrado quién decidió y cuándo.
- CA-05 **[servidor]**: Solo puedo mover un comprobante a aprobado o rechazado, ningún otro estado.
- CA-06 **[servidor]**: No tengo acceso a ningún reporte ni total de ingresos.

**HU-19: Ver las finanzas del dojo**
Como owner, quiero ver el dashboard financiero agregado, para tomar decisiones de negocio.
- CA-01: Veo ingresos por período, suscripciones activas y distribución por plan.
- CA-02: Puedo filtrar por rango de fechas y exportar.
- CA-03 **[servidor]**: Un usuario con rol admin recibe error al intentar acceder, tanto por la UI como llamando directamente.
- CA-04 **[servidor]**: Si a un owner se le retira el rol, pierde el acceso de inmediato, sin esperar al vencimiento de su sesión.

**HU-20: Recibir recordatorio de vencimiento**
Como miembro, quiero recibir un recordatorio antes de que venza mi membresía, para no perderla por olvido.
- CA-01: Recibo notificación in-app y push antes del vencimiento.
- CA-02: No recibo el mismo recordatorio dos veces para el mismo período.
- CA-03: El recordatorio me lleva a la pantalla de pago.

**HU-23: Agrupar a una familia bajo un plan compartido**
Como admin u owner, quiero agrupar a varios miembros en un grupo familiar, para cobrarles como unidad en vez de por separado.
- CA-01: Puedo crear un grupo familiar y asignarle miembros de la organización.
- CA-02: Cada integrante puede tener un plan distinto dentro del grupo.
- CA-03: Veo el estado de pago del grupo como unidad.
- CA-04: Quitar a alguien del grupo no borra su historial de pagos.

---

## Rol: Owner — configuración

### Epic: Identidad y pagos del dojo

**HU-21: Configurar el tema visual del dojo**
Como owner o admin, quiero configurar los colores y el logo del dojo, para que la app refleje la identidad de mi marca.
- CA-01: Puedo definir los colores del tema, el logo y el estilo de bordes.
- CA-02: Los cambios se ven en toda la app sin necesidad de un despliegue.
- CA-03: Al cargar la app el tema del dojo se aplica **antes del primer render** — no se ve un parpadeo con el tema por defecto.
- CA-04: Puedo elegir un preset como punto de partida en vez de definir todo desde cero.
- CA-05: Ninguna pantalla queda con colores que no correspondan al tema configurado.

**HU-29: Configurar los datos operativos del dojo** *(nueva)*
Como owner, quiero configurar los datos del dojo, para que los flujos usen mis reglas.
- CA-01: Puedo definir el número y nombre SINPE que ven los miembros al pagar.
- CA-02: Puedo definir la antelación mínima para cancelar una inscripción.
- CA-03: Puedo definir el plazo de expiración de los sparrings sin resolver.
- CA-04: Puedo definir la ventana de asistencia por defecto para promociones.

**HU-30: Conectar la cuenta de pagos** *(nueva)*
Como owner, quiero conectar la cuenta de pagos del dojo, para procesar cobros.
- CA-01: Puedo conectar y desconectar la cuenta del proveedor.
- CA-02: Veo el estado de la conexión.
- CA-03 **[servidor]**: Un admin no puede ver ni modificar esta configuración por ninguna vía.

---

## Rol: Sistema

### Epic: Procesos automáticos

**HU-31: Un solo proceso diario mantiene el estado al día** *(nueva)*
Como sistema, quiero ejecutar un proceso diario que resuelva todo lo que vence por tiempo, para que el estado de la app sea correcto sin intervención manual.
- CA-01: Expira los sparrings pendientes o aceptados fuera de plazo (HU-09c).
- CA-02: Envía los recordatorios de pago próximos a vencer, sin duplicar (HU-20).
- CA-03: Marca como vencidas las suscripciones que pasaron su período.
- CA-04: Si el proceso falla, queda registro y el intento siguiente no duplica efectos.

---

## Trazabilidad HU → requerimiento

| Epic | HU | RF principales |
|---|---|---|
| Autenticación y pertenencia | HU-22, 24, 25, 26 | RF-19, RF-20, RNF-02 |
| Disciplinas y rangos | HU-00, 27 | RF-01, RF-02, RF-02b, RNF-06 |
| Miembros | HU-28 | RF-20 |
| Calendario y clases | HU-01, 02, 02b, 02c, 03, 04, 04b | RF-03, RF-03b, RF-03c, RF-04, RF-04b |
| Sparring | HU-05 a HU-09c, 07b | RF-05, RF-06, RF-06b, RF-06c, RF-07, RF-08 |
| Peleas oficiales | HU-10, 11, 11b | RF-09, RF-10 |
| Promociones | HU-12, 12b, 13, 13b, 14 | RF-11 a RF-12b |
| Contenido | HU-15, 15b | RF-13, RF-13b |
| Challenges | HU-16 | RF-14 |
| Membresías y pagos | HU-16b, 16c, 17, 17b, 18, 19, 20, 23 | RF-15, RF-16, RF-17, RF-21, RF-22 |
| Configuración | HU-21, 29, 30 | RF-18, RF-16 |
| Procesos automáticos | HU-31 | RF-06c, RF-17 |

## Pendiente

- **`DESIGN.md`** — cada HU de esta lista debería referenciar la pantalla donde vive, como hace el de [[Proyectos/Tacha/DESIGN|Tacha]]. Se agrega esa columna cuando exista el inventario de pantallas.
- **Análisis de complejidad y orden de sprints** — el equivalente al `analisis-complejidad-viabilidad.md` de Tacha, con estimación por HU y dependencias, para ordenar el bloque 2 del plan.
