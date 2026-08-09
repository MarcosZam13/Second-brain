---
curso: Estadistica
tema: Guía Teórico-Práctica — Inferencia Estadística (Unidades 1 y 2)
fecha: 2026-08-07
tipo: apunte
fuente:
  - _fuentes/Estadistica_guia-inferencia-estadistica-unidades1-2_2026-08-07.pdf
  - _fuentes/Estadistica_guia-unidad1-resuelta-semana1_2026-08-07.pdf
tags: [inferencia-estadistica, distribuciones-probabilidad, estimacion-puntual, verosimilitud, intervalos-confianza, pruebas-hipotesis]
---

# Guía Teórico-Práctica — Inferencia Estadística (Unidades 1 y 2)

Ver también: [[Cursos/Estadistica/temario]] · [[Cursos/Estadistica/entregas]]

> Guía del profesor Elvis Mejías Ramírez (MA-3405, II Semestre 2026). Cubre la Unidad 1 (Introducción a la Inferencia Estadística) y la Unidad 2 (Estimación para una Población). El archivo `Estadistica_guia-unidad1-resuelta-semana1_2026-08-07.pdf` es la misma guía de Unidad 1 trabajada en la sesión de Semana 1, con las respuestas propias a los ejercicios de práctica ya resueltas a mano — no se transcriben acá, quedan en esa fuente archivada.

## 1. Introducción a la Inferencia Estadística

### 1.1. Conceptos preliminares

- **Estadística Inferencial** vs. **Descriptiva**: la inferencial estima parámetros, analiza comportamientos y toma decisiones a partir de una muestra; la descriptiva solo organiza/resume/representa datos.
- **Población**: conjunto de datos a estudiar (valores de una misma variable). **Muestra**: subconjunto relacionado con la población. Si muestra = población es un **censo** (exacto); si no, se busca representatividad para minimizar el sesgo.
- **Muestra aleatoria** de tamaño $n$: variables $(X_1, ..., X_n)$ que (1) siguen la misma distribución que $X$ y (2) son mutuamente independientes.
- **Variable**: cualitativa (nominal o jerárquica) o cuantitativa (discreta o continua).

### 1.2. Distribuciones de probabilidad

| Distribución | Notación | Uso | Media | Varianza |
|---|---|---|---|---|
| Binomial | $X \sim B(n,p)$ | número de éxitos en $n$ ensayos independientes | $np$ | $np(1-p)$ |
| Normal | $X \sim N(\mu, \sigma^2)$ | fenómenos continuos (estaturas, pesos, errores) | $\mu$ | $\sigma^2$ |
| Normal estándar | $Z \sim N(0,1)$ | referencia para estandarizar: $z = \frac{X-\mu}{\sigma}$ | 0 | 1 |
| t de Student | $T \sim t_v$ | inferencia sobre la media con muestra pequeña ($n<30$) y $\sigma$ desconocida | 0 (si $v>1$) | $\frac{v}{v-2}$ (si $v>2$) |
| Chi-cuadrado | $X \sim \chi^2_v$ | variabilidad (varianza) de una población | $v$ | $2v$ |

Para $X, Y$ independientes siempre: $E(X \pm Y) = E(X) \pm E(Y)$, $Var(X \pm Y) = Var(X) + Var(Y)$.

**Estadísticos de prueba:**
- t de Student: $T = \dfrac{\bar{X}-\mu}{S/\sqrt{n}} \sim t_{n-1}$, con $v=n-1$ grados de libertad.
- Chi-cuadrado: $\chi^2 = \dfrac{(n-1)S^2}{\sigma_0^2} \sim \chi^2_{n-1}$.

Las tablas de distribución acumulada (binomial, normal estándar, t, chi-cuadrado) están en el PDF fuente — no se reproducen acá.

### 1.3. Estimación puntual y verosimilitud

- **Parámetro** ($\theta$): valor numérico de la población (ej. $\mu$, $p$, $\sigma^2$), generalmente desconocido.
- **Estadístico** ($\hat\Theta$): valor calculado a partir de la muestra (ej. $\bar x$, $\hat p$, $s^2$). Cuando estima un parámetro, se llama **estimador** ($\hat\theta$).

| Medida | Parámetro | Estadístico |
|---|---|---|
| Media | $\mu = \frac{\sum x_i}{N}$ | $\bar x = \frac{\sum x_i}{n}$ |
| Varianza | $\sigma^2 = \frac{\sum(x_i-\mu)^2}{N}$ | $s^2 = \frac{\sum(x_i-\bar x)^2}{n-1}$ |
| Desviación estándar | $\sigma = \sqrt{\cdot}$ | $s = \sqrt{\cdot}$ |
| Proporción | $p = b/N$ | $\hat p = B(M)/n$ |
| Coeficiente de variación | $CV = \sigma/\mu \cdot 100\%$ | $CV = s/\bar x \cdot 100\%$ |

**Insesgadez:** $\hat\Theta$ es insesgado si $E(\hat\theta) = \theta$. $\bar X$, $S^2$ y $\hat P$ son insesgados de $\mu$, $\sigma^2$ y $p$ respectivamente. Entre dos estimadores insesgados del mismo parámetro, es mejor el de **menor varianza**.

