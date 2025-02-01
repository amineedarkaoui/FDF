/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:01:35 by aedarkao          #+#    #+#             */
/*   Updated: 2025/01/30 22:52:27 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	copy_array(t_point *array, int size, t_point *copy)
{
	int	i;

	i = 0;
	while (i < size)
	{
		copy[i] = array[i];
		i++;
	}
}

void	translate_map(t_map map, int x, int y)
{
	int	i;

	i = 0;
	while (i < map.w * map.h)
	{
		map.v[i].x += x;
		map.v[i].y += y;
		i++;
	}
}

void	translate_center(t_vars v)
{
	t_point	center;

	center = get_map_center(v);
	translate_map(v.map, W_W / 2 - center.x, W_H / 2 - center.y);
}
