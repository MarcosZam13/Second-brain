---
curso: QA
tema: Plan del proyecto — Fase 1
fecha: 2026-08-17
tipo: entregable
entregable_de: "[[Cursos/QA/apuntes/proyecto-qa-guia]]"
estado: borrador
tags: [proyecto, firefly-iii, fase1, plan-del-proyecto]
---

# Plan del proyecto — Fase 1

Ver también: [[Cursos/QA/entregables/mapeo-modulos-firefly-iii|Mapeo de módulos — Firefly III]] · [[Cursos/QA/entregables/seleccion-repositorio-proyecto|Selección de repositorio]] · [[Cursos/QA/apuntes/proyecto-qa-guia|Guía del Proyecto]] · [[Cursos/QA/entregas]]

**Estado:** contenido completo en borrador, según los 11 ítems de la estructura oficial (ver [[Cursos/QA/apuntes/proyecto-qa-guia]]). Entrega: **Semana 6**, del lunes 7 al domingo 13 de septiembre de 2026 (confirmado por Marcos: la semana 5 arrancó el lunes 31 de agosto). Falta el trabajo de formato: portada, tabla de contenidos e índice de tablas, y que el equipo revise y valide el contenido antes de entregarlo.

**Repositorio elegido:** [firefly-iii/firefly-iii](https://github.com/firefly-iii/firefly-iii), un gestor de finanzas personales de código abierto y autohospedado, hecho en Laravel/PHP con Vue en el frontend. La justificación completa de por qué se eligió está en [[Cursos/QA/entregables/seleccion-repositorio-proyecto]].

## Introducción

### Qué

Este proyecto aplica los procesos de calidad de software que se han visto en el curso (planeación, verificación y validación) sobre Firefly III, un gestor de finanzas personales de código abierto y autohospedado. En esta edición del curso el proyecto no se hace sobre una empresa real con contraparte, sino sobre un repositorio de GitHub elegido por el equipo (ver la corrección al respecto en [[Cursos/QA/apuntes/proyecto-qa-guia]]). El equipo escogió Firefly III siguiendo los 9 criterios que pidió la profesora, descritos en [[Cursos/QA/apuntes/criterios-seleccion-repositorio-github]].

### Por qué

La gestión de las finanzas personales es un problema con impacto social real. No llevar un registro claro de los ingresos y los gastos es uno de los factores que más contribuye al sobreendeudamiento, y buena parte de las aplicaciones de finanzas personales más usadas hoy en día piden conectar las cuentas bancarias a servidores externos para funcionar. Eso genera fricción para las personas que no quieren compartir información tan sensible con un tercero, y las deja sin muchas alternativas si igual quieren llevar el control de su dinero.

Firefly III responde a ese problema porque es completamente autohospedado: los datos financieros nunca salen del servidor del propio usuario. Eso lo convierte en una opción real para quienes les preocupa la privacidad de su información financiera, algo que las aplicaciones que dependen de la nube no ofrecen. Y validar que una herramienta así funcione bien no es un detalle menor, porque un error en el cálculo de saldos, presupuestos o transacciones recurrentes afecta directamente decisiones financieras reales de la persona que la usa.

### Cómo

El proyecto sigue las 5 fases del curso. Primero la identificación del problema y la definición de objetivos, que es esta misma fase y se entrega en la semana 6. Luego la planeación, donde se construye el plan de pruebas con al menos 60 casos y 3 tipos de prueba distintos, que se entrega en la semana 11. Después viene el diseño, desarrollo y evaluación, donde se automatiza al menos el 90% de esos casos de prueba y se documentan los defectos encontrados en un informe, entregables que caen entre la semana 15 y la 16. La comunicación de resultados es una presentación en inglés en la semana 16. Y en paralelo a todo esto corre la fase de reflexión, que es el diario individual desde la semana 2 hasta la 16 y se lleva aparte de este documento.

### Limitaciones

El equipo trabaja sobre el código tal como está publicado en el repositorio. No hay acceso a datos de usuarios reales en producción, solo a datos de prueba generados localmente. El alcance de las pruebas se limita a los módulos de alta y media prioridad que se identificaron en [[Cursos/QA/entregables/mapeo-modulos-firefly-iii]] (autenticación, cuentas, transacciones, presupuestos, categorías, facturas, recurrentes, reglas, piggy banks y monedas); los módulos administrativos o de soporte como Admin, Webhooks o Export quedan fuera del alcance a menos que sobre tiempo para cubrirlos. Tampoco hay una contraparte de negocio que valide los requerimientos: estos se sacaron del comportamiento observado y documentado del sistema, no de una entrevista con alguien del proyecto real.

## Especificaciones del software

Firefly III corre sobre PHP 8.5 o superior, con el framework Laravel en su versión 13. El frontend está en transición entre dos interfaces: la interfaz nueva (v2) usa Vite y Bootstrap 5, mientras que buena parte de las pantallas todavía activas siguen corriendo sobre la interfaz anterior (v1), construida con Vue 2.7 y Bootstrap 3. Esto es relevante para el proyecto porque significa que no toda la aplicación se puede tratar como una sola SPA moderna a la hora de automatizar pruebas de interfaz: hay pantallas servidas por Blade con islas de Vue 2 y pantallas más nuevas hechas con Vite.

Como base de datos, la configuración oficial de Docker usa MySQL (variable `DB_CONNECTION=mysql` en el `.env` de ejemplo del repo). El despliegue se hace con el `docker-compose` oficial del proyecto, que el equipo ya probó y confirmó que funciona: los contenedores levantan sin problema y se puede iniciar sesión en `http://localhost/login` (verificado el 17 de agosto). No se encontró en el repositorio una lista oficial de navegadores soportados, así que eso queda pendiente de definir con criterio propio del equipo (los navegadores modernos más comunes: Chrome, Firefox y Edge en sus versiones actuales).

## Requerimientos del sistema

Estos requerimientos salen del mapeo de módulos ([[Cursos/QA/entregables/mapeo-modulos-firefly-iii]]) y se verificaron contra el código fuente del repositorio, no solo contra la documentación.

**Funcionales**, por módulo de alta y media prioridad:
1. El sistema debe permitir registrar e iniciar sesión, incluyendo autenticación de dos factores (2FA).
2. El sistema debe permitir crear, editar y eliminar cuentas financieras de distintos tipos (activo, pasivo, gasto, ingreso).
3. El sistema debe permitir registrar transacciones de gasto, ingreso y transferencia entre cuentas propias, manteniendo la consistencia contable de doble entrada.
4. El sistema debe permitir definir presupuestos por categoría y período, calculando correctamente el monto disponible restante.
5. El sistema debe permitir clasificar las transacciones por categoría y por etiqueta.
6. El sistema debe permitir definir facturas o gastos recurrentes esperados y hacer coincidencia automática contra las transacciones reales que se van registrando.
7. El sistema debe permitir automatizar la creación de transacciones recurrentes según una programación temporal definida por el usuario.
8. El sistema debe permitir definir reglas condicionales que clasifiquen transacciones automáticamente según criterios que el usuario configure.
9. El sistema debe permitir crear metas de ahorro (piggy banks) con seguimiento del progreso.
10. El sistema debe soportar múltiples monedas, con conversión correcta según las tasas de cambio.

**No funcionales:**
- El sistema debe poder desplegarse localmente con Docker, usando el `docker-compose` oficial, sin depender de servicios externos que no estén documentados.
- El sistema debe exponer una API REST que cubra las operaciones principales, para poder automatizar pruebas más allá de la interfaz web.
- El sistema debe aislar correctamente los datos financieros entre distintos usuarios o grupos de usuarios (UserGroup).

## Problema

El problema central que motiva este proyecto es que muchas personas no tienen forma de llevar un control ordenado de sus finanzas personales sin exponer su información bancaria a servidores de terceros.

**Causas**, de la más general a la más puntual:
- Las personas no tienen el hábito de registrar sus ingresos y gastos de forma consistente.
- Las aplicaciones de finanzas personales más populares están construidas sobre un modelo cloud first, donde hay que conectar las cuentas bancarias directamente a los servidores de la empresa que ofrece el servicio.
- Muchos usuarios evitan usar esas aplicaciones porque no confían en compartir sus credenciales bancarias con un tercero, o porque el servicio simplemente no está disponible o tiene costo en su país.

**Efectos**, partiendo del problema hacia lo más general:
- Quien no lleva un control de sus finanzas tiende a tomar decisiones financieras mal informadas, lo que contribuye al sobreendeudamiento.
- Esto se traduce en más estrés financiero y menos capacidad real de ahorro.
- Como alternativa, muchas personas terminan usando hojas de cálculo manuales, que son más propensas a errores humanos que una herramienta pensada para eso.

Este árbol de problemas se construyó siguiendo la metodología del taller de la profesora (ver [[Cursos/QA/apuntes/taller-arbol-problemas-objetivos]]). Falta pasarlo a diagrama visual para el documento final, pero el contenido y el orden de causas y efectos ya está definido.

## Objetivos

### Objetivo general

Evaluar la calidad del software de Firefly III aplicando un proceso de pruebas (planeación, diseño, ejecución y análisis de resultados) sobre sus módulos financieros críticos, con el fin de determinar qué tanto cumple sus requerimientos funcionales y detectar los defectos que pueda tener.

### Objetivos específicos, metas e indicadores

| Objetivo específico | Metas | Indicadores |
|---|---|---|
| Analizar los requerimientos funcionales de los módulos de alta y media prioridad de Firefly III para delimitar el alcance de las pruebas | Revisar el código fuente de cada módulo (no solo la documentación); consultar con el equipo cuáles módulos quedan dentro y cuáles fuera del alcance | Documento de requerimientos completo antes de la semana 6; al menos 10 módulos cubiertos entre alta y media prioridad |
| Diseñar un plan de pruebas con al menos 60 casos, cubriendo 3 tipos de prueba distintos, con un máximo de 10% de casos manuales | Definir las técnicas de prueba a usar; escribir cada caso con el formato que dio la profesora | 60 o más casos de prueba definidos antes de la semana 11; 3 tipos de prueba distintos aplicados; 90% o más de los casos marcados como automatizables |
| Automatizar al menos el 90% de los casos de prueba diseñados | Elegir el framework de pruebas adecuado al stack (PHP/Laravel) o trabajar directo contra la API REST; escribir y correr las pruebas automatizadas | 90% o más de los 60+ casos ejecutándose de forma automática antes de la semana 15 |
| Ejecutar el plan de pruebas y documentar los defectos encontrados en un informe de pruebas | Correr todas las pruebas automatizadas; registrar cada defecto en el formato de fichas dado por la profesora | Informe de pruebas entregado en la semana 16, con todos los defectos encontrados descritos y con evidencia |
| Comunicar los resultados del proyecto en una presentación en inglés | Preparar la presentación y ensayarla como equipo antes de la fecha | Presentación de 20 minutos más 10 de preguntas, dentro del tiempo pactado, en la semana 16 |

## Recursos disponibles

El equipo cuenta con los siguientes recursos para llevar a cabo el proyecto:

- **Humanos:** los integrantes del equipo (3 a 4 personas según lo que pide el curso), cada uno con acceso a su propio entorno de desarrollo.
- **Infraestructura:** cada integrante puede levantar Firefly III localmente con Docker, usando el `docker-compose` oficial del proyecto, ya probado y funcionando desde el 17 de agosto.
- **Herramientas:** GitHub para el control de versiones y coordinación del equipo, y el framework de pruebas que se termine de elegir en la Fase 2 según el stack del repositorio (Laravel/PHP) o pruebas directas contra la API REST.
- **Tiempo:** desde ahora (semana 5) hasta la semana 16, repartido entre las cinco fases del curso.
- **Acceso a la información:** el código fuente completo del repositorio está disponible públicamente en GitHub, junto con sus issues, historial de commits y documentación.

## Cronograma de actividades

| Semana | Actividad |
|---|---|
| 5 (31 de agosto al 6 de septiembre) | Terminar de revisar y validar este Plan del proyecto en equipo, completar formato (portada, tabla de contenidos, índice de tablas) |
| 6 (7 al 13 de septiembre) | Entrega del Plan del proyecto |
| 7 a 10 | Definir técnicas de prueba, escribir los casos de prueba y avanzar el Plan de pruebas |
| 11 (12 al 18 de octubre) | Entrega del Plan de pruebas |
| 12 a 14 | Automatizar los casos de prueba definidos |
| 15 (9 al 15 de noviembre) | Entrega del Proyecto de pruebas |
| 16 (16 al 22 de noviembre) | Entrega del Informe de pruebas y de la Presentación |

## Conclusiones y recomendaciones

Firefly III es un proyecto adecuado para aplicar los procesos de calidad de software del curso porque combina un problema social real (privacidad y control de las finanzas personales) con un sistema técnicamente lo bastante complejo como para dar suficientes casos de prueba: cálculos financieros, autenticación con 2FA, reglas condicionales y soporte multi moneda, entre otros. El principal riesgo que el equipo identifica hasta ahora es que el mantenimiento del repositorio está bastante concentrado en un solo desarrollador, lo que podría dificultar reportar o dar seguimiento a algún hallazgo si hiciera falta, aunque para el propósito del curso (aplicar QA sobre el código ya existente) esto no debería ser un problema real.

## Referencias bibliográficas (IEEE)

[1] T. Stefanov, M. Stefanova, S. Varbanova, and S. Temelkov, "Personal Finance Management Application," *TEM Journal*, vol. 13, no. 3, pp. 2066-2075, Aug. 2024.

[2] M. Salahat, R. A. Said, K. Hamid, U. Haseeb, E. Abdel Maguid Abdel Ghani, A. Abualkishik, M. W. Iqbal, and M. Inairat, "Software Testing Issues Improvement in Quality Assurance," in *2023 2nd International Conference on Business Analytics for Technology and Security (ICBATS)*, 2023, doi: 10.1109/ICBATS57792.2023.10111145.

[3] *(Pendiente: falta una tercera fuente, idealmente sobre privacidad de datos financieros o adopción de software autohospedado. Se buscaron candidatos pero no se pudo confirmar con suficiente certeza la autoría exacta como para citarlos sin revisar el artículo original. Buscar directo en las bases del TEC: Scopus, IEEE Xplore, ISI Web of Science o Engineering Village.)*

## Anexos

*(No es un ítem que puntúe en la rúbrica oficial de este entregable, pero se deja la sección por si el equipo quiere agregar algo, como capturas de la app corriendo localmente.)*

## Pendiente

- [x] Especificaciones del software
- [x] Problema (árbol de problemas en texto, falta pasarlo a diagrama visual)
- [x] Objetivos específicos con tabla de metas e indicadores
- [x] Recursos disponibles
- [x] Cronograma de actividades
- [ ] Revisión y validación del equipo sobre todo el contenido
- [ ] Confirmar la tercera fuente bibliográfica (ver nota en Referencias)
- [ ] Agregar portada, tabla de contenidos e índice de tablas antes de entregar
- [ ] Pasar el árbol de problemas a un diagrama visual real
- [ ] Sincronizar la fecha de entrega (semana del 7 al 13 de septiembre) a Todoist y Calendar
