---
curso: QA
tema: Criterios para Seleccionar Proyectos en GitHub
fecha: 2026-08-15
tipo: apunte
fuente: _fuentes/QA_criterios-seleccion-repositorio-github_2026-08-15.pdf
tags: [proyecto, seleccion-repositorio, github, requisitos]
---

# Criterios para Seleccionar Proyectos en GitHub

Ver también: [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]] · [[Cursos/QA/entregables/seleccion-repositorio-proyecto|Selección de repositorio — candidatos evaluados]] · [[Cursos/QA/entregas]]

> Esta es la nota que aclara en concreto lo que [[Cursos/QA/apuntes/proyecto-qa-guia|proyecto-qa-guia.md]] dejó como "criterios exactos por precisar": el proyecto no es con una empresa real, es elegir un repositorio de GitHub — de una **aplicación web** — que cumpla los 9 requisitos de abajo.

Los estudiantes deben elegir un **proyecto de aplicación web en GitHub** que cumpla con los siguientes requisitos.

## 1. Relevancia tecnológica

- Debe ser una **aplicación web**, desarrollada con tecnologías como JavaScript (React, Angular, Vue), Python (Django, Flask), Java (Spring Boot), Ruby on Rails, PHP (Laravel), entre otras.
- Debe tener una estructura clara de frontend y/o backend.

## 2. Mantenimiento activo

- Debe tener **commits recientes** (preferiblemente en los últimos 3-6 meses).
- Debe contar con **colaboradores activos** en el desarrollo y mantenimiento del código.

## 3. Historial de bugs y reportes

- El repositorio debe contar con una sección activa de **Issues**, donde se reporten errores o solicitudes de mejoras.
- Debe ser posible verificar cómo los desarrolladores gestionan y resuelven bugs.

## 4. Login y autenticación

- La aplicación web debe incluir funcionalidad de autenticación (login y registro de usuarios).
- Puede implementar autenticación con JWT, OAuth, sesiones, etc.

## 5. Popularidad y comunidad

- El repositorio debe tener una cantidad significativa de estrellas (stars) y forks, lo que indica que es utilizado y mantenido por la comunidad.
- Debe tener actividad en las issues y pull requests, lo que refleja una comunidad activa.

## 6. Documentación completa

- Debe incluir un archivo `README.md` con instrucciones claras de instalación y ejecución.
- Es ideal que tenga documentación adicional sobre el API o el funcionamiento interno.

## 7. Estructura del código y buenas prácticas

- El código debe estar bien organizado y modularizado.
- Debe seguir estándares de codificación, como ESLint para JavaScript, PEP8 para Python, etc.

## 8. Compatibilidad y dependencias

- Debe especificar dependencias en archivos como `package.json` (Node.js), `requirements.txt` (Python), `pom.xml` (Java).
- Si es posible, debe incluir configuración para entornos virtuales o contenedores Docker.

## 9. Accesibilidad y estándares web

- Si es una aplicación web con interfaz de usuario, debe considerar la posibilidad de múltiples idiomas.
- Debe seguir buenas prácticas de accesibilidad web (WCAG, ARIA).

## Importante

- **No se aceptarán proyectos que no sean aplicaciones web** (por ejemplo, scripts, software de escritorio, apps móviles, etc.).
- Si el proyecto tiene una API, esta debe estar documentada y ser funcional.
- Se recomienda verificar que el proyecto se pueda ejecutar localmente sin problemas.
