---
curso: Seguridad
tema: "Tema 1 — La importancia de la Seguridad del Software"
fecha: 2026-08-18
tipo: apunte
fuente:
  - _fuentes/Seguridad_tema1-importancia-seguridad-software_2026-08-18.pdf
tags: [tema1, cia, historia, etica, legislacion, unidad1]
---

# Tema 1 — La importancia de la Seguridad del Software

Ver también: [[Cursos/Seguridad/temario]] · [[Cursos/Seguridad/apuntes/reglas-clase|Reglas de clase]] · [[Cursos/Seguridad/apuntes/tarea-1-legislacion-costarricense|Tarea 1 — Legislación]]

Diapositivas de la profesora que cubren completo el primer bloque de contenidos del programa oficial ("La importancia de la Seguridad en el Software"). Cubre introducción, historia, definición, complejidad/extensibilidad/conectividad, ética y legislación costarricense — probablemente el material acumulado de varias clases (el grupo va por semana 3 pero contando desde "semana 1" del profesor).

## Introducción — desde la mirada del desarrollador

- El código que escribimos define el nivel de riesgo de la organización: cada decisión de diseño impacta **Confidencialidad, Integridad y Disponibilidad (CIA)**.
- La seguridad no es una fase final, es un **requisito funcional**.
- Los 3 pilares (CIA):
  1. **Confidencialidad** — "Protege los datos por diseño"
  2. **Integridad** — "Que el software haga solo lo que debe hacer"
  3. **Disponibilidad** — "Software resiliente y confiable"
- Frase clave: *"Cada línea de código puede ser una puerta o un escudo."*

## Historia de la seguridad del software (por década)

1. **1960s** — conciencia inicial de errores y control de acceso; primeros debates sobre confiabilidad y permisos.
2. **1970s** — modelos formales y criptografía aplicada; nacen modelos de seguridad y uso práctico de cifrado.
3. **1980s** — seguridad en redes y control de acceso fino; protección frente a amenazas remotas y privilegios.
4. **1990s** — seguridad en la web y políticas organizadas; aparecen firewalls, políticas y pruebas de penetración.
5. **2000s** — desarrollo seguro y normas de calidad; integración de seguridad en el ciclo de vida del software.
6. **2010s** — DevSecOps y automatización de pruebas; seguridad como responsabilidad compartida y automatizada.
7. **2020s** — Zero Trust y enfoque en la tríada CIA.
8. **Resumen general:** de correcciones reactivas a prácticas proactivas — la seguridad pasó a integrarse desde el diseño.

*(Dinámica de clase asociada: buscar una noticia real por cada ciclo histórico y comentarla — actividad de clase, no entregable evaluado por separado que se haya identificado hasta ahora.)*

## ¿Qué es la Seguridad del Software?

Disciplina de la ingeniería de software que comprende prácticas, principios, metodologías y controles técnicos aplicados durante todo el **SDLC** (ciclo de vida del desarrollo), para proteger un sistema frente a amenazas/vulnerabilidades/ataques, garantizando **confidencialidad, integridad y disponibilidad**.

## Complejidad, Extensibilidad y Conectividad

| Factor | Riesgo | Principio de seguridad | Resumen |
|---|---|---|---|
| **Complejidad** | Más partes móviles = más difícil predecir el comportamiento ante ataques; vulnerabilidades se esconden entre módulos | Simplicidad — código limpio y minimalista, más fácil de auditar | "Lo que no está ahí, no puede ser hackeado" |
| **Extensibilidad** | Sistema muy abierto → código malicioso vía extensión no verificada | Sandboxing + validación estricta de complementos | Añadir habitaciones sin dar la llave de la caja fuerte a los nuevos inquilinos |
| **Conectividad** | Cada conexión es un punto de entrada; más conectividad = mayor superficie de ataque | Defensa en Profundidad + **Zero Trust** (nunca confiar, siempre verificar) | Más puertas y ventanas = más guardias necesarios |

## Implicaciones éticas de la seguridad del software

