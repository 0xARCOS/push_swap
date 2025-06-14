/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_ops.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

void	rra(t_node **a)
{
	if (!a || !*a || !(*a)->next)
		return ;
	reverse_rotate_nodes(a);
	write(1, "rra\n", 4);
}

void	rrb(t_node **b)
{
	if (!b || !*b || !(*b)->next)
		return ;
	reverse_rotate_nodes(b);
	write(1, "rrb\n", 4);
}

void	rrr(t_node **a, t_node **b)
{
	int	performed;

	performed = 0;
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
