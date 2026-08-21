---
curso: SistemasOperativos
tema: Unidad 2 — Historia y componentes de los Sistemas Operativos (Semana 2-3)
fecha: 2026-08-07
tipo: apunte
fuente:
  - _fuentes/SistemasOperativos_historia-componentes-so-unidad2_2026-08-07.pdf
  - _fuentes/SistemasOperativos_unidad2-semana2_2026-08-07.png
  - _fuentes/SistemasOperativos_historia-componentes-so-unidad2_2026-08-21.pdf
tags: [unidad2, historia-so, componentes-so, arquitecturas-so, modo-dual, llamadas-sistema]
---

# Unidad 2 — Historia y componentes de los Sistemas Operativos (Semana 2-3)

Ver también: [[Cursos/SistemasOperativos/temario]] · [[Cursos/SistemasOperativos/entregas]] · [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1]]

Introducción a los SO, su función como intermediario, y los componentes principales que lo conforman. Basado en Tanenbaum, Silberschatz y Stallings.

Unidad arrancada en semana 2 y cerrada en semana 3 con el mismo material (misma presentación, sin cambios de contenido).

## Objetivos de la unidad

- Definir objetivos, funciones y evolución histórica de los SO.
- Identificar los componentes fundamentales de un SO moderno.
- Analizar problemas clásicos que resuelven los SO.
- Comparar arquitecturas y tipos de SO actuales.
- Contextualizar el rol del SO en sistemas contemporáneos (nube, móviles, edge).

## Evolución histórica: de los mainframes a la nube

| Década | Tecnología | SO representativos | Característica clave |
|---|---|---|---|
| 1950s | Mainframes | GM-NAA I/O, IBSYS | Procesamiento por lotes |
| 1960s | Tiempo compartido | CTSS, MULTICS | Multiprogramación |
| 1970s | Minicomputadoras | UNIX, CP/M | Portabilidad, kernel en C |
| 1980s | Computadoras personales | MS-DOS, Mac OS | Interfaz de usuario |
| 1990s | Cliente-servidor | Windows NT, Linux | Redes, 32/64 bits |
| 2000s | Móviles/Web | Windows XP, Android, iOS | Conectividad, touch |
| 2010s | Cloud/Contenedores | Windows 10, Docker, K8s | Virtualización ligera |
| 2020s | Edge/IoT | Windows 11, ROS 2, RHEL | Distribuido, tiempo real |

*Referencia: Tanenbaum & Bos, Modern Operating Systems, 5th ed., 2023, cap. 1.*

## ¿Qué es un Sistema Operativo? (definición multidimensional)

1. **Administrador de recursos** — gestiona CPU, memoria, almacenamiento, dispositivos; asigna recursos de forma eficiente y justa.
2. **Máquina virtual/extendida** — abstrae la complejidad del hardware, da interfaces uniformes a los programas.
3. **Controlador/proveedor de servicios** — ofrece servicios comunes a las aplicaciones, garantiza operación confiable y segura.

> "El SO es el software que hace usable el hardware" — Silberschatz et al., *Operating System Concepts*, 11th ed., 2022.

Visión abstracta: usuarios → programas de aplicación (compiler, assembler, text editor, database system) → **operating system** → hardware. El SO es la capa entre "system and application programs" y el "computer hardware".

## Problemas clásicos que resuelve un SO

- **Coordinación entre procesos:** un programa en ejecución es un conjunto de procesos en ejecución. Ejemplo con procesos 1→2,3→4→5→6: ¿cómo sabe el proceso 2 que el 1 terminó? Si 2 y 3 corren en paralelo, ¿quién va primero? ¿Cómo se entera 4 de que 2 y 3 terminaron?
- **Asignación de recursos:** los procesos requieren recursos compartidos; mientras un programa no termina, sus procesos no pueden liberarlos. Una propiedad deseable del SO es la **multiprogramación**.
- **Bloqueo mutuo (deadlock / interbloqueo / traba mortal / abrazo mortal):** ocurre cuando el procesador no puede asignar un recurso compartido a un conjunto de procesos pendientes, porque cada uno tiene un recurso asignado pero necesita el que tiene el otro para continuar (ejemplo clásico: A tiene R1 y pide R2; B tiene R2 y pide R1).

## Componentes principales de un SO moderno

1. **Gestor de Procesos** — un proceso es programa en ejecución + estado + recursos. Responsabilidades: creación/destrucción (fork/exec/exit), scheduling, sincronización (semáforos, mutex), comunicación (pipes, sockets, memoria compartida). *Ejemplo moderno:* contenedores (namespaces, cgroups).
2. **Gestor de Memoria** — jerarquía: registros → caché L1/L2/L3 → RAM → SSD/NVMe → cloud storage. Responsabilidades: asignación/liberación, paginación/segmentación, memoria virtual (swap), caché y buffers. *Ejemplo moderno:* memoria no volátil (Optane), DAX.
3. **Gestor de E/S** — arquitectura en capas: aplicación → API de E/S → drivers genéricos → drivers específicos → hardware. Responsabilidades: buffering/caching, scheduling de discos, gestión de interrupciones, soporte plug-and-play. *Ejemplo moderno:* drivers NVMe, GPU compute.
4. **Sistema de Archivos** — abstracciones: archivo (datos + metadatos), directorio (organización jerárquica), punto de montaje (integración de dispositivos). Responsabilidades: organización en disco (FAT, NTFS, ext4, ZFS), permisos, recuperación ante fallos (journaling), caché de disco. *Ejemplo moderno:* sistemas de archivos distribuidos (HDFS, Ceph). Ver detalle completo en [[Cursos/SistemasOperativos/apuntes/sistema-archivos-unidad6]].
5. **Subsistema de Red** — protocolos (TCP/IP), interfaces (NIC drivers), firewall/filtrado, API de sockets. *Ejemplo moderno:* virtualización de red (OVS, eBPF).
6. **Seguridad y Protección** — autenticación (Linux PAM, Active Directory), control de acceso (DAC, MAC — SELinux, AppArmor), auditoría/logging, cifrado (dm-crypt, BitLocker). *Ejemplo moderno:* TPM 2.0, Secure Boot, measured boot.

