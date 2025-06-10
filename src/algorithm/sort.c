#include "push_swap.h"

int is_sorted(t_node *stack)
{
    while (stack && stack->next)
    {
        if (stack->value > stack->next->value)
            return 0;
        stack = stack->next;
    }
    return 1;
}

void sort_stack(t_node **a, t_node **b)
{
    int size;

    if (!a || !*a)
        return;
    size = stack_size(*a);
    if (size == 2)
    {
        if ((*a)->value > (*a)->next->value)
            sa(a);
    }
    else if (size == 3)
        sort_three(a);
    else if (size <= 5)
        sort_five(a, b);
    else
    {
        assign_indexes(*a);
        if (size <= 100)
            chunk_sort(a, b, 5);
        else
            chunk_sort(a, b, 11);
    }
}
