#include "push_swap.h"
#include <unistd.h>

void ra(t_node **a)
{
    if (!a || !*a || !(*a)->next)
        return;
    rotate_nodes(a);
    write(1, "ra\n", 3);
}

void rb(t_node **b)
{
    if (!b || !*b || !(*b)->next)
        return;
    rotate_nodes(b);
    write(1, "rb\n", 3);
}

void rr(t_node **a, t_node **b)
{
    int performed;

    performed = 0;
    if (a && *a && (*a)->next)
    {
        rotate_nodes(a);
        performed = 1;
    }
    if (b && *b && (*b)->next)
    {
        rotate_nodes(b);
        performed = 1;
    }
    if (performed)
        write(1, "rr\n", 3);
}
