---
curso: DesarrolloWeb
tema: Comandos de Git — flujo básico (init, clone, branch, stash, merge)
fecha: 2026-08-12
tipo: apunte
fuente: _fuentes/DesarrolloWeb_comandos-git-basicos_2026-08-12.pptx
tags: [git, comandos, branch, stash, merge, referencia]
---

# Comandos de Git — flujo básico

Ver también: [[Cursos/DesarrolloWeb/temario]] · [[Cursos/DesarrolloWeb/apuntes/gitflow-curso]]

> Referencia de comandos de Git en sí (init, clone, branch, stash, merge). No confundir con [[Cursos/DesarrolloWeb/apuntes/gitflow-curso|gitflow-curso.md]], que documenta el **modelo de ramas que exige el profesor** para el proyecto del curso — esta nota es solo mecánica de comandos, aplicable a cualquier repo.

## 1. Inicializar un proyecto nuevo

```bash
cd "ruta/del/proyecto"
git init
# revisar/crear .gitignore (al menos node_modules/, .env, dist/, build/)
git add .
git status                          # verificar qué quedó en staging
git commit -m "Primer commit"
git branch -M main
git remote add origin https://github.com/usuario/repo.git
git remote -v                       # verificar conexión
git push -u origin main
```

## 2. Clonar un proyecto existente

```bash
cd "ruta/donde/descargar"
git clone https://github.com/usuario/repo.git
cd repo
git branch                          # confirma en qué rama quedaste (ej. * main)
git remote -v                       # git clone ya configura origin automáticamente
```

## 3. Trabajar con ramas

```bash
git branch                          # listar ramas locales (* = rama actual)
git branch -a                       # incluir ramas remotas
git branch login                    # crear rama sin cambiarse
git switch login                    # cambiarse a una rama existente
git switch -c login                 # crear y cambiarse en un solo paso (reemplaza a `git checkout -b`)
```

**Flujo recomendado para empezar una funcionalidad:**

```bash
git switch main
git pull origin main                # main actualizado antes de ramificar
git switch -c feature/login
# ... trabajo normal ...
git status
git add .
git commit -m "Implementar pantalla de login"
git push -u origin feature/login    # -u solo la primera vez; después alcanza con `git push`
```

## 4. Cambiar de rama con cambios sin commitear

```bash
git status
git stash push -m "Login todavía incompleto"   # guarda los cambios temporalmente
git switch main                                 # directorio queda limpio
git switch feature/login                        # al volver...
git stash pop                                   # ...recupera los cambios
git stash list                                  # se pueden acumular varios stash
```

Para **descartar** cambios en vez de guardarlos (irreversible):

```bash
git restore src/App.jsx             # un archivo puntual
git restore .                       # todos los archivos modificados — cuidado, no se puede deshacer
```

## 5. Traer una rama remota que no existe localmente

```bash
git fetch
git branch -a                       # aparece como remotes/origin/feature/login
git switch feature/login            # Git moderno detecta el remoto y crea la rama local automáticamente
# forma explícita:
git switch -c feature/login --track origin/feature/login
```

## 6. Eliminar una rama

```bash
git switch main                     # hay que salir de la rama antes de borrarla
git branch -d feature/login         # local
git push origin --delete feature/login   # también en GitHub
```

## 7. Traer cambios nuevos de main hacia mi rama

```bash
git add .
git commit -m "Avance login"
git switch main
git pull origin main
git switch feature/login
git merge main
```

Si hay conflictos, Git marca el archivo con `CONFLICT (content): Merge conflict in ...`; hay que resolver el contenido a mano, quitar las marcas de conflicto, y luego:

```bash
git add .
git commit -m "Resolver conflictos con main"
```

## 8. Las tres reglas para evitar problemas

1. Antes de cambiar de rama: `git status`. Si hay cambios importantes, hacer `commit` o `stash` primero.
2. Antes de crear una rama nueva: actualizar main con `git pull origin main`.
3. **Commit no es lo mismo que subir a GitHub** — `commit` guarda localmente, `push` envía esos commits al repositorio remoto.
