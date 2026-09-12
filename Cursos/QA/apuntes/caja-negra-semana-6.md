---
curso: QA
tema: Técnicas de diseño — Pruebas de Caja Negra (Semana 6)
fecha: 2026-09-12
tipo: apunte
fuente: _fuentes/QA_caja-negra-semana-6_2026-09-12.pdf
tags: [caja-negra, clases-equivalentes, valores-limite, combinacion-por-pares, tablas-de-decision, diagrama-de-estados, tecnicas-de-diseno-de-pruebas]
---

# Técnicas de diseño — Pruebas de Caja Negra (Semana 6)

Aseguramiento de la calidad del software, I Semestre 2025 (numeración de la diapositiva original) / II Semestre 2026 (cursada). Elaborado por Marlen Treviño (mtrevino@itcr.ac.cr).

Ver también: [[Cursos/QA/temario]] · [[Cursos/QA/entregas]] · [[Cursos/QA/apuntes/pruebas-software-semana-4|Pruebas de Software — Semana 4]] (niveles y tipos de prueba, donde ya se adelantaba esta clasificación) · [[Cursos/QA/entregables/plan-de-pruebas|Plan de pruebas — Fase 2]] · [[Cursos/QA/entregables/diario-reflexivo|Diario Reflexivo]]

## Ubicación dentro de los tipos de prueba

```
Pruebas
├── Estáticas (Análisis estático, Revisión)
└── Dinámicas
    ├── Caja Blanca
    ├── Caja Negra (Funcional / No funcional)
    └── Basadas en la experiencia
```

**Definición:** las pruebas de caja negra verifican las funcionalidades del software sin tomar como referencia la estructura del código interno, las rutas internas ni la implementación.

**Las 5 técnicas de diseño de caja negra, en el orden en que se ven (una es refinamiento de la anterior):**

```
Clases equivalentes → Valores límite → Combinación por pares → Tablas de decisión → Diagrama de estados
```

## 1. Clases equivalentes (partición de equivalencia)

Una **partición equivalente** es un grupo de datos con comportamiento análogo: cada miembro del grupo tiene el mismo significado para una situación específica. El método divide el dominio de entrada en un número finito de clases; probar un valor representativo de una clase equivale a probar cualquier otro valor de esa misma clase (si un caso de una clase detecta un error, el resto de casos de esa clase deberían detectarlo también, y viceversa).

- **Entradas válidas:** generan un valor esperado.
- **Entradas no válidas:** generan un valor inesperado (excepciones).

**Pasos:** identificar variables y sus posibles valores → identificar las clases de equivalencia → seleccionar representantes → seleccionar casos de prueba.

**Pautas para definir clases según el tipo de condición de entrada:**

| Tipo de condición | Regla | Ejemplo |
|---|---|---|
| Rango de valores | 1 clase válida + 2 inválidas | contador de 1 a 999 → válida: 1-999; inválidas: `<1`, `>999` |
| Valor o número de valores | 1 clase válida + 2 inválidas | 1 a 6 propietarios por auto → inválidas: 0 propietarios, más de 6 |
| Condición lógica ("debe ser") | 1 clase válida + 1 inválida | primer carácter de un identificador debe ser letra |

**Regla práctica:** no es necesario combinar clases inválidas entre sí en un mismo caso de prueba — cada clase inválida se prueba por separado, aislada, para saber exactamente qué la disparó.

**Ejemplo trabajado (cálculo de precio con descuento y envío):** variables `valorProducto` (≥0), `Descuento` (0-100), `gastosEnvio` (6, 9 o 12) — se arma una tabla de variable/clase válida/clase inválida/representantes, y de ahí se seleccionan los casos de prueba marcando qué clase cubre cada uno.

## 2. Valores límite (Boundary Value Analysis)

Refinamiento de las clases equivalentes: muchos defectos ocurren justo en, sobre o debajo de los extremos de una clase, así que se seleccionan los bordes (límite) y sus proximidades para las pruebas. Solo aplica cuando los elementos de la clase están **ordenados** (valores numéricos, tabla ASCII, etc.).

**Los 7 valores a considerar por cada límite:**

| Valor | Significado |
|---|---|
| Min− | Justo por debajo del mínimo |
| Min | Mínimo |
| Min+ | Justo por encima del mínimo |
| Nom | Promedio |
| Max− | Justo por debajo del máximo |
| Max | Máximo |
| Max+ | Justo por encima del máximo |

**Ejemplo (fecha día/mes/año, rango de año 1812-2013):** con permutación completa da 7×7×7 = 343 casos; con clases de equivalencia se reduce a 7; con valores límite queda en 8 (combinando solo los extremos relevantes, sin explotar todas las combinaciones).

**Ejemplos de clasificación rápida (Inválido bajo | Válido | Inválido alto):**
- Entero "cuántos ítems": `0 | 1...99 | 100`
- Cadena "clave 6-10 caracteres alfanuméricos": demasiado corta / demasiado larga además de bajo/alto.

**Ventajas:** reduce el número de casos necesarios; alta eficacia empírica (los casos en el límite producen mejores resultados que los que no lo son).
**Desventajas:** no prueba todas las entradas posibles, no cubre dependencias entre variables, no se puede medir qué porcentaje del sistema quedó cubierto.

## 3. Combinación por pares (pairwise / all-pairs)

Probar **todas** las combinaciones de variables es casi siempre inviable: 10 variables con 10 valores posibles cada una dan 10,000,000,000 casos. La técnica de combinación por pares genera un conjunto de casos donde **cada par de valores de variables distintas aparece representado al menos una vez** — no todas las combinaciones, pero sí toda combinación de a dos.

