#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    t_node *stack = parse_input(argc, argv);
    if (!stack)
    {
        printf("ERROR\n");
        return 1;
    }
    printf("OK\n");
    free_stack(&stack);
    return 0;
}
