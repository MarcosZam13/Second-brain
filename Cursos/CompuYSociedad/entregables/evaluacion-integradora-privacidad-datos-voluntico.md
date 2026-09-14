---
curso: CompuYSociedad
tema: "Evaluación Integradora: Privacidad, seguridad y responsabilidad digital en VolunTico"
fecha: 2026-09-08
tipo: entregable
entregable_de: "[[Cursos/CompuYSociedad/apuntes/evaluacion-integradora-privacidad-datos-leyes-8968-9048]]"
estado: borrador
tags: [ley-8968, ley-9048, proteccion-datos, delitos-informaticos, trabajo-grupal, voluntico]
---

# Evaluación Integradora: Privacidad, seguridad y responsabilidad digital en VolunTico

Ver también: [[Cursos/CompuYSociedad/apuntes/evaluacion-integradora-privacidad-datos-leyes-8968-9048|Instrucciones completas + rúbrica de coevaluación]] · [[Cursos/CompuYSociedad/entregables/mi-empresa-voluntico|Mi Empresa — VolunTico]] · [[Cursos/CompuYSociedad/entregas]]

**Modalidad:** equipo · **Entregables:** documento (4–6 páginas) + video (4–6 min) · **Valor:** 15 puntos en el curso (la rúbrica de coevaluación puntúa internamente sobre 100 y se traduce a esos 15) · **Fecha límite: 2026-09-16, 8:00 a.m., entrega en el foro del curso.**

**Coevaluación entre equipos:** el profesor asigna, después de que todos entreguen, qué equipo evalúa a cuál usando la misma rúbrica de 6 criterios (ver [[Cursos/CompuYSociedad/apuntes/evaluacion-integradora-privacidad-datos-leyes-8968-9048|apuntes]]). No hay que hacer nada adicional para esto — solo entregar documento y video con enlace/permisos habilitados para que el otro equipo pueda verlos.

Archivo entregable generado: `EvaluacionIntegradora_VolunTico.docx`.

## Pregunta guía

¿Qué tendría que cambiar o diseñar VolunTico para que privacidad y seguridad formen parte del negocio desde el inicio y no sean una corrección posterior?

---

## 1. Contexto y mapa de datos

VolunTico es una plataforma web (y, a futuro, app móvil) que conecta a personas que quieren viajar por Costa Rica con organizaciones, comunidades y emprendimientos que necesitan colaboración voluntaria, a cambio de beneficios como hospedaje, alimentación o experiencias locales. Atiende dos públicos a la vez —viajeros/voluntarios y organizaciones anfitrionas— y opera principalmente a través de perfiles, un buscador filtrable por ubicación/duración/tipo de actividad, y un sistema de solicitudes de participación.

| Dato / categoría | ¿De quién? | ¿Para qué? | ¿Dónde se guarda? | ¿Quién accede? |
|---|---|---|---|---|
| Registro (nombre, correo, teléfono, contraseña) | Viajero/voluntario | Crear cuenta y autenticarse | Base de datos de usuarios (backend) | Backend, soporte |
| Perfil de habilidades e intereses (idiomas, programación, enseñanza, agricultura, fotografía, etc.) | Viajero/voluntario | Emparejar con oportunidades de voluntariado | Base de datos de perfiles | Organizaciones a las que aplica, backend |
| Necesidades especiales del viaje (alergias alimentarias, condiciones de salud relevantes para el hospedaje) | Viajero/voluntario | Que la organización anfitriona pueda ofrecer alimentación/hospedaje seguros | Base de datos de perfiles (campo sensible) | Solo la organización confirmada, backend |
| Solicitudes de participación (a qué proyectos aplicó, estado, fechas) | Viajero/voluntario | Gestionar el flujo de aprobación de voluntariados | Base de datos de solicitudes | Organización receptora, backend, soporte (en disputas) |
| Datos de la organización (nombre, ubicación, contacto, tipo de proyecto, beneficios ofrecidos) | Organización / comunidad / emprendimiento | Publicar oportunidades de voluntariado | Base de datos de organizaciones | Viajeros que navegan el buscador, backend |
| Calificaciones y comentarios post-voluntariado | Viajero y organización (mutuo) | Generar confianza/reputación en la plataforma | Base de datos de reseñas | Público en general (visible), backend |
| Nómina y cargas sociales (salario, número de seguro CCSS) | Colaboradores internos de VolunTico (10 personas) | Pago de planilla y cumplimiento patronal | Sistema de RRHH/contabilidad | Gerencia, encargado administrativo |

