---
curso: SistemasOperativos
tema: Unidad 6 — Sistema de Archivos (archivos y directorios)
fecha: 2026-08-07
tipo: apunte
fuente:
  - _fuentes/SistemasOperativos_sistema-archivos-unidad6_2026-08-07.pdf
tags: [unidad6, sistema-archivos, directorios, inodo, fat, enlaces, metodos-acceso]
---

# Unidad 6 — Sistema de Archivos (Semanas 14–15)

Ver también: [[Cursos/SistemasOperativos/temario]] · [[Cursos/SistemasOperativos/entregas]] · [[Cursos/SistemasOperativos/apuntes/historia-componentes-so-unidad2]]

## Objetivos de la unidad

- Entender los conceptos de fichero (archivo) y directorio.
- Mostrar métodos de acceso y mecanismos de protección.
- Entender la estructura del sistema de archivos.
- Analizar las llamadas al sistema y ejemplos de programación en Linux y Windows.
- Analizar distintas técnicas de gestión de archivos y directorios a nivel de diseño.

## Parte 1 — Archivos

### Visión del usuario

- **Visión lógica:** archivos, directorios, sistemas de archivos y particiones.
- **Visión física:** bloques o bytes ubicados en dispositivos (sectores, clusters).

**Función principal:** el sistema de archivos establece una correspondencia entre los archivos (file view) y los dispositivos lógicos (array view → physical view: sectores, platters). El controlador de disco gestiona el mapeo físico; el SO gestiona el mapeo lógico.

### Características para el usuario

- Almacenamiento **permanente** — no desaparece al apagar el computador.
- Conjunto de información **estructurada lógicamente** según criterios de la aplicación.
- **Nombres lógicos y estructurados**, no ligados al ciclo de vida de una aplicación particular.
- **Abstrae** los dispositivos de almacenamiento físico.
- Se accede vía llamadas al sistema operativo o bibliotecas de utilidades.

El sistema de archivos es la capa de software entre dispositivos y usuarios: el acceso directo a dispositivos es **incómodo** (detalles físicos, direcciones físicas) y **no seguro** (sin restricciones a nivel físico).

### Concepto de archivo

Espacio lógico de direcciones contiguas usado para almacenar datos. Tipos: **datos** (numéricos, carácter, binarios), **programas** (código fuente, archivos objeto/imagen de carga), **documentos**.

### Atributos del archivo

- **Nombre** — única información legible por una persona.
- **Identificación única** — descriptor interno, dueño y grupo.
- **Tipo de archivo** — necesario en sistemas con distintos formatos.
- **Tamaño** — bytes actuales, tamaño máximo posible, etc.
- **Protección** — control de accesos y operaciones permitidas.
- **Información temporal** — creación, acceso, modificación.
- **Información de control** — oculto, de sistema, normal o directorio.

Ejemplos de representación: **nodo-i de UNIX** (tipo/protección, número de nombres, propietario, grupo, tamaño, tiempos, punteros a bloques de datos 0-9, punteros indirectos simple/doble/triple); **entrada de directorio de MS-DOS** (nombre, atributos, tamaño en KB, agrupación FAT); **registro MFT de Windows NT** (cabecera, atributos, tamaño, nombre, seguridad, datos, vclusters).

### Nombres de archivo y extensiones

- Se usan nombres lógicos (tiras de caracteres) porque los usuarios no recuerdan identificadores numéricos.
- Longitud y extensión varían por sistema: fija en MS-DOS, variable en UNIX.
- **Sensibilidad a mayúsculas/minúsculas:** `CATALINA` y `catalina` son el mismo archivo en Windows pero distintos en Linux.
- El sistema de archivos trabaja con descriptores internos; solo distingue algunos formatos (ejecutables, texto) — ej. número mágico de UNIX. Las extensiones son significativas para las aplicaciones, no para el SO.

### Estructura de un archivo

- **Secuencia/tira de bytes** (UNIX, POSIX) — posición dentro de la tira.
- **Registros** de tamaño fijo o variable.
- **Estructuras complejas** construidas como capa sobre la tira de bytes: archivos indexados (fichero índice con clave → fichero principal con registros) y archivos directos o de dispersión.
- Ejemplo de archivo ejecutable de Linux: cabecera primaria (número mágico, número de secciones, tamaños de segmento texto/datos, tamaño tabla de símbolos, dirección inicial, opciones) + cabeceras de sección + secciones (código, datos con valor inicial, información de carga, tabla de símbolos).

### Visión lógica vs. física

El usuario ve una tira de posiciones (visión lógica); el SO traduce eso a un conjunto de bloques de la unidad de disco (visión física) — un mismo archivo puede ocupar bloques no contiguos (ej. bloques 13, 20, 1, 8, 3, 16, 19).

