/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:48:19 by aedarkao          #+#    #+#             */
/*   Updated: 2025/02/01 17:08:41 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	rotate_y(t_vars v, double angle)
{
	int	i;
	int	x;
	int	z;

	i = 0;
	while (i < v.map.w * v.map.h)
	{
		x = cos(angle) * v.v0[i].x + sin(angle) * v.v0[i].z;
		z = -sin(angle) * v.v0[i].x + cos(angle) * v.v0[i].z;
		v.map.v[i].x = x;
		v.map.v[i].z = z;
		v.map.v[i].y = v.v0[i].y;
		i++;
	}
}

void	rotate_x(t_vars v, double angle)
{
	int	i;
	int	y;
	int	z;

	i = 0;
	while (i < v.map.w * v.map.h)
	{
		y = cos(angle) * v.map.v[i].y - sin(angle) * v.map.v[i].z;
		z = sin(angle) * v.map.v[i].y + cos(angle) * v.map.v[i].z;
		v.map.v[i].y = y;
		v.map.v[i].z = z;
		i++;
	}
}

void	rotate_z(t_vars v, double angle)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < v.map.w * v.map.h)
	{
		x = cos(angle) * v.map.v[i].x - sin(angle) * v.map.v[i].y;
		y = sin(angle) * v.map.v[i].x + cos(angle) * v.map.v[i].y;
		v.map.v[i].x = x;
		v.map.v[i].y = y;
		i++;
	}
}
