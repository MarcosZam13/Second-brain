---
curso: Seguridad
tema: "Proyecto Final — Organización y kit de entrega sobre Parque Recreativo Mi Pueblo"
fecha: 2026-09-04
tipo: apunte
fuente:
  - https://github.com/yarield/ParqueRecreativoMiPueblo
  - apuntes/proyecto-final-instrucciones.md
tags: [proyecto-final, owasp, nist-csf, organizacion, parque-recreativo]
---

# Proyecto Final IC-8071 — Organización y kit de entrega, Parque Recreativo Mi Pueblo

Ver también: [[Cursos/Seguridad/apuntes/proyecto-final-instrucciones|Instrucciones y rúbrica completa]] · [[Cursos/Seguridad/entregas]]

Repo base: `https://github.com/yarield/ParqueRecreativoMiPueblo.git`, clonado en local en `C:\Users\luisy\Documents\Uni\Seguridad\ParqueRecreativoMiPueblo`. Skill del proyecto para IA en `.claude/skills/security-project/SKILL.md` dentro de ese repo (compartir esa carpeta `.claude/` junto con este documento — ver bloqueo de acceso más abajo, hoy solo vive en la compu de Marcos).

**Este documento es progresivo, como el curso**: no hace falta hacer todo ahora. La sección 3 marca qué le toca a cada quien empezar a mirar ya (Fase 1) y qué se deja para más adelante (Fase 2/3), aunque la entrega es una sola, el 9 de noviembre.

## 1. Qué es la app real

Sistema de gestión de un parque recreativo: clientes, paquetes (con categorías), facturación, estadísticas y autenticación. Stack: **frontend** React 19 + TypeScript + Vite + Tailwind + shadcn/ui + React Hook Form + Zod + TanStack Query; **backend** Node + Express + TypeScript + **Prisma ORM** sobre Postgres.

Es una app limpia y razonablemente bien construida (Zod en cada input, Prisma parametrizado — no hay SQL crudo en ningún lado, bcrypt + JWT, rate limiting en login). Esto es importante: **no va a haber SQLi clásico por concatenación de strings para "encontrar"** — los 3 vectores obligatorios de la rúbrica hay que construirlos activamente (PoC bien documentada, no solo "encontrar" un bug regalado), salvo los 2 hallazgos de abajo que sí son reales y gratis.

## 2. Hallazgos de control de acceso ya reales (no hace falta inventarlos)

1. **`POST /api/auth/register`** (`backend/src/routes/auth.routes.ts:22`) solo exige estar autenticado, **no exige ningún rol de admin** — el modelo `usuarios` no tiene campo de rol. Cualquier usuario logueado (aunque sea uno recién creado) puede crear otras cuentas con los mismos privilegios. Broken Access Control real (OWASP A01), buen punto de partida gratis para la PoC de escalación del módulo de Autenticación.
2. **Los `GET` de `paquetes` y `categorias`** (`/` y `/:id`) no tienen `authMiddleware`, a diferencia de todo lo demás en esos mismos archivos (POST/PUT/DELETE sí lo tienen). Puede ser intencional (catálogo público de precios) o un descuido — vale la pena que quien tome ese módulo lo confirme con el resto antes de tratarlo como vulnerabilidad, pero es un hallazgo real de todos modos.

## 3. Mapeo: módulos de la rúbrica ↔ módulos reales de la app ↔ equipo

La rúbrica pide 4 módulos (Autenticación, Gestión de Usuarios, Operaciones/Transacciones, Logs/Auditoría — ver [[Cursos/Seguridad/apuntes/proyecto-final-instrucciones|instrucciones]]). El equipo reparte 4 personas sobre los módulos reales de la app: Clientes, Paquetes+Categorías, Facturación, Autenticación+Estadísticas.

