#include "push_swap.h"
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    t_node      *stack_a;
     t_node      *stack_b;
    
    stack_a = NULL;
     stack_b = NULL;

    if (argc < 2)
        return (0); // no hay números a ordenar

    stack_a = parse_input(argc, argv);
    if (!stack_a)
    {
        write(2, "Error\n", 6);
        return 1; // Error de parsing
    }

    // Verificamos si está ordenado
    if (is_sorted(stack_a))
    {
        free_stack(&stack_a);
        return (0); // Nada que hacer
    }

    sort_stack(&stack_a, &stack_b);

    free_stack(&stack_a);
    free_stack(&stack_b);

    return 0;
}