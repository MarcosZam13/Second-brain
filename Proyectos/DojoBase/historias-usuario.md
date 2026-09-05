---
proyecto: DojoBase
tema: Historias de usuario y criterios de aceptación
fecha: 2026-09-03
tipo: documentacion
estado: v1.5 — 66 historias con criterios de aceptación, agrupadas en épicas por rol. Numeración heredada del spec 06; HU-24 en adelante son nuevas. v1.1 agrega progresión por disciplina, ficha del alumno y módulos opcionales (revisión de mockups); v1.2 agrega lo que salió del repaso de GymBase v1: sesión de sparring con cronómetro, clases recurrentes, anuncios, notificaciones por correo y proyección de torneos. v1.4 (2026-09-03) corrige HU-05/06/07/07c/08/09 contra lo que DOJO-9 terminó construyendo: sin fecha propuesta, el reto se decide por rounds ganados (no suma de puntos) con KO/sumisión/decisión por round, HU-07b (confirmación del rival) removida, preparación de 10s antes de cada round. v1.5 (2026-09-06) agrega la épica "Torneos" (HU-42 a HU-44, bocetada y sin priorizar) tras aclarar con Marcos que Torneos y Peleas oficiales (HU-10/11/11b) son features distintas — HU-38 (proyección) se reubicó ahí, vivía suelta bajo Configuración sin ninguna otra HU de torneos escrita todavía.
tags: [dojobase, historias-usuario, requerimientos]
---

# Historias de Usuario — DojoBase (v1.2)

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
- CA-02: Puedo definir los rangos de esa disciplina con nombre, etiqueta corta (`3.º kyu`, `1.º dan`), nivel de progresión y color (más un color secundario para cinturones bicolor). El campo de franjas solo aparece si la disciplina las usa (HU-00b).
- CA-03: Dos rangos de la misma disciplina no pueden compartir nivel.
- CA-04: Puedo reordenar los rangos y el orden se refleja en toda la app.
- CA-05: Puedo desactivar una disciplina sin borrar su historial de rangos, clases ni peleas.
- CA-06: Agregar una disciplina nueva no requiere ningún cambio de código ni migración.

**HU-00b: Definir cómo se progresa en una disciplina** *(nueva — corrección del 2026-08-28)*
Como admin, quiero indicar cómo se asciende en cada disciplina, para que la app refleje el sistema real de mi escuela y no uno inventado.
- CA-01: Al crear una disciplina elijo su estilo de progresión: **ascenso directo**, **franjas** o **por tiempo**.
- CA-02: Con ascenso directo, la app **no muestra franjas en ninguna parte** — ni en el cinturón, ni en el progreso del alumno, ni en la evaluación de ascensos.
- CA-03: Con franjas, cada rango define cuántas se necesitan para ascender.
- CA-04: Por tiempo, la disciplina puede no tener escalera de rangos, y el progreso del alumno se muestra como tiempo entrenando, clases y récord.
- CA-05: Elijo aparte cómo se representa el grado: cinturón, parche o nivel, o ninguna insignia.
- CA-06: Puedo exigir tiempo mínimo en el rango y asistencia mínima antes de habilitar un ascenso.
- CA-07 **[servidor]**: Otorgar una franja en una disciplina de ascenso directo se rechaza.

**HU-27: Asignar el rango de un miembro por disciplina** *(nueva)*
Como admin, quiero asignar o corregir el rango y las franjas de un miembro en una disciplina, para reflejar su nivel real.
- CA-01: Puedo asignar un rango por cada disciplina que el miembro practica, de forma independiente.
- CA-02: Si la disciplina usa franjas, puedo ajustar cuántas lleva dentro del rango actual. Si no las usa, ese control no existe.
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

