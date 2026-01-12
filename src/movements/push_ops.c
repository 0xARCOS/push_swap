/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariarcos <ariarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:10:14 by ariarcos          #+#    #+#             */
/*   Updated: 2026/01/11 21:10:16 by ariarcos         ###   ########.fr       */
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
