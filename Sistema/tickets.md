# Registro de códigos de ticket

Ver también: [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] · [[Sistema/CLAUDE|CLAUDE.md]]

Fuente de verdad única para los prefijos de ticket usados en branches/commits/PRs de este vault (ver [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]]). Antes de crear un branch o commit con un código nuevo, consultar esta tabla; después de usarlo, actualizar "Último usado" acá mismo en el mismo commit.

## Cursos

| Prefijo | Curso | Último usado | Próximo |
|---|---|---|---|
| SEM | Seminario de Estudios Costarricenses | SEM-18 | SEM-19 |
| QA | Aseguramiento de la Calidad del Software | QA-35 | QA-36 |
| SEG | Seguridad | SEG-21 | SEG-22 |
| WEB | Desarrollo Web | WEB-5 | WEB-6 |
| CYS | Computación y Sociedad | CYS-4 | CYS-5 |
| EST | Estadística | EST-7 | EST-8 |
| SO | Sistemas Operativos | SO-23 | SO-24 |

## Proyectos personales

| Prefijo | Proyecto | Último usado | Próximo |
|---|---|---|---|
| TACHA | Tacha | TACHA-23 | TACHA-24 |
| MB | CoreBase (plataforma, trabajo transversal del monorepo) | MB-8 | MB-9 |
| DOJO | DojoBase | DOJO-6 | DOJO-7 |
| GYM | GymBase | — | GYM-1 |
| CANELE | CaneleApp | — | CANELE-1 |
| COMPDES | COMPDES 2027 | — | COMPDES-1 |

## Sistema (el vault mismo)

| Prefijo | Alcance | Último usado | Próximo |
|---|---|---|---|
| VAULT | Cambios al propio sistema del vault (skills, agentes, CLAUDE.md, estructura) | VAULT-31 | VAULT-32 |

## Reglas

- Un curso/proyecto nuevo que todavía no tiene fila: agregarla acá antes de usar el prefijo por primera vez — no inventar uno sobre la marcha sin registrarlo.
- El prefijo se deriva del nombre de carpeta en `/Cursos/` o `/Proyectos/`, abreviado a algo reconocible (3-5 letras). Una vez fijado, no cambia.
- "Último usado" se actualiza en el mismo commit que lo usa — si por descuido queda desactualizado, confiar en `git log --all --format='%s' | grep {PREFIJO}` como fuente real y corregir la tabla.
