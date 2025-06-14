/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

static int	find_min_pos(t_node *stack)
{
	int		pos;
	int		idx;
	int		min;
	t_node	*tmp;

	pos = 0;
	idx = 0;
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
	return (pos);
}

void	sort_three(t_node **a)
{
	int		first;
	int		second;
	int		third;

	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;
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

void	sort_five(t_node **a, t_node **b)
{
	int		pos;

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
