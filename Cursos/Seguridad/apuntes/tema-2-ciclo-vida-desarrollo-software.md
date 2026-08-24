---
curso: Seguridad
tema: "Tema 2 — Ciclo de Vida de Desarrollo de Software (SDLC): buenas prácticas de seguridad"
fecha: 2026-08-24
tipo: apunte
fuente:
  - _fuentes/Seguridad_tema2-ciclo-vida-desarrollo-software_2026-08-24.pdf
tags: [tema2, sdlc, threat-modeling, owasp, nist, iso27034, cadena-suministro, casos-abuso, dread]
---

# Tema 2 — Ciclo de Vida de Desarrollo de Software (buenas prácticas de seguridad)

Ver también: [[Cursos/Seguridad/temario]] · [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/apuntes/tema-1-importancia-seguridad-software|Tema 1]] · [[Cursos/Seguridad/apuntes/stride-metodologia-amenazas|STRIDE — Modelo de Amenazas]]

Diapositivas de la profesora para el bloque 7 del programa oficial ("Ciclo de vida de Desarrollo de Software"). El material trae marcadores de sección "Clase 4 / Clase 5 / Clase 6" — se recibió todo de una vez, cubre varias clases futuras además de la de hoy (2026-08-24, presumiblemente Clase 4, ya que la última confirmada fue Clase 3 el 2026-08-19).

**Nota administrativa del deck (declaración de uso ético de IA):** se autoriza y fomenta usar IA generativa (Gemini/ChatGPT/Claude) para investigación/estructuración, PERO con 3 condiciones obligatorias: (1) responsabilidad del estudiante de verificar la veracidad técnica de lo que genera la IA (puede alucinar), (2) prohibido el copy-paste literal de respuestas de IA, (3) si se usó IA hay que incluir un **Anexo de Prompts** al final del entregable con la herramienta usada + copia íntegra de los prompts + los cambios hechos a esos prompts para llegar a una respuesta satisfactoria.

## El problema: la Ley del Costo Exponencial

Corregir un error de seguridad se encarece **exponencialmente** (no linealmente) cuanto más tarde se detecta en el ciclo de vida: diseño (costo bajo) → desarrollo (costo medio) → testing (costo alto) → producción (costo catastrófico).

## Tríada CIA aplicada a prácticas concretas del SDLC

- **Confidencialidad** → control de acceso, cifrado en tránsito/reposo, gestión de secretos
- **Integridad** → firmas, hashing, control de versiones, revisión de código automatizada
- **Disponibilidad** → diseño resiliente, tolerancia a fallos, planificación de capacidad
- **DevSecOps** → integrar seguridad en CI/CD para cumplir la tríada desde el ciclo de vida
- **Pruebas** → pentesting, análisis SAST/DAST, verificación de integridad
- **Monitoreo y respuesta** → detección de anomalías, recuperación rápida
- **Políticas y cumplimiento** → auditorías, gestión de parches, control de configuración

## Fase de Requerimientos y Diseño — Modelado de Amenazas (Threat Modeling)

Proceso estructurado para identificar qué puede salir mal, analizar cómo podría ser atacado el sistema, y definir controles desde el diseño. **No busca bugs de código, busca riesgos de diseño.** Se hace en la fase de diseño, antes de desarrollar, y cada vez que hay cambios grandes de arquitectura, datos o funcionalidad.

**7 pasos** (ejemplo usado en clase: app ficticia "FlashPresto", de pedidos y pagos):

