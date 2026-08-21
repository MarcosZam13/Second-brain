---
curso: QA
tema: Verificación, Validación y Pruebas — Semana 3
fecha: 2026-08-21
tipo: apunte
fuente: _fuentes/QA_verificacion-validacion-pruebas-semana3_2026-08-21.pptx
tags: [verificacion, validacion, pruebas, caso-de-prueba, proceso-de-pruebas, sistema-de-pruebas, principios-de-pruebas, etica-de-pruebas, qa-vs-testing]
---

# Verificación, Validación y Pruebas — Semana 3

Aseguramiento de la calidad del software, II Semestre 2026. Elaborado por Marlen Treviño, modificado por Marcos Rodríguez (ma.rodriguez@itcr.ac.cr).

Ver también: [[Cursos/QA/temario]] · [[Cursos/QA/entregas]] · [[Cursos/QA/apuntes/control-calidad-semana-2|Control de Calidad — Semana 2]] · [[Cursos/QA/apuntes/plantillas-fichas-caso-prueba-defectos|Plantillas — Ficha de Caso de Prueba y Defecto]]

## Verificación y Validación (V&V)

Procesos de evaluación de productos, útiles para determinar si se satisfacen las necesidades del negocio y si se está construyendo acorde a las especificaciones.

| | Verificación | Validación |
|---|---|---|
| Busca | Comprobar que el software está de acuerdo con su especificación; que satisface sus requisitos funcionales y no funcionales | Asegurar que el sistema satisface las expectativas del cliente |
| Determina | Consistencia, completitud y corrección de los artefactos de las distintas fases (productos intermedios) | La corrección del producto final respecto a las necesidades del usuario |
| La realiza | Ingenieros, con un modelo del programa y el programa en sí | El usuario, con lo que él espera del programa y el programa en sí |
| Pregunta clave | ¿Se está construyendo el producto de la manera correcta? ¿Qué haga lo correcto? | ¿El software cumple las expectativas del cliente? ¿Se está construyendo el producto correcto? ¿Qué sea lo correcto? |

## V&V en el ciclo de vida

- **Modelo en cascada** — ordena las etapas de forma que cada una espera a que termine la anterior. Las pruebas se hacen al final, por lo que los defectos se detectan cerca de la fecha de implementación → coste muy elevado de corrección.
- **Modelo en V** — soluciona ese problema: integra V&V en cada fase del ciclo de vida. La rama izquierda define especificaciones, la derecha las comprueba (contra la izquierda), y donde se juntan ambas está la corriente de desarrollo. Permite empezar las pruebas tan pronto como sea posible.
- **Modelo incremental** — se construye el producto añadiendo funcionalidades por incremento; cada funcionalidad se prueba a medida que se agrega, sin esperar la implementación completa.
- **Modelo por prototipos** — arranca recolectando requisitos, se construye un prototipo que el cliente evalúa y que sirve para refinarlos; V&V están muy presentes porque hay revisiones periódicas con el cliente.
- **XP (Extreme Programming)** — diseño y codificación incrementales; **probar** valida la correcta implementación de los requisitos; **escuchar** al cliente para entender sus necesidades.
- **Pilares Scrum** — Transparencia (comunicación constante del equipo, el cliente prueba lo pedido cada 2 semanas), Adaptación (reuniones diarias, cambios de requerimientos, retrospectiva de sprint, identificación de riesgos), Inspección (inspeccionar con frecuencia artefactos y progreso hacia los objetivos del sprint).

### Ciclo de vida genérico del software vs. pruebas (diagrama de clase)

```
Planificación → Diseño → Codificación → Pruebas → Liberación del producto → Cierre
     │              │           │            │
Estrategia    Diseño de    Pruebas       Pruebas
de pruebas    pruebas      unitarias →   sistema ↔ UAT
                            Pruebas       Gestión de puesta en marcha
                            integración
                                │
                    Pruebas de rendimiento ↔ Pruebas de seguridad (transversales)
```

La fila superior es el ciclo de vida genérico del software; la fila inferior muestra qué actividad de prueba corre en paralelo a cada etapa. Pruebas de rendimiento y de seguridad son transversales — se relacionan con integración, sistema y UAT a la vez.

## ¿Qué son las pruebas?

- "Proceso que consiste en todas las actividades del ciclo de vida, tanto estático como dinámico, que tiene que ver con planificación, preparación y evaluación de productos de software y productos relacionados al trabajo para determinar que satisfagan los requisitos especificados, para demostrar que son aptos para el propósito y para detectar defectos." — RBCS
- "La prueba (testing) es el proceso de ejecutar un programa con la intención de encontrar fallos." — Glenford J. Myers
- "Una investigación técnica del producto bajo prueba para proporcionar a los interesados (stakeholders) información relacionada con la calidad." — Cem Kaner

### Objetivos de las pruebas

- Encontrar defectos y proporcionar a los programadores la información que necesitan para corregir los importantes.
- Ganar confianza acerca del nivel de calidad del sistema.
- Prevenir defectos (participación temprana en revisiones y diseño anticipado de las pruebas).
- Proporcionar información sobre los aspectos más importantes de la calidad del sistema bajo prueba.
- Ayudar a la gerencia a comprender la calidad del sistema.