| Persona | Módulo real | Módulo(s) de rúbrica que cubre | Backend | Frontend |
|---|---|---|---|---|
| **1** (¿Marcos?) | Autenticación + Estadísticas | Autenticación — y de facto **Gestión de Usuarios**, porque `usuarios.routes.ts` no distingue roles | `routes/auth.routes.ts`, `routes/usuarios.routes.ts`, `middlewares/auth.ts`, `routes/estadisticas.routes.ts`, `config/env.ts` | `context/AuthContext.tsx`, `router/ProtectedRoute.tsx`, páginas de login/registro/dashboard |
| **2** | Clientes | Gestión de Usuarios (la rúbrica lo llama así, pero en esta app los "usuarios del sistema" gestionados son los *clientes* del parque, no los `usuarios` internos) | `routes/clientes.routes.ts`, schemas `cliente*` | `pages/ClientesPage.tsx`, `components/clientes/`, `hooks/useClientes.ts` |
| **3** | Paquetes + Categorías | Operaciones/Transacciones | `routes/paquetes.routes.ts`, `routes/categorias.routes.ts` | `pages/PaquetesPage.tsx` (categorías se gestionan embebidas ahí, no hay página propia), `components/paquetes/`, `components/categorias/` |
| **4** | Facturación | Operaciones/Transacciones + parte de **Logs/Auditoría** (ver nota abajo) | `routes/facturas.routes.ts`, `services/facturasExcel.ts`, `lib/periodo.ts`, `tasks/actualizarEstados.ts` | `pages/FacturasPage.tsx`, `components/facturas/`, `hooks/useFacturas.ts`/`useExportarFacturas.ts` |

Fuera de alcance de los 4 módulos: `estadisticas.routes.ts`/`EstadisticasPage` no es módulo de nadie en esta entrega (queda como referencia colgada del módulo de Auth, ver skill).

Infraestructura compartida (avisar al equipo antes de tocarla, afecta a todos): `server.ts`, `lib/prisma.ts`, `middlewares/errorHandler.ts`, `middlewares/validate.ts`, `schemas/validation.ts`, `components/ui/`, `lib/api.ts`.

**Nota — Logs/Auditoría no existe en la app:** no hay tabla ni middleware de auditoría en ningún lado del repo. La rúbrica exige el vector "Audit Poisoning" (Fase 2, punto 3) **por cada módulo individual**, no como un 5to módulo separado — así que **cada integrante necesita agregar su propio logging mínimo a su módulo** antes de poder atacarlo y luego defenderlo. Sugerencia: unificar el formato de log entre los 4 (mismo shape de evento) para que la Matriz de Gobernanza quede coherente — coordinarlo en la primera reunión de equipo, antes de que cada quien construya el suyo por separado.

## 4. Las piezas de entrega — qué es cada "ficha" y cuándo hace falta

La entrega es **una sola**, el 9 de noviembre 8pm, pero son 5 piezas distintas (100 pts). No hay que dejarlas para el final — la 1 y la 2 dependen una de la otra, y la 3/4/5 dependen de que la 2 (PoC) ya exista. Plantillas de ejemplo de la profesora, todas en `_fuentes/` del vault:

| # | Pieza | Pts | Cuándo empezar | Plantilla de referencia |
|---|---|---|---|---|
| 1 | **Matriz General de Gobernanza del Sistema** — 1 fila por módulo, mapeo a NIST CSF 2.0 (GOVERN/IDENTIFY/PROTECT/DETECT), activos críticos, control de línea base | 20 | **Ahora** — es la base de todo lo demás, y solo necesita leer el código, no atacarlo | `Seguridad_proyecto-final-matriz-gobernanza-ejemplo_2026-08-24.xlsx` |
| 2 | **Documento de PoCs estandarizado** — 3 PoCs por persona (servidor, cliente, alteración+detección), reproducibles paso a paso | 30 | Después de tener la Matriz de Gobernanza de tu módulo — necesitás saber qué activos/controles existen antes de atacarlos | `Seguridad_proyecto-final-ejemplo-poc-audit-poisoning_2026-08-24.docx` (ejemplo trabajado completo) |
| 3 | **Matriz de Riesgos NIST CSF Consolidada** — igual formato que la de Gobernanza + riesgo inicial/post-parche/estado final | 10 | Después de tener el parche (pieza 5) — necesitás el resultado del parche para calificar el riesgo residual | `Seguridad_proyecto-final-matriz-riesgo-residual-ejemplo_2026-08-24.xlsx` |
| 4 | **Reporte Técnico de Parches** — 4 secciones fijas, una **"Ficha del integrante y trazabilidad de Git"** por persona (estudiante, módulo, PR, commits, rama) + mapeo de vulnerabilidad + diff antes/después + verificación de no-reincidencia | 20 | Al mismo tiempo que el parche (pieza 5) — la ficha se llena con datos reales del PR/commits, no se puede simular | `Seguridad_proyecto-final-plantilla-reporte-parches_2026-08-24.docx` |
| 5 | **Video de demo individual** (≤5 min, 100% IDE/repo explicando línea por línea) | 20 | Al final, cuando el parche de tu módulo ya está mergeado — **regla estricta: diapositivas o lectura de documento = nota 0 automática** | — (sin plantilla, es grabación) |

