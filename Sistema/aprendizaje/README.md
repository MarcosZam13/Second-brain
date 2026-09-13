# Aprendizaje de arquitectura y buenas prácticas

Ver también: [[Sistema/CLAUDE|CLAUDE.md]] · [[Proyectos/AsistenciasTEC/README|Proyectos/AsistenciasTEC]] · [[Sistema/skills/clean-code-practices/SKILL|clean-code-practices]]

Base de conocimiento personal (no un curso, no un proyecto) para entender *por qué* el código se escribe de una forma y no de otra — arquitectura de software, del lenguaje, y de repositorio. Nace el 2026-09-09 a partir de la mentoría con el profesor de Desarrollo Web en [[Proyectos/AsistenciasTEC/README|Asistencias TEC]], que va a preguntar sobre estas decisiones directamente, no solo evaluar si el código funciona. Corta transversal a todos los proyectos (Tacha, CoreBase/DojoBase, Asistencias TEC), no se mezcla con `Sistema/skills/` porque esos son instrucciones para que Claude Code se comporte de cierta forma — esto es material para que **el usuario** entienda y pueda explicar el código en voz alta.

**Cómo usar esto:** cada nota cierra con una sección "Si el profesor pregunta..." — las respuestas cortas que hay que poder dar de memoria, no solo reconocer al leerlas.

## Notas

| Tema | Nota | Por qué importa |
|---|---|---|
| Principios de diseño OO | [[Sistema/aprendizaje/principios-solid\|principios-solid.md]] | Justifica *por qué* una estructura de código es mejor que otra — es lo que un profesor/senior pregunta cuando dice "¿por qué lo hiciste así?" |
| Arquitectura del lenguaje | [[Sistema/aprendizaje/arquitectura-typescript\|arquitectura-typescript.md]] | Cómo funciona TypeScript por dentro (compilador, sistema de tipos) y cómo eso informa cómo se estructura una app grande |
| Manejo de repositorio | [[Sistema/aprendizaje/git-workflow-diagrama\|git-workflow-diagrama.md]] | Diagrama y comparación de los modelos de branching reales de la industria, más allá de "hacer commit y push" |
| React | [[Sistema/aprendizaje/que-es-un-hook\|que-es-un-hook.md]] | Qué es un hook, por qué existe, cómo funciona por dentro, errores comunes |

## Cómo se amplía

Cuando aparezca una pregunta de arquitectura nueva (patrones de diseño, testing con Playwright, clean/hexagonal architecture, principios de bases de datos, etc.), se agrega acá como nota nueva y se referencia en esta tabla — no se resuelve solo en el chat y se pierde. El criterio para que algo viva acá y no en las notas de un proyecto puntual: si la respuesta sirve para *cualquier* proyecto futuro, va acá; si es una decisión específica de Asistencias TEC o Tacha, va en la carpeta de ese proyecto.

## Pendiente de investigar (mencionado por el profesor, no cubierto todavía)

- Patrones de diseño más allá de SOLID (Factory, Repository, Observer, etc.) aplicados a TypeScript/React.
- Testing con Playwright — primera vez que se usa en el vault, comparar con el patrón POM ya documentado en [[Sistema/skills/qa-testing-practices/SKILL|qa-testing-practices]].
- El skill de Stitch que va a compartir el profesor, en cuanto llegue.
- El flujo de git real que use la empresa del profesor, en cuanto se documente (ver [[Proyectos/AsistenciasTEC/README#Cómo se va a trabajar (distinto al resto de proyectos del vault)|README de Asistencias TEC]]).