1. **Definir el sistema** — objetivo, tipo de app (web/móvil/API), usuarios, datos que procesa
2. **Identificar activos críticos** — datos personales/sensibles, credenciales, reputación del negocio, disponibilidad del servicio. Pregunta clave: *"¿qué pasaría si este activo se pierde, se filtra o se altera?"*
3. **Dibujar el DFD** (Diagrama de Flujo de Datos) — usuarios, app, servidores, BD, servicios externos, y los flujos entre ellos, marcando **trust boundaries** (límites de confianza, ej. entre usuario y servidor, o entre la app y servicios externos). La mayoría de amenazas aparecen en los flujos de datos, no en los componentes aislados
4. **Identificar amenazas potenciales** — "¿qué podría salir mal aquí?": acceso no autorizado, robo de credenciales, manipulación de datos, exposición de datos personales, abuso de funcionalidades legítimas
5. **Evaluar impacto y probabilidad** (alto/medio/bajo cada uno) para poder priorizar — no todo se mitiga al mismo nivel
6. **Definir mitigaciones desde el diseño** — minimización de datos, cifrado, autenticación fuerte, control de accesos, registro y monitoreo, consentimiento explícito, separación de privilegios. **Las mitigaciones se diseñan, no se "parchan" después**
7. **Documentar y validar** — el resultado final es un documento con diagrama + lista de amenazas + riesgos priorizados + decisiones de diseño; sirve a desarrolladores, equipos legales y auditorías como evidencia de *Security & Privacy by Design*

Conexión con Costa Rica: el Threat Modeling apoya Privacidad desde el Diseño (Ley 8968) y reduce el riesgo de delitos informáticos (Ley 9048) — ver [[Cursos/Seguridad/apuntes/tema-1-importancia-seguridad-software|Tema 1]].

## Fase de Desarrollo/Codificación

(Diapositiva de título únicamente — sin contenido desarrollado más allá del encabezado en este deck.)

## Fase de Pruebas y Verificación

5 tipos de pruebas de seguridad (flujo sugerido: DAST → Pentesting → Fuzzing → Gestión de Vulnerabilidades → Code Reviews):

- **DAST** (Análisis de Código Dinámico) — probar la app en ejecución para encontrar fallos de flujo
- **Pentesting** — simulacros de ataques reales realizados por expertos en seguridad
- **Fuzzing** — enviar datos aleatorios/inválidos masivos para forzar errores en el sistema
- **Gestión de Vulnerabilidades** — priorizar qué corregir primero según impacto y probabilidad
- **Code Reviews con enfoque en seguridad** — no solo revisar lógica funcional, sino buscar "puertas traseras" o fallos de lógica

## Estándares de Desarrollo de Software Seguro

Tres "bibliotecas" de estándares y frameworks para que las empresas no tengan que adivinar cómo proteger su código.

### OWASP

Fundación sin fines de lucro, "el estándar global de seguridad en aplicaciones web". Pilares: **Comunidad** (miles de profesionales colaborando abiertamente), **Herramientas** (ej. OWASP ZAP, tecnologías open source sin barreras económicas), **Estándares** (documentos técnicos reconocidos globalmente).

**OWASP Top 10** = llamado el "Estándar de Oro": documento de consenso con los 10 riesgos de seguridad más críticos para aplicaciones web, reconocido mundialmente como punto de partida para implementar defensas robustas y adoptar codificación segura.

**Seguridad en la Cadena de Suministro de Software (SCA)** — identifica y reduce riesgos derivados de librerías, frameworks, dependencias de terceros, componentes open source. Idea clave: *tu aplicación es tan segura como la dependencia más débil que utilices*. Categoría OWASP dedicada: **A03:2025 Software Supply Chain Failures** — "hoy el software no se escribe completamente, se ensambla; cada componente ensamblado se vuelve parte de la superficie de ataque". Eslabones de la cadena: código propio → dependencias externas (librerías OSS, APIs, frameworks) → herramientas de desarrollo (repositorios, CI/CD, gestores de paquetes) → infraestructura (cloud, contenedores, servidores).

### NIST (National Institute of Standards and Technology)

Agencia federal de EE.UU. (Departamento de Comercio, fundada en 1901), **no reguladora** — sus estándares se adoptan voluntariamente por su calidad técnica. Sede en Gaithersburg, Maryland.

