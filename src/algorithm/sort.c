#include "push_swap.h"

static int stack_size(t_node *stack)
{
    int size = 0;
    while (stack)
    {
        size++;
        stack = stack->next;
    }
    return size;
}

static int find_min_pos(t_node *stack)
{
    int     pos = 0;
    int     idx = 0;
    int     min;
    t_node  *tmp;

    tmp = stack;
    min = tmp->value;
    while (tmp)
    {
        if (tmp->value < min)
        {
            min = tmp->value;
            pos = idx;
        }
        tmp = tmp->next;
        idx++;
    }
    return pos;
}

static void assign_indexes(t_node *stack)
{
    int     size = stack_size(stack);
    int     *arr;
    int     i;
    int     j;
    t_node  *tmp;

    arr = malloc(sizeof(int) * size);
    if (!arr)
        return;
    tmp = stack;
    i = 0;
    while (tmp)
    {
        arr[i++] = tmp->value;
        tmp = tmp->next;
    }
    i = 0;
    while (i < size - 1)
    {
        j = i + 1;
        while (j < size)
        {
            if (arr[i] > arr[j])
            {
                int swap = arr[i];
                arr[i] = arr[j];
                arr[j] = swap;
            }
            j++;
        }
        i++;
    }
    tmp = stack;
    while (tmp)
    {
        i = 0;
        while (i < size)
        {
            if (arr[i] == tmp->value)
            {
                tmp->index = i;
                break;
            }
            i++;
        }
        tmp = tmp->next;
    }
    free(arr);
}

static void sort_three(t_node **a)
{
    int first = (*a)->value;
    int second = (*a)->next->value;
    int third = (*a)->next->next->value;

    if (first > second && second < third && first < third)
        sa(a);
    else if (first > second && second > third)
    {
        sa(a);
        rra(a);
    }
    else if (first > second && second < third && first > third)
        ra(a);
    else if (first < second && second > third && first < third)
    {
        sa(a);
        ra(a);
    }
    else if (first < second && second > third && first > third)
        rra(a);
}

static void sort_five(t_node **a, t_node **b)
{
    int pos;
    while (stack_size(*a) > 3)
    {
        pos = find_min_pos(*a);
        if (pos <= stack_size(*a) / 2)
            while (pos-- > 0)
                ra(a);
        else
            while (pos++ < stack_size(*a))
                rra(a);
        pb(a, b);
    }
    sort_three(a);
    while (*b)
        pa(a, b);
}


static int find_pos_by_index(t_node *stack, int index)
{
    int pos = 0;
    while (stack)
    {
        if (stack->index == index)
            return pos;
        stack = stack->next;
        pos++;
    }
    return -1;
}

static int find_max_index(t_node *stack)
{
    int max = stack->index;
    while (stack)
    {
        if (stack->index > max)
            max = stack->index;
        stack = stack->next;
    }
    return max;
}

static void push_chunks(t_node **a, t_node **b, int chunk)
{
    int size = stack_size(*a);
    int pushed = 0;
    int limit = chunk;

    while (pushed < size)
    {
        if ((*a)->index < limit)
        {
            pb(a, b);
            pushed++;
            if ((*b)->index >= limit - chunk / 2)
                rb(b);
        }
        else
            ra(a);
        if (pushed == limit && limit < size)
            limit += chunk;
    }
}

static void push_back(t_node **a, t_node **b)
{
    int pos;
    int max;
    int size;

    while (*b)
    {
        max = find_max_index(*b);
        pos = find_pos_by_index(*b, max);
        size = stack_size(*b);
        if (pos <= size / 2)
            while (pos-- > 0)
                rb(b);
        else
            while (pos++ < size)
                rrb(b);
        pa(a, b);
    }
}

static void chunk_sort(t_node **a, t_node **b, int chunks)
{
    int size = stack_size(*a);
    int chunk = size / chunks + 1;

    push_chunks(a, b, chunk);
    push_back(a, b);
}

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

