# GymBase

**Repo:** https://github.com/MarcosZam13/Gymbase (privado)
**Demo:** https://demogymbase.vercel.app (cliente: `iron-gym`)

Esta nota es solo contexto general para orientarme rápido si mencionás GymBase en una conversación — **el repo completo no vive acá a propósito** (es grande y ya tiene su propio contexto técnico mantenido adentro, ver abajo). Si necesitás que trabaje directo en el código, es en el repo, no en el vault.

## Qué es

GymBase es una instancia vertical de **MemberBase**, una plataforma SaaS white-label multi-tenant para gimnasios y dojos de artes marciales. Un mismo código base sirve a distintos clientes (gyms) vía feature flags y theming por cliente — no es un gym individual, es el producto que varios gyms podrían usar.

Dos perfiles de cliente soportados:
- **Gym de fitness** (ej. Iron Gym CR — demo activa): check-in por QR, rutinas, métricas de salud (InBody/cinta/báscula), retos, marketplace.
- **Dojo de artes marciales** (ej. Zenith Club): asistencia por clase, rangos por disciplina (BJJ, Muay Thai, etc.), franjas, fight record, sparring con rivalidades, torneos con brackets, eventos de ascenso con rúbrica.

## Stack

Next.js 16 (App Router, TypeScript strict) · Supabase (Postgres 17 + Auth + Storage + RLS) · Tailwind CSS v4 + shadcn/ui · Framer Motion · React Hook Form + Zod v4 · monorepo pnpm + Turborepo · PWA instalable.

## Estado (al 2026-06-14, según el propio repo)

Prácticamente todos los módulos principales están completos: miembros, pagos/suscripciones, rutinas, calendario, comunidad, contenido, retos, inventario, marketplace, contabilidad, salud/progreso, rangos, fight record, torneos, notificaciones multicanal (campanita + email + push), design system, PWA. Pendiente: configuración de Google OAuth en Cloud Console (código ya listo), contenido real de la página del dojo por cliente.

## Dónde está el contexto técnico real

Dentro del propio repo, no acá — así no queda desactualizado en dos lugares:
- `Context/_CONTEXTO-IA.md` — arquitectura, stack, patrones de auth/multi-tenancy/server actions, feature flags, tablas de Supabase, rutas completas.
- `Context/_ESTADO-ACTUAL.md` — estado módulo por módulo, config de producción, variables de entorno.
- `Context/ONBOARDING-NUEVO-GYM.md`, `Context/ARQUITECTURA-MULTI-GYM-USUARIOS.md`, `Context/ROADMAP-V*.md` — para onboarding de un cliente nuevo, arquitectura multi-gym, y roadmaps por versión.

No tiene README todavía a nivel de repo — si en algún momento se arma uno, esta nota se puede achicar a solo el link.