**NIST CSF 2.0** — "el estándar de oro para la gestión de riesgos cibernéticos". 6 funciones: **Gobernar** (estrategia y política de gestión de riesgos — nueva en 2.0), **Identificar** (comprender activos y riesgos), **Proteger** (implementar salvaguardas), **Detectar** (identificar ocurrencia de eventos), **Responder** (tomar medidas ante incidentes), **Recuperar** (restaurar capacidades/servicios afectados).

| | CSF 1.1 (2018) | CSF 2.0 (2024) |
|---|---|---|
| Alcance | Infraestructuras críticas | Todas las organizaciones (universal) |
| Funciones core | 5 (ID, PR, DE, RS, RC) | 6 (añade GOVERN/Gobernar) |
| Enfoque | Operativo/técnico | Estratégico/riesgo de negocio |
| Recursos | Guías estáticas | Herramientas de referencia online |

Publicaciones especiales (serie 800) relevantes: **SP 800-53** (controles de seguridad y privacidad para sistemas de información), **SP 800-171** (protección de info sensible no clasificada en contratistas), **SP 800-30** (guía para evaluaciones de riesgo — ver sección de ARA más abajo), **NICE Framework** (roles y competencias de la fuerza laboral de ciberseguridad). También existe **NIST C-SCRM** (Cybersecurity Supply Chain Risk Management, SP 1305) específico para riesgo de cadena de suministro.

### ISO/IEC

- **ISO/IEC 27001** — el pilar de la gestión de la seguridad de la información organizacional. Define el **SGSI** (Sistema de Gestión de la Seguridad de la Información): protege confidencialidad/integridad/disponibilidad de los datos en toda la empresa (procesos, personas, tecnología). Es certificable, se basa en mejora continua, ayuda con cumplimiento regulatorio, mitigación de riesgo de negocio y genera confianza con clientes.
- **ISO/IEC 27034** — seguridad robusta integrada directamente en el ciclo de vida del software (Application Security). No se limita a revisar el código final; mete la seguridad desde la fase de requerimientos/arquitectura. Concepto clave: **ASC** (Application Security Controls) — controles específicos para mitigar riesgos puntuales del software. Orientada a procesos: ayuda a demostrar de forma auditable que la aplicación mantiene un nivel de riesgo aceptable en todas sus versiones.

| Criterio | ISO 27001 (SGSI) | ISO 27034 (Seguridad en Aplicaciones) |
|---|---|---|
| Enfoque principal | Toda la organización (políticas, TI, RRHH, físico) | Específico para el SDLC |
| Objetivo de seguridad | Gobernanza global de los activos de información | Asegurar que el software resista ataques de forma nativa |
| Usuarios clave | CISO, auditores, directivos | Desarrolladores, arquitectos de software, DevOps, QA |
| Relación entre ambas | Define el marco macro y los objetivos de seguridad del negocio | Ejecuta y cumple esos objetivos técnicos dentro del código y la app |

### SANS Institute

Líder mundial en formación y certificación de ciberseguridad. Pilares: **Formación** (cursos inmersivos de 5-6 días en defensa, ataque, forense y gestión), **GIAC** (certificaciones que validan habilidades prácticas, no solo conocimiento teórico), **Investigación** (proyectos de código abierto, carteles de referencia, el famoso **Internet Storm Center**). Recursos para la comunidad: ISC (monitorización global de amenazas en tiempo real), Reading Room (+3,000 artículos técnicos gratuitos), SANS Posters (hojas de referencia visuales de comandos Linux/Windows), NewsBites (boletín semanal con noticias críticas de seguridad).

## Análisis de Riesgo Orientado a la Arquitectura (ARA / Architectural Risk Analysis)

No es un checklist de vulnerabilidades de código — es una evaluación **estructural**. Analogía usada en clase: un **bug de código** es como un ladrillo quebrado o una ventana mal sellada (problema local, fácil de cambiar). Un **riesgo de arquitectura** es haber diseñado las columnas demasiado delgadas para el peso del techo, o poner la bóveda del banco junto a la ventana de la calle — por más buenos que sean los ladrillos, el edificio colapsa porque el diseño estructural está mal.