- **Bloque:** unidad de transferencia, 2ⁿ sectores, parámetro fijo por sistema de archivos.
- **Agrupación (cluster):** unidad de asignación, 2ᵖ bloques; aumenta la secuencialidad del archivo.

### Descripción física en UNIX (nodo-i / i-node)

El i-nodo contiene tipo y protección, número de enlaces, propietario/grupo, tamaño, fechas de creación/modificación/acceso, y punteros a bloques: 10 punteros directos + puntero indirecto simple + puntero indirecto doble + puntero indirecto triple. También llamados **ficheros indexados**.

Tamaño máximo del archivo con bloque de tamaño `Sb` y direcciones de bloque de 4 bytes:

```
10·Sb + (Sb/4)·Sb + (Sb/4)²·Sb + (Sb/4)³·Sb
```

(tamaño típico de bloque: 4 KB; tamaño típico de sector: 512 B)

### Descripción física en MS-DOS (FAT — File Allocation Table)

Primer byte del nombre de entrada: `0x00` entrada libre, `0xE5` entrada borrada, `0x05` primer carácter real es `0xE5`. Variantes: FAT de 12 bits (4K agrupaciones), 16 bits (64K agrupaciones), 32 bits (2²⁸ agrupaciones, solo usa 28 bits). Atributos: System, Hidden, Read-only, Archived, Directory, Volume. El directorio raíz apunta a la primera agrupación de cada archivo; la FAT encadena las siguientes agrupaciones hasta `<eof>`.

### Métodos de acceso

- **Acceso secuencial** — lectura en orden ascendente desde el principio (`read next`, `write next`, `reset`, `rewind`). La posición avanza según los datos leídos. Típico de dispositivos de cinta. ISAM = método de acceso secuencial indexado.
- **Acceso directo** — `read n`, `write n`, `goto n`, `rewrite n` donde `n` es el número de bloque relativo al origen. Típico de discos magnéticos.

### Semántica de coutilización

Especifica el efecto de varios procesos accediendo simultáneamente al mismo archivo y cuándo se hacen efectivas las modificaciones.

- **Semántica UNIX (POSIX):** las escrituras son inmediatamente visibles para todos los procesos con el archivo abierto; la coutilización afecta también a los metadatos.
- **Semántica de sesión:** las escrituras de un proceso no son visibles para otros hasta que se cierra el archivo; un archivo puede tener varias imágenes temporales asociadas.
- **Semántica de versiones:** las actualizaciones se hacen sobre copias con número de versión; solo son visibles al consolidar versiones; requiere sincronización explícita para actualización inmediata.
- **Semántica de archivos inmutables:** una vez creado, el archivo solo se comparte para lectura y nunca cambia.

## Parte 2 — Directorios

### Directorio

Objeto que relaciona de forma unívoca un nombre de usuario de archivo con su descriptor interno; organiza y da información sobre la estructuración del sistema de archivos; colección de nodos con información sobre los archivos.

### Visión lógica

Esquema jerárquico: al abrir un archivo, el SO busca el nombre en la estructura de directorios. Operaciones: crear/borrar, abrir/cerrar, renombrar, leer entradas, montar. La jerarquía simplifica el nombrado (nombres únicos) y permite agrupar archivos lógicamente (mismo usuario, misma aplicación).

### Estructura física de los directorios

Tanto el directorio como los archivos residen en disco; **los directorios se implementan como archivos**; copias de respaldo en cinta por seguridad. Información típica: nombre, tipo, dirección, longitud máxima/actual, tiempos de acceso/modificación, dueño.

Dos alternativas de diseño:
1. Almacenar los atributos del archivo directamente en la entrada de directorio.
2. Almacenar `<nombre, identificador>` con los datos del archivo en una estructura distinta — **esta es la mejor** (ej. UNIX: entrada = nodo-i + nombre).

Otras estructuras físicas de directorio:
- **Tabla contigua** con entradas de tamaño fijo — falta de flexibilidad, búsqueda lenta en directorios grandes.
- **Lista encadenada** con entradas de tamaño variable — búsqueda lenta en directorios grandes.
- **HTree** (BTree con hashes de 32 bits) — búsqueda rápida en directorios grandes.

