---
name: security-practices
description: Use this skill whenever writing or reviewing auth, API routes/server actions, role-based access control, forms that take user input, or anything touching secrets/env vars. Covers OWASP-relevant checks adapted to a Next.js/TypeScript stack with multiple user roles. Trigger this for any request involving login, sessions, permissions, forms, API routes, environment variables, or "is this secure."
---

# Security Practices — TypeScript / Next.js

The standard: **assume every client-supplied value is hostile and every UI-level restriction is decorative until the server enforces it too.** A role check that only hides a button is not a security control — it's a UX nicety a curious user bypasses by calling the API directly.

## 1. Threat-model mindset before writing the code

Before implementing anything that touches auth, data, or user input, answer:
- **Who can reach this?** Anonymous, authenticated, or a specific role?
- **What's the blast radius if the check is missing?** Reading another user's data vs. reading another organization's/tenant's data vs. writing/deleting are different severities.
- **Where does the real check have to live?** Server (API route, server action, database security rules) — never only in a client component or a hidden button.

## 2. Authentication & session handling

- Validate the session/token **server-side** on every request that returns or mutates protected data — never trust a client-sent user ID or role claim without re-verifying it against the auth provider's server SDK.
- Session/inactivity timeout is a requirement, not a nice-to-have, when the spec calls for it — configurable, but must exist.
- Password reset / email verification flows must not leak whether an email exists in the system through response timing or wording differences (no "email not found" vs "wrong password" distinction on login).
- Never log tokens, passwords, or full session objects — even in `console.log` during development; it's easy to forget to remove before a PR.

## 3. Authorization / role-based access control

For a multi-role system (e.g. member / staff / admin, or whatever roles this project actually has):
- Every server-side entry point (API route, server action, database rule) re-checks the caller's role — a role that's only checked in the UI to decide what to render is not authorization.
- Default-deny: a new endpoint/rule starts with no access and gets permissions added explicitly, never the reverse ("open by default, restrict later").
- Ownership checks are per-record, not per-role: "is staff" is not enough to edit a specific record — check "is this staff member the owner/assignee of this specific record."
- Privilege escalation paths: can a lower-role user submit a request body that includes a `role` or `isAdmin` field the server trusts blindly? Strip/ignore client-supplied role or ownership fields on create/update; derive them from the authenticated session server-side.

## 4. Input validation & injection

- Validate and parse every external input (form submission, API body, query param) at the boundary with a schema (Zod or equivalent) — don't pass raw `request.body` fields into a query or write.
- Never build a database query by string-concatenating user input, even with an ORM/SDK that "usually" parameterizes — check the specific call being used.
- Escape or avoid `dangerouslySetInnerHTML` entirely unless the content is sanitized server-side first (DOMPurify or equivalent) — this is the most common React XSS vector.
- File uploads: validate MIME type and size server-side (client-side `accept=` is not a security control), and never trust a client-supplied filename for storage paths.

## 5. Secrets & environment variables (Next.js-specific gotcha)

- Any env var prefixed `NEXT_PUBLIC_` is bundled into client-side JS and **visible to anyone** — never put an API secret, service-account key, or admin credential behind that prefix, only truly public values (a public config object, a public analytics ID).
- Server-only secrets (service account keys, admin SDK credentials, third-party API secrets) stay in unprefixed env vars, read only in server components, route handlers, or server actions — never imported into a file that also ships to the client.
- `.env*` files are never committed — check `.gitignore` covers them before the first commit of a new project, don't assume it's already there.

## 6. Database/BaaS rules mirror server checks

- Whatever enforces access at the database layer (Firestore/Storage security rules, Postgres RLS policies, or equivalent) is the last line of defense — it must enforce the same ownership/role logic as the server code, not just "any authenticated user can read/write." A server-side check with permissive database rules is still exploitable by anyone calling the SDK directly from the browser console.
- Any admin-privileged SDK (full-privilege, bypasses rules) only ever runs in server-side code (route handlers, server actions, background jobs) — if it's reachable from a client bundle, that's a critical finding.

## 7. Common checks for a Next.js app (OWASP-adjacent, adapted)

| Risk | What to check |
|---|---|
| Broken access control | Every mutation/read endpoint re-checks role + ownership server-side (§3) |
| Injection | Schema-validated inputs, no raw string-built queries (§4) |
| Sensitive data exposure | No secrets in client-exposed env vars, no tokens/PII in logs (§5, §2) |
| CSRF | State-changing routes use same-site cookies or a token check, not just a GET link |
| Vulnerable dependencies | `npm audit` clean (or documented, accepted risk) before a milestone, not ignored |
| Security misconfiguration | Default-deny rules (§3, §6), no debug/verbose error responses leaking stack traces in production |
| Rate limiting | Login, password reset, and any expensive/abusable endpoint has basic throttling, even naive |

## 8. Applying this in practice

When asked to review or write security-sensitive code under this skill:
1. Identify the roles that can reach the code path and what each should/shouldn't be able to do (§1, §3).
2. Verify the real check happens server-side, not just in a component's conditional render.
3. Check every external input has schema validation before it touches a query or a write (§4).
4. Grep for the framework's client-exposed env prefix near anything that looks like a secret, and check `.gitignore` covers `.env*` (§5).
5. If reviewing database security rules, confirm they don't just require "authenticated" when the server logic requires a specific role/ownership (§6).
6. Report findings by severity (Critical: broken auth/access control or exposed secret · High: missing input validation on a write path · Medium: missing rate limiting/hardening · Low: defense-in-depth suggestions) — don't bury a critical access-control gap under style nitpicks.
