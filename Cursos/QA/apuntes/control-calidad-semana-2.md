---
curso: QA
tema: Control de Calidad — Semana 2
fecha: 2026-08-12
tipo: apunte
fuente: _fuentes/QA_control-calidad-semana-2_2026-08-12.pdf
tags: [calidad, control-de-calidad, aseguramiento-calidad, defectos, fallo-error-defecto, costos-de-calidad]
---

# Control de Calidad — Semana 2

Aseguramiento de la calidad del software, II Semestre 2026. Elaborado por Marlen Treviño, modificado por Marcos Rodríguez (ma.rodriguez@itcr.ac.cr).

Ver también: [[Cursos/QA/temario]] · [[Cursos/QA/entregas]] · [[Cursos/QA/apuntes/calidad-semana-1|Calidad — Semana 1]]

## Por qué importa el control de calidad — casos reales

Casos usados en clase para ilustrar el costo de no tener (o tener mal diseñado) un control de calidad:

- **Boeing 737 MAX** — bug de software (MCAS) que causó la caída de dos aviones.
- **Fujitsu (Reino Unido)** — bug en el sistema Horizon que llevó a cientos de personas inocentes a prisión por fraude que nunca cometieron.
- **Knight Capital** — bug de software que hizo quebrar a la empresa en minutos por operaciones bursátiles erróneas.
- **Therac-25** — máquina de radioterapia cuyo defecto de software administró dosis letales de radiación a pacientes.
- **CrowdStrike** — fallo de actualización que colapsó sistemas Windows a nivel mundial.
- **Samsung Galaxy Note 7** — falla en las celdas de batería que causó incendios/explosiones; pregunta abierta en clase: ¿qué falló en el proceso de control de calidad de este producto?

## Control de calidad: origen

Tuvo su origen en la **producción industrial masiva de principios del siglo XX**.

## Control de calidad: definición

- **Sistema adoptado por las empresas** para medir la calidad de productos y servicios, evaluando si están de acuerdo con sus especificaciones técnicas.
- Son los **procesos y métodos** utilizados para controlar el trabajo y observar si se cumplen los requisitos.
- Etapa **crucial en cualquier proceso productivo**: garantiza la correcta realización de los procesos llevados a cabo y asegura que lo producido cumpla con sus legislaciones y objetivos.

