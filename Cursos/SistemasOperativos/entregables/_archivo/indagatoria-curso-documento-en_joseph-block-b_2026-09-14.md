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

**Weight:** 10% of final grade · **Due:** week 6, Thursday 2026-09-10 (extendable to week 7, 2026-09-17) · **Format:** written document + oral presentation, **both in English**.

> **Cómo usar esta plantilla:** este documento YA está en inglés porque así se entrega. Cada bloque abajo tiene: qué va, qué preguntas responder, y las fuentes/puntos de partida que ya investigamos en español para el equipo (Marcos las tradujo/adaptó al armar esta plantilla, no hace falta releer los apuntes en español para escribir — pero están linkeados por si hace falta más contexto). Reemplacen el texto en `[corchetes]` por el contenido real y borren las instrucciones en cursiva cuando la sección esté lista. No hace falta traducir nada del español — escriban directo en inglés — así el ensamblado final (Bloque C) es solo pulir consistencia de tono/terminología entre las tres partes, no traducir desde cero.

---

## Block A — Fundamentals *(pieces 1–2 · owner: Marcos · done)*

### 1. Introduction

CPU scheduling is the part of the operating system that decides, every time a processor core becomes free, which of the ready processes or threads gets to run next. A core goes idle constantly and for many different reasons — a running process blocks on I/O, a timer interrupt ends its quantum, a higher-priority task wakes up — and on a modern multi-core system with dozens or hundreds of runnable threads competing for a handful of cores, this decision happens thousands of times per second. The scheduler is therefore one of the few OS components whose logic runs on the critical path of essentially everything the system does: it has direct influence over throughput (how much useful work gets done per unit of time), latency (how quickly an individual task gets a response), and fairness (whether every task gets a reasonable share of the CPU, not just the loudest ones).

Classical schedulers make this decision using fixed, hand-designed rules: a time quantum, a priority level, or a queue position. These rules are primarily reactive: they make decisions based on the current system state and observed execution history rather than explicitly learning a predictive model of future workload behavior. This is one reason scheduling is a natural area for applying AI and machine learning. The decision is repeated at very high frequency, which provides substantial historical data about system and workload behavior. The objectives are also measurable, including throughput, latency, and fairness, giving a model concrete criteria to optimize. At the same time, the scheduler operates under uncertainty because it cannot know exactly how a task will behave in the future. Predictive and learning-based approaches therefore offer a potential way to incorporate patterns from previous observations into scheduling decisions, which is the premise investigated in the following sections.

### 2. Classical heuristics (baseline)

Three heuristics illustrate the range of classical scheduling design, from the simplest possible rule to the sophisticated fairness model used in the Linux kernel today. Each one is *reactive*: it decides based only on information about the past, never a prediction of the future — this is the baseline the AI/ML approach in Block B is measured against.

**Round Robin (RR)** is the simplest of the three: every ready process sits in a circular queue and receives a fixed time quantum before being moved to the back of the queue, regardless of what kind of work it is doing. RR is trivially fair in the sense that every process eventually gets a turn, and it is cheap to implement. Its weakness is that it treats every process identically: it has no notion of burst length or priority, so a process that only needs 2ms of CPU is forced to wait behind processes that will use their full quantum, hurting responsiveness for short, interactive jobs. The quantum size is also a difficult manual trade-off — too small and the system wastes time on context switches, too large and RR starts to behave like plain FCFS (First-Come-First-Served) with poor responsiveness.

**Multi-Level Feedback Queue (MLFQ)** improves on this by using several queues with different priority levels and, usually, different quantum sizes. A process that uses its entire quantum without blocking is demoted to a lower-priority (longer-quantum) queue, while a process that blocks for I/O before its quantum expires stays at a higher priority — the effect is that short, interactive, I/O-bound processes are favored over long CPU-bound ones, without the scheduler ever needing to know a process's burst length in advance. To prevent long-running processes from starving at the bottom queue forever, MLFQ periodically boosts every process back to the top ("aging"). The practical limitation is that MLFQ's good behavior depends on a handful of parameters — the number of queues, the quantum at each level, and the aging interval — that must be hand-tuned for a given workload; a configuration that works well for one mix of processes can behave poorly for another.

**CFS (Completely Fair Scheduler)**, the default Linux scheduler until kernel 6.6, and its successor **EEVDF (Earliest Eligible Virtual Deadline First)**, take a different approach based on proportional fairness rather than fixed quanta or priority queues. CFS tracks a *virtual runtime* (`vruntime`) for every task — actual CPU time received, scaled by the task's weight (derived from its `nice` value) — and always picks the runnable task with the smallest `vruntime` from a red-black tree, so CPU time converges toward an equal (or weight-proportional) split among all tasks. EEVDF refines this model by giving each task an explicit *virtual eligible time* and *virtual deadline* computed from its requested time slice, and picking the eligible task with the earliest deadline; this gives EEVDF a more principled way to bound how long a latency-sensitive task can be made to wait, which was a known weak point of CFS. Both are considerably more sophisticated than RR or MLFQ, but they share the same fundamental limitation as the other two: the decision is still driven entirely by *accounting for the past* (time already consumed, weight already assigned) — none of the three heuristics predicts what a process is about to do, which is exactly the gap the adaptive, ML-based approaches in Block B attempt to close.

