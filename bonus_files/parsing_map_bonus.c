/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:53:18 by aedarkao          #+#    #+#             */
/*   Updated: 2025/02/15 22:05:42 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	free_split(char ***strs)
{
	int	i;

	i = 0;
	while (*strs && (*strs)[i])
	{
		free((*strs)[i]);
		(*strs)[i] = NULL;
		i++;
	}
	free(*strs);
	*strs = NULL;
}

static void	count_map(char *filename, t_map *map)
{
	t_read_vars	vars;

	vars.is_colored = 0;
	vars.fd = open(filename, O_RDONLY);
	if (vars.fd == -1)
		exit(1);
	map->h = 0;
	while (1)
	{
		vars.gnl = get_next_line(vars.fd);
		if (!vars.gnl)
			break ;
		vars.count = count_words(vars.gnl, " \n");
		if (map->h > 0 && vars.count != map->w)
			vars.is_colored = 1;
		map->w = vars.count;
		free(vars.gnl);
		map->h++;
	}
	if (!map->w || !map->h || vars.is_colored)
		exit(1);
	close(vars.fd);
}

int	fill_pixel(t_map *map, char *row, int i, int j)
{
	char	**pair;

	map->scale = 0;
	pair = ft_split(row, ',');
	map->v[i * map->w + j].x = j * 1000;
	map->v[i * map->w + j].yf = -ft_atoi(pair[0]) * 100;
	map->v[i * map->w + j].y = 0;
	map->v[i * map->w + j].z = (map->h - i - 1) * 1000;
	if (pair[1])
	{
		ft_tolower(pair[1]);
		map->v[i * map->w + j].c = ft_hextoi(pair[1] + 2);
		free_split(&pair);
		return (1);
	}
	else
	{
		map->v[i * map->w + j].c = 0xFFFFFF;
		free_split(&pair);
		return (0);
	}
}

void	color_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->w * map->h)
	{
		if (map->v[i].yf == 0)
			map->v[i].c = 0xffffff;
		else if (map->v[i].yf < 0)
			map->v[i].c = MAX_COLOR;
		else
			map->v[i].c = MIN_COLOR;
		i++;
	}
}

void	read_map(char *filename, t_map *map)
{
	t_read_vars	v;

	v.row = ft_split(filename, '.');
	if (ft_strncmp(v.row[1], "fdf", 3))
		exit(1);
	free_split(&v.row);
	count_map(filename, map);
	v.fd = open(filename, O_RDONLY);
	map->v = malloc(map->h * map->w * sizeof(t_point));
	if (!map->v)
	exit(1);
	v.i = 0;
	v.is_colored = 0;
	while (v.i < map->h)
	{
		v.gnl = get_next_line(v.fd);
		v.row = ft_split(v.gnl, ' ');
		free(v.gnl);
		v.j = -1;
		while (++v.j < map->w)
		v.is_colored += fill_pixel(map, v.row[v.j], v.i, v.j);
		free_split(&v.row);
		v.i++;
	}
	if (!v.is_colored)
		color_map(map);
	close(v.fd);
}
