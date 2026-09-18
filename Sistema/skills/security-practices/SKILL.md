---
name: security-practices
description: Use this skill whenever writing or reviewing auth, API routes/server actions, role-based access control, forms that take user input, or anything touching secrets/env vars, for any TypeScript/Next.js project (Asistencias TEC, Tacha, GymBase, CaneleApp) or the Seguridad course. Covers OWASP-relevant checks adapted to a Next.js + Firebase/Supabase stack with multiple roles (student/professor/admin-style). Trigger this for any request involving login, sessions, permissions, forms, API routes, environment variables, or "is this secure."
---

# Security Practices — TypeScript / Next.js

The standard: **assume every client-supplied value is hostile and every UI-level restriction is decorative until the server enforces it too.** A role check that only hides a button is not a security control — it's a UX nicety a curious user bypasses by calling the API directly.

## 1. Threat-model mindset before writing the code

Before implementing anything that touches auth, data, or user input, answer:
- **Who can reach this?** Anonymous, authenticated, or a specific role?
- **What's the blast radius if the check is missing?** Reading another user's data vs. reading another household/company's data vs. writing/deleting are different severities.
- **Where does the real check have to live?** Server (API route, server action, Firestore/Postgres security rules) — never only in a client component or a hidden button.

## 2. Authentication & session handling

- Validate the session/token **server-side** on every request that returns or mutates protected data — never trust a client-sent user ID or role claim without re-verifying it against the auth provider's server SDK.
- Session/inactivity timeout is a requirement, not a nice-to-have, when the course/company rubric asks for it (seen in Tacha's auth requirements) — configurable, but must exist.
- Password reset / email verification flows must not leak whether an email exists in the system through response timing or wording differences (no "email not found" vs "wrong password" distinction on login).
- Never log tokens, passwords, or full session objects — even in `console.log` during development; it's easy to forget to remove before a PR.

## 3. Authorization / role-based access control

For a multi-role system (student / professor / super admin, or equivalent):
- Every server-side entry point (API route, server action, Firestore/Postgres rule) re-checks the caller's role — a role that's only checked in the UI to decide what to render is not authorization.
- Default-deny: a new endpoint/rule starts with no access and gets permissions added explicitly, never the reverse ("open by default, restrict later").
- Ownership checks are per-record, not per-role: "is professor" is not enough to edit a specific asistencia — check "is this professor the owner/assigned professor of this specific record."
- Privilege escalation paths: can a lower-role user submit a request body that includes a `role` or `isAdmin` field the server trusts blindly? Strip/ignore client-supplied role or ownership fields on create/update; derive them from the authenticated session server-side.

## 4. Input validation & injection

- Validate and parse every external input (form submission, API body, query param) at the boundary with a schema (Zod or equivalent) — don't pass raw `request.body` fields into a query or write.
- Never build a database query by string-concatenating user input, even with an ORM/SDK that "usually" parameterizes — check the specific call being used.
- Escape or avoid `dangerouslySetInnerHTML` entirely unless the content is sanitized server-side first (DOMPurify or equivalent) — this is the most common React XSS vector.
- File uploads: validate MIME type and size server-side (client-side `accept=` is not a security control), and never trust a client-supplied filename for storage paths.

## 5. Secrets & environment variables (Next.js-specific gotcha)

- Any env var prefixed `NEXT_PUBLIC_` is bundled into client-side JS and **visible to anyone** — never put an API secret, service-account key, or admin credential behind that prefix, only truly public values (a public Firebase config, a public analytics ID).
- Server-only secrets (service account keys, admin SDK credentials, third-party API secrets) stay in unprefixed env vars, read only in server components, route handlers, or server actions — never imported into a file that also ships to the client.
- `.env*` files are never committed — check `.gitignore` covers them before the first commit of a new project, don't assume it's already there.

## 6. Firebase/Supabase-specific: rules mirror server checks

- Firestore/Storage security rules (or Postgres RLS policies) are the last line of defense — they must enforce the same ownership/role logic as the server code, not just "any authenticated user can read/write." A server-side check with permissive database rules is still exploitable by anyone calling the SDK directly from the browser console.
- The Admin SDK (full-privilege, bypasses rules) only ever runs in server-side code (route handlers, server actions, Cloud Functions) — if it's reachable from a client bundle, that's a critical finding.

## 7. Common checks for a Next.js app (OWASP-adjacent, adapted)

| Risk | What to check |
|---|---|
| Broken access control | Every mutation/read endpoint re-checks role + ownership server-side (§3) |
| Injection | Schema-validated inputs, no raw string-built queries (§4) |
| Sensitive data exposure | No secrets in `NEXT_PUBLIC_*`, no tokens/PII in logs (§5, §2) |
| CSRF | State-changing routes use same-site cookies or a token check, not just a GET link |
| Vulnerable dependencies | `npm audit` clean (or documented, accepted risk) before a milestone/entrega, not ignored |
| Security misconfiguration | Default-deny rules (§3, §6), no debug/verbose error responses leaking stack traces in production |
| Rate limiting | Login, password reset, and any expensive/abusable endpoint has basic throttling, even naive |

## 8. Applying this in practice

When asked to review or write security-sensitive code under this skill:
1. Identify the roles that can reach the code path and what each should/shouldn't be able to do (§1, §3).
2. Verify the real check happens server-side, not just in a component's conditional render.
3. Check every external input has schema validation before it touches a query or a write (§4).
4. Grep for `NEXT_PUBLIC_` near anything that looks like a secret, and check `.gitignore` covers `.env*` (§5).
5. If reviewing Firestore/Storage/RLS rules, confirm they don't just require "authenticated" when the server logic requires a specific role/ownership (§6).
6. Report findings by severity (Critical: broken auth/access control or exposed secret · High: missing input validation on a write path · Medium: missing rate limiting/hardening · Low: defense-in-depth suggestions) — don't bury a critical access-control gap under style nitpicks.
