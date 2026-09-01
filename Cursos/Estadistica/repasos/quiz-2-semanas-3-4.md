---
curso: Estadistica
tema: "Repaso — Quiz 2 (Semanas 3-4: IC para proporción y varianza + Pruebas de hipótesis)"
fecha: 2026-09-01
tipo: repaso
repaso_de: "[[Cursos/Estadistica/apuntes/inferencia-estadistica-guia-unidades1-2]]"
entrega: 2026-09-03
tags: [intervalos-confianza, ic-proporcion, ic-varianza, pruebas-hipotesis, hipotesis-nula, hipotesis-alternativa, error-tipo-i, error-tipo-ii, potencia, valor-critico, repaso]
---

# Repaso — Quiz 2, Semanas 3-4 (Estadística MA-3405)

Ver también: [[Cursos/Estadistica/apuntes/inferencia-estadistica-guia-unidades1-2|Apunte completo]] · [[Cursos/Estadistica/repasos/quiz-1-semanas-1-2|Repaso Quiz 1 (semanas 1-2)]] · [[Cursos/Estadistica/temario]] · [[Cursos/Estadistica/entregas]]

Repaso para el Quiz 2 del **jueves 2026-09-03** (6%). Cubre semana 3 (IC para una proporción y para una varianza) y semana 4 (pruebas de hipótesis para media, proporción y varianza). Se asume dominado el contenido de semana 1-2 (ver el repaso del Quiz 1) — acá el foco es lo nuevo. Respuestas ocultas con `<details>` — clic para revelar.

## 1. IC para una proporción (Semana 3)

$\hat P = B/n$ estima $p$, con $E(\hat P)=p$ y $Var(\hat P) = pq/n$ ($q=1-p$).

**Cómo decidir el caso, en orden:**
1. Calculá $n\hat p$ y $n\hat q$ (con $\hat p = B/n$).
2. Si **ambos $\ge 5$** → muestra grande, distribución normal: $\hat p \pm z_{\alpha/2}\cdot\sqrt{\hat p\hat q/n}$.
3. Si **alguno $<5$** → muestra pequeña, hay que buscar $p_i$ y $p_s$ empíricamente en la distribución binomial: $P(B\le n\hat p \mid p=p_i) = 1-\alpha/2$ y $P(B<n\hat p \mid p=p_s) = \alpha/2$.

**Tamaño de muestra** para radio $\le r$: $n \ge \left(\dfrac{z_{\alpha/2}\cdot\sqrt{\hat p\hat q}}{r}\right)^2$, siempre redondeando hacia arriba.

**Truco clave:** si el enunciado NO da ningún $\hat p$ previo ("sin importar el verdadero valor de p"), usá $\hat p=\hat q=0.5$ — es el valor que maximiza $\hat p \hat q$, así el $n$ resultante garantiza el radio pedido sin importar el $p$ real. Si sí hay un $\hat p$ observado (de una muestra piloto o de los mismos datos), usá ese valor en vez de 0.5 — da un $n$ más chico y específico.

**"Trabajar la fórmula al revés"** (muy probable en el quiz): dado un IC completo, encontrar $\hat p$ (el centro del intervalo), $n$, o el nivel de confianza usado — siempre partiendo de que centro = $\hat p$ y radio = $z_{\alpha/2}\cdot\sqrt{\hat p\hat q/n}$.

## 2. IC para una varianza (Semana 3)

Requiere que $X$ siga una distribución **normal**. Estadístico: $\chi^2 = \dfrac{(n-1)S^2}{\sigma^2} \sim \chi^2_{n-1}$.

