---
curso: Seguridad
tema: "Tarea 3 — NIST CSF aplicado a VoteOnline (Grupo 11)"
fecha: 2026-09-07
tipo: entregable
entregable_de: "[[Cursos/Seguridad/apuntes/tarea-3-nist-csf-instrucciones]]"
estado: borrador
tags: [tarea3, nist-csf, voteonline, grupo11]
---

# Tarea 3 — NIST CSF aplicado a VoteOnline (Grupo 11)

Ver también: [[Cursos/Seguridad/apuntes/tema-2-ciclo-vida-desarrollo-software|Tema 2 — las 6 funciones del NIST CSF]] · [[Cursos/Seguridad/entregables/tarea-2-threat-modeling|Tarea 2 — Threat Modeling de VoteOnline]] · [[Cursos/Seguridad/apuntes/stride-metodologia-amenazas|STRIDE]]

**Valor: 5%** · Trabajo en clase, 30 min + exposición de 5 min. **Misma empresa que Tarea 2: VoteOnline** (sistema de votación remota para colegios profesionales).

**La idea no es llenar espacios de memoria — es tomar lo que ya identificamos en el Threat Modeling (Tarea 2) y organizarlo bajo las 5 funciones del NIST CSF.** Cada respuesta de acá abajo trae su "por qué" para poder explicarlo en la exposición sin leer textual.

## 1. IDENTIFY — Identificación de activos y riesgos

**1.1 Cuatro activos críticos:**

1. **Token del votante** — es la credencial que autoriza un voto; si se compromete, se puede suplantar a cualquier colegiado.
2. **ID del votante vinculado al voto** (misma tabla) — de esto depende el secreto del voto.
3. **Base de datos electoral** — contiene el resultado completo de la elección.
4. **Panel de administración / cookie de sesión** — es la puerta de acceso con más privilegio a todo lo anterior.

**1.2 Datos de clientes (colegiados) que deben protegerse:**

- Número de cédula (semilla del token).
- Correo electrónico (canal de entrega del token).
- El voto emitido y su vínculo con el votante (dato más sensible del sistema: revela cómo votó una persona específica).

**1.3 Cuatro riesgos de seguridad y por qué lo son:**

1. **Predicción de tokens** (SHA-1 sin sal sobre la cédula) — es riesgo porque la cédula es semi-pública en Costa Rica; un atacante externo puede calcular el token de otro colegiado sin necesitar acceso privilegiado ni interceptar nada.
2. **Cookie de sesión del panel sin `HttpOnly`** — es riesgo porque es robable vía XSS, y esa sola cookie da acceso de auditoría a toda la base de datos electoral.
3. **Un administrador legítimo puede ver qué votó una persona específica** (voto e ID en la misma tabla) — es riesgo aunque no haya "atacante": rompe el secreto del voto desde adentro, con acceso completamente autorizado.
4. **El canal de correo (proveedor externo)** puede ser interceptado — es riesgo porque el token viaja sin garantía de confidencialidad hacia un tercero fuera del control del colegio.

## 2. PROTECT — Controles de protección

**2.1 Cuatro controles de acceso y por qué deben implementarse:**

1. **MFA en el panel de administración** — porque hoy basta con robar una cookie para auditar toda la elección; un segundo factor rompe ese ataque de un solo paso.
2. **Mínimo privilegio por rol** (ej. "ver participación" separado de "ver resultado por persona") — porque hoy cualquier admin con acceso al panel puede ver el voto individual de alguien, y no todos necesitan ese nivel.
3. **Autenticación del votante más allá del token derivado de cédula** (ej. pedir un segundo dato al usar el token) — porque ataca directamente el riesgo de predicción de tokens.
4. **Separación de tablas** (quién votó vs. qué se votó, vinculadas solo por un token efímero) — es control de acceso a nivel de dato, no solo de sistema: ni un admin con acceso total a una tabla puede reconstruir el secreto del voto.

**2.2 Cómo proteger los datos de clientes / cambios de diseño de la aplicación:**

- Cifrado en tránsito (TLS) en todo el tráfico votante↔servidor↔correo, para que interceptar el canal no alcance para leer el token.
- Cifrado en reposo de la tabla electoral.
- Rediseño ya identificado en Tarea 2: separar "ID de quién votó" de "qué opción se eligió" en dos tablas, unidas solo por un token efímero que se destruye al cerrar la elección.
- Reemplazar SHA-1 sin sal por HMAC-SHA256 con clave secreta del servidor + salt único por token.

**2.3 Cuatro medidas de capacitación para empleados:**

1. Capacitar al comité electoral en manejo de datos sensibles y en no consultar resultados individuales sin que quede registrado el motivo.
2. Capacitación en phishing dirigida a votantes, para que reconozcan un correo falso de "token de votación".
3. Capacitación técnica al equipo de desarrollo sobre por qué SHA-1 sin sal es inseguro y sobre flags de cookie seguras (`HttpOnly`, `Secure`, `SameSite`).
4. Simulacros internos de respuesta a incidentes para el equipo técnico del colegio, antes de que ocurra uno real.

## 3. DETECT — Detección de incidentes

**3.1 Cuatro eventos de seguridad a monitorear y por qué:**

1. **Intentos repetidos de voto con tokens secuenciales o muy similares** — señal directa de que alguien está prediciendo tokens a partir de cédulas.
2. **Accesos al panel de administración fuera de la ventana de elección o desde ubicaciones inusuales** — el panel solo debería usarse durante la votación/auditoría, no fuera de ese contexto.
3. **Consultas inusualmente frecuentes a la tabla de votos por un mismo admin** — podría ser un insider revisando votos individuales uno por uno.
4. **Picos de errores o reenvíos en el servicio de correo** — podría indicar interceptación o intento de reenvío masivo de tokens por un atacante.

