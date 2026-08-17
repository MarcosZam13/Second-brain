---
curso: QA
tema: Selección de repositorio — candidatos evaluados
fecha: 2026-08-15
tipo: entregable
entregable_de: "[[Cursos/QA/apuntes/criterios-seleccion-repositorio-github]]"
estado: borrador
tags: [proyecto, seleccion-repositorio, github, fase1]
---

# Selección de repositorio — candidatos evaluados

Ver también: [[Cursos/QA/apuntes/criterios-seleccion-repositorio-github|Criterios para Seleccionar Proyectos en GitHub]] · [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]] · [[Cursos/QA/entregables/diario-reflexivo|Diario Reflexivo del Proyecto]] · [[Cursos/QA/entregas]]

**Estado:** exploración inicial hecha con Claude Code (`gh` CLI + GitHub API), verificando datos en vivo el 2026-08-15. **Decisión final del equipo (2026-08-17): [firefly-iii/firefly-iii](https://github.com/firefly-iii/firefly-iii).**

## Metodología

Se consultó la API de GitHub (estrellas, forks, issues abiertos, `pushedAt`, tamaño del repo, licencia, commits recientes y top contribuidores) para varios candidatos conocidos de código abierto que encajan con las tecnologías sugeridas por el profesor (React/Angular/Vue, Django/Flask, Spring Boot, Rails, Laravel). No se verificó en detalle cada criterio (ej. accesibilidad WCAG puntual, ESLint/PEP8 exacto) — eso requiere clonar y revisar el repo elegido antes de comprometerse.

## Candidatos recomendados

| Repo | Stack | ⭐ Stars | Forks | Issues abiertos | Último push | Auth | Docker | Notas |
|---|---|---|---|---|---|---|---|---|
| **[documenso/documenso](https://github.com/documenso/documenso)** | Next.js/TypeScript (React) + Prisma/Postgres | 14,484 | 3,061 | 253 | 2026-08-15 (mismo día) | Login/registro + 2FA + OAuth (NextAuth) | Sí, con healthcheck documentado | Tamaño moderado (repo único, no monorepo gigante), commit reciente de traducción al polaco → cumple el criterio 9 (múltiples idiomas) de forma concreta. Contribuidores humanos bien repartidos (top 5 entre 273-1145 contribuciones) |
| **[chatwoot/chatwoot](https://github.com/chatwoot/chatwoot)** | Ruby on Rails + Vue | 35,894 | 8,617 | 1,337 | 2026-08-14 | Login de agentes + widget de cliente | Sí | Comunidad enorme y muy activa (PRs mergeados a diario), pero stack local más pesado (Postgres + Redis + Sidekiq) — más setup |
| **[firefly-iii/firefly-iii](https://github.com/firefly-iii/firefly-iii)** | Laravel/PHP + Vue (islas) | 24,322 | 2,250 | 161 | 2026-08-15 (mismo día) | Login/registro + 2FA, también actúa como proveedor OAuth | Sí, `docker-compose` oficial | API documentada con OpenAPI/Swagger. Ojo: el mantenimiento está muy concentrado en un solo desarrollador (20,800 commits vs. 131 del siguiente humano) — la comunidad de PRs es menor que en los otros dos |

## ¿De qué se trata cada uno?

- **Documenso** — alternativa open source a DocuSign. Se sube un PDF, se marcan dónde van las firmas/campos, se envía a los firmantes por correo, y ellos firman desde el navegador (con verificación de identidad). Tiene dashboard de documentos, plantillas reutilizables, auditoría de quién firmó y cuándo, y API para integrarlo con otros sistemas.
- **Chatwoot** — plataforma de atención al cliente omnicanal, alternativa a Intercom/Zendesk/Salesforce Service Cloud. Centraliza en una sola bandeja los mensajes que llegan por chat en vivo (widget embebido en una web), correo, WhatsApp, Facebook, Instagram, etc. Los agentes responden desde ahí, se pueden asignar conversaciones, usar respuestas automáticas/bots, y ver reportes de tiempos de respuesta.
- **Firefly III** — gestor de finanzas personales (tipo Mint/YNAB, pero open source y self-hosted). Se llevan cuentas bancarias, tarjetas, ingresos y gastos categorizados, presupuestos, metas de ahorro, transacciones recurrentes, y genera reportes/gráficos de a dónde se va el dinero.

**Por qué importa para el proyecto de QA — cada uno da flujos distintos para diseñar los ≥60 casos de prueba:**

| Repo | Flujos típicos a probar |
|---|---|
| Documenso | Auth + subida/procesamiento de archivos + firma — bueno para validaciones de estado de documento, permisos, generación de PDFs |
| Chatwoot | Mensajería en tiempo real + multi-canal + roles de agente — bueno para permisos, websockets/realtime, integraciones |
| Firefly III | CRUD financiero con reglas de negocio (cálculos, categorías, presupuestos) — más fácil de probar con datos numéricos, menos dependencias externas (no requiere integrarse con WhatsApp/email como los otros dos) |

Si el equipo prefiere algo más simple de levantar y probar sin depender de servicios externos, **Firefly III** es probablemente el más directo. Si prefieren algo con interfaz más moderna en React, **Documenso**.

## Descartados en la exploración

- **BookStackApp/BookStack** (PHP/Laravel) — la descripción del repo en GitHub dice *"NOW MANAGED ON CODEBERG"* y muestra 0 issues abiertos: el proyecto se mudó de plataforma, así que ya no cumple el criterio 3 (historial de bugs gestionado activamente en GitHub).
- **calcom/cal.com** y **novuhq/novu** — cumplen los criterios técnicos (stack, auth, docs, comunidad enorme) pero son monorepos muy grandes (1.1 GB y ~490 MB, decenas de paquetes) — riesgo alto de fricción para "ejecutar localmente sin problemas" en el tiempo de un proyecto de curso.

## Recomendación

**Documenso** como primera opción: tamaño más manejable que Chatwoot, stack moderno (React/Next.js, cubierto por el criterio 1), auth real y testeable, Docker documentado, actividad reciente verificada el mismo día de esta búsqueda, y el criterio de idiomas (9) queda cubierto de forma explícita. Chatwoot es la alternativa si el equipo prefiere Ruby on Rails o quiere una comunidad todavía más grande. Firefly III es viable pero pesa más el riesgo de "un solo mantenedor" si hace falta interactuar con el proyecto real (ej. reportar algo) — aunque para el propósito del curso (aplicar QA sobre el código ya existente) no debería ser un problema real.

## Pendiente

- [x] Decisión final del equipo — **Firefly III**, 2026-08-17
- [ ] Clonar el repo y confirmar que corre localmente sin problemas (`docker-compose` oficial — criterio explícito del PDF)
- [ ] Revisar en detalle accesibilidad (WCAG/ARIA) y estándares de codificación (PSR-12/PHP, ESLint para las islas Vue) del repo
- [x] Mapear módulos de Firefly III — ver [[Cursos/QA/entregables/mapeo-modulos-firefly-iii]] (verificado contra el código fuente, no solo el README)
- [x] Borrador del Plan del proyecto (Fase 1) iniciado — ver [[Cursos/QA/entregables/plan-del-proyecto]] (falta revisión del equipo, fuentes IEEE, formato)
