---
curso: SistemasOperativos
tema: "Indagatoria del curso — documento final en inglés (plantilla para el equipo)"
fecha: 2026-09-04
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/indagatoria-curso]]"
estado: "Bloque A listo (Marcos, 2026-09-04), Bloques B y C pendientes de asignar"
tags: [indagatoria, ia, planificacion, scheduling, trabajo-grupal, ingles]
---

# AI and Resource Management in Operating Systems
### Group 3 — Topic #10 — Adaptive Scheduling & Load Prediction

Ver también: [[Cursos/SistemasOperativos/entregables/indagatoria-curso-plan-equipo|Plan de reparto (versión ES para coordinar)]] · [[Cursos/SistemasOperativos/apuntes/indagatoria-curso|Instrucciones/alcance]] · [[Cursos/SistemasOperativos/entregas]]

**Weight:** 10% of final grade · **Due:** moved to week 7, Thursday 2026-09-17 (week 6 is taken by the Arch Linux Indagatoria Corta) · **Format:** written document + oral presentation, **both in English**.

> **Cómo usar esta plantilla:** este documento YA está en inglés porque así se entrega. Cada bloque abajo tiene: qué va, qué preguntas responder, y las fuentes/puntos de partida que ya investigamos en español para el equipo (Marcos las tradujo/adaptó al armar esta plantilla, no hace falta releer los apuntes en español para escribir — pero están linkeados por si hace falta más contexto). Reemplacen el texto en `[corchetes]` por el contenido real y borren las instrucciones en cursiva cuando la sección esté lista. No hace falta traducir nada del español — escriban directo en inglés — así el ensamblado final (Bloque C) es solo pulir consistencia de tono/terminología entre las tres partes, no traducir desde cero.

---

## Block A — Fundamentals *(pieces 1–2 · owner: Marcos · done)*

### 1. Introduction

CPU scheduling is the part of the operating system that decides, every time a processor core becomes free, which of the ready processes or threads gets to run next. A core goes idle constantly and for many different reasons — a running process blocks on I/O, a timer interrupt ends its quantum, a higher-priority task wakes up — and on a modern multi-core system with dozens or hundreds of runnable threads competing for a handful of cores, this decision happens thousands of times per second. The scheduler is therefore one of the few OS components whose logic runs on the critical path of essentially everything the system does: it has direct influence over throughput (how much useful work gets done per unit of time), latency (how quickly an individual task gets a response), and fairness (whether every task gets a reasonable share of the CPU, not just the loudest ones).

Classical schedulers make this decision using fixed, hand-designed rules: a time quantum, a priority level, a queue position. These rules are reactive — they only know what a process has already done, never what it is about to do next. This is precisely what makes scheduling a natural entry point for AI and machine learning. The decision is repeated at very high frequency, which means there is an abundance of historical data to learn from (which process ran, for how long, how much CPU and memory it consumed, what it did afterward). The objective is measurable and explicit (throughput, tail latency, fairness), which gives a model something concrete to optimize. And the environment is genuinely uncertain: the scheduler does not know in advance how long a process will run before it blocks again, so any information that lets it *predict* that behavior — rather than just react to the past — is directly useful. Those three properties (high-frequency repetition, available history, a clear objective under uncertainty) are exactly the conditions under which a learned, predictive policy can outperform a fixed heuristic, which is the premise the rest of this document investigates.

### 2. Classical heuristics (baseline)

Three heuristics illustrate the range of classical scheduling design, from the simplest possible rule to the sophisticated fairness model used in the Linux kernel today. Each one is *reactive*: it decides based only on information about the past, never a prediction of the future — this is the baseline the AI/ML approach in Block B is measured against.

**Round Robin (RR)** is the simplest of the three: every ready process sits in a circular queue and receives a fixed time quantum before being moved to the back of the queue, regardless of what kind of work it is doing. RR is trivially fair in the sense that every process eventually gets a turn, and it is cheap to implement. Its weakness is that it treats every process identically: it has no notion of burst length or priority, so a process that only needs 2ms of CPU is forced to wait behind processes that will use their full quantum, hurting responsiveness for short, interactive jobs. The quantum size is also a difficult manual trade-off — too small and the system wastes time on context switches, too large and RR starts to behave like plain FCFS (First-Come-First-Served) with poor responsiveness.

