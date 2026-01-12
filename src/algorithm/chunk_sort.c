/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariarcos <ariarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:09:29 by ariarcos          #+#    #+#             */
/*   Updated: 2026/01/11 21:09:31 by ariarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_pos_by_index(t_node *stack, int index)
{
	int		pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		stack = stack->next;
		pos++;
	}
	return (-1);
}

static int	find_max_index(t_node *stack)
{
	int		max;

	max = stack->index;
	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

static void	push_chunks(t_node **a, t_node **b, int chunk)
{
	int		size;
	int		pushed;
	int		limit;

	size = stack_size(*a);
	pushed = 0;
	limit = chunk;
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

static void	push_back(t_node **a, t_node **b)
{
	int		pos;
	int		max;
	int		size;

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

void	chunk_sort(t_node **a, t_node **b, int chunks)
{
	int		size;
	int		chunk;

	size = stack_size(*a);
	chunk = size / chunks + 1;
	push_chunks(a, b, chunk);
	push_back(a, b);
}
