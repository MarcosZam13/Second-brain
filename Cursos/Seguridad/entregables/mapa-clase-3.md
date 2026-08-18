---
curso: Seguridad
tema: Mapa Clase 3 — mapa mental a mano
fecha: 2026-08-18
tipo: entregable
entregable_de: "[[Cursos/Seguridad/apuntes/reglas-clase]]"
estado: borrador
tags: [mapa-mental, cia, threat-modeling, complejidad]
---

# Mapa Clase 3 — estructura para copiar a mano

Ver también: [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/apuntes/tema-1-importancia-seguridad-software|Tema 1 (fuente)]]

Entrega: 2026-08-19, 23:45 — 1 página, **hecho a mano**, mapa mental o diagrama, foto en PNG/JPG.

## ⚠️ Sobre "Threat Modeling"

No tengo diapositivas de la profesora sobre este tema específico — no aparece en el PDF de Tema 1 que procesé. Lo que sigue es el marco **estándar** que se enseña universalmente (framework STRIDE de Microsoft), y encaja con la unidad "Patrones de Ataque" del programa oficial del curso. Si en clase lo dieron distinto, avisame para ajustar esta nota antes de que lo copies.

## Estructura sugerida (3 ramas, para que quepa en 1 página)

Nodo central: **Seguridad del Software**

### Rama 1 — Triada CIA (lo que ya tenías apuntado)
- **Confidencialidad** — proteger datos por diseño (cifrado, autenticación, VPN)
- **Integridad** — que el software haga solo lo que debe (hash, control de versiones, auditoría)
- **Disponibilidad** — software resiliente y confiable (redundancia, backups, anti-DoS)

### Rama 2 — Complejidad / Extensibilidad / Conectividad
| Factor | Riesgo | Principio de defensa |
|---|---|---|
| Complejidad | vulnerabilidades en las "grietas" entre módulos | Simplicidad — código minimalista y auditable |
| Extensibilidad | código malicioso vía extensión no verificada | Sandboxing + validar complementos |
| Conectividad | más conexiones = más superficie de ataque | Defensa en Profundidad + **Zero Trust** |

Frase para anclar la rama: *"Cada línea de código puede ser una puerta o un escudo."*

### Rama 3 — Threat Modeling (lo que te faltó apuntar)

**Qué es:** proceso estructurado para identificar, priorizar y mitigar amenazas **antes** de construir o desplegar el sistema — mover la seguridad al diseño, no a un parche posterior.

**Pasos (secuencia lineal, fácil de dibujar como flujo):**
1. Identificar activos — ¿qué hay que proteger?
2. Diagrama de arquitectura / flujo de datos (DFD) — cómo se mueve la información
3. Descomponer la app — puntos de entrada, límites de confianza
4. Identificar amenazas con **STRIDE**:
   - **S**poofing (suplantación)
   - **T**ampering (manipulación de datos)
   - **R**epudiation (repudio — negar una acción)
   - **I**nformation disclosure (fuga de información)
   - **D**enial of service (denegación de servicio)
   - **E**levation of privilege (escalación de privilegios)
5. Priorizar amenazas con **DREAD**: Damage, Reproducibility, Exploitability, Affected users, Discoverability
6. Mitigar y documentar

**Tip para el dibujo:** STRIDE se presta bien para un mini-hexágono o lista de 6 íconos alrededor de un candado — es la parte más "visual" del mapa y probablemente lo que más valora la profesora si insistió en que era importante.

## Checklist antes de entregar

- [ ] Rama CIA (ya la tenías, solo resumir a lo esencial)
- [ ] Rama Complejidad/Extensibilidad/Conectividad (con el principio de defensa de cada una)
- [ ] Rama Threat Modeling con STRIDE (confirmar si coincide con lo que dio la profesora)
- [ ] Hecho a mano, cabe en 1 página
- [ ] Foto legible en PNG o JPG
