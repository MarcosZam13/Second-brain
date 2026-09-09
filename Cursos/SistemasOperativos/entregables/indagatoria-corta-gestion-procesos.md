---
curso: SistemasOperativos
tema: "Indagatoria Corta: Análisis de la Gestión de Procesos en un Sistema Operativo"
fecha: 2026-08-27
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3]]"
estado: "en armado final (2026-09-07). Teoría completa. Evidencia de Omarchy integrada (Joseph). Pendiente: evidencia de CachyOS (Marcos), análisis de experiencia de usuario y conclusiones"
tags: [indagatoria-corta, unidad3, gestion-procesos, trabajo-grupal, arch-linux, cachyos, omarchy]
---

# Indagatoria Corta: Gestión de Procesos en un Sistema Operativo

Ver también: [[Cursos/SistemasOperativos/apuntes/gestion-procesos-unidad3|Instrucciones completas]] · [[Cursos/SistemasOperativos/entregables/guion-indagatoria-corta-gestion-procesos|Guión de la exposición]] · [[Cursos/SistemasOperativos/entregas]]

**Modalidad:** en equipo (semanas 3 a 5) · **Presentación:** semana 5 (2026-09-03), con demostración del SO indagado.

## Sistema operativo seleccionado

**Arch Linux**, instalado y probado a través de dos variantes: **CachyOS** y **Omarchy**.

- **CachyOS** (Marcos): distribución basada en Arch orientada a rendimiento. Kernel parcheado y, como diferencial más relevante para esta indagatoria, la posibilidad de elegir schedulers alternativos al de serie (BORE, y soporte de sched-ext). Da contenido directo para el apartado de "Planificación de procesos y políticas" (15%).
- **Omarchy** (Joseph): instalador y configuración opinionada de Arch + Hyprland, creada por David Heinemeier Hansson. Sirve sobre todo para el apartado de "Análisis de experiencia de usuario" (facilidad de instalación y configuración frente a un Arch vanilla) y como punto de comparación práctico entre dos formas distintas de llegar al mismo sistema base.

---

## 1. Introducción y descripción del sistema

Arch Linux es una distribución *rolling-release* minimalista construida alrededor de `pacman` y del principio KISS ("keep it simple, stupid"): el usuario arma el sistema paquete por paquete en vez de partir de una configuración preestablecida. Para esta indagatoria el equipo instaló y probó dos variantes derivadas de Arch que representan dos filosofías distintas sobre la misma base:

- **CachyOS** (Marcos): orientada a rendimiento, con kernel propio parcheado, paquetes optimizados por microarquitectura (x86-64-v3/v4) y soporte nativo de schedulers alternativos al de serie.
- **Omarchy** (Joseph): instalación opinionada de Arch + Hyprland, pensada para llegar a un escritorio de desarrollo funcional sin la fricción de una instalación manual de Arch.

La gestión de procesos importa particularmente en este par porque CachyOS interviene directamente el planificador del kernel, que es la pieza más central de la gestión de procesos, mientras que Omarchy no lo toca: deja el comportamiento de planificación en su valor por defecto y concentra sus decisiones de diseño en la capa de escritorio, no en el kernel. Eso permite comparar dos sistemas con el mismo kernel base y distinta política de planificación, sin cambiar de familia de sistema operativo.

> **Nota técnica.** La guía del curso usa "CFS" como ejemplo de algoritmo de planificación. Para un Arch Linux corriendo en 2026 (rolling release, kernel reciente) esto ya no es exacto: **CFS fue reemplazado por EEVDF** (*Earliest Eligible Virtual Deadline First*) como scheduler general-purpose por defecto a partir del kernel 6.6. Este informe usa la terminología correcta (EEVDF, BORE, sched-ext) y el equipo lo menciona explícitamente en la presentación, porque verificó qué corre realmente en el sistema elegido en vez de repetir el ejemplo genérico.

## 2. Descripción técnica de la gestión de procesos

### 2.1 Componentes principales

