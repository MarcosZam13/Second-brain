---
curso: Seguridad
tema: "Marco Legal Digital y Ciberseguridad en Costa Rica (informe técnico-jurídico)"
fecha: 2026-08-18
tipo: apunte
fuente:
  - _fuentes/Seguridad_marco-legal-digital-ciberseguridad-cr_2026-08-18.pdf
tags: [ley8968, ley6683, prodhab, arco, sanciones, legislacion]
---

# Informe técnico-jurídico — Marco Legal Digital y Ciberseguridad en Costa Rica

Ver también: [[Cursos/Seguridad/apuntes/tarea-1-legislacion-costarricense|Tarea 1 — Legislación]] · [[Cursos/Seguridad/apuntes/tema-1-importancia-seguridad-software|Tema 1]] · [[Cursos/Seguridad/apuntes/quiz1-estado-ciberseguridad-cr-2025|Quiz 1 — Estado de la Ciberseguridad en CR 2025]]

Documento de profundización legal — **cubre en detalle solo Ley 8968 y Ley 6683** (el propio informe declara que no tiene información sobre Ley 9048, Ley 7975 ni la Estrategia Nacional de Ciberseguridad del MICITT — para eso usar [[Cursos/Seguridad/apuntes/tema-1-importancia-seguridad-software|Tema 1]] y [[Cursos/Seguridad/apuntes/tarea-1-legislacion-costarricense|Tarea 1]]). Útil sobre todo para fundamentar con artículos concretos el rol de **Devs** en la Tarea 1.

## 1. Fundamentación constitucional

- **Artículo 24 de la Constitución Política:** garantiza el derecho a la intimidad, libertad y secreto de las comunicaciones; documentos privados y comunicaciones son inviolables.
- **Resolución de la Sala Constitucional N.° 5802-1999:** carácter preventivo del derecho a la intimidad, para evitar tratos discriminatorios por datos sensibles (raza, religión, salud).
- **Resolución N.° 4847-1999:** conceptualiza la **autodeterminación informativa** como derecho activo y autónomo — el titular ejerce dominio directo sobre la circulación y uso de su información, no solo protección pasiva.

**Principios rectores del tratamiento de datos** (bloque de constitucionalidad): Transparencia · Correspondencia · Exactitud y Veracidad · Prohibición de procesar datos sensibles (salvo autorización expresa) · Finalidad · Destrucción de datos al cumplirse el fin.

## 2. Ley N.° 8968 — detalle operativo

**Conceptos:** Datos Personales · Datos Sensibles (origen racial, opiniones políticas, convicciones religiosas, salud, vida sexual, datos biométricos) · Responsable de la Base de Datos · Encargado del Tratamiento (tercero que procesa por cuenta del responsable).

**Consentimiento válido — 3 condiciones concurrentes:**
1. Informado (notificación previa de fines y derechos)
2. Expreso (acción afirmativa clara; **no vale el silencio**)
3. Libre (sin coacción)

Para **datos sensibles**, el consentimiento debe ser **por escrito**, imperativamente.

**Plazos de respuesta — Derechos ARCO** (Decreto Ejecutivo N.° 37554-JP):

| Derecho ARCO | Plazo |
|---|---|
| Acceso | 5 días hábiles |
| Rectificación | 5 días hábiles |
| Cancelación / Supresión | 5 días hábiles |
| Oposición | Plazo que determine PRODHAB durante el trámite del reclamo |

## 3. Ley N.° 6683 — Propiedad Intelectual del Software

- **Art. 4, inciso ñ):** el software se asimila a **obra literaria** — cubre instrucciones, versiones sucesivas, desarrollos derivados, documentación técnica y manuales.
- **Derechos Morales (Arts. 13-14):** inalienables y perpetuos — autoría y oposición a modificaciones que dañen la reputación del autor.
- **Derechos Patrimoniales (Art. 16):** explotación económica exclusiva (reproducción, transformación, adaptación, distribución).
- **Creaciones en el ámbito laboral (Art. 40):** si el programa lo hace un trabajador asalariado en el marco de sus funciones, la titularidad patrimonial es del **empleador**, salvo pacto contrario.
- **Plazo de protección (Art. 58):** vida del autor + **70 años**.
- **Exclusión de copia privada (Art. 74):** la excepción de copiar una obra didáctica para uso personal **no aplica a software** — toda copia requiere autorización expresa.
- **Depósito legal (Art. 106):** depositar un ejemplar de la obra en bibliotecas nacionales/universitarias designadas, dentro de los 8 días posteriores a su publicación.

## 4. Cuadro comparativo rápido

| Normativa | Objeto | Consentimiento | Autoridad | Plazo |
|---|---|---|---|---|
| Ley 8968 | Datos personales | Informado, expreso, libre (escrito si es sensible) | PRODHAB | Máx. 10 años en bases inscritas |
| Ley 6683 | Software, documentación, manuales | Autorización expresa del titular | Registro Nacional de Derechos de Autor y Conexos | Vida del autor + 70 años |

## 5. PRODHAB — institucionalidad y casuística

Órgano de desconcentración máxima con independencia técnica. Sobre 1,489 reclamos tramitados:

- **Sectores con más reclamos:** Bancario/Financiero (302) · Comercial (262) · Gestión de Cobranzas (253).
- **Motivos más frecuentes:** solicitudes de eliminación/supresión de datos (601 casos) · falta de consentimiento informado (256 casos).

**Régimen sancionatorio administrativo 2026** (salario base judicial ₡462.200):

| Gravedad | Rango en salarios base | Monto máximo (₡) | ≈ USD |
|---|---|---|---|
| Falta leve | 1–5 | ₡2.311.000 | ~$4.250 |
| Falta grave | 5–15 | ₡6.933.000 | ~$12.750 |
| Falta muy grave | 15–30 | ₡13.866.000 | ~$25.500 |

Útil para el rol de **PRODHAB/Fiscalía** en la Tarea 1 al calcular una sanción fundamentada.

## 6. Checklist de cumplimiento corporativo

- [ ] Inscripción de bases de datos ante PRODHAB (si son para distribución/comercialización/difusión; canon anual USD 200; exentas las de uso interno o bajo supervisión SUGEF).
- [ ] Protocolo ARCO implementado (respuesta en máx. 5 días hábiles).
- [ ] Consentimiento firmado por escrito para datos sensibles (expedientes médicos, laborales, biométricos).
- [ ] Depósito legal de software (Ley 6683, Art. 106) — 8 días tras publicación.
- [ ] Auditoría de transferencias internacionales — solo a países/receptores con protección adecuada reconocida por PRODHAB.
- [ ] Política de depuración de datos — borrado/anonimización automática al cumplir 10 años, salvo exigencia legal distinta.
