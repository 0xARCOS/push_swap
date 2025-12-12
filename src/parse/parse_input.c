/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Verifica si hay números duplicados en el stack
** Complejidad: O(n²) - aceptable porque se ejecuta una sola vez
** Relación: Llamada por parse_input() al final de la validación
** Flujo: parse_input() → add_arguments() → has_duplicates()
** Retorno: 1 si hay duplicados (error), 0 si todos son únicos (OK)
*/
static int	has_duplicates(t_node *stack)
{
	t_node	*current;
	t_node	*runner;

	current = stack;
	while (current)
	{
		runner = current->next;
		while (runner)
		{
			if (current->value == runner->value)
				return (1);
			runner = runner->next;
		}
		current = current->next;
	}
	return (0);
}

/*
** Copia tokens de split al array de tokens principal
** Propósito: Consolida todos los splits en un único array
** Relación: Función auxiliar de split_args()
** Flujo: split_args() → ft_split() → append_tokens()
** Parámetros: tokens (destino), split (origen), k (índice actual)
** Retorno: 1 si éxito, 0 si falla strdup (limpia split automáticamente)
*/
static int	append_tokens(char **tokens, char **split, int *k)
{
	int	j;

	j = 0;
	while (split[j])
	{
		tokens[*k] = ft_strdup(split[j]);
		if (!tokens[*k])
		{
			free_split(split);
			return (0);
		}
		(*k)++;
		j++;
	}
	free_split(split);
	return (1);
}

/*
** Divide todos los argumentos en tokens individuales
** Maneja casos como: "./push_swap 3 2 1" y "./push_swap "3 2 1""
** Relación: Llamada por parse_input() al inicio del parsing
** Flujo: parse_input() → split_args() → ft_split() → append_tokens()
** Retorno: Array de strings (tokens) terminado en NULL, o NULL si error
** Nota: Usa count_all_tokens() para calcular el tamaño necesario
*/
char	**split_args(int argc, char **argv)
{
	char	**tokens;
	char	**split;
	int		i;
	int		k;

	tokens = malloc(sizeof(char *) * (count_all_tokens(argc, argv) + 1));
	if (!tokens)
		return (NULL);
	i = 1;
	k = 0;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		if (!split || !append_tokens(tokens, split, &k))
		{
			free_tokens(tokens, k);
			return (NULL);
		}
		i++;
	}
	tokens[k] = NULL;
	return (tokens);
}

/*
** OPTIMIZED: Invierte el stack (necesario porque add_node ahora inserta al inicio)
** Complejidad: O(n) una sola vez al final del parsing
** Propósito: Restaurar el orden original de los argumentos
** Relación: Llamada por add_arguments() después de añadir todos los nodos
*/
static void	reverse_stack(t_node **stack)
{
	t_node	*prev;
	t_node	*current;
	t_node	*next;

	if (!stack || !*stack)
		return ;
	prev = NULL;
	current = *stack;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*stack = prev;
}

/*
** Añade todos los tokens al stack validando cada número
** OPTIMIZED: add_node inserta al inicio (O(1)), luego invertimos una vez
** Total: O(n) en lugar de O(n²)
** Relación: Llamada por parse_input() después de split_args()
** Flujo: parse_input() → split_args() → add_arguments() → add_node()
*/
static int	add_arguments(t_node **stack, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!is_valid_number(tokens[i]) || !add_node(stack, tokens[i]))
			return (0);
		i++;
	}
	reverse_stack(stack);
	return (1);
}

/*
** FUNCIÓN PRINCIPAL DE PARSING: Convierte argumentos en stack validado
** Proceso de validación en 4 etapas:
**   1. split_args(): Divide argumentos en tokens individuales
**   2. add_arguments(): Convierte tokens en nodos del stack (OPTIMIZADO)
**   3. has_duplicates(): Verifica que no haya números repetidos
**   4. Validación de rango INT en ft_atoi_push_swap (dentro de create_node)
** Llamada por: main() después de validate_args()
** Retorno: Stack inicializado y validado, o NULL si hay algún error
** Nota: Limpia toda la memoria en caso de error antes de retornar NULL
*/
t_node	*parse_input(int argc, char **argv)
{
	char	**tokens;
	t_node	*stack;

	tokens = split_args(argc, argv);
	stack = NULL;
	if (!tokens || !add_arguments(&stack, tokens))
	{
		free_split(tokens);
		free_stack(&stack);
		return (NULL);
	}
	free_split(tokens);
	if (has_duplicates(stack))
	{
		free_stack(&stack);
		return (NULL);
	}
	return (stack);
}
