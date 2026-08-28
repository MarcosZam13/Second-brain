---
curso: SistemasOperativos
tema: Indagatoria Corta — Análisis de la Gestión de Procesos en un Sistema Operativo
fecha: 2026-08-27
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3]]"
estado: "borrador — teoría/estructura completa (armada con Claude Code 2026-08-27); falta evidencia práctica real (capturas/comandos de cada instalación) y el análisis de experiencia de usuario, que tienen que salir de Marcos y Joseph de primera mano"
tags: [indagatoria-corta, unidad3, gestion-procesos, trabajo-grupal, arch-linux, cachyos, omarchy]
---

# Indagatoria Corta — Gestión de Procesos en un Sistema Operativo

Ver también: [[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3|Instrucciones completas]] · [[Cursos/SistemasOperativos/entregas]]

**Modalidad:** en equipo (semanas 3–5) · **Presentación:** semana 5 (2026-09-03), con demostración del SO indagado.

## Sistema operativo seleccionado

**Arch Linux**, instalado/probado a través de dos variantes: **CachyOS** y **Omarchy**.

- **CachyOS** — distribución basada en Arch orientada a rendimiento: kernel parcheado, y como diferencial más relevante para esta indagatoria, permite elegir/usar schedulers alternativos al CFS por defecto (ej. **BORE**, y soporte de **sched-ext**). Da contenido directo para el apartado de "Planificación de procesos y políticas" (15%) — se puede comparar el comportamiento del scheduler de CachyOS contra el CFS estándar de un Arch vanilla o de otra distro.
- **Omarchy** — instalador/configuración opinionada de Arch + Hyprland (de DHH); útil sobre todo para el apartado de "Análisis de experiencia de usuario" (facilidad de instalación/configuración vs. Arch vanilla) y como punto de comparación práctico entre dos formas distintas de llegar al mismo sistema base.

**Ángulo sugerido para "Comparación con otro sistema operativo" (10%):** contrastar el scheduler por defecto de CachyOS (BORE/sched-ext) contra el CFS de un Arch/Ubuntu estándar — es el aspecto técnico más fuerte que ofrece esta elección y conecta directo con la rúbrica de planificación.

## Checklist contra la rúbrica

- [x] Introducción y descripción del sistema (10%) — borrador listo
- [x] Descripción técnica de la gestión de procesos — kernel, tablas, colas, herramientas (20%) — borrador listo
- [ ] Evidencia práctica — instalación y pruebas documentadas (15%) — **pendiente, necesita capturas/comandos reales de Marcos (CachyOS) y Joseph (Omarchy)**
- [x] Planificación de procesos y políticas (15%) — borrador listo, incluye corrección técnica (ver nota EEVDF/BORE abajo)
- [x] Sincronización y comunicación entre procesos (10%) — borrador listo
- [x] Comparación con otro sistema operativo (10%) — borrador listo (interna CachyOS↔Omarchy + externa vs. Windows)
- [~] Análisis crítico y conclusiones (10%) — análisis crítico listo, conclusiones pendientes de sintetizar con evidencia real
- [ ] Análisis de experiencia de usuario — 3-5 ventajas y 3-5 desventajas (5%) — **pendiente, tiene que salir de la experiencia real de instalación de cada quien**
- [x] Calidad del documento/presentación y referencias (5%) — referencias listas, formato final pendiente

## Borrador del informe

> **Nota técnica importante:** la guía del profesor usa "CFS" como ejemplo de algoritmo de planificación (ver pistas por SO en [[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3]]). Para un Arch Linux corriendo en 2026 (rolling release, kernel reciente) esto ya no es exacto: **CFS fue reemplazado por EEVDF** (Earliest Eligible Virtual Deadline First) como scheduler general-purpose por defecto desde el kernel 6.6. El informe usa la terminología correcta (EEVDF, BORE, sched-ext) y vale la pena mencionarlo explícitamente en clase — demuestra que el equipo no se quedó con el ejemplo genérico de la guía, sino que verificó qué corre realmente en el sistema elegido.

### Introducción

Arch Linux es una distribución *rolling-release* minimalista construida alrededor de `pacman` y el principio KISS ("keep it simple, stupid"): el usuario arma el sistema paquete por paquete en vez de partir de una configuración preestablecida. Para esta indagatoria el equipo instaló y probó dos variantes derivadas de Arch que representan dos filosofías distintas sobre la misma base:

