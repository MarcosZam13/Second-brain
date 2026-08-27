---
curso: Seguridad
tema: Mapa Clase 4 — mapa mental a mano
fecha: 2026-08-24
entrega: 2026-08-26
tipo: entregable
entregable_de: "[[Cursos/Seguridad/apuntes/reglas-clase]]"
estado: borrador
tags: [mapa-mental, pruebas-seguridad, owasp, estandares, cadena-suministro]
---

# Mapa Clase 4 — Tipos de Pruebas + Frameworks de Estándares + OWASP + Cadena de Suministro

Ver también: [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/apuntes/tema-2-ciclo-vida-desarrollo-software|Tema 2 (fuente)]]

Entrega: 2026-08-26, 23:45 (miércoles posterior a la clase) — 1 página, **hecho a mano**, mapa mental o diagrama, foto en PNG/JPG.

Semana con poco contenido nuevo — 4 ramas, solo conceptos (la profesora pidió esta vez no meter ejemplos, solo lo que entendimos de cada tema).

## Cómo se ve el dibujo

```
                 PRUEBAS Y ESTÁNDARES DE SEGURIDAD
        /                |                  |                \
  TIPOS DE PRUEBAS   FRAMEWORKS DE      OWASP            CADENA DE
  (fase de Pruebas   ESTÁNDARES         (el que usamos   SUMINISTRO
   y Verificación)   (solo mencionados)  en el curso)     DE SOFTWARE
```

## Rama 1 — Tipos de pruebas de seguridad

5 tipos, dentro de la fase de Pruebas y Verificación del SDLC:

- **DAST** → probar la app corriendo (en ejecución), no el código en reposo
- **Pentesting** → simular un ataque real para ver qué tan lejos se puede llegar
- **Fuzzing** → mandarle datos raros/masivos al sistema para ver dónde se rompe
- **Gestión de vulnerabilidades** → una vez que aparecen fallos, decidir cuáles corregir primero
- **Code Review de seguridad** → revisar el código no solo por lógica, sino buscando fallos de seguridad

*Idea para acordarme: van del sistema completo (DAST/Pentesting) hacia el código específico (Code Review) — no es solo "probar que funcione", es "probar que no se pueda abusar".*

## Rama 2 — Frameworks para estándares (solo mencionados, sin entrar en detalle)

Existen para que las empresas no tengan que inventar desde cero cómo proteger su software:

- **NIST** — organismo de EE.UU., estándares de adopción voluntaria (no obliga, se sigue porque es bueno)
- **ISO/IEC** — estándares internacionales certificables (organización + aplicación)
- **SANS** — más enfocado en formación/capacitación en seguridad que en emitir un estándar

*Solo quedarme con que existen y qué tipo de organización es cada una — no se profundizó en clase.*

## Rama 3 — OWASP (el estándar que vamos a usar en el curso)

- Fundación sin fines de lucro — el estándar global de seguridad en aplicaciones web
- 3 pilares: **comunidad** (gente colaborando abierto), **herramientas** (gratuitas/abiertas), **estándares** (documentos técnicos reconocidos)
- **OWASP Top 10** → el "estándar de oro": los riesgos más críticos, punto de partida para saber qué defender primero

*Por qué me importa: es el marco de referencia que se va a usar el resto del curso (proyecto final incluido).*

## Rama 4 — Cadena de suministro de software

- El software de hoy no se escribe completo, **se ensambla**: código propio + dependencias externas + herramientas de desarrollo + infraestructura
- Idea clave: mi app es tan segura como el eslabón más débil que uso (una dependencia externa insegura, me hace insegura a mí)
- Por eso OWASP le dedica una categoría propia dentro del Top 10 — no es un riesgo aparte, es parte de los riesgos que hay que evaluar

*Conecta directo con OWASP (Rama 3): es una de las categorías de riesgo que el Top 10 cubre.*

## Checklist — antes de entregar

- [ ] Árbol con las 4 ramas: Tipos de Pruebas / Frameworks / OWASP / Cadena de Suministro
- [ ] Cada rama con solo los conceptos clave (sin ejemplos, como pidió la profesora)
- [ ] Nombre, curso y fecha arriba de la hoja
- [ ] Hecho a mano, cabe en 1 página
- [ ] Foto legible en PNG o JPG, subida a TEC-Digital
