---
proyecto: DojoBase
tema: Repaso de GymBase v1 — qué se rescata, qué se descarta y qué faltaba
fecha: 2026-08-28
tipo: analisis
estado: completo — 29 módulos revisados, decisiones tomadas
tags: [dojobase, gymbase, alcance, repaso]
---

# Repaso de GymBase v1 — qué nos sirve

Ver también: [[Proyectos/DojoBase/documentacion-v1|documentacion-v1.md]] · [[Proyectos/DojoBase/historias-usuario|historias-usuario.md]] · [[Proyectos/DojoBase/DESIGN|DESIGN.md]] · [[Proyectos/GymBase/README|GymBase v1]]

Pasada módulo por módulo sobre los 29 de GymBase v1 (`Context/_ESTADO-ACTUAL.md`, los tres roadmaps y el código), para confirmar que nada útil quedó fuera del alcance de DojoBase. El primer recorte se hizo desde los specs; este se hace desde **lo que realmente está construido y funcionando**, que es donde aparecen las cosas que nadie documentó como requerimiento.

## Lo más importante: dos funciones que no estaban en ningún spec

### 1. El sparring tiene cronómetro, y es la mitad de la función

`sparring_challenges` en v1 guarda `total_rounds` y `round_duration_seconds` (por defecto 3 rounds de 180 s), y `SparringSessionModal.tsx` corre una máquina de cuatro fases: **timer → cargar resultado → descanso → resumen**, a pantalla completa.

Esto cambia la pantalla del marcador. No es "un formulario para anotar puntos": es **la herramienta que se usa durante el sparring**, con el celular apoyado al lado del tatami. El teclado de puntos que definimos encaja justo ahí — se anota mientras corre el round, no después.

Ninguno de los 9 specs lo mencionaba. Es el hallazgo más valioso de este repaso, y es exactamente el tipo de cosa que se pierde cuando se especifica desde documentos en vez de desde el producto que ya funciona.

**Entra al MVP**, integrado con el teclado de puntos.

### 2. La comunidad no es un foro, es el canal de anuncios del sensei

La policy de v1 se llama `posts_insert_admin_only`: **solo admin y owner publican**; los miembros comentan y reaccionan. Los posts tienen portada, se pueden fijar arriba, y se clasifican por categoría.

Esto importa porque cambia el diseño. Un foro libre necesita moderación, reportes y reglas de convivencia; un tablón de anuncios con comentarios no. Para un dojo el segundo modelo es el correcto — el sensei avisa del examen de cinturón, del cambio de horario, del resultado del torneo.

**Entra al MVP** con ese modelo, no como foro abierto.

---

## Veredicto módulo por módulo

### Entra al MVP

| Módulo de v1 | Qué se rescata | Cambios |
|---|---|---|
| Miembros y perfiles | Gestión completa, ficha por miembro | Ampliado con la ficha del alumno y datos de competencia |
| **Member intake** | Formulario de inscripción con datos personales, experiencia, lesiones y contacto de emergencia, más el guard que lo pide al entrar por primera vez | **Se fusiona con la ficha del alumno** — eran la misma cosa dicha dos veces. El guard de onboarding se conserva: es lo que garantiza que la ficha esté completa antes de que haga falta |
| Pagos y suscripciones | Planes, comprobantes, cola de períodos, plan recomendado | Sin cambios de fondo |
| Calendario y clases | Reserva, cupo, waitlist, asistencia por clase, clases privadas | **Recurrencia confirmada como obligatoria** (ver abajo) |
| **Comunidad** | Posts con portada, fijados, categorías, comentarios y reacciones | Modelo de anuncios, no foro |
| Contenido | Carpetas anidadas, gating por plan, favoritos, búsqueda | Sin cambios |
| Sistema de rangos | CRUD, **presets de escala precargados**, anillo de rango en el avatar | Ahora con estilo de progresión por disciplina |
| Multi-disciplina | Rango independiente por arte | Ahora es la única fuente de verdad |
| Fight record | Historial oficial, récord por disciplina | Con visibilidad configurable por el miembro |
| **Sparring** | Retos, notas, rivalidades, **cronómetro por rounds** | Más confirmación del rival y teclado de puntos |
| Ascensos con rúbrica | Eventos, criterios ponderados, grilla con guardado automático | Con los 11 casos borde resueltos |
| **Notificaciones** | In-app en tiempo real + push PWA + **correo** | Ver abajo |
| Contabilidad | Dashboard financiero del owner, cashflow, **exportaciones CSV/Excel/PDF** | Exclusivo de owner |
| PWA | Instalable, push por dispositivo, botón de instalar | Sin cambios |
| Seguridad | Rate limiting de login, RLS auditada | Reescrita sobre JWT |

### Entra como módulo opcional (`org_modules`)

| Módulo | Por qué opcional |
|---|---|
| Salud y mediciones | Un dojo la quiere para la categoría de peso, otro no la usa |
| Rutinas | Un dojo de competencia arma preparación física; uno tradicional no |
| Retos / challenges | Gamificación: útil para retener, prescindible para operar |
| Comunidad | Un dojo chico avisa por WhatsApp y no la necesita |

### Se descarta