- **CachyOS** (Marcos) — orientada a rendimiento: kernel propio parcheado, paquetes optimizados por microarquitectura (x86-64-v3/v4), y soporte nativo de schedulers alternativos al de serie.
- **Omarchy** (Joseph) — instalación opinionada de Arch + Hyprland creada por David Heinemeier Hansson, pensada para llegar a un escritorio de desarrollo funcional sin la fricción de una instalación manual de Arch.

La gestión de procesos importa particularmente en este par porque CachyOS interviene directamente el planificador del kernel — la pieza más central de la gestión de procesos — mientras que Omarchy no lo toca: deja el comportamiento de planificación en su valor por defecto y enfoca sus decisiones de diseño en la capa de escritorio, no en el kernel.

### Componentes principales de la gestión de procesos

- **Kernel:** ambas variantes corren un kernel Linux con `systemd` como PID 1 (init). CachyOS ships su propio paquete de kernel (`linux-cachyos`, con variantes `-bore`, `-bmq`, `-rt-bore`) con el parche BORE y otros ajustes de rendimiento; Omarchy usa el paquete `linux` estándar de Arch, sin modificar.
- **Tablas:** el kernel mantiene un `task_struct` por proceso — expuesto vía `/proc/[pid]/` (`status`, `stat`, `maps`, etc.) — igual en ambas variantes, porque es una estructura de datos del kernel, no de la distro.
- **Colas:** cola de ejecución (*run queue*) por CPU, gestionada por la clase de scheduler activa (EEVDF por defecto en Arch vanilla/Omarchy, BORE sobre EEVDF en CachyOS).
- **Herramientas de monitoreo:** `ps`, `top`, `htop` en ambas; `systemctl`/`journalctl` para gestión de procesos a nivel de servicio bajo systemd. CachyOS agrega herramientas propias como `cachyos-settings` y, si se instala el paquete `scx-scheds`, `scx_loader` para cambiar de scheduler sched-ext en caliente.

### Creación y finalización de procesos

- **`fork()`/`exec()`:** el mecanismo POSIX estándar heredado del kernel/glibc, usado por las shells (bash/zsh/fish) y cada vez que el usuario lanza una aplicación — idéntico en ambas variantes.
- **Unidades de systemd:** para servicios/demonios, ambas distros crean y gestionan procesos de forma declarativa vía archivos `.service`, con `systemctl start/stop/restart` — systemd hace el `fork`/`exec` y la asignación a cgroups por debajo.
- **Finalización:** `kill`/`killall`/`pkill` envían señales (`SIGTERM`, `SIGKILL`, `SIGHUP`...); `exit()` desde el propio programa. systemd además puede forzar el cierre de un proceso que no termina limpio vía `TimeoutStopSec`.

### Planificación de procesos y políticas

- El scheduler general-purpose por defecto del kernel Linux moderno (≥6.6, lo que corre en un Arch rolling release en 2026) ya **no es CFS sino EEVDF** (ver nota técnica arriba).
- **CachyOS** parte de EEVDF pero aplica encima el parche **BORE** (*Burst-Oriented Round Robin Extension*), que ajusta el "burst score" de cada proceso según su historial reciente de uso de CPU para mejorar la latencia/interactividad percibida (ej. que la interfaz no se sienta trabada mientras algo compila en segundo plano) sin sacrificar tanto throughput.
- CachyOS también ofrece **sched-ext** (schedulers extensibles vía BPF, soportados en mainline desde el kernel 6.12): permite cambiar de scheduler en caliente sin recompilar el kernel (ej. `scx_bore`, `scx_lavd`, `scx_rusty`), cada uno afinado para un caso de uso distinto (gaming, servidores, ahorro de energía).
- **Omarchy** no toca el scheduler — corre el EEVDF por defecto del kernel de Arch, sin BORE ni sched-ext.
- Parámetro de configuración concreto: en CachyOS la elección de scheduler se hace a nivel de qué paquete `linux-cachyos-*` se instala, y opcionalmente qué scheduler sched-ext se carga en runtime.

### Sincronización y comunicación entre procesos

- **`futex`** (*fast userspace mutex*) es el mecanismo base del kernel sobre el que se construyen los mutexes/semáforos de `pthread` en glibc — igual en ambas distros, porque es una característica del kernel/libc, no de la distro.
- IPC estándar disponible en ambas: *pipes*/FIFOs, señales, memoria compartida POSIX (`shm_open`), colas de mensajes, sockets Unix.
- **D-Bus:** el bus de mensajería que usa systemd y la mayoría del stack de escritorio moderno para comunicación entre procesos de usuario y servicios del sistema — componente central en la experiencia de escritorio de Omarchy en particular (Hyprland + portales de escritorio dependen de D-Bus).