**Framework de referencia:** NIST SP 800-30 (metodología para identificar amenazas, vulnerabilidades, impacto y probabilidad) + NIST SSDF/SP 800-218 (Secure Software Development Framework — en su pilar "Diseñar Software Seguro" exige explícitamente evaluar la arquitectura y hacer modelado de amenazas *antes* de escribir la primera línea de código).

**Proceso práctico en 4 pasos:**

- **A — Descomposición del sistema** ("ver el plano"): diagramas técnicos de componentes (servicios, bases de datos, APIs de terceros, microservicios), flujos de datos, y **límites de confianza** (dónde cambia el nivel de privilegio, ej. entre el navegador del usuario de internet y la red interna)
- **B — Identificación de amenazas** ("¿qué podría salir mal?"): aplicar **STRIDE** sobre el diagrama diseñado — ver [[Cursos/Seguridad/apuntes/stride-metodologia-amenazas|nota STRIDE]] para el detalle completo
- **C — Determinación del riesgo:** Riesgo = Probabilidad × Impacto
  - **Probabilidad (Likelihood)** — cruzar la frecuencia/viabilidad del ataque con la robustez de los controles existentes
  - **Impacto** — gravedad de las consecuencias sobre el negocio, evaluada considerando pérdida de Confidencialidad, Integridad y Disponibilidad (CIA)
  - Ambos índices se multiplican para obtener la puntuación final de riesgo
- **D — Mitigación e ingeniería de requerimientos de seguridad:** el ARA no es solo para documentar problemas, es para resolverlos — el resultado final es la generación de **requerimientos de seguridad concretos para los desarrolladores**. Ejemplo dado en clase: si el riesgo arquitectónico es *"fuga de credenciales porque el microservicio A se autentica con el microservicio B en texto plano"*, el requisito de diseño resultante es *"implementar mTLS (Mutual TLS) obligatorio para toda la comunicación este-oeste dentro del clúster"*

Cierre de la sección: el ARA consiste en *"evaluar el plano de la casa antes de comprar los materiales"* — permite identificar fallas estructurales destructivas cuando aún son baratas y fáciles de corregir en el papel, garantizando software resiliente por diseño.

## Casos de Abuso y Requerimientos de Seguridad en Software

- **Caso de uso** (funcional) → "¿qué debe hacer el software?" — describe interacciones positivas entre el usuario y el sistema para alcanzar una meta de negocio
- **Caso de abuso** (seguridad) → "¿qué NO debe permitir el software?" — describe interacciones maliciosas donde un actor intenta causar daño real al sistema o a sus datos

**El "Misuser"** — el actor antagonista, con metas que entran en conflicto con la seguridad del sistema. Motivación: ganancia financiera, espionaje o sabotaje. Capacidad: desde usuarios curiosos hasta atacantes organizados. Recursos: herramientas automatizadas y técnicas de ingeniería social.

**Anatomía de un caso de abuso:**

1. **Meta del abuso** — el objetivo final del atacante (ej. exfiltrar datos de tarjetas de crédito)
2. **Amenaza** — el método o vector utilizado (ej. inyección SQL en el formulario de login)
3. **Impacto** — la consecuencia negativa para la organización (ej. multa regulatoria y daño de marca)

**De la amenaza al requerimiento** (tabla de ejemplo trabajada en clase):

| Atributo (CIA) | Caso de abuso | Requerimiento de seguridad |
|---|---|---|
| Confidencialidad | Sniffing de credenciales | Cifrado TLS 1.3 en todas las conexiones |
| Integridad | Tampering de precios | Validación de firmas en el lado del servidor |
| Disponibilidad | Ataque DoS por recursos | Implementación de Rate Limiting y cuotas |
| Trazabilidad | Borrado de logs | Inmutabilidad de bitácoras de auditoría |

**Seguridad por Diseño** — integrar requerimientos de seguridad en la arquitectura previene fallos estructurales que son imposibles de corregir solo con código, a través de: **Defensa en Profundidad**, **Principio de Mínimo Privilegio**, **Reducción de Superficie de Ataque**.
