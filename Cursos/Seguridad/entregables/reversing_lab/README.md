# Reversing Lab – Guía rápida

## Compilar
```bash
chmod +x build.sh
./build.sh
```

## Binarios generados
- `bin/safecheck` (con símbolos)
- `bin/safecheck_stripped` (sin símbolos)
- `bin/obfcheck` (con de-ofuscación simple)

## Pasos recomendados
1) Recon estático: `file`, `sha256sum`, `strings`, `objdump -t`  
2) Ghidra: importar -> analizar -> abrir `main` -> vista decompilada -> localizar `strcmp`.  
3) GDB: `start`, `break strcmp`, `continue`, `x/s $rdi`, `x/s $rsi`, `finish`, `set $rax=0`, `continue`.