# Dashboard

## Próximas entregas (todos los cursos)

```dataview
TABLE WITHOUT ID
  file.link as "Curso",
  entrega.fecha as "Fecha",
  entrega.entregable as "Entregable",
  entrega.peso as "Peso"
FROM "Cursos"
WHERE entregas_pendientes
FLATTEN entregas_pendientes as entrega
SORT entrega.fecha ASC
```

<!--
Cómo se mantiene esto al día: cada Cursos/{curso}/entregas.md tiene un bloque de
frontmatter `entregas_pendientes` (lista de {fecha, entregable, peso}) además de
la tabla legible que ya existe — Dataview no puede leer la tabla markdown
directamente, necesita metadata estructurada. Cuando se agregue o cambie una
fecha en la tabla de algún entregas.md, hay que actualizar ese mismo bloque de
frontmatter para que aparezca acá. Si un curso todavía no tiene entregas_pendientes
(porque no se cargaron fechas todavía), simplemente no aparece en esta tabla.
-->
