---
curso: Seguridad
tema: Lab GRUPAL — Ingeniería Inversa
fecha: 2026-09-21
tipo: entregable
entregable_de: "[[Cursos/Seguridad/apuntes/lab-ingenieria-inversa-instrucciones]]"
estado: borrador
tags: [ingenieria-inversa, reversing, laboratorio, grupal, ghidra, gdb]
---

# Lab GRUPAL — Ingeniería Inversa: walkthrough y respuestas

Ver también: [[Cursos/Seguridad/apuntes/lab-ingenieria-inversa-instrucciones|Instrucciones oficiales del lab]] · [[Cursos/Seguridad/apuntes/ingenieria-inversa-analisis-software|Teoría — Ingeniería inversa]] · [[Cursos/Seguridad/entregables/reversing_lab/README|kit de archivos]] · [[Cursos/Seguridad/entregas]]

**Qué es esto:** guion técnico con los comandos exactos, la salida esperada y las explicaciones para grabar el video grupal (valor 5%, todos con cámara encendida ejecutando los pasos). No reemplaza grabar el video — es la base para no improvisar en cámara y para que cada quien entienda qué está pasando, no solo copie comandos.

**Estado:** borrador — falta correrlo en la VM/WSL real del equipo y confirmar que los valores exactos (hash, direcciones de memoria) coinciden con lo que muestro acá como "esperado". Las direcciones de memoria y el hash SHA-256 van a ser distintos en su máquina — eso es normal, lo que importa es el patrón.

## 0) Entorno — qué instalar antes de grabar

Windows no trae los binarios de recon (`strings`, `objdump`, `strip`) ni GDB de forma nativa. Opciones, de más a menos recomendada:

- **WSL2 + Ubuntu** (recomendado si están en Windows):
  ```powershell
  wsl --install -d Ubuntu
  ```
  Dentro de WSL:
  ```bash
  sudo apt update && sudo apt install -y build-essential gdb binutils
  ```
- **Ghidra** (no viene en los paquetes de arriba): descargar de ghidra-sre.org, requiere JDK 17+. Se puede correr Ghidra en Windows normal apuntando al binario compilado dentro de WSL (la ruta de WSL se ve como `\\wsl$\Ubuntu\...` desde el Explorador).
- Alternativa: máquina virtual Kali/Ubuntu completa, como recomienda el enunciado.

Si terminan usando una combinación distinta (ej. Ghidra en Windows + compilación en WSL), **eso es justo lo que el enunciado pide mencionar en el video** ("en caso que deban ajustar alguna instrucción, indicarlo").

## 1) Compilar

Dentro de `entregables/reversing_lab/`:
```bash
chmod +x build.sh
./build.sh
```
Genera `bin/safecheck`, `bin/safecheck_stripped`, `bin/obfcheck`.

## 2) Parte A — Reconocimiento estático

### `file bin/safecheck`
Esperado (el patrón, no el hash literal):
```
bin/safecheck: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, ..., not stripped
```
**Para el video:** señalar 3 cosas del output — formato (ELF = Linux), arquitectura (x86-64) y que dice `not stripped` (todavía tiene la tabla de símbolos).

### `sha256sum bin/safecheck`
Un hash de 64 caracteres hex. Anotarlo tal cual les salga — sirve para decir "esta es la muestra exacta que analizamos" si alguien más quisiera reproducir el análisis.

### `strings -n 4 bin/safecheck | less`
Entre mucho ruido de libc, deben aparecer estas 4 líneas — **son la clave de todo el ejercicio**:
```
Ingrese la clave: 
Cyber2025
Acceso concedido
Acceso denegado
```
**Para el video:** este es el punto más fuerte de la Parte A — sin desensamblar nada, `strings` ya reveló la contraseña en texto plano (`Cyber2025`). Esto es literalmente lo que dice la teoría: "a veces ya hay pistas sin ejecutar el binario".