## Objetivos del Sistema Operativo

- Facilitar el uso al usuario (interfaz).
- Facilitar la programación al programador (máquina virtual extendida).
- Ejecutar programas eficientemente (gestor de recursos).
- **Conveniencia:** proveer un ambiente para ejecutar programas (ej. computadoras personales).
- **Eficiencia:** incrementar la productividad de los recursos de producción.

Servicios del SO (capas): user and other system programs → interfaces de usuario (GUI, batch, command line) → **system calls** → servicios (program execution, I/O operations, file systems, communication, resource allocation, accounting, error detection, protection and security) → operating system → hardware.

## Modo dual de operación y protección por hardware

- Al compartir recursos, el SO debe asegurar que un programa no afecte a otro → mecanismo de protección hardware (bit) con al menos 2 modos: **usuario (1)** y **sistema (0)**.
- Las instrucciones privilegiadas solo son posibles en modo sistema. Ante interrupción, trap o excepción, el hardware cambia a modo sistema.
- **E/S:** siempre instrucciones privilegiadas (modo sistema).
- **Memoria:** registros base y límite por programa; accesos fuera de rango generan fallo de protección.
- **CPU:** temporizador que interrumpe periódicamente para devolver control al SO.

**Llamada al sistema** — método estándar de acceso a servicios del SO: el programa genera un trap (interrupción software), se ejecuta la RTI (Rutina de Tratamiento de Interrupción) cambiando a modo sistema, el SO verifica parámetros, ejecuta la petición y devuelve control en la instrucción siguiente. El SO oculta las llamadas al sistema en bibliotecas instaladas junto con él.

## Arquitecturas de Sistemas Operativos

- **Estructura simple (monolítica)** — todo entre las llamadas al sistema y el hardware, sin división en módulos ni separación de interfaces/niveles. Ejemplo: MS-DOS. Monoproceso, hardware reducido.
- **Enfoque por capas** — niveles tipo "cebolla"; cada nivel usa solo servicios del inferior y da servicio al superior; el más alto es la interfaz de llamadas. Ejemplo: Multics (1964). Problema potencial: orden de llamadas entre capas.
- **UNIX tradicional** — dos partes separables: kernel (con interfaces y controladores de dispositivos) y programas del sistema; puede verse como una estructura por capas hasta cierto punto.
- **Micronúcleo (microkernel)** — reducido a funcionalidades mínimas imprescindibles; el resto de servicios (sistema de archivos, drivers) corre en modo usuario y se comunica por paso de mensajes. Ejemplos: QNX, MINIX 3. Ventaja: piezas separables, camino hacia SO distribuido. Problema: una llamada puede requerir muchos mensajes.
- **Sistemas modulares** — dividido en módulos con funcionalidad e interfaces claramente definidos; componentes sustituibles con la misma interfaz; multiproceso y multiusuario. Ejemplo: core Solaris kernel con módulos (device/bus drivers, scheduling classes, file systems, loadable system calls, STREAMS modules, executable formats, miscellaneous modules).

## Ejercicio de planificación (visto en clase)

Tabla de procesos con Tiempo de Llegada y Tiempo de Servicio:

| Proceso | Tiempo Llegada | Tiempo Servicio |
|---|---|---|
| 1 | 0 | 3 |
| 2 | 2 | 2 |
| 3 | 4 | 4 |
| 4 | 7 | 3 |
| 5 | 12 | 5 |

Se pide calcular el tiempo de término (1) ejecutando en secuencia estricta y (2) permitiendo que dos procesos corran en paralelo. Sirve para introducir intuitivamente la planificación de CPU que se profundiza en Unidad 3 (Gestión de Procesos).

## TO-DO List — Semana 2

**Actividad Individual:** comprobación de la Unidad "Historia y Componentes de los SO" — analizar la presentación y el video de la semana, responder individualmente las preguntas establecidas. Entrega en PDF con nombre `S2_Preguntas_NombreApellido1Apellido2`. Fecha límite: semana 3, antes de las 11:30 p.m. (confirmar hora exacta en TEC Digital).

**Actividad en Equipos:** continuación de la [[Cursos/SistemasOperativos/apuntes/estructura-sistemas-computo-unidad1|Actividad en Equipos — Solución basada en Principios de los SO]]:
- **Fase 2 — Conceptualización de la solución:** definir la propuesta, componentes del SO involucrados, software y tecnologías necesarias.
- **Fase 3 — Diseño preliminar:** diagrama de bloques, algoritmos o procesos clave, recursos necesarios.

Ambas fases se trabajan en clase y fuera de clase, y se evalúan también a nivel individual. La entrega final de la propuesta es en semana 3 mediante presentación corta.

## Próxima lección (según la presentación)

- Introducción a SO (continuación): estructura del SO, máquinas virtuales.
- Administración de Procesos: conceptos, comunicación entre procesos, threads, planificación del CPU, sincronización, bloqueos.
