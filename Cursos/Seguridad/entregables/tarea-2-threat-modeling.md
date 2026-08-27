---
curso: Seguridad
tema: "Tarea 2 — Threat Modeling: VoteOnline (Grupo 11)"
fecha: 2026-08-24
tipo: entregable
entregable_de: "[[Cursos/Seguridad/apuntes/tarea-2-threat-modeling-instrucciones]]"
estado: borrador
tags: [tarea2, threat-modeling, voteonline, grupo11]
---

# Tarea 2 — Threat Modeling: VoteOnline (Grupo 11)

Ver también: [[Cursos/Seguridad/apuntes/tarea-2-threat-modeling-instrucciones|Instrucciones y rúbrica]] · [[Cursos/Seguridad/apuntes/tema-2-ciclo-vida-desarrollo-software|Proceso de 7 pasos (Tema 2)]] · [[Cursos/Seguridad/apuntes/stride-metodologia-amenazas|STRIDE]]

**Caso:** VoteOnline (Votación Institucional) — sistema web de elecciones remotas para colegios profesionales.

## Paso 1 — Entender el sistema

**Descripción corta:** VoteOnline es una plataforma web que permite a los miembros de un colegio profesional votar remotamente en elecciones institucionales (ej. junta directiva), sin acudir presencialmente. El votante recibe por correo un token de un solo uso — generado a partir de su cédula mediante SHA-1 sin sal — con el que emite su voto; el sistema guarda el ID del votante junto a la opción elegida en la misma tabla para evitar doble voto. Un panel de administración web, protegido solo por cookie de sesión, permite auditar la base de datos.

1. **Objetivo principal:** permitir votación remota y evitar doble voto en elecciones de un colegio profesional.
2. **Usuarios:** los colegiados (votantes) y el comité/administrador electoral (audita vía el panel de administración).
3. **Datos que procesa:** número de cédula, correo electrónico, token de un solo uso, ID del votante, opción de voto, cookie de sesión de administración.
4. **3 suposiciones técnicas** (no dichas explícitamente, consistentes con el texto):
   - El **token es el único factor de autenticación** para emitir el voto — el texto no menciona contraseña ni segundo factor, solo el token recibido por correo.
   - Existe **una única base de datos relacional centralizada** — se infiere de "la misma tabla de la base de datos".
   - La votación tiene **una ventana de tiempo definida** (apertura y cierre) — se infiere porque el sistema necesita un punto de corte para "consolidar resultados" y decidir que ya no se aceptan más votos, aunque el texto no menciona fechas ni plazos.

*(Cubre criterio 1 de la rúbrica — completar/ajustar con lo que diga el resto del grupo.)*

## Paso 2 — Identificar activos críticos

| Activo | Tipo | ¿Por qué es crítico? |
| --- | --- | --- |
| Cédula del votante | Dato personal | Es la semilla del token (SHA-1 sin sal) — si se conoce, se puede regenerar el token de cualquier otro colegiado |
| Token del votante | Credencial de acceso | Si se predice o intercepta, permite suplantar el voto de otra persona |
| Voto | Información confidencial | Es la decisión electoral del colegiado; su exposición o alteración vulnera la integridad y el secreto del proceso |
| Cookie de sesión | Credencial de acceso | Sin flag `HttpOnly`, es robable (ej. vía XSS) y da acceso de auditoría total a la base de datos electoral |
| ID del votante | Información confidencial | Al guardarse en la misma tabla que el voto, permite vincular la identidad del colegiado con su elección, rompiendo el secreto del voto |

**Priorización (presupuesto solo para 2):**

Priorizaría **Token del votante** e **ID del votante**. El token es la raíz de la suplantación de identidad al votar; y proteger el ID del votante (separándolo del voto en el diseño de la base de datos) es lo que realmente preserva el secreto del voto — un voto sin identificador asociado deja de ser sensible por sí solo, así que no hace falta proteger "Voto" aparte. Descartaría **Cookie de sesión** (es una mala configuración puntual, rápida de corregir después, no requiere rediseño) y **Cédula del votante** (solo es explotable en la medida en que sirve para predecir el token — si se arregla la generación del token, la cédula por sí sola deja de ser el vector de este ataque).

*(Cubre criterio 2 de la rúbrica.)*

## Paso 3 — Diagrama de flujo de datos (a hacer a mano)

**Boceto de referencia para copiar a mano** (4 cajas + flechas, 3 líneas rojas cruzando las flechas marcadas):

```
 ┌───────────┐  ①  cédula   ┌───────────────┐  token  ②  ┌───────────────────┐
 │  USUARIO  │ ───────────► │  SERVIDOR WEB  │ ─────────► │ SERVICIO DE CORREO │
 │ (votante) │ ◄─────────── │  (VoteOnline)  │            │     (externo)      │
 └───────────┘  token por   └───────────────┘            └───────────────────┘
                  correo       │        ▲
                          voto │        │ valida token
                                ▼        │
                        ┌────────────────────┐
                        │   BASE DE DATOS     │
                        │ (tabla única: ID    │
                        │ votante + opción)   │
                        └────────────────────┘
                                 ▲
                            ③   │ consultas directas
                                 │
                        ┌────────────────────┐
                        │  PANEL DE ADMIN.    │
                        │ (comité electoral)  │
                        └────────────────────┘
```

