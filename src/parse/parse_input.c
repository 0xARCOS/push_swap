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
	return (1);
}

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
