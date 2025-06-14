/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

void	pa(t_node **a, t_node **b)
{
	if (!b || !*b)
		return ;
	push_node(a, b);
	write(1, "pa\n", 3);
}

void	pb(t_node **a, t_node **b)
{
	if (!a || !*a)
		return ;
	push_node(b, a);
	write(1, "pb\n", 3);
}