- **Kernel:** ambas variantes corren un kernel Linux con `systemd` como PID 1 (init). CachyOS distribuye su propio paquete de kernel (`linux-cachyos`, con variantes `-bore`, `-bmq`, `-rt-bore`) con el parche BORE y otros ajustes de rendimiento. Omarchy usa el paquete `linux` estándar de Arch, sin modificar.
- **Tablas:** el kernel mantiene un `task_struct` por proceso, expuesto vía `/proc/[pid]/` (`status`, `stat`, `maps`, entre otros). Es idéntico en ambas variantes, porque es una estructura de datos del kernel y no de la distribución.
- **Colas:** una cola de ejecución (*run queue*) por CPU, gestionada por la clase de scheduler activa: EEVDF por defecto en Arch vanilla y Omarchy, BORE sobre EEVDF en CachyOS.
- **Herramientas de monitoreo:** `ps`, `top` y `htop` en ambas, más `systemctl` y `journalctl` para gestión de procesos a nivel de servicio bajo systemd. CachyOS agrega herramientas propias como `cachyos-settings` y, si se instala el paquete `scx-scheds`, `scx_loader` para cambiar de scheduler sched-ext en caliente.

### 2.2 Creación y finalización de procesos

- **`fork()` / `exec()`:** el mecanismo POSIX estándar heredado del kernel y glibc, usado por las shells (bash, zsh, fish) y cada vez que el usuario lanza una aplicación. Idéntico en ambas variantes.
- **Unidades de systemd:** para servicios y demonios, ambas distribuciones crean y gestionan procesos de forma declarativa mediante archivos `.service`, con `systemctl start/stop/restart`. systemd hace el `fork`/`exec` y la asignación a cgroups por debajo.
- **Finalización:** `kill`, `killall` y `pkill` envían señales (`SIGTERM`, `SIGKILL`, `SIGHUP`). Un programa también puede terminar por su cuenta con `exit()`. systemd puede además forzar el cierre de un proceso que no termina limpio mediante `TimeoutStopSec`.

## 3. Evidencia práctica: instalación y pruebas

### 3.1 Instalación de Omarchy (Joseph)

**Plataforma de la instalación:** ⟨CONFIRMAR CON JOSEPH: bare metal, dual boot o máquina virtual⟩

La instalación de Omarchy es relativamente sencilla. El primer paso es descargar el archivo ISO desde la página oficial (omarchy.org) y escribirlo en un USB booteable.

![[omarchy-descarga-iso.png]]

Antes de arrancar desde el USB hay que entrar a la BIOS y desactivar el Secure Boot, porque Omarchy lo requiere. Luego se entra al boot menu de la placa madre con F12 o la tecla que corresponda al fabricante.

Lo cómodo de Omarchy es que la ISO trae su propio instalador, así que el proceso es guiado e intuitivo: basta con seguir los pasos de configuración (distribución del teclado, usuario, contraseña y la partición del disco donde se va a instalar).

![[omarchy-instalador-final.png]]

Cuando el instalador termina, avisa que la instalación finalizó. Solo queda retirar el USB y reiniciar la computadora.

#### Demostración en vivo de Omarchy

**Gestor de ventanas:** Hyprland (compositor Wayland con tiling), configurado desde `~/.config/hypr`.

**Comandos que se muestran en la demo:**

| Comando | Qué evidencia |
| --- | --- |
| `fastfetch` | Distribución, versión de kernel, entorno de escritorio y hardware del equipo |
| `btop` | Procesos vivos, uso de CPU por núcleo y jerarquía padre/hijo en tiempo real |
| `cd ~/.config && ls` | Cómo Omarchy organiza la configuración del escritorio en archivos de texto |

**Atajos de teclado que se demuestran:**

| Atajo | Qué hace |
| --- | --- |
| `Super + Enter` | Abrir una terminal |
| `Super + Space` | Lanzador de aplicaciones |
| `Super + Alt + Space` | Menú principal de Omarchy |
| `Super + K` | Mostrar la lista de atajos configurados |
| `Super + <número>` | Cambiar al escritorio (workspace) correspondiente |
| `Super + Shift + <número>` | Mover la ventana activa a ese escritorio |
| `Super + W` | Cerrar la ventana activa |
| `Super + Shift + B` | ⟨confirmar en el ensayo⟩ |
| `Super + Shift + F` | ⟨confirmar en el ensayo⟩ |
| `Super + Escape` | ⟨confirmar en el ensayo⟩ |
| `Super + Shift + Ctrl + Space` | ⟨confirmar en el ensayo⟩ |

