/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:18:17 by aedarkao          #+#    #+#             */
/*   Updated: 2025/02/16 11:04:51 by aedarkao         ###   ########.fr       */
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

t_point	get_map_min(t_vars v)
{
	t_point	min;
	int		i;

	min.x = v.v0[0].x;
	min.yf = v.v0[0].yf;
	min.z = v.v0[0].z;
	i = 0;
	while (i < v.map.w * v.map.h)
	{
		min.x = min_int(min.x, v.v0[i].x);
		min.yf = min_int(min.yf, v.v0[i].yf);
		min.z = min_int(min.z, v.v0[i].z);
		i++;
	}
	return (min);
}

t_point	get_map_max(t_vars v)
{
	t_point	max;
	int		i;

	max.x = v.v0[0].x;
	max.yf = v.v0[0].yf;
	max.z = v.v0[0].z;
	i = 0;
	while (i < v.map.w * v.map.h)
	{
		max.x = max_int(max.x, v.v0[i].x);
		max.yf = max_int(max.yf, v.v0[i].yf);
		max.z = max_int(max.z, v.v0[i].z);
		i++;
	}
	return (max);
}

t_point	get_map_center(t_vars v)
{
	t_point	max;
	t_point	min;

	min = get_map_min(v);
	max = get_map_max(v);
	return ((t_point){(max.x + min.x) / 2, 0, (max.yf + min.yf) / 2, (max.z + min.z) / 2, 0});
}
