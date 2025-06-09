# push_swap

¿En qué consiste el proyecto?
Tendrás que crear un programa llamado push_swap que, dado una lista de números enteros, genera una secuencia 
se instrucciones para ordenarlos usando dos pilas (stack A y B) y un conjunto limitado de operaciones. 

REGLAS DEL JUEGO
Debes implementar dos programas:
1. push_swap: genera la secuencia de operaciones para ordenar.
2. checker (opcional, pero recomendado): verifica si una secuencia de operacione realmente ordena datos.

REGLAS DE ORDENACIÓN
Debes usar estas operaciones, cada una aplicada sobre la pila:
 - sa / sb / ss : swap el primer par de elementos de A/B o ambos.
 - pa / pb : push desde B a A o A a B.
 - ra / rb / rr : rotate la pila A/B o ambas (primer elemento al final)
 - rra / rrb / rrr : reverse rotate (último elemento al frente)

OBJETIVO
Ordenar la pila A con el menor número posible de operaciones, dejando B vacía. Esto se evaluará con test
automáticos y limitaciones de movimientos para distintos rangos de números (3, 5, 100, 500...).

REQUISITOS TÉCNICOS
- No puedes usar ninguna función de la libc exepto write, malloc y free.
- No puedes usar funciones como printf, atoi, etc. Tendrás que implementarlas tú.
- No leaks: todo debe estar liberado correctamente.

ESTRUCTURA DEL PROYECTO

push_swap/
├── Makefile
├── src/
│   ├── main.c
│   ├── checker_main.c
│   ├── parse/
│   │   └── parser.c
│   ├── movements/
│   │   └── operations.c
│   └── algorithm/
│       └── sort.c
└── include/
    └── push_swap.h


ESTRATEGIAS
- Para 3 números: pocos casos, puedo harcodear.
- Para 5 números: usa el más pequeño, pásalo a B, ordena los 3, vuelve a A.
- Para muchos números: adapta un algoritmo como RADIX SORT, usando el índice de cada número en la lista
ordenada (normalización).


## Compilación y uso
Para compilar los binarios ejecuta:
```bash
make
```
Esto generará dos programas: `push_swap` y `checker`. Si deseas recompilar desde cero utiliza `make re`.

Para ordenar una lista simplemente ejecuta `push_swap` seguido de los números:
```bash
./push_swap 3 2 1
```
Este comando mostrará una secuencia de operaciones por la salida estándar.

## Pruebas de ejemplo
A continuacion se muestran algunos comandos que puedes lanzar para verificar tu programa:

1. **Entrada simple**:
   ```bash
   ./push_swap 2 1 3
   ```
   Deberia imprimir una secuencia de operaciones que ordene `2 1 3`.

2. **Argumento unico con espacios**:
   ```bash
   ./push_swap "3 2 1"
   ```
   Comprueba que el parser maneje los espacios correctamente.

3. **Numeros repetidos**:
   ```bash
   ./push_swap 1 1
   ```
   Debe mostrar `Error` porque no se permiten duplicados.

4. **Valores no numericos**:
   ```bash
   ./push_swap 4 a 2
   ```
   Tambien debe imprimir `Error`.

5. **Lista ya ordenada**:
   ```bash
   ./push_swap 1 2 3 4 5
   ```
   El programa no deberia imprimir ninguna operacion.

6. **Prueba aleatoria grande (100 valores)**:
   ```bash
   seq 100 | sort -R | xargs ./push_swap
   ```
   Comprueba que la salida no sea excesiva y el programa termina.

## Verificación con checker
Una vez generada la secuencia de operaciones puedes validarla con `checker`:
```bash
./push_swap 3 1 2 | ./checker 3 1 2
```
Si la secuencia es correcta, se imprimirá `OK`; de lo contrario, `KO`.

También puedes guardar las operaciones en un archivo y pasarlas por entrada estándar:
```bash
./push_swap 3 1 2 > ops.txt
./checker 3 1 2 < ops.txt
```
