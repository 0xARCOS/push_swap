/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

/*
** Encuentra la posición (0-indexed) de un nodo por su índice normalizado
** Propósito: Localizar el máximo índice en B para push_back()
** Relación: Función auxiliar de push_back()
** Flujo: push_back() → find_max_index() → find_pos_by_index()
** Retorno: Posición del nodo, o -1 si no se encuentra
*/
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

/*
** Encuentra el índice normalizado más alto en el stack
** Propósito: Identificar el siguiente elemento a devolver a A (orden desc)
** Relación: Función auxiliar de push_back()
** Flujo: push_back() → find_max_index() → find_pos_by_index()
** Retorno: Valor del índice máximo en el stack
*/
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

/*
** Fase 1 de chunk_sort: Empuja elementos de A a B por chunks (grupos)
** Estrategia: Dividir los índices en grupos y procesarlos secuencialmente
** Optimización: Elementos de la mitad superior del chunk van al fondo de B (rb)
** Relación: Primera fase de chunk_sort(), llamada antes de push_back()
** Flujo: chunk_sort() → push_chunks() → [mueve todo a B en chunks]
** Parámetros: a (origen), b (destino), chunk (tamaño de cada grupo)
** Ejemplo: [0-19], [20-39], [40-59]... para 100 elementos con 5 chunks
*/
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

/*
** Fase 2 de chunk_sort: Devuelve elementos de B a A en orden descendente
** Estrategia: Siempre buscar el máximo índice en B y moverlo a A
** Optimización: Usa el camino más corto (rotate vs reverse_rotate)
** Relación: Segunda fase de chunk_sort(), llamada después de push_chunks()
** Flujo: chunk_sort() → push_chunks() → push_back() → [A ordenado]
** Resultado: A queda ordenado de menor a mayor (índices 0..n-1)
*/
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

/*
** ALGORITMO PRINCIPAL: Chunk Sort para stacks grandes (>5 elementos)
** Divide y conquista en 2 fases:
**   Fase 1: push_chunks() - Mueve elementos a B por grupos
**   Fase 2: push_back() - Devuelve elementos ordenados a A
** Rendimiento típico:
**   100 elementos, 5 chunks: ~600 movimientos
**   500 elementos, 11 chunks: ~5500 movimientos
** Llamada por: sort_stack() después de assign_indexes()
** Flujo: sort_stack() → assign_indexes() → chunk_sort()
** Parámetros: a/b (stacks), chunks (número de grupos a dividir)
*/
void	chunk_sort(t_node **a, t_node **b, int chunks)
{
	int		size;
	int		chunk;

	size = stack_size(*a);
	chunk = size / chunks + 1;
	push_chunks(a, b, chunk);
	push_back(a, b);
}