> El propio `Super + K` sirve para verificar los cuatro atajos marcados: abre la lista completa de bindings que Omarchy trae configurados.

### 3.2 Instalación de CachyOS (Marcos)

**Plataforma de la instalación:** bare metal en dual boot con Windows, sobre la misma máquina. Esto tiene una ventaja para el trabajo: permite contrastar los dos sistemas operativos corriendo sobre exactamente el mismo hardware, que es la base de la comparación externa de la sección 7.

**Kernel y scheduler:** se dejó el kernel que el instalador de CachyOS pone por defecto, es decir `linux-cachyos` con el parche BORE ya activo. No hizo falta elegir una variante distinta ni cargar un scheduler sched-ext a mano. Vale la pena subrayarlo, porque es justo lo que diferencia a CachyOS de un Arch vanilla: la política de planificación llega modificada de fábrica, sin que el usuario tenga que tocar nada.

**Proceso de instalación.** CachyOS se instala desde una ISO propia con instalador gráfico, así que no exige el procedimiento manual de un Arch vanilla (particionado a mano, `pacstrap`, `genfstab` y configuración del bootloader desde el chroot). Aun así la instalación no fue directa, y hubo dos puntos de fricción concretos:

1. **Particionado y arranque en dual boot.** Convivir con una instalación previa de Windows obligó a trabajar con cuidado el esquema de particiones y las entradas del gestor de arranque, para que ambos sistemas quedaran accesibles después de reiniciar.
2. **Controladores de dispositivo.** Buena parte del trabajo posterior a la instalación fue dejar el hardware funcionando bien. La configuración que hace falta depende bastante de la tarjeta de video y del procesador del equipo, y no es algo que la distribución resuelva sola en todos los casos.

**Verificación en el sistema instalado.** Estos comandos documentan, sobre la instalación real, los conceptos descritos en la sección 2. Conviene correrlos y adjuntar la salida o una captura de cada uno:

```bash
uname -r                          # versión y sabor del kernel en uso (debe mostrar cachyos)
pacman -Q | grep linux-cachyos    # paquete de kernel instalado, confirma la variante con BORE
nproc && lscpu | head -20         # núcleos disponibles y topología (sección 6, multiprocesador)
head -20 /proc/1/status           # datos del task_struct de systemd, PID 1 (sección 2.1, tablas)
chrt -p 1                         # política de planificación y prioridad de PID 1
ps -eo pid,ppid,ni,pri,cls,comm --sort=-pri | head -20   # clase de planificación por proceso
systemctl list-units --type=service --state=running | head -20   # procesos gestionados por systemd
btop                              # vista en vivo de procesos y carga por núcleo (captura de pantalla)
```

⟨PEGAR ACÁ la salida de los comandos y las capturas de la instalación⟩

## 4. Planificación de procesos y políticas

- El scheduler general-purpose por defecto del kernel Linux moderno (6.6 en adelante, que es lo que corre un Arch rolling release en 2026) ya no es CFS sino **EEVDF** (ver nota técnica de la introducción).
- **CachyOS** parte de EEVDF pero aplica encima el parche **BORE** (*Burst-Oriented Round Robin Extension*), que ajusta el "burst score" de cada proceso según su historial reciente de uso de CPU. El objetivo es mejorar la latencia y la interactividad percibida (por ejemplo, que la interfaz no se sienta trabada mientras algo compila en segundo plano) sin sacrificar tanto throughput.
- CachyOS también ofrece **sched-ext**, schedulers extensibles escritos en BPF y soportados en mainline desde el kernel 6.12. Permiten cambiar de planificador en caliente, sin recompilar el kernel: `scx_bore`, `scx_lavd` y `scx_rusty`, cada uno afinado para un caso de uso distinto (juegos, servidores, ahorro de energía).
- **Omarchy** no toca el scheduler: corre el EEVDF por defecto del kernel de Arch, sin BORE ni sched-ext.
- **Parámetro de configuración concreto:** en CachyOS la elección de planificador se hace a dos niveles. Primero, cuál paquete `linux-cachyos-*` se instala; segundo, y de forma opcional, cuál scheduler sched-ext se carga en tiempo de ejecución.

## 5. Sincronización y comunicación entre procesos

