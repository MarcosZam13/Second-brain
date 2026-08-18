---
curso: Seguridad
tema: Mapa Clase 3 — mapa mental a mano
fecha: 2026-08-18
tipo: entregable
entregable_de: "[[Cursos/Seguridad/apuntes/reglas-clase]]"
estado: borrador
tags: [mapa-mental, cia, stride]
---

# Mapa Clase 3 — árbol CIA + STRIDE (versión apunte de clase)

Ver también: [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/apuntes/tema-1-importancia-seguridad-software|Tema 1 (fuente)]]

Entrega: 2026-08-19, 23:45 — 1 página, **hecho a mano**, mapa mental o diagrama, foto en PNG/JPG.

Escrito como si fueran apuntes tomados en el momento, no como documentación formal — para que lo puedas copiar y entender de un vistazo.

## Cómo se ve el dibujo

```
                SEGURIDAD DEL SOFTWARE
                  /                \
           CIA (3 pilares)        STRIDE (6 formas de atacar)
```

## Rama 1 — CIA

**C — Confidencialidad**
→ que nadie que no deba, vea la info
- cifrado, login/permisos, VPN

**I — Integridad**
→ que nadie toque o cambie los datos sin permiso
- hash/firma digital, control de versiones, logs (queda registro de quién tocó qué)

**A — Disponibilidad** *(Availability — en inglés, por eso es "A" y no "D")*
→ que el sistema esté ahí cuando lo necesito, no se me caiga
- backups, redundancia (tener de repuesto), protegerse de ataques que saturan el sistema (DoS)

*Frase para acordarme: si me roban la info → falló Confidencialidad. Si me la cambian → falló Integridad. Si no puedo entrar → falló Disponibilidad.*

## Rama 2 — STRIDE (6 formas típicas de que te ataquen)

- **S**poofing → alguien se hace pasar por mí (o por el sistema)
- **T**ampering → me cambian los datos sin que yo me dé cuenta
- **R**epudiation → alguien hace algo malo y después dice "yo no fui" (por eso importan los logs)
- **I**nfo disclosure → se filtra info que no debía salir
- **D**enial of service → tumban el sistema a punta de tráfico/saturación
- **E**levation of privilege → un usuario normal logra volverse "admin" sin permiso

*Truco para acordarme: son básicamente las 6 formas en que pueden romper la Triada CIA de arriba — spoofing/tampering rompen integridad, info disclosure rompe confidencialidad, DoS rompe disponibilidad, elevation of privilege abre la puerta a todo lo demás.*

(Nota: en clase se vio STRIDE por encima, no el proceso completo de threat modeling — por eso me quedo solo con el significado de cada letra.)

## Checklist antes de entregar

- [ ] Árbol CIA con las 3 letras y su frase de "qué significa que falle"
- [ ] STRIDE con las 6 letras y su frase corta
- [ ] Nombre, curso y fecha arriba de la hoja
- [ ] Hecho a mano, cabe en 1 página
- [ ] Foto legible en PNG o JPG