## 2. Ley 8968 aplicada: protección de datos personales

- **Finalidad y minimización.** VolunTico no necesita el número de cédula ni la dirección exacta de un viajero para emparejarlo con un voluntariado — con nombre, contacto, perfil de habilidades y preferencias de ubicación alcanza. El campo de "necesidades especiales" (alergias, salud) solo se pide si el viajero decide postularse a un proyecto con hospedaje/alimentación, no en el registro general.
- **Información y consentimiento.** Al crear la cuenta, la persona debe ver un aviso corto (no un documento legal de 10 páginas) que explique qué datos se piden, para qué los usa VolunTico y para qué los ve la organización a la que aplique. El consentimiento se registra con un checkbox obligatorio y queda con fecha/hora en el registro de la cuenta.
- **Datos sensibles.** Las "necesidades especiales" (alimentarias, de salud) son el dato más sensible que maneja la plataforma. Solo se comparten con la organización específica una vez que la solicitud fue aceptada, nunca de forma pública ni con otras organizaciones.
- **Calidad y uso de la información.** El perfil de habilidades debe poder editarse y actualizarse por el propio usuario; los datos de contacto de una organización que cierra operaciones se marcan como inactivos en vez de seguir apareciendo en el buscador.
- **Acceso y derechos.** Una persona puede pedir, desde su perfil o escribiendo a soporte@voluntico.cr, ver qué datos tiene la plataforma sobre ella, corregirlos o pedir que se elimine su cuenta. VolunTico responde en un plazo definido (ej. 10 días hábiles).
- **Seguridad y confidencialidad.** Acceso a la base de datos de usuarios restringido al equipo de backend y soporte, con cuentas individuales (no una cuenta compartida de administrador). Contraseñas de usuarios almacenadas con hash, nunca en texto plano.
- **Terceros y ciclo de vida.** El proveedor de hosting/base de datos y, si se implementa cobro de comisiones, la pasarela de pago, reciben datos bajo un acuerdo de tratamiento de datos. Las cuentas inactivas por más de 2 años y sin voluntariados activos se eliminan o anonimizan.

## 3. Ley 9048 aplicada: ciberconducta y uso de sistemas

- **Acceso.** Solo el equipo de backend accede a la base de datos de producción; el resto del equipo interno (frontend, diseño, RRHH) trabaja contra un entorno de pruebas con datos ficticios, no datos reales de usuarios.
- **Credenciales.** Cada colaborador tiene su propia cuenta de administrador de la plataforma; está prohibido compartir contraseñas o usar una cuenta genérica de "admin". Autenticación de dos factores obligatoria para accesos administrativos.
- **Datos y sistemas.** Prohibido exportar la base de datos de usuarios u organizaciones fuera del sistema (a una nube personal, a un Excel local) salvo autorización expresa de la gerencia y con fines de trabajo definidos.
- **Fraude y engaño digital.** VolunTico verifica la identidad de cada organización antes de permitirle publicar una oportunidad (cédula jurídica o física, datos de contacto verificables), precisamente para prevenir perfiles falsos que ofrezcan voluntariados inexistentes o pidan pagos por adelantado a los viajeros. La plataforma nunca gestiona pagos de "depósitos" o "reservas" fuera de sus propios canales.
- **Herramientas y pruebas.** Cualquier prueba de seguridad (escaneo de vulnerabilidades, pentesting) sobre la plataforma debe ser autorizada por el desarrollador backend y documentada; nadie del equipo prueba vulnerabilidades sobre el sistema en producción sin permiso.
- **Reporte y evidencia.** Un colaborador que detecta un acceso sospechoso, una organización con comportamiento fraudulento o una posible fuga de datos lo reporta de inmediato al gerente y al desarrollador backend, quienes deciden si se contiene el acceso, se notifica a los usuarios afectados o se documenta como incidente.

