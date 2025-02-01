/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:18:17 by aedarkao          #+#    #+#             */
/*   Updated: 2025/02/01 11:37:54 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	min_int(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

t_point	get_map_min(t_map map)
{
	t_point	min;
	int		i;

	min.x = map.v[0].x;
	min.y = map.v[0].y;
	i = 0;
	while (i < map.w * map.h)
	{
		min.x = min_int(min.x, map.v[i].x);
		min.y = min_int(min.y, map.v[i].y);
		i++;
	}
	return (min);
}

t_point	get_map_max(t_map map)
{
	t_point	max;
	int		i;

	max.x = map.v[0].x;
	max.y = map.v[0].y;
	i = 0;
	while (i < map.w * map.h)
	{
		max.x = max_int(max.x, map.v[i].x);
		max.y = max_int(max.y, map.v[i].y);
		i++;
	}
	return (max);
}

t_point	get_map_center(t_vars v)
{
	t_point	max;
	t_point	min;

	min = get_map_min(v.map);
	max = get_map_max(v.map);
	return ((t_point){(max.x + min.x) / 2, (max.y + min.y) / 2, 0, 0, 0});
}
