/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:01:41 by aedarkao          #+#    #+#             */
/*   Updated: 2025/01/30 20:48:40 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_map map, double angle)
{
	int	i;
	int	y;
	int	z;

	i = 0;
	while (i < map.w * map.h)
	{
		y = cos(angle) * map.v[i].y - sin(angle) * map.v[i].z;
		z = sin(angle) * map.v[i].y + cos(angle) * map.v[i].z;
		map.v[i].y = y;
		map.v[i].z = z;
		i++;
	}
}

void	rotate_y(t_map map, double angle)
{
	int	i;
	int	x;
	int	z;

	i = 0;
	while (i < map.w * map.h)
	{
		x = cos(angle) * map.v[i].x + sin(angle) * map.v[i].z;
		z = -sin(angle) * map.v[i].x + cos(angle) * map.v[i].z;
		map.v[i].x = x;
		map.v[i].z = z;
		i++;
	}
}

void	rotate_z(t_map map, double angle)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < map.w * map.h)
	{
		x = cos(angle) * map.v[i].x - sin(angle) * map.v[i].y;
		y = sin(angle) * map.v[i].x + cos(angle) * map.v[i].y;
		map.v[i].x = x;
		map.v[i].y = y;
		i++;
	}
}

void	isometric(t_map map)
{
	rotate_y(map, ISO_Y);
	rotate_x(map, ISO_X);
}
