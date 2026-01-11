/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_indexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static int	*stack_to_array(t_node *stack, int size)
{
	int		*arr;
	int		i;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (stack)
	{
		arr[i++] = stack->value;
		stack = stack->next;
	}
	return (arr);
}

static void	swap_elements(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap_elements(&arr[i], &arr[j]);
		}
		j++;
	}
	swap_elements(&arr[i + 1], &arr[high]);
	return (i + 1);
}

static void	quicksort(int *arr, int low, int high)
{
	int	pivot_idx;

	if (low < high)
	{
		pivot_idx = partition(arr, low, high);
		quicksort(arr, low, pivot_idx - 1);
		quicksort(arr, pivot_idx + 1, high);
	}
}

static void	sort_array(int *arr, int size)
{
	if (size > 1)
		quicksort(arr, 0, size - 1);
}

static void	set_indexes(t_node *stack, int *arr, int size)
{
	int	i;

	while (stack)
	{
		i = 0;
		while (i < size && arr[i] != stack->value)
			i++;
		stack->index = i;
		stack = stack->next;
	}
}

void	assign_indexes(t_node *stack)
{
	int		size;
	int		*arr;

	size = stack_size(stack);
	arr = stack_to_array(stack, size);
	if (!arr)
		return ;
	sort_array(arr, size);
	set_indexes(stack, arr, size);
	free(arr);
}
