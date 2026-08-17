---
curso: QA
tema: Mapeo de módulos — Firefly III
fecha: 2026-08-17
tipo: entregable
entregable_de: "[[Cursos/QA/entregables/seleccion-repositorio-proyecto]]"
estado: borrador
tags: [proyecto, firefly-iii, mapeo-modulos, fase2, plan-de-pruebas]
---

# Mapeo de módulos — Firefly III

Ver también: [[Cursos/QA/entregables/seleccion-repositorio-proyecto|Selección de repositorio]] · [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]] · [[Cursos/QA/entregas]]

**Objetivo de esta nota:** listar los módulos reales de Firefly III (verificados contra el código fuente del repo, no solo la descripción de marketing) como insumo directo para el Plan del proyecto (Fase 1) y, más adelante, para diseñar los ≥60 casos de prueba de la Fase 2.

**Fuente:** estructura de controladores en `app/Http/Controllers/` y rutas en `routes/api.php` del repo [firefly-iii/firefly-iii](https://github.com/firefly-iii/firefly-iii), verificado en vivo el 2026-08-17 vía GitHub API — no es solo el README.

## Módulos y su relevancia para pruebas

| Módulo                                                     | Qué hace                                                                                                   | Por qué importa para QA                                                                                                                                                |
| ---------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Account** (Cuentas)                                      | CRUD de cuentas: activo (banco), pasivo (deuda), gasto, ingreso                                            | Base de todo lo demás — casi ningún otro módulo funciona sin cuentas válidas. Buen candidato para casos de valores límite (saldo negativo, cuenta sin moneda asignada) |
| **Transaction** (Transacciones)                            | Withdrawal (gasto), deposit (ingreso), transfer (entre cuentas propias)                                    | El corazón del sistema — reglas de negocio de cálculo de saldo, doble entrada contable (double-entry bookkeeping). Alta densidad de casos de prueba esperada           |
| **Budget** (Presupuestos)                                  | Límites de gasto por período y categoría                                                                   | Lógica de cálculo (gastado vs. disponible), casos de prueba de fechas/períodos                                                                                         |
| **Category** (Categorías)                                  | Etiquetar transacciones por tipo de gasto/ingreso                                                          | CRUD simple, útil para casos de filtrado/reportes                                                                                                                      |
| **Bill** (Facturas/suscripciones)                          | Gastos recurrentes esperados (ej. streaming, alquiler) con matching automático contra transacciones reales | Lógica de "match" automático — buen caso para pruebas de reglas/patrones                                                                                               |
| **Recurring** (Transacciones recurrentes)                  | Automatiza la creación de transacciones repetidas                                                          | Depende de fechas/cron — bueno para pruebas de programación temporal                                                                                                   |
| **Rule / RuleGroup** (Reglas)                              | Reglas "si-entonces" definidas por el usuario para clasificar transacciones automáticamente                | Lógica condicional compleja, ideal para pruebas de múltiples combinaciones de condiciones                                                                              |
| **PiggyBank** (Metas de ahorro)                            | Ahorro progresivo hacia una meta con fecha objetivo                                                        | Cálculos de progreso, fechas límite                                                                                                                                    |
| **TransactionCurrency**                                    | Soporte multi-moneda, tasas de cambio                                                                      | Pruebas de conversión numérica, redondeo, precisión decimal                                                                                                            |
| **ExchangeRates**                                          | Tasas de cambio entre monedas                                                                              | Datos externos/calculados — casos de prueba de valores inválidos o desactualizados                                                                                     |
| **Tag**                                                    | Etiquetas libres sobre transacciones                                                                       | CRUD simple, filtrado                                                                                                                                                  |
| **Report** / **Chart**                                     | Reportes financieros y gráficos agregados                                                                  | Pruebas de agregación de datos — ¿los totales cuadran contra las transacciones individuales?                                                                           |
| **Auth**                                                   | Login, registro, recuperación de contraseña                                                                | Cumple el criterio 4 (login/autenticación) del curso — casos clásicos de auth (credenciales inválidas, fuerza bruta, sesión expirada)                                  |
| **Profile**                                                | Perfil de usuario, cambio de contraseña, **2FA**, exportar/borrar cuenta                                   | 2FA da casos de prueba de seguridad; borrar cuenta da casos de prueba destructivos/irreversibles                                                                       |
| **UserGroup**                                              | Multi-usuario / grupos compartidos de finanzas                                                             | Casos de prueba de permisos y aislamiento de datos entre usuarios                                                                                                      |
| **Admin** / **System**                                     | Administración del sistema, información de versión/salud                                                   | Menor prioridad para el alcance del curso — más orientado a mantenimiento que a flujos de usuario final                                                                |
| **Export**                                                 | Exportar datos financieros                                                                                 | Pruebas de integridad de datos exportados                                                                                                                              |
| **Webhooks**                                               | Notificaciones salientes a URLs externas cuando ocurre un evento                                           | Requiere mockear un endpoint externo — más complejo de automatizar, evaluar si entra en alcance                                                                        |
| **Popup** / **Preferences** / **ObjectGroup** / **Search** | Utilidades de soporte (preferencias de UI, agrupación de piggy banks/bills, búsqueda)                      | Menor prioridad — funcionalidad secundaria, no crítica para el negocio                                                                                                 |
|                                                            |                                                                                                            |                                                                                                                                                                        |

## Priorización sugerida para el Plan de pruebas (Fase 2)

**Alta prioridad** (cubren autenticación + el flujo financiero central, exigido por los criterios del curso):
Auth, Profile (2FA), Account, Transaction, Budget, Category.

**Media prioridad** (lógica de negocio adicional, buena fuente de casos con reglas/condiciones):
Bill, Recurring, Rule/RuleGroup, PiggyBank, TransactionCurrency.

**Baja prioridad / evaluar si entra en alcance** (soporte, no flujo crítico, o requiere mocks externos):
Report/Chart, Tag, UserGroup, Admin/System, Export, Webhooks, Popup/Preferences/ObjectGroup/Search.

Con Auth + Profile + Account + Transaction + Budget + Category ya hay superficie de sobra para los ≥60 casos de prueba exigidos, combinando pruebas positivas, negativas y de valores límite — sin necesidad de tocar los módulos de baja prioridad a menos que sobre tiempo.

## Pendiente

- [ ] Clonar el repo y confirmar localmente que cada módulo de alta prioridad es alcanzable (login funcional, se pueden crear cuentas/transacciones de prueba)
- [ ] Revisar `routes/api.php` en detalle para confirmar qué endpoints de la API pública existen por módulo (insumo para pruebas automatizadas vía API, no solo UI)
- [ ] Con el equipo, confirmar qué módulos de media/baja prioridad entran en el alcance final del Plan de pruebas
