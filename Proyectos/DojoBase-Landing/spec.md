---
tipo: spec
proyecto: DojoBase Landing
fecha: 2026-08-30
estado: LAND-1 a LAND-5 hechos. La animación real del hero (no el fallback de reduced-motion) recién se probó por primera vez el 2026-08-31 — reveló un bug estructural de ScrollTrigger (franja en blanco de un viewport tras soltar el pin) que costó varias iteraciones encontrar bien; ya corregido y verificado. Copy del hero/posicionamiento/personalización ajustado a feedback directo del usuario. Imágenes optimizadas a WebP (2.1MB → 192KB). Falta LAND-6 (SEO/analytics/deploy) y LAND-7 (prueba social, gateado a Dojo Shoto)
fuente:
  - _fuentes/dojobase-hero-real-art.html
  - _fuentes/dojobase-scenes-prototype.html
  - _fuentes/fondo.jpg
  - _fuentes/torii.png
  - _fuentes/edificio.png
  - _fuentes/primer-plano.png
tags: [dojobase-landing, landing, diseño]
---

Ver también: [[Proyectos/DojoBase-Landing/README|DojoBase Landing]] · [[Proyectos/DojoBase/README|DojoBase (producto)]] · [[Proyectos/DojoBase/DESIGN|DESIGN.md (app)]] · [[Proyectos/DojoBase/project_dojobase_ui_research|investigación de UI de la app]]

Landing de venta de DojoBase. **Repo propio** — `ProyectosPersonales/dojobase-landing/` (Astro), separado de `corebase` desde el 2026-08-31 (ver "Stack" para el porqué). Vive aparte de la app y de la investigación de UI de la app: esta nota es la única fuente para la landing.

**A quién le habla y para qué — no es una landing de self-service.** `documentacion-v1.md` (2.2, fuera de alcance) es explícito: el registro self-service de dojos nuevos **no está planeado para esta versión** (RF-19), y "la demo es la venta" (1, resumen ejecutivo) — el primer prospecto (Dojo Shoto) se convence mostrándole el producto, no con un botón de "crear cuenta". Eso cambia el trabajo de esta landing: no es capturar un signup, es dejar a un sensei/dueño de academia con ganas de agendar una demo y con la sensación de que este producto entiende su negocio mejor que un ERP genérico o que Wodify/Glofox (ver [[project_dojobase_ui_research]] en memoria). El CTA es **"Agendar una demo"**, no "Empezar gratis" — ver "Posicionamiento y CTA" más abajo.

**No confundir con la página pública de cada dojo.** DojoBase tiene otra pantalla parecida en concepto pero de audiencia opuesta: P1/O7 "Página pública del dojo" (`DESIGN.md` §4), editable por cada organización desde `apps/dojobase`, para que un dojo *ya cliente* se muestre a sus propios alumnos/prospectos. Esta landing vende DojoBase-la-plataforma a dueños de academias; esa otra pantalla es contenido de un tenant, vive en otra app/repo, y no se toca desde acá. (Hay una conversación abierta, todavía sin resolver, sobre si esa "página de información del dojo" debería ser más libre/menos estructurada que lo que dice `DESIGN.md` hoy — ver [[project_dojobase_landing]] en memoria. No es parte de este proyecto; se retoma aparte.)

## Stack

### Pivote 2026-08-31: de Next.js/React (en `corebase/apps/marketing`) a Astro (repo propio)

El plan original metía la landing como `apps/marketing` dentro del monorepo `corebase`, en Next.js/React — por consistencia con `apps/dojobase`, no porque fuera la mejor herramienta para este trabajo específico. El usuario cuestionó las dos cosas por separado y las dos veces tenía razón:

- **¿Repo propio o dentro de `corebase`?** Repo propio. Las "cuatro reglas que no se negocian" de `corebase/CLAUDE.md` (RLS, JWT por tenant, `packages/core` sin conocimiento de vertical) protegen una plataforma SaaS multi-tenant — ninguna aplica a un sitio de marketing. Meterlo en el mismo repo le pone a este proyecto un marco mental que no le sirve.
- **¿React/Next.js o Astro?** Astro. La landing es ~90% arte/copy estático con un solo hero interactivo — Next.js/React carga el runtime completo de React en el cliente aunque casi nada de la página lo necesite; Astro manda **cero JS por defecto** y solo hidrata lo que se marca explícitamente. Medido, no solo argumentado: el bundle de JS del hero en Astro pesa **~44.5KB gzip** (es básicamente GSAP + ScrollTrigger, sin runtime de UI encima) contra los ~148KB "First Load JS" que reportaba el build de Next.js para la misma página — sin haber tocado el choreography ni el arte. El propio GSAP del hero no usa React más que para `useEffect`/`useRef`; en Astro es un `<script>` normal, se portó casi 1 a 1.

**Todo lo del choreography, la paleta, la tipografía y los bugs encontrados/corregidos abajo sigue siendo válido** — el pivote fue de plataforma, no de diseño. El código de Next.js existió, se probó y se corrigió en `corebase/apps/marketing` antes de portarse; se eliminó de `corebase` al mover el proyecto (nada commiteado ahí, sin pérdida de historia real).

**Ya decidido y en uso** (verificado con `astro check`/`build` reales, no solo elegido en el papel):

| Pieza | Elección | Por qué |
|---|---|---|
| Framework | Astro 7, `output: 'static'`, TS strict | Cero JS por defecto — la landing es casi toda estática, no necesita el runtime de un framework de UI para eso |
| UI | Markup de Astro (`.astro`) + un `<script>` de cliente para el hero — **sin React/Vue/Svelte**, no hace falta | GSAP no depende de ningún framework de UI; agregar uno solo para un `useEffect` sería peso sin beneficio |
| Estilos | CSS plano en `src/styles/global.css` para paleta/tipografía. Sin Tailwind por ahora | El hero necesita control preciso que las utilidades no aportan; se puede sumar `@astrojs/tailwind` más adelante para Sección 2/legales si conviene — instalarlo no cuesta nada mientras no se use |
| Animación | GSAP 3.15 + ScrollTrigger | Igual que antes: pin+scrub, `matchMedia` para mobile — el mecanismo no cambió, solo el framework que lo envuelve |
| Tipografía | `@fontsource/anton`, `@fontsource/barlow-condensed`, `@fontsource/space-grotesk` | Autohospedadas (sin request a Google Fonts), es el equivalente de `next/font` para el ecosistema Vite/Astro — mismo motivo que la migración anterior: nada de salto de tamaño mientras carga la fuente |
| Deploy | Vercel — proyecto propio, independiente del de `apps/dojobase` | Sin base de datos ni backend propio — la landing es 100% estática |

**Deliberadamente no instalado todavía** — se agrega cuando la sección que lo necesita esté decidida, no antes:

| Necesidad | Candidato | Se activa cuando |
|---|---|---|
| Íconos de UI menores (nav, footer, formulario) | `lucide-astro` (0.556.0, verificado en npm 2026-08-31) — trazo geométrico que combina con Space Grotesk | Se construya el footer/formulario de LAND-4. **No** es para los motivos principales de la Sección 3 — esos son arte a medida (ver Sección 3, "las 3 salas"), no íconos genéricos de librería |
| Analytics | `@vercel/analytics` — sin cookies, sin banner de consentimiento, cero config extra sobre el deploy que ya se usa | Cuando haya contenido real que valga la pena medir (no antes de tener Secciones 2-3) |
| Imagen del CTA final / OG | `astro:assets` (`<Image />`) para todo lo que no sea capa del hero (esas van por CSS `background-image` a propósito, ver Sección 1) | Cuando exista el copy real y una imagen de Open Graph |
| Tailwind | `@tailwindcss/vite` (plugin de Vite, **no** `@astrojs/tailwind` — esa integración quedó legacy, solo sirve para Tailwind v3). Se instala con `astro add tailwind` en Astro ≥5.2 y detecta la versión correcta sola | Si Sección 2/páginas legales se sienten más rápidas de armar con utilidades que a mano — no es una necesidad confirmada todavía |
| Formulario de LAND-4 (CTA) | **Astro Actions** (`src/actions/index.ts`, validación con Zod) + adaptador `@astrojs/vercel` | Al construir LAND-4 — ver nota abajo, "Cómo se resuelve el formulario del CTA" |

### Cómo se resuelve el formulario del CTA (verificado 2026-08-31, no asumido)

El resto del sitio se queda **100% estático** (`output:'static'`, sin cambiar nada de lo ya construido) — Astro no obliga a volver todo el sitio server-rendered solo por tener un formulario. El patrón verificado contra la documentación oficial de Astro:

