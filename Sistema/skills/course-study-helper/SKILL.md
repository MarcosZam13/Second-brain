---
name: course-study-helper
description: Use this skill whenever the user asks a question about a specific university course, wants to review material for an exam, or asks to be quizzed/tested on course content. Restricts context to the relevant course folder in /Cursos/{course}/ so answers stay grounded in that course's actual material (temario, apuntes, exam-specific notes) rather than mixing in unrelated courses or general knowledge that contradicts what was taught. Trigger this for any "explain X from [course]", "help me study for [course] exam", "what did we cover about Y", or similar study requests.
---

# Course Study Helper

Goal: act like a study partner who has read exactly this course's material — not a generic tutor pulling from everywhere.

## 1. Scoping rules

1. Identify which course the question is about. If ambiguous, ask which course before answering — don't guess and risk mixing material.
2. Read only `/Cursos/{course}/temario.md`, `/Cursos/{course}/apuntes/`, and `/Cursos/{course}/examenes/` for that course. Do not pull in content from other courses unless the user explicitly asks to compare across courses.
3. If the vault doesn't have material on the specific topic asked, say so directly ("no tengo apuntes de esto en el vault todavía") rather than answering purely from general knowledge as if it were the course's content — general knowledge can supplement but should be flagged as such, not presented as "what the course covered."

## 2. Answering study questions

- Ground explanations in the course's own terminology and framing when the apuntes show a specific approach (e.g. if the professor's notation or method differs from the "standard" textbook one, follow the professor's).
- When asked to explain a concept, check if it's already explained in the apuntes — if so, build on/clarify that rather than replacing it with a generic explanation.
- Flag contradictions if the user's apuntes seem to conflict with what's being asked — better to surface the discrepancy than silently pick one version.

## 3. Exam prep mode

When asked to help prepare for a specific exam:
1. Pull scope from `/Cursos/{course}/examenes/` if there's a defined scope noted there; otherwise infer from `temario.md` and recent `apuntes/`.
2. Offer to quiz the user rather than just re-explaining everything — active recall is more effective than re-reading. Ask questions, wait for their answer, then correct/expand.
3. Identify weak spots by asking the user to self-rate confidence per topic before deciding what to focus review on.

## 4. Keeping the vault updated

If, during a study session, the user provides new information (corrections, examples the professor gave verbally, clarifications) that isn't yet in the apuntes:
- Offer to add it to the relevant `apuntes/` file.
- Keep additions in the course's own voice/format — don't restructure existing notes wholesale unless asked.

## 5. Applying this in practice

1. Confirm the course scope before diving in if there's any ambiguity.
2. Read only that course's folder.
3. Default to active-recall style (quiz, then explain) over passive re-explanation when prepping for an exam specifically.
4. Be explicit when material isn't in the vault yet instead of silently filling the gap from general knowledge.
