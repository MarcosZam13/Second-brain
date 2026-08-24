---
curso: Seguridad
tema: "Proyecto Final — Instrucciones, Rúbrica y Plantillas de Ejemplo"
fecha: 2026-08-24
tipo: apunte
fuente:
  - _fuentes/Seguridad_proyecto-final-instrucciones_2026-08-24.pdf
  - _fuentes/Seguridad_proyecto-final-rubrica_2026-08-24.xlsx
  - _fuentes/Seguridad_proyecto-final-matriz-gobernanza-ejemplo_2026-08-24.xlsx
  - _fuentes/Seguridad_proyecto-final-matriz-riesgo-residual-ejemplo_2026-08-24.xlsx
  - _fuentes/Seguridad_proyecto-final-ejemplo-poc-audit-poisoning_2026-08-24.docx
  - _fuentes/Seguridad_proyecto-final-plantilla-reporte-parches_2026-08-24.docx
tags: [proyecto-final, owasp, nist-csf, threat-modeling, pentesting, hardening, rubrica]
---

# Proyecto Final IC-8071 — Instrucciones, Rúbrica y Plantillas de Ejemplo

Ver también: [[Cursos/Seguridad/temario]] · [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/apuntes/reglas-clase|Reglas de clase]] · [[Cursos/Seguridad/apuntes/tema-2-ciclo-vida-desarrollo-software|Tema 2 — SDLC]] · [[Cursos/Seguridad/apuntes/stride-metodologia-amenazas|STRIDE]]

**Valor: 20% (grupal)** · **Fecha de entrega: 9 de noviembre 2026, 8:00pm**

> Aclaración del usuario (2026-08-24): aunque el PDF oficial describe la estructura en 3 fases, cada una con su propio entregable, según lo comunicado en clase **no hay entregas parciales por fase** — es una única entrega en noviembre con todos los documentos y el video juntos. La estructura de fases de abajo sirve como guía de contenido/orden de trabajo, no como calendario de entregas intermedias.

## Objetivos de aprendizaje

1. Evaluar, explotar y remediar de forma integral las vulnerabilidades de seguridad en una arquitectura cliente-servidor, combinando el OWASP Top 10, los controles de NIST CSF 2.0 y técnicas avanzadas de manipulación de entradas.
2. Diagnosticar el estado de seguridad de la app mapeando vulnerabilidades críticas contra los controles de gobernanza y gestión de riesgos de NIST CSF 2.0, estableciendo una línea base de impacto técnico y de negocio.
3. Demostrar la viabilidad de los vectores de ataque mediante PoCs reproducibles en cliente y servidor: escalación de privilegios, inyecciones (OWASP A03), XSS y alteración de registros de auditoría (Audit Poisoning).
4. Implementar las correcciones a nivel de código fuente (codificación segura, sanitización de entradas, control de accesos, mecanismos defensivos) sin alterar la operación del sistema.

## Instrucciones generales

- Cada equipo selecciona una **aplicación web intencionalmente vulnerable** de arquitectura cliente-servidor (ej. Python/Flask o Node.js con cliente web interactivo) — propia o de repositorios públicos.
- El sistema se divide en **4 módulos** (Autenticación, Gestión de Usuarios, Operaciones/Transacciones, Logs/Auditoría) — **3 módulos si el equipo es de 3 personas**.
- **Cada integrante asume la responsabilidad individual de un módulo completo**, pero el trabajo se consolida en una única entrega grupal (no se aceptan documentos separados por persona).

## Fase 1 — Diagnóstico y Marco Normalizado (NIST CSF 2.0)

Por módulo, cada integrante ejecuta individualmente:

- **Mapeo del módulo contra NIST CSF 2.0** — componentes, endpoints y lógica de negocio frente a las subcategorías del marco.
- **Inventario de activos e impacto de riesgo** (funciones GOVERN e IDENTIFY) — activos críticos (datos, servicios, BD) e impacto operacional/de negocio ante un incidente.
- **Línea base de controles** (funciones PROTECT, DETECT) — controles mínimos requeridos antes de la fase de explotación.
- **Consolidación grupal** en una Matriz General de Gobernanza del Sistema, coherente entre los módulos.

