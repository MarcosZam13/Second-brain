---
curso: Seguridad
tema: Tarea 1 — Legislación (El Contrato Roto), rol Devs
fecha: 2026-08-18
entregable_de: "[[Cursos/Seguridad/apuntes/tarea-1-legislacion-costarricense]]"
estado: borrador
tags: [tarea1, devs, ley8968, ley7975, ley6683]
---

# Tarea 1 — Rol: The Devs (La Defensa)

Ver también: [[Cursos/Seguridad/apuntes/tarea-1-legislacion-costarricense|Instrucciones completas]] · [[Cursos/Seguridad/apuntes/marco-legal-digital-ciberseguridad-cr|Marco legal ampliado]] · [[Cursos/Seguridad/entregas]]

Entrega: 2026-09-01, 23:50. Doc Word, máx. 5 páginas + portada (anexo de prompts aparte si se usa IA).

## Lo que debe demostrar el documento (rúbrica Devs, 20 pts)

- [ ] Citar la ley aplicable a cada dato que recolecta MediSync CR
- [ ] Demostrar cumplimiento del nivel **ALTO** del Reglamento a la Ley 8968 (Art. 24 + medidas técnicas concretas — cifrado AES-256, 2FA, logs, backups)
- [ ] Argumentar protección del algoritmo de diagnóstico bajo **Ley 7975** (secreto comercial) y **Ley 6683** (derechos de autor sobre el código)
- [ ] Consentimiento informado y principio de finalidad (explícito, previo, por escrito, limitado al fin declarado)
- [ ] Prevención de delitos (Ley 9048) — controles técnicos que habrían impedido el acceso del ex-empleado
- [ ] Anexo de prompts de IA si se usó (fuera de las 5 páginas)

## Borrador

### Introducción

MediSync CR sostiene que su operación cumple los marcos legales costarricenses aplicables al tratamiento de datos personales, la protección de su propiedad intelectual y la prevención de delitos informáticos. El presente escrito responde a los tres señalamientos de la denuncia — (1) supuesto intercambio de historiales clínicos con aseguradoras sin consentimiento explícito, (2) replicación del algoritmo de diagnóstico por un competidor, y (3) acceso remoto de un ex-empleado tras su despido — con fundamento en la Ley N.° 8968, su Reglamento, la Ley N.° 7975, la Ley N.° 6683 y la Ley N.° 9048.

### I. Ley aplicable a cada dato recolectado

| Dato recolectado | Naturaleza | Ley aplicable |
|---|---|---|
| Nombre, cédula, fecha de nacimiento | Dato personal | Ley 8968 (dato personal ordinario) |
| Historial clínico, diagnósticos, medicamentos, imágenes médicas | Dato sensible (salud) | Ley 8968 + Reglamento, nivel de seguridad **Alto**; Art. 24 Constitución (intimidad) |
| Ubicación | Dato personal | Ley 8968 |
| Datos de pago | Dato personal (financiero) | Ley 8968; en lo aplicable, normativa de protección al consumidor financiero |
| Algoritmo de diagnóstico asistido por IA | Activo de propiedad intelectual | Ley 7975 (secreto comercial/know-how) + Ley 6683 (obra protegida por derecho de autor, Art. 4 inciso ñ) |
| Código fuente de la plataforma | Obra intelectual | Ley 6683, Art. 4 inciso ñ y Art. 40 (titularidad patrimonial del empleador, MediSync, sobre el código desarrollado por su planilla) |

Todo dato de salud recolectado por MediSync se clasifica como **dato sensible** bajo el Art. 3 de la Ley 8968, por lo que su tratamiento exige consentimiento informado, expreso y **por escrito**, y obliga a MediSync como Responsable de la Base de Datos a aplicar el nivel de seguridad más alto que define el Reglamento.

### II. Cumplimiento del nivel ALTO (Constitución Art. 24, Ley 8968 Art. 10, y su Reglamento)

