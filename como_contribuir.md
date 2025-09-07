# Cómo Contribuir

## 1. Haz un fork del Repositorio Principal

1. Haz click en el botón **"Fork"** (esquina superior derecha)
2. Selecciona tu cuenta para crear la copia

## 2. Clonar Tu Fork

```bash
# Clona el fork
git clone https://github.com/TU_USUARIO/nombre-proyecto.git

# Entrar al directorio
cd PAC-Tarea-1

# Agregar el repositorio original como "upstream"
git remote add upstream https://github.com/USUARIO_ORIGINAL/PAC-Tarea-1.git
```

## 3. Sincronizar con el Repositorio Principal

```bash
# Descargar los cambios del repositorio original
git fetch upstream

# Cambiar a la rama principal
git checkout main

# Fusionar cambios del upstream
git merge upstream/main
```

## 4. Crear una rama para el pull request

```bash
# Crear y cambiar a nueva rama
git checkout -b feature/nueva-funcionalidad
```

**Sugerencias para los nombres de las ramas**

- `feature/nombre-funcionalidad`: Nuevas características
- `bugfix/descripcion-bug`: Corrección de errores
- `refactor/mejora-codigo`: Refactorización

> No tengo ninguna preferencia por el nommbre así que le pueden poner lo que quieran

## 5. Desarrollar y Hacer Commits

```bash
# Ver estado de archivos
git status

# Agregar archivos específicos
git add x y z

# O agregar todos los cambios
git add .

# Hacer commit con mensaje descriptivo
git commit -m "Agregar función para identificar el OS"
```

## 6. Subir Cambios a tu Fork

```bash
# Subir tu rama al fork
git push origin feature/nueva-funcionalidad
```

## 7. Crear Pull Request

1. Ve a **tu fork** en GitHub
2. Haz click en **Compare & pull request**
3. Idealmente pon un título y descripción
4. Haz click en **"Create pull request"**

## 8. Esto no es tan serio para hacer code reviews

Si por alguna razón hay que hacer cambios:

```bash
# Hacer cambios
# Commitear los cambios
git add .
git commit -m "fix: corregir validación de dimensiones matrices"

# Subir actualizaciones
git push origin feature/nueva-funcionalidad
```

El pull request se actualiza automáticamente.

## 9. Después de que el pull request se acepte

```bash
# Cambiar a main
git checkout main

# Actualizar desde upstream
git pull upstream main

# Subir cambios a tu fork
git push origin main

# Borrar rama local (opcional)
git branch -d feature/nueva-funcionalidad

# Borrar rama remota (opcional)
git push origin --delete feature/nueva-funcionalidad
```

## Tips Importantes

- **Siempre** crear rama nueva para cada contribución
- **Nunca** trabajar directamente en `main`
- Hacer commits pequeños y frecuentes
- Probar tu código antes del pull request
- Mantener el fork sincronizado