| Módulo | Por qué |
|---|---|
| Check-in por QR y ocupación en vivo | Es el perfil de gimnasio de fitness. En un dojo la asistencia es por inscripción a clase |
| Inventario, ventas, POS | Vender productos es otro negocio. Si un dojo lo pide, se evalúa como módulo, no como parte del núcleo |
| Marketplace / tienda | Idem |
| Fotos de progreso | Perfil de gimnasio, y en v1 la feature ya estaba apagada |
| PRs y tests de 1RM | Perfil de gimnasio |
| Config por cliente en código (M17) | **Reemplazado** por `tenant_themes` + `org_modules`. Es justamente lo que estamos arreglando |

### Queda para v1.1

| Ítem | Por qué no ahora |
|---|---|
| Bracket automático de torneos | El modelo de datos entra; la UI de armado es el primer recorte acordado |
| Badges y niveles de challenges | La gamificación de la gamificación puede esperar |
| Google OAuth | Requiere dominio y consola configurada; el correo alcanza para arrancar |
| Drag-and-drop en el armado de rutinas | Comodidad, no capacidad |

---

## Lo que se confirma como obligatorio

### Clases recurrentes

v1 lo resuelve con `recurrence_group_id`, `recurrence_rule` y `recurrence_weeks`, y con la distinción entre **editar la serie completa** y **editar una sola ocurrencia**. Es lo correcto y no hay razón para simplificarlo: un dojo tiene el mismo horario todas las semanas, y crear las clases a mano cada lunes es exactamente el trabajo que la app tiene que quitar.

Lo que hay que respetar del diseño de v1: cancelar una clase puntual **no** rompe la serie, y editar la serie **no** pisa las excepciones ya hechas.

### Notificaciones por correo

v1 tiene tres canales y los usa distinto. Lo que entra tal cual:

| Evento | Canales |
|---|---|
| Membresía por vencer (3 días antes), vencida, aviso de recargo | **Correo** + in-app |
| Comprobante aprobado o rechazado | **Correo** + in-app |
| Clase cancelada | **Correo** + push + in-app |
| Recordatorio de clase próxima | Push + in-app |
| Reto de sparring recibido, resultado por confirmar | Push + in-app |
| Resultado de promoción | **Correo** + push + in-app |

El correo importa sobre todo en los pagos: un push se ignora, un correo con el monto y la fecha queda. Y es el único canal que llega si el alumno desinstaló la PWA.

Dos jobs, no uno: **recordatorio de membresía diario** y **recordatorio de clase cada 15 minutos** (para avisar con la antelación configurada). El de sparrings vencidos y suscripciones expiradas va con el diario.

### Kiosco de proyección de torneos

Pantalla pública de solo lectura, a pantalla completa, con zoom, para proyectar el bracket en vivo durante el torneo. En v1 refresca por `setInterval` cada 15 segundos — **acá va con Realtime de verdad**, que es justamente la pantalla que más lo justifica y la que la auditoría marcó como "realtime falso donde más importa".

---

## Cosas sueltas que valen la pena y no estaban

| Hallazgo | Decisión |
|---|---|
| **Presets de escala de rangos** (`SeedPresetsButton`): al crear una disciplina, cargar la escala de cinturones ya armada | Entra. Es la diferencia entre configurar un dojo en 3 minutos o en 40, y se ve en la demo de venta |
| **Editar perfil y foto** — quedó pendiente en v1 | Entra. Es de lo primero que un usuario intenta hacer |
| **Récord por disciplina** en la sección de peleas | Entra, ya está en la ficha del alumno |
| **Exportaciones** CSV, Excel y PDF en los reportes del owner | Entra. Un dueño quiere sus números en Excel |
| **Toggle de push por dispositivo** en el perfil | Entra. Sin esto la única salida del usuario es bloquear notificaciones en el navegador |
| **Página pública del dojo** (`gym_about`): historia, head coach, programas, entrenadores, logros, ubicación | **Propuesta**: entra, pero como contenido **editable desde la app**, no hardcodeado por cliente como en v1 — donde el editor de admin se removió y Marcos personalizaba en código. Es un activo de venta: el dojo puede mandar el link |
| **Política de privacidad y términos** dentro de la app | Entra. Es bloqueante del primer cobro, no un detalle |
| **Factura electrónica de Costa Rica** | **Fuera del MVP, pero hay que decidirlo antes de cobrar.** Es requisito legal para facturar, no una feature opcional. Se resuelve por fuera (un proveedor de facturación) o se integra después |

---

## Lo que este repaso confirma sobre el recorte original

De los 29 módulos de v1, **17 entran al MVP, 4 quedan como opcionales, 6 se descartan y 4 pasan a v1.1**. El recorte original acertó en lo grande — el perfil de gimnasio de fitness (QR, inventario, marketplace, PRs) sale limpio — y falló en dos cosas concretas:

1. Subestimó el sparring: le faltaba el cronómetro, que es la mitad de la función.
2. Sacó de un plumazo comunidad, correo y proyección de torneos, que son baratos de portar y de los que más se notan al usar el producto.

Ambos errores tienen la misma causa: **especificar desde documentos en vez de desde el producto que ya funciona.** Vale la pena repetir este repaso una vez más antes de cerrar el MVP, cuando ya estén las pantallas construidas.
