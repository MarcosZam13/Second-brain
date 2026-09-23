---
curso: Seguridad
tema: "Proyecto Final — Organización de módulos sobre Parque Recreativo Mi Pueblo"
fecha: 2026-09-04
tipo: entregable
entregable_de: "[[Cursos/Seguridad/apuntes/proyecto-final-instrucciones]]"
estado: borrador
tags: [proyecto-final, owasp, nist-csf, organizacion, parque-recreativo]
---

# Proyecto Final IC-8071 — Organización de módulos

Ver también: [[Cursos/Seguridad/apuntes/proyecto-final-instrucciones]] · [[Cursos/Seguridad/entregas]]

> Nota: existe un apunte previo sobre este mismo repo en [[Cursos/Seguridad/apuntes/proyecto-final-parque-recreativo]], con una repartición de módulos distinta (Auth+Estadísticas en vez de Auth+Logs/Auditoría) y un skill en `.claude/skills/proyecto-seguridad/`. Este documento es la versión vigente — la reasignación de abajo excluye Estadísticas del alcance y agrega Logs/Auditoría como módulo obligatorio de la rúbrica. Al confirmar con el equipo, conviene decidir si se archiva el apunte viejo o se actualiza para que no queden dos versiones contradictorias.

Repo base: `https://github.com/yarield/ParqueRecreativoMiPueblo.git`, clonado en local en `C:\Users\luisy\Documents\Uni\Seguridad\ParqueRecreativoMiPueblo`. Skill del equipo para Claude Code en `.claude/skills/security-project/SKILL.md` dentro de ese repo (viaja con el repo al hacer `git pull`).

## Hallazgo crítico: el módulo Logs/Auditoría no existe en el código

Confirmado por inspección directa: el repo **no tiene ninguna infraestructura de logging/auditoría** — sin librería tipo winston/pino/morgan en `backend/package.json`, sin tabla de logs en `backend/prisma/schema.prisma`, sin ningún registro de eventos en ningún middleware o ruta. La rúbrica exige Logs/Auditoría como uno de los 4 módulos obligatorios (fijo, no negociable con 4 integrantes), así que **hay que construirlo desde cero**, no solo auditarlo. Encaja con el espíritu del curso: primero se construye/asegura una capa mínima de auditoría, y sobre esa misma capa se demuestra la vulnerabilidad de **Audit Poisoning** (Fase 2, punto 3) y después se remedia (Fase 3).

## Reasignación de módulos — CONFIRMADA con el equipo (2026-09-21)

La rúbrica pide 4 módulos de negocio (Autenticación, Gestión de Usuarios, Operaciones/Transacciones, Logs/Auditoría). Mapeo confirmado contra los módulos reales de la app:

| # | Persona | Módulo de rúbrica | Dominio real de la app |
|---|---|---|---|
| 1 | Rachel | Gestión de Usuarios | Clientes |
| 2 | Wesley | Operaciones/Transacciones (parte 1) | Paquetes + Categorías |
| 3 | Marcos | Operaciones/Transacciones (parte 2) | Facturación |
| 4 | Dereck | Autenticación + Logs/Auditoría | Autenticación (+ construir logging) |

En la reunión del equipo se había propuesto inicialmente "Estadísticas y autenticación" para el cuarto módulo — se corrigió a Logs/Auditoría porque es uno de los 4 módulos fijos de la rúbrica (no negociable) y porque el vector obligatorio de Audit Poisoning (Fase 2, punto 3) depende de que esa capa exista para los 4 integrantes, no solo para Dereck.

**Estadísticas (`estadisticas.routes.ts`) queda fuera del alcance de seguridad de esta entrega** — puede seguir existiendo en el código pero no es módulo de nadie a efectos de la rúbrica.

## Tabla módulo → persona → archivos reales del repo

### Rachel — Clientes

| Capa | Archivos/carpetas |
|---|---|
| Backend | `backend/src/routes/clientes.routes.ts`; validación en `backend/src/schemas/validation.ts` (`clienteCreateSchema`, `clienteUpdateSchema`); modelo `clientes` en `backend/prisma/schema.prisma` |
| Frontend | `frontend/src/pages/ClientesPage.tsx`; `frontend/src/components/clientes/` (`ClientesTable.tsx`, `ClienteFormDialog.tsx`, `ClienteDeleteDialog.tsx`, `ClienteHistorialDialog.tsx`, `clientes.types.ts`); `frontend/src/hooks/useClientes.ts`; `frontend/src/schemas/clientes.schema.ts`; `frontend/src/types/clientes.ts`; `frontend/src/constants/clientes.constants.ts` |

