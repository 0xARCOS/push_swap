/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Calcula el número de elementos en el stack
** Complejidad: O(n) - recorre toda la lista
** Relación: Función de utilidad usada por múltiples algoritmos
** Usado por: sort_stack(), sort_five(), chunk_sort(), etc.
** Nota: Cachear el resultado si se usa varias veces en un bucle
** Retorno: Número de nodos en el stack
*/
int	stack_size(t_node *stack)
{
	int		size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}