### Gestión en sistemas multiprocesador y virtualizados

- EEVDF/BORE son schedulers conscientes de múltiples CPUs: cada núcleo mantiene su propia cola de ejecución, con balanceo de carga entre núcleos y, si el hardware lo soporta, awareness de topología NUMA.
- `cgroups v2` (usado por systemd para agrupar/limitar recursos por servicio o por sesión de usuario) es el mecanismo compartido de administración de recursos multiprocesador en ambas variantes.
- **Pendiente:** documentar acá la plataforma real de cada instalación (bare-metal, dual-boot, o VM vía QEMU/KVM/VirtualBox) con evidencia de que efectivamente corre ahí — necesario para el 15% de "evidencia práctica" de la rúbrica.

### Comparación con otro sistema operativo

- **Comparación interna (misma familia, dos filosofías):** CachyOS (BORE/sched-ext sobre EEVDF) vs. Omarchy (EEVDF estándar sin modificar) — mismo kernel base, distinta decisión sobre el planificador; permite aislar el efecto real de BORE sin cambiar de distro.
- **Comparación externa (para el criterio de "otro sistema operativo" de la rúbrica):** contra Windows, cuyo scheduler usa clases de prioridad fijas + quantum variable por tipo de proceso (con *foreground boost* para la app activa) — un modelo más rígido y orientado a prioridades estáticas, comparado con el cálculo dinámico de "tiempo virtual" que usan EEVDF/BORE en Linux.

### Análisis crítico

**Fortalezas:** CachyOS ofrece control fino sobre el planificador sin salir del ecosistema Arch — algo raro entre distros mainstream, que normalmente no exponen sched-ext al usuario final. Omarchy demuestra que se puede llegar a un Arch funcional sin la fricción de una instalación manual, a costa de ceder ese control fino de rendimiento.

**Debilidades:** un scheduler parcheado como BORE introduce una superficie de comportamiento no estándar — si algo falla, hay menos documentación/ayuda específica disponible que para el kernel vanilla. Omarchy, al ser mantenido por una sola persona y relativamente joven, depende de que su script de instalación se mantenga al día contra los cambios upstream de Arch/Hyprland.

### Conclusiones

*(Pendiente — mejor sintetizar esto una vez el equipo tenga la evidencia práctica real de ambas instalaciones, para que la conclusión hable de lo que realmente se observó y no solo de la teoría.)*

### Referencias

- Stallings, W. (2018). *Operating Systems: Internals and Design Principles* (9th ed.). Pearson.
- Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). *Operating System Concepts* (10th ed.). Wiley.
- Arpaci-Dusseau, R. H., & Arpaci-Dusseau, A. C. (2018). *Operating Systems: Three Easy Pieces*. Arpaci-Dusseau Books. Disponible en https://pages.cs.wisc.edu/~remzi/OSTEP/
- Linux Kernel Documentation — *Scheduler: EEVDF*. https://docs.kernel.org/scheduler/
- CachyOS Wiki — *Kernel & Scheduler options*. https://wiki.cachyos.org/
- Omarchy — documentación oficial del proyecto. https://omarchy.org/
- Arch Wiki — *systemd*, *Process management*. https://wiki.archlinux.org/

### Análisis de experiencia de usuario

*(Pendiente — necesita la experiencia real de instalación de Marcos (CachyOS) y Joseph (Omarchy); no corresponde inventar ventajas/desventajas de haber usado algo que el equipo tiene que documentar de primera mano.)*

**Estructura sugerida para completar (3-5 ventajas / 3-5 desventajas por instalación):**
- CachyOS: ¿el proceso de instalación fue más largo que un Arch vanilla? ¿se notó diferencia real de rendimiento/latencia contra un sistema sin BORE? ¿algún paquete/driver dio problemas por ser una distro más chica?
- Omarchy: ¿qué tanto redujo la fricción de instalar Arch a mano? ¿qué tan opinionado resultó ser en la práctica (¿costó salirse de sus decisiones por defecto)? ¿Hyprland (tiling/Wayland) fue una curva de aprendizaje notable viniendo de otro entorno?