### `strings -n 4 bin/obfcheck | less`
Acá el mensaje del video cambia — busquen las mismas 4 líneas y van a notar que **falta una**:
```
Ingrese la clave: 
Dzcfs3136
Acceso concedido
Acceso denegado
```
No aparece "Cyber2025" en ningún lado. Aparece `Dzcfs3136` — la clave ofuscada tal cual está escrita en el código fuente (`char secret[] = "Dzcfs3136"`), **antes** de que el programa la de-ofusque en tiempo de ejecución.

**Este es el contraste central del lab, dedíquenle tiempo en el video:** `strings` funciona genial contra `safecheck` porque la clave vive en el binario tal cual, pero contra `obfcheck` un análisis de solo-strings falla — hace falta desensamblar/decompilar (Parte B) o ejecutar y observar en memoria (Parte C) para recuperar la clave real. Es la demostración práctica de por qué la ofuscación, aunque sea trivial (restar 1 a cada carácter), ya rompe el análisis estático más básico.

### `objdump -t bin/safecheck | head`
Con símbolos (no stripped) van a ver entradas como `main`, `printf`, `scanf`, `strcmp` en la tabla de símbolos.

### Comparar con `objdump -t bin/safecheck_stripped`
Debe salir algo como:
```
bin/safecheck_stripped:     file format elf64-x86-64
```
Sin tabla de símbolos locales — `strip` se la quitó. **Para el video:** esto es la diferencia práctica entre analizar un binario "de desarrollo" (con símbolos, más fácil) y uno "de producción" (stripped, como suele venir el malware real).

## 3) Parte B — Ghidra

Pasos: File → New Project → Non-Shared → Import File (`bin/safecheck`) → Analyze con opciones por defecto → Symbol Tree → `main` → panel Decompile.

**Lo que van a ver decompilado (aproximado, gcc -O0 con símbolos reconstruye casi literal el C original):**
```c
undefined8 main(void)
{
  char pass [64];
  int iVar1;

  printf("Ingrese la clave: ");
  iVar1 = __isoc99_scanf("%63s", pass);
  if (iVar1 == 1) {
    iVar1 = strcmp(pass, "Cyber2025");
    if (iVar1 == 0) {
      puts("Acceso concedido");
    }
    else {
      puts("Acceso denegado");
    }
  }
  return 0;
}
```
**Aclaración para el video:** no se asusten si Ghidra le pone `__isoc99_scanf` en vez de `scanf` — es el nombre versionado interno de glibc para esa función, es la misma `scanf` del código fuente.

Repitiendo con `bin/obfcheck`, van a encontrar una función extra (`deobfuscate` o el nombre que Ghidra le invente si no hay símbolos) que recorre un buffer restando 1 a cada carácter antes del `strcmp`:
```c
void deobfuscate(char *s)
{
  int i;
  for (i = 0; s[i] != '\0'; i = i + 1) {
    s[i] = s[i] + -1;
  }
}
```
Y en `main`, la variable `secret` inicializada como `"Dzcfs3136"`, pasada a `deobfuscate(secret)` antes del `strcmp(pass, secret)`. **Este es el momento de la Parte B donde recuperan la clave real sin haber podido verla con `strings`** — conectarlo explícitamente con el hallazgo de la Parte A en el video.

**Etiquetado:** renombren `secret` → algo como `contraseña_real`, y agreguen un comentario en la línea del `strcmp` indicando que ahí se decide acceso concedido/denegado — esto es lo que pide el punto 6 del enunciado.

## 4) Parte C — GDB (dinámico)

