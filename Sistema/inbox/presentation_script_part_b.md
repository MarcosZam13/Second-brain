# AI and Resource Management in Operating Systems
## Group 3 — Presentation Script & Structure (Part B: AI/ML Approach)

### Slide 1: Adaptive Scheduling with Machine Learning
**Visual / Bullet Points:**
- Beyond classical heuristics: Artificial Intelligence & Machine Learning
- **Heterogeneous Environments:** Managing CPUs, GPUs, and NPUs together
- **Reinforcement Learning (RL):** Using adapted Q-Learning
- **Dynamic Decision-Making:** Choosing when to run vs. when to delay tasks

**Speaker Script (Person B):**
> "Hello everyone. Moving on to how we can improve these classical limitations, we look into Artificial Intelligence and Machine Learning. 
> 
> Instead of using fixed, rigid rules, machine learning allows the system to adapt. For instance, in heterogeneous environments—where we have CPUs, GPUs, and NPUs working together—Reinforcement Learning (like adapted Q-Learning) can learn optimal scheduling policies by interacting with the system environment. 
> 
> The scheduler doesn't just react to what just happened; it can evaluate the broader system state and make decisions, such as choosing whether to assign a task immediately or delay its execution until a more appropriate resource becomes available."

---

### Slide 2: Load Prediction & How it Works
**Visual / Bullet Points:**
- **Time-Series Forecasting:** Estimating future resource demand
- **Model Architecture:** Combining LSTM neural networks and ARIMA statistical models
- **Optimization Goal:** Maximizing a mathematical reward function
- **Performance Targets:** Lower task completion times and reduced waiting times

**Speaker Script (Person B):**
> "To make these smart decisions, the system often relies on load prediction. By using time-series forecasting models—like a combination of LSTM neural networks and ARIMA statistical models—we can estimate future resource demands based on historical workload data.
> 
> The reinforcement learning agent is trained by maximizing a mathematical reward function, which is specifically designed to favor lower task completion times and reduced waiting times."

---

### Slide 3: Advantages over Classical Heuristics
**Visual / Bullet Points:**
- **Multi-Resource Handling:** Superior adaptation across CPU, GPU, and NPU pools
- **Bursty Workloads:** Ability to pause or delay tasks to prevent bad allocations
- **Experimental Impact:** Up to ~271% performance improvement under evaluated burst-arrival conditions (study-specific)

**Speaker Script (Person B):**
> "So, what are the main advantages? 
> First, ML-based schedulers can handle complex, multi-resource environments (CPU, GPU, NPU) much better than traditional queues like MLFQ. 
> Second, under bursty or highly variable workloads, an adaptive scheduler can pause or delay tasks to prevent inefficient allocations. For example, in specific experimental studies, adaptive RL schedulers have shown massive performance improvements under burst-arrival conditions compared to baseline strategies."

---

### Slide 4: Risks and Disadvantages
**Visual / Bullet Points:**
- **Computational Overhead:** Extra CPU cycles and inference latency from the model
- **Low Interpretability:** Harder to debug black-box learned policies vs. explicit code rules
- **Distribution Shifts:** Performance drops when real workloads drift from training data
- **Mitigation:** Need for fallback mechanisms and online adaptation

**Speaker Script (Person B):**
> "However, we must also consider the risks:
> 1. Computational Overhead: Running an ML model takes extra CPU cycles and introduces inference latency.
> 2. Lower Interpretability: Unlike a clear rule, a learned policy is harder to debug when things go wrong.
> 3. Distribution Shifts: If the workload changes drastically from the training data, the model's performance can drop, which is why real systems require fallback mechanisms."