1. Agregar el adaptador `@astrojs/vercel` (`astro add vercel`).
2. Definir la acción en `src/actions/index.ts` con `defineAction` + un schema de Zod (nombre, dojo, disciplinas, correo/teléfono) — el handler es donde se manda el lead a donde se decida (correo, webhook de Notion/Airtable).
3. Solo la página/endpoint que recibe el submit lleva `export const prerender = false` arriba — el resto del sitio (hero, Secciones 2-3, legales) sigue prerenderizado igual que ahora, sin costo de performance.

No hace falta backend propio ni base de datos — es exactamente el tipo de necesidad puntual para la que existe esta pieza de Astro.

## Decisiones técnicas revisadas (2026-08-30)

Auditoría explícita de si la librería/técnica elegida sigue siendo la correcta para el nivel de acabado que se busca — no solo reafirmar lo ya elegido.

- **¿Capas PNG + `transform:scale` por GSAP, o video pre-renderizado / Lottie / WebGL?** Se queda como está. Video con scroll-scrubbing (`video.currentTime` atado al progreso) es una técnica real y se ve muy bien en sitios premiados, pero pide arte fotoreal o 3D — acá el arte es ilustración flat-vector, y capas independientes dan control fino por capa (offsets de fade, reposicionamiento en mobile) que un video ya renderizado no permite sin volver a exportarlo. Lottie es para animación de íconos/personajes, no para escenas full-bleed. WebGL/Three.js es sobre-ingeniería para arte 2D plano — no hay nada ahí que un shader resuelva mejor que CSS. La elección actual es la correcta para este estilo de arte, no la default por no pensarlo.
- **¿GSAP + ScrollTrigger, o `animation-timeline: scroll()` nativo de CSS / Framer Motion?** Se queda GSAP. El scroll-timeline nativo todavía no tiene soporte parejo entre navegadores (un sensei viendo esto en Safari/iOS se queda sin animación) — mal trade para una herramienta de venta que no controla el navegador de quien la ve. Framer Motion es una alternativa real y muy usada, pero ya hay una implementación de GSAP probada y funcionando; cambiar de librería ahora sería puro riesgo de regresión sin ganar ninguna capacidad nueva.
- **¿Tailwind, si `global.css` ya resuelve todo a mano?** Sin instalar por ahora (ver "Deliberadamente no instalado todavía") — todo el hero es CSS a mano porque necesita control preciso. Candidato real para Sección 2/legales si el layout tipo texto+grid se siente más rápido con utilidades; se agrega ahí, no antes.
- **Bug de accesibilidad real, encontrado en esta auditoría — ya corregido, y verificado con `prefers-reduced-motion` activado de verdad, no solo leyendo el código. Sigue corregido después del pivote a Astro (re-verificado 2026-08-31).** El `@media (prefers-reduced-motion: reduce)` reduce duraciones de `transition`/`animation` de CSS, pero el pin+scale+shake del hero lo mueve GSAP por JS (`ScrollTrigger` scrub) — una regla de CSS no lo toca. Corregido: el `<script>` de `index.astro` lee el mismo media query y, si aplica, no arma el pin ni el timeline — deja el título visible directo, sin secuestrar el scroll.

  **Al verificarlo en el navegador (el navegador de esta sesión de Claude Code trae `prefers-reduced-motion: reduce` activado por defecto — sirvió de prueba real gratis) salió un segundo bug, de cascada CSS pura:** el override `.hero-pin{height:auto}` estaba escrito *antes* que la regla base `.hero-pin{height:400dvh}` en el archivo. Misma especificidad (una sola clase cada una) → gana la que aparece última en el archivo, sin importar si su media query calza o no — así que el override nunca aplicaba, pese a que la condición sí era cierta. `heroPinHeight` medía 3976px (los 400dvh completos) en vez de los ~994px esperados. Corregido moviendo el bloque `@media` después de la regla base. Verificado de nuevo: `heroPinHeight` pasó a coincidir con el viewport, sin scroll vacío. Vale la pena recordar esto como regla general: **un override en un media query pierde contra una regla sin condición que aparece después, si tienen la misma especificidad** — el orden en el archivo importa tanto como la condición.
- **Peso de los 4 assets del hero, sin optimizar todavía:** `edificio.png` 561KB + `primer-plano.png` 783KB + `torii.png` 333KB + `fondo.jpg` 475KB ≈ **2.1MB** solo en capas de fondo, antes de comprimir. No urge mientras se sigue iterando el arte (comprimir algo que se va a reemplazar es trabajo perdido), pero es una tarea real antes de publicar — agregado a LAND-6. Candidato: exportar las 3 capas PNG con alfa a WebP (comprime mucho mejor que PNG para este estilo de arte y mantiene transparencia) y el fondo a WebP/AVIF también.

**Corregido (ya no es un bloqueo, era un malentendido del CTA):** "Empezar gratis" asumía un flujo self-service que **no existe en el plan de producto** — `documentacion-v1.md` (2.2) pone el registro self-service de dojos nuevos explícitamente fuera de alcance del MVP (RF-19); el alta es manual, vendida por el equipo. No hay nada que esperar de DojoBase (ni HU-22, que es para invitar miembros *dentro* de un dojo ya existente, no para dar de alta un dojo nuevo). El CTA correcto es **"Agendar una demo"**, apuntando a un formulario de lead simple o un `mailto:` — ver "Posicionamiento y CTA".

## Roadmap

| Ticket | Qué | Estado |
|---|---|---|
| LAND-1 | Sección 1 — hero cinemático | **Hecho y verificado en el navegador.** Reescrito 2026-08-31 al patrón estándar de GSAP (`pinSpacing:true` + `end` por función, sin altura CSS) tras 3 bugs estructurales — ver la sección "Reescritura del hero". Commiteado y pusheado a `feature/LAND-1-landing-page-hero` |
| LAND-2 | Sección 2 — posicionamiento ("lo que es") | **Hecho y verificado en el navegador** (2026-08-31): copy final **en positivo** (el enfoque negativo original no le gustó al usuario) + reveal liviano al scroll, superficie `--ink` para separarla del hero. Sin imagen — a propósito, texto puro |
| LAND-3 | Sección 3 — "salas del dojo" + franja de personalización + CTA final | **Hecho y verificado en el navegador** (2026-08-31). **Son 4 salas**, no 3 — se agregó "Torneos y ascensos" a pedido explícito del usuario, las 3 originales quedaron igual. Fondos son gradientes CSS todavía (arte pendiente, ver `prompts-salas.md`). Motivos de rangos/`ScorePad`/SINPE/ascenso son recreaciones en CSS puro. Franja de personalización usa los 3 presets **reales** de `packages/core/src/theming/presets.ts` (Combate/Papel/Tatami, colores y radio de bordes exactos) |
| LAND-4 | CTA final "Agendar una demo" + formulario real | **Hecho y verificado en el navegador** (2026-08-31): Astro Action (`src/actions/index.ts`, Zod), destino configurable por `LEADS_WEBHOOK_URL` (sin definir todavía = solo log del servidor, nunca falla ni pierde el lead en silencio). **Pendiente antes de deploy: decidir y configurar el destino real de los leads** (correo, Notion, Airtable — la decisión del "dónde" sigue sin tomar, ver checklist de deploy) |
| LAND-5 | Páginas legales — Términos y Privacidad | **Hecho** (2026-08-31): `/terminos` y `/privacidad`, contenido de borrador razonable (incluye que la ficha de competencia guarda tipo de sangre — dato sensible, HU-32) con aviso visible de que falta revisión legal real contra la Ley 8968 de Costa Rica. **No publicar tal cual sin que un abogado lo revise** |
| LAND-6 | SEO (metadata, sitemap), `og:image`, Vercel Analytics, deploy real | Favicon y meta básicos (`og:title`/`og:description`/`theme-color`) ya en código. **Deploy ya existe** — `https://dojobase-landing.vercel.app/` desde la rama de trabajo, redespliega solo en cada push (lo creó el usuario a mano por el 403 del MCP de Vercel). Falta `og:image` (necesita arte/copy final), sitemap, Analytics, y el deploy "de producción" propiamente dicho (dominio + merge a main) |
| LAND-7 | Sección de prueba social — Dojo Shoto como primer cliente (logo, cita/testimonio) | **Bloqueado por el visto bueno de Dojo Shoto** tras su período de prueba gratis. Dejar el espacio contemplado en el layout de LAND-3/LAND-4 aunque el contenido llegue después — no fabricar nada antes de esa aprobación |

LAND-2 y LAND-3 pueden avanzar en paralelo. LAND-4 y LAND-6 dependen del contenido de arriba; LAND-5 es independiente y se puede adelantar cuando convenga (es texto legal, no depende del resto del diseño).

## QA — pase de code review y optimización (2026-08-31)

Pase completo pedido explícitamente ("revisa que todo se vea bien... si necesitamos cambiar o agregar algo... optimizar la página y dejarla impecable antes del deploy"). Cuatro hallazgos reales, los cuatro corregidos:

