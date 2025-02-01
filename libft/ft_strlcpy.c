/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:22:17 by aedarkao          #+#    #+#             */
/*   Updated: 2024/10/26 13:58:31 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	while (src[i])
		i++;
	return (i);
}

// void test_strlcpy(char *dest, const char *src, size_t size) {
// 	printf("output: %zu, %s\n", ft_strlcpy(dest, src, size), dest);
// }

// int main()
// {
// 	char src[] = "coucou";
//     char dest[10];
// 	memset(dest, 'A', 10);
// 	printf("%s\n", dest);
//     printf("%d, %s\n", ft_strlcpy(dest, src, 0), dest);
// 	return (0);
// }