1. **Privacidad vs. Vigilancia** — dilema de cuánta info del usuario es lícito recolectar para "mantenerlo seguro"; el software debe proteger sin volverse espionaje masivo.
2. **Divulgación responsable (Responsible Disclosure)** — al hallar una vulnerabilidad: informar primero a la empresa y dar tiempo razonable para el parche antes de hacerla pública, para evitar el caos.
3. **Sesgos en algoritmos de seguridad** — IA entrenada con datos sesgados puede marcar injustamente a ciertos grupos; la seguridad debe ser equitativa, no discriminatoria.
4. **El costo de la seguridad y la exclusión** — si solo quien paga tiene software seguro, la seguridad se vuelve privilegio de clase; hay responsabilidad moral de dar protección básica en servicios esenciales (salud, banca, educación).
5. **Responsabilidad por fallos (Accountability)** — ¿quién responde cuando software inseguro causa daño real (auto autónomo, equipo médico)? La ética exige transparencia sobre limitaciones y asunción clara de responsabilidad legal/moral.
6. **Manifiesto del Hacker Ético** — el "poder" de conocer una vulnerabilidad conlleva la responsabilidad de no usarla para daño personal.

## Legislación costarricense y otros referentes

En Costa Rica no hay una sola ley — es un ecosistema de normas. (Detalle ampliado y aplicado a un caso en [[Cursos/Seguridad/apuntes/tarea-1-legislacion-costarricense|Tarea 1]].)

**1. Protección de Datos Personales**
- **Ley N.° 8968** (Protección de la Persona frente al Tratamiento de sus Datos Personales): los datos son del ciudadano, no de quien los recolecta.
- **Consentimiento informado:** autorización expresa y por escrito (física o digital) antes de recolectar cualquier dato.
- **Artículo 24:** obliga a medidas técnicas/organizativas de seguridad.
- **PRODHAB:** agencia estatal que vigila y sanciona.
- **Reglamento a la Ley 8968:** define niveles básico/medio/alto según sensibilidad de los datos.

**2. Delitos informáticos y seguridad lógica — Ley N.° 9048** (reforma del Código Penal):
- Suplantación de identidad (Art. 230)
- Daño informático (Art. 229 bis)
- Sabotaje informático (Art. 229 ter)
- Instalación de programas maliciosos (Art. 232)
- Espionaje informático (Art. 231)

**3. Propiedad intelectual y protección del software** — en CR el software se protege como **obra literaria**, no invención industrial:
- **Ley N.° 6683** (Derechos de Autor): protege código fuente y objeto desde su creación; se recomienda registrarlo en el Registro Nacional.
- **Ley N.° 7975** (Información No Divulgada): protege algoritmos/know-how como secreto comercial.

**4. Normativa técnica y ciberseguridad nacional**
- **Estrategia Nacional de Ciberseguridad** (MICITT) — lineamientos para infraestructura crítica.
- **Ley de Ciberseguridad** (en trámite/reciente) — busca centralizar respuesta a incidentes (CSIRT Nacional) y elevar estándares para instituciones públicas/proveedores del Estado.
- **ISO/IEC 27001** — estándar voluntario, pero usado como referencia de "buenas prácticas" en jurisprudencia administrativa costarricense.

### Puntos críticos para un desarrollador/empresa

1. **Derecho al olvido** — datos personales deben poder borrarse tras 10 años del hecho generador (o antes si el fin expiró).
2. **Notificación de brechas** — obligación (ética y cada vez más legal) de informar a PRODHAB y afectados ante un compromiso de seguridad.
3. **Transferencia internacional** — si los datos se alojan fuera de CR (AWS, Azure, etc.), el país destino debe tener protección equiparable.

**Principio rector:** *Privacidad desde el Diseño* (Privacy by Design) — el cumplimiento normativo se integra en el código desde el día uno, no se agrega después.

### Checklist maestro de cumplimiento normativo (Costa Rica)

| Fase del proyecto | Requisito | Acción concreta | Fundamento legal |
|---|---|---|---|
| 1. Concepción | Privacidad desde el Diseño | Definir solo los datos mínimos necesarios | Ley 8968, Art. 6 |
| 2. Desarrollo | Seguridad de Datos | Cifrado AES-256 en reposo + TLS 1.3 en tránsito | Ley 8968, Art. 24 |
| 3. Interfaz | Consentimiento Informado | Pop-up/casilla de aceptación NO marcada por defecto | Ley 8968, Art. 5 |
| 4. Usuario | Derechos ARCO | Panel para ver/editar/solicitar borrado de cuenta | Ley 8968, Cap. II |
| 5. Arquitectura | Prevención de Delitos | Logs de auditoría inalterables | Código Penal (Ley 9048) |
| 6. Legal | Políticas de Privacidad | Términos y Condiciones claros y accesibles | Ley 7472 (Consumidor) |
| 7. Lanzamiento | Propiedad Intelectual | Depósito del código fuente en el Registro Nacional | Ley 6683 |
| 8. Mantenimiento | Gestión de Brechas | Protocolo de notificación inmediata a PRODHAB | Reglamento Ley 8968 |