- **`futex`** (*fast userspace mutex*) es el mecanismo base del kernel sobre el que glibc construye los mutex y semáforos de `pthread`. Es igual en ambas distribuciones, porque es una característica del kernel y de la libc, no de la distro.
- IPC estándar disponible en ambas: *pipes* y FIFOs, señales, memoria compartida POSIX (`shm_open`), colas de mensajes y sockets Unix.
- **D-Bus:** el bus de mensajería que usan systemd y la mayor parte del stack de escritorio moderno para la comunicación entre procesos de usuario y servicios del sistema. Es un componente central en la experiencia de escritorio de Omarchy, porque Hyprland y los portales de escritorio dependen de él.

## 6. Gestión en sistemas multiprocesador y virtualizados

- EEVDF y BORE son schedulers conscientes de múltiples CPUs: cada núcleo mantiene su propia cola de ejecución, con balanceo de carga entre núcleos y, si el hardware lo soporta, conocimiento de la topología NUMA.
- `cgroups v2`, que systemd usa para agrupar y limitar recursos por servicio o por sesión de usuario, es el mecanismo compartido de administración de recursos multiprocesador en ambas variantes.
- **Plataforma real de cada instalación.** La instalación de CachyOS corre en bare metal, en dual boot con Windows, de modo que el scheduler trabaja sobre el hardware real y no sobre CPUs virtualizadas. La de Omarchy corre en ⟨CONFIRMAR CON JOSEPH⟩. La distinción importa para este apartado: en una máquina virtual el planificador del sistema huésped reparte tiempo sobre CPUs que a su vez son procesos planificados por el anfitrión, así que las mediciones de latencia no son directamente comparables con las de una instalación nativa.

## 7. Comparación con otro sistema operativo

- **Comparación interna (misma familia, dos filosofías):** CachyOS (BORE y sched-ext sobre EEVDF) contra Omarchy (EEVDF estándar sin modificar). Mismo kernel base, distinta decisión sobre el planificador, lo que permite aislar el efecto real de BORE sin cambiar de distribución.
- **Comparación externa (criterio de "otro sistema operativo" de la rúbrica):** contra Windows, cuyo scheduler usa clases de prioridad fijas más un quantum variable según el tipo de proceso, con *foreground boost* para la aplicación activa. Es un modelo más rígido y orientado a prioridades estáticas, frente al cálculo dinámico de "tiempo virtual" que usan EEVDF y BORE en Linux.
- Esta comparación no es solo teórica en nuestro caso: como la instalación de CachyOS quedó en dual boot con Windows, ambos sistemas corren sobre el mismo procesador, la misma memoria y el mismo disco. Cualquier diferencia de comportamiento que se observe al alternar entre uno y otro es atribuible al sistema operativo y no al hardware, que es la única forma limpia de sostener una comparación de este tipo.

## 8. Análisis de experiencia de usuario

Este apartado recoge la experiencia de primera mano de cada integrante con su instalación. Conviene aclarar el punto de partida, porque cambia el peso de lo que sigue: para quien instaló CachyOS esta fue su primera experiencia con Linux, así que varias de las dificultades que se listan abajo son propias de la curva de entrada al sistema y no defectos exclusivos de esta distribución.

### 8.1 CachyOS

**Ventajas**

1. **El rendimiento se nota.** El sistema se siente rápido en el uso diario, incluso viniendo de Windows en la misma máquina. Es una impresión de uso, no una medición, pero es consistente con lo que la distribución promete al enviar el kernel con BORE activo.
2. **La parte técnicamente interesante viene resuelta de fábrica.** El kernel parcheado y la política de planificación modificada llegan configurados desde la instalación. Para efectos de esta indagatoria eso significa que el objeto de estudio estaba disponible sin tener que compilar ni configurar nada a mano.
3. **Instalador gráfico en vez del procedimiento manual de Arch.** Se evita el particionado a mano, el `pacstrap` y la configuración del bootloader desde el chroot, que es la barrera clásica de entrada a Arch Linux.
4. **Herramientas propias útiles.** La distribución agrega utilidades propias para administrar el sistema y cambiar de kernel o de scheduler, que en un Arch vanilla habría que armar por cuenta propia.

**Desventajas**