1. **Bug de datos, el más importante — `edificio.webp` y `primer-plano.webp` tenían el contenido invertido** desde el primer archivado de los assets en esta misma sesión (mucho antes del pivote a Astro). `edificio` contenía el camino con árboles; `primer-plano` contenía el edificio. El error se propagó fielmente por todos los `cp`/`mv` posteriores (todos por nombre exacto o wildcard, ninguno lo habría detectado) — nunca se vio a simple vista en el navegador porque ambas capas son ilustraciones de peso visual similar y el choreography seguía "funcionando" por coincidencia, no porque la semántica fuera correcta: la coreografía está ajustada para que **el edificio domine** (escala 1.5x, se desvanece último) y **el primer plano sea el acento rápido** (escala 1.9x, se desliza y se desvanece a mitad de camino) — con el contenido cambiado, esos pesos narrativos quedaban al revés. Corregido en el repo **y** en el archivo del vault (`_fuentes/`), para que la fuente también quede bien. Lección: un swap de contenido entre dos archivos con nombres "correctos" es invisible a cualquier lint/build — solo se encuentra mirando la imagen real, no el nombre del archivo.
2. **Bug de UX en el formulario (LAND-4):** el `<form>` tenía `novalidate` puesto por reflejo, sin haber escrito validación propia — un envío vacío llegaba al servidor y mostraba un mensaje crudo de Zod ("Invalid input: expected string, received null") en vez de la validación nativa del navegador. Corregido quitando `novalidate` (la validación HTML5 `required` ahora bloquea el envío antes de llamar a la Action) y, como defensa adicional, el mensaje de error de campo ya nunca muestra texto crudo de Zod al usuario.
3. **Accesibilidad: motivos decorativos con elementos interactivos reales.** Los botones `+1`/`+2`/`+3`/`+4` del motivo de `ScorePad` (Sección 3, sala de sparring) eran `<button>` de verdad, sin acción — quedaban enfocables por teclado/lector de pantalla sin hacer nada, un anti-patrón de accesibilidad conocido. Corregido: `aria-hidden="true"` en los tres motivos puramente decorativos (rangos, ScorePad, comprobante SINPE) y `tabindex="-1"` en los botones del ScorePad — el contenido equivalente ya está en el texto accesible de cada panel.
4. **Faltaban favicon y metadatos básicos.** `Layout.astro` no tenía `<link rel="icon">` ni `og:title`/`og:description`/`theme-color`. Agregado un favicon SVG simple (silueta de torii en el carmesí de marca, ya que no hay logo final todavía — reemplazable) y los meta tags que no dependen de arte final. `og:image` queda pendiente de LAND-6 (necesita arte/copy final).
5. **El estado de `prefers-reduced-motion` del hero estaba incompleto — encontrado por el usuario probándolo en su propia máquina, no en esta sesión.** Windows tiene una opción de accesibilidad ("Mostrar animaciones"/"Animation effects") que, si está apagada, hace que **todo** el sistema (incluida cualquier pestaña de Chrome) reporte `prefers-reduced-motion: reduce` — el usuario la tiene así, así que ve el fallback estático siempre, no solo como caso límite. Ese fallback ocultaba `.layer-primerplano` (`opacity:0`) y no explicaba por qué: sin los árboles/camino, con el edificio y el torii solos, se veía incompleto y "descuadrado" — el reporte textual del usuario ("no están los árboles ni el caminito", "muy descuadrada"). La causa real: **las 4 capas comparten el mismo lienzo (~1376×768) y registran perfectamente entre sí a `scale:1`** — es la escena completa "antes del zoom" tal como la exportó quien hizo el arte, no un estado a medio armar. Corregido: el fallback ahora muestra las 4 capas tal cual, sin ocultar ninguna — solo quita la animación, no el arte. Verificado de nuevo en el navegador tras el fix: escena completa y coherente.

**Optimización de imágenes, pedida explícitamente antes del deploy:** las 4 capas del hero pasaron de PNG/JPG sin comprimir a WebP — **2.1MB → 192KB** (91% menos), calidad 82-90, verificado visualmente sin artefactos perceptibles. `LAYER_IMAGES` y los `background-image` de `global.css` actualizados a `.webp`; los PNG/JPG originales ya no se sirven desde `public/` (siguen intactos en `_fuentes/` del vault, con el swap ya corregido).

**Verificado en el navegador (2026-08-31):** con `prefers-reduced-motion: reduce` activo (el caso real, no solo teórico — así lo ve el usuario en su propia máquina), la escena estática compone las 4 capas correctamente, sin nada oculto. `getComputedStyle` confirma que `.layer-edificio`/`.layer-primerplano`/`.layer-torii` cargan cada uno el `.webp` que le corresponde. Sin errores de consola.

## El bug grande: franja en blanco al soltar el pin del hero (2026-08-31)

Cuando por fin se probó la animación real (ni esta sesión ni el usuario habían tenido `prefers-reduced-motion: no-preference` activo hasta este punto — siempre habían visto el fallback estático), apareció una franja completamente en blanco de **un viewport completo** entre el final del hero y el inicio de la Sección 2. El usuario lo reportó primero como "torii mal puesto, cabaña mal puesta" (esa parte era el fallback de reduced-motion, ya corregido arriba); esta sección es sobre el bug *distinto* que salió al ver la animación de verdad por primera vez.

**Causa raíz, verificada contra la documentación oficial de GSAP (no adivinada) y reproducida en 4 configuraciones distintas antes de encontrar la correcta:** con `pinSpacing:true` (el default de ScrollTrigger), el pin-spacer que arma automáticamente **siempre** mide `duración del pin + altura propia del elemento pineado` — sin importar si el trigger es un wrapper separado o el elemento mismo, ni qué sintaxis de `end` se use (`'bottom bottom'`, `'+=550%'`, con o sin `pinType:'fixed'` forzado). Al soltarse el pin, el elemento pineado vuelve a su posición estática, que es la parte de ARRIBA del spacer — no donde el usuario está parado — dejando vacía la franja de más (exactamente la altura propia del elemento, un viewport) hasta que el spacer completo termina ahí.

Cuatro intentos de arreglo que **no funcionaron**, en orden, cada uno descartado con evidencia medida (`getComputedStyle`/`getBoundingClientRect` en vivo, no suposición):
1. Wrapper separado + `pinSpacing:false` + `end:'bottom bottom'` (la config original heredada del prototipo) — `'bottom bottom'` resta la altura del viewport al calcular la duración del pin, dejando la misma franja por una razón distinta (resta de más, no suma de más).
2. `pinSpacing:true` (default) con el mismo wrapper — franja de un viewport, medida y confirmada.
3. `#pinStage` como su propio trigger con `end:'+=550%'` — mismo resultado.
4. Forzar `pinType:'fixed'` explícito — sin cambio; la doc de GSAP promete una "transform de compensación" al soltar el pin, pero nunca se observó (`transform:matrix(1,0,0,1,0,0)`, identidad, en los cuatro intentos).

**La combinación que se usó en ese momento:** wrapper separado (`.hero-pin`, altura fija por CSS) + `pinSpacing:false` + **`end:'bottom top'`**. Cerró la franja en blanco y se verificó en vivo.

> [!warning] Esta solución fue REVERTIDA el 2026-08-31 — no volver a ella.
> `pinSpacing:false` cerraba la franja en blanco, pero **creaba un bug peor y más difícil de ver**: al no reservar espacio para el elemento pineado, la Sección 2 entra en pantalla *mientras el hero sigue pineado y fijo encima*, así que se superponen. Ese traslape fue el bug que el usuario reportó ~5 veces seguidas y que no se arreglaba moviendo timings, porque era **estructural**. Además, la "altura fija por CSS" del wrapper (en `dvh`/`svh`) resultó ser la otra causa raíz: cambia sola en móvil y corre todas las posiciones de ScrollTrigger.
>
> **La solución correcta y vigente está más abajo, en "Reescritura del hero al patrón estándar de GSAP".** Se dejó esta sección como historia porque explica bien la mecánica del pin-spacer, pero la conclusión de arriba ya no aplica.

**Por qué nadie lo vio antes:** el mecanismo del hero se probó muchísimas veces esta sesión, pero siempre bajo `prefers-reduced-motion: reduce` (el navegador de automatización lo tenía forzado la mayor parte de la sesión, y coincide que el Windows del usuario también lo tiene así) — ese camino nunca arma el timeline con pin, así que el bug era estructuralmente invisible hasta que alguien viera el scroll real por primera vez.

