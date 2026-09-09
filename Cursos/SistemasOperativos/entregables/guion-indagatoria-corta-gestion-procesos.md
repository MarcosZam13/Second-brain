---
curso: SistemasOperativos
tema: "Guión de presentación — Indagatoria Corta: Gestión de Procesos en Arch Linux"
fecha: 2026-09-08
tipo: entregable
entregable_de: "[[Cursos/SistemasOperativos/entregables/indagatoria-corta-gestion-procesos]]"
estado: borrador
fuente: _fuentes/SistemasOperativos_indagatoria-corta-presentacion-html_2026-09-08.html
tags: [indagatoria-corta, unidad3, gestion-procesos, trabajo-grupal, arch-linux, guion, presentacion]
---

# Guión — Indagatoria Corta: Gestión de Procesos en Arch Linux

Ver también: [[Cursos/SistemasOperativos/entregables/indagatoria-corta-gestion-procesos|Documento completo]] · [[Cursos/SistemasOperativos/entregas]]

**Exposición:** jueves 2026-09-10 (semana 6) · 10 diapositivas + demo en vivo, 11 pantallas contando portada.

**Distribución (según la reparto que armó el equipo):** Mario abre con la parte conceptual (qué es Arch, el kernel, nacer/morir de un proceso); Marcos se mete con el experimento propio (CachyOS vs Omarchy, el planificador, la comparación con Windows, la experiencia de uso) y le cede la palabra a Joseph; Joseph hace la demo en vivo y cierra con el hallazgo y las preguntas. ⟨Mario/Marcos/Joseph: confirmen que las diapositivas 1, 3 y 4 quedan con Mario — el mensaje original no lo decía explícito, se asumió por descarte ya que Marcos y Joseph tienen bloque propio⟩.

Tono: hablado, no leído. Explicar lo justo para que se entienda, sin sonar a que se está recitando el documento. Ajustar el texto de cada bloque a como suene natural al ensayarlo — lo que importa es la idea, no la frase exacta.

## 1. Portada (0:20 — Mario)

> "Buenas, somos el equipo de Sistemas Operativos: Marcos Zamora, Mario Rojas y Joseph Fonseca. Nuestra indagatoria corta parte de una pregunta simple: ¿quién manda de verdad adentro de un Linux? Para responderla instalamos dos variantes de Arch Linux, CachyOS y Omarchy, y comparamos cómo cada una gestiona los procesos del sistema."

## 2. Qué es Arch — filosofía KISS (0:40 — Mario)

> "Antes de meternos en procesos, un contexto rápido de qué es Arch. La mayoría de sistemas operativos llegan armados: instalás y ya tenés el escritorio, los programas, todo. Arch no. Arch te da la bolsa de piezas y el instructivo — vos decidís qué corre en tu máquina, pieza por pieza, nada viene por defecto.
>
> Eso es literalmente la filosofía del proyecto, que se resume en una sigla: KISS, 'keep it simple, stupid'. Menos capas escondidas por debajo, más control real sobre lo que está pasando. Y ese control es justo lo que nos va a servir para el resto de la presentación, porque nos deja ver la gestión de procesos sin nada tapándola."

## 3. El kernel como torre de control (1:00 — Mario)

> "Para hablar de gestión de procesos hay una analogía que nos sirvió mucho: el kernel funciona como la torre de control de un aeropuerto. Cada programa corriendo es un avión pidiendo pista. El kernel decide el orden de despegue, maneja la fila de espera, y si hace falta, interrumpe un vuelo — todo eso sin que el usuario tenga que meter mano.
>
> Tres cosas concretas sostienen esa analogía. Primero, el `task_struct`: es el registro de cada proceso, su identidad, qué CPU pidió, dónde está en la fila. Segundo, `/proc/[pid]`, que es donde el kernel expone esos registros para que cualquiera los pueda consultar. Y tercero, la run queue, que es literalmente la fila de despegue — hay un carril de espera por cada núcleo del procesador."

## 4. Nacer y morir: fork, exec, kill (0:45 — Mario)

> "¿Y cómo nace y muere un proceso en la práctica? Cuando abrís una terminal y escribís un comando, el sistema clona el proceso actual — eso es `fork` — y lo reemplaza por el programa nuevo, eso es `exec`. Para cerrarlo, se le manda una señal.
>
> [mostrar terminal] Acá lo tenemos en vivo: `kill -SIGTERM` es pedirle amablemente al proceso que se cierre, le da chance de guardar lo que tenga pendiente. `kill -9` ya es obligarlo, sin preguntar. Con esto ya cubrimos todo el ciclo de vida de un proceso: nace con fork y exec, muere con una señal."

*(Mario cede la palabra: "Con esto ya vimos cómo funciona un Linux en general. Ahora Marcos les cuenta las dos variantes concretas que instalamos y probamos.")*

## 5. CachyOS vs Omarchy (0:50 — Marcos)