## 4. La empresa vista desde dos roles

| Tema | Como empresarios (VolunTico) | Como colaboradores |
|---|---|---|
| Datos personales | Diseñar qué datos pedir, el aviso de privacidad, y auditar que solo se use la información para emparejar viajeros con proyectos | Usar el perfil de un viajero o los datos de una organización solo para la tarea asignada (soporte, matching), nunca para fines personales |
| Accesos | Definir qué rol de la plataforma (backend, soporte, RRHH) accede a qué base de datos, y revocar accesos al salir alguien del equipo | Pedir el acceso que falte por el canal formal, no usar la cuenta de un compañero para "resolver rápido" |
| Seguridad | Financiar MFA, cifrado, backups y capacitación básica en seguridad para el equipo de 10 personas | Activar el MFA, no reutilizar contraseñas de otras cuentas, reportar un correo sospechoso antes de hacer clic |
| Incidentes | El gerente y el desarrollador backend deciden, contienen y documentan cualquier incidente (fuga, cuenta comprometida, organización fraudulenta) | Reportar de inmediato cualquier acceso raro, organización sospechosa o pérdida de su propio dispositivo de trabajo |
| Cultura | Incentivar que reportar un error o incidente no tenga represalia, para que se reporte rápido y no se oculte | No compartir capturas de pantalla de perfiles de usuarios ni comentar datos de viajeros/organizaciones fuera del trabajo |

## 5. Matriz de tres riesgos propios de VolunTico

| Riesgo / escenario | Personas o activos afectados | Prevención | Respuesta | Rol clave |
|---|---|---|---|---|
| Un colaborador exporta el listado completo de viajeros (incluyendo fechas de viaje y necesidades especiales de salud) a su nube personal "para trabajar desde casa" | Viajeros registrados (riesgo de que se sepa cuándo están fuera de casa o su condición de salud) y VolunTico (sanción bajo Ley 8968) | Prohibir exportaciones fuera del sistema salvo autorización; acceso mínimo por rol; cifrado de campos sensibles | Revocar el acceso, identificar qué se copió, notificar a los usuarios afectados y a la gerencia, documentar el incidente | Desarrollador backend (administrador de datos) |
| Un perfil de "organización" falso publica un voluntariado inexistente y pide un depósito de reserva por fuera de la plataforma a los viajeros interesados | Viajeros (pérdida económica, riesgo de estafa tipo phishing) | Verificación de identidad obligatoria antes de publicar oportunidades; prohibir explícitamente pagos fuera de los canales de VolunTico; advertencia visible en la plataforma | Suspender la cuenta de inmediato, alertar a los viajeros que aplicaron, reportar a las autoridades si hubo perjuicio económico | Equipo de soporte/moderación |
| Un excolaborador (por ejemplo, un desarrollador que ya no trabaja en VolunTico) conserva credenciales de acceso al backend y las usa para alterar o borrar datos de organizaciones | Organizaciones aliadas (pérdida de información, daño reputacional a VolunTico) | Cuentas individuales, nunca compartidas; revocar accesos el mismo día que alguien deja el equipo; rotar credenciales administrativas periódicamente | Revisar logs de acceso, restaurar desde respaldo, notificar a las organizaciones afectadas, evaluar denuncia si hay daño intencional | Gerente + desarrollador backend |

## 6. Plan de implementación 30 / 60 / 90 días

**30 días — bajo costo, alto impacto**
1. Activar autenticación de dos factores (MFA) para las cuentas administrativas y de backend. *Evidencia: MFA activado, capturas de configuración.*
2. Publicar el aviso de privacidad y el checkbox de consentimiento en el registro de usuarios. *Evidencia: aviso visible en el formulario de registro.*
3. Pasar de una cuenta de administrador compartida a cuentas individuales para los 10 colaboradores. *Evidencia: lista de cuentas creadas, contraseña genérica desactivada.*