**Segundo bug, encontrado por el usuario con una captura de pantalla apenas se arregló el primero:** con la franja en blanco corregida, el contenido fluye continuo — pero `.layer-title` queda en `opacity:1` desde que el pin suelta, y como `#pinStage` (100dvh) tarda un viewport completo de scroll en terminar de salir de pantalla en flujo normal, se solapaba con el reveal de la Sección 2 (que ya empieza cuando `#posicionamiento` llega a 75% del viewport) — título del hero y "No es un ERP..." superpuestos, ilegibles. Corregido con un `gsap.to('#pinStage',{opacity:0,scrollTrigger:{trigger:'#heroPin',start:'bottom bottom',end:'bottom top',scrub:true}})` — reutiliza el mismo tramo de scroll en el que el pin se suelta (no agrega distancia nueva), así el hero ya es invisible para cuando la Sección 2 se vuelve prominente. Verificado en el navegador: transición ahora es un cross-fade limpio, sin superposición de texto legible.

## Reescritura del hero al patrón estándar de GSAP (2026-08-31) — SOLUCIÓN VIGENTE

Después de los arreglos de arriba, el usuario siguió reportando en celular (Edge) que las secciones aparecían **después** del punto donde debían aparecer, y que a veces el contenido "se movía solo" al subir o bajar. Se reportó ~5 veces. Los primeros 4 intentos de mi parte fueron todos ajustes de timing (mover el punto de corte, retimear tweens, adelantar el fade, agregar un cutoff duro sin scrub) y **ninguno tocó la causa** — ver [[feedback-medir-antes-de-parchar]] en memoria: el segundo reporte del mismo síntoma ya era señal de que la hipótesis estaba mal, no el número.

Al medir en vivo en el navegador (no suponer) aparecieron **tres bugs estructurales que se sumaban**:

**1. `overflow-x: hidden` en `html`/`body` rompía TODO `position:sticky` de la página.** Por spec de CSS, si un eje queda en no-visible, el otro pasa de `visible` a `auto` computado — o sea el `body` se vuelve su propio contenedor de scroll, y cualquier sticky adentro se posiciona contra ESE contenedor en vez del viewport. Fix: `overflow-x: clip` (recorta igual, no crea contenedor de scroll).

**2. La distancia de scroll del hero estaba como altura CSS en unidades de viewport y cambiaba sola.** `.hero-pin` tenía `550dvh` (y por un rato `550svh`). Medido en vivo: **el mismo elemento pasó de 4286px a 3450px entre dos lecturas**, porque el alto del viewport cambia en móvil (barra de direcciones). Cada cambio corre ~800px TODAS las posiciones que ScrollTrigger ya tenía calculadas → las animaciones disparan donde no va. Fix: se eliminó la altura CSS; la distancia ahora tiene **una sola fuente de verdad**, el `end` del ScrollTrigger por función (`end: () => '+=' + window.innerHeight * 4.5`) con `invalidateOnRefresh:true`.

**3. `pinSpacing:false` hacía el traslape estructuralmente inevitable.** Sin spacer, no se reserva el espacio del elemento pineado, así que la Sección 2 entra en pantalla mientras el hero sigue fijo encima. Por eso ningún ajuste de timing lo arreglaba. Fix: `pinSpacing:true` (el default de GSAP), dejando que GSAP dimensione el spacer. **Verificado: el pin termina en 3506 y el reveal de la Sección 2 arranca en 3662 — el traslape es imposible por construcción.**

**Bug adicional encontrado en el camino:** los reveals de `.scene-panel` usaban el panel mismo como trigger, estando el panel dentro de un `position:sticky`. Como son `gsap.from` (arrancan en `opacity:0`), un punto de disparo mal calculado no da "mal timing" sino **contenido que nunca aparece** — reproducido en local: los 4 paneles en `opacity:0` con su sala completamente en pantalla. Fix: disparar con la `.scene` contenedora, que tiene geometría estable.

También se agregó `ScrollTrigger.config({ ignoreMobileResize: true })` para que la barra de direcciones no dispare un refresh completo en cada scroll, y el fade del hero volvió a `0.86` (estaba en `0.72` solo como parche contra el traslape, que ya no existe).

**Verificación:** recorrido completo con scroll real de rueda en viewport de celular (414×896) — hero, título/CTA, Sección 2 y las 4 salas aparecen en orden, sin traslape en ningún punto. Salvedad honesta: el bug solo se manifestaba en el celular del usuario, así que no se pudo confirmar al 100% que estas 3 causas cubran todo lo que él veía; las 3 sí son bugs reales y verificados, no teorías.

## Concepto general

Landing cinemática inspirada en la web de COMPDES 2027. Hook de 3 segundos con zoom por capas al hacer scroll, luego contenido más ligero — pero no un microsite genérico: cada sección después del hero existe para convencer a un sensei/dueño de academia de que este producto entiende su negocio, no para llenar espacio. Estructura completa (revisada 2026-08-30, con el contexto completo de `DESIGN.md`/`historias-usuario.md`/`documentacion-v1.md` ya cerrado):

1. **Hero cinemático** (Sección 1, hecho) — el hook.
2. **Posicionamiento** (Sección 2) — qué NO es DojoBase, en la voz de la marca.
3. **Salas del dojo** (Sección 3) — 3 escenas, cada una una capacidad real del producto.
4. **Personalización por dojo** — franja corta, no una sala más: la misma pantalla real en 2-3 paletas distintas, prueba visual de "tu marca, no la nuestra" (ver "Conexión de marca con la app").
5. **CTA final** — "Agendar una demo".
6. **Footer** — con Términos y Privacidad (requerimiento real, no relleno).

Sin secciones de más. La personalidad de `DESIGN.md` §1 es "disciplinado, preciso, con peso" — eso también aplica a cuántas secciones tiene la landing, no solo a cómo se ve cada una.

## Conexión de marca con la app

El pedido explícito es que la landing "le dé vida" a la marca y conecte con la app — sin ser lo mismo (una landing y un dashboard de uso diario no comparten ni contenido ni densidad). Así se traduce eso a decisiones concretas, ancladas en `DESIGN.md` §1-2.4 (personalidad y tokens ya definidos para la app, no inventados acá):

- **Corrección importante (2026-08-30):** lo de abajo conecta la landing con la **identidad de marca de DojoBase-la-empresa** (el preset por defecto, lo que se ve en la demo antes de personalizar) — **no** con "la app que va a usar cada cliente". Cada dojo que compra el producto personaliza su propia app a su propia marca vía `tenant_themes`/`ThemeEditor` (`DESIGN.md` §2.2, O3) — colores, tipografía, radio de bordes, logo. Eso es la ventaja de diseño real del producto (v1 necesitaba un deploy por cliente; esto es una fila) y va a haber muchos dojos, cada uno con su propia cara. La landing **no** debería prometer implícitamente "así se va a ver tu app" — se ve como el dojo lo configure. Ver el punto nuevo más abajo, "Personalización por dojo: mostrarlo, no solo decirlo".

- **La paleta de la landing YA es casi el preset "Combate" real de la app** (`DESIGN.md` §2.5, el que ve un dojo recién creado antes de personalizar) — no es coincidencia, es la misma dirección de marca (spec 08b) tomada dos veces por separado. Vale la pena cerrar la brecha en vez de dejar dos carmesís parecidos-pero-no-iguales, porque es la cara que DojoBase-la-empresa muestra en su propio material (landing, demo por defecto) — no porque vaya a coincidir con lo que ve un cliente ya personalizado:

  | Token | Landing (actual) | App — preset "Combate" | Acción |
  |---|---|---|---|
  | Fondo | `#0B0D12` | `#0B0B0D` | Casi idéntico, dejar así (la landing tiene un pelín más de azul a propósito, por el cielo del hero) |
  | Superficie | `#15181F` (`--ink`) | `#141417` | Casi idéntico, dejar así |
  | Primario/crimson | `#B23A2E` | `#D91C2B` | **Unificar a `#D91C2B`** — es el mismo color de marca, la landing no debería tener "su propio rojo" |
  | Acento/ámbar | `#C89660` | `#E8A33D` | **Unificar a `#E8A33D`** — mismo criterio |
  | Texto | `#EDE6DA` (`--paper`) | `#F2F0EB` | Casi idéntico, dejar así |
  | Texto muted | `#8891A0` (`--mist`) | `#8A8A94` | Casi idéntico, dejar así |

  **Ya aplicado en código** (`globals.css`, 2026-08-30): `--crimson` → `#D91C2B`, `--amber` → `#E8A33D`. `--crimson-bright` (`#E85C4A`) queda como está, solo para el flash/shockwave del hero, donde la saturación completa se vería mal contra el atardecer.

