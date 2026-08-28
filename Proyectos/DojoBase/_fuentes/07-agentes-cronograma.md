# Spec Dojo — Sección 7: Agentes y cronograma de trabajo (8 semanas)

## Modelo de trabajo: 1 orquestador + subagentes de contexto acotado

Un solo agente (el orquestador, sesión principal de Claude Code) mantiene el contexto completo del proyecto — este documento, el schema, las decisiones ya tomadas — y delega tareas puntuales a subagentes que reciben solo lo que necesitan para esa tarea específica, no el historial completo. Esto es lo que evita saturar ventanas de contexto y lo que ya identificaste como el problema de fondo del vibe coding.

## Los 5 agentes

### 1. Agente Orquestador
- **Contexto que mantiene**: los 6 documentos de spec completos (arquitectura, schema, RLS, theming, notificaciones, requerimientos), el estado del monorepo, decisiones ya tomadas.
- **Responsabilidad**: planifica el trabajo de cada semana, redacta el prompt específico para cada subagente con solo la porción de spec relevante, revisa el output antes de integrarlo.
- **No programa directamente** — delega y revisa. Esto es lo que preserva su ventana de contexto larga.

### 2. Agente de Desarrollo UI/Componentes
- **Contexto por tarea**: la sección 4 (theming) + el contrato de `packages/ui` + la historia de usuario específica que está implementando (no todas las 23 a la vez).
- **Responsabilidad**: construir componentes de `packages/ui`, pantallas de `apps/dojo`, siempre con Tailwind + variables de tema, nunca hex hardcodeado (regla de lint ya definida en sección 4).
- **Entregable por tarea**: componente + verificación visual con al menos 2 temas distintos (para confirmar que el theming realmente funciona, no solo con los colores de Dojo Shoto).

### 3. Agente de Documentación
- **Contexto por tarea**: el código recién escrito por el agente de UI o el que toque esa semana.
- **Responsabilidad**: mantener actualizado un `CLAUDE.md` por paquete/app (igual que ya hiciste con Tacha), documentar decisiones de implementación que se desvíen del spec original, generar comentarios de código donde la lógica no sea obvia (especialmente en RLS y en la función de cálculo de promociones).
- **Se ejecuta al cierre de cada tarea**, no en paralelo — documenta lo que ya se construyó, no lo planificado.

### 4. Agente de QA/Testing
- **Contexto por tarea**: la historia de usuario específica + sus RF asociados (ej. para HU-05 a HU-09, los RF-05 a RF-08).
- **Responsabilidad**: escribir tests contra los RF como criterios de aceptación explícitos (ej. "RF-06b: verificar que un sparring `accepted` sin resultado por 14 días pasa a `cancelled`"), no tests genéricos de framework. Prioriza los flujos con estado (sparring, promociones) sobre los CRUD simples.
- **Entregable**: reporte de qué RF están cubiertos y cuáles no, por semana.

### 5. Agente de Seguridad (OWASP 2025)
- **Contexto por tarea**: las policies RLS de la sección 3 + el código de server actions que toque esa semana.
- **Responsabilidad**: revisar contra el modelo OWASP Top 10 2025 con foco en lo que ya es superficie de ataque conocida en este proyecto:
  - **Control de acceso roto**: validar que ninguna mutación de estado (promociones, sparring, finanzas) dependa solo de UI oculta — esto ya quedó como RNF-01, el agente lo verifica en cada PR.
  - **Fallas criptográficas / exposición de datos**: revisar que `financial_summary` y `org_payment_connections` nunca sean alcanzables por `admin`, solo `owner` — es el caso más sensible del proyecto.
  - **Diseño inseguro**: revisar el fix de `push_subscriptions` (que ya tenía el bug de fuga cross-org) esté realmente cerrado con el `org_id` scoping de la sección 3.
  - **Inyección**: cualquier query dinámica en filtros de búsqueda de contenido/clases.
- **Se ejecuta antes de mergear**, no como auditoría final al terminar todo — revisar temprano y seguido, no una vez al final cuando ya es costoso corregir.

## Cronograma de 8 semanas

| Semana | Foco | Agentes principales activos | Entregable |
|---|---|---|---|
| 1 | Setup monorepo + core (auth, JWT, RLS base) | Orquestador, Seguridad | `packages/core` funcional, login con JWT claim de org/rol |
| 2 | Design system + theming dinámico | UI, Documentación | `packages/ui` con tokens, `tenant_themes` cargado con el tema de Dojo Shoto |
| 3 | Disciplinas, rangos, franjas (HU-00, RF-02/02b) | UI, QA | Admin puede crear disciplinas y su escala de rangos completa |
| 4 | Clases y asistencia (HU-01 a HU-04b) | UI, QA, Seguridad | Calendario semanal/mensual, inscripción, cancelación, instructor=admin |
| 5 | Sparring completo (HU-05 a HU-09c) | UI, QA, Seguridad | Reto → aceptación → resultado por rounds → head-to-head → expiración |
| 6 | Promociones + portal del miembro (HU-12 a HU-14, HU-13b) | UI, QA, Seguridad | Flujo completo de evaluación + pantalla nueva de desglose para el miembro |
| 7 | Billing completo (HU-16b a HU-20) + contenido/challenges (HU-15, 15b, 16) | UI, QA, Seguridad | Planes, suscripción, comprobantes, revisión, recordatorios, carpetas de contenido |
| 8 | Peleas oficiales (HU-10, HU-11) + grupos familiares (HU-23) + hardening general | Seguridad, QA, Documentación | Feed de próximas peleas, historial oficial, revisión OWASP completa, `CLAUDE.md` final por paquete |

**Nota de secuencia**: las semanas 3-4 son bloqueantes de casi todo lo posterior (sparring, promociones y peleas dependen de disciplinas/rangos ya existentes) — no conviene adelantar semana 5 en paralelo si la 3 no cerró limpio.

## Manejo de ventanas de contexto (aplicando lo que ya diseñaste para tu Second Brain)

- Cada semana arranca con el Orquestador leyendo solo la(s) sección(es) de spec relevante(s) a esa semana — nunca las 7 secciones completas de una vez.
- Los subagentes de UI/QA/Seguridad reciben prompts armados por el Orquestador con: la HU específica, los RF asociados, y el fragmento de schema/RLS relevante — nunca el documento completo.
- Al cierre de cada semana, el agente de Documentación resume en `CLAUDE.md` lo construido, para que la siguiente semana el Orquestador no necesite releer código, solo el resumen.
