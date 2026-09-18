---
curso: Seguridad
tema: Ingeniería inversa para análisis de software (Tema 3 del programa)
fecha: 2026-09-21
tipo: apunte
fuente: _fuentes/Seguridad_ingenieria-inversa-analisis-software_2026-09-15.pdf
tags: [ingenieria-inversa, reversing, analisis-estatico, analisis-dinamico, desensamblado, decompilado, malware, ghidra, gdb]
---

# Ingeniería inversa para análisis de software

Clase asincrónica del 2026-09-21 (contenido subido al inbox el 2026-09-15). Corresponde al punto 3 del programa oficial: [[Cursos/Seguridad/temario|"Ingeniería inversa para análisis de software"]].

Ver también: [[Cursos/Seguridad/entregas]] · [[Cursos/Seguridad/apuntes/lab-ingenieria-inversa-instrucciones|Lab GRUPAL — Ingeniería Inversa (instrucciones)]] · [[Cursos/Seguridad/entregables/lab-ingenieria-inversa|Entregable — walkthrough del lab]] · [[Cursos/Seguridad/entregables/reversing_lab/README|kit de archivos del lab]]

## ¿Qué es la Ingeniería Inversa?

Proceso de desensamblar, descompilar o analizar un software **sin acceso al código fuente**.

**Objetivos:** comprender el funcionamiento interno · identificar vulnerabilidades y malware · verificar cumplimiento de estándares/licencias · recuperar conocimiento perdido (ej. analizar un ejecutable sin documentación).

**Ingeniería directa vs. inversa:** directa va del diseño a la implementación; inversa va de la implementación hacia el entendimiento del diseño.

## Los 3 enfoques

| Enfoque | Qué hace | Ejemplo |
|---|---|---|
| **Estático** | Examina el binario/código sin ejecutarlo | Desensamblado, análisis de cadenas, firmas |
| **Dinámico** | Estudia el comportamiento durante la ejecución | Debugging, monitoreo de API, sandboxing |
| **Híbrido** | Combina ambos para un análisis más completo | — |

## Historia y evolución

Años 80: análisis de virus en MS-DOS → Años 90: auge de cracking y piratería → Actualidad: investigación avanzada de malware y seguridad.

## Importancia en seguridad del software

Base para análisis de malware · permite auditar software sin código fuente · soporte en peritajes digitales · contribuye al desarrollo de defensas más efectivas.

## Casos de uso reales

- **Seguridad informática:** análisis de malware, exploits y rootkits.
- **Forense digital:** recuperación de funciones dañadas.
- **Auditoría de software:** cumplimiento de licencias.
- **Compatibilidad:** adaptar sistemas heredados sin documentación.

## Desafíos y ética

**Desafíos técnicos:** ofuscación, anti-debugging, packers; alta curva de aprendizaje.
**Ética y legalidad:** puede estar restringida por licencias y leyes; en seguridad se aplica bajo **consentimiento** y con fines educativos o defensivos.

## Herramientas clave

| | Estático | Dinámico |
|---|---|---|
| Desensambladores/decompiladores | IDA Pro, Ghidra | — |
| Frameworks | Radare2, Binwalk | — |
| Debuggers | — | OllyDbg, x64dbg |
| Instrumentación en runtime | — | Frida, Pin Tool |
| Entorno aislado | — | Cuckoo Sandbox |

## Métodos de reversión (nivel de automatización)

**Manual** (desensambladores/debuggers, control total pero lento, requiere experiencia) → **Semi-automática** (Ghidra/IDA Pro con vistas gráficas, balance detalle/productividad) → **Automática** (sandboxes y sistemas de análisis de malware, ideal para triage inicial pero menos preciso).

## Desensamblado vs. decompilado

- **Desensamblado:** traduce el binario a lenguaje ensamblador (bajo nivel, más preciso). Herramientas: IDA Pro, Radare2, Hopper. Permite ver flujo de ejecución, llamadas a funciones/APIs, manipulación de memoria y registros. Uso típico: comprender rutinas críticas, detectar instrucciones maliciosas.
- **Decompilado:** reconstruye un pseudo-código de alto nivel (C, Java, etc.) — más legible, pero no siempre perfecto (la optimización del compilador y la ofuscación pueden hacer que pierda estructura original). Herramientas: Ghidra, JADX (Android), RetDec.

## Flujo de trabajo típico

