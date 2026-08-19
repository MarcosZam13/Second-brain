---
proyecto: Tacha
tema: Historias de Usuario — v1.0 (borrador)
fecha: 2026-08-18
tipo: documentacion
estado: borrador — reunión de equipo 2026-08-18, desglosando requerimientos en épicas/HU/CA; falta completar Sublistas, Listas privadas, Catálogo, Recetas, Planificador, Inventario y Grupos
tags: [historias-usuario, requerimientos, tacha]
---

# Historias de Usuario — Tacha (v1.0)

Ver también: [[Proyectos/Tacha/README|README]] · [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] (v2.1) · [[Proyectos/Tacha/DESIGN|DESIGN.md]]

> Borrador de la reunión de equipo del 2026-08-18, desglosando cada requerimiento de [[Proyectos/Tacha/documentacion-v1|documentacion-v1.md]] en épicas, historias de usuario (HU) y criterios de aceptación (CA), para dejar claros los módulos/pestañas/funciones antes de construir. El formato final de HU/CA puede cambiar — esto es el desglose de trabajo, no reemplaza documentacion-v1.md como fuente de los requerimientos de producto. Los requerimientos nuevos que salieron de este desglose (landing pública, autenticación extendida, invitación a household por link) ya están incorporados en [[Proyectos/Tacha/documentacion-v1#4.12 Acceso público y autenticación extendida (landing, about, auth)|documentacion-v1.md sección 4.12]] y en [[Proyectos/Tacha/DESIGN|DESIGN.md]].

## Roles

- **Mirones** (nombre interno) / **Visitante** (nombre de cara al usuario) — no autenticado.
- **Usuario** — autenticado.
- **Administrador**.

## Rol: Visitante

### Epic: Página de inicio

**HU-01: Barra de navegación**
Como visitante, quiero visualizar una barra de navegación en la página principal, para poder acceder fácilmente a las diferentes secciones disponibles de la plataforma.
- CA-01: La barra de navegación debe mostrar las opciones correspondientes a las secciones públicas disponibles.
- CA-02: Cada opción de navegación debe dirigir al visitante a la sección correspondiente.
- CA-03: La navegación debe funcionar correctamente sin que el visitante haya iniciado sesión.

**HU-02: Sección principal (Hero Section)**
Como visitante, quiero visualizar una sección principal con información relevante y una llamada a la acción (CTA), para conocer el propósito de la plataforma y acceder rápidamente a las funcionalidades principales.
- CA-01: La sección debe presentar información breve sobre el propósito de la plataforma.
- CA-02: La sección debe incluir al menos una llamada a la acción (CTA).
- CA-03: El CTA debe dirigir al visitante a la funcionalidad o sección correspondiente.
- CA-04: El contenido de la sección debe ser legible y visualizarse correctamente.

**HU-03: Información introductoria**
Como visitante, quiero visualizar una sección introductoria sobre la plataforma, para conocer brevemente sus características y propósito.
- CA-01: La página principal debe incluir una sección con información introductoria sobre la plataforma.
- CA-02: La información debe ser visible para cualquier visitante sin necesidad de iniciar sesión.
- CA-03: El contenido debe presentar una estructura visual que facilite su lectura.

**HU-04: Consultar información ampliada**
Como visitante, quiero acceder a información ampliada sobre la plataforma mediante la opción "Leer más", para conocer con mayor detalle sus características y beneficios.
- CA-01: La sección introductoria debe incluir una opción denominada "Leer más" o equivalente.
- CA-02: Al seleccionar la opción, el visitante debe ser dirigido a la información ampliada correspondiente.
- CA-03: La información ampliada debe estar disponible sin requerir autenticación.
- CA-04: La información presentada debe corresponder al contenido anunciado en la sección introductoria.
- CA-05: El visitante debe poder regresar a la página principal mediante los mecanismos de navegación disponibles.

**HU-05: Testimonios**
Como visitante, quiero visualizar testimonios de otros usuarios, para conocer sus experiencias y generar confianza en la plataforma.
- CA-01: La página principal debe incluir una sección de testimonios.
- CA-02: Cada testimonio debe mostrar la información definida para identificar al usuario que lo proporciona.
- CA-03: Los testimonios deben presentarse de manera clara y diferenciada.
- CA-04: La sección debe ser accesible sin necesidad de iniciar sesión.
- CA-05: Si los testimonios se presentan mediante un carrusel, el visitante debe poder desplazarse entre ellos mediante los controles disponibles.

**HU-06: Formulario de contacto (reCAPTCHA)**
Como visitante, quiero disponer de un formulario de contacto protegido mediante reCAPTCHA, para poder comunicarme con la organización de manera segura y evitar el envío automatizado de solicitudes.
- CA-01: La página debe proporcionar un formulario de contacto accesible para el visitante.
- CA-02: El formulario debe incluir los campos definidos como obligatorios para realizar una solicitud de contacto.
- CA-03: El sistema debe validar que los campos obligatorios hayan sido completados antes de permitir el envío.
- CA-04: El formulario debe incluir una validación mediante reCAPTCHA.
- CA-05: El sistema no debe permitir el envío del formulario cuando la validación reCAPTCHA no haya sido completada correctamente.
- CA-06: El sistema debe validar el formato de los datos ingresados cuando corresponda.
- CA-07: Una vez enviado correctamente el formulario, el visitante debe recibir una confirmación de que la solicitud fue procesada.
- CA-08: Si ocurre un error durante el envío, el sistema debe informar al visitante de manera clara.

**HU-07: Demo de uso**
Como visitante, quiero visualizar una demostración del funcionamiento de la plataforma, para comprender de manera sencilla cómo utilizarla.
- CA-01: La página principal debe incluir una sección destinada a mostrar una demostración del funcionamiento de la plataforma.
- CA-02: La demostración debe ser accesible sin necesidad de iniciar sesión.
- CA-03: El visitante debe poder reproducir la demostración mediante los controles disponibles.
- CA-04: El contenido de la demostración debe explicar o mostrar las funcionalidades principales de la plataforma.
- CA-05: La demostración debe visualizarse correctamente en los dispositivos contemplados por la plataforma.

### Epic: Pie de página (Footer)

**HU-08: Información del pie de página**
Como visitante, quiero visualizar un pie de página con información relevante de la plataforma, para acceder fácilmente a sus principales medios de contacto y recursos legales.
- CA-01: Las páginas públicas de la plataforma deben mostrar un pie de página.
- CA-02: El pie de página debe contener la información institucional definida para la plataforma.
- CA-03: El pie de página debe incluir los medios de contacto disponibles.
- CA-04: Los elementos del pie de página deben ser visibles y accesibles para el visitante.

**HU-09: Redes sociales**
Como visitante, quiero acceder a los enlaces de las redes sociales de la organización, para conocer sus diferentes canales de comunicación.
- CA-01: El pie de página debe mostrar los enlaces correspondientes a las redes sociales oficiales de la organización.
- CA-02: Cada enlace debe dirigir a la red social correspondiente.
- CA-03: Los enlaces deben ser identificables mediante texto, iconos o ambos.
- CA-04: Los enlaces deben funcionar correctamente.
- CA-05: El acceso a las redes sociales no debe requerir autenticación en la plataforma.

**HU-10: Términos y condiciones**
Como visitante, quiero consultar los términos y condiciones de la plataforma, para conocer las normas y condiciones asociadas a su utilización.
- CA-01: El pie de página debe incluir un enlace a los términos y condiciones.
- CA-02: El visitante debe poder acceder a los términos y condiciones sin iniciar sesión.
- CA-03: El enlace debe dirigir al documento o sección correspondiente.
- CA-04: El contenido debe presentar de manera clara las condiciones de uso de la plataforma.
- CA-05: El visitante debe poder regresar a la página desde la que accedió a los términos y condiciones.

**HU-11: Logotipo**
Como visitante, quiero visualizar el logotipo de la organización en el pie de página, para identificar visualmente la plataforma.
- CA-01: El pie de página debe mostrar el logotipo oficial de la organización.
- CA-02: El logotipo debe visualizarse correctamente y mantener sus proporciones.
- CA-03: El logotipo debe ser reconocible y mantenerse visible en los dispositivos contemplados.
- CA-04: Si el logotipo funciona como enlace, este debe dirigir a la página principal de la plataforma.

### Epic: Acerca de (About)

**HU-12: Misión y visión**
Como visitante, quiero consultar la misión y visión de la organización, para conocer su propósito, objetivos y orientación.
- CA-01: La sección "About" debe presentar la misión de la organización.
- CA-02: La sección "About" debe presentar la visión de la organización.
- CA-03: La misión y visión deben estar claramente diferenciadas.
- CA-04: La información debe estar disponible para cualquier visitante sin necesidad de iniciar sesión.
- CA-05: El contenido debe ser legible y presentarse de manera organizada.

**HU-13: Información de la organización**
Como visitante, quiero consultar información general sobre la organización, para conocer su origen, propósito y principales características.
- CA-01: La sección "About" debe presentar información general sobre la organización.
- CA-02: La información debe incluir los aspectos institucionales definidos para la plataforma.
- CA-03: El contenido debe estar organizado de manera que facilite su comprensión.
- CA-04: La información debe ser accesible sin necesidad de iniciar sesión.
- CA-05: El contenido debe visualizarse correctamente en los dispositivos contemplados por la plataforma.

**HU-14: Contacto desde About (reCAPTCHA)**
Como visitante, quiero disponer de un formulario de contacto protegido mediante reCAPTCHA en la sección "About", para comunicarme con la organización de forma segura.
- CA-01: La sección "About" debe incluir un formulario de contacto.
- CA-02: El formulario debe incluir los campos definidos como necesarios para realizar una solicitud.
- CA-03: El sistema debe validar los campos obligatorios antes de permitir el envío.
- CA-04: El formulario debe contar con protección mediante reCAPTCHA.
- CA-05: El sistema no debe permitir el envío si el reCAPTCHA no ha sido validado correctamente.
- CA-06: El sistema debe validar el formato de los datos ingresados cuando corresponda.
- CA-07: Después de un envío exitoso, el visitante debe recibir un mensaje de confirmación.
- CA-08: En caso de producirse un error, el sistema debe mostrar un mensaje informativo al visitante.

### Epic: Registro manual

**HU-14b: Registro con datos básicos**
Como visitante, quiero registrarme ingresando mis datos personales y una contraseña, para crear una cuenta en el sistema.
- El formulario solicita nombre, correo electrónico, contraseña y repetir contraseña.
- El sistema valida que todos los campos obligatorios estén completos antes de habilitar el botón de registro.
- El sistema muestra mensajes de error claros si algún campo es inválido o falta.
- No se permite el registro si el correo ya existe en el sistema.

**HU-15: Validar coincidencia de contraseña**
Como visitante, quiero que el sistema valide que la contraseña y su repetición coincidan, para evitar errores de digitación al crear mi cuenta.
- Si "Contraseña" y "Repetir Contraseña" no coinciden, se muestra un mensaje de error en tiempo real.
- El botón de registro permanece deshabilitado si las contraseñas no coinciden.

**HU-16: Feedback de seguridad de contraseña**
Como visitante, quiero ver una indicación visual de qué tan segura es la contraseña que estoy creando, para elegir una contraseña robusta.
- El sistema evalúa la contraseña mientras la escribe según criterios como longitud, mayúsculas, minúsculas, números y caracteres especiales.
- Se muestra un indicador visual tipo barra de progreso.
- Se informan los requisitos mínimos no cumplidos (ej. "debe incluir al menos un número").

**HU-17: Verificación de correo electrónico**
Como visitante, quiero recibir un correo electrónico después de registrarme, para confirmar que mi cuenta y dirección de correo son válidas.
- Al completar el registro, se envía automáticamente un correo con un enlace o código de verificación.
- La cuenta queda en estado "pendiente de verificación" hasta que el usuario lo confirme.
- El código de verificación tiene un tiempo de expiración definido.
- El usuario puede solicitar el reenvío del correo de verificación si no lo recibió.
- Se muestra un mensaje de confirmación cuando la verificación es exitosa.

**HU-18: Aceptación de términos y condiciones**
Como visitante, quiero aceptar los términos y condiciones antes de completar mi registro, para cumplir con las políticas legales del sistema.
- Se muestra un checkbox de aceptación de términos y condiciones, no marcado por defecto.
- El registro no puede completarse si el checkbox no está marcado.
- El usuario puede acceder al texto completo de los términos y condiciones antes de aceptar.

### Epic: Registro con Google/Facebook

**HU-19: Registro mediante proveedor externo**
Como visitante, quiero registrarme usando mi cuenta de Google o Facebook, para crear mi cuenta de forma rápida sin llenar un formulario extenso.
- Se muestran botones de "Registrarse con Google" y "Registrarse con Facebook".
- Al seleccionar una opción, el sistema redirige al flujo de autenticación OAuth del proveedor correspondiente.
- El sistema obtiene y valida la identificación del usuario (correo, nombre) desde el proveedor.
- Si el correo ya está registrado, se informa al usuario y se sugiere iniciar sesión en su lugar.

**HU-20: Completar datos faltantes tras registro social**
Como visitante, quiero completar los datos que Google/Facebook no proporcionan, para finalizar mi perfil correctamente.
- Tras la autenticación exitosa con el proveedor, se muestra un formulario con los campos faltantes requeridos por el sistema.
- El sistema valida que los campos obligatorios estén completos antes de crear la cuenta.
- La cuenta no se considera completa/activa hasta que estos datos sean ingresados.

**HU-21: Aceptación de términos y condiciones en registro social**
Como visitante, quiero aceptar los términos y condiciones al registrarme con Google/Facebook, para cumplir con las políticas legales del sistema, igual que en el registro manual.
- Se muestra el checkbox de términos y condiciones como parte del flujo posterior a la autenticación social.
- El registro no se completa si no se aceptan términos y condiciones.
- El usuario puede consultar el texto completo de los términos y condiciones.

### Epic: Login

**HU-22: Inicio de sesión con validación reCAPTCHA**
Como visitante, quiero que el sistema valide que no soy un robot al iniciar sesión, para proteger mi cuenta contra ataques automatizados.
- El formulario del login incluye un componente reCAPTCHA.
- El sistema no procesa el intento de login si el reCAPTCHA no se completa o falla.
- Se muestra un mensaje de error si la validación de reCAPTCHA no es exitosa.

**HU-23: Mostrar/ocultar contraseña**
Como visitante, quiero poder mostrar u ocultar la contraseña que escribo, para verificar que la ingresé correctamente.
- El campo de contraseña incluye un ícono tipo "ojo" para alternar la visibilidad.
- Al hacer clic, el texto cambia entre oculto (puntos) y visible (texto plano).
- El estado por defecto del campo es oculto.

**HU-24: Mensajes de error en login**
Como visitante, quiero recibir mensajes claros cuando mis credenciales son incorrectas, para entender por qué no pude iniciar sesión.
- Se muestra un mensaje de error genérico (sin especificar qué es lo que está mal) para credenciales inválidas.
- Se muestran mensajes específicos para otros casos: cuenta no verificada, cuenta bloqueada, cuenta inactiva.
- Los mensajes de error son visibles y no bloquean el formulario para reintentar.

**HU-25: Feedback de seguridad de contraseña en login**
Como visitante, quiero que el sistema me indique si mi contraseña cumple los estándares de seguridad al momento de iniciar sesión (en caso de cambios forzados), para mantener mi cuenta protegida.
- Si el sistema detecta una contraseña débil o vencida según política, se notifica al usuario.
- Se ofrece la opción de actualizar la contraseña desde el mismo flujo, cuando aplique.

**HU-26: Token de seguridad de sesión**
Como visitante, quiero que mi sesión esté protegida mediante un token de seguridad, para garantizar que mis datos e identidad estén protegidos durante el uso del sistema.
- Al iniciar sesión exitosamente, el sistema genera un token de sesión (ej. JWT).
- El token tiene un tiempo de expiración definido.
- Las peticiones al sistema requieren un token válido; de lo contrario, se redirige al login.

**HU-27: Cierre de sesión por inactividad**
Como visitante, quiero que mi sesión se cierre automáticamente tras un periodo de inactividad, para proteger mi cuenta si olvido cerrar sesión.
- El sistema contabiliza el tiempo transcurrido desde la última acción del usuario (clics, navegación, etc.).
- Al superar el tiempo límite definido (configurable), la sesión se cierra automáticamente.
- Se muestra una notificación indicando que la sesión expiró por inactividad.
- El usuario es redirigido a la pantalla de login.

### Epic: Recuperación de contraseña

**HU-28: Recuperación de contraseña**
Como visitante, quiero solicitar la recuperación de mi contraseña ingresando mi correo, para poder recuperar el acceso a mi cuenta si la olvidé.
- Existe un enlace "¿Olvidaste tu contraseña?" en la pantalla de login.
- El usuario ingresa su correo electrónico registrado.
- El sistema envía un correo con un enlace/código para restablecer la contraseña, si el correo existe.
- Se muestra un mensaje genérico de confirmación (sin revelar si el correo existe, por seguridad).

**HU-29: Vista de actualización de contraseña**
Como visitante, quiero acceder a una vista donde pueda definir una nueva contraseña tras solicitar la recuperación, para restablecer el acceso a mi cuenta.
- Al hacer clic en el enlace recibido por correo, se muestra un formulario con "Nueva contraseña" y "Repetir nueva contraseña".
- El sistema valida que ambos campos coincidan.
- Se muestra el feedback de seguridad de la contraseña (igual que en el registro).
- El enlace de recuperación tiene un tiempo de expiración; si venció, se informa al usuario y se ofrece reenviar la solicitud.
- Al actualizar la contraseña exitosamente, se muestra confirmación y se redirige al login.

## Rol: Usuario

### Sidebar / Perfil

- Logout.
- Editar datos de perfil.
- Cambiar contraseña (con repetir contraseña).

### Gestión del grupo familiar (household)

- Como usuario puedo crear un link de invitación familiar.
- Como usuario puedo consultar familiares.
- Como usuario puedo eliminar familiares.
- Modificar / filtrar / paginar (back-end) sobre la tabla de miembros.

### Lista general

**Buscar y añadir producto**
Como usuario, quiero buscar productos en una barra de búsqueda y añadirlos a mi lista de compras, para armar mi lista rápidamente sin tener que navegar a otra pantalla.
- Se muestra una barra de búsqueda en la parte superior de la vista principal (to-do list).
- Al escribir, el sistema muestra en tiempo real los productos del catálogo que coinciden con el texto ingresado.
- Al seleccionar un producto de los resultados, este se añade a la lista con una cantidad por defecto de 1.
- El producto añadido aparece de inmediato como una fila en la lista, sin recargar la pantalla.

**Ajustar cantidad**
Como usuario, quiero incrementar o decrementar la cantidad de un producto en mi lista, para ajustar cuánto necesito comprar sin tener que eliminarlo y volver a añadirlo.
- Cada producto en la lista muestra controles de "+" y "-" junto a la cantidad actual.
- Al tocar "+", la cantidad aumenta en 1.
- Al tocar "-", la cantidad disminuye en 1, sin poder bajar de 1.
- El cambio se refleja de inmediato en la fila, sin necesidad de confirmación adicional.

**Ver detalle de producto**
Como usuario, quiero ver los detalles de un producto añadido a mi lista, para ver marcas, presentación y precios de diferentes supermercados. *(pendiente de detallar entre todo el equipo)*
- Al tocar la fila del producto (fuera del checkbox y de los controles de cantidad), se despliega o navega a una vista de detalle.
- La vista de detalle muestra marca, presentación/variante y precio de referencia (si existe).

**Eliminar producto**
Como usuario, quiero eliminar un producto de mi lista, para quitar algo que agregué por error o que ya no necesito.
- Cada producto en la lista tiene una acción de eliminar (ícono por definir).
- Al eliminar, el producto se remueve de la lista de inmediato.
- Se muestra un toast breve de confirmación ("Producto eliminado") con opción de deshacer.

**Tachar/destachar producto**
Como usuario, quiero tachar un producto de mi lista al comprarlo, para llevar control de lo que ya conseguí sin borrarlo de la lista.
- Cada producto en la lista tiene un checkbox para marcarlo como comprado.
- Al tocar el checkbox, el producto se marca visualmente como tachado sin eliminarse de la lista.
- Al tocar el checkbox de nuevo, el producto vuelve al estado pendiente (destachado).

**Pendientes de desglosar en HU (mencionados, sin CA todavía):**
- Realizar compra (modo compra).
- Combinar listas, sublistas.

### Dashboard financiero (Finanzas)

- Como usuario puedo ver el gasto total por día/semana/mes.
- Como usuario puedo ver los gastos por familia/listas privadas.
- Como usuario puedo ver los gastos por categoría de producto.
- Como usuario puedo ver los gastos por supermercado.
- Como usuario puedo ver los gastos por persona (quién compra/gasta más).
- Como usuario puedo ver los productos específicos más comprados.
- Como usuario puedo ver los productos específicos más costosos.
- Aviso siempre visible de que los precios son estimados.

### Pendientes de desglosar en HU/CA

Listados en la reunión, sin HU/CA todavía:

- Sublistas por fecha
- Listas privadas
- Catálogo de productos y categorías
- Historial de compras
- Filtrado de compra
- Recetas
- Planificador semanal de comidas
- Inventario doméstico
- Grupos de productos
