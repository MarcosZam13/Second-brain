---
curso: QA
tema: "Repaso — Quiz Caja Negra (Semana 6: Técnicas de diseño de pruebas)"
fecha: 2026-09-15
tipo: repaso
repaso_de:
  - "[[Cursos/QA/apuntes/caja-negra-semana-6]]"
entrega: 2026-09-16
tags: [caja-negra, clases-equivalentes, valores-limite, combinacion-por-pares, tablas-de-decision, diagrama-de-estados, tecnicas-de-diseno-de-pruebas, repaso]
---

# Repaso — Quiz Caja Negra, Semana 6 (QA)

Ver también: [[Cursos/QA/apuntes/caja-negra-semana-6|Apunte completo — Caja Negra (Semana 6)]] · [[Cursos/QA/temario]] · [[Cursos/QA/entregas]]

Repaso para el quiz probable del 2026-09-16 (miércoles, siguiendo el patrón de quizzes semanales). Versión densa para memorizar rápido, más autoevaluación. Respuestas ocultas con `<details>` — clic para revelar.

## 1. Ubicación y definición

```
Pruebas
├── Estáticas (Análisis estático, Revisión)
└── Dinámicas
    ├── Caja Blanca
    ├── Caja Negra (Funcional / No funcional)
    └── Basadas en la experiencia
```

**Caja negra:** verifica funcionalidades **sin** referencia a la estructura del código interno, rutas internas ni implementación.

**Las 5 técnicas, en orden (cada una refina o se apoya en la anterior):**

```
Clases equivalentes → Valores límite → Combinación por pares → Tablas de decisión → Diagrama de estados
```

## 2. Clases equivalentes (partición de equivalencia)

Grupo de datos con comportamiento análogo: probar un representante de la clase equivale a probar cualquier otro miembro. **Entradas válidas** → valor esperado. **Entradas no válidas** → valor inesperado/excepción.

**Pasos:** identificar variables y valores posibles → identificar clases de equivalencia → seleccionar representantes → seleccionar casos de prueba.

| Tipo de condición | Regla | Ejemplo |
|---|---|---|
| Rango de valores | 1 válida + 2 inválidas | contador 1-999 → válida 1-999; inválidas `<1`, `>999` |
| Valor o número de valores | 1 válida + 2 inválidas | 1-6 propietarios → inválidas: 0, más de 6 |
| Condición lógica ("debe ser") | 1 válida + 1 inválida | primer carácter debe ser letra |

**Regla práctica:** no combinar clases inválidas entre sí en el mismo caso — cada inválida se prueba aislada, para saber exactamente qué la disparó.

## 3. Valores límite (Boundary Value Analysis)

Refinamiento de clases equivalentes: los defectos ocurren justo en/sobre/debajo de los extremos. Solo aplica si los elementos están **ordenados**.

**Los 7 valores por cada límite:** Min−, Min, Min+, Nom, Max−, Max, Max+.

**Ejemplo clave (fecha, rango de año 1812-2013):** permutación completa 7×7×7 = 343 → clases de equivalencia lo reduce a 7 → valores límite lo deja en 8.

**Ventajas:** reduce casos necesarios; alta eficacia empírica.
**Desventajas:** no prueba todas las entradas posibles, no cubre dependencias entre variables, no se puede medir % de cobertura.

## 4. Combinación por pares (pairwise / all-pairs)

Probar todas las combinaciones es casi siempre inviable (10 variables × 10 valores = 10,000,000,000 casos). Pairwise genera casos donde **cada par de valores de variables distintas** aparece al menos una vez (no todas las combinaciones, solo toda combinación de a dos).

**Pasos:** identificar variables → identificar dominios/valores (ej. con clases de equivalencia) → generar combinaciones de a pares → analizar combinaciones inválidas → agregar combinaciones particulares importantes no cubiertas.

**Ejemplo (cuentas bancarias):** Operación × Tipo de cuenta × Moneda = 2×2×2 = 8 casos totales → pairwise lo resuelve en 4 casos.

**Caso real (web):** 4 SO × 5 navegadores × 3 resoluciones × 3 colores × 5 idiomas = 900 combinaciones → pairwise ≈ 25 casos. Herramienta: pairwise.yuuniworks.com.

**Cuidado:** ante una combinación inválida (ej. "IE no corre en Linux") no se borra el caso sin más — hay que reemplazarlo por uno equivalente que preserve los demás pares que cubría.

**Ventajas:** fácil, asegura cobertura de pares, sin trabajo extra tras armar la tabla.
**Desventajas:** puede no generar alguna combinación importante/frecuente; variables dependientes generan combinaciones inválidas a tratar a mano.

