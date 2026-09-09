---
curso: Seguridad
tema: "Mapa Clase (semana NIST) — mapa mental a mano"
fecha: 2026-09-07
entrega: 2026-09-09
tipo: entregable
entregable_de: "[[Cursos/Seguridad/apuntes/reglas-clase]]"
estado: "entregado (confirmado por el usuario 2026-09-09)"
tags: [mapa-mental, nist, csf, nice, ssdf]
---

# Mapa Clase (semana NIST) — NIST, CSF, Core Functions, NICE, SSDF

Ver también: [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/apuntes/tema-2-ciclo-vida-desarrollo-software|Tema 2 (fuente)]] · [[Cursos/Seguridad/entregables/tarea-3-nist-csf|Tarea 3 (aplicación práctica del CSF)]]

**Nota:** número exacto de "Mapa Clase N" pendiente de confirmar en TEC-Digital (la semana del 2026-09-02 no hubo clase, así que el conteo se corrió). Entrega estimada: miércoles 2026-09-09, 23:45 — 1 página, **hecho a mano**, foto en PNG/JPG.

La profesora no pidió memorizar NIST/NICE/SSDF de memoria, sino **saber qué es cada uno y para qué se usa**. Por eso cada rama de abajo trae un "cómo se usa" además de la definición — es lo que hay que poder decir en el mapa.

## Cómo se ve el dibujo

```
                              NIST
                (agencia EE.UU., estándares voluntarios)
        /                |                    |                \
      CSF          CORE FUNCTIONS           NICE               SSDF
  (marco de       (las 6 preguntas       (marco de           (desarrollo
  riesgo, qué      del CSF, en           personas: quién      seguro de
  hace la org)     detalle)              hace el trabajo)     software)
```

## Rama 1 — CSF (Cybersecurity Framework)

- Marco de NIST para **gestionar el riesgo de ciberseguridad de una organización** — no es una checklist técnica de vulnerabilidades, es un lenguaje común para hablar de "qué tan protegidos estamos".
- Desde la versión 2.0 (2024) es **universal**: aplica a cualquier organización, no solo infraestructura crítica como la 1.1.
- **Cómo se usa:** como estructura para evaluar/organizar la seguridad de una empresa o sistema — es lo que aplicamos en la Tarea 3 sobre VoteOnline, y es la base del Proyecto Final del curso.

*Idea para acordarme: CSF es el "para qué" (gestionar riesgo); Core Functions es el "cómo" (las 6 funciones que lo ejecutan).*

## Rama 2 — Core Functions (las 6 funciones del CSF)

Se ejecutan de forma concurrente, no en orden fijo — GOVERN/IDENTIFY/PROTECT/DETECT son continuas; RESPOND/RECOVER se activan cuando hay un incidente.

- **GOVERN** → ¿cuál es la estrategia y quién es responsable?
- **IDENTIFY** → ¿qué tenemos y qué riesgo corre?
- **PROTECT** → ¿cómo evitamos que pase?
- **DETECT** → ¿cómo nos damos cuenta de que está pasando?
- **RESPOND** → ¿qué hacemos mientras pasa?
- **RECOVER** → ¿cómo volvemos a la normalidad?

**Cómo se usa:** como 6 preguntas para auditar cualquier sistema — dado un sistema, se responde una por una (exactamente lo que se hizo con VoteOnline en Tarea 3).

## Rama 3 — NICE Framework (SP 800-181)

- Mientras el CSF organiza **qué outcomes de seguridad** debe lograr una organización, NICE organiza **quién hace el trabajo**: roles de trabajo, tareas, conocimientos y habilidades (KSA) de la fuerza laboral de ciberseguridad.
- Es el complemento de "personas" del CSF — no habla de tecnología, habla de puestos y competencias.
- **Cómo se usa:** para describir puestos, diseñar capacitación, o repartir roles en un equipo de seguridad (ej. quién cubre qué módulo en un proyecto).

*Conecta con CSF: el CSF dice qué hay que lograr, NICE dice quién tiene las competencias para lograrlo.*

## Rama 4 — SSDF (Secure Software Development Framework, SP 800-218)

- Prácticas para meter la seguridad **dentro del ciclo de desarrollo de software**, no como revisión al final.
- Su pilar "Diseñar Software Seguro" exige evaluar la arquitectura y hacer modelado de amenazas **antes de escribir la primera línea de código**.
- **Cómo se usa:** al diseñar o revisar la arquitectura de una app — es el marco detrás del análisis de riesgo de arquitectura que ya se vio en clase (STRIDE / threat modeling).

*Conecta con Core Functions: SSDF es donde vive "PROTECT" cuando el objeto que se protege es software que se está construyendo, no un sistema ya en producción.*

## Checklist — antes de entregar

- [x] Árbol con las 4 ramas: CSF / Core Functions / NICE / SSDF, centro NIST
- [x] Cada rama con la definición corta + el "cómo se usa" (no solo qué es)
- [x] Nombre, curso y fecha arriba de la hoja
- [x] Hecho a mano, cabe en 1 página
- [x] Foto legible en PNG o JPG, subida a TEC-Digital (confirmado por el usuario 2026-09-09)