## Caso de prueba

> "Un caso de prueba es un conjunto de entradas, condiciones de ejecución y resultados esperados, desarrollado para conseguir un objetivo particular o condición de prueba."
> "Un caso de prueba es un proceso detallado que busca probar una funcionalidad o requerimiento particular, parcial o totalmente."
> "Un buen caso de prueba tiene una alta probabilidad de encontrar defectos."

Ver plantillas concretas de ficha de caso de prueba y de defecto en [[Cursos/QA/apuntes/plantillas-fichas-caso-prueba-defectos]].

### Ciclo de vida de un caso de prueba

Estados: **Nuevo → Automatizado → Ejecutado**. Cada caso queda asociado a un requerimiento, tiene un script de ejecución, y cada ejecución produce una versión de producto + resultado.

```
Test Plan → Group of requirements
    Test Cases (1…N by requirement)
        Test executions (1…N)
            - Results (Pass / Fail) (1 by execution)
            - Bugs? (0…N)
```

## Proceso de pruebas

Las pruebas de software se integran dentro de las diferentes fases del ciclo del software; puede considerarse un subproyecto dentro del proyecto sobre el que se ejecutan. Al superar todas sus actividades se obtiene:

**Salidas:**
- Producto probado y listo para su implantación.
- Planes de prueba con los casos de prueba identificados.
- Informes de pruebas: resultados, errores detectados, acciones de corrección, evidencia de superación de todas las pruebas.
- Elementos de prueba: scripts, programas de prueba, datos de prueba, etc., desarrollados para ejecutar y reproducir las pruebas.

**Objetivos del proceso de pruebas:**
- Establecer la participación de los roles implicados.
- Definir alcance, momento y características de las pruebas a realizar.
- Definir contenidos de los manuales de usuario y de administración.
- Establecer requisitos de aceptación del producto antes de pasar a la siguiente fase del ciclo de vida.
- Definir el ciclo de vida de gestión de un caso de prueba.
- Establecer mecanismos de resolución de casos fallidos.
- Presentar técnicas y estrategias para elaborar y ejecutar pruebas.

### Productos del proceso de pruebas

- **Plan de pruebas** — define forma, nivel de cobertura y estrategias a seguir según el estado del producto a probar.
- **Informe de pruebas** — documento con objetivo y alcance de las pruebas, resultados obtenidos, evaluación de los elementos de prueba respecto a sus criterios de salida, y resultado final.

## Sistema de pruebas

### Componentes

| Componente | Descripción |
|---|---|
| **Equipo** | Ingenieros de pruebas, técnicos de pruebas y responsable de pruebas; tienen las habilidades y experiencia para diseñar, implementar y usar componentes de pruebas |
| **Procesos** | Condiciones informales, formales, no documentadas y documentadas en las que se realiza el trabajo de pruebas |
| **Entorno** | Hardware, software, infraestructura de redes, oficina/laboratorio y demás elementos del lugar de trabajo |
| **Recursos** | Casos de prueba, datos de prueba, herramientas de prueba y otro material de desarrollo |

### Relación entre los componentes

```
                Entorno de pruebas
                       ▲
   Determinan el uso de │  Proporcionan una plataforma
                         │  para la operación de
Procesos ◄──────── Equipo de pruebas ────────► Recursos
de prueba   Crean,       │      Diseñan,           de prueba
Articulan,    Forman, Aplican,  Implementan, Adquieren,
Internalizan              Operan, Mantienen
        └────── Son utilizados acorde a los ──────┘
```

El equipo de pruebas determina el uso del entorno, y crea/articula/forma/aplica/internaliza los procesos; procesos y recursos se relacionan entre sí ("son utilizados acorde a los"); equipo y recursos se diseñan/implementan/adquieren/operan/mantienen mutuamente; entorno y equipo proporcionan una plataforma de operación entre sí.

### Atributos deseables de un buen sistema de pruebas

| Atributo | Qué significa |
|---|---|
| **Funcional** | Debería cubrir los riesgos de calidad críticos |
| **Fiable** | Al ejecutar la misma prueba sobre el mismo sistema, deberían obtenerse los mismos resultados |
| **Robusto** | Cambios pequeños y errores menores en el entorno de prueba no deberían causar fallos mayores en las pruebas |
| **Eficiente** | La ejecución de pruebas debería ser rápida |
| **Portable** | Debería permitir a los técnicos ejecutar pruebas en cualquier plataforma |
| **Útil** | Para todos los que quieran usarlo; curva de aprendizaje corta para personal calificado |

## Principios de las pruebas