## 5. Tablas de decisión

Construye casos de prueba sin usar la estructura interna: condiciones ("causas") y acciones ("efectos") en una matriz; cada columna = una combinación única de valores de las condiciones.

**Notación:** `S` = debe cumplirse, `N` = no debe cumplirse, `-` = indiferente.

**Pasos:** enumerar causas → calcular combinaciones posibles (`2^n` si todo es Y/N; multiplicar cardinalidades si hay más valores) → llenar columnas con todas las combinaciones → reducir redundantes/imposibles → verificar que cada variable se pruebe en Y y en N al menos una vez → añadir efectos a cada columna.

**Ejemplo (facturación con descuento):** 3 causas booleanas (cliente empresa, plazo ≤30 días, cantidad ≤ stock) → 2³ = 8 combinaciones → efectos: facturar con/sin descuento, enviar completo o parcial.

**Nota:** valores límite y tablas de decisión se combinan cuando hay condiciones numéricas por tramos junto a condiciones booleanas (ej. multa de tránsito).

## 6. Diagrama de estados (máquina de estados)

Útil para: protocolos de comunicación, control de movimiento, control de dispositivos, ciclo de vida de entidades, ciclos de negocio.

**Componentes:** estados, transiciones, eventos, acciones. `Estado A --evento/acción--> Estado B`.

**Pasos (ejemplo ticket):**
1. Identificar estados: Made → Paid → Ticketed → Used (+ terminales Cancelled NonPay, Cancelled ByCust).
2. Tabla de transiciones (estado actual, evento, acción, próximo estado) — para **cada** combinación estado×evento, incluidas las que no cambian de estado.
3. Casos de prueba: cubrir cada flecha del grafo al menos una vez (no jugadas aleatorias).

**Cálculo de casos:** nodos × flechas − transiciones no aplicables + 1 (camino "todo válido"). Ejemplo ticket: 6×8 = 48 − 8 no aplicables + 1 = **41 casos**.

## 7. Autoevaluación — suite de casos de prueba

**Automatizados** (opción múltiple / respuesta corta):

<details>
<summary><strong>TC-01</strong> — ¿Cuáles son las 5 técnicas de diseño de caja negra, en el orden en que se ven en clase?</summary>

Clases equivalentes → Valores límite → Combinación por pares → Tablas de decisión → Diagrama de estados.
</details>

<details>
<summary><strong>TC-02</strong> — En clases equivalentes, ¿cuántas clases válidas e inválidas corresponden a un "rango de valores"?</summary>

1 clase válida + 2 clases inválidas (una por debajo del rango, otra por encima).
</details>

<details>
<summary><strong>TC-03</strong> — ¿Por qué no se deben combinar dos clases inválidas en el mismo caso de prueba?</summary>

Porque si el caso falla no se sabría cuál de las dos clases lo disparó; cada inválida se prueba aislada.
</details>

<details>
<summary><strong>TC-04</strong> — Nombrá los 7 valores que se consideran por cada límite en Boundary Value Analysis.</summary>

Min−, Min, Min+, Nom, Max−, Max, Max+.
</details>

<details>
<summary><strong>TC-05</strong> — ¿Qué condición deben cumplir los elementos de una clase para poder aplicar valores límite?</summary>

Deben estar ordenados (valores numéricos, tabla ASCII, etc.).
</details>

<details>
<summary><strong>TC-06</strong> — ¿Qué garantiza (y qué NO garantiza) la técnica de combinación por pares?</summary>

Garantiza que cada par de valores de variables distintas aparezca al menos una vez. NO garantiza cubrir todas las combinaciones posibles de todas las variables juntas.
</details>

<details>
<summary><strong>TC-07</strong> — Ante una combinación inválida generada por pairwise (ej. "IE no corre en Linux"), ¿qué se debe hacer con ese caso de prueba?</summary>

No borrarlo sin más — reemplazarlo por un caso equivalente que preserve los demás pares válidos que cubría, evitando la combinación imposible.
</details>

<details>
<summary><strong>TC-08</strong> — En una tabla de decisión, ¿qué significan las notaciones `S`, `N` y `-`?</summary>

`S` = la condición debe cumplirse, `N` = no debe cumplirse, `-` = indiferente (no importa el valor).
</details>

<details>
<summary><strong>TC-09</strong> — Si una tabla de decisión tiene 4 causas booleanas (Y/N), ¿cuántas combinaciones posibles hay antes de reducir?</summary>

2⁴ = 16 combinaciones.
</details>

<details>
<summary><strong>TC-10</strong> — ¿Cuáles son los 4 componentes de una máquina de estados?</summary>

