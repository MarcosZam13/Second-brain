---
curso: Seguridad
tema: "Tarea 2 — Threat Modeling Grupal (trabajo en clase)"
fecha: 2026-08-24
tipo: apunte
fuente:
  - _fuentes/Seguridad_tarea2-threat-modeling-instrucciones_2026-08-24.pdf
tags: [tarea2, threat-modeling, dfd, stride, rubrica]
---

# Tarea 2 — Threat Modeling Grupal (trabajo en clase, 5%)

Ver también: [[Cursos/Seguridad/temario]] · [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/apuntes/tema-2-ciclo-vida-desarrollo-software|Tema 2 — proceso de Threat Modeling en 7 pasos]] · [[Cursos/Seguridad/apuntes/stride-metodologia-amenazas|STRIDE]] · [[Cursos/Seguridad/entregables/tarea-2-threat-modeling|Borrador del grupo]]

**Valor: 5%** · Trabajo en clase, 1 hora 45 minutos · Entregable: documento corto de 2-5 páginas máximo.

**Caso asignado al Grupo 11 (compartido con Grupo 8): "VoteOnline" (Votación Institucional)**

> Sistema web de elecciones remotas para colegios profesionales. El votante recibe un token de un solo uso por correo electrónico, pero el token se genera utilizando el número de cédula del usuario pasado por una función Hash SHA-1 sin sal (*salt*), lo que permite predecir los tokens de otros votantes. Cuando el usuario vota, el sistema almacena en la misma tabla de la base de datos el ID del votante junto a la opción elegida para "evitar que vote dos veces". Para agilizar la auditoría, la base de datos permite consultas directas vía web a través de un panel de administración protegido únicamente por una cookie de sesión sin flag `HttpOnly`.

## Los 6 pasos de la actividad

**Paso 1 — Entender el sistema:** responder objetivo del sistema, usuarios, datos que procesa, y 3 suposiciones técnicas consistentes con la descripción. Resultado esperado: descripción corta (máx. 10 líneas).

**Paso 2 — Identificar activos críticos:** tabla de 5 activos (Activo | Tipo | ¿Por qué es crítico?). Responder además: si solo hay presupuesto para proteger 2, ¿cuáles se priorizan y por qué se descartan los otros dos?

**Paso 3 — Dibujar el flujo de datos (DFD):** a mano, con foto pegada en el documento — Usuario, Servidor, Base de Datos, Servicios externos. Marcar en rojo los **límites de confianza**. No se evalúa estética, se evalúa comprensión.

**Paso 4 — Identificar amenazas:** tabla de 5 amenazas (Amenaza | Activo afectado), con la mezcla obligatoria:
- 2 amenazas con atacante = empleado interno con permisos válidos
- 1 amenaza con vector = servicio externo de terceros
- 2 amenazas libres

**Paso 5 — Evaluar riesgos:** tabla (Amenaza | Impacto Alto/Medio/Bajo | Probabilidad Alta/Media/Baja | Riesgo).

**Paso 6 — Definir mitigaciones desde el diseño:** tabla (Amenaza | Mitigación desde diseño) — medidas de diseño, no parches de código. Pregunta clave: "¿cómo evitarías esto antes de programar?"

## Rúbrica (7 criterios, escala 1-4)

| Criterio | 4 – Excelente |
|---|---|
| 1. Comprensión del sistema | Describe claramente propósito, usuarios y tipos de datos tratados |
| 2. Identificación de activos críticos | Activos relevantes con justificación clara de por qué son críticos |
| 3. Diagrama de Flujo de Datos (DFD) | Componentes, flujos y límites de confianza bien definidos |
| 4. Identificación de amenazas | Amenazas relevantes, bien razonadas, alineadas al diseño del sistema |
| 5. Evaluación de riesgos | Prioriza correctamente según impacto y probabilidad |
| 6. Mitigaciones desde el diseño | Mitigaciones claras, realistas, aplicables antes del desarrollo |
| 7. Claridad y coherencia | Documento claro, estructurado, máximo 5 páginas |

## Otros casos del listado (referencia — no aplican al Grupo 11)

10 casos en total, cada uno asignado a 1-2 grupos: MedCare Connect (G1), AutoPark Express (G2), EduGrade Cloud (G3), PayQuick (G4), SmartHome Hub (G5), QuickEat (G6 y G12), SupplyChain Tracker (G7), **VoteOnline (G8 y G11)**, HR-Core (G9), TicketPass (G10).
