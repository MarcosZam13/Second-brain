# DojoBase Landing

Ver también: [[Proyectos/README|Proyectos]] · [[Proyectos/DojoBase/README|DojoBase (producto)]] · [[Proyectos/CoreBase/README|CoreBase (plataforma)]]

**Qué es:** la landing de venta de DojoBase — proyecto separado de la app (docs, tickets, seguimiento propios en el vault, **y repo de código propio**: `ProyectosPersonales/dojobase-landing/`, Astro). No vive en `corebase` — se sacó de ahí el 2026-08-31: las cuatro reglas de esa plataforma SaaS multi-tenant no aplican a un sitio de marketing, y Astro (cero JS por defecto) es la herramienta correcta para una página ~90% estática, no Next.js/React. Detalle completo en `spec.md`, sección "Stack".

**Estado:** LAND-1 a LAND-5 hechos — página completa de punta a punta (hero, posicionamiento, **4 salas**, personalización, formulario real con Astro Actions, páginas legales), en Astro (~48.7KB gzip de JS, contra ~148KB de la versión anterior en Next.js). Imágenes optimizadas a WebP (2.1MB → 192KB). **En vivo en `https://dojobase-landing.vercel.app/`**, repo privado en GitHub (`MarcosZam13/dojobase-landing`), rama `feature/LAND-1-landing-page-hero` sin mergear. Vercel redespliega solo en cada push; el proyecto lo creó el usuario a mano porque el MCP de Vercel no tiene permiso para crear proyectos (403) — ver `spec.md`.

Fondos de las 4 salas son gradientes CSS por ahora, no arte ilustrado — reemplazables sin tocar estructura, prompts listos en `prompts-salas.md`. CTA "Agendar una demo" (no habrá registro self-service ni precios públicos). Falta: destino real de los leads (LAND-4), revisión legal real de `/terminos` y `/privacidad` (LAND-5), LAND-6 (SEO/`og:image`/analytics/deploy a producción), LAND-7 (prueba social, gateado a Dojo Shoto).

**Historial de QA — cuatro pases, cada uno más profundo que el anterior:**

1. **Pase propio (2026-08-31):** 4 bugs, el peor uno de datos — las capas `edificio`/`primer-plano` tenían el contenido invertido desde el primer archivado, invisible en el navegador porque el choreography "funcionaba" por coincidencia. Ver `spec.md`, "QA".
2. **El usuario probando en su máquina:** franja en blanco de un viewport entero entre el hero y la Sección 2 — problema conocido de `pinSpacing`, verificado contra la doc oficial de GSAP. Ver `spec.md`, "El bug grande".
3. **Deploy real visto desde celular:** zoom del hero demasiado cerrado en móvil; título/CTA casi sin ventana visible (causa real: tweens de GSAP sin `duration` explícita estirando el timeline sin que nadie lo calculara); blur entre salas arrancando demasiado pronto; y el copy de "Oficina del sensei" afirmando que el sensei paga su propia mensualidad — **el usuario aclaró que eso no es así**, reescrito a "Cero perseguir pagos". Se agregó la 4.ª sala ("Torneos y ascensos") a pedido explícito.
4. **Reescritura estructural del hero (lo más importante).** Tras ~5 reportes del mismo síntoma en celular ("las salas aparecen después de donde deberían", "se mueve solo"), se dejó de ajustar timings y se midió en vivo. Aparecieron **3 bugs estructurales, ninguno de timing**: `overflow-x:hidden` en `html`/`body` rompiendo todo `position:sticky`; la altura del hero en unidades de viewport **cambiando sola de 4286px a 3450px** y corriendo ~800px las posiciones cacheadas de ScrollTrigger; y `pinSpacing:false` dejando que la Sección 2 entrara mientras el hero seguía fijo encima (traslape estructural, imposible de arreglar moviendo timings). El hero se reescribió al patrón estándar de GSAP. Verificado de punta a punta con scroll real en viewport de celular. Detalle completo y reglas generales en `spec.md`, "Bugs conocidos a evitar".

Stack y roadmap en `spec.md`.

## Dónde está cada cosa

| Documento | Qué contiene |
|---|---|
| [[Proyectos/DojoBase-Landing/spec\|spec.md]] | Paleta, tipografía, choreography del hero, bugs a evitar (y ya encontrados) y dónde vive el código |
| [[Proyectos/DojoBase-Landing/prompts-salas\|prompts-salas.md]] | Prompts de fondo/primer plano para el arte de las 4 salas de la Sección 3 — pendientes de generar |
| `_fuentes/` | Prototipos HTML originales y las 4 capas de arte, sin editar |

## Ticket prefix

`LAND`. Ver [[Sistema/tickets|tickets.md]] y [[Sistema/skills/gitflow-scrum/SKILL|gitflow-scrum]].