1. **Mucha configuración dependiente del hardware.** Dejar el equipo funcionando bien exigió trabajo posterior a la instalación, y lo que hace falta cambia bastante según la tarjeta de video y el procesador. La distribución no lo resuelve sola en todos los casos.
2. **Controladores de dispositivo.** Los drivers fueron uno de los dos puntos de fricción reales de la instalación, en línea con lo anterior.
3. **Fricción del dual boot.** Convivir con Windows obligó a manejar con cuidado el particionado y las entradas de arranque, un paso donde un error deja la máquina sin arrancar a ninguno de los dos sistemas.
4. **Curva de entrada alta para un primer Linux.** Es un buen sistema, pero no es el que recomendaríamos como primera distribución. La combinación de dual boot, drivers y ecosistema Arch supone más conocimiento previo del que un usuario nuevo suele tener.
5. **Comunidad y documentación más chicas.** Al ser una distribución menos masiva, ante un problema específico hay menos material disponible que para Ubuntu o para el propio Arch vanilla.

### 8.2 Omarchy

**Ventajas**

1. **La ISO trae su propio instalador.** No hay que seguir la guía manual de instalación de Arch: el proceso es guiado y basta con responder los pasos habituales de teclado, usuario, contraseña y partición de destino.
2. **Se llega a un escritorio de desarrollo ya configurado.** El sistema queda listo con Hyprland y sus atajos definidos, sin la etapa de elegir y configurar entorno gráfico, barra, lanzador y compositor pieza por pieza.
3. **Configuración legible y en archivos de texto.** Todo lo del escritorio vive bajo `~/.config`, así que se puede leer y modificar directamente, lo que ayuda a entender qué está corriendo y por qué.

**Desventajas**

1. **Exige desactivar Secure Boot.** Hay que entrar a la BIOS y desactivarlo antes de instalar, un paso que no es evidente para un usuario nuevo y que en equipos con Windows puede afectar otras configuraciones del arranque.
2. **Es una configuración opinionada.** Se acepta el conjunto de decisiones que tomó el autor del proyecto. Es la contracara directa de la comodidad: se gana velocidad de puesta en marcha y se cede control sobre las piezas elegidas.
3. **Depende de un proyecto joven y mantenido por una sola persona.** Frente a los cambios upstream de Arch y de Hyprland, la continuidad del instalador depende de que su autor lo mantenga al día.

⟨JOSEPH: revisá estos seis puntos y agregá lo que hayas vivido de primera mano, sobre todo la curva de aprendizaje de Hyprland viniendo de otro entorno, que es la desventaja que más se repite en la práctica y que nadie más del equipo puede escribir⟩

## 9. Análisis crítico y conclusiones

**Fortalezas.** CachyOS ofrece control fino sobre el planificador sin salir del ecosistema Arch, algo poco común entre distribuciones mainstream, que normalmente no exponen sched-ext al usuario final. Omarchy demuestra que se puede llegar a un Arch funcional sin la fricción de una instalación manual, a cambio de ceder ese control fino de rendimiento.

**Debilidades.** Un scheduler parcheado como BORE introduce una superficie de comportamiento no estándar: si algo falla, hay menos documentación y menos ayuda específica disponible que para el kernel vanilla. Omarchy, al ser mantenido por una sola persona y ser relativamente joven, depende de que su script de instalación se mantenga al día frente a los cambios upstream de Arch y de Hyprland.

### Conclusiones

**La gestión de procesos es un asunto del kernel, no de la distribución.** Fue el hallazgo más claro de comparar dos sistemas de la misma familia. Todo lo estructural resultó idéntico en CachyOS y en Omarchy: la creación de procesos con `fork()` y `exec()`, el `task_struct` expuesto en `/proc`, systemd como PID 1 organizando servicios en cgroups, `futex` como base de la sincronización y D-Bus como bus de comunicación entre procesos. Una distribución no reescribe nada de eso. El margen real que tiene para diferenciarse es estrecho, pero es justamente el más decisivo: qué política de planificación aplica y qué herramientas entrega para observarla y cambiarla.

