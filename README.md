# push_swap

¿En qué consiste el proyecto?
Tendrás que crear un programa llamado push_swap que, dado una lista de números enteros, genera una secuencia 
se instrucciones para ordenarlos usando dos pilas (stack A y B) y un conjunto limitado de operaciones. 

REGLAS DEL JUEGO
Debes implementar dos programas:
1. push_swap: genera la secuencia de operaciones para ordenar.
2. cheker (opcional, pero recomendado): verifica si una secuencia de operacione realmente ordena datos.

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
│   ├── parser.c
│   ├── operations.c
│   ├── sort_small.c
│   └── sort_large.c
└── include/
    └── push_swap.h


ESTRATEGIAS
- Para 3 números: pocos casos, puedo harcodear.
- Para 5 números: usa el más pequeño, pásalo a B, ordena los 3, vuelve a A.
- Para muchos números: adapta un algoritmo como RADIX SORT, usando el índice de cada número en la lista
ordenada (normalización).
