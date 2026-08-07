---
name: professional-technical-docs
description: Use this skill whenever writing READMEs, architecture docs, code comments, API documentation, or any written technical documentation for a project (GymBase, Tacha, CaneleApp, university deliverables). Ensures documentation reads as professional and human-written, not generic AI output, and follows a consistent structure that lets any future reader understand the project without asking questions. Trigger this for any documentation-writing task, not just when the user explicitly says "write docs."
---

# Professional Technical Documentation

The standard: documentation that reads like it was written by someone who actually built the thing and wants the next person to succeed quickly — specific, direct, no filler.

## 1. How to avoid the "AI-generic" writing tell

Common patterns that signal generic/unedited AI output — actively avoid:
- Opening with throat-clearing ("In today's fast-paced development environment...", "This document aims to provide a comprehensive overview of...").
- Excessive hedging or vague qualifiers ("It's worth noting that...", "generally speaking...", "in most cases...") when a direct statement works.
- Restating the obvious ("This function returns a value" as the entire docstring for a function called `calculateTotal`).
- Bullet-pointing everything even when prose reads better, or the reverse — walls of prose where a table/list would be clearer.
- Uniform paragraph lengths and rhythm — real writing has variation; a 3-sentence paragraph next to a 1-sentence one is normal.
- Excessive emoji or exclamation points as enthusiasm substitutes for actual content.
- Ending every section with a forward-looking summary sentence ("This sets the foundation for...") — just stop when the point is made.

Counter-move: **write like you're explaining it to a specific competent person who wasn't there**, not performing thoroughness. Cut anything that doesn't help that person. Say things directly: "This endpoint requires an admin token" not "It should be noted that this endpoint typically requires appropriate authorization."

## 2. README structure (the front door of any repo)

```markdown
# Project Name

One or two sentences: what this is and who it's for.

## Stack
Bullet list of the actual technologies — no explanation needed if standard.

## Getting started
1. Clone
2. Install (exact command)
3. Environment variables needed (list them, don't just say "set up your .env")
4. Run locally (exact command)

## Project structure
Brief map of where things live — point to docs/architecture.md for depth, don't duplicate it here.

## Deployment
How this actually gets deployed — the real process, not a generic placeholder.

## Key decisions / gotchas
Anything a new contributor would trip over that isn't obvious from the code.
```

If a step requires more than the command itself (e.g. "requires Node 20+, run `nvm use` first"), say so — assume nothing about the reader's environment.

## 3. Architecture docs

Document **decisions**, not just structure — the code already shows structure. What belongs in `docs/architecture.md`:
- Why this data model over an alternative (e.g. why `product_catalog.household_id` nullable instead of a separate global table).
- Why this third-party choice (e.g. why Supabase over Firebase, why PostgREST/RPC over GraphQL).
- Known trade-offs and what would need to change if a constraint shifts (e.g. "this assumes single-region; multi-region would require X").

A diagram earns its place only if it clarifies a relationship that's hard to hold in your head from prose alone (data flow, entity relationships) — not decoration.

## 4. Code comments

- Comments explain **why**, never **what** — the code already says what it does.
- Document non-obvious constraints directly at the point they matter: `// must run before RLS policy applies, see migration 003` beats a comment three files away.
- Public functions/APIs get a docstring: purpose, params, return, edge cases — not a restatement of the function signature in prose.
- Delete comments that no longer match the code — a wrong comment is worse than no comment.

## 5. Voice and tone checklist before finishing any doc

- Read it back and cut every sentence that could be deleted without losing information.
- Replace vague qualifiers with specifics ("fast" → "under 200ms", "many users" → an actual number or "no fixed limit, tested to X").
- Vary sentence length — if every sentence is roughly the same length and structure, rewrite half of them.
- If a section could apply to literally any project by swapping the name, it's too generic — make it specific to this project's actual decisions and constraints.

## 6. Applying this in practice

When asked to write documentation under this skill:
1. Identify who's actually going to read this (a new contributor? an interviewer? future-you in six months?) and write for that reader specifically.
2. Draft, then do a pass specifically checking against section 1's tells — cut anything that reads as filler.
3. For READMEs, verify every command listed actually matches the current project setup — don't leave placeholder commands.
4. Cross-reference with `clean-code-practices` for repo structure conventions the docs should reflect accurately.
