#include "push_swap.h"
#include <unistd.h>

void sa(t_node **a) // swap a
{
    if (!a || !*a || !(*a)->next)
        return;
    swap_nodes(a);
    write(1, "sa\n", 3);
}

void sb(t_node **b) // swap b
{
    if (!b || !*b || !(*b)->next)
        return;
    swap_nodes(b);
    write(1, "sb\n", 3);
}

void ss(t_node **a, t_node **b) // swap a y b
{
    int performed = 0;

    if (a && *a && (*a)->next)
    {
        swap_nodes(a);
        performed = 1;
    }
    if (b && *b && (*b)->next)
    {
        swap_nodes(b);
        performed = 1;
    }
    if (performed)
        write(1, "ss\n", 3);
}

void pa(t_node **a, t_node **b) // push a (b → a)
{
    if (!b || !*b)
        return;
    push_node(a, b);
    write(1, "pa\n", 3);
}

void pb(t_node **a, t_node **b) // push b (a → b)
{
    if (!a || !*a)
        return;
    push_node(b, a);
    write(1, "pb\n", 3);
}

void ra(t_node **a) // rotate a
{
    if (!a || !*a || !(*a)->next)
        return;
    rotate_nodes(a);
    write(1, "ra\n", 3);
}

void rb(t_node **b) // rotate b
{
    if (!b || !*b || !(*b)->next)
        return;
    rotate_nodes(b);
    write(1, "rb\n", 3);
}

void rr (t_node **a, t_node **b) //rotate a y b
{
    int performed = 0;

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

void rra(t_node **a) // reverse rotate a
{
    if (!a || !*a || !(*a)->next)
        return;
    reverse_rotate_nodes(a);
    write(1, "rra\n", 4);
}

void rrb(t_node **b) // reverse rotate b
{
    if (!b || !*b || !(*b)->next)
        return;
    reverse_rotate_nodes(b);
    write(1, "rrb\n", 4);
}

void rrr(t_node **a, t_node **b) // reverse rotate a y b
{
    int performed = 0;

    if (a && *a && (*a)->next)
    {
        reverse_rotate_nodes(a);
        performed = 1;
    }
    if (b && *b && (*b)->next)
    {
        reverse_rotate_nodes(b);
        performed = 1;
    }
    if (performed)
        write(1, "rrr\n", 4);
}