**3.2 Cuatro herramientas o mecanismos y por qué se elige cada uno:**

1. **Logging centralizado con alertas (SIEM básico)** — correlaciona eventos del panel, la BD y el correo en un solo lugar, en vez de revisar tres bitácoras sueltas.
2. **Rate limiting / detección de anomalías en el endpoint de votación** — el ataque de predicción de tokens necesita probar muchos valores rápido; limitar la tasa lo hace visible.
3. **Monitoreo de integridad de la base de datos electoral (file/DB integrity monitoring)** — detecta si un resultado fue modificado fuera del flujo normal de votación.
4. **Auditoría de sesiones del panel** (detectar la misma cookie usada desde dos ubicaciones a la vez) — revela directamente un robo de cookie de sesión.

## 4. RESPOND — Respuesta a incidentes

**Escenario:** un atacante obtuvo acceso a la cuenta de un empleado (del comité electoral, con acceso al panel).

**4.1 Cuatro acciones inmediatas y por qué:**

1. **Revocar la sesión comprometida y forzar cambio de credenciales** — corta el acceso activo del atacante de inmediato, antes de investigar nada más.
2. **Poner el panel de administración en modo solo lectura temporalmente** — evita que el atacante altere resultados mientras dura la investigación.
3. **Revisar los logs de esa cuenta** (qué consultó, qué modificó) — permite saber si solo hubo lectura (grave para el secreto del voto) o también alteración de resultados (grave para la integridad de la elección).
4. **Notificar al equipo técnico/seguridad y activar el plan de respuesta** — convierte el hallazgo de una persona en una gestión formal del incidente, no una reacción improvisada.

**4.2 Cómo comunicar el incidente internamente (quién hace qué):**

- Quien detecta la anomalía (un miembro del comité o un votante que reporta algo raro) avisa de inmediato al responsable técnico — no intenta resolverlo por su cuenta.
- El equipo técnico/TI confirma si es un incidente real y, de serlo, escala a la dirección del colegio profesional (por el impacto directo en una elección institucional).
- La dirección decide si corresponde notificar a los colegiados o a algún ente regulador (transparencia del proceso electoral) — esa comunicación externa es una decisión aparte de la interna.
- Se designa un solo vocero para consolidar la comunicación mientras dura la investigación, para evitar versiones contradictorias.

## 5. RECOVER — Recuperación

**5.1 Cuatro acciones para restaurar los sistemas y por qué:**

1. **Restaurar la cuenta comprometida con credenciales nuevas y MFA obligatorio antes de reactivarla** — evita que el mismo atacante reingrese apenas se reabra el acceso.
2. **Verificar la integridad de los votos ya emitidos contra un respaldo previo al incidente** — confirma si los resultados fueron alterados o no antes de dar la elección por válida.
3. **Reemitir tokens a los votantes afectados**, si se determina que hubo exposición — preserva la validez de sus votos sin invalidar toda la elección.
4. **Restaurar desde el último backup íntegro conocido**, solo si se confirma manipulación de datos — se vuelve a un estado verificado en vez de confiar en el estado actual del sistema.

**5.2 Cuatro mejoras de proceso después del incidente y por qué:**

1. **MFA obligatorio en todas las cuentas del panel** (no solo tras el incidente) — cierra permanentemente la puerta que se usó esta vez.
2. **Adoptar el rediseño de tokens (HMAC + salt) y la separación de tablas** ya identificado en el Threat Modeling de Tarea 2 — convierte una lección aprendida en un cambio de diseño real, no solo un parche puntual.
3. **Revisiones periódicas de logs de auditoría**, no solo reactivas ante incidentes — pasa de "nos dimos cuenta de casualidad" a "lo detectamos por proceso".
4. **Post-mortem sin culpa (blameless)** que actualice el plan de respuesta con lo aprendido — mejora continua real del proceso, no solo cerrar el caso puntual.

## Cómo se conecta con lo que ya vimos

Esto no es un ejercicio aislado: es el mismo caso VoteOnline de Tarea 2, reorganizado bajo las 5 funciones del NIST CSF (Identify/Protect/Detect/Respond/Recover — ver [[Cursos/Seguridad/apuntes/tema-2-ciclo-vida-desarrollo-software|Tema 2]] para las 6, incluyendo Govern). El Threat Modeling identificó **qué** podía salir mal y cómo mitigarlo desde el diseño; el NIST CSF organiza esas mismas ideas en un ciclo continuo — de hecho, casi todas las mitigaciones de diseño de Tarea 2 (separar tablas, MFA, tokens HMAC+salt, cookies seguras) reaparecen acá bajo PROTECT, porque son la misma solución vista desde dos frameworks distintos.

## Checklist contra la rúbrica

- [x] IDENTIFY — activos, datos de clientes y riesgos identificados con justificación
- [x] PROTECT — controles de acceso, protección de datos y capacitación
- [x] DETECT — eventos a monitorear y herramientas, con el porqué de cada elección
- [x] RESPOND — acciones inmediatas y plan de comunicación interna para el escenario dado
- [x] RECOVER — acciones de restauración y mejoras de proceso
- [ ] Repasar en voz alta antes de exponer — 5 minutos es poco, priorizar el "por qué" de 2-3 puntos por función en vez de leer todo
