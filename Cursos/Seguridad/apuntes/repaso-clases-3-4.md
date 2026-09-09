---
curso: Seguridad
tema: "Repaso — Clases 3 y 4 (para quiz)"
fecha: 2026-09-05
tipo: apunte
fuente:
  - Cursos/Seguridad/entregables/mapa-clase-3.md
  - Cursos/Seguridad/entregables/mapa-clase-4.md
  - Cursos/Seguridad/apuntes/stride-metodologia-amenazas.md
  - Cursos/Seguridad/apuntes/tema-1-importancia-seguridad-software.md
tags: [repaso, quiz, cia, stride, dread, pruebas-seguridad, owasp, estandares, cadena-suministro]
---

# Repaso — Clases 3 y 4

Ver también: [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/temario]] · [[Cursos/Seguridad/entregables/mapa-clase-3|Mapa Clase 3]] · [[Cursos/Seguridad/entregables/mapa-clase-4|Mapa Clase 4]] · [[Cursos/Seguridad/apuntes/stride-metodologia-amenazas|STRIDE — nota separada]]

> Alcance confirmado por el usuario 2026-09-05: el quiz de mañana cubre lo mismo que los mapas mentales de Clase 3 y Clase 4. **No hay ningún "Quiz 2" registrado en [[Cursos/Seguridad/entregas]]** — esta nota es solo material de estudio, no un entregable.
>
> También existe como guía visual con autoevaluación interactiva: [artifact "Repaso Clases 3-4"](https://claude.ai/code/artifact/3a0eeb51-6a96-4bc3-878a-ca78fcec280a) (mismo contenido, formato de tarjetas para tapar/revelar respuestas).

## Clase 3 — Fundamentos

### Triada CIA

| Pilar | Qué protege | Ejemplos de control | Si falla |
|---|---|---|---|
| **C** — Confidencialidad | Que nadie que no deba, vea la info | cifrado, login/permisos, VPN | se filtra información |
| **I** — Integridad | Que nadie toque o cambie los datos sin permiso | hash/firma digital, control de versiones, logs | me cambian los datos sin darme cuenta |
| **A** — Disponibilidad | Que el sistema esté ahí cuando lo necesito | backups, redundancia, protección ante DoS | no puedo entrar |

### Complejidad / Extensibilidad / Conectividad

| Factor | Riesgo | Solución |
|---|---|---|
| **Complejidad** | Más código = más fácil esconder fallos | Simplicidad — *"lo que no está, no se puede hackear"* |
| **Extensibilidad** | Plugins/extensiones sin revisar dejan colar código malo | Sandboxing + validación estricta |
| **Conectividad** | Más conexiones = más puertas de entrada | **Zero Trust** — nunca confiar, siempre verificar |

### STRIDE — 6 formas de atacar

| Letra | Categoría | Qué es | Rompe |
|---|---|---|---|
| **S** | Spoofing | Suplantar identidad de usuario o sistema | Integridad |
| **T** | Tampering | Modificar datos en tránsito/reposo/memoria | Integridad |
| **R** | Repudiation | Negar una acción que sí se hizo | — (por eso importan los logs) |
| **I** | Information Disclosure | Exponer datos a quien no debe verlos | Confidencialidad |
| **D** | Denial of Service | Agotar recursos, tumbar el sistema | Disponibilidad |
| **E** | Elevation of Privilege | Ganar permisos superiores a los propios | abre la puerta a todo lo demás |

**DREAD** (cómo se prioriza una amenaza ya identificada con STRIDE — no estaba en el mapa de Clase 3, repasar bien):

- **D**amage — daño potencial
- **R**eproducibility — qué tan fácil es reproducir el ataque
- **E**xploitability — qué tan fácil es explotarlo
- **A**ffected users — cuántos usuarios se ven afectados
- **D**iscoverability — qué tan fácil es descubrir la vulnerabilidad

## Clase 4 — Pruebas y estándares

Semana marcada como "poco contenido nuevo" — 4 ramas, solo conceptos, sin ejemplos.

### Tipos de pruebas de seguridad

Van del sistema completo hacia el código específico:

1. **DAST** — probar la app corriendo (en ejecución), no el código en reposo
2. **Pentesting** — simular un ataque real para ver qué tan lejos se puede llegar
3. **Fuzzing** — mandar datos raros/masivos al sistema para ver dónde se rompe
4. **Gestión de vulnerabilidades** — una vez aparecen fallos, decidir cuáles corregir primero
5. **Code Review de seguridad** — revisar el código buscando fallos de seguridad, no solo lógica

### Frameworks de estándares (solo mencionados, sin profundizar)

- **NIST** — EE.UU., estándares de adopción voluntaria (no obliga, se sigue porque es bueno)
- **ISO/IEC** — estándares internacionales certificables
- **SANS** — enfocado en formación/capacitación, no en emitir un estándar

### OWASP (el estándar que se usa en el curso)

- Fundación sin fines de lucro — estándar global de seguridad en aplicaciones web
- 3 pilares: **comunidad** (colaboración abierta), **herramientas** (gratuitas/abiertas), **estándares** (documentos técnicos)
- **OWASP Top 10** = el "estándar de oro": los riesgos más críticos, punto de partida para saber qué defender primero

### Cadena de suministro de software

- El software de hoy **se ensambla**: código propio + dependencias externas + herramientas de desarrollo + infraestructura
- Idea clave: soy tan segura como el eslabón más débil que uso
- Por eso OWASP le dedica una categoría propia dentro del Top 10 — no es un riesgo aparte

## Autoevaluación rápida

Contestá antes de mirar la respuesta.

1. Si a alguien le cambian los datos sin darse cuenta, ¿qué pilar de la CIA falló?
   `Integridad`
2. De los 3 factores de riesgo, ¿cuál se resuelve con Zero Trust?
   `Conectividad`
3. ¿Qué letra de STRIDE explica por qué son importantes los logs de auditoría?
   `R — Repudiation`
4. Nombrá las 5 métricas de DREAD.
   `Damage, Reproducibility, Exploitability, Affected users, Discoverability`
5. ¿Cuál tipo de prueba se hace sobre la app en ejecución, no sobre el código en reposo?
   `DAST`
6. ¿Cuál de los 3 frameworks se enfoca en capacitación, no en emitir un estándar propio?
   `SANS`
7. ¿Cuáles son los 3 pilares de OWASP?
   `Comunidad, herramientas y estándares`
8. ¿Por qué la Cadena de Suministro no se trata como un riesgo aparte de OWASP?
   `Es una categoría propia dentro del OWASP Top 10`
9. ¿Qué letra de STRIDE "abre la puerta a todo lo demás"?
   `E — Elevation of Privilege`