**Ejercicio de clase — [userinyerface.com](https://userinyerface.com/game.html):** un "formulario" deliberadamente lleno de patrones oscuros/anti-UX, usado para mostrar en carne propia que:
- Los errores de UX se convierten en **defectos de calidad**.
- La falta de atención genera **omisión de fallos**.
- Las **pruebas exploratorias** revelan problemas que scripts de prueba rígidos no cubren.

## Control de calidad: 4 funciones

1. **Reportes**
2. **Pruebas**
3. **Auditoría**
4. **Monitoreo**

## Control de calidad: beneficios

- Tener una visión sobre los procesos de la empresa, entendiendo el orden y su interrelación.
- Llevar a cabo un seguimiento detallado de las operaciones.
- Conseguir un flujo productivo más eficaz.
- Identificar errores y problemas con anterioridad, corregirlos y prevenirlos.
- Identificar los niveles de calidad que el mercado y los clientes esperan.
- Mejorar el compromiso de los empleados.
- Aumentar el número de clientes valiosos.
- Fortalecer la imagen de marca.
- Y, lo más importante: **satisfacer las necesidades de los clientes**.

## Actividad de clase — torre de globos

**Objetivo:** aplicar el concepto de control de calidad. **Materiales:** 12 globos rojos, 12 verdes, 12 blancos, cinta, tijera, regla.

**Procedimiento:**
- Dividir a los asistentes en 4 equipos: Grupo 1 (globos verdes), Grupo 2 (globos blancos), Grupo 3 (globos rojos), Grupo 4 (cinta, regla y tijera — rol de **inspección**).
- En 10 minutos, cada equipo arma una torre de 12 globos (4 verdes, 4 blancos, 4 rojos) que cumpla: globos intercalados, solo pegados con cinta (no nudos), todos del mismo tamaño.

**Preguntas de reflexión de la actividad:**
- ¿Cómo se sintieron al realizar la dinámica? ¿Qué inconvenientes tuvieron? ¿Qué estrategias emplearon? ¿De qué forma aplicaron el concepto de control de calidad?
- ¿Qué pasa cuando no hay control?
- ¿Qué ocurre cuando el control está mal diseñado?
- La diferencia entre producir rápido y producir bien.

## Control de calidad de software

**Definición:** conjunto de procedimientos utilizados por las organizaciones para garantizar que un producto de software cumpla con sus objetivos de calidad al mejor precio para el cliente, y para mejorar continuamente la capacidad de la organización de producir software en el futuro.

**Actividades principales:**
1. **Inspección**
2. **Revisión**
3. **Proceso de pruebas**

## Control de calidad vs. aseguramiento de la calidad

**Regla mnemotécnica de la clase:** *Aseguramiento se enfoca en el proceso. Control se enfoca en el producto.*

| Aspecto | Control de calidad | Aseguramiento de la calidad |
|---|---|---|
| Concepto | La calidad la controla una sola persona, mediante inspección del producto después de completada la producción | No hay una sola persona encargada; todo el negocio se enfoca en asegurar la calidad de la producción |
| Costo | Se establece una tasa de rechazo aceptable (ej. 2% de los productos puede fallar) | Se esperan 0 rechazos — cada producto debe pasar la inspección |
| Proceso | La calidad termina con el trabajo (entrega) | La calidad involucra a distribuidores y servicio postventa |
| Personas | Responsabilidad de una sola persona — una vía de comunicación | Responsabilidad de todo el equipo — cultura de calidad total, comunicación de 360° |

Recursos de tarea mencionados en clase (entrevistas en YouTube): *Aseguramiento vs. Control de calidad — Entrevista a Javier Marchese*, *Aseguramiento de la Calidad — Entrevista a Min Chen*, *Pruebas de Software (Testing de Software) — Entrevista a Javier Marchese*.

## Fallo, defecto y error

Cadena: **Fallo → Defecto → Error** (en el orden en que se manifiestan/descubren; la causalidad real va al revés — ver relación abajo).

- **Fallo:** ocurre cuando algo deja de funcionar cuando debería, o como debería. Es la manifestación física o funcional de un defecto — la discrepancia visible que se produce al ejecutar un programa con un defecto, respecto a la ejecución del programa correcto (IEEE).
- **Defecto:** carencia de una cualidad propia de algo, o imperfección (RAE). Es la **causa de un fallo**. Es algo en el producto que: está pero no debe / no está pero debe / no está como debe estar.
  - Desde el punto de vista del **productor**: un requerimiento del producto que no ha sido cumplido, o un atributo que el producto posee que no fue definido como parte de los requerimientos.
  - Desde el punto de vista del **cliente**: cualquier cosa que cause su insatisfacción, sea o no un requerimiento definido.
- **Error:** acción humana que produce un resultado incorrecto. El estándar IEEE 829 lo define como "una idea falsa o equivocada" — una imperfección/deficiencia que hace que el producto no cumpla los requerimientos (ej. malinterpretar un requisito o la funcionalidad de un método). **Un error puede conducir a uno o más defectos.**

**Relación (resumen de la clase):**
- Un **error** lo **COMETE una PERSONA** durante el desarrollo.
- Un **defecto** se **INTRODUCE en el PRODUCTO** durante su desarrollo.
- Un **fallo OCURRE durante el FUNCIONAMIENTO**.

**Ejemplo trabajado en clase:**
- Error: el programador no utiliza una condición para conocer si el denominador es cero en una división.
- Defecto: no se maneja la excepción.
- Fallo: el sistema finaliza su ejecución inesperadamente.

**Pregunta de examen (formato relevante para el curso):** *"Un teléfono que suena momentáneamente distrae a un programador, causando que programe incorrectamente la lógica que verifica el límite superior de una variable de entrada. Durante pruebas de sistema, un probador observa que la variable acepta valores inválidos. La lógica codificada incorrectamente para el límite superior es: (a) la causa raíz, (b) la falla, (c) un error, (d) el defecto"* → respuesta: **(d) el defecto** (la lógica mal codificada que quedó en el producto es el defecto; el momento de distracción es la causa raíz del error del programador, y la aceptación de valores inválidos observada por QA es el fallo).

## Defecto: ciclo de vida

```
Abierto → Resuelto → Cerrado
   ↑___________________|
```

**Resoluciones posibles al pasar de Abierto a Resuelto:** Arreglado, No se arreglará, Por diseño, Pospuesto, Duplicado, No reproducible.

## Defecto: tipos

| Tipo | Incluye |
|---|---|
| **Defectos en requisitos** | Requisitos/especificaciones, funcionalidad, interfaz de usuario/software/hardware, descripción funcional. Ej.: descripción incorrecta de cómo el software se comunica con software externo, hardware y usuarios |
| **Defectos de diseño** | Algoritmos, lógica de control, estructuras de datos, acceso a bases de datos, formularios de entrada/salida, descripción de interfaz, comunicación entre procesos, definición de datos, diseño del módulo, chequeo de errores, estándares |
| **Defectos de código** | Causados por pobre comprensión del diseño, mala elección de estructuras de datos/algoritmos, o errores de lógica/sintaxis; problemas de cómputo o manipulación de datos, implementación/interfaz del módulo, estándares |
| **Defectos de documentación** | Errores en manuales, instrucciones de instalación, demostraciones — todo centrado en el cliente |
| **Defectos del entorno de apoyo** | Software/hardware de pruebas, herramientas de desarrollo, software de integración |

## Defectos: clasificación por severidad

- **Críticos** — violan leyes, agreden al consumidor, o hacen inservible el producto.
- **Mayores** — disminuyen el correcto funcionamiento/utilización del producto y son notados por el consumidor.
- **Menores** — disminución leve del funcionamiento, probablemente no la note el consumidor.

## Costos de la calidad

**Definición:** desembolsos que tiene la empresa para asegurar y garantizar la calidad de sus productos/servicios, más las pérdidas sufridas cuando no se logra la calidad.

### Costos de no conformidad vs. costos de conformidad

- **Costos de no conformidad** — producidos como consecuencia de defectos o fallos.
  - *Anomalías internas* (mientras el producto sigue bajo control de la empresa): rechazos y mermas, compras inutilizables, averías de equipos, desvalorización del producto, rotura de stock, contaminación.
  - *Anomalías externas* (después de la entrega): reclamaciones de clientes, garantías, descuentos, campañas de sustitución de productos defectuosos, indemnizaciones.
- **Costos de conformidad** — producidos para detectar o evitar que se produzcan defectos.
  - *Costos de detección*: control de recepción, control en proceso, control de producto terminado, controles subcontratados, mantenimiento/calibración de equipos de control, materiales, estudios de satisfacción del cliente.
  - *Costos de prevención*: departamento de calidad, revisión del diseño, formación y sensibilización, mantenimiento preventivo, evaluación de proveedores, sistemas de mejora, estudios de expectativas del cliente.

**Trade-off implícito de la clase:** invertir más en prevención/detección (costos de conformidad) reduce los costos de no conformidad — el balance entre ambos es lo que se conoce como el costo total de la calidad.
