---
curso: Seguridad
tema: "Quiz 1 — Estado de la Ciberseguridad en Costa Rica 2025 (UNA/LabCIBE)"
fecha: 2026-08-18
tipo: apunte
fuente:
  - _fuentes/Seguridad_quiz1-estado-ciberseguridad-cr-2025_2026-08-18.pdf
tags: [quiz1, cibercriminalidad, legislacion, oij, prodhab, micitt, ia, glosario]
---

# Quiz 1 — Estado de la Ciberseguridad en Costa Rica 2025

Ver también: [[Cursos/Seguridad/temario]] · [[Cursos/Seguridad/apuntes/tema-1-importancia-seguridad-software|Tema 1]] · [[Cursos/Seguridad/apuntes/marco-legal-digital-ciberseguridad-cr|Marco legal ampliado]]

**Este es el documento fuente del quiz** ("UNA-Estado-de-la-Cyberseguridad-en-Costa-Rica-QUIZ1.pdf", 166 páginas, ISBN 978-9968-526-27-2). Autores: Edgar Vega Briceño, Roberto Lemaitre Picado, Alex Villegas Carranza, Laura Flores Barrantes — LabCIBE, Sede Regional Chorotega, UNA, abril 2026. Tercer informe de la serie (2023, 2024, 2025).

**Cómo usar esta nota durante el quiz (es open-book, se permite IA):** esta nota es un índice/resumen denso de las cifras, leyes y definiciones más "preguntables". Para una cita textual exacta o un artículo específico no cubierto aquí, el PDF completo está archivado en `_fuentes/Seguridad_quiz1-estado-ciberseguridad-cr-2025_2026-08-18.pdf` — pedirle a Claude que lo abra y busque la sección puntual.

## Estructura del informe (para ubicarse rápido)

- **Capítulo I** (p.15-77): Situación jurídica de la ciberseguridad nacional — leyes, decretos, estrategias
- **Capítulo II** (p.78-93): Investigación y desarrollo — entidades, industria, academia
- **Capítulo III** (p.94-147): Diagnóstico — encuesta 2025 (143 instituciones), hallazgos
- Conclusiones (p.148) · Reflexiones finales (p.149-151) · Referencias (p.153-159) · **Anexo I: Glosario** (p.161-163)

---

## 1. ¿Qué es la ciberseguridad? (p.17)

Componente esencial de la seguridad de la información. Conjunto de políticas, procesos, controles y prácticas para proteger activos de información digital frente a amenazas — a diferencia de la seguridad de la información (todo soporte), la ciberseguridad se centra en el **entorno digital** (infraestructura, aplicaciones, datos).

**Pilares:**
- **Confidencialidad** — accesible solo a sujetos/procesos autorizados (cifrado, autenticación, VPN)
- **Integridad** — datos exactos, completos, sin alteración no autorizada (firmas digitales, hash, control de versiones)
- **Disponibilidad** — accesible cuando se requiere (redundancia, backups, anti-DoS)
- Atributos complementarios: autenticidad, trazabilidad, no repudio, resiliencia operativa

## 2. Amenazas informáticas (p.18)

- **Malware** (virus, gusanos, troyanos, ransomware)
- **Phishing** (y variantes: smishing, vishing)
- **Ataques de fuerza bruta / credenciales** expuestas
- **DDoS** (denegación de servicio distribuida)
- **Exploits/vulnerabilidades** (incluye 0-day)
- **Man-in-the-middle**

Riesgo = amenaza × vulnerabilidad × impacto.

## 3. Tendencias de cibercriminalidad en Costa Rica 2018-2025 (OIJ, p.19-23)

- **40,457 denuncias totales** (01/01/2018–31/08/2025)
- Serie anual: 2018: 1,647 · 2019: 2,100 · 2020: 2,387 · 2021: 2,882 · 2022: 5,158 · 2023: 5,287 · **2024: 10,398** (+96.7% vs 2023) · **2025: 10,598** (ya supera 2024, +1.9%)
- Volumen se multiplicó **×6.4** entre 2018 y 2025

**Composición delictiva (% del total):**
- Estafa informática: **62.1%** (25,100 casos)
- Suplantación de identidad: **21.7%** (8,757)
- (juntas concentran el **84%**)
- Otro/indeterminado 5.5% · Difusión info falsa 2.4% · Suplantación páginas 2.3% · Espionaje informático 1.8% · Facilitación delito 1.6% · Seducción menores por medios electrónicos 1.2% · Instalación malware 0.9% · Sabotaje informático 0.4% · Daño informático 0.2%

