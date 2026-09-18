---
curso: Seguridad
tema: "Proyecto Final — Fase 1: Matriz General de Gobernanza del Sistema (borrador)"
fecha: 2026-09-17
tipo: entregable
entregable_de: "[[Cursos/Seguridad/apuntes/proyecto-final-instrucciones]]"
estado: borrador
tags: [proyecto-final, fase-1, nist-csf, gobernanza]
---

# Fase 1 — Matriz General de Gobernanza del Sistema (borrador)

Ver también: [[Cursos/Seguridad/entregables/proyecto-final-organizacion]] · [[Cursos/Seguridad/apuntes/proyecto-final-instrucciones]] · [[Cursos/Seguridad/entregas]]

> Generado antes de la sesión de equipo del domingo 2026-09-20, a partir de los hallazgos ya confirmados por inspección del repo en [[Cursos/Seguridad/entregables/proyecto-final-organizacion]]. **No reemplaza la sesión** — la reasignación de módulos de esa nota sigue "pendiente de confirmar con el equipo", así que las filas de abajo son el punto de partida para que cada persona verifique/ajuste su fila, no la versión final. Columnas según la plantilla oficial de la profesora (`_fuentes/Seguridad_proyecto-final-matriz-gobernanza-ejemplo_2026-08-24.xlsx`).

## Matriz

| Módulo y Responsable | Activo Crítico | Función NIST CSF | Categoría/Subcategoría NIST CSF | Control de Seguridad Requerido (línea base) | Nivel de Riesgo Inherente |
|---|---|---|---|---|---|
| **Gestión de Usuarios** (Clientes) — Persona 1 | PII de clientes: cédula, teléfono, `observaciones` (texto libre) | PROTECT / DETECT | `PR.DS-01` (protección de datos en reposo), `PR.AA-01` (control de acceso) | Sanitización de `observaciones` antes de render (anti-XSS Stored); cifrado/enmascarado de PII en reposo | **Alto** — `observaciones` se renderiza sin sanitizar; candidato directo a XSS Stored |
| **Operaciones/Transacciones — parte 1** (Paquetes + Categorías) — Persona 2 | Catálogo de paquetes/categorías y su disponibilidad | PROTECT / GOVERN | `PR.AA-01` (control de acceso) | `authMiddleware` en todos los endpoints de lectura, no solo escritura | **Alto** — `GET /api/paquetes`, `GET /api/paquetes/:id`, `GET /api/categorias`, `GET /api/categorias/:id` son públicos sin auth, a diferencia del resto del sistema (Broken Access Control, OWASP A01) |
| **Operaciones/Transacciones — parte 2** (Facturación) — **Marcos, confirmado 2026-09-17** | Montos, comisiones, archivo Excel exportado (`facturasExcel.ts`) | PROTECT / IDENTIFY | `PR.DS-01` (integridad de datos), `ID.RA-01` (identificación de vulnerabilidades) | Tope superior en `precio_base` para paquetes de precio abierto (hoy solo se rechaza `<= 0`, no hay máximo) | **Bajo-Medio** — verificado 2026-09-17: el servidor sí clampea `descuento_monto`/`comisión_valor`, y la exportación a Excel vía ExcelJS NO es explotable como CSV/Excel injection (celda queda como texto, no fórmula — ver [[Cursos/Seguridad/entregables/proyecto-final-facturacion-marcos]] para la prueba). Dos de los tres ángulos originales de esta fila quedaron descartados; ver esa nota para los 3 vectores de PoC reales a construir en Fase 2. |
| **Autenticación + Logs/Auditoría** — Persona 4 | `password_hash`, `JWT_SECRET`, token JWT (vive en `localStorage`) | GOVERN / PROTECT / DETECT | `PR.AA-01` (autenticación de identidades), `DE.CM-01` (monitoreo continuo) | Rol/permiso en `POST /api/auth/register`; JWT en cookie `HttpOnly`/`SameSite` en vez de `localStorage`; capa mínima de audit logging (no existe hoy) | **Crítico** — `register` no exige rol (cualquier usuario autenticado crea cuentas), JWT expuesto a robo vía XSS de cualquier módulo, y `DE.CM-01` en riesgo Alto por ausencia total de logging/auditoría en el repo |

## Pendiente de confirmar en la sesión del domingo (2026-09-20)

- [x] Persona 3 (Facturación) = Marcos, confirmado 2026-09-17
- [ ] Quién es cada una de las otras 3 Personas — la asignación de arriba es la propuesta de [[Cursos/Seguridad/entregables/proyecto-final-organizacion]], no una decisión tomada por el resto del equipo
- [ ] Si se mantiene esta reasignación (Auth+Logs en vez de Auth+Estadísticas) o se vuelve a la versión vieja de [[Cursos/Seguridad/apuntes/proyecto-final-parque-recreativo]] — de mantenerse esta, archivar la nota vieja para no dejar dos versiones contradictorias
- [ ] Revisar/ajustar cada fila con quien termine dueño del módulo — esta matriz asume los hallazgos técnicos ya confirmados, pero el Riesgo Inherente y el Control requerido son punto de partida, no palabra final
- [ ] Consolidar esta tabla dentro del documento único de equipo cuando se arme (no se entrega como archivo separado — ver instrucciones)