- **Tipografía: alinear la jerarquía completa, no solo el display.** La app usa tres fuentes con roles estrictos (`DESIGN.md` §2.4): Anton solo en 3-4 momentos de celebración, Barlow Condensed para títulos, Space Grotesk para todo lo demás. La landing hoy solo tiene dos (Anton + Space Grotesk) — **falta Barlow Condensed para los títulos de sección** (Sección 2, encabezados de cada "sala" en Sección 3). Usar Anton únicamente para el reveal del hero es, de hecho, coherente con la regla de la app ("máximo 3-4 puntos en toda la app" para Anton): el momento en que "DOJOBASE" aparece tras el impacto ES el equivalente landing de un `CelebrationOverlay" — el mismo lenguaje tipográfico para el mismo tipo de momento emocional, no una coincidencia de gusto.

- **Motivos visuales a reutilizar, no reinventar:**
  - **Las formas de `RankBadge`** (`DESIGN.md` §5.4: barra directa, barra con punta y franjas, o ninguna insignia según la disciplina) son la pieza con más peso visual del producto — reaparecen como motivo gráfico en la escena de rangos de la Sección 3 en vez de inventar otro ícono para "progresión".
  - **El lenguaje táctil de `ScorePad`** (§5.5: botones de valor directo, grandes, pensados para usarse de pie) — la escena de sparring puede mostrar literalmente esos botones (+1 a +4) como parte del arte/UI de la escena, no un ícono genérico de "cronómetro".
  - **La contención del `CelebrationOverlay`** (§7.15: "impacto por contraste y tipografía, no por movimiento... sin confeti genérico") es la misma regla que ya sigue el flash+ring del hero (Sección 1) — mantenerla también en cualquier micro-interacción nueva de Secciones 2-3: nada de confeti, partículas o easing rebotado "por default".

- **Lo que la landing SÍ puede hacer y la app no:** `DESIGN.md` §1 marca "Animación protagonista" como un NO explícito de la app (RNF-07: gama media, uso diario) — pero también dice por qué: *"la landing impresiona una vez; la app se usa todos los días"*. El pin+scrub del hero, la escala 3.4x, el shake — todo eso es intencionalmente más que lo que la app se permite jamás. No hay contradicción: es la misma marca con dos presupuestos de atención distintos, y la landing ya vive del lado permitido.

- **Personalización por dojo: mostrarlo, no solo decirlo.** Que cada dojo tenga su propia marca dentro de DojoBase (colores, tipografía, logo — `ThemeEditor`/O3, con validación de contraste automática, `DESIGN.md` §2.3) no es un detalle técnico, es la ventaja de diseño real del negocio: GymBase v1 necesitaba un deploy por cliente para eso, esto es una fila en `tenant_themes`. Va a haber muchos dojos y ninguno se va a ver "genérico DojoBase" puertas adentro. Eso es un argumento de venta que se demuestra mejor con una imagen que con un párrafo — candidato fuerte para una franja corta entre la Sección 3 y el CTA final (no una "sala" más, algo más liviano): **la misma pantalla real de la app (ej. una `ClassCard` o el `RankBadge`) repetida 2-3 veces, cada una con un preset de color distinto** (Combate / Papel / Tatami, ya definidos en `DESIGN.md` §2.5, o los colores reales de Dojo Shoto una vez estén). La repetición prueba el punto sola — "no es nuestra marca, es la tuya" — sin necesitar el párrafo explicativo. Encaja bien justo antes del CTA: es el último argumento antes de pedir la demo.

## Sección 1 — Hero cinemático (zoom por capas)

**Estado: implementado en código**, `src/pages/index.astro` (script inline) en el repo `dojobase-landing`, rama `feature/LAND-1-landing-page-hero`. Portado de una implementación previa en Next.js/React (`corebase/apps/marketing`, ya eliminada del repo) tras el pivote a Astro del 2026-08-31 — ver "Stack".

- Mecanismo: GSAP + ScrollTrigger, pin + scrub sobre contenedor de 400dvh.
- Capas (de atrás hacia adelante): fondo (cielo/montañas) → edificio → torii → primer plano.
- Choreography: torii escala ~3.4x hasta "tragar" pantalla, edificio ~1.5x, primer plano se desvanece a mitad de camino.
- Momento de impacto: flash blanco + shockwave ring + camera shake sutil, 68-75% del progreso.
- Revela: título "DOJOBASE" + tagline + CTA.
- Assets: las 4 capas PNG/JPG generadas con Gemini, 1376×768, con canal alfa real verificado (no fondo blanco/negro sólido) en las 3 capas PNG.

### Revisión hecha sobre el prototipo del inbox (2026-08-30)

El prototipo (`dojobase-hero-real-art.html`) ya implementaba el choreography completo y correcto, pero incumplía dos de sus propios "bugs a evitar" — corregidos al portarlo a `apps/marketing`:

1. **Usaba `vh`, no `dvh`** (`.hero-pin{height:400vh}`, `.pin-stage{height:100vh}`) — exactamente el bug que la spec dice evitar. Corregido en `globals.css`.
2. **No había `gsap.matchMedia()`** — "reducir intensidad del zoom en mobile" y "edificio más grande en mobile" estaban documentados como pendientes pero no escritos. Implementado: `toriiScale`/`edificioScale`/`primerPlanoScale` bajan en `(max-width: 768px)`; el "edificio se ve chico" se resuelve aparte con un `transform:scale(1.15)` base en `.layer-edificio` bajo el media query (como punto de partida que GSAP hereda, no peleando con `background-size`).
3. **No había `ScrollTrigger.refresh()` tras cargar imágenes** — inofensivo en el prototipo porque las 4 capas eran `data:` URIs inline (cargan síncrono con el HTML, por eso pesaba 2.8MB), pero se vuelve un bug real en cuanto son archivos reales servidos desde `/public` (carga async). Implementado: precarga las 4 imágenes con `Image()` y llama `ScrollTrigger.refresh()` cuando las 4 terminan.

**Dos bugs más, encontrados recién al portarlo a React y probarlo de verdad en el navegador (no solo leyendo el HTML) — ninguno visible en el prototipo original porque nunca se probó con scroll real:**

4. **Orden de capas en el DOM no coincidía con el orden escrito en la propia spec.** El HTML del inbox apilaba `fondo → torii → edificio → primerplano`, pero el texto de la spec dice explícitamente "de atrás hacia adelante: fondo → edificio → torii → primer plano". Sin `z-index`, el orden del DOM ES el orden de apilado — con el orden del HTML, el edificio (opaco) tapaba el torii por completo durante toda la animación; el torii nunca se veía. Corregido: `fondo, edificio, torii, primerplano` en `hero-cinematico.tsx`.
5. **Bug de flexbox real, no cosmético — encontrado con la app corriendo, no se pudo haber visto en el HTML estático.** `.pin-stage` es `display:flex` y `.layer-title` (con el `<h1>DOJOBASE</h1>`, una palabra sin espacio a font-size hasta 150px) es un hijo flex normal. El `min-width:auto` por defecto de un flex item lo fuerza a medir, como mínimo, el ancho máximo de su contenido — y con la fuente de respaldo (antes de que cargue Anton vía Google Fonts) esa palabra midió más ancho que con Anton ya cargada. GSAP mide `.pin-stage` en ese instante para crear el `pin-spacer` que sostiene el layout durante el pin, y ese ancho incorrecto queda grabado ahí para siempre — medido en vivo: 1897px de pin-spacer contra un viewport de 1512px, corriendo las 4 capas ~385px fuera de cuadro para el resto de la sesión. Corregido con `min-width:0` en `.layer-title` (el fix correcto de CSS para este patrón, no depende de la velocidad de carga de la fuente). Vale la pena recordar este patrón para cualquier otra sección con texto grande dentro de un contenedor con pin de ScrollTrigger.

**Pendiente de verificar, no bloqueante:** los 4 assets son 1376×768. Al 3.4x de zoom del torii (el "money shot" del hero) eso pide render efectivo ~4678×2611 — por debajo de lo que pide una pantalla 4K/retina en el momento exacto de impacto. Puede notarse suavizado/pixelado ahí. Preguntar a quien generó las imágenes si son export final o si hay una versión de mayor resolución antes de dar el hero por cerrado visualmente.

**Verificado en el navegador (2026-08-30):** secuencia completa de scroll probada de punta a punta — pin, fundido de las 4 capas, flash + shockwave ring + shake en la ventana 68-75%, revelado del título y CTA. Sin errores de consola. `pnpm lint`, `typecheck` y `build` limpios.

## Sección 2 — Posicionamiento ("lo que es")

**Reescrita 2026-08-31 a pedido directo del usuario.** La primera versión traducía literalmente `DESIGN.md` §1 ("Lo que NO es") a copy negativo ("No es un ERP con el logo de un cinturón") — el usuario lo probó y no le gustó: *"siento que decir que no es... es como raro, me gustaría que diga lo que sí es DojoBase"*. Reemplazada por completo con enfoque positivo, inventado a partir de su propia descripción ("nosotros ayudamos y nos encargamos para que todo sea más fácil de manejo y gestión de diferentes cosas"):

- Eyebrow: **"Lo que es"**
- Titular: **"Rangos, sparring y pagos. Un solo lugar."** — nombra en concreto las 3 cosas que la Sección 3 muestra justo después (funciona como preview, no como resumen redundante)
- Cuerpo: *"DojoBase junta lo que hoy manejás por separado: quién sube de cinturón, quién le debe un reto en el tatami, quién pagó este mes. Un solo sistema, hecho para cómo funciona un dojo de verdad."*
- Cierre: **"Menos administración, más tatami."**

**Estado: implementado en código y verificado en el navegador** (`src/pages/index.astro`, `#posicionamiento`), sin imagen a propósito — texto puro sobre superficie `--ink`, sin caja/card alrededor. Reveal liviano al entrar en pantalla vía GSAP, sin scrub ni pin.