**Ejemplos de entradas de directorio por sistema:**
- **CP/M:** código de usuario, nombre, tipo de archivo, flag de archivo extendido, contador de bloques, números de bloque.
- **MS-DOS:** nombre, tipo de archivo, atributos, reservado, hora, fecha, número del primer bloque, tamaño.
- **UNIX:** nodo-i (puntero al descriptor) + nombre.
- **ISO-9660 (CD-ROM):** longitud, tamaño archivo, ubicación archivo, número CD, fecha y hora, nombre base, sistema.
- **FAT:** nombre, atributos, reservado, hora, fecha, tamaño, tipo de fichero, número del primer bloque.
- **UNIX SV:** nodo-i, nombre.
- **Linux Ext2:** nodo-i, longitud entrada, longitud nombre, tipo, nombre.
- **Windows NTFS:** entrada MFT, atributos, longitud nombre, nombre unicode.

### Organización del directorio (criterios de diseño)

- **Eficiencia:** localizar un archivo rápidamente.
- **Nombrado:** conveniente para usuarios — dos usuarios pueden nombrar archivos distintos igual; el mismo archivo puede tener nombres distintos; nombres de longitud variable.
- **Agrupación:** lógica según propiedades (programas, juegos, etc.).
- **Estructurado:** operaciones claramente definidas y ocultación de detalles.
- **Sencillez:** la entrada de directorio debe ser lo más simple posible.

### Modelos de organización

- **Directorio de un nivel** — un único directorio para todos los usuarios; problemas de nombrado y agrupación (colisión de nombres entre usuarios).
- **Directorio de dos niveles** — un directorio por usuario dentro de un directorio maestro; camino de acceso automático o manual; el mismo nombre de archivo puede repetirse entre usuarios distintos; búsqueda eficiente pero con problemas de agrupación dentro del espacio de cada usuario.
- **Directorio con estructura de árbol** — búsqueda eficiente y agrupación; nombres relativos y absolutos vía el directorio de trabajo (working directory).
- **Directorio de grafo acíclico** — permite archivos y subdirectorios **compartidos** entre ramas del árbol (ej. un archivo `claves` referenciado desde dos directorios distintos). **Este concepto no existe en Windows.**

### Interpretación de nombres en Linux (resolución de ruta)

Ejemplo: interpretar `/users/Ana/claves`
1. Traer a memoria las entradas del archivo con i-nodo 2 (raíz).
2. Buscar `users` dentro → se obtiene el i-nodo 342.
3. Traer a memoria las entradas del archivo con i-nodo 342.
4. Buscar `Ana` dentro → se obtiene el i-nodo 256.
5. Traer a memoria las entradas del archivo con i-nodo 256.
6. Buscar `claves` dentro → se obtiene el i-nodo 758.
7. Leer el i-nodo 758 → se tiene la ubicación de los datos del archivo.
8. Leer los bloques del fichero.

¿Cuándo parar la resolución? — no se tienen permisos; se encontró el i-nodo del archivo; no se encontró y no hay más subdirectorios; se está en un directorio que no contiene la siguiente componente del nombre.

**Importante:** un directorio no es un i-nodo — el i-nodo del directorio apunta a un bloque de datos del directorio (tabla nombre→i-nodo), y cada entrada de esa tabla apunta al i-nodo real del archivo, que a su vez apunta a los bloques de datos del archivo. La llamada `OPEN` termina con la lectura del i-nodo del archivo; la verificación de permisos se hace con los datos de ese i-nodo.

### Enlaces (links)

Un archivo con varios nombres requiere control de enlaces:
- **Enlace físico (hard link):** un único archivo, con contador de enlaces en su descriptor (i-nodo). Comparten el mismo número de i-nodo.
- **Enlace simbólico (symlink):** un archivo nuevo cuyo contenido es la ruta al destino (como un "acceso directo" de Windows).

**Borrado de enlaces — estrategias posibles:**
a) Decrementar el contador de enlaces; si llega a 0, borrar el archivo.
b) Recorrer todos los enlaces y borrarlos todos.
c) Borrar únicamente el enlace referenciado, dejando los demás intactos.

**Problema grave:** posibilidad de bucles en el árbol de directorios. Soluciones: permitir enlaces solo a archivos (no a subdirectorios), o un algoritmo de búsqueda de bucles al crear el enlace.

**Limitación de UNIX:** los enlaces físicos solo funcionan dentro del mismo sistema de archivos (mismo dispositivo/partición).

**Síntesis enlaces físicos vs. simbólicos:**

| Aspecto | Enlace físico | Enlace simbólico |
|---|---|---|
| Se puede crear sobre | Solo archivos | Archivos y/o directorios |
| Entre sistemas de archivos distintos | No | Sí |
| Comparte número de i-nodo con el original | Sí | No |
| Si se borra el original | El enlace sigue funcionando (dato no se pierde) | La información se pierde (enlace roto) |
| Naturaleza | Copia exacta / referencia al mismo archivo | Puntero o "acceso directo" |
