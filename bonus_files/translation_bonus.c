/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:01:35 by aedarkao          #+#    #+#             */
/*   Updated: 2025/02/16 11:14:01 by aedarkao         ###   ########.fr       */
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

void	translate_map(t_vars v, int x, int y, int yf, int z)
{
	int	i;

	i = 0;
	while (i < v.map.w * v.map.h)
	{
		v.v0[i].x += x;
		v.v0[i].y += y;
		v.v0[i].yf += yf;
		v.v0[i].z += z;
		i++;
	}
}

void	translate_center(t_vars v)
{
	t_point	center;

	center = get_map_center(v);
	translate_map(v, W_W / 2 - center.x, W_H / 2 - center.yf, 0, 0);
}
