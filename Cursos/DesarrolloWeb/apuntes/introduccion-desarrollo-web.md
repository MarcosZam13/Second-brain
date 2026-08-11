---
curso: DesarrolloWeb
tema: Introducción al curso
fecha: 2026-08-07
tipo: apunte
fuente: _fuentes/DesarrolloWeb_introduccion-curso_2026-08-07.pptx
tags: [introduccion, web, roles, herramientas, proyecto-curso, flujo-ia]
---

# Introducción al curso — Desarrollo Web

Ver también: [[Cursos/DesarrolloWeb/temario]] · [[Cursos/DesarrolloWeb/entregas]] · [[Cursos/DesarrolloWeb/apuntes/gitflow-curso]] · [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise|arquitectura enterprise del repo base del profesor]]

## Objetivo y enfoque

- **Objetivo:** comprender cómo funciona la Web y crear aplicaciones modernas.
- **Enfoque práctico:** aprender construyendo.
- **Proyecto real con cliente** (contexto académico).
- **Tecnologías del curso:** HTML5, JavaScript, React, Next.js.

## Situación actual: realidad vs. mitos

Slide de arranque contrastando percepciones comunes sobre desarrollo web ("mitos") contra la realidad de la industria — sin detalle adicional en la diapositiva, se profundiza en clase.

## ¿Qué es la Web?

- **Internet:** infraestructura global de redes.
- **Web:** servicio que usa Internet para compartir información.
- La Web funciona con navegadores y servidores.
- Más información: [MDN — What is the Web](https://developer.mozilla.org/es/docs/Learn/Common_questions/Web_mechanics/What_is_the_Web)

## Cómo funciona una página web

- **URL:** dirección del recurso.
- **DNS:** traduce nombre a IP.
- **HTTP:** protocolo de comunicación.
- **Request:** solicitud del navegador.
- **Response:** respuesta del servidor.
- Más información: [MDN — How does the Internet work](https://developer.mozilla.org/es/docs/Learn/Common_questions/Web_mechanics/How_does_the_Internet_work) · [http.cat](https://http.cat/)

## Arquitectura básica de una aplicación web

- **Cliente:** navegador del usuario.
- **Servidor:** procesa solicitudes.
- **Base de datos:** almacena información.
- **API:** puente entre frontend y backend.
- Más información: [MDN — Server-side first steps](https://developer.mozilla.org/es/docs/Learn/Server-side/First_steps) · [Red Hat — What are APIs](https://www.redhat.com/es/topics/api/what-are-apis)

## Roles en desarrollo web

- **Frontend:** interfaz y experiencia del usuario.
- **Backend:** lógica y datos.
- **Fullstack:** frontend + backend.
- **UX/UI:** diseño y usabilidad.
- **QA:** calidad y pruebas.
- Más información: [roadmap.sh/frontend](https://roadmap.sh/frontend) · [roadmap.sh/backend](https://roadmap.sh/backend)

## Calidad en aplicaciones web

- **Usabilidad:** fácil de usar.
- **Mantenibilidad:** fácil de modificar.
- **Rendimiento:** carga rápida.
- **Accesibilidad:** usable por todos.
- Más información: [web.dev/learn](https://web.dev/learn/) · [NN/g — Usability 101](https://www.nngroup.com/articles/usability-101-introduction-to-usability/)

## Proyecto del curso

- Trabajo en equipos.
- **Cliente real** con expectativas realistas (contexto académico).
- **2 entregas** durante el curso (fechas aún no confirmadas — actualizar [[Cursos/DesarrolloWeb/entregas]] cuando el profesor las publique).
- Aprender a recibir feedback.
- Uso de repositorios y buenas prácticas — ver el flujo de git específico del curso en [[Cursos/DesarrolloWeb/apuntes/gitflow-curso]].

## Herramientas del curso

- **VS Code** — editor de código.
- **Navegador** — pruebas y depuración.
- **GitHub** — control de versiones.
- **Node.js** — entorno de ejecución.
- **Firebase**
- Más información: [code.visualstudio.com](https://code.visualstudio.com/) · [nodejs.org/es](https://nodejs.org/es) · [github.com](https://github.com/)

## Flujo de trabajo con agentes de IA (dado en clase)

Secuencia sugerida por el profesor para trabajar features con ayuda de IA, aplicable al proyecto del curso:

1. **Agregar agentes** al entorno de trabajo.
2. **Escribir la Spec de la feature** (describir componente, base de datos, backend, restricciones, etc.) — **100% humano, sin usar IA** en este paso.
3. **Entrevista con un agente:** pasarle la Spec a la IA; el agente hace preguntas y ayuda a pulir la spec.
4. Pedirle al agente que **cree el componente**.
5. Aplicar la **skill de unit testing**.
6. Al terminar de aplicar el feedback (si lo hubo), **pasar la tarea a QA**.

Este flujo es exactamente el que sigue el repo base que el profesor comparte a nivel empresarial (spec en `specs/SPEC.md`, ViewModel + Page Object Model para testing) — ver [[Cursos/DesarrolloWeb/apuntes/base-proyectos-arquitectura-enterprise|análisis completo]] y la skill reutilizable [[Sistema/skills/nextjs-enterprise-patterns/SKILL|nextjs-enterprise-patterns]].
