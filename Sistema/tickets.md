# Registro de códigos de ticket

Ver también: [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] · [[Sistema/CLAUDE|CLAUDE.md]]

Fuente de verdad única para los prefijos de ticket usados en branches/commits/PRs de este vault (ver [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]]). Antes de crear un branch o commit con un código nuevo, consultar esta tabla; después de usarlo, actualizar "Último usado" acá mismo en el mismo commit.

## Cursos

| Prefijo | Curso | Último usado | Próximo |
|---|---|---|---|
| SEM | Seminario de Estudios Costarricenses | SEM-22 | SEM-23 |
| QA | Aseguramiento de la Calidad del Software | QA-40 | QA-41 |
| SEG | Seguridad | SEG-29 | SEG-30 |
| WEB | Desarrollo Web | WEB-5 | WEB-6 |
| CYS | Computación y Sociedad | CYS-5 | CYS-6 |
| EST | Estadística | EST-8 | EST-9 |
| SO | Sistemas Operativos | SO-26 | SO-27 |

## Proyectos personales

| Prefijo | Proyecto | Último usado | Próximo |
|---|---|---|---|
| TACHA | Tacha | TACHA-24 | TACHA-25 |
| MB | CoreBase (plataforma, trabajo transversal del monorepo) | MB-23 | MB-24 |
| DOJO | DojoBase | DOJO-26 | DOJO-27 |
| GYM | GymBase | — | GYM-1 |
| CANELE | CaneleApp | — | CANELE-1 |
| COMPDES | COMPDES 2027 | — | COMPDES-1 |
| LAND | DojoBase Landing | LAND-2 | LAND-3 |
| AS | Asistencias TEC | — | AS-32 (los items AS-01 a AS-31 ya vienen numerados del backlog del profesor, ver [[Proyectos/AsistenciasTEC/backlog\|backlog.md]]) |

## Sistema (el vault mismo)

| Prefijo | Alcance | Último usado | Próximo |
|---|---|---|---|
| VAULT | Cambios al propio sistema del vault (skills, agentes, CLAUDE.md, estructura) | VAULT-31 | VAULT-32 |

## Reglas

- Un curso/proyecto nuevo que todavía no tiene fila: agregarla acá antes de usar el prefijo por primera vez — no inventar uno sobre la marcha sin registrarlo.
- El prefijo se deriva del nombre de carpeta en `/Cursos/` o `/Proyectos/`, abreviado a algo reconocible (3-5 letras). Una vez fijado, no cambia.
- "Último usado" se actualiza en el mismo commit que lo usa — si por descuido queda desactualizado, confiar en `git log --all --format='%s' | grep {PREFIJO}` como fuente real y corregir la tabla.
