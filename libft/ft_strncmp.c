/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:13:16 by aedarkao          #+#    #+#             */
/*   Updated: 2024/10/26 13:58:39 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
			return (1);
		if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
			return (-1);
		i++;
	}
	return (0);
}

// int main()
// {
// 	printf("%d %d\n", ft_strncmp("a", "a", 100), strncmp("a", "a", 100));
// 	printf("%d %d\n", ft_strncmp("", "helrld" , 6), strncmp("", "helrld" , 6));
// 	printf("%d %d\n", ft_strncmp("40", "e", 0), strncmp("40", "e", 0));
// 	printf("%d %d\n", ft_strncmp(" ", "e", 1), strncmp(" ", "e", 1));
// 	printf("%d %d\n", ft_strncmp("", "e", 20), strncmp("", "e", 20));
// 	printf("%d %d\n", ft_strncmp(".", "e", -1), strncmp(".", "e", -1));
// 	printf("%d %d\n", ft_strncmp("p", "e", 2), strncmp("p", "e", 2));
// 	return (0);
// }