**60 días — requieren coordinación**
1. Redactar y aprobar una política interna de uso aceptable (qué se puede y no se puede hacer con los sistemas) y un proceso simple de reporte de incidentes. *Evidencia: política aprobada por la gerencia.*
2. Implementar verificación de identidad para organizaciones antes de que puedan publicar una oportunidad. *Evidencia: formulario de verificación en producción.*
3. Capacitación de una hora al equipo completo sobre la Ley 8968 y la Ley 9048 aplicadas a su trabajo diario. *Evidencia: sesión realizada, lista de asistencia.*

**90 días — presupuesto o cambios de producto**
1. Cifrado de los campos sensibles (necesidades especiales de salud, ubicación de viaje) en tránsito y en reposo. *Evidencia: verificación técnica del cifrado.*
2. Firmar un acuerdo de tratamiento de datos con el proveedor de hosting y, si aplica, con la pasarela de pago. *Evidencia: contrato firmado.*
3. Simulacro de incidente (fuga de datos simulada) para probar el plan de respuesta del punto anterior. *Evidencia: reporte del simulacro y ajustes identificados.*

---

## Video reflexivo (4–6 min) — guía de contenido

*No es un guion para leer — es la guía de qué debe aparecer en cada bloque, para discutirlo en voz propia el día de la grabación.*

| Tiempo | Bloque | Idea para VolunTico |
|---|---|---|
| 0:00–0:45 | Contexto | VolunTico conecta viajeros con voluntariados; maneja datos de dos públicos (viajeros y organizaciones) más datos sensibles de salud/alimentación cuando hay hospedaje de por medio — por eso privacidad y ciberseguridad importan desde el diseño |
| 0:45–2:15 | Decisiones | Ejemplos: pasar de cuenta de administrador compartida a cuentas individuales + MFA; verificación de identidad de organizaciones antes de publicar |
| 2:15–3:30 | Doble perspectiva | Como empresarios, decidir qué datos pedir y auditar accesos; como colaboradores, no reutilizar contraseñas ni exportar datos por conveniencia |
| 3:30–5:00 | Tensión o dilema | Verificar la identidad de cada organización nueva agrega fricción y retrasa que publiquen su primer voluntariado — tensión entre velocidad de crecimiento y prevención de fraude |
| 5:00–6:00 | Cierre | Aprendizaje: la seguridad no es solo técnica, es también decidir qué no recolectar. Práctica que mantendrían: nunca gestionar pagos fuera de la propia plataforma |

## Control interno (no va en la entrega)

### Checklist contra la rúbrica de coevaluación

- [x] Aplicación de la Ley N.° 8968 (20%) — sección 2 completa con los 7 ejes
- [x] Aplicación de la Ley N.° 9048 (20%) — sección 3 completa
- [x] Perspectiva como empresarios (15%) y como colaboradores (15%) — tabla de la sección 4
- [x] Riesgos y medidas de prevención (15%) — matriz de la sección 5, con un riesgo de datos personales y dos de acceso/engaño/sabotaje
- [ ] Análisis crítico y aprendizajes del video (15%) — depende de la grabación real, no se puede marcar desde el borrador escrito

### Pendiente antes de entregar

1. **Revisar los tres riesgos de la sección 5 con el equipo** — se escribieron como propuesta razonable a partir del modelo de negocio de VolunTico, pero conviene que el equipo los valide o cambie por otros que conozcan mejor.
2. **Grabar el video** siguiendo la guía de bloques, con participación de todos los integrantes.
3. **Completar nombres reales de los integrantes** en la portada del documento (mismo pendiente que quedó abierto en `mi-empresa-voluntico.md`).
4. Exportar/confirmar el documento final como PDF o DOCX identificado con el nombre de la empresa y las personas integrantes.
5. Entregar en el foro del curso antes del 2026-09-16, 8:00 a.m., con el video como enlace con permisos de visualización habilitados (no requiere edición profesional).
