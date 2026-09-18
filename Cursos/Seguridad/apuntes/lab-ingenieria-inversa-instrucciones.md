---
curso: Seguridad
tema: Lab GRUPAL — Ingeniería Inversa (instrucciones)
fecha: 2026-09-21
tipo: apunte
fuente: _fuentes/Seguridad_lab-ingenieria-inversa-instrucciones_2026-09-15.pdf
tags: [ingenieria-inversa, reversing, laboratorio, grupal, ghidra, gdb, strings, objdump]
---

# Lab GRUPAL — Ingeniería inversa (desensamblado, decompilado y debugging)

Instrucciones del profesor para la clase asincrónica del 2026-09-21. Ver también: [[Cursos/Seguridad/apuntes/ingenieria-inversa-analisis-software|Contenido teórico — Ingeniería inversa]] · [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/entregables/lab-ingenieria-inversa|Entregable — walkthrough con resultados y respuestas]] · [[Cursos/Seguridad/entregables/reversing_lab/README|kit de archivos del lab (Makefile, build.sh, src/)]]

**Valor:** 5% · **Modalidad:** GRUPAL
**Entregable:** video con la explicación de los pasos seguidos, donde participen todos los integrantes y la cámara esté encendida mientras ejecutan los pasos del laboratorio. Si deben ajustar alguna instrucción para hacer funcionar el laboratorio, indicarlo en el video.

**Objetivo general:** comprender de forma práctica cómo recuperar la lógica de un programa compilado usando análisis estático (strings, desensamblado, decompilado) y análisis dinámico (debugging).

## 1) Requisitos y entorno seguro

- **Sistema:** Linux (Ubuntu/Kali) recomendado en máquina virtual. También funciona en macOS; en Windows usar **WSL** o **MinGW-w64**.
- **Herramientas:** compilador C (gcc/clang) + terminal · `strings`, `file`, `sha256sum`, `objdump` (o `otool` en macOS) · **Ghidra** (desensamblador/decompilador con GUI) · **GDB** (debugger; en macOS puede usarse **LLDB**).
- **Archivos del laboratorio:** `safecheck.c`, `obfcheck.c`, `Makefile`, `build.sh` (ver [[Cursos/Seguridad/entregables/reversing_lab|kit ya archivado en entregables/reversing_lab]]).

**Ética y legalidad:** este laboratorio usa programas benignos creados para fines educativos. No aplicar ingeniería inversa a software propietario sin permiso.

## 2) Objetivos específicos

1. Reconocer metadatos y cadenas útiles en un binario.
2. Desensamblar y decompilar para ubicar la lógica de validación.
3. Usar el depurador para observar argumentos de funciones en tiempo de ejecución.
4. (Extra) Alterar el flujo en runtime para comprender el impacto de parches/bypasses.

## 3) Preparación

```bash
chmod +x build.sh
./build.sh
```

Esto crea `bin/safecheck`, `bin/safecheck_stripped` y `bin/obfcheck`.

Comandos manuales equivalentes:
```bash
gcc -g -O0 src/safecheck.c -o bin/safecheck
cp bin/safecheck bin/safecheck_stripped && strip bin/safecheck_stripped
gcc -g -O0 src/obfcheck.c -o bin/obfcheck
```

## 4) Parte A — Reconocimiento estático rápido (sobre `bin/safecheck`)

1. **Tipo de archivo y arquitectura:** `file bin/safecheck` — identifica formato (ELF/Mach-O/PE), arquitectura (x86_64/ARM) y si es dinámico/estático.
2. **Hash:** `sha256sum bin/safecheck` — para integridad y referenciar la muestra.
3. **Cadenas visibles:** `strings -n 4 bin/safecheck | less` — buscar "Ingrese la clave", "Acceso concedido". Conclusión: a veces ya hay pistas sin ejecutar el binario.
4. **Símbolos/secciones (si no está stripped):** `objdump -t bin/safecheck | head` — si aparece `main`, no está stripped; comparar con `bin/safecheck_stripped`. macOS: `otool -L` (librerías) y `nm` (símbolos).

## 5) Parte B — Desensamblado y decompilado con Ghidra

1. Abrir proyecto: File → New Project → Non-Shared Project.
2. File → Import File… → seleccionar `bin/safecheck` → OK.
3. Doble clic en el binario → Yes para Analyze → opciones por defecto → Analyze.
4. Symbol Tree → abrir `main`.
5. Vista Decompile (panel derecho): identificar la lógica principal — observar la llamada a `scanf` y la comparación con `strcmp`; debe aparecer una constante clara (ej. "Cyber2025").
6. Etiquetado y notas: renombrar funciones/variables (click derecho → Rename) y añadir comentarios.
7. Graph de funciones: Window → Function Graph.

Repetir con `bin/obfcheck`: aparecerá una función que **de-ofusca** la clave restando 1 a cada carácter antes de comparar.

## 6) Parte C — Debugging (dinámico) con GDB

Objetivo: interceptar la llamada a `strcmp` y observar sus argumentos.

```gdb
gdb -q bin/safecheck
start
break strcmp
continue
x/s $rdi      # primer argumento (RDI) → entrada del usuario
x/s $rsi      # segundo argumento (RSI) → cadena objetivo
finish        # vuelve a la llamada en el caller
set $rax=0    # finge que strcmp devolvió 0 (iguales) — bypass educativo
continue
```

Esperado: se ve el input propio y la clave real en memoria; forzar `$rax=0` modifica el flujo **sin tocar el binario en disco**.

**Tip ARM64/M1:** el registro de retorno es `x0`. **macOS con LLDB:** `breakpoint set --name strcmp`, `register read`, `thread return -x 0`.

## 7) Cierre y recordatorio ético

Este laboratorio demuestra cómo combinar análisis estático y dinámico para comprender la lógica de un binario. Úsalo para **defensa, auditoría y aprendizaje**, respetando licencias y marco legal vigente.
