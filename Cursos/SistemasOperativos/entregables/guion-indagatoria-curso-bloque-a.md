---
curso: SistemasOperativos
tema: "Guión de presentación — Indagatoria del curso, Block A (Fundamentals)"
fecha: 2026-09-12
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/entregables/indagatoria-curso-documento-en]]"
estado: borrador — listo para ensayar, falta timing real y nombre de quien presenta Block B
tags: [indagatoria, ia, planificacion, scheduling, trabajo-grupal, ingles, guion, presentacion]
---

# Guión — Indagatoria del curso, Block A (Fundamentals)

Ver también: [[Cursos/SistemasOperativos/entregables/indagatoria-curso-documento-en|Documento completo (inglés)]] · [[Cursos/SistemasOperativos/entregables/indagatoria-curso-plan-equipo|Plan de reparto]] · [[Cursos/SistemasOperativos/entregas]]

**Exposición:** jueves 2026-09-17 (semana 7) · presentación **en inglés** · Marcos presenta Block A completo (piezas 1-2: Introduction + Classical heuristics) y le cede la palabra a quien presente Block B.

**Tono:** hablado, no leído — igual que en el guión de la Indagatoria Corta de Arch Linux. Explicar la idea con tus propias palabras al ensayar; lo que importa es que suene natural en inglés, no memorizar la frase exacta. Los tiempos entre paréntesis son un estimado para armar el ritmo, no una regla — ajustalos al ensayar en voz alta.

**Gancho pedido por el profesor:** arranca con una pregunta retórica + un dato real (el cambio de scheduler de Linux en 2023) en vez de empezar directo con la definición — es la parte que engancha antes de meterse en lo técnico.

---

## 1. Hook + team intro (~0:25)

> "Quick question before we start: how many times per second do you think the CPU in front of you decides which process runs next? Not tens. Not hundreds. On a modern multi-core system, it's thousands of times every second. And here's the part that surprised us: the exact rule the Linux kernel uses to make that decision changed in 2023 — after almost two decades. Something this fundamental is still evolving, and that's exactly why our group picked this topic. We're Group 3, Topic 10: AI and Resource Management in Operating Systems. I'm Marcos, and I'll cover the fundamentals — what scheduling is, and how it's done today — before handing off to [teammate] for the machine learning side."

## 2. What scheduling is, and why it matters (~0:40)

> "So, what is CPU scheduling? Every time a core goes idle — a process blocks on I/O, its time slice runs out, something higher-priority wakes up — the operating system has to decide who runs next. On a machine with dozens of runnable threads and only a handful of cores, that happens constantly, and it directly shapes three things: throughput, how much work gets done; latency, how fast you get a response; and fairness, whether every process gets a real turn."

## 3. Why this is a natural fit for AI — bridge to Block B (~0:35)

> "Classical schedulers make that decision with fixed, hand-designed rules — a time quantum, a priority level. The problem is they're reactive: they only know what a process already did, never what it's about to do next. But scheduling has three things going for it if you want to apply machine learning: it repeats at very high frequency, so there's a ton of data to learn from; the goal is measurable — throughput, latency, fairness; and the environment is genuinely uncertain, so predicting what a process will do is actually useful. That's the gap [teammate]'s part of the talk picks up. But first, let's look at how it's done today — the baseline we're comparing against."

## 4. Classical heuristics (~2:15 total)

### 4a. Round Robin (~0:30)

> "The simplest one is Round Robin. Every process sits in a circular queue and gets a fixed time slice before going to the back of the line. It's fair — everyone eventually gets a turn — and it's cheap to implement. But it treats every process the same: one that only needs two milliseconds still waits behind long ones, which hurts anything interactive. And picking the time slice itself is a trade-off — too short, and the system wastes time switching between processes; too long, and it starts behaving like plain first-come-first-served."

### 4b. Multi-Level Feedback Queue (~0:35)

> "Multi-Level Feedback Queue improves on that with several queues at different priority levels. Use your whole time slice without blocking, and you drop a level; block early for I/O, and you stay high priority. So short, interactive processes naturally float to the top — without the scheduler ever knowing in advance how long a process needs. To stop long processes from starving at the bottom forever, MLFQ periodically boosts everyone back up — that's called aging. The catch: it depends on a handful of hand-tuned numbers, and a setup that works for one workload can fall apart for another."

### 4c. CFS and EEVDF (~0:50)

> "Which brings us back to that fact from the beginning. For almost two decades, Linux used CFS — the Completely Fair Scheduler — which tracks a 'virtual runtime' for every task and always picks whoever has received the least CPU time so far, scaled by priority. Since 2023, Linux runs EEVDF instead — spelled out, E-E-V-D-F — which gives each task a virtual deadline and picks whoever's deadline is closest. That's a more principled way to guarantee latency-sensitive tasks don't starve, which was CFS's known weak spot. But here's the thing: even EEVDF only looks backward, at time already spent. None of these three heuristics predicts what a process is about to do next — and closing exactly that gap is what [teammate] is about to show you."

## 5. Handoff to Block B (~0:15)

> "So that's our baseline: three heuristics, all reactive, all tuned by hand. Now [teammate] is going to show you what happens when a model learns the pattern instead of someone hard-coding it."

---

## Pronunciation notes (para no trabarse en vivo)

| Término | Cómo suena |
|---|---|
| Heuristic(s) | hyoo-RIS-tik(s) |
| Quantum | KWAN-tuhm |
| Round Robin | ronda normal, sin acento raro — "raund ROB-in" |
| Queue | "kyoo" (como "cue") |
| EEVDF | deletrealo letra por letra: "E, E, V, D, F" — nadie lo pronuncia como palabra |
| vruntime / virtual runtime | mejor decir "virtual runtime" completo en vez de la abreviatura, se entiende más claro hablado |
| Starve / starving | starv / STAR-ving (que un proceso "starves" = se queda sin CPU nunca) |
| Throughput | THROO-put |
| Latency | LAY-tuhn-see |

## Vocabulario clave para tener fresco (por si preguntan)

- **Scheduler** = planificador · **Ready queue** = cola de procesos listos · **Time slice / quantum** = cuanto de tiempo
- **Reactive** (decide con el pasado) vs. **predictive** (anticipa el futuro) — es el contraste central entre Block A y Block B
- **Starvation** = un proceso nunca recibe CPU · **Aging** = mecanismo para evitarlo, subiendo prioridad con el tiempo
- **Fairness** = que nadie acapare el CPU injustamente

## Próximos pasos

- [ ] Confirmar quién presenta Block B para reemplazar los `[teammate]` del guión por el nombre real.
- [ ] Ensayar en voz alta contra el tiempo real — este guión da ~4 minutos para Block A solo; sumarle Block B y Block C para saber el total.
- [ ] Practicar la pronunciación de EEVDF, heuristics y quantum unas cuantas veces sueltas antes de meterlas en el guión completo.
- [ ] Una vez Block B y C estén escritos, acordar transiciones cortas entre bloques (ver la sección 5 de arriba como ejemplo) y hacer un ensayo grupal completo.
