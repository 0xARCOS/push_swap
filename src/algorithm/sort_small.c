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

/*
** Encuentra la posición (0-indexed) del valor mínimo en el stack
** Propósito: Localizar el elemento más pequeño para moverlo a B
** Relación: Función auxiliar de sort_five()
** Flujo: sort_five() → find_min_pos() → [retorna posición]
** Retorno: Índice del nodo con el valor mínimo
*/
static int	find_min_pos(t_node *stack)
{
	int		pos;
	int		idx;
	int		min;
	t_node		*tmp;

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

/*
** Ordena exactamente 3 elementos con el mínimo de movimientos (máx 2)
** Casos posibles: 6 permutaciones, 5 requieren ordenación
** Estrategia: Identifica el caso y aplica la secuencia óptima
** Relación: Llamada por sort_stack() (size==3) y sort_five() (al final)
** Flujo: sort_stack()/sort_five() → sort_three()
** Movimientos por caso:
**   [1,3,2]: sa
**   [2,1,3]: sa
**   [2,3,1]: rra
**   [3,1,2]: ra
**   [3,2,1]: sa + rra
*/
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

/*
** OPTIMIZED: Ordena stacks de 4-5 elementos
** Estrategia: Mover los 2 más pequeños a B, ordenar los 3 restantes, devolver
** OPTIMIZACIÓN: Guardar stack_size en variable (evita recálculos en bucles)
** Relación: Llamada por sort_stack() cuando size <= 5 && size > 3
** Flujo: sort_stack() → sort_five() → find_min_pos() + sort_three()
** Complejidad: Máximo 12 movimientos para 5 elementos
*/
void	sort_five(t_node **a, t_node **b)
{
	int		pos;
	int		size;

	while (stack_size(*a) > 3)
	{
		size = stack_size(*a);
		pos = find_min_pos(*a);
		if (pos <= size / 2)
			while (pos-- > 0)
				ra(a);
		else
			while (pos++ < size)
				rra(a);
		pb(a, b);
	}
	sort_three(a);
	while (*b)
		pa(a, b);
}