---
## Block B — The AI/ML approach *(pieces 3–6 · owner: Joseph · done)*


### 3. Adaptive Scheduling with ML

Machine learning can be applied to scheduling and resource-allocation problems at different levels of a computing system. In the heterogeneous scheduling framework described by Shen et al., the decision process incorporates information about available CPU, GPU, and NPU resources, as well as task-related information [3]. Similarly, optimization approaches can coordinate CPU resource allocation across distributed computing centers [2]. The scheduler can also consider information associated with incoming tasks, including their resource requirements and scheduling-related timing information [3]. These examples illustrate how learning-based approaches can extend scheduling beyond the selection of a single CPU process by considering heterogeneous resources and broader system-level workload information.

Reinforcement learning (RL) agents can process these dynamic inputs by learning scheduling policies through interaction with the environment. In particular, Q-Learning can learn the value of different actions under a given system state and use these values to select scheduling decisions. The framework proposed by Shen et al. uses an adapted Q-Learning agent to make scheduling decisions in a heterogeneous computing environment [3]. This approach allows the agent to learn from the consequences of previous scheduling actions rather than relying exclusively on manually specified scheduling rules.

Unlike classical heuristics that reactively assign time slices or select tasks according to predefined rules, an RL scheduler can learn a policy that maps an observed system state to a scheduling action. In the framework proposed by Shen et al., the action space includes decisions involving the assignment of a task to a computing resource as well as the possibility of delaying its execution for a specified period [3]. This allows the scheduler to consider whether immediate execution is preferable to waiting for a more appropriate heterogeneous resource to become available. The resulting approach therefore incorporates both resource selection and scheduling timing into the decision process [3].

### 4. Load Prediction

Time-series forecasting techniques can be used to estimate future resource demand from historical workload measurements. Classical statistical methods such as ARIMA are designed to model temporal patterns in sequential data, while neural network architectures such as LSTM can capture more complex temporal dependencies. Liu et al. investigate a combined LSTM-ARIMA model for cloud computing load forecasting, illustrating how statistical and neural forecasting techniques can be combined to model dynamic workload behavior [4].

Forecasting and scheduling can also be separated into two stages. In one approach, a forecasting model first estimates future workload or resource demand, and that prediction is then provided to another scheduling mechanism as an additional input. In contrast, reinforcement learning can learn a policy that maps the observed system state directly to scheduling actions. In the framework proposed by Shen et al., the RL agent directly selects scheduling actions rather than producing only a workload forecast [3].

The agent learns to make these decisions by maximizing a mathematical reward function. In the scheduling framework proposed by Shen et al., the reward function is designed to favor lower task completion and waiting times [3]. By repeatedly interacting with the environment and receiving rewards based on the resulting scheduling performance, the RL agent learns a policy that attempts to improve task execution efficiency [3].

### 5. Advantages over Classical Heuristics

One potential advantage of ML-based scheduling is its ability to incorporate a broader range of information when making decisions in heterogeneous computing environments. Classical schedulers such as MLFQ rely on predefined queueing rules and manually selected parameters, whereas an ML-based scheduler can explicitly incorporate information about different resource types and their current availability. In the heterogeneous scheduling framework studied by Shen et al., the RL agent considers CPU, GPU, and NPU resources when selecting how tasks should be scheduled [3].

ML-based scheduling can also provide advantages under highly variable or bursty workloads. Classical and greedy scheduling strategies typically make decisions based primarily on the current queue state and available resources. An adaptive RL scheduler can instead evaluate a broader system state and, in the framework studied by Shen et al., can choose to delay a task rather than assign it immediately [3]. This mechanism can help avoid inefficient resource allocation when an immediately available resource is not the most appropriate one for the task.

In the burst-arrival experiments reported by Shen et al., the proposed RL-based scheduler achieved a reported performance improvement of approximately 271% under the evaluated burst-arrival workload, compared with the baseline scheduling strategies considered in the study [3]. This result suggests that adaptive scheduling can provide substantial benefits under certain highly variable workload conditions. However, the reported improvement is specific to the experimental setup and should not be interpreted as a universal performance improvement for all RL-based schedulers [3].

### 6. Risks / Disadvantages