Todos los endpoints (`GET/POST/PUT/DELETE /api/clientes`, más `GET /proximos-a-vencer` y `GET /en-mora`) están detrás de `authMiddleware`. Campo `observaciones` es texto libre — candidato natural a XSS Stored si el frontend lo renderiza sin sanitizar.

### Wesley — Paquetes + Categorías

| Capa | Archivos/carpetas |
|---|---|
| Backend | `backend/src/routes/paquetes.routes.ts`, `backend/src/routes/categorias.routes.ts`; validación en `backend/src/schemas/validation.ts` (`paqueteCreateSchema`/`paqueteUpdateSchema`, `categoriaCreateSchema`/`categoriaUpdateSchema`); modelos `paquetes` y `categorias` |
| Frontend | `frontend/src/pages/PaquetesPage.tsx` (no hay página propia de Categorías — se gestiona embebida ahí); `frontend/src/components/paquetes/` y `frontend/src/components/categorias/` completos; `frontend/src/hooks/usePaquetes.ts`, `useCategorias.ts`; `frontend/src/schemas/paquetes.schema.ts`, `categorias.schema.ts`; `frontend/src/types/paquetes.ts`, `categorias.ts`; `frontend/src/constants/paquetes.constants.ts`, `categorias.constants.ts` |

**Hallazgo de Broken Access Control ya real y gratis:** `GET /api/paquetes`, `GET /api/paquetes/:id`, `GET /api/categorias` y `GET /api/categorias/:id` **no llevan `authMiddleware`** — son de lectura pública sin autenticación, a diferencia de todos los demás módulos. Buen punto de partida para el vector de PoC de servidor (control de acceso, OWASP A01) de esta persona, sin tener que fabricar uno.

### Marcos — Facturación

| Capa | Archivos/carpetas |
|---|---|
| Backend | `backend/src/routes/facturas.routes.ts`; `backend/src/services/facturasExcel.ts` (export a Excel); `backend/src/lib/periodo.ts`; `backend/src/tasks/actualizarEstados.ts` (tarea programada, solo hace `console.log`, no persiste — candidato directo si esta persona también toca auditoría de su propio módulo); validación en `backend/src/schemas/validation.ts` (`facturaSchema`, `facturaExportQuerySchema`); modelo `facturas` |
| Frontend | `frontend/src/pages/FacturasPage.tsx`; `frontend/src/components/facturas/` (`FacturasTable.tsx`, `FacturaFormDialog.tsx`, `FacturaDeleteDialog.tsx`, `FacturaExportDialog.tsx`, `facturas.types.ts`); `frontend/src/hooks/useFacturas.ts`, `useExportarFacturas.ts`; `frontend/src/schemas/facturas.schema.ts`, `facturasExport.schema.ts`; `frontend/src/types/facturas.ts`; `frontend/src/constants/facturas.constants.ts`; `frontend/src/lib/descuentos.ts`, `descargas.ts` |

Los montos se recalculan en servidor (`resolverBase`/`calcularImporte`), pero el ángulo realista de PoC es manipulación de parámetros fuera de rango (`precio_base`, `comision_valor`, `noches`) o CSV/Excel injection con fórmulas (`=...`) en `facturasExcel.ts` si algún campo de texto libre (`origen`) se vuelca sin sanitizar a la celda.

### Dereck — Autenticación + Logs/Auditoría (a construir)

| Capa | Archivos/carpetas |
|---|---|
| Backend | `backend/src/routes/auth.routes.ts`, `backend/src/routes/usuarios.routes.ts`; `backend/src/middlewares/auth.ts`; `backend/src/config/env.ts` (`JWT_SECRET`); modelo `usuarios`. **A crear:** capa mínima de audit logging (middleware + tabla nueva en `schema.prisma`, ej. `logs_auditoria`) — necesaria para tener algo que atacar vía Audit Poisoning y luego remediar |
| Frontend | `frontend/src/pages/LoginPage.tsx`, `RegisterPage.tsx`; `frontend/src/components/auth/` (`LoginForm.tsx`, `RegisterForm.tsx`); `frontend/src/context/AuthContext.tsx`; `frontend/src/router/ProtectedRoute.tsx`; `frontend/src/schemas/auth.schema.ts`; `frontend/src/types/auth.ts`; `frontend/src/constants/auth.constants.ts` |