**HU-02d: Programar una serie de clases recurrentes** *(nueva — confirmada en el repaso de v1)*
Como admin, quiero crear una clase que se repite todas las semanas, para no cargar el mismo horario cada lunes.
- CA-01: Al crear una clase puedo indicar que se repite, con días de la semana, hora y fecha de fin.
- CA-02: Al editar la serie, el cambio aplica a las ocurrencias futuras.
- CA-03 **[servidor]**: Editar la serie **no pisa** una ocurrencia que ya se había editado aparte.
- CA-04: Cancelar una ocurrencia puntual **no rompe la serie**: la siguiente se genera igual.
- CA-05: Al eliminar la serie elijo entre solo las futuras o todas.
- CA-06 **[servidor]**: Eliminar una serie nunca borra ocurrencias pasadas que ya tienen asistencia registrada.

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
- CA-01: Elijo rival, disciplina, cantidad de rounds y duración de cada round y del descanso. *(2026-09-03: sin fecha propuesta — sacada a pedido explícito, ver HU-07c CA-01 donde vivía la config de rounds/duración por default; ahora se elige siempre al retar.)*
- CA-02 **[servidor]**: No puedo retarme a mí mismo.
- CA-03 **[servidor]**: No puedo retar a alguien de otra organización.
- CA-04: El reto queda pendiente y aparece en mi lista de retos.
- CA-05: El rival recibe notificación inmediata (HU-09).

**HU-06: Aceptar o rechazar un reto**
Como miembro retado, quiero aceptar o rechazar, para decidir si me enfrento a esa persona.
- CA-01: Veo el reto con quién me reta, en qué disciplina, y su rango en esa disciplina. *(2026-09-03: ya no muestra fecha propuesta — el campo se sacó del alta, ver HU-05 CA-01.)*
- CA-02: Puedo aceptar o rechazar, y el retador recibe notificación de mi respuesta.
- CA-03 **[servidor]**: Solo el rival puede responder, y solo mientras el reto esté pendiente.
- CA-04: Un reto rechazado queda en el historial como rechazado; no desaparece sin dejar rastro.

**HU-07: Cargar el resultado round por round**
Como retador, quiero cargar los resultados por round del sparring aceptado, para dejar registro del enfrentamiento.
- CA-01: Puedo agregar rounds con puntaje para ambos y una nota opcional.
- CA-01b: Anoto con **botones de valor directo** (+1 a +4 por defecto) para cada peleador, no sumando de a uno.
- CA-01c: Un **deshacer** revierte la última anotación de cualquiera de los dos, e indica cuál va a revertir antes de usarlo.
- CA-01d: Los valores de los botones se configuran por disciplina; si no se configuran, son 1 a 4.
- CA-02 **[servidor]**: Solo el retador puede cargar rounds, y solo si el reto está aceptado.
- CA-03 *(rediseñada 2026-09-03)*: Al cerrar el reto, el ganador se calcula a partir de **cuántos rounds ganó cada uno** — no de la suma de puntos. Cada round se lo lleva quien anotó más en ESE round; un round empatado en puntos no cuenta para ninguno de los dos.
- CA-04 **[servidor]**: El cálculo del ganador usa la misma función que el preview que veo en pantalla — el resultado mostrado y el guardado nunca difieren.
- CA-05 *(rediseñada 2026-09-03)*: Un empate en la cantidad de rounds ganados por cada uno es un resultado válido y se guarda como tal.
- CA-06 *(nueva — 2026-09-03)*: Puedo corregir un round ya cargado sin tener que deshacer los rounds posteriores.
- CA-07 *(nueva — 2026-09-03)*: Un round puede decidirse por **KO, sumisión o decisión** en vez de por puntos — declaro quién ganó ese round y queda fijo, sin importar el marcador que hubiera hasta ahí. No cierra el reto: el reto sigue jugándose los rounds que falten, y se sigue decidiendo por CA-03.