Identidades clave para una muestra $M=(X_1,...,X_n)$ de una población con media $\mu$ y varianza $\sigma^2$: $E(X_i)=\mu$, $Var(X_i)=\sigma^2$, $E(X_i^2)=\sigma^2+\mu^2$, $E(\bar X)=\mu$, $Var(\bar X)=\sigma^2/n$, $E(\bar X^2)=\sigma^2/n+\mu^2$, $E(S^2)=\sigma^2$.

**Método de máxima verosimilitud** para un parámetro $a$:
1. Construir $g(a) = f(x_1)f(x_2)f(x_3)\cdots$
2. Calcular y simplificar $\ln[g(a)]$.
3. Derivar $\ln[g(a)]$.
4. Despejar $a$ de $g'(a)=0$.

## 2. Estimación para una Población

### 2.1. Intervalos de confianza

Forma general: $IC = \text{estimador puntual} \pm \text{margen de error}$, con $P(\theta \in I(\hat\Theta)) = 1-\alpha$.

**Media:**

| Caso | IC del $(1-\alpha)100\%$ |
|---|---|
| $\sigma^2$ conocida | $\bar x \pm z_{\alpha/2} \cdot \frac{\sigma}{\sqrt n}$ |
| $\sigma^2$ desconocida | $\bar x \pm t_{\alpha/2,\,n-1} \cdot \frac{s}{\sqrt n}$ |

Tamaño de muestra para radio $\le r$: $n \ge \left(\frac{z_{\alpha/2}\cdot\sigma}{r}\right)^2$. $\bar X$ es normal si $X$ es normal, o si $n\ge 30$ (Teorema del Límite Central; con $\sigma$ desconocida se usa $s$).

**Proporción** ($\hat P = B/n$, $E(\hat P)=p$, $Var(\hat P)=pq/n$):

| Caso | IC del $(1-\alpha)100\%$ |
|---|---|
| Muestras grandes ($n\hat p\ge5$ y $n\hat q\ge5$) | $\hat p \pm z_{\alpha/2}\cdot\sqrt{\hat p\hat q/n}$ |
| Muestras pequeñas | empírico vía binomial: $P(B\le n\hat p \mid p=p_i)=1-\alpha/2$, $P(B<n\hat p \mid p=p_s)=\alpha/2$ |

Tamaño de muestra: $n \ge \left(\frac{z_{\alpha/2}\cdot\sqrt{\hat p\hat q}}{r}\right)^2$.

**Varianza** (requiere $X$ normal, $\chi^2 = \frac{(n-1)S^2}{\sigma^2}\sim\chi^2_{n-1}$):

| Parámetro | IC del $(1-\alpha)100\%$ |
|---|---|
| $\sigma^2$ | $\left]\dfrac{(n-1)S^2}{\chi^2_{1-\alpha/2,\,n-1}},\ \dfrac{(n-1)S^2}{\chi^2_{\alpha/2,\,n-1}}\right[$ |
| $\sigma$ | raíz cuadrada de los extremos anteriores |

### 2.2. Pruebas de hipótesis

- $H_0: \theta=\theta_0$ (afirmación que se somete a prueba). $H_1$: $\theta<\theta_0$, $\theta>\theta_0$ o $\theta\ne\theta_0$ (una o dos colas respectivamente).
- **Error tipo I** ($\alpha$): rechazar $H_0$ siendo verdadera — nivel de significancia. **Error tipo II** ($\beta$): no rechazar $H_0$ siendo falsa (riesgo del consumidor).
- **Coeficiente de confianza** $=1-\alpha$. **Potencia** $=1-\beta$ (probabilidad de rechazar $H_0$ cuando es falsa, para una $H_1'$ específica).

**Procedimiento:** (1) redactar $H_0$/$H_1$ → (2) fijar $\alpha$, distribución de $\hat\Theta$, tipo de prueba y regiones de aceptación/rechazo → (3) determinar valores críticos → (4) calcular el estadístico con los datos muestrales → (5) decidir según la región de rechazo → (6) concluir en términos de $H_1$ (evidencia suficiente o no).

**Media:**

| Caso | Estadístico |
|---|---|
| Normal o $n\ge30$, $\sigma$ conocida | $Z=\frac{\bar X-\mu}{\sigma/\sqrt n}\sim N(0,1)$ |
| Normal, $\sigma$ desconocida | $T=\frac{\bar X-\mu}{S/\sqrt n}\sim t_{n-1}$ |

**Proporción:**

| Caso | Estadístico |
|---|---|
| Muestras grandes ($np_0\ge5$, $nq_0\ge5$) | $Z=\frac{\hat P-p_0}{\sqrt{p_0q_0/n}}\sim N(0,1)$ |
| Muestras pequeñas | $B\sim B(n,p_0)$, probabilidades acumuladas vía binomial |

**Varianza** (población normal): $\chi^2 = \frac{(n-1)S^2}{\sigma_0^2}\sim\chi^2_{n-1}$, valores críticos de la distribución chi-cuadrado.

## Ejercicios de práctica

La guía incluye baterías extensas de ejercicios (resueltos y sin resolver) por cada tema: conceptos preliminares, distribuciones binomial/normal/t/chi-cuadrado, estimación puntual y verosimilitud, e IC/pruebas de hipótesis para media, proporción y varianza. Quedan en el PDF fuente — no se transcriben acá para no duplicar contenido que ya está completo y ordenado en el original.
