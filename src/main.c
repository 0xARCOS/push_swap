/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariarcos <ariarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:11:31 by ariarcos          #+#    #+#             */
/*   Updated: 2026/01/11 21:11:32 by ariarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

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