**HU-07c: Correr la sesión de sparring con cronómetro** *(nueva — hallazgo del repaso de v1)*
Como challenger, quiero que la app me lleve el tiempo de cada round y del descanso, para poder concentrarme en el sparring en vez de en el reloj.
- CA-01: Al crear el reto defino cantidad de rounds, duración de cada uno y del descanso; si no los defino, son 3 rounds de 3 minutos con 1 de descanso.
- CA-02: La sesión recorre las fases: **preparación → cronómetro del round → cargar el resultado → descanso → round siguiente**, y termina en un resumen. *(2026-09-03: se agregó la fase de preparación, ver CA-08.)*
- CA-03: Puedo anotar puntos **mientras el round corre**, sin pausar nada.
- CA-04 **[servidor / cliente]**: El tiempo se calcula contra el instante de inicio, no descontando un contador. **Con la pantalla apagada o la app en segundo plano, al volver el cronómetro muestra el tiempo correcto.**
- CA-05: Suena un aviso y vibra al faltar 10 segundos y al terminar el round — nadie mira la pantalla mientras pelea.
- CA-06: El paso a descanso es automático; el paso al round siguiente lo confirmo yo, porque el descanso real nunca dura lo configurado.
- CA-07: Puedo pausar y retomar, y puedo terminar el reto antes de completar todos los rounds.
- CA-08 *(nueva — 2026-09-03)*: Antes de CADA round (incluido el primero) hay una preparación de 10 segundos con cuenta regresiva, con un aviso sonoro distinto al de "quedan 10s"/"terminó el round" — para notar la diferencia entre "falta poco" y "arrancó de verdad" sin mirar la pantalla. También puedo declarar un round por KO/sumisión/decisión desde acá mismo (HU-07 CA-07), sin volver al detalle primero.

~~**HU-07b: Confirmar el resultado**~~ *(removida — 2026-09-03, a pedido explícito)*
Existía como "el rival confirma o disputa el resultado antes de que cuente en el historial". Se sacó por completo: en un sparring amistoso entre compañeros que ya lo vieron, pedir un click de "confirmar" además del cierre era fricción sin ninguna decisión real detrás. `cerrar_reto()` cierra en firme, sin paso aparte — el mecanismo de dejar una nota (`sparring_notes`) sigue existiendo en la base, pero sin superficie en la UI.

**HU-08: Ver mi historial contra un compañero**
Como miembro, quiero ver mi historial de enfrentamientos contra un compañero, para llevar cuenta de la rivalidad.
- CA-01: Veo el marcador acumulado de retos por disciplina contra cada rival con el que tuve sparrings, **y el total de rounds ganados/perdidos** sumando todos esos retos. *(2026-09-03: se agregó el detalle de rounds, no solo retos.)*
- CA-02 *(2026-09-03: ya no depende de confirmación, ver HU-07b)*: Solo se cuentan enfrentamientos completados.
- CA-03: Puedo abrir el detalle de cada enfrentamiento y ver los rounds.
- CA-04 **[servidor]**: No puedo ver el historial cruzado de dos miembros en el que no participo.

**HU-09: Recibir el reto al momento**
Como miembro, quiero enterarme inmediatamente cuando me retan, para responder a tiempo.
- CA-01 *(ampliada 2026-09-03)*: Si estoy usando la app, el reto aparece como aviso inmediato sin recargar — **sin importar en qué pantalla esté**, no solo en la lista de retos. El aviso muestra rival, disciplina y la configuración de rounds, y lleva al detalle si lo toco.
- CA-02: Si no estoy, recibo una notificación push. *(Todavía sin construir — no existe tabla de notificaciones/suscripciones push; queda como ticket aparte, no parte de esta tanda.)*
- CA-03: El reto persiste en mi lista de retos pendientes — no desaparece por haberse mostrado una vez.
- CA-04: Si recibí el aviso in-app, la notificación push no vuelve a llamar la atención sobre lo mismo una vez que la marqué leída.

**HU-09b: Cancelar un sparring propio**
Como miembro, quiero cancelar un sparring en el que participo antes de que se complete, para salir de un reto que ya no quiero sostener.
- CA-01: Puedo cancelar mientras el reto esté aceptado. Si todavía está pendiente, **solo el retador puede cancelar** — el rival responde con Aceptar/Rechazar, no cancela. *(2026-09-04: precisado tras encontrar la asimetría real en `cancelar_reto()`, migración `20260830020000_dojo_sparring_hallazgos_code_review.sql` — el hallazgo original decía "cualquiera de los dos" sin distinguir el estado pendiente.)*
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

