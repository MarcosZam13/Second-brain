---
curso: Estadistica
tema: "Repaso — Quiz 1 (Semanas 1-2: introducción a inferencia + IC para una media)"
fecha: 2026-08-18
tipo: repaso
repaso_de: "[[Cursos/Estadistica/apuntes/inferencia-estadistica-guia-unidades1-2]]"
entrega: 2026-08-19
tags: [inferencia-estadistica, distribuciones-probabilidad, estimacion-puntual, verosimilitud, intervalos-confianza, ic-media, repaso]
---

# Repaso — Quiz 1, Semanas 1-2 (Estadística MA-3405)

Ver también: [[Cursos/Estadistica/apuntes/inferencia-estadistica-guia-unidades1-2|Apunte completo]] · [[Cursos/Estadistica/temario]] · [[Cursos/Estadistica/entregas]]

Repaso para el Quiz 1 del 2026-08-19 (6%). Cubre semana 1 (repaso rápido, ya lo dominás) y semana 2 (a fondo, especialmente **IC para una media** — el tema de la segunda clase de semana 2, a la que no pudiste ir). Respuestas ocultas con `<details>` — clic para revelar.

## 1. Semana 1 — repaso rápido (conceptos base)

- **Inferencial vs. descriptiva:** inferencial estima/decide a partir de una muestra; descriptiva solo organiza/resume datos.
- **Muestra aleatoria** de tamaño $n$: $(X_1,...,X_n)$ misma distribución que $X$ + independientes entre sí.
- **Parámetro** ($\theta$, ej. $\mu$, $p$, $\sigma^2$) vs. **estadístico** ($\hat\Theta$, ej. $\bar x$, $\hat p$, $s^2$) — el estadístico que estima un parámetro es un **estimador**.
- **Insesgadez:** $E(\hat\theta)=\theta$. $\bar X$, $S^2$, $\hat P$ son insesgados. Entre dos insesgados, gana el de **menor varianza**.

| Distribución | Notación | Cuándo se usa |
|---|---|---|
| Binomial | $B(n,p)$ | # de éxitos en $n$ ensayos independientes |
| Normal | $N(\mu,\sigma^2)$ | fenómenos continuos |
| t de Student | $t_v$ | media, muestra chica ($n<30$), $\sigma$ desconocida |
| Chi-cuadrado | $\chi^2_v$ | varianza |

**Método de máxima verosimilitud (MLE)** — 4 pasos, siempre igual:
1. $g(\theta) = f(x_1)\cdot f(x_2)\cdots f(x_n)$ (producto de la densidad evaluada en cada dato).
2. $\ln[g(\theta)]$ y simplificar (usar propiedades de logaritmos para bajar exponentes y separar productos en sumas).
3. Derivar $\ln[g(\theta)]$ respecto a $\theta$.
4. Igualar a 0 y despejar $\theta$. (La otra raíz, $g(\theta)=0$, se descarta siempre — no aporta información).

**Truco para no perderse en el álgebra:** agrupá primero todo lo que no depende de $\theta$ (constantes, combinatorias) en un solo bloque — al aplicar $\ln$ ese bloque se vuelve una constante aditiva que desaparece al derivar. Lo único que sobrevive a la derivada son los términos con $\theta$.

## 2. Semana 2 (clase 1) — Estimación para una población: intro

