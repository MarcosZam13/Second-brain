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

**Estado:** borrador de contenido (objetivos, requerimientos, problema contextualizado). Entrega oficial: **Semana 6** (ver [[Cursos/QA/apuntes/proyecto-qa-guia]], actualizado 2026-08-29 con el PPT oficial de rúbricas). Faltan, según la estructura oficial de 11 ítems de esa nota: portada, tabla de contenidos, índice de tablas, especificaciones del software (hardware/software, proveedores y versiones), sección de Problema (árbol de problemas), recursos disponibles, cronograma de actividades, y referencias bibliográficas en formato IEEE (mínimo 3 fuentes de bases indexadas del TEC, últimos 5 años).

**Repositorio elegido:** [firefly-iii/firefly-iii](https://github.com/firefly-iii/firefly-iii) — gestor de finanzas personales self-hosted (Laravel/PHP + Vue). Ver justificación en [[Cursos/QA/entregables/seleccion-repositorio-proyecto]].

## Introducción

### Qué

Este proyecto aplica los procesos de calidad de software (planeación, verificación, validación) vistos en el curso sobre Firefly III, un gestor de finanzas personales de código abierto y autohospedado. En lugar de un proyecto real de empresa (no aplica en esta edición del curso — ver [[Cursos/QA/apuntes/proyecto-qa-guia]]), el equipo eligió este repositorio siguiendo los 9 criterios de [[Cursos/QA/apuntes/criterios-seleccion-repositorio-github]].

### Por qué

*(Borrador — pendiente pulir con fuentes bibliográficas IEEE)* La gestión financiera personal es un problema con impacto social real: la falta de visibilidad sobre los propios gastos es un factor documentado de sobreendeudamiento, y buena parte de las herramientas populares de finanzas personales dependen de subir datos bancarios sensibles a servidores en la nube de terceros, lo cual genera fricción de privacidad para quien no quiere compartir esa información. Firefly III responde a ese problema siendo completamente autohospedado — los datos financieros del usuario nunca salen de su propio servidor — lo cual lo vuelve un caso de uso legítimo para poblaciones preocupadas por la privacidad de sus datos financieros (a diferencia de apps cloud-first). Validar la calidad de una herramienta así importa porque errores en el cálculo de saldos, presupuestos o transacciones recurrentes tienen consecuencia directa sobre decisiones financieras reales de quien la usa.

### Cómo

Se aplican las 5 fases del curso: identificación/selección de repositorio (esta fase, Semana 6), planeación (plan de pruebas, ≥60 casos, 3 tipos de prueba distintos, Semana 11), diseño/desarrollo/evaluación (proyecto de pruebas automatizado, ≥90% de cobertura automatizada, Semana 15-16), comunicación (presentación en inglés, Semana 16) y reflexión (diario individual, en paralelo, Semana 2 a 16).

### Limitaciones

- El equipo prueba sobre el código tal como está en el repositorio público — no hay acceso a datos de usuarios reales de producción, solo datos de prueba generados localmente.
- El alcance de pruebas se limita a los módulos de alta y media prioridad identificados en [[Cursos/QA/entregables/mapeo-modulos-firefly-iii]] (autenticación, cuentas, transacciones, presupuestos, categorías, facturas, recurrentes, reglas, piggy banks, monedas) — módulos administrativos/de soporte (Admin, Webhooks, Export) quedan fuera salvo que sobre tiempo.
- No hay contraparte de negocio real que valide requerimientos — los requerimientos se derivan del comportamiento documentado y observado del sistema, no de una entrevista con stakeholders.

## Especificaciones del software

*(Pendiente — listar hardware y software que usa la aplicación, incluyendo proveedores y versiones: stack Laravel/PHP + Vue, versión de PHP/Composer/Node, base de datos, Docker/docker-compose oficial, navegadores soportados, etc. Ítem oficial de la estructura del Plan del proyecto, vale 15 pts en la rúbrica.)*

## Requerimientos del sistema

Derivados del mapeo de módulos ([[Cursos/QA/entregables/mapeo-modulos-firefly-iii]]) y verificados contra el código fuente del repo:

**Funcionales (por módulo, alta/media prioridad):**
1. El sistema debe permitir registro e inicio de sesión de usuarios, incluyendo autenticación de dos factores (2FA).
2. El sistema debe permitir crear, editar y eliminar cuentas financieras de distintos tipos (activo, pasivo, gasto, ingreso).
3. El sistema debe permitir registrar transacciones de tipo gasto, ingreso y transferencia entre cuentas propias, manteniendo la consistencia contable de doble entrada.
4. El sistema debe permitir definir presupuestos por categoría y período, y calcular correctamente el gasto disponible restante.
5. El sistema debe permitir clasificar transacciones por categoría y por etiqueta.
6. El sistema debe permitir definir facturas/gastos recurrentes esperados y hacer coincidencia automática (matching) contra transacciones reales.
7. El sistema debe permitir automatizar la creación de transacciones recurrentes según una programación temporal definida por el usuario.
8. El sistema debe permitir definir reglas condicionales que clasifiquen transacciones automáticamente según criterios definidos por el usuario.
9. El sistema debe permitir crear metas de ahorro (piggy banks) con seguimiento de progreso.
10. El sistema debe soportar múltiples monedas con conversión correcta según tasas de cambio.

**No funcionales:**
- El sistema debe poder desplegarse localmente vía Docker (`docker-compose` oficial) sin dependencias externas no documentadas.
- El sistema debe exponer una API REST documentada (OpenAPI/Swagger) que cubra las operaciones principales, para permitir pruebas automatizadas más allá de la interfaz web.
- El sistema debe aislar correctamente los datos financieros entre distintos usuarios/grupos (UserGroup).

## Problema

*(Pendiente — construir árbol de problemas y árbol de objetivos siguiendo [[Cursos/QA/apuntes/taller-arbol-problemas-objetivos]]: causas y efectos del problema, contextualizado desde una perspectiva social/educativa/política/económica. Ítem oficial de la estructura, vale 25 pts combinados en la rúbrica — 10 por contextualizar el problema social real, 15 por determinar sus partes/características/factores.)*

## Objetivos

### Objetivo general

Evaluar la calidad del software de Firefly III mediante la aplicación de un proceso de pruebas de software (planeación, diseño, ejecución y análisis de resultados) sobre sus módulos financieros críticos, con el fin de determinar el grado de cumplimiento de sus requerimientos funcionales y detectar posibles defectos.

### Objetivos específicos

1. Analizar los requerimientos funcionales de los módulos de alta y media prioridad de Firefly III (autenticación, cuentas, transacciones, presupuestos, categorías, facturas, recurrentes, reglas, piggy banks, monedas) para delimitar el alcance de pruebas.
2. Diseñar un plan de pruebas con al menos 60 casos de prueba, cubriendo 3 tipos de prueba distintos, con un máximo del 10% de casos manuales.
3. Automatizar al menos el 90% de los casos de prueba diseñados, utilizando un framework adecuado al stack del repositorio (Laravel/PHP + Vue) o pruebas contra la API REST documentada.
4. Ejecutar el plan de pruebas y documentar los defectos encontrados en un informe de pruebas con análisis de resultados.
5. Comunicar los resultados del proyecto en una presentación en inglés ante la profesora y el docente de inglés.

## Recursos disponibles

*(Pendiente — ítem oficial de la estructura, vale 10 pts en la rúbrica: recursos humanos del equipo, herramientas de testing a usar, infraestructura para correr Firefly III localmente, tiempo disponible.)*

## Cronograma de actividades

*(Pendiente — ítem oficial de la estructura, vale 10 pts en la rúbrica: cronograma de trabajo del equipo hasta la Semana 6, coordinado con las fechas de entrega de las siguientes fases — Semana 11 Plan de pruebas, Semana 15 Proyecto de pruebas, Semana 16 Informe de pruebas y Presentación.)*

## Conclusiones y recomendaciones

*(Pendiente — se completa una vez el equipo revise y valide este borrador)*

## Referencias bibliográficas (IEEE)

*(Pendiente — mínimo 3 fuentes de bases indexadas del TEC (Scopus, ISI Web of Science, IEEE Xplore, Engineering Village), publicadas en los últimos 5 años, sobre gestión financiera personal / privacidad de datos financieros / calidad de software en aplicaciones financieras)*

## Anexos

*(Pendiente)*

## Pendiente

- [ ] Llenar Especificaciones del software (hardware/software, proveedores, versiones — 15 pts)
- [ ] Construir árbol de problemas y árbol de objetivos (medios/fines) siguiendo [[Cursos/QA/apuntes/taller-arbol-problemas-objetivos]] para la sección Problema (25 pts); formalizar los objetivos específicos con tabla de metas e indicadores
- [ ] Llenar Recursos disponibles (10 pts) y Cronograma de actividades (10 pts)
- [ ] Revisión y validación del equipo de QA sobre requerimientos y objetivos
- [ ] Buscar y citar mínimo 3 fuentes IEEE para contextualizar el problema social
- [x] Formato bibliográfico confirmado: IEEE para este entregable (resuelto — ver [[Cursos/QA/apuntes/proyecto-qa-guia]], rúbricas oficiales del PPT 2026-08-29)
- [ ] Agregar portada, tabla de contenidos e índice de tablas antes de entregar (siguen el orden oficial de 11 ítems — ver [[Cursos/QA/apuntes/proyecto-qa-guia]]; conclusiones/anexos no puntúan en la rúbrica oficial pero no está de más dejarlos)
- [ ] Confirmar fecha de calendario real para la Semana 6 (TEC-Digital) y sincronizar a Todoist/Calendar
