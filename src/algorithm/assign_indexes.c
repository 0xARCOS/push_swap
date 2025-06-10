#include "push_swap.h"

void assign_indexes(t_node *stack)
{
    int     size;
    int     *arr;
    int     i;
    int     j;
    t_node  *tmp;

    size = stack_size(stack);
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
