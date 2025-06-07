#include "push_swap.h"
#include <unistd.h>

static void swap_stack(t_node **stack)
{
    t_node *first;
    t_node *second;

    if (!stack || !*stack || !(*stack)->next)
        return;
    first = *stack;
    second = first->next;
    first->next = second->next;
    second->next = first;
    *stack = second;
}

static void push_stack(t_node **to, t_node **from)
{
    t_node *tmp;

    if (!from || !*from)
        return;
    tmp = *from;
    *from = (*from)->next;
    tmp->next = *to;
    *to = tmp;
}

static void rotate_stack(t_node **stack)
{
    t_node *first;
    t_node *last;

    if (!stack || !*stack || !(*stack)->next)
        return;
    first = *stack;
    *stack = first->next;
    last = *stack;
    while (last->next)
        last = last->next;
    last->next = first;
    first->next = NULL;
}

static void reverse_rotate_stack(t_node **stack)
{
    t_node *prev;
    t_node *last;

    if (!stack || !*stack || !(*stack)->next)
        return;
    prev = NULL;
    last = *stack;
    while (last->next)
    {
        prev = last;
        last = last->next;
    }
    prev->next = NULL;
    last->next = *stack;
    *stack = last;
}

void sa(t_node **a) // swap a
{
    swap_stack(a);
    write(1, "sa\n", 3);
}

void sb(t_node **b) // swap b
{
    swap_stack(b);
    write(1, "sb\n", 3);
}

void ss(t_node **a, t_node **b) // swap a y b
{
    swap_stack(a);
    swap_stack(b);
    write(1, "ss\n", 3);
}

void pa(t_node **a, t_node **b) // push a (b → a)
{
    push_stack(a, b);
    write(1, "pa\n", 3);
}

void pb(t_node **a, t_node **b) // push b (a → b)
{
    push_stack(b, a);
    write(1, "pb\n", 3);
}

void ra(t_node **a) // rotate a
{
    rotate_stack(a);
    write(1, "ra\n", 3);
}

void rb(t_node **b) // rotate b
{
    rotate_stack(b);
    write(1, "rb\n", 3);
}

void rr (t_node **a, t_node **b) //rotate a y b
{
    rotate_stack(a);
    rotate_stack(b);
    write(1, "rr\n", 3);
}

void rra(t_node **a) // reverse rotate a
{
    reverse_rotate_stack(a);
    write(1, "rra\n", 4);
}

void rrb(t_node **b) // reverse rotate b
{
    reverse_rotate_stack(b);
    write(1, "rrb\n", 4);
}

void rrr(t_node **a, t_node **b) // reverse rotate a y b
{
    reverse_rotate_stack(a);
    reverse_rotate_stack(b);
    write(1, "rrr\n", 4);
}