- Un **intervalo de confianza** da un *rango* de valores para $\theta$, no un solo número: $IC = \text{estimador puntual} \pm \text{margen de error}$.
- $I(\hat\Theta) = ]\hat\Theta_{inf}, \hat\Theta_{sup}[$ es un IC del $(1-\alpha)100\%$ si $P(\theta \in I(\hat\Theta)) = 1-\alpha$, repartiendo $\alpha/2$ en cada cola.
- **Centro** del IC $= \dfrac{\theta_{inf}+\theta_{sup}}{2}$ (es el estimador puntual). **Radio** $= \dfrac{\theta_{sup}-\theta_{inf}}{2}$ (el margen de error).
- Este tema se construye sobre tres parámetros: media $\mu$, proporción $p$, varianza $\sigma^2$ — pero **la única que se practicó a fondo en semana 2 fue la media** (ver sección 3). Proporción y varianza probablemente son de semanas siguientes — si el quiz las incluye, avisame para armar ese repaso aparte.

## 3. Semana 2 (clase 2, la que falta) — IC para una media ⚠️ foco del repaso

Esta es la sección para estudiar con más cuidado — no fuiste a esta clase.

### 3.1. Las dos fórmulas

| Caso | Condición | Fórmula del IC del $(1-\alpha)100\%$ |
|---|---|---|
| $\sigma^2$ **conocida** | se da la varianza/desviación poblacional | $\bar x \pm z_{\alpha/2} \cdot \dfrac{\sigma}{\sqrt n}$ |
| $\sigma^2$ **desconocida** | solo se tiene $s$ de la muestra | $\bar x \pm t_{\alpha/2,\,n-1} \cdot \dfrac{s}{\sqrt n}$ |

**Cómo decidir cuál usar, en orden:**
1. ¿El enunciado te da $\sigma$ (poblacional) directamente, o solo $s$ (de la muestra)? Si da $\sigma$ → normal ($z$). Si solo da $s$ → t de Student.
2. Si usás $t$: los grados de libertad son $v = n-1$, y buscás $t_{\alpha/2, n-1}$ en la tabla t.
3. **Excepción:** si $n \ge 30$ (Teorema del Límite Central), $\bar X$ ya es normal aunque $X$ no lo sea, y si no conocés $\sigma$ podés usar $s$ en su lugar **dentro de la fórmula de $z$** (no la de $t$) — es la única situación donde se mezcla "no conozco $\sigma$" con "uso $z$".
4. Si $X$ ya es normal (el enunciado lo dice explícito, "suponga que $X\sim N$"), la fórmula de $t$ vale para cualquier $n$, no hace falta $n\ge30$.

### 3.2. Tamaño de muestra necesario

Para que el radio del IC sea $\le r$:
$$n \ge \left(\frac{z_{\alpha/2}\cdot\sigma}{r}\right)^2$$
Siempre redondear **hacia arriba** (un $n$ más chico no garantiza el radio pedido).

### 3.3. Cómo se responde el "¿es aceptable la afirmación?"

Patrón que se repite en casi todos los ejercicios de la guía (frijoles de 2kg, estatura ideal de 105cm, rendimiento de 43km/galón, tiempo saludable de bañarse ≥15min):

1. Calculás el IC para $\mu$.
2. Ubicás el valor que afirma el enunciado (2kg, 105cm, 43km/galón, 15min...).
3. **¿Ese valor cae dentro del IC?** Si sí → la afirmación es consistente con los datos, no hay evidencia para rechazarla. Si no → los datos no respaldan la afirmación.
4. Ojo con afirmaciones de una sola dirección ("al menos 11 minutos", "por lo menos 43 km/galón"): ahí no solo importa si el valor cae en el IC, sino si **todo el IC** queda del lado que la afirmación pide (ej. si el IC completo es mayor a 11, hay más respaldo que si el valor 11 apenas roza el borde inferior).

### 3.4. Ejercicios trabajados en la guía (semana 2, resueltos a mano)

Quedan completos en la fuente archivada `_fuentes/Estadistica_guia-unidad2-resuelta-semana2_2026-08-18.pdf` (14 ejercicios, problemas 1-14 de la sección 2.1.1) — no se transcriben acá para no duplicar, pero valen la pena repasar en el PDF porque cubren variantes útiles: despejar el tamaño de muestra, despejar el extremo faltante de un IC dado el otro extremo, despejar $\bar x$ o $s$ a partir de un extremo conocido, y despejar el nivel de confianza a partir de un IC completo (problemas 10-14 — son el tipo "trabajar la fórmula al revés", que suele salir en quiz porque exige entender la fórmula en vez de solo aplicarla mecánicamente).

## 4. Autoevaluación

**Preguntas rápidas (semana 1, repaso):**

<details>
<summary><strong>P1</strong> — En el método de máxima verosimilitud, ¿por qué se usa $\ln[g(\theta)]$ en vez de derivar $g(\theta)$ directamente?</summary>

Porque $g(\theta)$ es un producto de $n$ términos (difícil de derivar) y el logaritmo convierte productos en sumas — $\ln[g(\theta)]$ es mucho más fácil de derivar, y como $\ln$ es creciente, el máximo se alcanza en el mismo punto.
</details>

<details>
<summary><strong>P2</strong> — ¿Qué significa que un estimador sea insesgado?</summary>

Que su valor esperado es igual al parámetro que estima: $E(\hat\theta) = \theta$. No significa que un solo cálculo dé exactamente el valor real, sino que en promedio (sobre muchas muestras) no hay sesgo sistemático hacia arriba o abajo.
</details>

**Casos de IC para la media (semana 2 — el foco):**

<details>
<summary><strong>P3</strong> — Un enunciado te da la desviación estándar poblacional $\sigma$. ¿Usás $z$ o $t$?</summary>

$z$ (normal), con $\bar x \pm z_{\alpha/2}\cdot\sigma/\sqrt n$ — siempre que se conoce $\sigma$ poblacional, no importa el tamaño de $n$ (asumiendo $X$ normal o $n\ge30$).
</details>

<details>
<summary><strong>P4</strong> — Tenés $n=15$, no te dan $\sigma$ sino $s$ calculada de la muestra, y el enunciado dice "suponga que $X\sim N$". ¿Qué fórmula usás?</summary>

$t$ de Student: $\bar x \pm t_{\alpha/2,\,n-1}\cdot s/\sqrt n$, con $v=n-1=14$ grados de libertad. Como $X$ ya es normal por enunciado, no hace falta que $n\ge30$.
</details>

<details>
<summary><strong>P5</strong> — ¿Qué cambia en la fórmula si en vez de $n=15$ tuvieras $n=40$ y tampoco te dan $\sigma$?</summary>

Con $n\ge30$ aplica el Teorema del Límite Central: $\bar X$ ya es normal sin necesidad de que $X$ lo sea, y ahora se usa $s$ dentro de la fórmula de **$z$** (no la de $t$): $\bar x \pm z_{\alpha/2}\cdot s/\sqrt n$.
</details>

<details>
<summary><strong>P6</strong> — Un IC del 95% para $\mu$ da $]96.05, 103.14[$ y la afirmación es que $\mu=105$. ¿Qué concluís?</summary>

Que 105 no cae dentro del intervalo $]96.05, 103.14[$, así que los datos no respaldan que el promedio real sea 105 — hay evidencia de que es menor.
</details>

<details>
<summary><strong>P7</strong> — Si un intervalo de confianza del 90% para el radio debe ser $\le r$, ¿la fórmula del tamaño de muestra da un mínimo o un máximo de $n$?</summary>

Un mínimo: $n \ge (z_{\alpha/2}\cdot\sigma / r)^2$. Siempre se redondea hacia arriba, porque un $n$ menor al calculado no garantiza que el radio quede dentro de lo pedido.
</details>

<details>
<summary><strong>P8</strong> — ¿Qué representa el "centro" y qué representa el "radio" de un IC, en términos de lo que ya calculaste con la fórmula $\bar x \pm z_{\alpha/2}\cdot\sigma/\sqrt n$?</summary>

El centro es $\bar x$ (el estimador puntual, siempre el punto medio del intervalo). El radio es el margen de error, $z_{\alpha/2}\cdot\sigma/\sqrt n$ — la mitad del ancho total del intervalo.
</details>
