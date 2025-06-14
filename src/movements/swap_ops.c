/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

void	sa(t_node **a)
{
	if (!a || !*a || !(*a)->next)
		return ;
	swap_nodes(a);
	write(1, "sa\n", 3);
}

void	sb(t_node **b)
{
	if (!b || !*b || !(*b)->next)
		return ;
	swap_nodes(b);
	write(1, "sb\n", 3);
}

void	ss(t_node **a, t_node **b)
{
	int	performed;

	performed = 0;
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