El fundamento constitucional de la protección reforzada que MediSync aplica a los datos de salud es el **Artículo 24 de la Constitución Política**, que garantiza el derecho a la intimidad, la libertad y el secreto de las comunicaciones, y declara inviolables los documentos privados y las comunicaciones de los habitantes de la República. La Sala Constitucional ha precisado el alcance de esta garantía: la **Resolución N.° 5802-1999** subraya su carácter preventivo frente a tratos discriminatorios fundados en datos sensibles como el estado de salud, y la **Resolución N.° 4847-1999** conceptualiza la autodeterminación informativa como un derecho activo mediante el cual el paciente ejerce dominio directo sobre la circulación de su propia información.

Sobre esa base constitucional, el Reglamento a la Ley 8968 clasifica las bases de datos de salud en el nivel **Alto** por tratarse de datos sensibles, y el **Artículo 10 de la Ley 8968 ("Seguridad de los datos")** obliga al responsable de la base de datos a adoptar las medidas técnicas y de organización necesarias para garantizar su seguridad. MediSync CR declara las siguientes medidas, correspondientes a ese nivel:

- **Cifrado AES-256** de los historiales clínicos e imágenes médicas, tanto en reposo (base de datos) como en tránsito (TLS en toda comunicación cliente-servidor).
- **Autenticación de doble factor (2FA)** para todo acceso de médicos, personal administrativo y pacientes a información clínica.
- **Logs de acceso** inmutables por cada consulta o modificación de un expediente, con trazabilidad de usuario, fecha y acción.
- **Backups diarios** cifrados, que garantizan disponibilidad sin exponer la confidencialidad del dato ante una pérdida o incidente.

Estas cuatro medidas, tomadas en conjunto, satisfacen el estándar de "medidas de seguridad técnicas y organizativas" que exige el Art. 10 para datos de nivel Alto, y exceden el nivel Medio que aplicaría a datos personales ordinarios no sensibles.

### III. Protección de la propiedad intelectual del algoritmo (Ley 7975 y Ley 6683)

**Bajo la Ley 7975 (información no divulgada):** el algoritmo de diagnóstico asistido por IA cumple las tres condiciones del know-how protegido: (1) tiene valor comercial evidente al ser el diferenciador competitivo de MediSync frente a otras plataformas de gestión médica, (2) se ha mantenido en secreto — no ha sido publicado, registrado públicamente ni divulgado a terceros sin acuerdo de confidencialidad, y (3) MediSync ha tomado medidas razonables de protección: control de acceso restringido al código del modelo, acuerdos de confidencialidad (NDA) con el equipo de desarrollo, y segmentación de credenciales para que ningún desarrollador individual tenga acceso íntegro al pipeline de entrenamiento. Si el competidor replicó el algoritmo, la vía legal correspondiente es la acción por apropiación indebida de información no divulgada, no una falla atribuible a MediSync.

**Bajo la Ley 6683 (derechos de autor):** el código fuente del algoritmo se asimila a obra literaria desde su creación (Art. 4 inciso ñ), sin necesidad de registro para existir la protección, aunque se recomienda el registro ante el Registro Nacional de Derechos de Autor como prueba de anterioridad. Al haber sido desarrollado por personal asalariado de MediSync en el ejercicio de sus funciones, la titularidad patrimonial corresponde a la empresa (Art. 40). Esto habilita a MediSync a ejercer acción civil y penal contra la reproducción o transformación no autorizada de su código por parte del competidor.

### IV. Consentimiento informado y principio de finalidad

Respecto al cargo de compartir historiales clínicos con aseguradoras: la Ley 8968 exige que el consentimiento para datos sensibles sea informado, expreso y **por escrito** — el silencio o la aceptación genérica de términos y condiciones no es válida. MediSync sostiene que su flujo de registro incorpora una casilla de consentimiento **específica y separada** de los términos generales, en la que el paciente autoriza expresamente el envío de su historial a la aseguradora que él mismo designa, con la finalidad declarada de gestionar el reembolso o la cobertura de sus citas — cumpliendo el principio de finalidad, ya que el dato solo se usa para el fin que motivó su recolección (la atención médica y su cobro) y no para un fin distinto no autorizado por el paciente. Este consentimiento es previo al primer envío de datos a cualquier aseguradora y queda registrado con fecha y versión del texto aceptado, como evidencia ante una eventual auditoría de PRODHAB.