1. **Las pruebas revelan la presencia de defectos, pero no pueden probar su ausencia.** Metáfora de la huerta: si ve hojas comidas sabe que hay insectos, pero no verlos no significa que no los haya — algunos son fáciles de detectar, otros no.
2. **Imposibilidad de pruebas exhaustivas.** Los caminos de ejecución en software no trivial son casi infinitos; hay flujos de datos separados en espacio (características) y tiempo (datos estáticos); pequeños cambios pueden provocar regresiones no lineales al tamaño del cambio; perfiles de uso y configuración variados (algunos desconocidos o imposibles de conocer).
3. **Beneficios de las pruebas tempranas.** El costo de un defecto tiende a aumentar a medida que el proyecto avanza; la mayor parte del costo de un defecto pre-versión es el esfuerzo de eliminarlo (costos más altos → cronogramas más largos); mientras más defectos entran a una actividad de QA/pruebas, más defectos se escapan de esa actividad.
4. **Agrupamiento (aglomeración) de defectos.** La distribución de defectos es desigual — ejemplos históricos: MVS (38% de defectos de campo en el 4% de los módulos), IMS (57% en el 7% de los módulos). Capers Jones: la presencia excesiva de módulos propensos a errores reduce 50% la productividad de mantenimiento. Regla de Pareto (20/80).
5. **Paradoja del pesticida.** Si rocía pesticida en la huerta, los gusanos picudos mueren pero no es eficaz contra todos los insectos — igual que las pruebas repetidas se vuelven menos eficaces (las pruebas funcionales no encuentran defectos de rendimiento). Hay que variar las técnicas de prueba (seguridad, rendimiento, etc.) si el objetivo es seguir encontrando defectos.
6. **Las pruebas deberían adaptarse a necesidades específicas.** El contexto cambia cómo se prueba (ej. seguridad en e-commerce vs. una red social de fotos) y el impacto de los problemas no es uniforme (trivial vs. costoso/perjudicial, hasta lesiones o muerte). Fallas medias por KLOC según contexto: 3-10 en software comercial típico, 1-3 en software industrial típico, 0.01 en código de lanzamiento de la NASA.
7. **Falacia de la ausencia de errores.** Encontrar y corregir errores no garantiza la satisfacción del cliente; los proyectos exitosos equilibran características, cronograma, presupuesto y calidad; muchos productos con pocos defectos han fracasado en el mercado. *"El testing puede probar la presencia de errores, pero no la ausencia de ellos."* — Edsger Dijkstra.

## Psicología de las pruebas

**Atributos de un buen probador:** curiosidad, atención al detalle, buenas habilidades de comunicación — la mezcla correcta de habilidades es necesaria.

**Habilidades:**
- Lectura (especificaciones, correos, casos de prueba...) y escritura (casos de prueba, informes de defectos, documentación).
- Tecnología: lenguajes de programación, sistemas operativos, redes, Internet, dispositivos móviles.
- Dominio de la aplicación: banca, oficina, salud, etc.
- Pruebas: construcción de guiones, exploración y ataque del sistema, automatización, modelado de rendimiento.

**¿Constructor o destructor?** A veces se percibe que el probador critica el producto o a su autor, y se visualiza el testing como actividad destructiva (ojo crítico/constructivista) — el probador debe comunicar los defectos de forma constructiva.

## Código de ética de las pruebas

La ética son reglas de conducta reconocidas para una clase de acciones humanas; los probadores tienen acceso a información confidencial/privilegiada y las guías éticas ayudan a usarla adecuadamente.

| Principio | Regla |
|---|---|
| **Público** | Actuar coherentemente con el interés público (ej. salud de quienes usarán el sistema) |
| **Cliente y empleador** | Actuar en el mejor interés de cliente y empleador, compatible con el interés público — no dejar cosas a medias o mal hechas conscientemente por quedar bien con alguien |
| **Producto** | Asegurar que los entregables cumplan los estándares más altos posibles — lo mejor posible, aunque no nos vean |
| **Juicio** | Mantener integridad e independencia en el juicio profesional — ante conflictos, no afectar al equipo, ser imparcial |
| **Profesión** | Promover la integridad y reputación de la profesión — el QA a veces se menosprecia por ser "el malo", pero eso se reduce viendo al equipo como un todo (ej. en Ágil) |
| **Colegas** | Ser justo y de ayuda con los colegas, promover cooperación con desarrolladores |
| **Uno mismo** | Aprendizaje permanente, mantenerse al día, método ético para la práctica profesional |

## QA vs Testing

- **QA (Quality Assurance) ⊃ Quality Control ⊃ Testing** — Testing es el círculo más interno; QA es el más amplio que contiene a ambos.
- **QA:** define procedimientos, coordina revisiones entre pares, controla procesos, define métricas y estándares, analiza el testing, hace auditorías/muestreos, busca mejora continua.
- **Software Testing:** black-box testing, white-box testing, regression test, sanity test, functional test, smoke test, bug verification, load testing, performance test.

*Nota de clase: "Semanas 1, 2 y 3, y de acá en adelante" — QA vs Testing es un hilo conductor de todo el curso, no un tema aislado de esta semana.*

## Actividad de clase

- **Telaraña conceptual** — dinámica de repaso de los conceptos vistos.
- **Configuración de Jira + TCMS** (Test Case Management System) — trabajo práctico de herramientas.
- **Repaso final** — quiz interactivo vía Kahoot.
