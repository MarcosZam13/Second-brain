---
curso: QA
tema: Taller — Árbol de problemas, árbol de objetivos y planificación inicial del proyecto
fecha: 2026-08-21
tipo: apunte
fuente: _fuentes/QA_taller-guia-planificacion-inicial-proyecto_2026-08-21.docx
tags: [proyecto, arbol-de-problemas, arbol-de-objetivos, smart, metas, indicadores, plan-del-proyecto]
---

# Taller — Árbol de problemas, árbol de objetivos y planificación inicial del proyecto

Ver también: [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]] · [[Cursos/QA/entregables/plan-del-proyecto|Plan del proyecto — Fase 1]] · [[Cursos/QA/entregables/seleccion-repositorio-proyecto|Selección de repositorio]] · [[Cursos/QA/entregas]]

Taller de la Fase 1 (Identificación del problema y definición de objetivos) del proyecto. Define **cómo** construir la justificación y los objetivos del [[Cursos/QA/entregables/plan-del-proyecto|Plan del proyecto]], más allá del esqueleto de documento ya cubierto en [[Cursos/QA/apuntes/proyecto-qa-guia]].

## Árbol de problemas

Herramienta para entender en profundidad las causas y efectos relacionados con un problema — se lee de abajo hacia arriba: causa más baja a la izquierda → sube causa por causa hasta la problemática → se conecta con sus efectos.

**Pasos:**
1. Definir la situación problema en el centro del diagrama — con detalles básicos de contexto, ni muy general ni muy específico.
2. Abajo: las causas, cada una conectada a la siguiente de forma lógica, yendo de lo general a lo específico.
3. Arriba: los efectos, partiendo del problema, también de lo general a lo específico.

## Árbol de objetivos (árbol de medios y fines)

Transforma el árbol de problemas: las causas (raíces) se vuelven **medios**, los efectos (hojas) se vuelven **fines**.

**Pasos:**
1. **De negativo a positivo** — redactar causas y efectos en positivo (causas → medios, efectos → fines). Si los medios/fines resultantes no son apropiados o quedan difusos, volver a discutir el árbol de problemas.
2. **Verificar y modificar** — chequear redundancias, semejanzas o inconsistencias con una relación 1 a 1 causa→efecto y efecto→fin.
3. **Ajustar** — hacer el método flexible: revisar si falta algo y agregarlo.

**Ejemplo trabajado en el taller:**
- Problema central: alta delincuencia juvenil en el barrio San Roque.
- Causa: centros de venta de drogas alucinógenas ofrecidas a la salida de los colegios del barrio.
- Efecto: aumento de la población juvenil que consume drogas alucinógenas.
- Efecto convertido en fin: disminución de la población juvenil que consume drogas alucinógenas.

## Objetivos

- Cada objetivo debe **comenzar con un verbo en infinitivo**.
- Deben ser **SMART**: **E**specíficos (claros sobre qué/dónde/cuándo/cómo cambia la situación), **M**edibles (posible cuantificar fines/beneficios), **A**lcanzables/Realizables (posible lograrlos con los recursos/capacidades disponibles), **R**ealistas (posible obtener el nivel de cambio reflejado), **L**imitados en tiempo (con periodo de cumplimiento establecido).

## Metas

Procesos que se deben seguir y terminar para llegar al objetivo — un objetivo es la sumatoria de sus metas, el resultado final de una serie de metas y procesos.

**Ejemplo (Tour de Francia):** el objetivo es ganar el título/la vuelta; la meta es ganar cada etapa. Existen también metas volantes y premios de montaña — metas intermedias dentro del proceso de alcanzar el objetivo.

## Indicadores

Especificación cuantitativa/cualitativa para medir el logro de un objetivo, aceptada colectivamente por los involucrados como adecuada. Deben ser **prácticos** (importantes y realistas), **independientes** (miden en qué medida los medios permitieron alcanzar los objetivos, no los medios en sí) y **focalizados** (población objetivo, lugar, tiempo, cantidad y calidad definidos).

**Ejemplo de formato de indicador:**

| Nombre del indicador | Descripción | Quién | Dónde | Cuánto | Cómo | Cuándo |
|---|---|---|---|---|---|---|
| Aumento de la utilidad | En el tercer año, tener un aumento del 10% o más en la utilidad respecto al estado antes de iniciar el proyecto | Compañía | Compañía | Igual o mayor a 10% | Aumento en la utilidad comparado con año 0 | Tercer año después del proyecto |

**Ejemplo objetivo/metas/indicadores (mismo formato que usará el equipo en el plan de pruebas):**

| Objetivo | Metas | Indicadores |
|---|---|---|
| Definir los casos de prueba necesarios para la adecuada determinación de que un requisito es satisfactorio | Utiliza las técnicas de prueba más adecuadas según la estrategia definida; define correctamente los casos tomando en cuenta valores válidos e inválidos; comunica con facilidad los resultados de su proceso | Define al menos 60 casos de prueba; el Plan de pruebas contiene todas las partes y está organizado como se solicitó; aplica correctamente reglas gramaticales y de acentuación; la redacción tiene concordancia, coherencia y claridad; puntualidad; participación; responsabilidad |

## Conexión con el proyecto — pendiente en el Plan del proyecto

[[Cursos/QA/entregables/plan-del-proyecto|El borrador actual del Plan del proyecto]] tiene la justificación (sección "Por qué") en prosa libre, pero **no** sigue todavía este taller: le falta construir explícitamente el árbol de problemas y el árbol de objetivos (medios/fines), y formalizar los objetivos específicos con su tabla de metas e indicadores en el formato de arriba. Se agregó como pendiente en esa nota.