**Marcar en rojo (①②③):** son los 3 límites de confianza — cruzan justo las flechas Usuario↔Servidor, Servidor↔Correo, y Panel de Admin↔Base de Datos. En la hoja física, basta poner una línea punteada roja perpendicular a cada una de esas 3 flechas.

**Pendiente — dibujar a mano y pegar la foto acá.** Elementos a incluir:

- **Usuario (votante)** → envía cédula/solicita token → **Servidor Web**
- **Servidor Web** → genera token (SHA-1 sobre cédula) → envía por → **Servicio de Correo** (externo, de terceros)
- **Servidor Web** ↔ **Base de Datos** (tabla única: ID votante + opción elegida)
- **Panel de Administración** (accedido por el comité electoral vía cookie de sesión) ↔ **Base de Datos**

**Marcar en rojo 3 límites de confianza:**
1. Entre el navegador del **Usuario** e Internet/Servidor Web (el usuario no es confiable por defecto)
2. Entre el **Servidor Web** y el **Servicio de Correo externo** (un tercero fuera del control del colegio)
3. Entre el **Panel de Administración** y la **Base de Datos** (el auditor tiene privilegios elevados — límite crítico dado que la cookie no tiene `HttpOnly`)

*(Cubre criterio 3 — este paso lo tienen que completar ustedes a mano.)*

## Paso 4 — Identificar amenazas

| Amenaza                                                                                                                                                                     | Activo afectado                                 |
| --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------- |
| Un administrador con acceso legítimo al panel consulta directamente la BD para ver qué opción votó un colegiado específico (voto e ID están en la misma tabla) — *insider*  | Voto / ID del votante                           |
| Un empleado con acceso al panel modifica manualmente el resultado de la votación antes del cierre de la elección — *insider*                                                | Voto                                            |
| El canal de correo (proveedor externo/tercero) es interceptado y el token de un solo uso es capturado antes de llegar al votante legítimo — *vector externo*                | Token del votante                               |
| Un atacante externo calcula el hash SHA-1 sin sal de cédulas de otros colegiados (dato semi-público) para predecir y usar sus tokens de votación                            | Token del votante / Cédula del votante          |
| Un atacante roba la cookie de sesión del panel de administración (ej. vía XSS, al no tener flag `HttpOnly`) y obtiene acceso de auditoría a toda la base de datos electoral | Cookie de sesión → expone Voto e ID del votante |

*(Cubre criterio 4 — cumple la mezcla obligatoria: 2 insider + 1 vector externo + 2 libres.)*

## Paso 5 — Evaluar riesgos

| Amenaza | Impacto | Probabilidad | Riesgo |
|---|---|---|---|
| Admin ve el voto de un colegiado específico | Alto | Media | Alto |
| Empleado modifica resultado antes del cierre | Alto | Baja | Medio |
| Interceptación del token vía correo | Alto | Media | Alto |
| Predicción de tokens (SHA-1 sin sal sobre cédula) | Alto | Alta | **Crítico** |
| Robo de cookie de sesión sin `HttpOnly` | Alto | Media | Alto |

*(Cubre criterio 5. La predicción de tokens es la más grave: no requiere acceso interno ni interceptar nada, solo conocer cédulas — que ya son semi-públicas en Costa Rica.)*

## Paso 6 — Mitigaciones desde el diseño

| Amenaza                                      | Mitigación desde diseño                                                                                                                                                                                                     |
| -------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Admin ve el voto de un colegiado específico  | Separación de datos por diseño: dos tablas desacopladas (una de "quién ya votó", sin la opción; otra de "opciones elegidas", sin identificador), vinculadas solo por un token efímero que se descarta al cerrar la elección |
| Empleado modifica resultado antes del cierre | Registro de auditoría inmutable (append-only, con hash encadenado) + separación de roles: ningún administrador individual puede alterar resultados sin doble aprobación                                                     |
| Interceptación del token vía correo          | No depender de un canal sin cifrar como único factor: enlace de un solo uso con expiración corta + verificación adicional al usarlo (ej. reingresar la cédula)                                                              |
| Predicción de tokens (SHA-1 sin sal)         | Autenticación fuerte en la generación: token aleatorio criptográficamente seguro (no derivado de la cédula), o HMAC-SHA256 con clave secreta del servidor + salt único                                                      |
| Robo de cookie de sesión sin `HttpOnly`      | Cifrado y configuración segura de sesión desde el diseño: cookies con `HttpOnly` + `Secure` + `SameSite`, y mínimo privilegio en lo que el panel de administración puede hacer sin reautenticación                          |

*(Cubre criterio 6.)*

## Checklist contra la rúbrica

- [x] 1. Comprensión del sistema
- [x] 2. Identificación de activos críticos (con priorización de 2)
- [ ] 3. Diagrama de Flujo de Datos — **pendiente, hacer a mano y pegar foto**
- [x] 4. Identificación de amenazas (2 insider + 1 externo + 2 libres)
- [x] 5. Evaluación de riesgos
- [x] 6. Mitigaciones desde el diseño
- [ ] 7. Claridad y coherencia final — revisar que el documento completo quede en 2-5 páginas antes de entregar
