/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

/*
** Verifica si un string contiene solo espacios o tabs
** Propósito: Detectar argumentos vacíos como "./push_swap '   '"
** Relación: Función auxiliar de validate_args()
** Flujo: main() → validate_args() → has_only_spaces()
** Retorno: 1 si solo tiene espacios/NULL, 0 si tiene contenido
*/
static int	has_only_spaces(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '	')
			return (0);
		i++;
	}
	return (1);
}

/*
** Validación inicial de argumentos antes del parsing
** Verifica: Argumentos no vacíos o solo espacios
** Relación: Primera validación en main() antes de parse_input()
** Flujo: main() → validate_args() → has_only_spaces()
** Retorno: 1 si válidos, 0 si error (imprime "Error\n" a stderr)
*/
static int	validate_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (has_only_spaces(argv[i]))
		{
			write(2, "Error\n", 6);
			return (0);
		}
		i++;
	}
	return (1);
}

/*
** PUNTO DE ENTRADA: Coordina el flujo completo del programa
** Flujo de ejecución:
**   1. Validar argumentos (validate_args)
**   2. Parsear entrada (parse_input) - incluye validación completa
**   3. Verificar si ya está ordenado (is_sorted) - optimización
**   4. Ordenar (sort_stack) - selecciona algoritmo según tamaño
**   5. Liberar memoria (free_stack)
** Casos especiales:
**   - Sin argumentos: salida silenciosa
**   - Argumentos inválidos: imprime "Error" y sale con código 1
**   - Ya ordenado: salida silenciosa sin operaciones
** Salida: Imprime secuencia de operaciones (sa, pb, ra, etc.) a stdout
*/
int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
		return (0);
	if (!validate_args(argc, argv))
		return (1);
	stack_a = parse_input(argc, argv);
	if (!stack_a)
		return (write(2, "Error\n", 6));
	if (is_sorted(stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	sort_stack(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