**Hallazgos ya reales:**
- `POST /api/auth/register` solo exige estar autenticado (`authMiddleware`), sin ningún chequeo de rol — el modelo `usuarios` no tiene campo `rol`. Cualquier usuario logueado puede crear otras cuentas con los mismos privilegios (Broken Access Control, OWASP A01).
- El JWT se guarda en `localStorage` (`AuthContext.tsx`, líneas `login()`/`logout()`), no en cookie `HttpOnly` — cualquier XSS en cualquier otro módulo compromete la sesión completa del sistema.

### Fuera de alcance

`backend/src/routes/estadisticas.routes.ts`, `frontend/src/pages/EstadisticasPage.tsx`, `frontend/src/components/estadisticas/`, `frontend/src/hooks/useEstadisticas.ts` — puede seguir existiendo en el código pero no es módulo de nadie en esta entrega.

### Infraestructura compartida (no es de una sola persona)

`backend/src/server.ts`, `backend/src/lib/prisma.ts`, `backend/src/middlewares/errorHandler.ts`, `backend/src/middlewares/validate.ts`, `backend/src/schemas/validation.ts` (agrupa todos los schemas Zod); en frontend: `components/ui/`, `components/layout/`, `components/common/`, `lib/api.ts`, `lib/utils.ts`. Quien toque estos archivos para su parche debe avisar al resto porque afectan a todos los módulos.

## Checklist de las 3 fases por persona

### Fase 1 — Mapeo NIST CSF 2.0 + Matriz de Gobernanza (20 pts)

- [ ] Rachel (Clientes) — activos críticos (PII: cédula, teléfono, observaciones), funciones GOVERN/IDENTIFY/PROTECT/DETECT, subcategorías (ej. `PR.AA-01` control de acceso, `PR.DS-01` protección de datos en reposo), control de línea base faltante, riesgo inherente Alto/Medio/Bajo
- [ ] Wesley (Paquetes + Categorías) — mismo formato; activo crítico incluye el hallazgo de endpoints GET sin auth
- [ ] Marcos (Facturación) — mismo formato; activo crítico son los montos/comisiones y el archivo Excel exportado
- [ ] Dereck (Auth + Logs) — mismo formato; activo crítico `password_hash`, `JWT_SECRET`, token en `localStorage`; `DE.CM-01` (monitoreo continuo) con riesgo Alto por ausencia total de logging
- [ ] Consolidar las 4 filas en una sola Matriz General de Gobernanza coherente

### Fase 2 — 3 PoCs obligatorias por persona (30 pts)

Cada persona necesita, sobre su propio módulo:
- [ ] **Servidor:** Inyección SQL/Command Injection (OWASP A03) o escalación de privilegios vía Broken Access Control (OWASP A01) / JWT
- [ ] **Cliente:** XSS Stored/Reflected (OWASP A03) para robo de sesión/DOM
- [ ] **Alteración de entrada + detección:** CSRF/manipulación de parámetros HTTP (OWASP A08) + **Audit Poisoning** sobre el logging de la Persona 4 (o el que cada quien construya para su propio módulo)

Cada PoC necesita payload/código, pasos reproducibles y evidencia — no alcanza con describir la vulnerabilidad en prosa.

### Fase 3 — Remediación + Reporte Técnico de Parches (20 pts) + Matriz de Riesgo Residual (10 pts) + Video (20 pts)

- [ ] Implementar el parche en rama propia, con commits propios (trazabilidad Git individual)
- [ ] Reporte Técnico de Parches, 4 secciones fijas en este orden:
  1. Ficha de trazabilidad Git (estudiante, módulo, enlace a PR, ID de commits, rama)
  2. Mapeo vulnerabilidad ↔ parche (categoría OWASP, subcategoría NIST CSF, archivos/líneas afectados)
  3. Diff antes/después (`git diff` real, no descripción en prosa)
  4. Verificación de no-reincidencia (re-correr la PoC de Fase 2 contra el código parchado)
- [ ] Actualizar la fila del módulo en la Matriz de Riesgo Residual (escala Alto-Crítico/Medio/Bajo)
- [ ] Video individual, máx. 5 min, **100% IDE/repositorio** explicando línea por línea — **cualquier diapositiva o teoría = nota 0 en ese rubro**, sin excepción

## Entrega final

**Un solo documento consolidado del equipo** con las 4 matrices/reportes unidos — no se aceptan documentos separados por persona. Los videos sí pueden subirse por separado (uno por integrante, máx. 5 min c/u). Fecha límite: 9 de noviembre 2026, 8:00pm.
