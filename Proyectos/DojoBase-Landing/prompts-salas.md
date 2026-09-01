---
proyecto: DojoBase Landing
tema: Prompts de arte para las 4 salas (Sección 3)
fecha: 2026-08-31
tipo: brief-arte
tags: [dojobase-landing, arte, prompts]
---

# Prompts — arte de las 4 salas

Ver también: [[Proyectos/DojoBase-Landing/spec|spec.md]] · [[Proyectos/DojoBase-Landing/README|DojoBase Landing]]

2 capas por sala: **fondo** (escena completa, sin transparencia) y **primer plano** (elemento superpuesto, **con transparencia** — PNG con canal alfa, igual que el torii/edificio del hero). Mismo estilo que las 4 capas del hero, ya generadas — adjuntalas como referencia visual si el generador acepta imágenes.

Formato: 1376×768 o cualquier proporción cercana a 16:9.

## Prompt base (anteponer a los 6 de abajo)

```
Ilustración low-poly flat vector de un dojo japonés, paleta de atardecer/dusk
(violetas, rosados, ámbar cálido), luz cálida saliendo de ventanas o
lámparas, sin líneas de contorno duras, sombras planas por gradiente. Mismo
estilo exacto que esta escena de referencia [adjuntar las 4 capas del hero:
fondo, torii, edificio, primer plano].
```

## Sala 1 — Sala de entrenamiento

Tono: madera cálida.

**Fondo:**
```
Interior de una sala de entrenamiento de dojo japonés tradicional, paredes
de madera cálida, ventanas grandes con luz ámbar de atardecer entrando,
vacía y serena, vista amplia, sin personas.
```

**Primer plano (transparente):**
```
Piso de tatami en perspectiva, en primer plano, patrón geométrico de tejido
de tatami, tono de madera cálida, se extiende hacia el espectador, fondo
transparente.
```

## Sala 2 — Zona de sparring

Tono: dusk frío.

**Fondo:**
```
Interior de zona de sparring de un dojo, al atardecer con luz azul-violeta
fría, piso de tatami abierto, minimalista, ambiente enfocado, sin personas,
plano amplio.
```

**Primer plano (transparente):**
```
Estante de cinturones de artes marciales de distintos colores colgados en
una pared de madera, en primer plano, luz fría de atardecer, fondo
transparente.
```

## Sala 3 — Oficina del sensei

Tono: carmesí apagado.

**Fondo:**
```
Pequeña oficina tradicional dentro de un dojo japonés, escritorio de
madera, luz cálida de lámpara, tonos carmesí oscuro y profundo, espacio
administrativo acogedor, sin personas.
```

**Primer plano (transparente):**
```
Escritorio de madera con un libro de registro abierto y una lámpara o
linterna encendida, en primer plano, luz cálida ámbar, fondo transparente.
```

## Sala 4 — Torneos y ascensos

Agregada 2026-08-31, las 3 salas originales no cambian. Tono: dorado
apagado, "ceremonia/medalla" — distinto de las otras 3 (madera, dusk
frío, carmesí).

**Fondo:**
```
Interior de un salón de ceremonias de un dojo japonés, con un pequeño
podio o tarima de exhibición, banderines o cintos colgados como trofeos,
luz cálida dorada de atardecer, ambiente festivo pero sobrio, sin
personas.
```

**Primer plano (transparente):**
```
Una medalla o cinto enrollado sobre un pedestal de madera simple, en
primer plano, luz dorada cálida, fondo transparente.
```

## Cuando lleguen los archivos

Mismo proceso que con el hero: soltarlos en `Sistema/inbox/` del vault,
indicar cuál es fondo y cuál primer plano de cada sala, y se optimizan a
WebP + se conectan en `.scene-bg-*`/`global.css` reemplazando los
gradientes actuales, sin tocar el resto de la estructura.
