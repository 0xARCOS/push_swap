/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

/*
** Verifica si el stack está ordenado en orden ascendente
** Complejidad: O(n) en peor caso, O(1) mejor caso
** Relación: Llamada por main() antes de sort_stack()
** Propósito: Optimización - evitar ordenar si ya está ordenado
** Retorno: 1 si está ordenado, 0 si no lo está
*/
int	is_sorted(t_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

/*
** FUNCIÓN PRINCIPAL DE ORDENAMIENTO: Selecciona el algoritmo según tamaño
** Estrategias por tamaño:
**   - 2 elementos: 1 swap si es necesario
**   - 3 elementos: sort_three() (máx 2 movimientos)
**   - 4-5 elementos: sort_five() (máx 12 movimientos)
**   - 6-100 elementos: chunk_sort con 5 chunks (~600 movs para 100)
**   - 500+ elementos: chunk_sort con 11 chunks (~5500 movs para 500)
** Llamada por: main() si el stack no está ordenado
** Flujo: main() → is_sorted() → sort_stack() → [algoritmo específico]
** Relación: Punto de entrada al sistema de ordenamiento
*/
void	sort_stack(t_node **a, t_node **b)
{
	int		size;

	if (!a || !*a)
		return ;
	size = stack_size(*a);
	if (size == 2)
	{
		if ((*a)->value > (*a)->next->value)
			sa(a);
	}
	else if (size == 3)
		sort_three(a);
	else if (size <= 5)
		sort_five(a, b);
	else
	{
		assign_indexes(*a);
		if (size <= 100)
			chunk_sort(a, b, 5);
		else
			chunk_sort(a, b, 11);
	}
}
