/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:18:17 by aedarkao          #+#    #+#             */
/*   Updated: 2025/03/25 13:58:33 by aedarkao         ###   ########.fr       */
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
	min.y = v.v0[0].y;
	min.z = v.v0[0].z;
	i = 0;
	while (i < v.m.w * v.m.h)
	{
		min.x = min_int(min.x, v.v0[i].x);
		min.y = min_int(min.y, v.v0[i].y);
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
	max.y = v.v0[0].y;
	max.z = v.v0[0].z;
	i = 0;
	while (i < v.m.w * v.m.h)
	{
		max.x = max_int(max.x, v.v0[i].x);
		max.y = max_int(max.y, v.v0[i].y);
		max.z = max_int(max.z, v.v0[i].z);
		i++;
	}
	return (max);
}

t_point	get_map_center(t_vars v)
{
	t_point	m;
	t_point	n;

	n = get_map_min(v);
	m = get_map_max(v);
	return ((t_point){(m.x + n.x) / 2, (m.y + n.y) / 2, (m.z + n.z) / 2, 0, 0});
}