**Entregable:** 1 documento de Matriz General de Gobernanza del Sistema.

## Fase 2 — Evaluación Ofensiva y Explotación (OWASP)

Cada integrante documenta una PoC de su módulo cubriendo 3 vectores obligatorios:

1. **Explotación de Software de Servidores** — Inyección SQL/Command Injection (OWASP A03) + escalación de privilegios explotando Broken Access Control (OWASP A01) y desconfianza en tokens JWT o llamadas entre microservicios.
2. **Explotación de Software en Clientes** — XSS Stored/Reflected (OWASP A03) para robo de cookies/sesión, manipulación del DOM y ejecución de código no autorizado en el navegador.
3. **Alteración de Entrada de Usuario y Detección** — CSRF o manipulación de parámetros HTTP (OWASP A08) + Audit Poisoning (manipulación de entradas para alterar/evadir logs de auditoría, invalidando la detección de intrusos).

**Entregable:** 1 documento de PoCs estandarizado (todas las PoCs de todos los miembros, cada una cubriendo los 3 puntos completos para su módulo).

## Fase 3 — Remediación, Hardening y Respuesta (NIST Protect & Detect)

Cada integrante implementa y firma la autoría de las correcciones de su propio módulo, con trazabilidad individual en el repositorio.

- **Protección (Protect):** codificación segura — parametrización de consultas, sanitización estricta de entradas, Content Security Policy (CSP), cookies seguras (HttpOnly/SameSite), principio de menor privilegio en los endpoints asignados.
- **Detección e Integridad (Detect):** corrección de la lógica de auditoría — prevención de Audit Poisoning vía desinfección de encabezados/parámetros e implementación de firmas o tracing defensivo.

**Escala de Riesgo Residual** (a justificar técnicamente por cada módulo):

| Nivel | Criterio |
|---|---|
| **Alto/Crítico** (no aceptable) | El parche soluciona el síntoma pero no la causa raíz, o las validaciones se pueden saltar con codificación alternativa — requiere re-trabajo inmediato |
| **Medio** (tolerable) | La vulnerabilidad principal fue eliminada, pero persisten configuraciones laxas (ej. falta de rate limiting) |
| **Bajo** (aceptado) | El vector de ataque fue completamente neutralizado, la PoC original ya no es ejecutable, y el control cumple con la subcategoría NIST CSF correspondiente |

**Entregables de la Fase 3:**

1. **Matriz de Riesgos NIST CSF Consolidada y actualizada** — riesgo residual post-remediación por módulo.
2. **Reporte Técnico de Parches** — evidencia de PRs/commits individuales, estructurado en 4 secciones:
   1. Ficha del integrante y trazabilidad de Git (responsable, módulo, enlace al PR, ID de commits, rama)
   2. Mapeo de la vulnerabilidad y parche (OWASP Top 10 + NIST CSF 2.0 + archivos/líneas afectadas)
   3. Comparativa de código — bloque Diff (antes vs. después)
   4. Verificación de no-reincidencia (prueba de regresión sobre la PoC corregida, con evidencia)
3. **Demostración funcional individual en video** — máximo 5 minutos por integrante (pueden subirse por separado), grabado 100% sobre el IDE y el repositorio, explicando línea por línea los parches de su módulo.
   - ⚠️ **Regla de evaluación estricta:** cualquier video con diapositivas, lectura de documentos o explicación teórica se descarta de inmediato con **nota cero (0)** en ese rubro — debe ser 100% técnico sobre las líneas modificadas.

## Consideraciones especiales

1. La profesora entrega plantillas de ejemplo (ver abajo), pero son libres de crear sus propios documentos.
2. Si un integrante no realiza su parte, no se penaliza al grupo — pero en el momento en que la incorpore, sí afecta la nota de todos si la solución integral no es de calidad.
3. El proyecto se entrega como **un solo documento consolidado**, no documentos separados por persona.

## Rúbrica de evaluación (100 pts)

