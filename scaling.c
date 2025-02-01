/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:04:25 by aedarkao          #+#    #+#             */
/*   Updated: 2025/01/30 15:27:28 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_map(t_map map)
{
	int	i;

	i = 0;
	while (i < map.w * map.h)
	{
		map.v[i].x *= map.scale;
		map.v[i].y *= map.scale;
		map.v[i].z *= map.scale;
		i++;
	}
}

double	min_double(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	dynamic_scale(t_map *map)
{
	t_point	min;
	t_point	max;
	int		dx;
	int		dy;

	min = get_map_min(*map);
	max = get_map_max(*map);
	dx = max.x - min.x;
	dy = max.y - min.y;
	map->scale += min_double((0.9 * W_W) / dx, (0.9 * W_H) / dy);
	if (map->w == 1 && map->h == 1)
		map->scale = 1;
	scale_map(*map);
}
