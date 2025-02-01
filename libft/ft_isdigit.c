/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:30:02 by aedarkao          #+#    #+#             */
/*   Updated: 2024/10/26 13:57:55 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// int main()
// {
// 	printf("%d\n", ft_isdigit('a'));
// 	printf("%d\n", ft_isdigit('7'));
// 	printf("%d\n", ft_isdigit(40));
// 	printf("%d\n", ft_isdigit('Y'));
// 	printf("%d\n", ft_isdigit('4'));
// 	printf("%d\n", ft_isdigit('.'));
// 	printf("%d\n", ft_isdigit('p'));
// }
