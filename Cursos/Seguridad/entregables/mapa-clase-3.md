---
curso: Seguridad
tema: Mapa Clase 3 — mapa mental a mano
fecha: 2026-08-18
tipo: entregable
entregable_de: "[[Cursos/Seguridad/apuntes/reglas-clase]]"
estado: borrador
tags: [mapa-mental, cia, stride]
---

# Mapa Clase 3 — árbol CIA + STRIDE

Ver también: [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/apuntes/tema-1-importancia-seguridad-software|Tema 1 (fuente)]]

Entrega: 2026-08-19, 23:45 — 1 página, **hecho a mano**, mapa mental o diagrama, foto en PNG/JPG.

**Enfoque acordado con el usuario (2026-08-18):** concentrarse en el árbol de la Triada CIA y en STRIDE, bien desarrollados y claros — es lo que realmente se vio en clase. STRIDE se tocó solo por encima (probablemente hay material adicional en TEC-Digital que todavía no está en el vault), así que aquí se menciona a nivel de "qué significa cada letra", no el proceso completo de threat modeling. Si aparece la diapositiva original, ajusto esta nota contra ella.

## Estructura del árbol (nodo central en el medio de la página, dos ramas grandes)

```
                    SEGURIDAD DEL SOFTWARE
                     /                    \
              TRIADA CIA                 STRIDE
           /    |      \              (amenazas comunes)
   Confiden-  Integri-  Disponi-      S T R I D E
   cialidad   dad       bilidad
```

### Rama 1 — Triada CIA (rama principal, la más desarrollada)

**Confidencialidad** — "proteger los datos por diseño"
- Cifrado
- Autenticación / autorización
- VPN, segmentación de redes

**Integridad** — "que el software haga solo lo que debe hacer"
- Firmas digitales / funciones hash
- Control de versiones
- Registros de auditoría (logs)

**Disponibilidad** — "software resiliente y confiable"
- Redundancia
- Copias de respaldo (backups)
- Protección anti-DoS

### Rama 2 — STRIDE (mención clara pero breve, sin entrar al proceso completo)

Framework para nombrar tipos de amenaza — cada letra es una categoría de ataque a tener en mente:

| Letra | Amenaza | En una frase |
|---|---|---|
| **S** | Spoofing | Suplantación — hacerse pasar por alguien/algo que no es |
| **T** | Tampering | Manipulación — alterar datos sin autorización |
| **R** | Repudiation | Repudio — negar haber hecho una acción |
| **I** | Information disclosure | Fuga de información — exponer datos que no debían verse |
| **D** | Denial of service | Denegación de servicio — tumbar o saturar el sistema |
| **E** | Elevation of privilege | Escalación de privilegios — obtener más acceso del permitido |

**Tip para el dibujo:** las 6 letras funcionan bien como un hexágono chiquito o una lista vertical al lado de un candado/escudo — no hace falta dibujar el proceso de threat modeling completo (DFD, priorización, etc.), solo el acrónimo con su significado, ya que en clase se vio por encima.

## Checklist antes de entregar

- [ ] Árbol de la Triada CIA bien desarrollado (3 ramas + mecanismos de cada una)
- [ ] STRIDE con las 6 letras y su significado en una frase corta
- [ ] Hecho a mano, cabe en 1 página
- [ ] Foto legible en PNG o JPG
