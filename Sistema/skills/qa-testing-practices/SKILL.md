---
name: qa-testing-practices
description: Use this skill whenever writing test plans, test cases, bug reports, or reviewing code/features for quality assurance, for any project or coursework (QA course, Tacha, GymBase, CaneleApp). Covers professional-grade QA documentation, test case design, and bug reporting so it reads like enterprise QA work, not an afterthought. Trigger this for any request involving testing, QA, test coverage, bug tracking, or "how do I verify this works."
---

# QA & Testing Practices

The standard: **QA artifacts (test plans, cases, bug reports) should be usable by someone who never saw the feature being built** — reproducible, unambiguous, and traceable to a requirement.

## 1. Test case structure

Every test case needs, at minimum:

```markdown
### TC-{TICKET-ID}-{n}: {short title}

**Preconditions:** what state the system/data must be in before starting
**Steps:**
1. 
2. 
3. 
**Expected result:** exactly what should happen
**Actual result:** (filled in during execution)
**Status:** Pass / Fail / Blocked
```

Rules:
- One test case verifies one thing. If "expected result" needs "and," it's probably two test cases.
- Steps are numbered and literal — no "test the login flow," but "1. Open app. 2. Enter valid email. 3. Enter valid password. 4. Tap Login."
- Cover the happy path AND at least: one invalid-input case, one boundary case, one empty/null case.

## 2. Test case categories to cover (don't just test happy paths)

| Category | What it checks |
|---|---|
| Functional | Does the feature do what the requirement says |
| Boundary | Min/max values, empty lists, exactly-at-limit cases (e.g. quantity = 0, a list with exactly 1 item) |
| Negative/invalid input | Wrong types, malformed data, unauthorized access attempts |
| Regression | Did this change break something that worked before |
| Integration | Does this feature behave correctly with the systems around it (e.g. Realtime sync in Tacha, RLS policies in GymBase) |
| Usability | Can someone unfamiliar complete the flow without confusion |

For a requirement to be considered "QA-covered," it needs at least functional + one negative case + one boundary case — not just the demo-happy-path.

## 3. Bug reports

```markdown
### BUG-{n}: {short, specific title — not "button broken"}

**Severity:** Critical / High / Medium / Low
**Environment:** OS, browser/app version, device
**Steps to reproduce:**
1. 
2. 
**Expected:** 
**Actual:** 
**Evidence:** screenshot/video/log
**Related ticket/feature:** {TICKET-ID}
```

Severity guide:
- **Critical:** data loss, security issue, app crash, blocks core flow entirely
- **High:** feature broken with no workaround
- **Medium:** feature broken but workaround exists
- **Low:** cosmetic, doesn't affect function

Rules:
- Title describes the actual failure, not the symptom's vibe: "Checkout fails with 500 error when cart has 0 items" not "checkout is broken."
- Never file a bug without reproduction steps — if it can't be reliably reproduced, note that explicitly and describe conditions observed instead.
- One bug per report — don't bundle unrelated issues found during the same session.

## 4. Test plan (for a feature or milestone, not a single case)

```markdown
# Test Plan: {feature/milestone name}

## Scope
What's being tested / explicitly out of scope

## Requirements covered
{TICKET-IDs} this plan validates

## Test approach
Manual / automated / mixed, and why

## Test cases
Link or list of TC-IDs included

## Risk areas
What's most likely to break, and why it matters most

## Exit criteria
What "done testing" means (e.g. all critical/high cases pass, no open Critical bugs)
```

## 5. Applying this in practice

When asked to do QA work under this skill:
1. Identify the requirement/ticket first — every test case and bug report ties back to one.
2. Write test cases covering functional + negative + boundary at minimum before calling coverage "done."
3. For bug reports, always include reproduction steps — if you can't reproduce it yourself, say so explicitly rather than guessing.
4. Cross-reference with `gitflow-scrum`: QA branches (`qa/{TICKET-ID}-...`) and their test cases should map to the same ticket as the feature PR they validate.