## Rol: Admin y Miembro — torneos

> **Distinto de "Peleas oficiales" (HU-10/11/11b) — aclarado por Marcos el 2026-09-05.** Una pelea oficial es competencia profesional del miembro fuera del dojo; un torneo es un evento que el propio dojo organiza (interno o abierto a externos) para que varios miembros participen y se foguen entre ellos. Un torneo no genera peleas oficiales por sí solo — ver la nota abierta en HU-45 CA-03. Épica nueva, todavía sin construir; **bocetada, no priorizada** — falta pasarla por el mismo desglose crítico que recibieron las demás antes de tener un ticket.

### Epic: Torneos internos y externos

**HU-42: Crear un torneo** *(nueva — bocetada 2026-09-06)*
Como admin, quiero crear un torneo interno o externo indicando disciplina y fecha, para organizar un evento donde varios miembros se midan y se foguen.
- CA-01: Puedo crear un torneo indicando nombre, disciplina, si es interno (solo miembros del dojo) o abierto a externos, y fecha.
- CA-02: El torneo tiene un estado (borrador, en curso, cerrado) — mismo ciclo de vida que un evento de promoción (HU-12/13b).
- CA-03 **[servidor]**: Solo admin y owner pueden crear, editar o cancelar un torneo.

**HU-43: Armar el cuadro de participantes** *(nueva — bocetada 2026-09-06)*
Como admin, quiero agregar participantes al torneo viendo la información de cada uno, para armar los cruces con criterio en vez de al azar.
- CA-01: Puedo agregar miembros del dojo como participantes; en un torneo abierto a externos también puedo agregar un participante libre por nombre, igual que el rival de una pelea oficial (HU-10 CA-01).
- CA-02: Al decidir un cruce veo la ficha de cada candidato a participante — rango, disciplina y, si es miembro del dojo, su historial de peleas — para emparejar peleadores de nivel parecido.
- CA-03: Armo los cruces a mano, un participante contra otro — no es un bracket generado automáticamente ni una eliminatoria con avance automático.
- CA-04 **[servidor]**: Un participante no puede quedar cruzado contra sí mismo, ni en dos cruces sin resolver del mismo torneo a la vez.

**HU-44: Ver la card de cada cruce y registrar su resultado** *(nueva — bocetada 2026-09-06)*
Como admin, quiero ver una card por cada cruce con la información de la pelea y registrar su resultado, para llevar el orden del torneo mientras avanza.
- CA-01: Cada cruce se ve como una card con los dos participantes, la disciplina y su estado (pendiente, jugado).
- CA-02: Puedo registrar resultado y método del cruce (mismo vocabulario que una pelea oficial, HU-10), quedando reflejado en la card.
- CA-03: **Abierto, sin decidir todavía:** si un participante es miembro del dojo, ¿el resultado del cruce entra a su historial de peleas oficiales (HU-10/HU-11) o queda solo dentro del torneo? Un torneo interno de fogueo probablemente no debería mezclarse con el historial competitivo "afuera del dojo" que HU-10/11 describen — a decidir antes de construir esta HU.
- CA-04: Miembros y staff pueden ver el estado de todos los cruces del torneo, jugados y pendientes, sin necesidad de ser admin.

**HU-38: Proyectar el torneo en una pantalla** *(nueva — confirmada en el repaso; reubicada acá el 2026-09-06, vivía suelta bajo "Owner — configuración" sin ninguna otra HU de torneos todavía escrita)*
Como admin, quiero proyectar el cuadro de cruces en un televisor durante el torneo, para que los presentes sigan las peleas.
- CA-01: Abro una vista a pantalla completa, de solo lectura, con control de zoom.
- CA-02: El marcador se actualiza **en tiempo real** al registrarse un resultado (HU-44 CA-02), sin recargar ni esperar.
- CA-03: La pantalla se abre con un enlace propio, **sin necesidad de iniciar sesión** en la tableta o laptop del proyector.
- CA-04 **[servidor]**: Ese enlace da acceso únicamente a la vista de lectura de ese torneo, a nada más.

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

