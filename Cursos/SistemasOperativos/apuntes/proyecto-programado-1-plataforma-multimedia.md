---
curso: SistemasOperativos
tema: "I Proyecto Programado — Plataforma Distribuida de Procesamiento Multimedia por Casos (v2.0)"
fecha: 2026-09-11
tipo: apunte
fuente: _fuentes/ProyectoProgramadoI_PlataformaMultimediaCasos_v2.pdf
tags: [proyecto-programado, sistemas-distribuidos, concurrencia, semana-9]
---

# I Proyecto Programado — Plataforma Distribuida de Procesamiento Multimedia por Casos (v2.0)

Ver también: [[Cursos/SistemasOperativos/temario]] · [[Cursos/SistemasOperativos/entregas]] · [[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3]] · [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]]

**IC-6600, II Semestre 2026.** Se asigna en semana 5 (2026-09-03); entrega en semana 9 (2026-10-01) según [[Cursos/SistemasOperativos/entregas|entregas.md]].

> Nota de versión del propio documento: esta v2.0 actualiza una versión previa que procesaba archivos individuales. Ahora la unidad de trabajo es el **caso** (uno o varios archivos relacionados, homogéneos o heterogéneos, sometidos como una sola solicitud). Se mantiene la arquitectura mínima, la exigencia de distribución física real y el dataset de prueba; cambia el modelo de la unidad de trabajo y la lógica de orquestación.

## Qué hay que construir

Plataforma distribuida: nodo coordinador + múltiples nodos worker (genéricos o especializados por tipo de contenido) + mecanismo de comunicación entre procesos/servicios + dashboard de monitoreo.

**Foco explícito de evaluación:** no es la reproducción multimedia ni una interfaz sofisticada, es la arquitectura distribuida de procesamiento con los principios de gestión de procesos y recursos del curso visibles. No se valora una implementación monolítica ni un modelo de "casos" que sea solo una etiqueta sobre archivos idénticos — tiene que resolver enrutamiento, sincronización y agregación real sobre casos heterogéneos.

## El caso como unidad de trabajo

- Un caso = 1+ archivos relacionados, sometidos como una sola solicitud.
- **Homogéneo:** todos los archivos del mismo tipo, misma operación.
- **Heterogéneo:** mezcla de audio/video/imagen, cada uno con su propia operación.
- El coordinador debe inspeccionar cada archivo del caso, decidir la operación (routing por tipo) y encolar cada sub-tarea.

Operaciones posibles por sub-tarea: conversión de formatos, extracción de audio desde video, generación de miniaturas/portadas, consulta o asociación de metadatos, integración de letras/recursos informativos, clasificación/organización de resultados.

## Conexión con Unidad 1 (heterogeneidad de cómputo)

El enrutamiento de sub-tareas a workers genéricos vs. especializados retoma la discusión de Unidad 1 sobre CPU/GPU/NPU: igual que una NPU rinde mejor para inferencia y una GPU para paralelismo masivo, ciertas operaciones (transcodificación de video) se benefician de workers con más cómputo, mientras otras (metadatos) corren bien en nodos de propósito general. Hay que **justificar** la decisión de asignación bajo esa misma lógica — ver [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]].

## Componentes mínimos

`Cliente → Cola → Coordinador (routing) → Workers`

- **Cola de trabajos:** almacena sub-tareas pendientes, consumo concurrente, orden/prioridades.
- **Coordinador/planificador:** recibe casos, inspecciona cada archivo y determina operación, descompone el caso en sub-tareas y las encola, lleva el estado agregado del caso, aplica sincronización tipo **barrier/join** para decidir cuándo un caso termina, asigna workers y redistribuye carga.
- **Workers:** ejecutan sub-tareas, reportan estado/resultado al coordinador. Cada equipo decide y justifica: workers genéricos vs. pools especializados (worker-video, worker-audio, worker-metadata) y cómo eso afecta el balanceo.
- **Intercomunicación:** cola, broker, sockets, mensajería o equivalente.
- **Monitoreo de recursos:** CPU, memoria, carga por worker, estado de nodos, sub-tareas activas/en espera agrupadas por caso.
- **Dashboard:** estado del sistema y nodos activos; estado agregado por caso (`queued`, `processing`, `completed`, `partially_completed`, `failed`, `retrying`, `cancelled`) y por sub-tarea/worker.
- **Dataset multimedia de prueba** (ver abajo).
- **Cliente de pruebas/generador de carga:** envía casos, consulta estado, recupera resultados, genera casos concurrentes.
- **Documentación:** manual de usuario + documentación técnica (arquitectura, despliegue, API si aplica).