### V. Prevención de delitos informáticos (Ley 9048) — caso del ex-empleado

La Ley 9048 tipifica el acceso no autorizado a sistemas de información. MediSync argumenta que ya contaba, al momento del incidente, con controles técnicos diseñados para impedir exactamente este escenario:

- **2FA** en todas las cuentas con acceso a la base de datos, lo que exige un segundo factor que un ex-empleado sin dispositivo corporativo activo no debería poder generar.
- **Logs de acceso**, que fueron precisamente el mecanismo que permitió detectar y documentar el acceso indebido — evidencia técnica que hoy sustenta la denuncia penal contra el ex-empleado bajo la Ley 9048, no una omisión de MediSync.

El punto de falla real fue procedimental, no técnico: la cuenta del ex-empleado no fue revocada de inmediato al momento de la desvinculación. MediSync ha corregido esto incorporando un protocolo de **revocación de accesos en el mismo día del despido**, integrado al proceso de recursos humanos, lo que refuerza — y no contradice — que la arquitectura de seguridad de la plataforma (2FA + logs + backups) ya cumplía el estándar exigible; el vector de explotación fue una credencial no revocada a tiempo, responsabilidad que la Ley 9048 dirige hacia quien accede sin autorización, no hacia el diseño del sistema.

### Conclusión

MediSync CR cumple el nivel Alto del Reglamento a la Ley 8968 mediante cifrado, 2FA, logs y backups; protege su algoritmo bajo la Ley 7975 y su código bajo la Ley 6683; obtiene consentimiento informado, expreso y por escrito con finalidad específica para el intercambio de datos con aseguradoras; y disponía de controles técnicos razonables frente al acceso no autorizado tipificado en la Ley 9048, cuya falla fue procedimental y ya fue subsanada. Se solicita al panel del MICITT desestimar los cargos de incumplimiento estructural contra MediSync CR.

### Anexo de prompts de IA

*(completar antes de entregar: herramienta utilizada, prompts íntegros enviados y ajustes hechos a esos prompts — obligatorio según [[Cursos/Seguridad/apuntes/reglas-clase|reglas de clase]]. No cuenta dentro de las 5 páginas.)*

## Checklist contra la rúbrica

- [x] Citar la ley aplicable a cada dato que recolecta MediSync CR
- [x] Demostrar cumplimiento del nivel ALTO del Reglamento a la Ley 8968
- [x] Argumentar protección del algoritmo bajo Ley 7975 y Ley 6683
- [x] Consentimiento informado y principio de finalidad
- [x] Prevención de delitos (Ley 9048) — caso del ex-empleado
- [x] Anexo de prompts de IA — incluido en el Word (fuera de las 5 páginas)
- [x] Pasar a Word y verificar máx. 5 páginas + portada — el documento final es `Tarea1SeguridadMarcosZamora.docx` (hecho por el estudiante, revisado y corregido 2026-08-26). Confirmado con Word: portada + cuerpo = **5 páginas exactas (en el límite, sin margen)**, Anexo de IA en página 6 aparte con salto de página explícito, sin contar contra el límite.
- [x] Corregido 2026-08-26: la cita "Art. 24 de la Ley 8968" para medidas de seguridad era incorrecta (Art. 24 de la Ley es "Denuncia" ante PRODHAB, verificado contra el texto oficial); el artículo correcto es el **Art. 10 ("Seguridad de los datos")**. Se reforzó además la Sección II citando el **Art. 24 de la Constitución Política** (el que realmente pide la guía de la profesora como "arma secreta") con las resoluciones de Sala IV N.° 5802-1999 y N.° 4847-1999.
- [ ] Confirmar si se entrega en pareja (ambos deben subir el documento o no se evalúa)
- [x] Nombre del estudiante ya está en la portada del Word final (Marcos Zamora Sánchez); `[Nombre del estudiante]` solo queda como placeholder en mi copia auxiliar `Seguridad_tarea-1-legislacion-devs.docx`, que ya es redundante.
