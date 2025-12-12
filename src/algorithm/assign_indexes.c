/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_indexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

/*
** Convierte la lista enlazada (stack) en un array de enteros
** Propósito: Facilita la ordenación de valores para asignar índices
** Relación: Llamada por assign_indexes() antes de ordenar
** Flujo: assign_indexes() → stack_to_array() → [retorna array]
** Retorno: Array dinámico con los valores del stack (NULL si falla malloc)
*/
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

/*
** OPTIMIZED: Selection Sort algorithm (más eficiente que Bubble Sort)
** Encuentra el mínimo en cada iteración y lo coloca en su posición correcta
** Complejidad: O(n²) pero con menos intercambios que Bubble Sort
** Relación: Usado por assign_indexes() para ordenar el array temporal
** Flujo: assign_indexes() → stack_to_array() → sort_array() → set_indexes()
*/
static void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	min_idx;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		min_idx = i;
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
			j++;
		}
		if (min_idx != i)
		{
			tmp = arr[i];
			arr[i] = arr[min_idx];
			arr[min_idx] = tmp;
		}
		i++;
	}
}

/*
** Asigna a cada nodo del stack su índice correspondiente
** El índice representa la posición del valor en el array ordenado
** Ejemplo: valores [5, 2, 8] → índices [1, 0, 2]
** Relación: Llamada por assign_indexes() después de ordenar el array
** Flujo: assign_indexes() → sort_array() → set_indexes()
** Propósito: Permite algoritmos basados en índices (chunk_sort, radix, etc)
*/
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

/*
** FUNCIÓN PRINCIPAL: Normaliza los valores del stack a índices 0..n-1
** Proceso de 3 pasos:
**   1. Convierte stack a array (stack_to_array)
**   2. Ordena el array (sort_array - OPTIMIZADO con Selection Sort)
**   3. Asigna índices basados en el array ordenado (set_indexes)
** Llamada por: sort_stack() antes de chunk_sort() para stacks grandes
** Propósito: Normalización permite algoritmos eficientes independientes del valor
** Ejemplo: [42, -5, 100] se convierte en índices [1, 0, 2]
*/
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