**Ahí se separan las dos variantes.** CachyOS interviene ese punto exacto, enviando un kernel con BORE aplicado sobre EEVDF y la opción de cargar schedulers sched-ext en caliente. Omarchy no lo toca y deja el EEVDF por defecto, porque su esfuerzo está puesto en la capa de escritorio. Son dos respuestas distintas a la misma pregunta sobre qué vale la pena optimizar, y ninguna de las dos es incorrecta: dependen de qué le duele al usuario, la latencia bajo carga o el tiempo que cuesta llegar a un sistema utilizable.

**Verificar el sistema real valió más que repetir el ejemplo de la guía.** El material del curso presenta CFS como el planificador de Linux, y comprobar qué corría de verdad en un kernel de 2026 mostró que ese dato quedó desactualizado desde la versión 6.6, cuando EEVDF lo reemplazó. La conclusión metodológica es que en un sistema *rolling-release* la documentación general envejece rápido y conviene confirmar contra la máquina que se tiene enfrente.

**El costo de la facilidad se paga en control, y viceversa.** Las dos instalaciones lo mostraron en la práctica. Omarchy redujo la fricción a un instalador guiado, a cambio de aceptar un conjunto cerrado de decisiones. CachyOS entregó la política de planificación optimizada de fábrica, pero exigió resolver drivers, particionado y arranque en dual boot, y resultó exigente como primera experiencia con Linux. La comodidad y el control fino se compran uno con el otro.

**Limitación del trabajo.** La percepción de mayor fluidez en CachyOS es una impresión de uso y no una medición. Para sostenerla haría falta ejecutar la misma carga de trabajo sobre el mismo hardware alternando entre un kernel con BORE y uno vanilla, y comparar latencia y throughput con datos. Es la continuación natural de esta indagatoria y, con el dual boot ya montado, la máquina para hacerlo está disponible.

## 10. Referencias

- Stallings, W. (2018). *Operating Systems: Internals and Design Principles* (9th ed.). Pearson.
- Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). *Operating System Concepts* (10th ed.). Wiley.
- Arpaci-Dusseau, R. H., & Arpaci-Dusseau, A. C. (2018). *Operating Systems: Three Easy Pieces*. Arpaci-Dusseau Books. https://pages.cs.wisc.edu/~remzi/OSTEP/
- Linux Kernel Documentation. *Scheduler: EEVDF*. https://docs.kernel.org/scheduler/
- CachyOS Wiki. *Kernel & Scheduler options*. https://wiki.cachyos.org/
- Omarchy. Documentación oficial del proyecto. https://omarchy.org/
- Arch Wiki. *systemd*, *Process management*. https://wiki.archlinux.org/

---

## Control interno (no va en la entrega)

### Checklist contra la rúbrica

- [x] Introducción y descripción del sistema (10%)
- [x] Descripción técnica de la gestión de procesos: kernel, tablas, colas, herramientas (20%)
- [~] Evidencia práctica: instalación y pruebas documentadas (15%). Narrativa de ambas instalaciones lista. Falta: salida de los comandos de verificación en CachyOS, las dos capturas de Omarchy en el vault, y confirmar la plataforma de Joseph
- [x] Planificación de procesos y políticas (15%), incluye la corrección EEVDF/BORE
- [x] Sincronización y comunicación entre procesos (10%)
- [x] Comparación con otro sistema operativo (10%)
- [x] Análisis crítico y conclusiones (10%)
- [~] Análisis de experiencia de usuario, 3-5 ventajas y 3-5 desventajas (5%). CachyOS listo (5 y 5). Omarchy escrito a partir de lo que documentó Joseph, falta que él lo revise y agregue la curva de Hyprland
- [x] Calidad del documento y referencias (5%)

### Cosas que quedan fuera de mi alcance

1. **Joseph:** plataforma de su instalación (bare metal, dual boot o VM), los cuatro atajos marcados en la tabla, y revisar el apartado 8.2.
2. **Marcos:** correr el bloque de comandos de la sección 3.2 y pegar la salida, más las capturas de la instalación.

### Capturas que faltan meter al vault

Las dos imágenes de la instalación de Omarchy no están en el vault (Joseph las pasó pegadas en el documento compartido). Hay que dejarlas en la raíz del vault con estos nombres para que los enlaces de arriba resuelvan:

- `omarchy-descarga-iso.png` (página de descarga de omarchy.org)
- `omarchy-instalador-final.png` (pantalla de fin de instalación)