| Parámetro | IC del $(1-\alpha)100\%$ |
|---|---|
| $\sigma^2$ | $\left]\dfrac{(n-1)S^2}{\chi^2_{1-\alpha/2,\,n-1}},\ \dfrac{(n-1)S^2}{\chi^2_{\alpha/2,\,n-1}}\right[$ |
| $\sigma$ | raíz cuadrada de ambos extremos del IC de $\sigma^2$ |

**Ojo con la asimetría:** a diferencia del IC de la media/proporción (simétrico, $\pm$ margen), el IC de la varianza usa el $\chi^2$ de cola **superior** ($1-\alpha/2$) para el extremo **inferior**, y el $\chi^2$ de cola **inferior** ($\alpha/2$) para el extremo **superior** — es fácil invertirlos por error.

**Patrón "¿es aceptable la afirmación?"** — igual que en semana 2 con la media: calculás el IC, ubicás el valor afirmado, y ves si cae dentro. Ojo con afirmaciones de una sola dirección ("varían demasiado", "superior a X") — ahí importa de qué lado del IC completo queda el valor, no solo si roza el borde.

**"Al revés"** — dado un extremo del IC, hallar el otro o $s^2$; dado el IC completo, hallar el nivel de confianza usado (se despeja el $\chi^2$ correspondiente y se busca en tabla el $\alpha$ asociado).

## 3. Pruebas de hipótesis — conceptos generales (Semana 4)

- **$H_0: \theta = \theta_0$** — la afirmación que se somete a prueba, válida mientras no haya evidencia suficiente para rechazarla.
- **$H_1$** — lo que se acepta si se rechaza $H_0$: $\theta<\theta_0$, $\theta>\theta_0$ (una cola) o $\theta\ne\theta_0$ (dos colas).

**Cómo identificar $H_0$/$H_1$ a partir de un enunciado:** la afirmación que se quiere **probar/demostrar** normalmente es $H_1$ (lo que el investigador sospecha); lo que se asume cierto por defecto ("la máquina está bien ajustada", "el proceso está bajo control") es $H_0$. Frases como "por lo menos", "al menos", "no más de", "no superior a" fijan la dirección de la desigualdad en $H_0$ (con $\ge$ o $\le$) y por lo tanto la cola de $H_1$.

| Elemento | Definición |
|---|---|
| Región de aceptación | Valores de $\hat\Theta$ razonables si $H_0$ es verdadera — no se rechaza $H_0$ |
| Región de rechazo | Valores de $\hat\Theta$ poco probables si $H_0$ es verdadera — se rechaza $H_0$ |
| Valor crítico ($\theta_c$) | Separa ambas regiones; se determina con $\alpha$ y el tipo de prueba |

**Errores:**

| Error | Cuándo ocurre | Probabilidad | Se calcula con |
|---|---|---|---|
| Tipo I | Rechazar $H_0$ siendo verdadera | $\alpha$ (nivel de significancia) | $\theta = \theta_0$ |
| Tipo II | No rechazar $H_0$ siendo falsa | $\beta$ (riesgo del consumidor) | $\theta = \theta_1$ de una $H_1'$ específica |

**Coeficiente de confianza** $=1-\alpha$. **Potencia** $=1-\beta$ (probabilidad de rechazar $H_0$ cuando es falsa, para una $H_1'$ dada).

## 4. Procedimiento — dos enfoques

**Enfoque clásico (regiones):**
1. Redactar $H_0$/$H_1$.
2. Fijar $\alpha$, distribución de $\hat\Theta$, tipo de prueba (1 o 2 colas), regiones de aceptación/rechazo.
3. Determinar el valor crítico $\theta_c$ (usando $\alpha$).
4. Calcular el $\hat\theta$ observado con los datos muestrales.
5. Decisión: si $\hat\theta \in$ región de rechazo → se rechaza $H_0$; si no, no se rechaza.
6. Conclusión en términos de $H_1$ (hay/no hay evidencia suficiente).

**Enfoque de valor P:**
1. Redactar $H_0$/$H_1$.
2. Calcular el valor observado $\hat\theta$.
3. Calcular el valor P (menor $\alpha$ con el que se rechazaría, dado lo observado).
4. Decisión: si $P \le \alpha$ → se rechaza $H_0$ (si no se da $\alpha$, usar 0.05). Si $P>\alpha$ → no se rechaza.
5. Conclusión igual que el enfoque clásico.

## 5. Estadísticos de prueba por parámetro

**Media:**

| Caso | Estadístico |
|---|---|
| Normal o $n\ge30$, $\sigma$ conocida | $Z = \dfrac{\bar X - \mu_0}{\sigma/\sqrt n} \sim N(0,1)$ |
| Normal, $\sigma$ desconocida (se usa $s$) | $T = \dfrac{\bar X - \mu_0}{S/\sqrt n} \sim t_{n-1}$ |

**Proporción** (muestras grandes, $np_0\ge5$ y $nq_0\ge5$): $Z = \dfrac{\hat P - p_0}{\sqrt{p_0q_0/n}} \sim N(0,1)$.

**Varianza** (población normal): $\chi^2 = \dfrac{(n-1)S^2}{\sigma_0^2} \sim \chi^2_{n-1}$.

**Patrón de ejercicio típico (visto 8 veces en semana 4, todos de media):** te dan $n$, $\bar x$, $s$ (o $\sigma$) y una afirmación → planteás $H_0$/$H_1$ → despejás $\mu_c$ de la ecuación $\alpha = P(\bar X \gtrless \mu_c \mid \mu=\mu_0)$ → comparás $\bar x$ contra $\mu_c$ (o el estadístico contra el valor crítico de tabla) → concluís si hay evidencia a favor de $H_1$ o no.

**Variante "al revés":** te dan $\mu_c$ (o un extremo de la región) y pedís el $\alpha$ usado — se despeja el estadístico estandarizado y se busca en tabla.

**Variante potencia:** dado un $\mu_1$ específico (el valor "real" bajo $H_1'$), calculás $\beta = P(\bar X \in \text{región de aceptación} \mid \mu=\mu_1)$ y la potencia es $1-\beta$.

## 6. Autoevaluación

**Preguntas rápidas — IC proporción y varianza (semana 3):**

<details>
<summary><strong>P1</strong> — En una muestra de 50 personas, 4 tienen cierta condición. ¿Se usa el caso de muestra grande o pequeña para el IC de la proporción, y por qué?</summary>

Muestra pequeña: $n\hat p = 50\times0.08 = 4 < 5$, así que no se cumple la condición $n\hat p\ge5$ y $n\hat q\ge5$ — hay que buscar $p_i$ y $p_s$ empíricamente en la binomial en vez de usar la fórmula normal.
</details>

<details>
<summary><strong>P2</strong> — Si un enunciado pide el tamaño de muestra necesario "sin importar el verdadero valor de p", ¿qué valores de $\hat p$ y $\hat q$ se usan?</summary>

$\hat p = \hat q = 0.5$ — es el valor que maximiza $\hat p\hat q$, garantizando el radio pedido sin importar cuál sea el $p$ real.
</details>

<details>
<summary><strong>P3</strong> — ¿Qué distribución debe seguir $X$ para poder construir un IC para $\sigma^2$ o $\sigma$?</summary>

Distribución normal — es un requisito, a diferencia del IC para la media o proporción que puede apoyarse en el Teorema del Límite Central con $n\ge30$.
</details>

<details>
<summary><strong>P4</strong> — En la fórmula del IC para $\sigma^2$, ¿qué percentil de $\chi^2$ va en el extremo inferior del intervalo y cuál en el superior?</summary>

El extremo inferior usa $\chi^2_{1-\alpha/2,\,n-1}$ (cola superior de la tabla) y el extremo superior usa $\chi^2_{\alpha/2,\,n-1}$ (cola inferior) — están invertidos respecto a lo que uno esperaría por intuición, por eso es el error más común.
</details>

**Preguntas rápidas — pruebas de hipótesis (semana 4):**

<details>
<summary><strong>P5</strong> — Un gerente afirma que un producto tiene, en promedio, "al menos 3 litros". ¿Cómo se plantean $H_0$ y $H_1$?</summary>

$H_0: \mu = 3$ (equivalente a $\mu\ge3$) y $H_1: \mu < 3$ — la afirmación fija el límite inferior como el valor que se asume cierto por defecto, y la prueba busca evidencia de que en realidad es menor.
</details>

<details>
<summary><strong>P6</strong> — ¿Cuál es la diferencia entre el error tipo I y el error tipo II?</summary>

Tipo I ($\alpha$): rechazar $H_0$ cuando en realidad es verdadera. Tipo II ($\beta$): no rechazar $H_0$ cuando en realidad es falsa. El primero se calcula asumiendo $\theta=\theta_0$; el segundo asumiendo un valor específico $\theta=\theta_1$ de $H_1'$.
</details>

<details>
<summary><strong>P7</strong> — ¿Qué representa la potencia de una prueba y cómo se relaciona con $\beta$?</summary>

La potencia ($1-\beta$) es la probabilidad de rechazar correctamente $H_0$ cuando es falsa, para una hipótesis alternativa específica $H_1'$ — es el complemento del error tipo II.
</details>

<details>
<summary><strong>P8</strong> — Con $\sigma$ desconocida y una muestra de $n=25$ de una población normal, ¿qué estadístico se usa para probar una hipótesis sobre la media?</summary>

$T = \dfrac{\bar X - \mu_0}{S/\sqrt n} \sim t_{n-1}$, con $v=24$ grados de libertad (t de Student, porque $\sigma$ es desconocida y se usa $s$).
</details>

<details>
<summary><strong>P9</strong> — En el enfoque de valor P, si no se especifica un nivel de significancia $\alpha$ en el enunciado, ¿qué valor se usa por defecto?</summary>

$\alpha = 0.05$.
</details>

<details>
<summary><strong>P10</strong> — Un cliente sospecha que la batería de una laptop dura menos de las 3 horas indicadas. Después de la prueba, se rechaza $H_0$. ¿Qué se concluye?</summary>

Que existe evidencia estadística suficiente a favor de $H_1$ — en este caso, evidencia de que la duración promedio real es menor a 3 horas, respaldando la sospecha del cliente.
</details>

**Casos completos (recordar y explicar):**

<details>
<summary><strong>P11</strong> — Explicá paso a paso cómo se calcula un valor crítico $\mu_c$ en el enfoque clásico, usando el ejemplo del recorrido de empleados: $n=50$, $\bar x=9.1$, $s=5$, $H_0:\mu=9$ ($\le$), $H_1:\mu>9$, $\alpha=0.05$.</summary>

Se plantea $\alpha = P(\bar X > \mu_c \mid \mu=9)$, se estandariza con $Z=\frac{\mu_c-9}{5/\sqrt{50}}$, se iguala a $0.05 = P(Z > z)$ y se busca $z_{0.05}=1.6449$ en tabla. Se despeja: $\frac{\mu_c-9}{5/\sqrt{50}}=1.6449 \Rightarrow \mu_c\approx10.16$. Como $\bar x = 9.1 < 10.16$ (está en la región de aceptación, $]-\infty, 10.16[$), no se rechaza $H_0$ — no hay evidencia en contra de la afirmación de la directiva.
</details>

<details>
<summary><strong>P12</strong> — ¿Por qué en el ejercicio del cargador (n=49, $\bar x=13.6$, $s=5$, afirmación "menor a 15 minutos") se usa Z y no T, a pesar de que $\sigma$ no se conoce directamente?</summary>

Porque $n=49 \ge 30$: por el Teorema del Límite Central, $\bar X$ ya es aproximadamente normal, y con $\sigma$ desconocida se puede usar $s$ dentro de la fórmula de $Z$ (no la de $T$) — la misma regla que en los IC de semana 2, aplicada acá a pruebas de hipótesis.
</details>

<details>
<summary><strong>P13</strong> — Explicá el ejercicio "al revés" del médico: una muestra de $n=20$ da $\bar x=36.7$, $s=4.5$, y se sabe que uno de los promedios críticos es $\mu_c=33.1389$. ¿Cómo se halla el nivel de significancia usado?</summary>

Se estandariza el valor crítico dado: $z = \frac{\mu_c - \mu_0}{s/\sqrt n} = \frac{33.1389-35}{4.5/\sqrt{20}}$, se calcula ese z, y se busca en tabla la probabilidad acumulada asociada — esa probabilidad (o su complemento, según de qué lado esté la región de rechazo) es el $\alpha$ utilizado.
</details>

<details>
<summary><strong>P14</strong> — ¿Qué significa calcular la "potencia de la prueba para muestras de tamaño 20 si el tiempo medio real es de 13 minutos" (ejercicio 6, cargador)?</summary>

Primero se calcula $\mu_c$ con $H_0:\mu=15$, $\alpha=0.04$ y $n=20$ (igual que cualquier prueba clásica). Luego, asumiendo que el valor real es $\mu_1=13$ (la $H_1'$ específica), se calcula $\beta = P(\bar X > \mu_c \mid \mu=13)$ — la probabilidad de NO rechazar $H_0$ aunque en realidad la media sea 13. La potencia es $1-\beta$: la probabilidad de que la prueba sí detecte correctamente que la media es 13 y no 15.
</details>
