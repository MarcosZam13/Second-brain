---
proyecto: AsistenciasTEC
tipo: backlog
fecha: 2026-09-09
---

# Product Backlog — Asistencias TEC

Ver también: [[Proyectos/AsistenciasTEC/README|README]]

Convertido de `_fuentes/Backlog.xlsx` (hoja "Requerimiento", la única con contenido real del proyecto — "Copia de Requerimiento" y "Ejemplo" son plantilla vacía/de muestra del curso, no se importaron). IDs y texto tal como los dejó el profesor/equipo, sin corregir redacción.

## Sedes y perfil

| ID | Enunciado | Detalle |
|---|---|---|
| AS-01 | Sedes | Como usuario deseo poder usar la plataforma en diferentes sedes del TEC |
| AS-02 | Sedes | Conectar el endpoint del proyecto de registro |
| AS-03 | Mi perfil (estudiante/profesor) | Como usuario puedo ver mi perfil — únicamente de referencia visual para observar el nombre del usuario |
| AS-04 | Mi perfil | Como usuario puedo editar mis datos de perfil |
| AS-05 | Mi perfil | Como usuario puedo deshabilitar mi cuenta (+ advertencia antes de la acción) |
| AS-06 | — | *(vacío en el spreadsheet original — ver nota de revisión)* |

## Vista de estudiante

| ID | Enunciado | Detalle |
|---|---|---|
| AS-07 | Vista de estudiante | Como estudiante puedo ver las asistencias disponibles — si no hay ninguna, no se muestra nada |
| AS-08 | Vista de estudiante | Como estudiante puedo filtrar asistencias por ámbito (asistencia especiales, horas asistente, tutoría, hora estudiante) |
| AS-09 | Vista de estudiante | Como estudiante puedo filtrar asistencias por sede |
| AS-10 | Vista de estudiante | Como estudiante puedo postularme a una asistencia disponible |
| AS-11 | Vista de estudiante | Como estudiante puedo ver el estado de mi asistencia — *pendiente aclarar dónde/desde qué vista* |
| AS-12 | Vista de estudiante | Como estudiante puedo cancelar una solicitud de formar parte de una asistencia |
| AS-13 | Vista de estudiante | Como estudiante puedo informar mi situación de cumplimiento de requerimientos durante el llenado del formulario de la asistencia |
| AS-14 | Formulario de solicitud | *(vacío en el spreadsheet original — ver nota de revisión)* |

## Vista de profesor

| ID | Enunciado | Detalle |
|---|---|---|
| AS-15 | Vista de profesor | Como profesor puedo ver las solicitudes pendientes donde solicito asistentes |
| AS-16 | Vista de profesor | Como profesor puedo ver las asistencias activas con sus respectivos asistentes nombrados |
| AS-17 | Vista de profesor | Como profesor puedo ver los postulantes de mis solicitudes de asistencia |
| AS-18 | Vista de profesor | Como profesor puedo aceptar los postulantes que deseo para la asistencia |
| AS-19 | Vista de profesor | Como profesor puedo solicitar editar los datos de una asistencia ya aprobada por el administrador de la plataforma (tras ser aprobada por el superadmin) |

## Vista de super admin

| ID | Enunciado | Detalle |
|---|---|---|
| *(sin ID)* | Vista de super admin | Como super admin puedo agregar correos de profesores — *ver nota de revisión, numeración pendiente* |
| AS-20 | Vista de super admin | Como super admin puedo eliminar correos de profesores |
| AS-21 | Vista de super admin | Como super admin puedo revisar las solicitudes de apertura de asistencia |
| AS-22 | Vista de super admin | Como super admin puedo crear una asistencia |
| AS-23 | Vista de super admin | Como super admin puedo editar una asistencia |
| AS-24 | Vista de super admin | Como super admin puedo borrar una asistencia |
| AS-25 | Vista de super admin | Como super admin puedo habilitar una asistencia |
| AS-26 | Vista de super admin | Como super admin puedo inhabilitar una asistencia |
| AS-27 | Vista de super admin | Como super admin puedo aceptar la solicitud de un estudiante a una asistencia |
| AS-28 | Vista de super admin | Como super admin puedo denegar la solicitud de un estudiante a una asistencia |

## Notificaciones

| ID | Enunciado | Detalle |
|---|---|---|
| AS-29 | Notificaciones | Como estudiante deseo ser notificado cuando se modifican datos de interés de una asistencia (horas, profesor a cargo, horario, etc.) |
| AS-30 | Notificaciones | Como estudiante deseo ser notificado con el progreso de mi solicitud |
| AS-31 | Notificaciones | Como estudiante deseo ser notificado con el resultado de mi solicitud (correo/web) |

## Notas de revisión (lectura crítica, 2026-09-09)

Cosas que valdría la pena aclarar con el profesor/equipo antes de estimar sprints, no correcciones hechas unilateralmente al backlog:

1. **AS-01 y AS-02 no tienen forma de HU** (rol + quiero + para). AS-01 es en realidad un requisito no funcional (soporte multi-sede transversal a todo el sistema, no una acción puntual de un actor) y AS-02 es una tarea técnica de integración ("conectar el endpoint del proyecto de registro" — ¿de qué proyecto? ¿ya existe un sistema de registro/autenticación externo al que esta plataforma se conecta?). Vale la pena separarlas del resto: no son "features" que se demuestren en un sprint review de la misma forma.
2. **AS-06 y AS-14 están vacíos** en el archivo original — son huecos de numeración (¿se borró contenido, o el ID está reservado para algo que todavía no se definió?). Si nadie los llena antes del primer sprint planning, van a generar confusión al mapear IDs a Jira.
3. **Falta un ID** en la fila de "Como super admin puedo agregar correos de profesores" — quedó entre AS-19 y AS-20 sin número propio. Correr la numeración desde ahí (o insertar como AS-19.1) antes de importar a Jira, para no reasignar IDs que ya se hayan citado en otro lado.
4. **Contradicción de flujo entre AS-19 y la sección de super admin**: AS-19 asume que una asistencia pasa por un estado "aprobada por el administrador" antes de que el profesor pueda pedir editarla — pero no existe ninguna HU de "el profesor solicita crear/abrir una asistencia" (AS-15 solo cubre ver solicitudes de *asistentes*, no de *apertura de asistencia*). Mientras tanto, el superadmin tiene HU directas de "crear una asistencia" (AS-22) sin pasar por una solicitud previa del profesor. Antes de diseñar la base de datos o las pantallas, hay que resolver: ¿quién origina una asistencia nueva — el profesor pide y el superadmin aprueba, o el superadmin la crea directamente y el profesor solo la gestiona después? Ahora mismo el backlog sugiere ambas cosas a la vez.
5. **AS-11** señala explícitamente la misma duda ("¿Dónde la puede ver? ¿De dónde?") — ya viene marcada como pendiente en el spreadsheet original, no es hallazgo nuevo.

Estas dudas son buen material para la primera reunión de refinamiento del backlog — mejor levantarlas ahí que asumir una interpretación y descubrir el choque a mitad de sprint.
