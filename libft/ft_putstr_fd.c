/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:48:29 by aedarkao          #+#    #+#             */
/*   Updated: 2024/11/01 17:40:57 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	n;

	if (s)
	{
		n = write(fd, s, ft_strlen(s));
		(void)n;
	}
}

// int	main()
// {
// 	int fd = open("myfile.txt", O_WRONLY);
// 	char str[] = "hello world";
// 	ft_putstr_fd(str, fd);
// 	close(fd);
// 	return (0);
// }
