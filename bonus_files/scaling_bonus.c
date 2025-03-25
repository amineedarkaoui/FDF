/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:04:25 by aedarkao          #+#    #+#             */
/*   Updated: 2025/03/25 13:52:36 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	scale_map(t_vars *v)
{
	int	i;

	i = 0;
	while (i < v->m.w * v->m.h)
	{
		v->v0[i].x = (v->m.scale0 + v->m.scale) * v->v0[i].x;
		v->v0[i].y = (v->m.scale0 + v->m.scale) * v->v0[i].y;
		v->v0[i].z = (v->m.scale0 + v->m.scale) * v->v0[i].z;
		i++;
	}
}

t_point	get_array_min(t_point *v, t_map map)
{
	t_point	min;
	int		i;

	min.x = v[0].x;
	min.y = v[0].y;
	min.y = v[0].y;
	i = 0;
	while (i < map.w * map.h)
	{
		min.x = min_int(min.x, v[i].x);
		min.y = min_int(min.y, v[i].y);
		min.y = min_int(min.y, v[i].y);
		i++;
	}
	return (min);
}

t_point	get_array_max(t_point *v, t_map map)
{
	t_point	max;
	int		i;

	max.x = v[0].x;
	max.y = v[0].y;
	max.y = v[0].y;
	i = 0;
	while (i < map.w * map.h)
	{
		max.x = max_int(max.x, v[i].x);
		max.y = max_int(max.y, v[i].y);
		max.y = max_int(max.y, v[i].y);
		i++;
	}
	return (max);
}

double	min_double(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	dynamic_scale(t_vars *v)
{
	t_point	min;
	t_point	max;
	int		dx;
	int		dy;

	if (!v->s_flag)
	{
		min = get_array_min(v->v0, v->m);
		max = get_array_max(v->v0, v->m);
		dx = max.x - min.x;
		dy = max.y - min.y;
		v->m.scale0 = min_double((0.8 * W_W) / dx, (0.8 * W_H) / dy);
		if (v->m.w == 1 && v->m.h == 1)
			v->m.scale0 = 1;
	}
	scale_map(v);
}
