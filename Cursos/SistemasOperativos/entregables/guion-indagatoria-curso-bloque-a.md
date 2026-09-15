---
curso: SistemasOperativos
tema: "Guión de presentación — Indagatoria del curso, Block A (Fundamentals)"
fecha: 2026-09-12
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/entregables/indagatoria-curso-documento-en]]"
estado: "borrador v2 (2026-09-14) — simplificado a pedido de Marcos, más coloquial. Joseph confirmado como presentador de Block B, listo para ensayar"
tags: [indagatoria, ia, planificacion, scheduling, trabajo-grupal, ingles, guion, presentacion]
---

# Guión — Indagatoria del curso, Block A (Fundamentals)

Ver también: [[Cursos/SistemasOperativos/entregables/indagatoria-curso-documento-en|Documento completo (inglés)]] · [[Cursos/SistemasOperativos/entregables/indagatoria-curso-plan-equipo|Plan de reparto]] · [[Cursos/SistemasOperativos/entregas]]

**Exposición:** jueves 2026-09-17 (semana 7) · presentación **en inglés** · Marcos presenta **todo el Bloque A seguido** (puntos 1 al 4, sin que nadie más hable en el medio) y recién en el punto 5 le cede la palabra a quien presente Block B.

> **v2 (2026-09-12):** versión simplificada — la primera quedó demasiado densa, con oraciones largas metiendo dos o tres ideas técnicas juntas. Se acortaron las frases, se sacó el dato de EEVDF del gancho de apertura (quedaba forzado ahí, ahora aparece una sola vez, en su lugar natural dentro de la sección de CFS/EEVDF), y se bajó el vocabulario "de paper" a algo que suene a como se explicaría en una conversación real.

**Tono:** hablado, coloquial — como si le explicaras esto a un compañero de otra carrera que no sabe nada de sistemas operativos, no como si leyeras un párrafo del documento. Los tiempos entre paréntesis son un estimado, no una regla.

---

## 1. Hook + team intro (~0:20)

> "Quick question. How many times per second do you think your computer decides which program gets to run next? Go ahead, take a guess. ...It's not ten. It's not a hundred. It's thousands — every single second. That's how often your CPU has to pick a winner. So today, we're looking at how it makes that choice. We're Group 3, Topic 10: AI and Resource Management in Operating Systems. I'm Marcos — I'll cover the basics, what scheduling is and the classic ways to do it. Then Joseph takes over with the AI side."

## 2. What scheduling actually is (~0:35)

> "So, what does 'scheduling' mean? Picture this: your CPU has a few cores, but way more programs want to run than it has room for. Every time a core frees up — something finishes, gets stuck waiting, or its turn just ends — the operating system has to pick who goes next. And that one decision affects three things: how much work gets done overall, how fast you get a response, and whether everyone actually gets a fair turn."

## 3. Why this is a good problem for AI — bridge to Block B (~0:30)

> "Now, the classic way to make that decision uses fixed rules someone wrote by hand — a timer, a priority number. The problem is, those rules only look at what already happened, never what's coming. And that's exactly why this is a great problem for AI: it happens constantly, so there's tons of data; there's a clear goal, like speed or fairness; and the future really is uncertain, so being able to predict it is actually useful. That's where Joseph comes in. But first — let's see how it's done today, without any AI."

## 4. The classic ways to do it (~2:00 total)

### 4a. Round Robin (~0:30)

> "First one: Round Robin. Simple idea — everyone stands in a circle, gets the same amount of time, then goes to the back of the line. It's fair, and it's cheap to build. But it's not smart: a tiny task still has to wait behind a huge one. And picking how long each turn should last is tricky — too short, and you waste time just switching between people; too long, and it stops feeling fair at all."

### 4b. Multi-Level Feedback Queue (~0:35)

> "Next one: Multi-Level Feedback Queue, or MLFQ. The idea is simple. You don't have one line, you have several lines, and each one has its own priority. A task that uses its whole turn moves down to a lower line. A task that finishes early because it was waiting on something stays near the top. That way, short tasks stay near the top, and long tasks move down over time. The problem is, a task at the bottom could get stuck there forever. So every task gets moved back to the top once in a while. That's called aging. The downside is you have to tune a bunch of numbers to make it work well, and the right numbers depend on the situation."

### 4c. CFS and the 2023 surprise (~0:45)

> "And then there's Linux. For almost twenty years, Linux used something called CFS. Simple idea: it tracks how much CPU time each task has already gotten, and always gives the next turn to whoever has the least. It worked well enough to last two decades. But — fun fact — in 2023, Linux actually replaced it with a new one, called EEVDF. Instead of just tracking time spent, it gives every task a deadline, and picks whoever's deadline is closest. It's better at making sure nobody gets left behind. But here's the thing — even this brand-new one only looks at the past. It still can't predict what a process is about to do. And that's exactly the door Joseph is about to open."

## 5. Handoff to Block B (~0:15)

> "So — three ways to do this, each smarter than the last, but all of them reactive. None of them can see the future. Let's see what happens when we let a model try."

---

## Pronunciation notes (para no trabarse en vivo)

| Término | Cómo suena |
|---|---|
| Heuristic(s) — *ya no aparece en esta v2, se sacó la palabra del guión* | — |
| Quantum / time slice | se cambió por "turn" y "time" en el guión — más fácil de decir que "quantum" |
| Round Robin | "raund ROB-in" |
| Queue | "kyoo" (como "cue") |
| EEVDF | deletrealo: "E, E, V, D, F" — nadie lo pronuncia como palabra |
| Starve / starving | STARV / STAR-ving |
| Throughput | THROO-put |

## Próximos pasos

- [x] Confirmar quién presenta Block B — Joseph, ya reemplazado en el guión.
- [ ] Practicar esta versión en voz alta un par de veces — al ser más coloquial, va a sonar más natural con menos ensayo que la v1.
- [ ] Joseph necesita su propio guión hablado para Block B (secciones 3–6) — el documento escrito ya está, pero un guión de exposición es un texto aparte, más corto y coloquial, igual que este.
- [ ] Una vez Block B tenga guión y Block C esté escrito, acordar transiciones cortas entre bloques y hacer un ensayo grupal completo.