A major challenge is the computational overhead introduced by the ML model itself. Unlike conventional schedulers based primarily on fixed rules, an ML-based scheduler requires additional computation to process system information and select an action. This creates a trade-off between the complexity of the model and the performance benefits it provides. The practical impact depends on factors such as the model architecture, inference frequency, and workload [5].

Another concern is reduced interpretability. A learned scheduling policy can be more difficult to inspect than a rule-based heuristic because the reasoning behind an individual decision may be encoded in the model rather than expressed through an explicit rule. This can make debugging and diagnosing unexpected scheduling behavior more difficult.

Finally, ML-based scheduling can be less robust when workloads differ substantially from the patterns represented in the training data. Under such distribution shifts, the model may produce less reliable predictions or scheduling decisions. SwarmX illustrates this challenge by evaluating its predictor under an out-of-distribution workload change and using online adaptation to respond to changing workload behavior [5]. It also includes a fallback mechanism that allows the underlying scheduling policy to continue operating when the predictive component is temporarily unavailable [5].

---
## Block C — Real case + closing *(pieces 7–8 · owner: [asignar])*


### 7. Documented Real-World Case

Choose ONE documented real-world case and analyze it in depth. The case must be supported by primary or authoritative technical sources and should not be presented only as a general description.

Possible options include:

- **Kubernetes** — HPA/VPA, cluster scheduling, or another documented resource-management mechanism. If Kubernetes is selected, clearly identify where prediction, learning, or adaptive decision-making is involved. Do not present Kubernetes itself as an AI scheduler unless the selected source explicitly supports that claim.

- **Google Borg** — a strong option for analyzing large-scale cluster resource management and scheduling, with extensive technical documentation and measurable results.

- **Linux `sched_ext` / eBPF-based scheduling** — technically closer to operating-system scheduling, but requires more detailed discussion of Linux kernel scheduling mechanisms and the role of learning-based policies.

The selected case should answer three questions:

1. **What problem does the system solve?**

2. **How do prediction, learning, or adaptive resource management influence its decisions?**

3. **What concrete evidence demonstrates its effectiveness or limitations?**


Include at least one verifiable quantitative result, such as a performance improvement, latency reduction, resource-utilization metric, scalability result, or documented trade-off.

The case should connect directly with the concepts discussed in Blocks A and B: classical scheduling limitations, adaptive scheduling, workload/resource prediction, benefits under changing workloads, and the risks or safeguards associated with ML-based approaches.

---
### 8. Conclusions

Tie Block A (limits of classical heuristics) to Block B (what ML actually buys you) to Block C (proof it works in practice) into a short conclusion. References in a consistent format (APA or IEEE — confirm which the professor prefers) covering every source cited in Blocks A–C, not just Block C's case study.*


##  References

  **Campo de [1] por si Marcos quiere agregar una referencia

- **[2]** M. Doostmohammadian _et al._, "Machine Learning and CPU (Central Processing Unit) Scheduling Co-Optimization over a Network of Computing Centers," _arXiv preprint arXiv:2510.25176_, 2025. Available: [https://arxiv.org/html/2510.25176v1](https://arxiv.org/html/2510.25176v1)

- **[3]** W. Shen, W. Lin, W. Wu, H. Wu, and K. Li, “Reinforcement learning-based task scheduling for heterogeneous computing in end-edge-cloud environment,” _Cluster Computing_, vol. 28, no. 3, art. no. 179, 2025, doi: 10.1007/s10586-024-04828-2.

- **[4]** X. Liu _et al._, "Research on Cloud Computing load forecasting based on LSTM-ARIMA combined model," in _2022 International Conference on Advanced Cloud and Big Data (CBD)_, 2022. Available: [https://es.scribd.com/document/710772100/Research-on-Cloud-Computing-Load-Forecasting-Based-on-LSTM-ARIMA-Combined-Model](https://es.scribd.com/document/710772100/Research-on-Cloud-Computing-Load-Forecasting-Based-on-LSTM-ARIMA-Combined-Model)

- **[5]** "SwarmX: Agentic Scheduling for Low-Latency Agentic Systems," _arXiv preprint arXiv:2606.21401_, 2026. Available: [https://arxiv.org/html/2606.21401v1](https://arxiv.org/html/2606.21401v1)

`[pending — depends on A, B, C all being drafted first]`

---

## Team checklist

- [x] Assign Block B owner(s)
- [x] Assign Block C owner
- [x] Pick the Block C case study (Kubernetes/Borg vs. eBPF) — blocks section 7
- [ ] Confirm reference format (APA/IEEE) with the professor
- [ ] Weekly sync to merge blocks before the 2026-09-10 deadline (or 09-17 if extended)
- [ ] Translate/adapt oral presentation slides from the merged document (not a separate writing effort — reuse this doc's structure)
