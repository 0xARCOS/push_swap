/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_indexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariarcos <ariarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:09:20 by ariarcos          #+#    #+#             */
/*   Updated: 2026/01/11 21:09:23 by ariarcos         ###   ########.fr       */
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

static void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
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