**Pasos:** identificar variables → identificar dominios/valores posibles (por ejemplo con clases de equivalencia) → generar las combinaciones de a pares → analizar combinaciones inválidas → agregar combinaciones particulares importantes que el algoritmo no haya cubierto.

**Ejemplo (cuentas bancarias):** Operación (Retiro/Depósito) × Tipo de cuenta (Corriente/Ahorro) × Moneda (Colones/Dólares) → combinación total = 2×2×2 = 8 casos; por pares alcanza con 4 casos para cubrir todos los pares al menos una vez.

**Caso real de configuración de pruebas web:** 4 SO × 5 navegadores × 3 resoluciones × 3 configuraciones de color × 5 idiomas = 900 combinaciones totales → con pairwise se resuelve en ~25 casos (herramienta de referencia: [pairwise.yuuniworks.com](https://pairwise.yuuniworks.com/)).

**Cuidado con combinaciones inválidas** (ej. "Internet Explorer no corre en Linux"): no se debe simplemente borrar el caso de prueba que la contiene, porque ese caso probablemente cubre otros pares válidos — hay que reemplazarlo por casos equivalentes que preserven esos pares sin la combinación imposible.

**Ventajas:** fácil de usar, asegura cobertura de todos los pares, no implica trabajo extra una vez armada la tabla.
**Desventajas:** puede no generar alguna combinación importante o frecuente; variables dependientes pueden producir combinaciones inválidas que hay que tratar a mano.

## 4. Tablas de decisión

Método para construir casos de prueba **sin** usar la estructura interna del programa: se listan condiciones y acciones en una matriz, donde cada columna es una combinación única de valores de las condiciones ("causas") y las filas de abajo ("efectos") marcan qué acción se dispara.

**Elementos:** condiciones (dominio de entrada), acciones/salidas, entradas válidas por condición, reglas (qué acción corresponde a cada combinación de entrada).

**Notación de entradas:** `S` = la condición debe cumplirse, `N` = no debe cumplirse, `-` = indiferente (no importa).

**Pasos:** enumerar todas las causas → calcular el número de combinaciones posibles (si todas las causas son Y/N: `2^n`; si alguna tiene más valores, se multiplican las cardinalidades) → llenar las columnas con todas las combinaciones → reducir combinaciones redundantes/imposibles → verificar que cada variable se pruebe al menos una vez en Y y en N → añadir los efectos correspondientes a cada columna.

**Ejemplo trabajado — facturación con descuento:** causas `Cliente de la empresa`, `Plazo de pago ≤ 30 días`, `Cantidad solicitada ≤ stock` (2³ = 8 combinaciones) → efectos: facturar con/sin descuento, enviar mercadería completa o solo el stock disponible, dejar pendiente el resto.

**Ejemplo de tabla más compleja (multa de tránsito):** combina condiciones booleanas (licencia OK, orden de arresto, registro OK, vehículo OK) con un rango numérico (exceso de velocidad, con sus propios tramos) — muestra que valores límite y tablas de decisión se combinan cuando hay reglas excluyentes entre sí.

## 5. Diagrama de estados (máquina de estados)

Útil para documentar el diseño y capturar requerimientos de: protocolos de comunicación, sistemas de control de movimiento (robots, aviones, autos), software de control de dispositivos, ciclo de vida de entidades y ciclos de negocio.

Una máquina de estados se compone de **estados**, **transiciones**, **eventos** y **acciones**; describe el ciclo de vida de un sistema u objeto, documentando qué eventos procesa el sistema y cómo responde a cada uno (`Estado A --evento/acción--> Estado B`).

**Ejemplo trabajado — reserva de un ticket:**

1. **Identificar estados:** Made (hecha) → Paid (pagada) → Ticketed (impresa) → Used (usada); más los estados terminales Cancelled NonPay (cancelada por vencimiento del temporizador de pago) y Cancelled ByCust (cancelada por el cliente, en cualquier punto antes de usarla).
2. **Tabla de transiciones** (estado actual, evento, acción, próximo estado) — se completa fila por fila para **cada** combinación de estado × evento posible, incluyendo las que no cambian de estado (ej. dar información de nuevo estando en `Made` se queda en `Made`).
3. **Casos de prueba:** se seleccionan los caminos que ejercitan cada transición relevante del diagrama (no jugadas aleatorias sino cubriendo cada flecha del grafo al menos una vez).

**Cálculo de casos de prueba:** número de nodos × número de flechas, menos las transiciones que no aplican, más 1 para cubrir el camino "todo válido" (en el ejemplo del ticket: 6 estados × 8 eventos = 48 transiciones posibles; descontando las 8 no aplicables da 40 casos + 1 = 41 casos de prueba).

## Ejercicios propuestos en clase

- Definir clases de equivalencia para: contribución de membresía de TV ($0.01-$99,999.99 + estatus regular/estudiante/retirado) y retiro de cajero automático (múltiplo de $5.00, ≤ $200.00).
- Valores límite para: peso de usuario de gimnasio (58.5-61.5 kg), condición de bucle `while (z>=150.0 && z<225.6)`, y un registro de empleado con número (3 dígitos, sin el 000), nombre (10 caracteres), meses trabajados (3 dígitos, incluye el 000) y campo directivo (`+`/`-`).
- Tabla de decisión para descuentos acumulables por tipo de tarjeta (oro 15%, club 5%, modalidad joven +5%).
- Diagrama de estados para una lavadora (enjuagado/lavando/secando, con apertura de puerta que no cambia el estado) y para la gestión de mesas de un restaurante (libre → reservada → ocupada → pidiendo → en espera de comida → servidos → esperando cuenta → pagando).