1. Recolección de información (hash, strings, dependencias).
2. Análisis estático inicial (estructura, secciones, funciones).
3. Ejecución controlada (debugging/sandboxing).
4. Documentación y diagramado del comportamiento.
5. Identificación de vulnerabilidades, backdoors o lógica crítica.

## 5 ejemplos de análisis binario (con uso en seguridad)

1. **Cabeceras y metadatos** — editor hexadecimal (HxD, Hex Fiend, Bless) sobre cabecera PE (Windows)/ELF (Linux): dirección de entrada, secciones (text/data/rsrc), tamaño y alineación. Revela si un malware está empaquetado o tiene secciones inusuales.
2. **Extracción de cadenas (`strings`)** — URLs sospechosas, IPs, nombres de funciones/librerías; identifica rápido llamadas críticas (`CreateProcess`, `WinExec`, `socket`).
3. **Desensamblado básico** (IDA Pro/Ghidra) — instrucciones ASM, saltos condicionales (`jmp`, `call`), funciones importadas del SO (`OpenFile`, `WriteProcessMemory`); detecta rutinas maliciosas como keyloggers o exploits.
4. **Comparación de binarios** (BinDiff) — diferencias entre versiones de un programa, útil para ver qué cambió un parche; localiza vulnerabilidades corregidas o backdoors nuevos.
5. **Detección de empaquetadores/ofuscadores** (PEiD, Detect It Easy) — si el binario fue comprimido con UPX/Themida; sospecha de malware que esconde su código.

**El análisis binario se usa para:** revisar malware sin código fuente, auditar software propietario (puertas traseras), comparar parches (qué vulnerabilidades corrigen), validar integridad (detectar alteraciones maliciosas).

## Otros tipos de análisis (más allá del binario)

- **Con código fuente:** solo posible cuando está disponible; permite validar seguridad con mayor precisión.
- **Basado en comportamiento:** observar la interacción del software con el sistema; ideal para detectar malware.
- **Comparación de enfoques:** binario = precisión técnica · comportamiento = visión práctica · código fuente = mayor detalle pero menos frecuente.

## Patrones comunes en binarios maliciosos

Ofuscación de strings · rutinas de cifrado · llamadas sospechosas al sistema.

## Análisis estático vs. dinámico (resumen técnico)

| | Análisis estático | Análisis dinámico |
|---|---|---|
| Qué hace | Estudiar el software sin ejecutarlo | Observar el software en ejecución |
| Para qué | Identificar funciones, librerías, patrones | Monitoreo de procesos y red |
| Técnicas | Firmas de malware, árbol de llamadas, flujo de datos | Sandboxing, debuggers en tiempo real, monitoreo de llamadas al sistema |
| Herramientas | Ghidra, ClamAV (firmas), Checkmarx/SonarQube | Cuckoo Sandbox, Wireshark, Process Monitor |

**Inspección manual** (revisión directa del código desensamblado, requiere alta experiencia) y **automatización parcial** (scripts/plugins para acelerar procesos, apoyo en detección de patrones) son complementarias — los **métodos híbridos** (combinación manual + automático) se usan en investigaciones complejas. Ventaja general: descubrimiento profundo de amenazas. Limitación: requiere tiempo y experiencia.

## Analogías usadas en clase (videos de objetos "misteriosos")

La profesora usó 3 videos de objetos físicos sin explicación visible de su mecanismo interno, para ilustrar la lógica de la ingeniería inversa sobre software sin código fuente:

1. **Lata/juguete que muge** al voltearse — análogo a un software que produce una salida reconocible con mecanismo interno opaco.
2. **Tubo que gime** al girarlo (mecanismo vibratorio interno) — análogo al comportamiento observable sin acceso al diseño interno (análisis dinámico).
3. **Rattleback** (gira, se detiene y gira en sentido contrario solo) — análogo a comportamiento "contraintuitivo" que revela cómo asimetrías internas generan efectos inesperados, como ciertos tipos de ofuscación en software.

**Reflexión de cierre:** la "caja misteriosa" = software binario sin código fuente; los comportamientos contraintuitivos (como la rattleback) = lógica oculta o patrones no obvios en malware.

## Recurso adicional (opcional, no evaluado)

Webinar de Corellium sobre ingeniería inversa en apps móviles (iOS/Android), técnicas estática/dinámica con Frida: https://www.corellium.com/reverse-engineering-webinar
