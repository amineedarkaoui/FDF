/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:21:55 by aedarkao          #+#    #+#             */
/*   Updated: 2025/01/28 07:43:42 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	read_buf(int fd, char **buf, int *read_bytes)
{
	char	*new_cont;
	char	*old_cont;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return ;
	if (*buf)
		old_cont = ft_strdup(*buf);
	else
		old_cont = ft_strdup("");
	new_cont = (char *) malloc(BUFFER_SIZE + 1);
	*read_bytes = read(fd, new_cont, BUFFER_SIZE);
	if (*read_bytes > 0)
	{
		new_cont[*read_bytes] = 0;
		free(*buf);
		*buf = ft_strjoin(old_cont, new_cont);
	}
	free(new_cont);
	free(old_cont);
}

static int	contains_nl(char *buf)
{
	int	i;

	if (!buf)
		return (0);
	i = 0;
	while (buf[i])
	{
		if (buf[i++] == '\n')
			return (1);
	}
	return (0);
}

static int	is_valid(char *buf, int read_bytes)
{
	if (contains_nl(buf) || read_bytes == 0 || read_bytes == -1)
		return (1);
	return (0);
}

static char	*get_ret_buf(char **buf, int read_bytes, char *ret_buf, char *tmp)
{
	int		pos;

	if (!ft_strlen(*buf) || read_bytes == -1)
		return (NULL);
	if (!contains_nl(*buf))
	{
		ret_buf = ft_strdup(*buf);
		free(*buf);
		*buf = NULL;
	}
	else
	{
		pos = ft_strchr(*buf, '\n') - *buf;
		ret_buf = ft_substr(*buf, 0, pos + 1);
		tmp = *buf;
		*buf = ft_substr(tmp, pos + 1, ft_strlen(tmp) + 1);
		free(tmp);
		if (!ft_strlen(*buf))
		{
			free(*buf);
			*buf = NULL;
		}
	}
	return (ret_buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	int			read_bytes;
	char		*ret_buf;
	char		*tmp;

	ret_buf = NULL;
	tmp = NULL;
	read_bytes = -2;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (is_valid(buf, read_bytes))
			return (get_ret_buf(&buf, read_bytes, ret_buf, tmp));
		read_buf(fd, &buf, &read_bytes);
	}
}