## Sección 3 — "Salas del dojo"

**Opción B decidida** (escenas tipo "salas del dojo", sobre glassmorphism) — la investigación de UI de la app ya marcó el glassmorphism-como-sistema-completo como uno de los tells de "genérico/hecho por IA" en 2026 ([[project_dojobase_ui_research]] en memoria), y el prototipo de escenas (`dojobase-scenes-prototype.html`, mecanismo `position:sticky` + crossfade, sin pin de ScrollTrigger — técnica válida, distinta a la del hero) ya funciona. Lo que faltaba no era decidir el mecanismo, era decidir **qué muestra cada sala** — eso es lo que se resuelve acá con el contexto completo de la app ya cargado.

**Las 4 salas, mapeadas a componentes y HU reales** (no texto genérico de "funcionalidad X"):

| Sala | Capacidad real que muestra | De dónde sale | Motivo visual |
|---|---|---|---|
| **Sala de entrenamiento** | Rangos multi-disciplina, independientes por arte marcial — un alumno de karate y BJJ en el mismo dojo tiene dos escalas, dos cinturones, sin que el sistema le invente franjas a quien no las usa | `RankBadge` (`DESIGN.md` §5.4), HU-00/HU-00b/HU-27 | Las 3 formas reales de `RankBadge` (barra directa, barra con punta y franjas, sin insignia) — es literalmente el componente con más peso visual del producto, usado como arte, no como referencia |
| **Zona de sparring** | Retos con marcador por rounds, hecho para anotarse de pie al lado del tatami, no un formulario de escritorio | `ScorePad` (`DESIGN.md` §5.5), `SparringSession` (M20), HU-05 a HU-09 | Los botones de valor directo (+1 a +4) del `ScorePad` — el detalle que ya distingue el producto de un stepper genérico de +/− |
| **Oficina del sensei** | Administración de finanzas (comprobantes SINPE, mensualidades) sin fricción, para liberar tiempo hacia el tatami. **Corregido 2026-08-31:** la primera versión de esta copy decía que "el mismo sensei paga su mensualidad como cualquier alumno" (basado en el hallazgo de "tres sombreros" de `DESIGN.md` §3.5) — el usuario aclaró en vivo que **eso no es así**, no es una afirmación válida para la landing. Revisar `DESIGN.md` §3.5 contra este cambio antes de reusar ese hallazgo en otro lado | `RF-...` finanzas + comprobante SINPE (documentacion-v1.md §2.1), "El dojo hoy" (D1) | El comprobante SINPE es, además, un diferenciador real contra Wodify/Glofox (ambos pensados para EE.UU., sin SINPE) — vale la pena que el arte de esta sala lo insinúe, no solo un ícono de "$" genérico |
| **Torneos y ascensos** | Agregada 2026-08-31 a pedido del usuario (las 3 originales no cambian). Resultados de torneo y exámenes de cinturón con fecha y registro — el ascenso queda documentado, no solo anotado en un cuaderno | Sin HU/componente específico todavía identificado — copy genérico sobre progresión formal | Tarjeta de "ascenso registrado" (nombre, cinturón, fecha), acento dorado — recreación en CSS puro (`.ascenso-motif`), mismo criterio que las otras 3 |

**Por qué eran 3 y ahora 4:** la razón original para frenar en 3 (progresión + mecánica táctil + argumento de negocio, sin diluir con una cuarta) sigue siendo válida como criterio — la sala 4 se agregó igual porque fue una decisión explícita del usuario (2026-08-31), no un cambio de criterio de mi parte. Si en algún momento se vuelve a sentir "diluido", esta es la razón original a revisar primero.

**Aclaración técnica: "usado como arte" significa recrear el motivo visual, no importar el componente real.** La landing (repo propio, Astro) no consume `@corebase/ui` a propósito — libertad creativa total, cero acoplamiento con el design system del producto. Cuando esta tabla dice que `RankBadge` o `ScorePad` son el motivo visual de una sala, es una recreación ligera en CSS puro inspirada en su forma real (mismas 3 formas de cinturón, mismos botones +1 a +4), **ya implementada así** (`.rank-motif`, `.scorepad-motif` en `global.css`) — no un `import` con datos falsos.

**Sección de prueba social: todavía no, pero planeada — no descartada.** Corrección del 2026-08-30: Dojo Shoto no es un cliente en operación *hoy*, pero sí es el primer cliente real en camino — va a probar la app gratis un tiempo y después se le vende. La sección de logos/testimonios ("usado por...") queda **gateada al visto bueno de Dojo Shoto tras la prueba**, no descartada indefinidamente: en cuanto apruebe, es el primer contenido honesto que se puede mostrar, y vale la pena dejar el layout con espacio para ese momento (aunque el contenido no exista todavía). Hasta ese visto bueno, no se fabrica ni un logo ni una cita — eso no cambia. Ver LAND-7 en el roadmap.

**Estado: implementado en código** (`#sala1`/`#sala2`/`#sala3`/`#sala4`, `.scene-track` en `index.astro`), verificado con `astro check`/`build` — crossfade + parallax entre las 4, motivos de rangos/`ScorePad`/SINPE/ascenso, copy final (pendiente confirmar en el deploy real que la sala 4 se vea bien en el crossfade, como se hizo con las otras 3). **Fondos de cada sala son gradientes CSS por ahora**, no arte ilustrado — reutilizan las mismas paletas del prototipo validado (madera cálida / dusk frío / carmesí apagado / dorado apagado para la sala 4) en vez de imagen. Esto es intencionalmente reemplazable sin tocar estructura ni contenido: vos seguís viendo cómo queda el arte de imagen (torii, edificio — mismo criterio que el hero) y probando alternativas; cuando haya dirección de arte definida para las 4 salas, se cambia `.scene-bg-*` en `global.css` por capas ilustradas reales, igual que se hizo con el hero.

### Brief de arte para las 4 salas (2026-08-31, el usuario las va a generar él mismo)

**2 capas por sala** (confirmó su propia intuición: "probablemente sean como dos, el fondo y algo más por encima"):

1. **Fondo** — la escena completa del ambiente, full-bleed, sin transparencia (JPG o PNG opaco está bien, como `fondo.jpg` del hero). Es lo que se ve cubriendo toda la pantalla.
2. **Primer plano** — un elemento que se superpone sobre el fondo con parallax sutil (como el piso de tatami de la Sala 1 hoy, que es un patrón CSS puesto ahí de marcador). **Necesita canal alfa (PNG con transparencia)**, igual que `torii.png`/`edificio.png`/`primer-plano.png` del hero — si no tiene fondo transparente, va a tapar el fondo entero en vez de superponerse.

**Estilo — el mismo de las 4 capas del hero ya generadas**, para que no se note el salto entre el hero y las salas: ilustración low-poly/flat vector, paleta de atardecer/dusk (nada de colores saturados tipo dibujo animado infantil), luz cálida ámbar en las fuentes de luz (ventanas, lámparas), sin líneas de contorno duras, sombras planas por gradiente suave. Formato 1376×768 (o cualquier proporción cercana a 16:9) para que `background-size:cover` recorte bien en cualquier viewport.

**Prompt base a anteponer a los 6 prompts** (dale este contexto al generador junto con las 4 imágenes del hero como referencia visual, si el generador acepta imágenes de referencia):

> Ilustración low-poly flat vector de un dojo japonés, paleta de atardecer/dusk (violetas, rosados, ámbar cálido), luz cálida saliendo de ventanas o lámparas, sin líneas de contorno duras, sombras planas por gradiente. Mismo estilo exacto que esta escena de referencia [adjuntar las 4 capas del hero: fondo, torii, edificio, primer plano].

**Sala 1 — Sala de entrenamiento** (`.scene-bg-entrenamiento` hoy: tono madera cálida)
- Fondo: *"Interior de una sala de entrenamiento de dojo japonés tradicional, paredes de madera cálida, ventanas grandes con luz ámbar de atardecer entrando, vacía y serena, vista amplia, sin personas."*
- Primer plano (transparente): *"Piso de tatami en perspectiva, en primer plano, patrón geométrico de tejido de tatami, tono de madera cálida, se extiende hacia el espectador, fondo transparente para superponer."*

