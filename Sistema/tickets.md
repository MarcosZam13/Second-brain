# Registro de códigos de ticket

Ver también: [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]] · [[Sistema/CLAUDE|CLAUDE.md]]

Fuente de verdad única para los prefijos de ticket usados en branches/commits/PRs de este vault (ver [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]]). Antes de crear un branch o commit con un código nuevo, consultar esta tabla; después de usarlo, actualizar "Último usado" acá mismo en el mismo commit.

## Cursos

| Prefijo | Curso | Último usado | Próximo |
|---|---|---|---|
| SEM | Seminario de Estudios Costarricenses | SEM-4 | SEM-5 |
| QA | Aseguramiento de la Calidad del Software | QA-1 | QA-2 |
| SEG | Seguridad | — | SEG-1 |
| WEB | Desarrollo Web | — | WEB-1 |
| CYS | Computación y Sociedad | — | CYS-1 |
| EST | Estadística | EST-1 | EST-2 |
| SO | Sistemas Operativos | SO-3 | SO-4 |

## Proyectos personales

| Prefijo | Proyecto | Último usado | Próximo |
|---|---|---|---|
| TACHA | Tacha | — | TACHA-1 |
| GYM | GymBase | — | GYM-1 |
| CANELE | CaneleApp | — | CANELE-1 |

## Sistema (el vault mismo)

| Prefijo | Alcance | Último usado | Próximo |
|---|---|---|---|
| VAULT | Cambios al propio sistema del vault (skills, agentes, CLAUDE.md, estructura) | VAULT-18 | VAULT-19 |

## Reglas

- Un curso/proyecto nuevo que todavía no tiene fila: agregarla acá antes de usar el prefijo por primera vez — no inventar uno sobre la marcha sin registrarlo.
- El prefijo se deriva del nombre de carpeta en `/Cursos/` o `/Proyectos/`, abreviado a algo reconocible (3-5 letras). Una vez fijado, no cambia.
- "Último usado" se actualiza en el mismo commit que lo usa — si por descuido queda desactualizado, confiar en `git log --all --format='%s' | grep {PREFIJO}` como fuente real y corregir la tabla.
