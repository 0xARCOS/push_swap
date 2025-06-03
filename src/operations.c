#include "push_swap.h"

void sa(t_node **a) // swap a
{
    t_node *first;
    t_node *second;
    if (!a || !*a || !(*a)->next)
        return;
    first = *a;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *a = second;
}

void sb(t_node **b) // swap b
{
    sa(b);
}

void ss(t_node **a, t_node **b) // swap a y b
{
    sa(a);
    sa(b);
}

void pa(t_node **a, t_node **b) // push a (b → a)
{
    t_node *tmp;
    if (!b || !*b)
        return;
    tmp = *b;
    *b = (*b)->next;
    tmp->next = *a;
    *a = tmp;
}

void pb(t_node **a, t_node **b) // push b (a → b)
{
    pa(b, a);
}

void ra(t_node **a) // rotate a
{
    t_node *first;
    t_node *last;
    if (!a || !*a || !(*a)->next)
        return;
    first = *a;
    *a = first->next;
    last = *a;
    while (last->next)
        last = last->next;
    last->next = first;
    first->next = NULL; 
}

void rb(t_node **b) // rotate b
{
    ra(b);
}

void rr (t_node **a, t_node **b) //rotate a y b
{
    ra(a);
    ra(b);
}

void rra(t_node **a) // reverse rotate a
{
    t_node *prev;
    t_node *last;
    if (!a || !*a || !(*a)->next)
        return;
    prev = NULL;
    last = *a;
    while (last->next)
    {
        prev = last;
        last = last->next;
    }
    prev->next = NULL;
    last->next = *a;
    *a = last;
}

void rrb(t_node **b) // reverse rotate b
{
    rra(b);
}

void rrr(t_node **a, t_node **b) // reverse rotate a y b
{
    rra(a);
    rrb(b);
}