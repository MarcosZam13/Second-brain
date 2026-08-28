---
proyecto: CoreBase
tema: Una página por marca — dominios, login con identidad del dojo, y por qué no repite el error de v1
fecha: 2026-08-28
tipo: documentacion
estado: decisión tomada, pendiente de implementar
tags: [corebase, dojobase, multi-tenant, auth, dominios]
---

# Una página por marca

Ver también: [[Proyectos/CoreBase/arquitectura|arquitectura.md]] · [[Proyectos/CoreBase/seguridad-jwt-rls|seguridad-jwt-rls.md]] · [[Proyectos/CoreBase/realtime|realtime.md]] · [[Proyectos/DojoBase/DESIGN|DESIGN.md]]

## La pregunta

Hoy DojoBase es una sola aplicación: todos entran por el mismo `/login`, que se ve genérico porque antes de iniciar sesión no hay sesión, no hay organización, y por lo tanto no hay tema.

Lo que se quiere: **que cada dojo tenga su propia página**, con su logo y sus colores desde la pantalla de entrada, y su propio flujo de registro y recuperación de contraseña. Que el alumno sienta que entra a *su* dojo, no a una plataforma que lo atiende.

Es lo que hacía GymBase v1, y es correcto.

## La respuesta corta: sí, y no choca con nada

Pero hay una distinción que hay que dejar clavada, porque es **exactamente donde v1 se equivocó** y es fácil volver a caer:

| | Cómo se resuelve | Por qué |
|---|---|---|
| **Quién sos y qué podés ver** (autorización) | **Siempre por el claim del JWT.** Nunca por el dominio | Es el dato que usa el RLS. Si dependiera del dominio, cualquier cliente que no pase por el servidor web —empezando por Realtime— quedaría sin tenant y la base denegaría todo en silencio |
| **De quién es esta página** (presentación) | **Por el dominio o el subdominio** | Antes de iniciar sesión no hay JWT. Es la única forma de saber de quién es el logo que se muestra |

En v1 estas dos cosas eran la misma, y el resultado fue un año de tiempo real roto. Acá son dos mecanismos separados que nunca se tocan:

- El dominio decide **qué se pinta** antes de entrar.
- El JWT decide **qué se puede leer** después de entrar.

Un atacante que se invente un subdominio ve el logo de otro dojo y nada más: sin sesión válida no alcanza un solo dato.

## Cómo funciona

### Resolución pública de marca

Una función que, dado un `slug`, devuelve **solo lo público** de una organización: nombre, logo y tema. Nada más — ni cantidad de miembros, ni si existe determinado correo.

```sql
create or replace function public.marca_publica(p_slug text)
returns table (org_id uuid, name text, logo_url text, colors jsonb, chart jsonb, radius text)
language sql stable security definer set search_path = '' as $$
  select o.id, o.name, o.logo_url, t.colors, t.chart, t.radius
  from public.organizations o
  left join public.tenant_themes t on t.org_id = o.id
  where o.slug = p_slug;
$$;
```

Es `SECURITY DEFINER` y ejecutable por `anon` **a propósito**: tiene que funcionar sin sesión. Lo que la hace segura no es el permiso, es que **no hay nada sensible en lo que devuelve**. Esa es la condición que hay que mantener si algún día se le agrega una columna.

Que un slug exista o no es información pública de todos modos: el dojo va a repartir su enlace.

### El dominio

Dos formas, las dos soportadas por la misma resolución:

- **Subdominio**: `shoto.dojobase.app`. Es el default y no requiere nada del dojo.
- **Dominio propio**: `dojoshoto.com`. Para el dojo que quiera invertir en su marca; se resuelve con una columna `custom_domain` en `organizations`.

El middleware lee el host, saca el slug, y lo deja disponible para las pantallas públicas. **Solo para pintar.** El middleware sigue sin tocar la autorización — esa regla no se negocia.

### Al iniciar sesión en una página de marca

Si el usuario pertenece a ese dojo, su organización activa pasa a ser ese dojo. Resuelve dos cosas de una: alguien que entrena en dos escuelas entra a la correcta según el enlace que abrió, y desaparece la pantalla de "elegí tu organización" en el caso normal.

Si no pertenece, se le dice con claridad — no se le muestra un error de credenciales, que confundiría dos problemas distintos.

## Lo que falta del módulo de autenticación

El login de v1 era bueno y acá está incompleto. Hoy solo hay iniciar sesión. Falta:

| Falta | Por qué importa |
|---|---|
| **Crear cuenta al aceptar una invitación** | Hoy la pantalla de invitación manda a `/login`, y quien nunca tuvo cuenta se queda sin salida. Es un hueco real del flujo, no una mejora |
| **Recuperación de contraseña** | Sin esto, cada olvido es un mensaje al sensei |
| **Confirmación de correo** | Un correo mal escrito deja al alumno sin forma de recuperar su cuenta |
| **Google** | Menos fricción, y evita una contraseña más |
| **Límite de intentos de login** | v1 lo tenía en 5 cada 15 minutos. Es lo mínimo contra fuerza bruta |

**Sobre el registro:** RF-19 dice que no hay autoregistro público, y se mantiene. Crear cuenta **solo se puede desde una invitación válida** — la cuenta se crea, pero la pertenencia al dojo sale de la invitación, nunca de quien se registra. Que exista un formulario de registro no significa que cualquiera pueda entrar a un dojo.

## Qué cambia en el diseño

Tres pantallas públicas nuevas, todas con la marca del dojo:

| Pantalla | Nota |
|---|---|
| Entrada del dojo | Logo, nombre y colores del dojo. Es la primera impresión del producto para un alumno |
| Crear cuenta desde invitación | Muestra a qué dojo entra y con qué rol antes de pedir datos |
| Recuperar contraseña | Dos pasos, con la marca del dojo |

El `DESIGN.md` las agrega al inventario. La landing de venta de DojoBase (`apps/marketing`) es otra cosa y no se mezcla: esa lleva la marca de **DojoBase**, no la del dojo.

## El costo, dicho de frente

- **Certificados y DNS por dominio propio.** Con subdominios es automático; con dominio propio hay un trámite por cliente. No es desarrollo, es operación, y conviene cobrarlo aparte.
- **Una organización que no existe** tiene que dar una pantalla decente, no un error del servidor.
- **La página pública se cachea distinto**: no depende de la sesión, así que puede servirse desde caché por slug. Es una ventaja, pero hay que invalidarla al cambiar el tema.

## La regla que queda escrita

> El dominio decide **qué marca se muestra**. El JWT decide **qué datos se pueden leer**. Ningún código puede usar el dominio para decidir acceso, y ninguna consulta puede depender de que el servidor web haya inyectado algo.
>
> La prueba: si mañana se borra el middleware, la aplicación debe seguir siendo **segura** — solo dejaría de verse bonita antes de entrar.
