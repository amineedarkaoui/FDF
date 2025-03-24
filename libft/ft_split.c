/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:07:05 by aedarkao          #+#    #+#             */
/*   Updated: 2024/11/01 17:37:30 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_char(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	count_words(char const *s, char *charset)
{
	size_t			i;
	size_t			j;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		// printf("a");
		while (s[i + j] && !is_char(s[i + j], charset))
		{
			// printf("b");
			j++;
		}
		if (j > 0)
		{
			// printf("c");
			count++;
			i += j;
		}
		if (s[i])
			i++;
		// printf("d");
	}
	return (count);
}

static int	free_list(char **result, unsigned int count)
{
	unsigned int	i;

	i = 0;
	while (i < count)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}

static int	cpy_strs(char const *s, char c, char **result)
{
	size_t			i;
	size_t			j;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j > 0)
		{
			result[count] = ft_substr(s, i, j);
			if (!result[count])
				return (free_list(result, count));
			count++;
			i += j;
		}
		if (s[i])
			i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**result;

	if (!s)
		return (0);
	len = count_words(s, (char[]){c});
	result = malloc((len + 1) * sizeof(char *));
	if (result == 0)
		return (0);
	if (!cpy_strs(s, c, result))
		return (0);
	result[len] = 0;
	return (result);
}