**Sala 2 — Zona de sparring** (`.scene-bg-sparring` hoy: dusk frío)
- Fondo: *"Interior de zona de sparring de un dojo, al atardecer con luz azul-violeta fría, piso de tatami abierto, minimalista, ambiente enfocado, sin personas, plano amplio."*
- Primer plano (transparente): *"Estante de cinturones de artes marciales de distintos colores colgados en una pared de madera, en primer plano, luz fría de atardecer, fondo transparente para superponer."*

**Sala 3 — Oficina del sensei** (`.scene-bg-oficina` hoy: carmesí apagado)
- Fondo: *"Pequeña oficina tradicional dentro de un dojo japonés, escritorio de madera, luz cálida de lámpara, tonos carmesí oscuro y profundo, espacio administrativo acogedor, sin personas."*
- Primer plano (transparente): *"Escritorio de madera con un libro de registro abierto y una lámpara o linterna encendida, en primer plano, luz cálida ámbar, fondo transparente para superponer."*

**Cuando lleguen los archivos:** mismo proceso que con el hero — pasarlos a `Sistema/inbox/` del vault, decirme cuál es fondo y cuál primer plano de cada sala, y se optimizan a WebP + se conectan en `.scene-bg-*`/`global.css` reemplazando los gradientes actuales, sin tocar el resto de la estructura.

## Posicionamiento y CTA

**CTA principal: "Agendar una demo"**, no "Empezar gratis" — ver la nota de alcance arriba (registro self-service fuera de plan). **Ya en código en los dos lugares** (`#pinStage .cta` en el hero, `#ctaFinal .cta` después de la franja de personalización) — mismo botón, misma clase `.cta`, mismo color de marca en los dos.

Formulario simple: nombre, dojo, disciplinas, correo/teléfono. Destino todavía sin decidir (¿un correo directo, una hoja de Notion/Airtable, algo mínimo?) — no hace falta backend propio ni base de datos para esto, es exactamente el tipo de cosa que una Astro Action hacia un webhook/correo resuelve sin agregar infraestructura (ver "Stack", "Cómo se resuelve el formulario del CTA").

**Decidido (2026-08-30): sin precios públicos en la landing.** Coherente con el modelo actual — "la demo es la venta", alta manual — el precio se conversa en la llamada, donde se puede ajustar por dojo, y no compromete a una cifra pública antes de tener más de un cliente real. No agregar una sección de planes/pricing más adelante sin revisar esta decisión primero.

## Páginas legales

**Requerimiento real de producto, no relleno de footer:** `documentacion-v1.md` §2.2b dice explícito — *"La política de privacidad y los términos viven en el landing page, no dentro de la app."* Dos rutas simples (`/terminos`, `/privacidad`), enlazadas desde el footer. Contenido pendiente de redactar (no es un tema de librería ni de diseño — es texto legal real, vale la pena que alguien lo revise antes de publicarlo, no soy la fuente adecuada para redactar términos vinculantes desde cero).

## Bugs conocidos a evitar

