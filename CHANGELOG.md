# Historial de Cambios

Este archivo resume las principales tareas realizadas en el proyecto **push_swap**.

## Inicialización del repositorio
- Se añadió una estructura básica con directorios `src/`, `include/` y `tests/` junto con un `Makefile` para compilar el proyecto.
- Se incluyó un entorno de desarrollo en `.vscode/` para facilitar la depuración.

## Implementación de la lógica del programa
- Se definió la estructura `t_node` y las funciones de parsing en `parse/` para validar la entrada y construir la pila.
- Se programaron todas las operaciones de la normativa (swap, push, rotate y reverse rotate) en `movements/operations.c`.
- Se añadió el algoritmo principal de ordenación en `algorithm/sort.c`, que contempla casos para listas pequeñas y un enfoque de *radix sort* para volúmenes mayores.

## Utilidades y manejo de memoria
- Se implementaron funciones auxiliares como `ft_split`, `ft_strdup` y versiones seguras de `atoi` y liberación de memoria.
- Se añadieron herramientas para detectar números duplicados y gestionar correctamente la pila.

## Soporte de pruebas y scripts
- Dentro de `tests/` se incluyeron un programa auxiliar en C y un script en Python para comprobar que el parser se ejecuta sin bloqueos e informa de errores correctamente.

## Otros ajustes
- Se creó `.gitignore` para excluir binarios y directorios temporales.
- Se actualizó `README.md` con una explicación del proyecto y ejemplos de uso.

