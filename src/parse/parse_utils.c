/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Cuenta el número total de tokens en todos los argumentos
** Propósito: Pre-calcular el tamaño del array para malloc en split_args()
** Relación: Llamada por split_args() antes de hacer malloc
** Flujo: split_args() → count_all_tokens() → ft_split()
** Nota: Hace split de cada argumento para contar (se puede optimizar)
** Retorno: Número total de tokens, o 0 si error
*/
int	count_all_tokens(int argc, char **argv)
{
	int		i;
	int		count;
	char	**split;
	int		j;

	i = 1;
	count = 0;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		if (!split)
			return (0);
		j = 0;
		while (split[j++])
			count++;
		free_split(split);
		i++;
	}
	return (count);
}

/*
** Valida que un string represente un número entero válido
** Formato aceptado: [+/-]dígitos
** Rechaza: strings vacíos, solo signo, caracteres no numéricos
** Relación: Llamada por add_arguments() antes de add_node()
** Flujo: add_arguments() → is_valid_number() → [retorna bool]
** Retorno: 1 si es válido, 0 si no es un número válido
*/
int	is_valid_number(const char *str)
{
	int		i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/*
** Crea un nuevo nodo a partir de un string numérico
** Valida rango INT_MIN a INT_MAX en ft_atoi_push_swap
** Relación: Función auxiliar de add_node()
** Flujo: add_node() → create_node() → ft_atoi_push_swap()
** Parámetros: str (string numérico), error (flag de salida)
** Retorno: Nodo inicializado con index=-1, o NULL si error/overflow
*/
static t_node	*create_node(const char *str, int *error)
{
	t_node	*new;

	*error = 0;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = ft_atoi_push_swap(str, error);
	if (*error)
	{
		free(new);
		return (NULL);
	}
	new->index = -1;
	new->next = NULL;
	return (new);
}

/*
** OPTIMIZED: Añade un nodo al INICIO del stack (O(1) en lugar de O(n))
** La lista se construye en orden inverso, se invierte después en parse_input
** Relación: Llamada por add_arguments() para cada token parseado
** Flujo: parse_input() → add_arguments() → add_node() → create_node()
** Optimización: Evita recorrer toda la lista en cada inserción (O(n²) → O(n))
** Retorno: 1 si éxito, 0 si error de memoria o overflow
*/
int	add_node(t_node **stack, const char *str)
{
	t_node	*new;
	int		error;

	new = create_node(str, &error);
	if (!new)
		return (0);
	new->next = *stack;
	*stack = new;
	return (1);
}