Estados, transiciones, eventos, acciones.
</details>

<details>
<summary><strong>TC-11</strong> — ¿Cuál es la fórmula para calcular el número de casos de prueba a partir de un diagrama de estados?</summary>

(Nodos × flechas) − transiciones no aplicables + 1 (para cubrir el camino "todo válido").
</details>

**Manuales** (recordar y explicar con tus palabras):

<details>
<summary><strong>TC-12</strong> — Explicá con el ejemplo de la fecha (día/mes/año, año 1812-2013) cómo se reduce el número de casos al pasar de permutación completa → clases equivalentes → valores límite.</summary>

Permutación completa combina todos los valores posibles de cada variable entre sí: 7×7×7 = 343 casos. Clases de equivalencia agrupa los valores con comportamiento análogo (uno por clase), bajando a 7 casos. Valores límite se enfoca solo en los bordes relevantes de cada variable, sin explotar todas las combinaciones entre ellos, dejando el total en 8 casos — mucho más manejable y aun así cubriendo los puntos donde más ocurren los defectos.
</details>

<details>
<summary><strong>TC-13</strong> — Explicá el ejemplo de las cuentas bancarias (Operación × Tipo de cuenta × Moneda) y por qué pairwise reduce los casos de 8 a 4.</summary>

Con 3 variables de 2 valores cada una (Retiro/Depósito, Corriente/Ahorro, Colones/Dólares), la combinación total es 2×2×2=8. Pairwise no busca cubrir las 8 combinaciones triples, sino asegurar que cada par de valores (ej. Retiro+Corriente, Corriente+Colones, Retiro+Dólares, etc.) aparezca al menos una vez en algún caso. Como varios pares se pueden cubrir simultáneamente en un mismo caso de 3 variables, basta con 4 casos bien elegidos para que todos los pares queden representados.
</details>

<details>
<summary><strong>TC-14</strong> — Trabajá el ejemplo de facturación con descuento (3 causas: cliente de la empresa, plazo de pago ≤30 días, cantidad ≤ stock) y describí qué efectos dispara cada combinación relevante.</summary>

Con 3 causas booleanas hay 2³=8 combinaciones. Los efectos posibles son: facturar con descuento (si es cliente de la empresa y paga a tiempo) o sin descuento, y enviar la mercadería completa (si hay stock suficiente) o solo el stock disponible dejando el resto pendiente. Cada columna de la tabla combina una causa específica (S/N para cada una) con el efecto que le corresponde; por ejemplo, cliente=S, plazo=S, stock=N dispara "facturar con descuento" + "enviar stock disponible y dejar pendiente el resto".
</details>

<details>
<summary><strong>TC-15</strong> — Con el ejemplo del ticket (Made → Paid → Ticketed → Used, más los estados de cancelación), explicá qué información debe llevar cada fila de la tabla de transiciones y por qué se completan también las transiciones que "no cambian de estado".</summary>

Cada fila lleva: estado actual, evento que ocurre, acción que se ejecuta y estado próximo resultante. Se completan también los casos donde el evento no cambia el estado (ej. pedir información de nuevo estando en "Made" se queda en "Made") porque esas transiciones también son parte del comportamiento válido del sistema y deben quedar documentadas y probadas — omitirlas dejaría un hueco de cobertura en el diagrama.
</details>

<details>
<summary><strong>TC-16</strong> — ¿Por qué se dice que las 5 técnicas de caja negra se ven "en el orden en que una es refinamiento de la anterior"? Dá un ejemplo de esa relación entre dos técnicas consecutivas.</summary>

Porque cada técnica parte de o mejora a la anterior en vez de ser un método aislado. Ejemplo: valores límite es un refinamiento de clases equivalentes — en lugar de probar cualquier representante de la clase, se enfoca específicamente en los bordes de esa clase, porque empíricamente ahí ocurren más defectos. De forma similar, combinación por pares usa las clases/dominios de valores ya identificados con clases equivalentes como insumo para generar las combinaciones.
</details>

<details>
<summary><strong>TC-17</strong> — Nombrá 2 ventajas y 2 desventajas de valores límite, y 2 ventajas y 2 desventajas de combinación por pares.</summary>

**Valores límite** — Ventajas: reduce el número de casos necesarios; alta eficacia empírica (los bordes producen mejores resultados). Desventajas: no prueba todas las entradas posibles; no cubre dependencias entre variables.
**Combinación por pares** — Ventajas: fácil de usar; asegura cobertura de todos los pares sin trabajo extra una vez armada la tabla. Desventajas: puede no generar alguna combinación importante/frecuente; variables dependientes producen combinaciones inválidas que hay que tratar a mano.
</details>
