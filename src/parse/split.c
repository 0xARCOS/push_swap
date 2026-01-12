/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariarcos <ariarcos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:11:11 by ariarcos          #+#    #+#             */
/*   Updated: 2026/01/11 21:11:13 by ariarcos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	word_count(const char *s, char c)
{
	int		count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*word_dup(const char *start, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_all(char **result, int i)
{
	while (i--)
		free(result[i]);
	free(result);
}

static int	populate_words(char **res, const char *s, char c, int *k)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	start = -1;
	while (s[i])
	{
		if (s[i] != c && start < 0)
			start = i;
		if ((s[i] == c || s[i + 1] == '\0') && start >= 0)
		{
			if (s[i] == c)
				len = i - start;
			else
				len = i - start + 1;
			res[*k] = word_dup(s + start, len);
			if (!res[*k])
				return (0);
			(*k)++;
			start = -1;
		}
		i++;
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		k;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!result)
		return (NULL);
	k = 0;
	if (!populate_words(result, s, c, &k))
	{
		free_all(result, k);
		return (NULL);
	}
	result[k] = NULL;
	return (result);
}