## Rol: Miembro y Admin — ficha del alumno

### Epic: Perfil completo y competencia

**HU-32: Tener toda mi información en un solo lugar** *(nueva — pedido del 2026-08-28)*
Como alumno, quiero que mis datos completos vivan en mi ficha, para no andar buscando cédula, seguro y contacto de emergencia cada vez que me inscribo a un torneo.
- CA-01: Mi ficha reúne datos personales (identificación, nacimiento, teléfono, tipo de sangre), contacto de emergencia, y datos de competencia (federación, seguro deportivo, categoría de peso).
- CA-02: Si soy menor de edad, la ficha incluye los datos del tutor y **la app avisa que sin ellos no puedo inscribirme**.
- CA-03: Puedo editar mis propios datos; el admin también puede editarlos.
- CA-04: La ficha muestra mi rango vigente en cada disciplina y mi récord oficial.
- CA-05 **[servidor]**: Ningún otro miembro puede ver mi ficha.

**HU-32b: Ver qué me falta antes de necesitarlo** *(nueva)*
Como alumno, quiero que la app me diga qué datos me faltan, para no descubrirlo el día de la inscripción.
- CA-01: Los campos requeridos para competir que estén vacíos se marcan visiblemente en mi ficha.
- CA-02: Veo un aviso con el campo puntual que falta y un acceso directo para completarlo.
- CA-03: El admin ve, en la lista de miembros, quiénes tienen la ficha incompleta.

**HU-32c: Generar la ficha para un torneo** *(nueva)*
Como admin o alumno, quiero generar la ficha de inscripción ya armada, para no reunir los datos a mano cada vez.
- CA-01: Un solo control genera un documento con datos personales, rango vigente en la disciplina elegida, peso más reciente y récord.
- CA-02: Si falta algún dato requerido, la app lo indica **antes** de generar, no después.
- CA-03: Elijo la disciplina, porque el rango y el récord dependen de ella.

**HU-33: Llevar mis mediciones** *(nueva — módulo opcional)*
Como alumno de un dojo que activó el módulo, quiero ver mi peso, estatura y composición corporal en el tiempo, para seguir mi progreso físico.
- CA-01: Veo mi última medición y su variación respecto a la anterior.
- CA-02: Veo la evolución en el tiempo de cada métrica.
- CA-03: La app relaciona mi peso actual con mi categoría de peso para competir.
- CA-04: Si el dojo no activó el módulo, **no existe ninguna señal de la función en la interfaz** — ni menú, ni sección vacía, ni control deshabilitado.

**HU-33b: Registrar una medición** *(nueva — módulo opcional)*
Como admin, quiero registrar las mediciones de un alumno, para llevar su seguimiento.
- CA-01: Registro peso, estatura, porcentaje de grasa y de masa muscular con su fecha.
- CA-02: Puedo agregar métricas adicionales sin que haga falta un cambio de sistema.
- CA-03: Queda registrado quién tomó la medición y cuándo.

**HU-34: Activar o desactivar módulos del dojo** *(nueva)*
Como owner, quiero elegir qué módulos opcionales usa mi dojo, para que la app muestre solo lo que me sirve.
- CA-01: Veo la lista de módulos opcionales con su estado.
- CA-02: Al desactivar uno, desaparece de la navegación de todos los roles.
- CA-03 **[servidor]**: Desactivar un módulo **no borra sus datos**; al reactivarlo, el historial sigue ahí.
- CA-04 **[servidor]**: Con el módulo desactivado, sus operaciones se rechazan aunque se llamen directamente.

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

### Epic: Anuncios del dojo

