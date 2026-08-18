---
curso: Seguridad
tema: Programa del curso IC-8071 — Seguridad del Software
fecha: 2026-08-18
tipo: apunte
fuente:
  - _fuentes/Seguridad_programa-curso_2026-08-18.pdf
tags: [programa, ic8071, temario]
---

# Temario — Seguridad del Software (IC-8071)

Ver también: [[Cursos/Seguridad/entregas]]

**Profesora:** Adriana Rojas Chavarria (adrojas@itcr.ac.cr) · Consulta: martes 7:00am–8:00am, virtual
**Vigencia del programa:** II semestre 2021 (programa base; el curso arrancó con ~2 semanas de atraso este semestre — la profesora está contando contenidos como si fuera semana 3)

## Datos generales

- **Código:** IC-8071 · Teórico-Práctico · 3 créditos · 4h clase/semana + 5h extraclase/semana
- **Ubicación:** electiva de 6to o 7mo semestre — Ingeniería en Computación, Plan 411
- **Requisito:** IC-5701 Compiladores e Intérpretes
- **Asistencia obligatoria** · sin correquisitos · sin suficiencia

## Descripción y objetivos

Fundamentos de seguridad del software: vulnerabilidades y vectores de ataque (Buffer Overflows, SQL Injection, robo de sesiones, entre otros) y las defensas para prevenirlos/mitigarlos — técnicas de programación segura, modelado de vulnerabilidades, pruebas avanzadas. Cierra con el impacto de "Seguridad por Diseño" (Security by Design) en el ciclo de desarrollo.

**Objetivo general:** diseñar soluciones de software seguro mediante Security by Design, garantizando confidencialidad, integridad y disponibilidad de los datos.

**Objetivos específicos:**
- Conocer escenarios de vulnerabilidad y vectores de ataque en el software.
- Evaluar estrategias de defensa para prevenir/mitigar ataques.
- Diseñar software con perspectiva de seguridad desde el diseño y a lo largo de todo el ciclo de desarrollo.

## Contenidos oficiales del programa

1. **La importancia de la Seguridad en el Software**
   Introducción · Historia · ¿Qué es Seguridad del Software? · Complejidad, Extensibilidad y Conectividad · Implicaciones Éticas · Legislación Costarricense y otros referentes
2. **Patrones de Ataque**
   Taxonomía de los patrones de ataque · Análisis de Riesgo en el Código Fuente · Patrones de Ataque Comunes · Aplicación de los patrones de ataque
3. **Ingeniería inversa para análisis de software**
   Conceptos y Herramientas · Enfoques de Ingeniería Inversa · Métodos de Reversión · Decompilado y Desensamblado · Análisis dinámico y estático de código
4. **Explotación de Software de Servidores**
   Escalación de privilegios · Encontrar puntos de inyección · Explotación de la confianza · Patrones de ataque específicos para software de servidores
5. **Explotación de Software en Clientes**
   Programas cliente como objetos de ataque · Cross-site Scripting (XSS) · Client Scripts y código malicioso
6. **Alteración de Entrada de Usuario**
   Detección de Intrusos · Tracing Code · Creación de Solicitudes Equivalentes · Envenenamiento del proceso de Auditoría (Audit Poisoning)
7. **Ciclo de vida de Desarrollo de Software (buenas prácticas de seguridad)**
   Estándares de Desarrollo de Software Seguro · Análisis de Riesgo orientado a la arquitectura · Marcos de Trabajo para el Análisis de Riesgo · Casos de Abuso · Requerimientos de Seguridad en Software

## Metodología

Clases magistrales + desarrollo de casos por la profesora, con alta participación del estudiante (llamadas orales, casos en pizarra, trabajo en grupo). Se espera profundizar en las lecturas recomendadas fuera de clase.

## Evaluación (ponderación oficial)

| Rubro | % |
|---|---|
| Tareas | 40 |
| Exámenes | 40 |
| Proyectos | 20 |
| **Total** | **100** |

Ver el detalle de fechas y entregas concretas en [[Cursos/Seguridad/entregas]].

## Bibliografía

- Gary McGraw. *Exploiting Software: How to Break Code*. 1a ed., Addison Wesley.
- Gary McGraw. *Software Security: Building Security In*. 1a ed., Addison Wesley.
- Michael Howard y Steve Lipner. *The Security Development Lifecycle*. Microsoft Press.