| Criterio | Pts | Sobresaliente (100%) | Insuficiente (<50%) |
|---|---|---|---|
| Fase 1 — Matriz General de Gobernanza | 20 | Mapea los 4 módulos contra NIST CSF 2.0 con activos, impacto (GOVERN/IDENTIFY) y línea base de controles (PROTECT/DETECT) completos y coherentes | No entrega la matriz o no cumple con las funciones NIST CSF 2.0 |
| Fase 2 — Documento de PoCs estandarizado | 30 | 3 PoCs completas por integrante (Servidor, Cliente, Alteración de Entrada), reproducibles paso a paso, con payloads/código/tracing/evidencia | No entrega, o las PoCs no son funcionales ni demuestran los hallazgos |
| Fase 3 — Matriz de Riesgos consolidada y actualizada | 10 | Riesgo residual preciso y justificado técnicamente por módulo | No entrega o no aplica la escala solicitada |
| Fase 3 — Reporte Técnico de Parches | 20 | Ficha individual con trazabilidad Git, mapeo OWASP/NIST, Diff, y evidencia de regresión — todos los integrantes | No individual, sin trazabilidad en el repo |
| Fase 3 — Video de demostración individual (máx. 5 min) | 20 | 100% IDE/repositorio, explicación línea por línea de la solución técnica | Usa diapositivas/lectura/teoría → **nota 0** en el rubro, o no entrega |

(Escalas intermedias "Aceptable 70-89%" y "Necesita Mejora 50-69%" existen en la rúbrica original, archivada en `_fuentes/` — omitidas acá por espacio, consultar el Excel si hace falta el detalle exacto para autoevaluarse.)

## Plantillas de ejemplo entregadas por la profesora

Todas archivadas en `_fuentes/` — sirven de referencia de formato, no son de uso obligatorio (punto 1 de "Consideraciones especiales").

### Ejemplo de PoC — Audit Poisoning (docx)

Ejemplo completo trabajado sobre el módulo de Auditoría/Logs, estructura: Resumen de la vulnerabilidad (tabla: nombre, categoría OWASP A03:2021/A09:2021, nivel de riesgo ALTO) → Vector de ataque e impacto → Paso a paso de explotación (identificación del punto de entrada en código, intercepción HTTP con proxy, inyección de payload CRLF vía header `X-Forwarded-For`, verificación del envenenamiento en `audit.log`) → Propuesta de remediación (sanitización de saltos de línea + logging estructurado con la librería `logging` de Python en vez de escritura directa a archivo).

### Plantilla — Reporte Técnico de Parches de Código (docx)

Formato en blanco para completar por integrante, con las 4 secciones de la rúbrica: Ficha del Integrante y Trazabilidad de Git (tabla: estudiante, módulo asignado, enlace a PR, ID de commit, rama) → Mapeo de Vulnerabilidad y Parche (tabla: vulnerabilidad corregida, categoría OWASP, subcategoría NIST CSF, archivos/líneas modificados) → Comparativa de Código en formato Diff → Verificación de No-Reincidencia (comportamiento anterior vs. actual + espacio para evidencia).

### Matriz General de Gobernanza del Sistema — ejemplo (xlsx)

Columnas: Módulo y Responsable | Activo Crítico | Función NIST CSF | Categoría/Subcategoría NIST CSF | Control de Seguridad Requerido (línea base) | Nivel de Riesgo Inherente. Ejemplo con los 4 módulos estándar (Autenticación, Gestión de Usuarios, Operaciones, Auditoría y Logs), cada uno con su función NIST (PROTECT/GOVERN/DETECT), subcategoría concreta (ej. `PR.AA-01`, `PR.DS-01`, `DE.CM-01`) y control mínimo esperado.

### Matriz actualizada de Riesgo Residual — ejemplo (xlsx)

Columnas: Módulo y Responsable | Vulnerabilidad Identificada | Subcategoría NIST CSF | Control/Parche Aplicado (Fase 3) | Riesgo Inherente (Inicial) | Riesgo Residual (Post-Parche) | Estado Final. Ejemplo con los 4 módulos, cada uno pasando de riesgo Alto/Crítico a Bajo tras aplicar el parche correspondiente (ej. firma HMAC-SHA256 en JWT, sanitización con DOMPurify + CSP, Prepared Statements/ORM, purga de `\r\n` en headers de logging).