**Distribución territorial:** San José 38.2% · Alajuela 19.2% · Heredia 11.4% · Cartago 10.4% · Guanacaste 7.3% · Puntarenas 7.1% · Limón 5.5%

**Víctimas (41,836 total):**
- Sexo: Mujer 49.9% · Hombre 45.7% · Desconocido 4.5%
- Edad: 30-39 (25.2%, pico) · 18-29 (20.7%) · 40-49 (20.1%) · 50-64 (19.9%) · 65+ (8.7%) · 12-17 (2.5%) · 0-11 (0.4%)
- 86% de las víctimas está en el rango 18-64 — la vulnerabilidad no es analfabetismo digital sino fatiga atencional/presión de tiempo/sesgos de confianza

---

## 4. Leyes de ciberseguridad en Costa Rica (13 leyes, sección 1.4)

| # | Ley | Año | Punto clave |
|---|---|---|---|
| 1 | **N.° 8131** Administración Financiera y Presupuestos Públicos | 2001 | Arts. 110 (responsabilidad administrativa) y 111 (delito informático, prisión 1-3 años) contra sistemas de Administración Financiera/Proveeduría |
| 2 | **N.° 8934** Protección niñez/adolescencia frente a contenido nocivo de Internet | 2010 | SUTEL fiscaliza; obliga a proveedores de Internet a ofrecer filtros de contenido (Art. 7); educación (Art. 8) |
| 3 | **N.° 8642** Ley General de Telecomunicaciones | 2008 | SUTEL (órgano de ARESEP) regula; protege privacidad/confidencialidad de comunicaciones |
| 4 | **N.° 8454** Certificados, Firmas Digitales y Documentos Electrónicos | 2005 | Principio de equivalencia funcional; Art. 10 presunción de autoría con firma digital certificada; reformada por Ley 10181 (2024) |
| 5 | **N.° 9943** Creación de la Agencia Nacional de Gobierno Digital (ANGD) | 2020 | ANGD bajo rectoría MICITT; servicios digitales comunes obligatorios |
| 6 | **N.° 9738** Regular el Teletrabajo | 2019 | Deber de confidencialidad ligado a seguridad de la información; derecho a desconexión digital |
| 7 | **N.° 9048** Reforma al Código Penal (delitos informáticos) | 2012 (+ N.° 9135 en 2013) | Ver detalle abajo — **la más importante para el curso** |
| 8 | **N.° 8968** Protección de Datos Personales + Reglamento (Decreto 37554-JP) | 2011 | Ver detalle en [[Cursos/Seguridad/apuntes/marco-legal-digital-ciberseguridad-cr\|nota ampliada]] |
| 9 | Adhesión al **Convenio de Budapest** sobre Ciberdelincuencia (Ley N.° 9452) | 2017 (convenio de 2001) | Único tratado multilateral vinculante integral sobre ciberdelincuencia; 3 declaraciones interpretativas de CR |
| 10 | **Segundo Protocolo Adicional** al Convenio de Budapest (Ley N.° 10778) | 2025 | Cooperación reforzada + evidencia electrónica; plazos: 20 días (info abonado), 45 días (datos de tráfico); Red 24/7 para emergencias |

**Ley N.° 9048 en detalle (la reforma penal clave):**
- **Delitos clásicos adaptados:** Art. 196 (violación de correspondencia) · Art. 196 bis (violación de datos personales)
- **Delitos económicos:** Art. 217 bis (estafa informática) · Arts. 229 bis/229 ter (daño y sabotaje informático)
- **Delitos del ecosistema digital:** Art. 230 (suplantación de identidad) · Art. 231 (espionaje informático) · Art. 232 (instalación/propagación de malware) · Art. 233 (suplantación de páginas electrónicas — phishing) · Art. 234 (facilitación del delito informático) · Art. 235 (agravante por crimen organizado/narcotráfico)

## 5. Decretos (10 principales, sección 1.5)

