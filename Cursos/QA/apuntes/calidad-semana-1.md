---
curso: QA
tema: Calidad - Semana 1 (Definición y evolución del concepto)
fecha: 2026-08-07
tipo: apunte
fuente: _fuentes/QA_calidad-semana-1_2026-08-07.pptx
tags: [calidad, aseguramiento-calidad, definicion-calidad, evolucion-calidad, sqa]
---

# Calidad — Semana 1

Aseguramiento de la calidad del software, II Semestre 2026. Contacto: Marcos Rodríguez (ma.rodriguez@itcr.ac.cr).

## Presentación del curso

**Objetivo del curso:** experimentar los procesos de calidad del software mediante actividades de planeación, validación y verificación, para producir artefactos y sistemas que satisfagan los requerimientos en forma oportuna y económica.

**Objetivos específicos:**
- Describir las características de la calidad del software mediante la revisión de modelos pertinentes.
- Diferenciar los conceptos de verificación y validación de software, aplicando estándares y técnicas de evaluación.
- Aplicar métodos de aseguramiento y control de la calidad integrados a planes de proyectos.
- Examinar productos de software con técnicas de evaluación apoyadas por herramientas.

**Cronograma (temas por semanas):**
| Semanas | Tema |
|---|---|
| 1 | Calidad de software |
| 2 | Aseguramiento de la calidad del software |
| 2 | Control de calidad |
| 3 | Pruebas de software |
| 4 | Verificación de software |
| 5 | Validación de software |
| 10 | Herramientas de apoyo |

**Evaluación:**
| Rubro | Porcentaje |
|---|---|
| Tareas y quices (todas las semanas) | 20% |
| Laboratorios (3, parejas aleatorias) | 15% |
| **Proyecto** | **50%** |
| — Planificación del proyecto | 5% |
| — Plan de pruebas | 10% |
| — Proyecto de pruebas | 15% |
| — Informe de pruebas | 10% |
| — Presentación (inglés) | 5% |
| — Diario reflexivo (bitácora) | 5% |
| Examen I (digital – presencial) | 15% |
| **Total** | **100%** |

## Definición de calidad

Varios autores, distintos énfasis:
- **Crosby:** cumplimiento de los requerimientos; el sistema es la prevención, el estándar es cero defectos.
- **Juran:** ausencia de defectos y adecuación al uso.
- **Deming:** grado perceptible de uniformidad y fiabilidad a bajo costo, adecuado a las necesidades del cliente.
- **Ishikawa:** diseñar, producir y ofrecer un producto o servicio útil, al mejor precio posible, que siempre satisfaga las necesidades del cliente.
- **Norma ISO 9000:** grado en el que un conjunto de características inherentes cumple con los requisitos.

**Idea clave de la actividad "¿qué tiene más calidad?":** dos productos pueden tener la misma calidad siempre que cumplan con sus requerimientos — la calidad se valida probando las especificaciones, no comparando a simple vista.

## Características y requisitos

- **Características:** propiedades asignadas a un producto/servicio para cubrir necesidades del usuario (ej. productos: apariencia, peso, durabilidad, estilo, dimensión; servicios: rapidez, honestidad, puntualidad, flexibilidad, cortesía, efectividad).
- **Requisitos:** cómo tienen que ser esas características. Incluyen requisitos obligatorios (seguridad, legales, etc.).

## Evolución del concepto de calidad (etapas)

1. **Artesanal** — el productor y el usuario suelen coincidir; el control de calidad es implícito en el propio proceso artesanal.
2. **Industrialización** — el concepto de calidad es sustituido por el de producción: hacer mucho y rápido sin importar la calidad. Importan cantidad y tiempo, no la calidad.
3. **Control final** — ya no importa solo la cantidad producida sino que el cliente reciba el producto según sus especificaciones. Nace el Control de Calidad entendido como control final. *Calidad = Control de Calidad = Control Final.*
4. **Control en el proceso** — los defectos no solo aparecían en la inspección final sino también por materia prima defectuosa. Se agregan puntos de inspección durante el proceso para prevenir, no solo detectar. *Calidad = Prevención = Ausencia de defectos.*
5. **Control en diseño** — seguían apareciendo problemas de calidad no atribuibles a materia prima, máquinas ni proceso: el problema estaba en el propio diseño (especificación irrealizable). La calidad empieza a programarse desde el diseño. *Calidad = Gestión de Calidad.*
6. **Mejora continua** — para ser competitivos hay que buscar la excelencia mediante mejora continua de productos/servicios, con un sistema de gestión que alinee lo que el cliente busca, lo que se programa y lo que se fabrica.

## Calidad de software

- **IEEE Std. 610-1990:** grado con el que un sistema, componente o proceso cumple los requerimientos especificados y las necesidades o expectativas del cliente/usuario.
- **Pressman (1992):** concordancia con los requisitos funcionales y de rendimiento (no funcionales) explícitamente establecidos, con los estándares de desarrollo explícitamente documentados, y con las características implícitas que se esperan de todo software desarrollado profesionalmente.
- **ISO 8402 (UNE 66-001-92):** conjunto de características de una entidad que le confieren su aptitud para satisfacer las necesidades expresadas e implícitas.

## Aseguramiento de la calidad del software (SQA)

**Definición:** conjunto de actividades (incluyendo facilitación, entrenamiento, medición y análisis) requeridas para proveer la confianza adecuada de que los procesos están establecidos y son continuamente mejorados, con el objetivo de producir un producto o servicio que cumple los requerimientos y está listo para usarse.

**Beneficios:**
- Se detectan problemas rápidamente — identificar problemas en etapas tempranas del desarrollo permite corregirlos de inmediato y avanzar más rápido.
- Se crean y siguen estándares de trabajo (codificación, documentación) que uniformizan y consolidan el proceso.
- Se verifica que los objetivos individuales vayan acordes con los objetivos de la organización.
- Se recomiendan métodos de trabajo ajustados a la naturaleza del producto a desarrollar.
- Se evita incurrir en costos innecesarios (ej. mantenimiento correctivo).
- Se planea la calidad — no es algo automático, hay que planearla, construirla e implantarla en el producto.