Sobre `bin/safecheck`:
```
$ gdb -q bin/safecheck
(gdb) start
Temporary breakpoint 1, main () at src/safecheck.c:6
(gdb) break strcmp
(gdb) continue
Ingrese la clave: hola          <- escriban cualquier cosa acá, a propósito

Breakpoint 2, 0x... in strcmp ()
(gdb) x/s $rdi
0x...:  "hola"
(gdb) x/s $rsi
0x...:  "Cyber2025"
(gdb) finish
Run till exit from #0  strcmp ()
0x... in main ()
(gdb) set $rax=0
(gdb) continue
Acceso concedido
[Inferior 1 (process ...) exited normally]
```
**Qué está pasando (para narrar en el video):** `$rdi` es el primer argumento de `strcmp` en la convención x86_64 SysV — lo que ustedes escribieron. `$rsi` es el segundo argumento — la clave real, tal cual vive en el binario. Al forzar `$rax=0` después de que `strcmp` retorna, le mienten a `main`: le hacen creer que las cadenas fueron iguales aunque escribieron cualquier cosa. Esto es un **bypass en memoria, sin tocar el archivo en disco** — el binario `bin/safecheck` en el filesystem sigue intacto.

Sobre `bin/obfcheck`, repitan la misma secuencia. El punto a resaltar: cuando GDB se detiene en `strcmp`, `x/s $rsi` va a mostrar **"Cyber2025" ya en claro**, no "Dzcfs3136" — porque `deobfuscate()` ya corrió antes de llegar a esa línea. **Esto cierra el argumento de todo el lab:** aunque el string esté ofuscado en el archivo (Parte A no lo encontró), en memoria durante la ejecución siempre termina en claro en algún punto (tiene que estarlo para poder compararse), y un debugger lo revela igual. La ofuscación de strings retrasa el análisis estático, pero no detiene el análisis dinámico.

**macOS/ARM64** (si alguien del equipo usa Apple Silicon): registro de retorno es `x0` en vez de `rax`; con LLDB los comandos análogos son `breakpoint set --name strcmp`, `register read`, `thread return -x 0`.

## 5) Preguntas de análisis (enunciado, página final)

1. **¿Qué formato de archivo binario es?** ELF de 64 bits (Linux), arquitectura x86-64 — se determina con `file`.
2. **¿Qué funciones del sistema operativo parece usar?** Solo funciones estándar de libc (`printf`, `__isoc99_scanf`, `strcmp`, `puts`) — no hay llamadas directas al kernel más allá de la carga dinámica normal de un binario ELF. Es intencional: son binarios didácticos mínimos, no hacen syscalls "interesantes" como malware real.
3. **¿Encontraron mensajes o URLs ocultas?** No hay URLs (son binarios sin red). Sí hay mensajes y — en `safecheck` — la clave completa en texto plano; en `obfcheck` solo la versión ofuscada.
4. **¿Por qué estas cadenas pueden ser útiles para identificar malware?** Porque revelan intención y lógica interna sin tener que ejecutar el binario ni tener el código fuente: URLs/IPs delatan infraestructura de C2, nombres de funciones de Windows (`WinExec`, `CreateProcess`) delatan capacidad de ejecutar código o inyectar procesos, y mensajes de error/rutas de archivo a veces filtran el entorno de desarrollo del autor. Es la técnica de triage más barata antes de pasar a desensamblado o debugging.

## 6) Cierre ético (para el guion del video)

Cerrar el video retomando el punto del enunciado: este laboratorio combina análisis estático y dinámico sobre binarios creados a propósito con fines educativos; las mismas técnicas se usan en la vida real para **defensa, auditoría y aprendizaje** — nunca para aplicar ingeniería inversa a software propietario sin permiso.

## Checklist antes de grabar

- [ ] Compilar los 3 binarios y confirmar que corren igual que acá descrito.
- [ ] Correr y anotar el hash real de `sha256sum bin/safecheck` (va a diferir del de un compañero si usan versiones de gcc distintas — mencionarlo si pasa).
- [ ] Tener Ghidra ya importado y analizado *antes* de empezar a grabar (el análisis inicial puede tardar y no aporta al video).
- [ ] Decidir quién narra cada parte (A/B/C) para que todos participen con cámara encendida.
- [ ] Si cambiaron algo del entorno (WSL en vez de VM, Ghidra en Windows apuntando a un binario de WSL, etc.), decirlo explícitamente en el video — el enunciado lo pide.