| Decreto | Tema | Punto clave |
|---|---|---|
| Reglamento Protección Programas de Cómputo (37549-JP, 2012) | Software gubernamental legal | Auditoría anual ante Registro Nacional de Derechos de Autor |
| Comisión Internet Costa Rica — CI-CR (32083, 2004) | Políticas de Internet | Administra ccTLD .cr vía Academia Nacional de Ciencias |
| Priorización Cómputo en la Nube (046-H-MICITT, 2013) | Cloud-first en sector público | Evaluación técnica/legal/financiera obligatoria antes de comprar infraestructura |
| Accesibilidad Sitios Web (036-MTSS-MICITT, 2024) | WCAG 2.1 | Nivel A en 3 años, Nivel AA en 6 años |
| **Reglamento Ciberseguridad 5G** (44196-MSP-MICITT, 2023) | Redes 5G | Exige ISO/IEC 27001/27002/27003/27011 + SCS 9001; **controvertido** por vetar equipos de países no adheridos a Budapest (3 acciones de inconstitucionalidad, una admitida a estudio de fondo) |
| **Reglamento Gobernanza en Ciberseguridad** (45061-MICITT, 2025) | Crea Dirección de Ciberseguridad (DC), **CSIRT-CR** y **SOC-CR** | Modelo NIST CSF 2.0; reporte de incidentes obligatorio en **24 horas**; deroga el decreto de 2012 que creó el CSIRT-CR original |
| Apertura de Datos Públicos (40199-MP, 2017) | Datos abiertos | Portal datosabiertos.presidencia.go.cr; protege datos Ley 8968 |
| Fortalecimiento Capacidades Ciberseguridad (44487-MICITT, 2024) | Donación USD 25 millones (fundación EE.UU.) | Prioriza 18 ministerios; SOC/MDR temporales |
| **Código Nacional de Tecnologías Digitales — CNTD** (44507-MICITT, 2024) | Estándar transversal | Obligatorio salvo defensa/seguridad del Estado |
| Directriz 053-H-MICITT (2019) | Compras de tecnología | SICOP obligatorio + convenios marco |
| Directriz 133-MP-MICITT (2022) | Post-ataque Conti 2022 | Medidas mínimas de "higiene digital"; reporte a csirt@micitt.go.cr |
| Acuerdo CONASSIF 5-24 (2024) | Sector financiero | Gobierno y gestión de TI para bancos/cooperativas/aseguradoras |
| Acuerdo SUGEF 10-07 (2007, reformado 2025) | Consumidor financiero | Desde 2025 exige MFA, cifrado, notificación de actividad sospechosa |

## 6. Estrategias nacionales (sección 1.6)

1. **ENIA — Estrategia Nacional de IA 2024-2027**: 7 ejes (IA ética/segura, articulación territorial, I+D+i, gobierno inteligente, talento, infraestructura digital, liderazgo internacional). Basada en UNESCO + OCDE; considera el AI Act (UE), NIST AI RMF, HAIP.
2. **Estrategia Nacional de Ciberseguridad 2023-2027**: **5 pilares** — (1) reforzar gobernanza, (2) adecuar marco jurídico, (3) fortalecer protección de infraestructuras/ciberresiliencia, (4) reforzar capacidades del ecosistema, (5) cooperar en el entorno digital. Surge tras los ataques de ransomware de **2022 (grupo Conti)**.
3. **Estrategia de Transformación Digital 2023-2027**: 2 ejes (Ciudadanía Digital, Buena Gobernanza), 7 pilares de gobernanza (personas ciudadanas, interoperabilidad, ciberseguridad, marco de políticas, marco jurídico, identidad digital, digital por diseño).

## 7. Entidades e industria (Capítulo II)

- **CAMTIC** (Cámara de TIC, +200 empresas) y **Cybersec Clúster** — entidades gremiales
- Empresas de ciberseguridad en CR (registro CAMTIC): ŠTÍT Cybersecurity, ATTI Cyberlabs, White Jaguars Cyber Security, Sofistic, Grupo B.L, Grupo Eulen, SPC Internacional, AEC Networks, Sitec Seguridad, Delta Protect, CRLabSec, IMACTUS
- **Universidades públicas (CONARE):** TEC tiene Maestría en Ciberseguridad (3 énfasis: seguridad del software, defensa/ataque, gestión de seguridad de la información) + Técnico. **UNA** abrió en 2025 la Maestría Profesional en Ciberseguridad Industrial (Sede Chorotega, vía LabCIBE). UCR y UTN y UNED no tienen programa formal específico, solo cursos sueltos.
- **Universidades privadas (CONESUP, 54 registradas):** Cenfotec (Maestría desde 2014), Universidad Latina, Universae, Fidélitas, Lead University, La Salle, Castro Carazo, ULACIT, Universidad Empresarial, Boston, UISIL, San Marcos — todas con Técnico/Bachillerato/Maestría en Ciberseguridad
- Inversión nacional en I+D: **0.34% del PIB** (estable 2020-2025), muy por debajo del promedio OCDE de **2.67%**