**HU-35: Publicar un anuncio** *(nueva — confirmada en el repaso)*
Como admin, quiero publicar anuncios con imagen para todo el dojo, para avisar de exámenes, cambios de horario y resultados.
- CA-01: Publico con título, texto, categoría e imagen de portada opcional.
- CA-02: Puedo fijar un anuncio arriba del resto.
- CA-03: Puedo restringir un anuncio a planes específicos.
- CA-04 **[servidor]**: **Solo admin y owner publican.** Un miembro que llame directamente al server action recibe error — es un tablón de anuncios, no un foro.

**HU-35b: Comentar y reaccionar** *(nueva)*
Como miembro, quiero comentar y reaccionar a los anuncios, para participar de la vida del dojo.
- CA-01: Puedo comentar un anuncio y reaccionar una sola vez por anuncio.
- CA-02: Veo los comentarios de mis compañeros con su nombre y rango.
- CA-03: El admin puede **ocultar** un comentario sin borrarlo.
- CA-04: Si el dojo no activó el módulo, la sección no existe en la navegación.

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

**HU-36: Recibir los avisos por el canal correcto** *(nueva — confirmada en el repaso)*
Como miembro, quiero que los avisos importantes me lleguen por correo y no solo dentro de la app, para no perderme un vencimiento de pago.
- CA-01: Los avisos de pago — por vencer, vencido, comprobante aprobado o rechazado — me llegan **siempre por correo**, además de in-app.
- CA-02: El resultado de una promoción y la cancelación de una clase también llegan por correo.
- CA-03: Los retos de sparring y los recordatorios de clase llegan por push e in-app.
- CA-04: El correo incluye el dato concreto — monto, fecha, clase — y no solo "tenés una notificación".
- CA-05 **[servidor]**: Un mismo aviso no se envía dos veces por el mismo canal para el mismo período.

**HU-36b: Elegir qué avisos quiero** *(nueva)*
Como miembro, quiero decidir por qué canal me llega cada tipo de aviso, para no tener que bloquear todo.
- CA-01: Veo la lista de tipos de aviso y elijo canales para cada uno.
- CA-02: Puedo activar o desactivar las notificaciones push **por dispositivo**.
- CA-03 **[servidor]**: Los avisos de pago no se pueden desactivar por completo — el correo se mantiene, porque afecta la vigencia de la membresía.

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

**HU-37: Editar mi perfil y mi foto** *(nueva — quedó pendiente en v1)*
Como miembro, quiero editar mi nombre, teléfono y foto de perfil, para que mi ficha esté al día.
- CA-01: Puedo editar mis datos básicos y subir una foto.
- CA-02: La foto se ve en el avatar de toda la app, con el anillo de mi rango.
- CA-03: Si no tengo foto, se muestran mis iniciales — nunca un espacio en blanco.

**HU-39: Ver la página pública del dojo** *(nueva — confirmada en el repaso)*
Como owner, quiero una página pública del dojo editable desde la app, para poder compartirla con interesados.
- CA-01: Edito historia, instructores, programas, logros y ubicación **desde la app**, sin tocar código.
- CA-02: La página es pública y usa el tema del dojo.
- CA-03: Puedo despublicarla mientras la preparo.

**HU-40: Ver el pulso del dojo sin salir de mi inicio** *(nueva)*
Como instructor o dueño, quiero ver lo que necesita atención hoy debajo de mi propio inicio, para no tener que entrar a otra sección para saber si hay algo pendiente.
- CA-01: Bajo mi inicio personal veo un bloque con los comprobantes esperando revisión, las clases de hoy y los ascensos próximos.
- CA-02: Cada dato lleva a la pantalla donde se resuelve.
- CA-03: **No aparecen números de negocio** (ingresos, morosidad): esos viven en Finanzas y son del dueño.
- CA-04: Un alumno no ve este bloque en absoluto.
- CA-05: Si no hay nada pendiente, el bloque lo dice — no se muestra vacío ni se esconde.

