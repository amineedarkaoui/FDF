/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:48:19 by aedarkao          #+#    #+#             */
/*   Updated: 2025/02/16 11:07:02 by aedarkao         ###   ########.fr       */
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
		v.v0[i].x = x;
		v.v0[i].z = z;
		v.v0[i].y = v.v0[i].y;
		v.v0[i].yf = v.v0[i].yf;
		i++;
	}
}

void	rotate_x(t_vars v, double angle)
{
	int	i;
	int	y;
	int	yf;
	int	z;

	i = 0;
	while (i < v.map.w * v.map.h)
	{
		y = cos(angle) * v.v0[i].y - sin(angle) * v.v0[i].z;
		yf = cos(angle) * v.v0[i].yf - sin(angle) * v.v0[i].z;
		z = sin(angle) * v.v0[i].y + cos(angle) * v.v0[i].z;
		v.v0[i].y = y;
		v.v0[i].yf = yf;
		v.v0[i].z = z;
		i++;
	}
}

void	rotate_z(t_vars v, double angle)
{
	int	i;
	int	x;
	int	y;
	int	yf;

	i = 0;
	while (i < v.map.w * v.map.h)
	{
		x = cos(angle) * v.v0[i].x - sin(angle) * v.v0[i].y;
		y = sin(angle) * v.v0[i].x + cos(angle) * v.v0[i].y;
		yf = sin(angle) * v.v0[i].x + cos(angle) * v.v0[i].yf;
		v.v0[i].x = x;
		v.v0[i].y = y;
		v.v0[i].yf = yf;
		i++;
	}
}