- NO mezclar CSS `position:sticky` con pin de ScrollTrigger — usar solo ScrollTrigger pin. (El prototipo B de escenas usa `sticky` puro sin pin de ScrollTrigger — eso es una técnica distinta y válida, no el bug: el bug es mezclar los dos mecanismos en la misma sección.)
- Usar `svh`/`dvh` en vez de `vh` (evita salto de barra de navegador en móvil).
- Llamar `ScrollTrigger.refresh()` tras cargar imágenes reales.
- En móvil, reducir intensidad del zoom (`gsap.matchMedia`).
- Cualquier texto grande dentro de un contenedor `display:flex` que tenga pin de ScrollTrigger necesita `min-width:0` — si no, un word-break imposible (como "DOJOBASE") puede forzar el contenedor más ancho que el viewport durante la medición inicial y ScrollTrigger lo graba en el pin-spacer para siempre (bug #5 arriba).
- Un override de CSS dentro de un `@media` pierde contra una regla sin condición que aparece **después** en el archivo, aunque el media query sí calce — misma especificidad, gana el orden. El override de `prefers-reduced-motion` para `.hero-pin` tiene que ir después de la regla base de `.hero-pin`, no antes.
- Un botón/patrón que se va a reutilizar en más de un lugar de la página (`.cta`) necesita ser una clase standalone, no quedar anidado bajo el selector de su primer uso (`.layer-title .cta`) — si no, cuando se reutiliza en otro contenedor (el CTA final, fuera del hero) queda sin estilos y nadie lo nota hasta verlo en el navegador. Encontrado al construir LAND-3.
- **Un pin de ScrollTrigger sobre un elemento oversized (más alto que el viewport, para darle distancia de scroll a un timeline) SIEMPRE deja una franja en blanco de un viewport al soltarse, con `pinSpacing:true` (default) — sin importar el `end` que se use.** La combinación que funciona: wrapper separado + `pinSpacing:false` + `end:'bottom top'` (nunca `'bottom bottom'`, que resta la altura del viewport y reproduce el mismo bug por otra vía). Ver "El bug grande" arriba para el detalle completo — costó 4 intentos encontrarlo.
- **Probar el mecanismo real, no solo el fallback de `prefers-reduced-motion`.** Si el entorno de prueba (navegador de automatización, o el sistema operativo de quien prueba) tiene esa preferencia activada, el camino con pin/scrub nunca se ejecuta y un bug estructural ahí puede quedar invisible indefinidamente — pasó con el bug de arriba.
- **Un tween de GSAP sin `duration` explícita usa el default (0.5) — si varios tweens con `position` numérica pequeña (tipo "fracción 0 a 1") comparten un timeline con duraciones implícitas, `tl.duration()` termina siendo un número que nadie calculó a mano, y esas posiciones dejan de significar "fracción del scroll real".** Encontrado 2026-08-31: el reveal del título del hero (`.layer-title`) usaba duración por defecto arrancando en la posición `0.72`, pero como otro tween sin duración explícita estiraba `tl.duration()` a ~1.22, el título en realidad terminaba de aparecer casi al final real del scroll — casi pegado al fade-out de salida, dejando una ventana casi nula para leer el título y tocar el CTA. Fix aplicado: duración explícita en cada tween del "reveal cluster" + un `.set({}, {}, 1)` al final para anclar `tl.duration()` en exactamente 1, así cada posición ES la fracción real de scroll sin cálculo indirecto. Ver el bloque comentado en `index.astro` para el detalle.
- **Un `scrollTrigger` con `start` basado en la posición propia de un elemento (`'top 75%'`) puede dispararse ANTES de lo esperado si ese elemento está justo después, en el documento, de una sección pineada** — mientras el pin sigue activo, el scroll real sigue avanzando y la posición en viewport del elemento siguiente ya puede cumplir la condición, aunque visualmente el pin todavía cubra la pantalla. Encontrado 2026-08-31 (captura real del usuario): la Sección 2 (`#posicionamiento`, trigger `'top 75%'` sobre sí misma) empezaba a aparecer mientras el hero todavía se estaba desvaneciendo, y ambas se veían superpuestas. Fix: el trigger de la Sección 2 se ancla al elemento pineado (`'#heroPin'`, `start:'bottom top'`), no a la sección que revela — así no puede dispararse hasta que el pin efectivamente se suelta.
- **En un sticky-stack de secciones (`.scene { position:sticky }`) sin spacer extra, cada sección solo tiene su propia altura (100dvh) de scroll disponible para transicionar a la siguiente.** Un crossfade con `start:'top bottom'` sobre la sección entrante ocupa TODO ese tramo — no queda tiempo de "descanso" antes de que el blur empiece. Encontrado 2026-08-31 (feedback real de usuario probando en celular): el blur entre salas "empieza a aparecer muy antes". Fix: `start:'top 35%'` en vez de `'top bottom'`, dejando ~65% del tramo sin blur antes de que arranque la transición.
- **`overflow-x: hidden` en `html`/`body` ROMPE todo `position: sticky` de la página.** Por spec, si un eje queda en no-visible, el otro pasa de `visible` a `auto` computado — o sea, el `body` se vuelve su propio contenedor de scroll, y cualquier sticky adentro se posiciona contra ESE contenedor en vez del viewport. Encontrado 2026-08-31 revisando el bug de las salas apareciendo tarde/movidas en celular. Usar `overflow-x: clip`: recorta igual, pero NO crea contenedor de scroll.
- **Nunca fijar la distancia de scroll de un pin como altura CSS en unidades de viewport (`dvh`/`svh`/`vh`).** Medido en vivo 2026-08-31: `.hero-pin` con `550svh` cambió sola de 4286px a 3450px entre dos mediciones, porque el alto del viewport cambia en móvil. Cada cambio corre ~800px TODAS las posiciones que ScrollTrigger ya calculó, y las animaciones disparan donde no va — la causa raíz de "las salas aparecen después de donde deberían" y "se mueve solo". La distancia del pin tiene que tener UNA sola fuente de verdad: el `end` del ScrollTrigger (idealmente por función, ej. `end: () => '+=' + window.innerHeight * 4.5`, con `invalidateOnRefresh:true`), y dejar que GSAP reserve el espacio con `pinSpacing:true`. Nunca una altura CSS y un `end` que tengan que coincidir a mano.
- **`pinSpacing:false` hace que la sección siguiente entre en pantalla MIENTRAS el elemento pineado sigue fijo encima** — el traslape es estructural, no de timing. Por eso mover puntos de corte, bajar el fade o adelantar el ocultado nunca lo arreglaron del todo (varios intentos, 2026-08-31). Con `pinSpacing:true` GSAP inserta el spacer del tamaño exacto del pin y la sección siguiente NO PUEDE aparecer antes de que el pin termine. Verificado: pin termina en 3506, el reveal de la Sección 2 arranca en 3662.
- **Un `gsap.from` (que arranca el elemento en `opacity:0`) disparado con un trigger cuya geometría es poco confiable es un riesgo de "contenido que nunca aparece", no solo de mal timing.** Los reveals de `.scene-panel` usaban el panel mismo como trigger, estando el panel DENTRO de un `position:sticky`: reproducido en local, los 4 paneles quedaban en `opacity:0` con su sala completamente en pantalla. Regla: si el elemento a revelar vive dentro de un sticky/pin, disparar con el contenedor (que tiene geometría estable), no con el elemento.
- **Nunca aplicar `transform` (incluye `scale` de GSAP) o `filter` (incluye `blur`) directo a un elemento con `position: sticky` — Safari/WebKit (Safari en iOS, y también Chrome en iPhone porque ahí corre sobre WebKit) tiene un bug conocido donde eso rompe el cálculo interno de "stuck" del elemento.** Reportado por el usuario 2026-08-31, solo en celular, nunca en escritorio (la pista clave — el patrón exacto de este bug): las salas del crossfade (ver "Sección 3") aparecían y desaparecían en momentos que no correspondían al scroll real, como si la animación estuviera "al revés". La causa: el crossfade le aplicaba `scale`+`filter:blur` directo a `.scene`, que tiene `position:sticky`. Fix: todo el contenido visual de cada sala se movió a un `.scene-inner` interno (div normal, sin sticky) que es lo que ahora recibe el transform/filter — `.scene` queda intacto, solo se lee su geometría (como `trigger` del ScrollTrigger). Regla general para el resto del sitio: si algo tiene `position:sticky`, el transform/filter va en un hijo, nunca en el elemento sticky mismo.
- **Un `blur()`/scale/opacity aplicado a un elemento con fondo LISO (gradiente sin textura) no se nota, aunque el tween esté corriendo perfecto.** El usuario reportó "la sala 4 no tiene el efecto" — se verificó con `ScrollTrigger` en vivo que el tween SÍ corría proporcional al scroll (opacity/blur con los valores exactos esperados), no era un bug de lógica. La causa real: comparando capturas a igual % de progreso, la transición sala1→2 se veía "cool" porque el fondo de la sala 1 tiene textura (`.tatami`, líneas repetidas) y el blur la distorsiona visiblemente — las salas 2/3/4 eran gradientes lisos, sin nada que el blur pudiera distorsionar. Se intentó como fix un `::after` con `repeating-linear-gradient` sutil en cada fondo (mismo criterio que `.tatami`), **pero el usuario pidió revertirlo** (*"ok la cagaste... quedó fatal, ya no se ve y se buguea todo"*) y se revirtió en el commit siguiente. **No volver a intentarlo sobre los gradientes placeholder.** El diagnóstico sí sigue siendo válido y vale la pena tenerlo presente para cuando llegue el arte ilustrado real: un efecto de blur/distorsión necesita algo con detalle fino debajo para que se note. Con las ilustraciones reales de `prompts-salas.md` el problema desaparece solo, sin necesidad de textura sintética.
- **`scrub` con un número (no `true`) le da al tween hasta ese tanto de segundos de "alcance" detrás de la posición real de scroll — durante un scroll rápido (el flick típico de celular), el contenido visual puede quedar notablemente atrasado respecto a dónde está realmente la página.** Encontrado 2026-08-31: el usuario mandó captura mostrando el hero (`#pinStage`, `scrub:1`) todavía semi-transparente y superpuesto sobre la Sección 2, después de haber confirmado que la animación "se ve bien" scrolleando despacio. Verificado en local con `ScrollTrigger.update()` forzado: en reposo, la opacidad SÍ llega limpio a 0 — el bug solo aparece durante scroll rápido, por el alcance del scrub, no por la lógica del fade en sí. Fix robusto (no depende de afinar el número de scrub, que además ya estaba bien para el resto de la animación): un `ScrollTrigger.create` aparte, SIN scrub, con `onEnter`/`onLeaveBack` que oculta el elemento por `visibility` en el instante exacto en que se cruza el límite — sin alcance, sin importar la velocidad del scroll. No toca `opacity` (evita pisarse con el tween scrubbed que sigue existiendo para la transición suave en scroll normal).

## Responsive

- Breakpoint mobile: `max-width: 768px`.
- Reducir escalas de zoom en mobile (menos mareo). Valores actuales tras feedback real en celular (2026-08-31, el usuario veía "solo el torii y un poco de la casa"): torii `1.6`, edificio `1.2`, primer plano `1.2` (contra `3.4`/`1.5`/`1.9` en escritorio).
- Edificio necesita más tamaño relativo en mobile (se ve chico si no).
- **`svh`, nunca `dvh`, para alturas de sección a pantalla completa.** `dvh` cambia de valor mientras se scrollea en móvil (barra de direcciones), y eso mueve el layout debajo de ScrollTrigger. `svh` es fijo.
- **Pero para la distancia de scroll de un pin, ninguna unidad de viewport en CSS** — va en el `end` del ScrollTrigger, por función. Ver "Bugs conocidos a evitar".
- `ScrollTrigger.config({ ignoreMobileResize: true })` está activo: evita que mostrar/esconder la barra de direcciones dispare un refresh completo en cada scroll.
- **La diferencia móvil/escritorio es información de diagnóstico, no ruido.** Varios bugs de esta sesión solo se manifestaban en el celular del usuario y eran invisibles en escritorio — y en los tres casos la diferencia entre los dos entornos era exactamente la pista (viewport que cambia de alto, WebKit en iOS, barra de direcciones).

## Referencias de estilo

Ilustración low-poly/flat vector, paleta atardecer, estética "terminal/HUD" en la navegación (ver referencia COMPDES 2027).

## Dónde vive el código

**Repo propio**, `ProyectosPersonales/dojobase-landing/` (Astro) — separado de `corebase` desde el 2026-08-31, ver "Stack" para el porqué. Trabajo en curso en `feature/LAND-1-landing-page-hero`. Desde el 2026-08-31 también vive en GitHub como repo privado (`MarcosZam13/dojobase-landing`), pusheado para poder desplegarlo a Vercel y revisarlo en celular — Vercel MCP no tenía permiso de crear proyecto (403), así que el deploy inicial lo hizo el usuario a mano importando el repo desde vercel.com/new; queda pendiente resolver el permiso del MCP para poder desplegar directo desde acá.

**En vivo:** `https://dojobase-landing.vercel.app/` — Vercel redespliega solo en cada push a la rama.

```
dojobase-landing/
├── package.json
├── astro.config.mjs                     ← output:'static' + adapter @astrojs/vercel
├── public/landing/layers/{fondo, torii, edificio, primer-plano}.webp
└── src/
    ├── actions/index.ts       ← Astro Action del formulario (LEADS_WEBHOOK_URL)
    ├── layouts/Layout.astro   ← fuentes (@fontsource/*), <head>, meta/OG
    ├── layouts/LegalLayout.astro
    ├── pages/index.astro      ← markup completo + <script> con toda la lógica de GSAP
    ├── pages/terminos.astro
    ├── pages/privacidad.astro
    └── styles/global.css      ← paleta + tipografía, único lugar con hex literal (ver nota en el propio archivo)
```

**Estructura del DOM que importa para las animaciones** (no romperla sin leer "Bugs conocidos a evitar"):
- `.hero-pin` → `#pinStage` (100svh, es lo que se pinea) → 4 `.layer-*` + `.flash` + `.impact-ring` + `.layer-title`. `.hero-pin` **no** lleva altura; la distancia la da el `end` del ScrollTrigger.
- `.scene-track` → 4 `.scene` (`position:sticky`) → cada una con un `.scene-inner` adentro. **Todo transform/filter va en `.scene-inner`, nunca en `.scene`** (romper esto rompe el sticky en Safari/iOS).
