# Prompt — verificación y cierre del lab con IA

Para pegar en Claude Code (u otra IA con acceso a archivos/terminal) parado
dentro de esta carpeta (`reversing_lab/`), en la máquina con Ubuntu/WSL ya
lista.

```
Estoy en el repo del lab de ingeniería inversa del curso de Seguridad, carpeta
Cursos/Seguridad/entregables/reversing_lab. Necesito que:

1. Compiles el lab: chmod +x build.sh && ./build.sh (genera bin/safecheck,
   bin/safecheck_stripped, bin/obfcheck).
2. Corras y capturés la salida REAL (no la del walkthrough, que son valores
   de ejemplo) de:
   - file bin/safecheck
   - sha256sum bin/safecheck
   - strings -n 4 bin/safecheck | grep -A2 -B2 clave
   - strings -n 4 bin/obfcheck | grep -A2 -B2 clave
   - objdump -t bin/safecheck | head -20
   - objdump -t bin/safecheck_stripped | head -5
3. Confirmes en GDB la secuencia de Parte C sobre bin/safecheck y luego sobre
   bin/obfcheck: start, break strcmp, continue, x/s $rdi, x/s $rsi, finish,
   set $rax=0, continue — y me digas si el comportamiento coincide con lo
   descrito en Cursos/Seguridad/entregables/lab-ingenieria-inversa.md
   (sección "Parte C").
4. Me digas si tuviste que ajustar algo del entorno respecto a lo que dice
   la sección "0) Entorno" de ese mismo archivo (versión de gcc, distro,
   Ghidra en Windows vs WSL, etc.) — el enunciado pide mencionar esto en el
   video si aplica.
5. Con todos esos valores reales, actualizame
   Cursos/Seguridad/entregables/lab-ingenieria-inversa.md:
   - reemplazá los valores de ejemplo (hash, líneas de objdump) por los
     reales donde el documento dice "esperado" / "el patrón, no el hash
     literal"
   - marcá el checklist final de la sección "Checklist antes de grabar"
   - cambiá el frontmatter estado: borrador a estado: confirmado
   No cambies la explicación conceptual si ya coincide con lo que viste
   correr — solo confirmá/corregí los valores concretos y el estado.
```
