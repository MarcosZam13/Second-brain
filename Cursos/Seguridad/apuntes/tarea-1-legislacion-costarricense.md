---
curso: Seguridad
tema: Tarea 1 — Legislación Costarricense ("El Contrato Roto")
fecha: 2026-08-18
tipo: apunte
fuente:
  - _fuentes/Seguridad_tarea1-legislacion-costarricense_2026-08-18.pdf
tags: [legislacion, ley8968, ley9048, ley6683, ley7975, prodhab, micitt, tarea]
---

# Tarea 1 — Legislación Costarricense: "El Contrato Roto"

Ver también: [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/temario]]

**Subtítulo:** Cuando el software toca la ley costarricense
**Valor:** 5% del rubro de Tareas
**Entrega:** 2026-09-01, antes de las 11:50pm (23:50) — corrige la hora 23:45 anotada inicialmente desde la plataforma
**Modalidad:** puede trabajarse en parejas, pero **ambos** deben subir el documento o no se evalúa

## Objetivo de aprendizaje

Identificar y aplicar las leyes costarricenses que regulan el desarrollo de software, analizar un sistema real frente a esos marcos legales y argumentar decisiones técnicas con fundamentación jurídica.

## ⚠️ Decisión pendiente: elegir rol

Hay que elegir **uno** de 3 roles antes de poder redactar el entregable — todavía no confirmado cuál le toca al usuario (o a la pareja):

1. **The Devs — La Defensa**: demostrar que MediSync CR cumple TODOS los marcos legales aplicables.
2. **The PRODHAB — La Fiscalía**: actuar como inspectores, demostrar infracciones específicas citando artículos concretos.
3. **El MICITT — Los Jueces Técnicos**: panel técnico-legal, evaluar si MediSync toca infraestructura crítica, hacer preguntas a ambos grupos y sentenciar.

## Caso: MediSync CR

Plataforma web/móvil de gestión médica y citas (pacientes, médicos, clínicas privadas de CR).

| Campo | Detalle |
|---|---|
| Datos recolectados | Nombre, cédula, fecha de nacimiento, historial clínico, diagnósticos, medicamentos, imágenes médicas, ubicación, datos de pago |
| Nivel de seguridad requerido | **ALTO** (datos sensibles de salud, según Reglamento a la Ley 8968) |
| Tecnologías declaradas | Cifrado AES-256, autenticación 2FA, logs de acceso, backups diarios |
| Propiedad intelectual | Algoritmo propietario de diagnóstico asistido por IA |
| Integraciones | CCSS (datos de citas), pasarelas de pago, correo electrónico |

**Contexto del caso (la denuncia):** PRODHAB recibió una denuncia anónima: (1) MediSync comparte historiales clínicos con aseguradoras sin consentimiento explícito, (2) su algoritmo de IA (sin registro) fue replicado por un competidor, (3) un ex-empleado accedió remotamente a la base de datos tras su despido. El MICITT investiga si la integración con la CCSS califica como infraestructura crítica.

## Guía de referencia legal rápida

- **Ley N.° 8968 — Protección de Datos Personales:** los datos son del ciudadano, no de quien los recolecta. Consentimiento informado expreso, por escrito, previo. **Artículo 24** obliga a medidas técnicas/organizativas de seguridad. Reglamento define 3 niveles: Básico / Medio / **Alto** (datos sensibles: salud, religión, orientación sexual, etc.).
- **PRODHAB:** ente estatal que vigila la Ley 8968, sanciona, puede imponer multas y ordenar cierre temporal de bases de datos; audita de oficio o por denuncia.
- **Ley N.° 9048 — Reforma de Delitos Informáticos:** tipifica el acceso no autorizado a sistemas; aplica a ex-empleados que conservan credenciales o acceden tras el despido; el software que facilite o no prevenga esos accesos puede implicar responsabilidad del desarrollador.
- **Ley N.° 6683 — Derechos de Autor y Derechos Conexos:** protege código fuente/objeto como obra intelectual desde su creación; se recomienda registro en el Registro Nacional.
- **Ley N.° 7975 — Información No Divulgada (Know-How):** protege algoritmos propietarios/secretos comerciales cuando tienen valor comercial, se mantienen en secreto y se toman medidas razonables de protección.
- **Estrategia Nacional de Ciberseguridad (MICITT):** lineamientos para infraestructura crítica; un sistema que interactúa con servicios estatales (ej. CCSS) puede calificar como infraestructura crítica y quedar sujeto a controles adicionales.

## Entregable por rol

Documento Word, **máximo 5 páginas incluyendo portada** (el anexo de prompts de IA, si aplica, va aparte y no cuenta en esas 5 páginas):

- **Devs:** citar la ley aplicable a cada dato recolectado; demostrar cumplimiento del nivel ALTO del Reglamento 8968; argumentar protección del algoritmo bajo Ley 7975 y Ley 6683.
- **PRODHAB:** al menos 3 cargos formales de acusación, cada uno citando artículo específico; cálculo de sanción económica/administrativa posible.
- **MICITT:** 5 preguntas técnicas para los Devs y 5 para la Fiscalía con su respuesta según criterio propio; análisis preliminar de si MediSync califica como infraestructura crítica (investigar antes qué es infraestructura crítica).

## Rúbrica (20 pts por rol, 5 criterios de 4 pts c/u)

Todos los roles comparten un criterio de **"Uso ético de la IA"** (4 pts) — evalúa que el uso de la IA declarado coincida con lo entregado y que haya argumentos propios, no solo transcripción.

**Rol 1 — Devs (Defensa Legal):** aplicación del Reglamento Ley 8968 (niveles de seguridad) · protección de propiedad intelectual (Ley 6683/7975) · consentimiento informado y principio de finalidad · prevención de delitos (Ley 9048, caso ex-empleado) · uso ético de la IA.

**Rol 2 — PRODHAB (Fiscalía Legal):** identificación de infracciones a la Ley 8968 · aplicación de la Ley 9048 al caso del ex-empleado · argumento sobre propiedad intelectual (Ley 6683/7975) · propuesta de sanción fundamentada · uso ético de la IA.

**Rol 3 — MICITT (Panel de Jueces):** comprensión de la Ley 8968 y su Reglamento · evaluación de riesgos bajo Ley 9048 y Estrategia MICITT · fundamentación de la sentencia (veredicto + sanción + recomendaciones técnicas) · imparcialidad/ética/objetividad · uso ético de la IA.

(Detalle completo de los 4 niveles de desempeño por criterio en el PDF fuente archivado — no se transcribe aquí para no duplicar toda la tabla; consultar `_fuentes/Seguridad_tarea1-legislacion-costarricense_2026-08-18.pdf` si se necesita el desglose exacto al redactar.)

## Declaración de ética de IA (igual a [[Cursos/Seguridad/apuntes/reglas-clase|reglas de clase]])

Uso autorizado y fomentado; prohibido el copy-paste literal; anexo de prompts obligatorio si se usó IA (herramienta + prompts íntegros + cambios hechos a esos prompts).
