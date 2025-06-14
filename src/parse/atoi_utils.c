/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codex <codex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:00:00 by codex             #+#    #+#             */
/*   Updated: 2024/06/06 00:00:00 by codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_sign(const char *str, int *i)
{
	int		sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi_push_swap(const char *str, int *error_flag)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	i = 0;
	sign = parse_sign(str, &i);
	*error_flag = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && (-result) < INT_MIN))
		{
			*error_flag = 1;
			return (0);
		}
		i++;
	}
	return ((int)(result * sign));
}
