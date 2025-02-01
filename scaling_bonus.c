/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:04:25 by aedarkao          #+#    #+#             */
/*   Updated: 2025/02/01 13:34:40 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	scale_map(t_vars *v)
{
	int	i;

	i = 0;
	while (i < v->map.w * v->map.h)
	{
		v->map.v[i].x = (v->map.scale0 + v->map.scale) * v->v1[i].x;
		v->map.v[i].y = (v->map.scale0 + v->map.scale) * v->v1[i].y;
		v->map.v[i].z = (v->map.scale0 + v->map.scale) * v->v1[i].z;
		i++;
	}
}

t_point	get_array_min(t_point *v, t_map map)
{
	t_point	min;
	int		i;

	min.x = v[0].x;
	min.y = v[0].y;
	min.yf = v[0].yf;
	i = 0;
	while (i < map.w * map.h)
	{
		min.x = min_int(min.x, v[i].x);
		min.y = min_int(min.y, v[i].y);
		min.yf = min_int(min.yf, v[i].yf);
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
	max.yf = v[0].yf;
	i = 0;
	while (i < map.w * map.h)
	{
		max.x = max_int(max.x, v[i].x);
		max.y = max_int(max.y, v[i].y);
		max.yf = max_int(max.yf, v[i].yf);
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
		min = get_array_min(v->v1, v->map);
		max = get_array_max(v->v1, v->map);
		dx = max.x - min.x;
		dy = max.y - min.y;
		v->map.scale0 = min_double((0.9 * W_W) / dx, (0.9 * W_H) / dy);
		if (v->map.w == 1 && v->map.h == 1)
			v->map.scale0 = 1;
		v->s_flag = 1;
	}
	scale_map(v);
}