**Multi-Level Feedback Queue (MLFQ)** improves on this by using several queues with different priority levels and, usually, different quantum sizes. A process that uses its entire quantum without blocking is demoted to a lower-priority (longer-quantum) queue, while a process that blocks for I/O before its quantum expires stays at a higher priority — the effect is that short, interactive, I/O-bound processes are favored over long CPU-bound ones, without the scheduler ever needing to know a process's burst length in advance. To prevent long-running processes from starving at the bottom queue forever, MLFQ periodically boosts every process back to the top ("aging"). The practical limitation is that MLFQ's good behavior depends on a handful of parameters — the number of queues, the quantum at each level, and the aging interval — that must be hand-tuned for a given workload; a configuration that works well for one mix of processes can behave poorly for another.

**CFS (Completely Fair Scheduler)**, the default Linux scheduler until kernel 6.6, and its successor **EEVDF (Earliest Eligible Virtual Deadline First)**, take a different approach based on proportional fairness rather than fixed quanta or priority queues. CFS tracks a *virtual runtime* (`vruntime`) for every task — actual CPU time received, scaled by the task's weight (derived from its `nice` value) — and always picks the runnable task with the smallest `vruntime` from a red-black tree, so CPU time converges toward an equal (or weight-proportional) split among all tasks. EEVDF refines this model by giving each task an explicit *virtual eligible time* and *virtual deadline* computed from its requested time slice, and picking the eligible task with the earliest deadline; this gives EEVDF a more principled way to bound how long a latency-sensitive task can be made to wait, which was a known weak point of CFS. Both are considerably more sophisticated than RR or MLFQ, but they share the same fundamental limitation as the other two: the decision is still driven entirely by *accounting for the past* (time already consumed, weight already assigned) — none of the three heuristics predicts what a process is about to do, which is exactly the gap the adaptive, ML-based approaches in Block B attempt to close.

---

## Block B — The AI/ML approach *(pieces 3–6 · owner: [asignar])*

This is the heaviest research block — it's the actual core of Topic #10, not a review section. Four sub-pieces, can be split further between two people if needed.

### 3. Adaptive scheduling with ML
*What gets predicted (next burst length, priority, resource need)? What model families are used (regression, decision trees, small neural nets, reinforcement learning agents)? What data trains them (historical process traces, syscall patterns, resource counters)?*

`[pending]`

### 4. Load prediction
*Techniques: time-series forecasting (e.g. ARIMA, LSTM) vs. reinforcement learning approaches. How does the prediction actually feed into the scheduling decision — is it advisory (heuristic still decides) or does the model decide directly?*

`[pending]`

### 5. Advantages over classical heuristics
*Adaptability to changing load patterns, better resource utilization under variable/bursty load. Ground this against Block A's baseline — name the specific classical-heuristic weakness each advantage addresses.*

`[pending]`

### 6. Risks / disadvantages
*Computational cost of running the model itself, lack of determinism/explainability (matters for OS-level decisions — hard to debug "why did it pick this process"), risk of bad decisions on out-of-distribution data the model never saw during training.*

`[pending]`

---

## Block C — Real case + closing *(pieces 7–8 · owner: [asignar])*

### 7. Documented real-world case
*Pick ONE and go deep — reproducible, source-backed, not just a marketing description:*
- *Kubernetes autoscaling (HPA/VPA) or Google Borg — well-documented, lots of public papers/engineering blog posts.*
- *An eBPF-based scheduler (e.g. `sched_ext` in the Linux kernel) — more technical/kernel-level, closer to "OS scheduling" in the strict sense, good if the presenter is comfortable getting technical.*

*Whichever is picked, this section should explain: what problem it solves, how prediction/learning factors into its decisions, and at least one concrete piece of evidence (a metric, an incident, a documented tradeoff) — not just "it exists and it's good."*

**Decision needed:** `[team must pick Kubernetes/Borg vs. eBPF before this section can be written — see plan-equipo.md step 2]`

`[pending]`

### 8. Conclusions + References
*Tie Block A (limits of classical heuristics) to Block B (what ML actually buys you) to Block C (proof it works in practice) into a short conclusion. References in a consistent format (APA or IEEE — confirm which the professor prefers) covering every source cited in Blocks A–C, not just Block C's case study.*

`[pending — depends on A, B, C all being drafted first]`

---

## Team checklist

- [ ] Assign Block B owner(s)
- [ ] Assign Block C owner
- [ ] Pick the Block C case study (Kubernetes/Borg vs. eBPF) — blocks section 7
- [ ] Confirm reference format (APA/IEEE) with the professor
- [ ] Weekly sync to merge blocks before the 2026-09-17 deadline
- [ ] Translate/adapt oral presentation slides from the merged document (not a separate writing effort — reuse this doc's structure)
