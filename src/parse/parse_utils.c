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

int	count_all_tokens(int argc, char **argv)
{
	int		i;
	int		count;
	char		**split;
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

int	add_node(t_node **stack, const char *str)
{
	t_node	*new;
	t_node	*temp;
	int		error;

	new = create_node(str, &error);
	if (!new)
		return (0);
	if (!*stack)
	{
		*stack = new;
		return (1);
	}
	temp = *stack;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (1);
}
