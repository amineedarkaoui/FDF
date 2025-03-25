/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:01:39 by aedarkao          #+#    #+#             */
/*   Updated: 2025/03/25 13:59:48 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	perspective(t_vars v)
{
	int		i;
	double	a;
	int		z;
	int		min;

	a = 393 / v.m.scale0;
	min = get_map_min(v).z;
	i = 0;
	while (i < v.m.w * v.m.h)
	{
		if (min <= 0)
			z = v.v0[i].z + 1 + abs(get_map_min(v).z);
		else
			z = v.v0[i].z;
		if (v.v0[i].z != 0)
		{
			v.v0[i].x = (v.v0[i].x * a) / z;
			v.v0[i].y = (v.v0[i].y * a) / z;
		}
		i++;
	}
}
