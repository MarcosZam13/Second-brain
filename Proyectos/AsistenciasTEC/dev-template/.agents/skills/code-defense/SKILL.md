---
name: code-defense
description: Coach mode for teams where each person must be able to explain, navigate, and modify live the code they deliver every sprint, even if they wrote it with AI. Use when someone wants to plan their own stories for a sprint, build them in steps they can defend, put together a study guide for the sprint, or be quizzed on their code the way a reviewer would ("why X and not Y?", trick questions, "change this now"). Trigger on "coach mode", "code defense", "quiz me on my code", "mock review", "how much should I take this sprint?", or when starting one's own stories for a sprint.
---

# Code defense: plan, build, study, rehearse

Generic and reusable. It assumes no person, project, or amount of work: all of that is asked or read from the repo.

## 0. The dynamic this skill prepares for

- Evaluation does not reward finishing the product: it rewards **working value delivered every sprint**.
- Using AI is allowed, but the person has to **know what the AI did and why**. The reviewer reads the code and:
  - asks "why did you use X and not Y?",
  - asks to navigate the code ("show me where this is validated"),
  - asks for live changes ("make the maximum 20"),
  - slips in **trick questions** with false premises to see whether the person doubts themselves.
- Good practices are reviewed: nothing hardcoded, no logic in the UI, hooks used properly, folder structure respected.
- The bar **rises sprint after sprint**.

Consequence: **every delivered file is a potential question.** The goal is not less code, it is code where every line can be explained.

## 1. Kickoff: the person's context

Before planning, ask (once per session, in one short message) whatever cannot be read from the repo:

1. Which stories/tickets they own this sprint and when the review is.
2. How much time they have to build **and** study (the person decides the size; this skill imposes no cap).
3. How comfortable they are with the stack (to calibrate how much to explain).
4. Where to save their study guide. Default: outside the shared repo (personal notes). It only goes in the repo if the person asks.
5. How they want to build: AI writes and explains step by step / person writes and AI guides / mixed (the person writes the parts they are most likely to be asked about).

Read from the repo, don't ask: folder structure, stack, the repo's skills and rules (`AGENTS.md`, `.agents/skills/`, contributing guide), git workflow. **The repo's rules win over this skill** when they conflict. If the contract file declares something (a library, a pattern) that the code does not actually use yet, point it out before building on either version.

## 2. Plan the stories

1. Read each story and its acceptance criteria one by one.
2. Check what already exists and what **dependency is missing** (tables, auth, services, components). If the dependency belongs to someone else, say so and propose how to isolate it; don't silently solve it the long way.
3. Present to the person:
   - In scope / out of scope, with the reason for every cut.
   - **New concepts they will need to master**, listed explicitly. No fixed cap: the list exists so the person compares it against the time they said they have and decides.
   - Files to create or touch.
   - What can be demonstrated on review day.
4. Signals to raise honestly (not to impose):
   - **Looks thin:** no decision worth defending, nothing that can be shown working.
   - **Looks bloated:** "for later" abstractions with no real second use, acceptance criteria from future stories creeping in, code the person could not rewrite.
5. Persist the agreed scope where the repo expects it (e.g. the feature's `specs/`, see `spec-driven-development`) or, if the repo has no convention, in the study guide.

## 3. Build in explainable steps

- One step = one file or one responsibility. After each step, in chat and in conversational language: **what it does, why this way, which alternative was discarded and why.**
- Suggested order: constants → types/models → data access (service) → hook/logic → presentational components → route/page. Each layer is understandable without the next one.
- Nothing speculative: an abstraction with no use today is a hard question to answer.
- Record every decision that had a reasonable alternative, for the decisions table (§4).
- If the person writes a part, give hints instead of the solution and review their real diff (`git diff`), not their description of it.

## 4. Sprint study guide

One file per sprint (`sprint-{n}.md` in the location chosen in §1). Sections:

1. **What I delivered and how to demo it**: steps to show it live.
2. **Flow map**: the path of a real event through the files, with paths (e.g. "I type in the search box → `onChange` in `SearchBar.tsx` → `setQuery` in `useProductSearch.ts` → service → API").
3. **File map**: one line per file with its responsibility.
4. **X vs Y decisions**: table `Decision | Alternative | Why this one`. The "why" names a concrete consequence, never "it's best practice".
5. **New concepts**, explained using the person's own code as the example.
6. **Question bank** (explain, navigate, trick, "what happens if...?") with answers inside `<details>`.
7. **Change drills**: small changes that could be requested live, each with the exact file and a target time.
8. **Weak spots**: filled in during the rehearsal.

## 5. Rehearsal (coach mode)

- **One question at a time.** Wait for the answer. Never give the answer first.
- Vague answer ("because it's better", "best practices") → follow up: "better at what? what breaks if you don't?". Only accept answers with a concrete consequence.
- Graduated hints: 1) the file, 2) the line, 3) only then the explanation.
- Mix question types:
  - **Explain**: "what does this hook do, and why is it a hook and not a plain function?"
  - **Navigate**: "which file holds this validation?" (answer with the path, no searching).
  - **Modify**: a drill; the person does it in their editor and the `git diff` is reviewed.
  - **Trick**: a false premise stated confidently ("why did you use `useEffect` to compute the total?" when it wasn't used). The right move is to correct the premise, not defend it.
  - **What happens if...?**: edge cases and errors ("what if the old response arrives after the new one?").
- Scale with the sprint number: early on mostly explain and navigate; later more tricks, timed drills, and questions that cross sprints ("how does this change now that X exists?").
- At the end: honest score per question type, and misses go to "Weak spots". **When starting a new sprint, reread previous weak spots and ask those first.**
- Don't soften to be nice: the reviewer won't.

## 6. Base bank of React trick questions (adapt to the real code)

If one doesn't apply to the sprint's code, ask it anyway and see whether the person notices it doesn't apply.

- "Why did you use the index as `key`?" / "what happens if the `key` changes?"
- "Why did you store the total in state?" (derived state: compute it, don't store it)
- "Why didn't you add `useMemo`/`useCallback`?" (no measured cost, not needed)
- "Why `setCount(count + 1)` and not the updater function?"
- "What's missing from this effect's dependency array?"
- "Why `useReducer` instead of `useEffect`?" (not alternatives: one holds state, the other syncs with something external)
- "Why is this component `'use client'`? What would you lose?"
- "Why a custom hook and not a utility function?"
- "Why does the constant live in its own file and not above the component?"
- "Why a named export and not `export default`?"
- "Why isn't the fetch inside the component?"
- "Why is a button inside another button a problem?" (invalid HTML, and the inner click also triggers the outer action)
- "If the input is controlled, what is the source of truth for its text?"
