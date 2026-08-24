---
curso: Seguridad
tema: "STRIDE — Modelo de Amenazas (Microsoft)"
fecha: 2026-08-24
tipo: apunte
fuente:
  - _fuentes/Seguridad_stride-metodologias_2026-08-24.pptx
tags: [stride, threat-modeling, dread, microsoft, tema2]
---

# STRIDE — Modelo de Amenazas (Microsoft)

Ver también: [[Cursos/Seguridad/temario]] · [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/apuntes/tema-2-ciclo-vida-desarrollo-software|Tema 2 — Ciclo de Vida de Desarrollo de Software]] (donde se referencia como material complementario para el Paso B del Análisis de Riesgo Orientado a Arquitectura) · [[Cursos/Seguridad/entregables/mapa-clase-3|Mapa Clase 3]] (ya cubría el significado de cada letra; esta nota agrega el proceso de aplicación y DREAD)

Presentación dedicada al modelo STRIDE, entregada junto con [[Cursos/Seguridad/apuntes/tema-2-ciclo-vida-desarrollo-software|Tema 2]] como material complementario ("ver ppt separada").

## Qué es

Desarrollado por Microsoft en 1999. Modelo de clasificación de amenazas que permite a los equipos de seguridad identificar y categorizar sistemáticamente los riesgos en sistemas de software. Es una metodología proactiva de threat modeling, aplicable desde las fases tempranas del diseño, y ampliamente adoptada en la industria.

## Las 6 categorías de amenazas

| Letra | Nombre | Descripción |
|---|---|---|
| **S** | Spoofing (Suplantación de Identidad) | Un atacante se hace pasar por otro usuario, sistema o componente para obtener acceso no autorizado |
| **T** | Tampering (Manipulación de Datos) | Modificación maliciosa de datos en tránsito, en reposo o en memoria del sistema |
| **R** | Repudiation (Repudio de Acciones) | Un usuario niega haber realizado una acción sin que el sistema pueda demostrarlo |
| **I** | Information Disclosure (Fuga de Información) | Exposición de datos confidenciales a partes no autorizadas |
| **D** | Denial of Service (Denegación de Servicio) | Ataques que agotan recursos del sistema, haciéndolo no disponible para usuarios legítimos |
| **E** | Elevation of Privilege (Escalada de Privilegios) | Un usuario obtiene permisos superiores a los asignados para realizar acciones no autorizadas |

(Ver también el resumen mnemotécnico ya guardado en [[Cursos/Seguridad/entregables/mapa-clase-3|Mapa Clase 3]]: cada letra rompe alguna pata de la tríada CIA — spoofing/tampering rompen integridad, info disclosure rompe confidencialidad, DoS rompe disponibilidad, elevation of privilege abre la puerta a todo lo demás.)

## Proceso de aplicación (5 pasos)

1. **Definir el sistema** — identificar componentes, flujos de datos, actores y límites de confianza mediante Diagramas de Flujo de Datos (DFD)
2. **Descomponer la aplicación** — mapear entradas, salidas, activos críticos y puntos de entrada; identificar la superficie de ataque (*Attack Surface*)
3. **Identificar amenazas** — aplicar STRIDE a cada elemento del DFD, preguntando "¿qué podría salir mal aquí según cada categoría?"
4. **Evaluar riesgos con DREAD** — priorizar las amenazas usando métricas de:
   - **D**amage (daño potencial)
   - **R**eproducibility (qué tan fácil es reproducir el ataque)
   - **E**xploitability (qué tan fácil es explotarlo)
   - **A**ffected users (cuántos usuarios se ven afectados)
   - **D**iscoverability (qué tan fácil es descubrir la vulnerabilidad)
5. **Definir mitigaciones** — seleccionar controles técnicos y de proceso para reducir o eliminar cada amenaza identificada

DREAD es información nueva que no estaba cubierta en el mapa mental de la Clase 3 (que solo tenía el significado de las 6 letras) — vale la pena repasarla si una pregunta toca "cómo se prioriza" una amenaza y no solo "qué tipos de amenaza existen".