## Generación de casos

- **Manual:** el cliente indica archivos del caso, operación (o deja que el coordinador la determine), prioridad/configuración.
- **Automática:** un proceso agrupa archivos por criterio (carpeta local, repositorio compartido, almacenamiento en la nube, metadatos de evento/sesión/usuario/lote), a partir de info asociada en BD/JSON, y genera las sub-tareas automáticamente.

## Estado y resultados

**Por sub-tarea:** id de trabajo y de caso, archivo y operación, estado (pendiente/asignado/en ejecución/completado/fallido), worker responsable, % de progreso, tiempos de inicio/fin.

**Por caso (agregado):** id, listado de sub-tareas, estado agregado — **el coordinador solo lo determina cuando tiene el resultado de todas las sub-tareas del caso (barrier/join)**. `completed` = todas exitosas; `partially_completed` = al menos una fallida.

Actualización asincrónica, consultable en tiempo real por dashboard/cliente. Resultados de cada sub-tarea van a un repositorio de resultados (almacenamiento local compartido, nube, carpeta distribuida, o BD/FS distribuido) — mecanismo a definir y justificar por el equipo.

## Reporte consolidado por caso

Al cerrar un caso (`completed` o `partially_completed`): id + momento de creación/fin, archivos procesados agrupados por tipo/operación, resultado de cada sub-tarea (éxito/fallo + detalle de error), tiempos del caso y de cada sub-tarea, worker(s) responsable(s), resumen agregado (ej. "de 55 archivos: 30 audios transcritos, 10 videos convertidos, 15 miniaturas generadas, 2 fallidos por formato no soportado").

## Arquitectura mínima de referencia

```
Cliente/Generador → Job Queue → Nodo Coordinador → Worker 1..n → Repositorio de resultados → Dashboard
```

- **Al menos 3 nodos worker concurrentes**, en **entidades de ejecución separadas** — idealmente 3 computadoras físicas distintas (una por integrante del equipo), en red.
- Si no hay 3 máquinas físicas: VMs, contenedores o instancias en la nube son válidos, **siempre que haya** separación real de procesos, comunicación por red (no memoria compartida) y coordinación distribuida real.
- **No es válido** que todo corra en una sola máquina sin distribución real.

## Dataset de prueba

- Mínimo 400–600 archivos multimedia, mezcla audio/video, formatos y tamaños diversos (mp3, wav, mp4, mkv, livianos/medianos/pesados).
- Organizado en al menos un conjunto de casos homogéneos y uno de casos heterogéneos.
- Metadatos asociados (JSON, BD, u otra estructura).
- Debe permitir: concurrencia dentro y entre casos, carga por lotes, análisis de tiempos por sub-tarea y por caso, observar saturación y redistribución de carga.
- Documentar composición, criterios de agrupación en casos, y volumen total.

## Entregables

Documento de arquitectura · repositorio de código · sistema funcional distribuido · dashboard (vista por caso y por sub-tarea) · documentación técnica y manual de uso · informe de pruebas (carga, distribución, casos heterogéneos, comportamiento del sistema).

## Rúbrica (escala 0–5)

| Rubro | Peso |
|---|---|
| Arquitectura del sistema | 15% |
| Implementación distribuida del sistema | 20% |
| Gestión de procesos, casos y concurrencia (routing, colas, barrier/join) | 20% |
| Monitoreo y balanceo de recursos | 15% |
| Procesamiento multimedia distribuido | 10% |
| Gestión de casos, archivos y resultados | 10% |
| Interfaz de usuario / dashboard | 5% |
| Documentación técnica y manual de usuario | 5% |

Escala de desempeño: 0 nulo, 1 deficiente, 2 básico, 3 aceptable, 4 bueno, 5 sobresaliente.

## Consideraciones tecnológicas

Libertad de stack, siempre que se justifique y garantice arquitectura distribuida real. Se recomienda herramientas gratuitas/open source y aprovechar las máquinas del equipo o nube gratuita/barata.

## Perspectiva desde los temas del curso

Administración de procesos · estados y control de trabajos (sub-tarea y caso) · planificación/asignación (routing) · colas · concurrencia y asincronía · sincronización (barrier/join) · comunicación entre procesos · administración de recursos y heterogeneidad de cómputo (Unidad 1) · monitoreo y balanceo de carga · sistemas distribuidos · administración de información y archivos.