> "Gracias, Mario. Instalamos el mismo Arch armado de dos formas distintas. Yo instalé CachyOS, que es un Arch pensado para exprimir el hardware: viene con un kernel propio ya modificado, y lo más importante para nosotros, te deja elegir cómo reparte el CPU su tiempo entre los procesos — eso va a ser el corazón de lo que viene.
>
> Joseph instaló Omarchy, que es un Arch con instalador guiado y el escritorio ya listo. Dato curioso: lo hizo David Heinemeier Hansson, el creador de Ruby on Rails. Omarchy no toca el motor del sistema — se enfoca en que la experiencia de llegar a un Arch funcionando sea fácil, no en cambiar cómo planifica procesos."

## 6. El planificador: EEVDF vs BORE (1:00 — Marcos)

> "Esta es la parte que más nos interesó investigar. El planificador es la pieza que decide quién pasa primero cuando varios procesos quieren CPU al mismo tiempo. Y acá hay algo que ni el mismo material del curso tiene actualizado: Linux moderno ya no usa CFS, que es lo que uno suele ver en los libros. Desde 2023 corre uno nuevo, EEVDF.
>
> CachyOS le suma encima un parche llamado BORE, que le da prioridad a lo que uno siente en el momento — mover el mouse, escribir en el teclado — por sobre lo que corre calladito en el fondo, como una compilación. [mostrar gráfico de barras] Esto que ven acá es nuestra impresión de uso al usar cada sistema en el día a día, no una medición de laboratorio con benchmarks — lo aclaramos porque es una diferencia importante entre percepción y medición real."

## 7. Comparación con Windows (0:40 — Marcos)

> "Para tener un punto de comparación fuera de la familia Linux, lo pusimos contra Windows. Windows reparte turnos fijos: le asigna una prioridad fija a cada proceso y le da un empujón extra a la ventana que tenés activa. Linux con EEVDF y BORE hace algo distinto: recalcula todo el tiempo un 'tiempo virtual' por proceso. Es un modelo más flexible, pero también menos predecible que el de Windows."

## 8. Experiencia de usuario (0:45 — Marcos)

> "Y en la práctica, ¿qué se siente usar cada uno? Con CachyOS, lo primero que notás es que se siente rápido desde el día uno, y Omarchy se instala solo, sin tener que tocar terminal para nada — las dos partes trajeron sus herramientas ya resueltas.
>
> La otra cara: a mí instalar CachyOS me costó pelear con drivers y con el dual boot. Omarchy, en cambio, te hace aceptar las decisiones de su creador tal cual vienen. Y los dos tienen una comunidad más chica que Ubuntu si algo se rompe. En resumen: ganás rendimiento o ganás comodidad, pero rara vez las dos cosas a la vez."

## 9. Transición a la demo (0:15 — Marcos → cede a Joseph)

> "Toda esta teoría se entiende mejor viéndola correr de verdad. Le paso la palabra a Joseph, que nos va a mostrar todo esto en vivo sobre las dos máquinas."

## 10. Demo en vivo (fuera del archivo — Joseph)

*No está en las diapositivas, es la parte más importante en tiempo. Base para improvisar, según lo que ya quedó documentado en el informe:*

- **Omarchy:** `fastfetch` (kernel/hardware), `btop` (procesos y CPU en vivo), recorrer `~/.config` para mostrar que la configuración es texto plano. Atajos de teclado clave: `Super+Enter` (terminal), `Super+K` (lista de atajos — sirve para resolver en vivo los que falten confirmar).
- **CachyOS:** `uname -r` y `pacman -Q | grep linux-cachyos` (confirmar kernel BORE), `chrt -p 1` y `ps -eo pid,ppid,ni,pri,cls,comm --sort=-pri` (clase de planificación por proceso), `btop` en vivo.
- Si algo no arranca en el momento, tener las capturas de respaldo del documento a mano.

## 11. Conclusión — el hallazgo real (0:40 — Joseph)

> "Después de instalar y probar las dos variantes, esto es lo que nos quedó claro: gestionar procesos es trabajo del kernel, no de la distribución. `fork`, `/proc`, systemd, futex, D-Bus — todo eso fue idéntico en los dos sistemas, letra por letra. Lo único que una distribución puede cambiar de verdad es qué planificador corre y qué tan fácil es llegar a usarlo. Y eso fue justo lo que comparamos hoy."

## 12. Cierre — preguntas (0:15 — Joseph)

> "Con eso cerramos: dos formas distintas de armar el mismo Arch, comparadas en el mismo hardware. Marcos Zamora, Mario Rojas y Joseph Fonseca. Muchas gracias, quedamos atentos a preguntas."

---

## Próximos pasos

- [ ] Confirmar con Mario y Joseph la asignación de las diapositivas 1, 3 y 4 (se asumió que las dice Mario, por descarte).
- [ ] Ensayar en voz alta contra el tiempo real. Sin contar la demo, el guión da ~7 minutos; sumarle lo que tome la demo en vivo.
- [ ] Definir en el ensayo qué tan larga hacen la demo Joseph y el equipo — es la parte con más margen para estirarse o acortarse según el tiempo que quede.
- [ ] Traer las capturas del documento como respaldo por si algo falla en vivo durante la demo.