La "ficha" que preguntaste es la pieza 4 — no es un documento aparte, es la primera de las 4 secciones fijas del Reporte Técnico de Parches, una por persona.

## 5. Bloqueo real — resolver antes de la pieza 4 y 5

El repo es de **yarield**, no del equipo — hoy solo hay acceso de **lectura**. La pieza 4 (Reporte de Parches) exige **trazabilidad de Git real** (enlace al PR, IDs de commit, rama) y la pieza 5 exige mostrar el código parcheado en el propio IDE/repo — **ninguna de las dos se puede cumplir sin poder hacer push**.

Antes de llegar a Fase 3 (parches), el equipo tiene que resolver uno de estos dos caminos:
- **Fork del repo** a la cuenta de alguien del equipo (o a una org compartida) — cada quien trabaja/parchea sobre ese fork, con sus propios PRs/commits.
- **Pedirle a yarield** que agregue a los 4 integrantes como colaboradores del repo original.

No urge resolverlo hoy (Fase 1 y 2 no necesitan escribir código todavía, solo leerlo), pero si se deja para último momento va a bloquear justo las piezas que más puntos valen (20+20 = 40 pts entre Reporte de Parches y Video).

## 6. Cómo levantar el repo en local

`backend/.env.example` → copiar a `.env` (requiere Postgres corriendo); `npx prisma migrate dev` + `npx prisma db seed`; confirmar que tu módulo carga antes de intentar nada de seguridad sobre él.

## 7. Vectores de PoC sugeridos por módulo (punto de partida, no obligatorio usar exactamente estos)

- **Autenticación/Usuarios:** servidor → el `register` sin control de rol (sección 2). Cliente → el JWT se guarda en `localStorage` (`AuthContext.tsx`), así que un XSS en **cualquier otro módulo** permite robar la sesión completa (no hay cookie `HttpOnly`). Alteración/detección → logging de intentos de login fallidos/registro, luego mostrar cómo se puede poisonear.
- **Clientes:** servidor → confirmar que Zod bloquea Mass Assignment en `PUT /api/clientes/:id` como parte de la línea base de controles. Cliente → si `observaciones` (texto libre) se renderiza sin escape, candidato a XSS Stored.
- **Paquetes/Categorías:** servidor → `DELETE` de una categoría/paquete sin validar si tiene paquetes/facturas asociadas (revisar si Prisma lo previene por FK o si hay que probarlo), más el hallazgo de GETs sin auth (sección 2). Cliente → XSS en `descripcion` de categorías si se renderiza sin sanitizar.
- **Facturación:** servidor → los montos se recalculan en servidor (`resolverBase`/`resolverMonto` en `facturas.routes.ts`, bien hecho) — el ángulo más realista es manipulación de `precio_base`/`comision_valor` fuera de rango, o CSV/Excel injection con fórmulas `=` en el export (`facturasExcel.ts`). Auditoría → `actualizarEstados.ts` solo hace `console.log`, no persiste nada — candidato directo para implementar logging real y luego atacarlo.

## 8. Siguientes pasos para el equipo

1. Repartir formalmente los 4 módulos de la tabla (reemplazar los placeholders "Persona 2/3/4").
2. Resolver el acceso al repo (sección 5) — no bloquea hoy, sí bloquea antes de Fase 3.
3. Primera reunión: acordar el formato común de logging de auditoría (para que la Matriz de Gobernanza quede coherente entre los 4).
4. Cada quien levanta el repo en local (sección 6) y confirma que su módulo corre.
5. Usar el skill del proyecto (`.claude/skills/security-project/SKILL.md`) para generar la Matriz de Gobernanza (pieza 1) de cada módulo — mismo formato entre los 4, sin releer el PDF completo cada vez.