## 8. Hallazgos clave de la encuesta 2025 (Capítulo III — 143 instituciones)

- Muestra: Estatal 33.6% · Banca y finanzas 26.6% · Educativo 12.6% · Servicios 11.2% · Telecom/informática 7%
- **Amenaza más preocupante: ransomware y extorsión** (igual que 2024), seguida de phishing/BEC y pérdida/filtración de datos
- Solo **14.7%** tiene póliza de ciberseguro vigente; 55.2% no tiene y **62.9% no piensa contratarla**
- De quienes sufrieron un ataque, solo **13.3% lo denunció** ante el Sistema Judicial
- 76.2% tiene protocolo de actuación ante incidentes; 79% hace revisiones periódicas de seguridad
- Responsable primario de incidentes: **Dirección de TI** en 55.2% de los casos (no un área de seguridad dedicada)
- Controles más usados: MFA 84.5% · Active Directory 84.5% · Firewall/NGFW 83.8% · Filtrado web/DNS 76.8%
- Solo **26.6%** hace simulacros de phishing regularmente; **35%** no hace ninguno
- Presupuesto de ciberseguridad: **39.2% no sabe** cuánto se asigna; 45.5% cree que es insuficiente
- Adopción de IA en ciberseguridad: solo 12.6% en producción, 7.7% en piloto, 39.9% no la usa — usos principales: detección de amenazas (67.2%), EDR/XDR/MDR (56.9%), SIEM/SOC (43.1%)
- **Escasez de personal calificado (94.1%)** y falta de financiamiento (82.4%) son las principales barreras para I+D en ciberseguridad

---

## Glosario oficial del informe (Anexo I, p.161-163)

- **Activo de información:** elemento con valor para la organización que debe protegerse (info, datos, sistemas, infraestructura, personas, procesos). *ISO/IEC 27000:2022*
- **Amenaza informática:** causa potencial de un incidente no deseado que explota una vulnerabilidad. *ISO/IEC 27000; NIST SP 800-30*
- **Ataque cibernético:** intento deliberado de comprometer confidencialidad/integridad/disponibilidad mediante malware, ingeniería social, explotación de vulnerabilidades o DoS. *NIST SP 800-61; NIST CSF*
- **Ciberseguridad:** preservación de confidencialidad, integridad y disponibilidad de la información en el ciberespacio. *ISO/IEC 27032:2012; NIST CSF*
- **Confidencialidad:** info no disponible/divulgada a no autorizados. *ISO/IEC 27000*
- **Control de seguridad:** medida (preventiva/detectiva/correctiva) para modificar el riesgo. *ISO/IEC 27000; NIST SP 800-53*
- **Datos personales:** info de persona física identificada/identificable. *ISO/IEC 27701 + legislación nacional*
- **Disponibilidad:** acceso oportuno y confiable cuando se requiere. *ISO/IEC 27000*
- **Gestión del riesgo de ciberseguridad:** proceso de identificación, análisis, evaluación y tratamiento del riesgo. *ISO/IEC 27005; NIST SP 800-30*
- **Incidente de ciberseguridad:** evento(s) que comprometen o amenazan comprometer CIA de info/sistemas. *ISO/IEC 27000; NIST SP 800-61*
- **Integridad:** exactitud y completitud de info y métodos de procesamiento. *ISO/IEC 27000*
- **Marco normativo de ciberseguridad:** leyes/reglamentos/directrices/políticas/estándares. *NIST CSF – Govern*
- **Política de ciberseguridad:** declaración formal de alta dirección con principios/objetivos/roles. *ISO/IEC 27001*
- **Riesgo de ciberseguridad:** probabilidad × consecuencias de un incidente sobre activos. *ISO/IEC 27005; NIST SP 800-30*
- **Vulnerabilidad:** debilidad de un activo/control explotable por una amenaza. *ISO/IEC 27000; NIST SP 800-30*