**HU-41: Ver la app como la ve un alumno** *(nueva)*
Como instructor o dueño, quiero mirar la app tal como la ve un alumno, para poder ayudar a alguien sin adivinar qué está viendo.
- CA-01: Puedo activar y desactivar el modo desde mi menú de usuario.
- CA-02: Con el modo activo desaparecen las secciones de gestión y de negocio de la navegación.
- CA-03: Un aviso permanente indica que estoy en ese modo, para no confundirlo con un problema de permisos.
- CA-04 **[servidor]**: **Es una preferencia de interfaz, no un cambio de permisos.** Mi rol real no cambia: si pido un dato de gestión estando en ese modo, lo obtengo. Ocultar una sección nunca fue un control de acceso.

---

## Rol: Sistema

### Epic: Procesos automáticos

**HU-31: Un solo proceso diario mantiene el estado al día** *(nueva)*
Como sistema, quiero ejecutar un proceso diario que resuelva todo lo que vence por tiempo, para que el estado de la app sea correcto sin intervención manual.
- CA-01: Expira los sparrings pendientes o aceptados fuera de plazo (HU-09c).
- CA-02: Envía los recordatorios de pago próximos a vencer, sin duplicar (HU-20).
- CA-03: Marca como vencidas las suscripciones que pasaron su período.
- CA-04: Si el proceso falla, queda registro y el intento siguiente no duplica efectos.

**HU-31b: Avisar de la clase que se acerca** *(nueva)*
Como sistema, quiero avisar a los inscritos antes de su clase, para bajar las ausencias.
- CA-01: Un proceso frecuente envía el recordatorio con la antelación configurada en cada clase.
- CA-02 **[servidor]**: Cada clase recibe su recordatorio una sola vez, aunque el proceso corra muchas veces.
- CA-03: Una clase cancelada no genera recordatorio.

---

## Trazabilidad HU → requerimiento

| Epic | HU | RF principales |
|---|---|---|
| Autenticación y pertenencia | HU-22, 24, 25, 26 | RF-19, RF-20, RNF-02 |
| Disciplinas y rangos | HU-00, 00b, 27 | RF-01, RF-02, RF-02b a RF-02d, RNF-06 |
| Miembros | HU-28 | RF-20 |
| Calendario y clases | HU-01, 02, 02b, 02c, 02d, 03, 04, 04b | RF-03 a RF-04c |
| Sparring | HU-05 a HU-09c, 07b, 07c | RF-05 a RF-08 |
| Peleas oficiales | HU-10, 11, 11b | RF-09, RF-10 |
| Torneos *(bocetada, sin priorizar)* | HU-42, 43, 44, 38 | — |
| Promociones | HU-12, 12b, 13, 13b, 14 | RF-11 a RF-12b |
| Contenido | HU-15, 15b | RF-13, RF-13b |
| Challenges | HU-16 | RF-14 |
| Membresías y pagos | HU-16b, 16c, 17, 17b, 18, 19, 20, 23 | RF-15, RF-16, RF-17, RF-21, RF-22 |
| Configuración | HU-21, 29, 30 | RF-18, RF-16 |
| Anuncios del dojo | HU-35, 35b | RF-13c |
| Notificaciones por canal | HU-36, 36b | RF-17, RF-17b |
| Perfil y página del dojo | HU-37, 39 | RF-18c |
| Inicio del staff y ver como alumno | HU-40, 41 | RF-23 |
| Ficha del alumno | HU-32, 32b, 32c | RF-12c, RF-12d |
| Mediciones (opcional) | HU-33, 33b | RF-12e |
| Módulos opcionales | HU-34 | RF-12f |
| Procesos automáticos | HU-31, 31b | RF-06c, RF-17, RF-17c |

## Pendiente

- **`DESIGN.md`** — cada HU de esta lista debería referenciar la pantalla donde vive, como hace el de [[Proyectos/Tacha/DESIGN|Tacha]]. Se agrega esa columna cuando exista el inventario de pantallas.
- **Análisis de complejidad y orden de sprints** — el equivalente al `analisis-complejidad-viabilidad.md` de Tacha, con estimación por HU y dependencias, para ordenar el bloque 2 del plan.
