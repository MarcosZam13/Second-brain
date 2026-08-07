# Dashboard

```dataviewjs
// Colores por curso — orden fijo, nunca se reordena (si se agrega un curso
// nuevo, va al final de esta lista; así el color de un curso ya existente
// nunca cambia). Paleta categórica validada (CVD-safe en claro y oscuro).
const courseColor = {
  "CompuYSociedad":      { light: "#2a78d6", dark: "#3987e5" },
  "DesarrolloWeb":       { light: "#eb6834", dark: "#d95926" },
  "Estadistica":         { light: "#1baf7a", dark: "#199e70" },
  "QA":                  { light: "#eda100", dark: "#c98500" },
  "Seguridad":           { light: "#e87ba4", dark: "#d55181" },
  "Seminario":           { light: "#008300", dark: "#008300" },
  "SistemasOperativos":  { light: "#4a3aa7", dark: "#9085e9" },
};
const status = { critical: "#d03b3b", warning: "#fab219", muted: "var(--text-muted)" };

const isDark = document.body.classList.contains("theme-dark");
const colorFor = curso => (courseColor[curso] ? courseColor[curso][isDark ? "dark" : "light"] : "var(--text-muted)");

// --- recolectar entregas pendientes de todos los cursos ---
const pages = dv.pages('"Cursos"').where(p => p.entregas_pendientes && p.curso);
let items = [];
for (const p of pages) {
  for (const e of p.entregas_pendientes) {
    const fecha = dv.date(e.fecha);
    items.push({ curso: p.curso, entregable: e.entregable, peso: e.peso, fecha, link: p.file.link });
  }
}
items.sort((a, b) => a.fecha - b.fecha);

const today = dv.date("today");
const daysLeft = f => Math.ceil(f.diff(today, "days").days);

const container = this.container;

if (items.length === 0) {
  container.innerHTML = `<p style="color:var(--text-muted)">Sin entregas pendientes cargadas todavía.</p>`;
} else {

  // --- stat tiles ---
  const next = items[0];
  const nextDays = daysLeft(next.fecha);
  const semana = items.filter(i => daysLeft(i.fecha) >= 0 && daysLeft(i.fecha) <= 7).length;
  const mes = items.filter(i => daysLeft(i.fecha) >= 0 && daysLeft(i.fecha) <= 30).length;

  const tile = (label, value, sub) => `
    <div style="flex:1; min-width:140px; background:var(--background-secondary); border:1px solid var(--background-modifier-border); border-radius:8px; padding:12px 14px;">
      <div style="font-size:0.75em; color:var(--text-muted); text-transform:uppercase; letter-spacing:0.04em;">${label}</div>
      <div style="font-size:1.6em; font-weight:700; color:var(--text-normal); line-height:1.2;">${value}</div>
      ${sub ? `<div style="font-size:0.8em; color:var(--text-muted);">${sub}</div>` : ""}
    </div>`;

  const tilesHtml = `
    <div style="display:flex; gap:10px; flex-wrap:wrap; margin-bottom:18px;">
      ${tile("Próxima entrega", `${nextDays}d`, `${next.entregable} · ${next.curso}`)}
      ${tile("Esta semana", semana, semana === 1 ? "entrega" : "entregas")}
      ${tile("Este mes", mes, mes === 1 ? "entrega" : "entregas")}
      ${tile("Total pendientes", items.length, "en el vault")}
    </div>`;

  // --- agrupar por urgencia ---
  const groups = [
    { label: "Esta semana", icon: "🔴", test: d => d >= 0 && d <= 7 },
    { label: "Próximas 2 semanas", icon: "🟡", test: d => d > 7 && d <= 14 },
    { label: "Este mes", icon: "🟢", test: d => d > 14 && d <= 30 },
    { label: "Más adelante", icon: "⚪", test: d => d > 30 },
  ];

  const rowHtml = i => {
    const d = daysLeft(i.fecha);
    const badgeColor = d <= 3 ? status.critical : d <= 7 ? status.warning : status.muted;
    return `
      <div style="display:flex; align-items:center; gap:10px; padding:8px 10px; border-radius:6px; border:1px solid var(--background-modifier-border); margin-bottom:6px; background:var(--background-primary);">
        <span style="width:8px; height:8px; border-radius:50%; background:${colorFor(i.curso)}; flex-shrink:0;"></span>
        <span style="font-size:0.75em; color:var(--text-muted); min-width:78px;">${i.curso}</span>
        <span style="flex:1; color:var(--text-normal);">${i.entregable}</span>
        <span style="font-size:0.8em; color:var(--text-muted); background:var(--background-secondary); padding:1px 7px; border-radius:10px;">${i.peso}</span>
        <span style="font-size:0.85em; color:var(--text-muted); min-width:90px; text-align:right;">${i.fecha.toFormat("yyyy-MM-dd")}</span>
        <span style="font-size:0.8em; font-weight:600; color:${badgeColor}; min-width:38px; text-align:right;">${d}d</span>
      </div>`;
  };

  let groupsHtml = "";
  for (const g of groups) {
    const rows = items.filter(i => g.test(daysLeft(i.fecha)));
    if (rows.length === 0) continue;
    groupsHtml += `
      <div style="margin-bottom:16px;">
        <div style="font-weight:600; margin-bottom:6px; color:var(--text-normal);">${g.icon} ${g.label}</div>
        ${rows.map(rowHtml).join("")}
      </div>`;
  }

  container.innerHTML = tilesHtml + groupsHtml;
}
```

%% Cómo se mantiene esto al día: cada Cursos/{curso}/entregas.md tiene frontmatter
curso: {nombre} y entregas_pendientes (lista de {fecha, entregable, peso}), además
de la tabla legible que ya existía ahí. Este dashboard lee esos dos campos con
DataviewJS — no la tabla markdown, que Dataview no puede parsear directamente.
Cuando se agregue/cambie/elimine una fecha en algún entregas.md, actualizar
también su frontmatter para que se refleje acá. Colores por curso están
hardcodeados arriba en orden fijo — un curso nuevo se agrega al final del
objeto courseColor, nunca se reordenan los existentes. Requiere "Enable
JavaScript Queries" activado en Settings → Community plugins → Dataview. %%
