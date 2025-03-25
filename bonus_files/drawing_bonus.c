/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:01:46 by aedarkao          #+#    #+#             */
/*   Updated: 2025/03/25 13:48:55 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	are_coords_valid(int x, int y)
{
	int	c1;
	int	c2;

	c1 = (x < W_W && x >= 0);
	c2 = (y < W_H && y >= 0);
	return (c1 && c2);
}

void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (are_coords_valid(x, y))
	{
		dst = data->addr + (y * data->ll + x * (data->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void	draw_l(t_img *img, t_point a, t_point b)
{
	t_line_vars	v;

	v.dx = abs(b.x - a.x);
	v.dy = abs(b.y - a.y);
	v.sx = is_greater(b.x, a.x);
	v.sy = is_greater(b.y, a.y);
	v.err = v.dx - v.dy;
	v.i = 0;
	while (a.x != b.x || a.y != b.y)
	{
		my_pixel_put(img, a.x, a.y, gcolor(max_int(v.dx, v.dy), v.i, a.c, b.c));
		v.err2 = 2 * v.err;
		if (v.err2 > -v.dy)
		{
			v.err -= v.dy;
			a.x += v.sx;
		}
		if (v.err2 < v.dx)
		{
			v.err += v.dx;
			a.y += v.sy;
		}
		v.i++;
	}
	my_pixel_put(img, b.x, b.y, b.c);
}

void	draw_row(t_vars v, int x)
{
	int	y;

	y = 0;
	while (y < v.m.h)
	{
		if (y < v.m.h - 1 && x < v.m.w - 1)
		{
			draw_l(&v.img, v.v0[y * v.m.w + x], v.v0[y * v.m.w + x + 1]);
			draw_l(&v.img, v.v0[y * v.m.w + x], v.v0[(y + 1) * v.m.w + x]);
		}
		else if (y < v.m.h - 1 || x < v.m.w - 1)
		{
			if (x == v.m.w - 1)
				draw_l(&v.img, v.v0[y * v.m.w + x], v.v0[(y + 1) * v.m.w + x]);
			if (y == v.m.h - 1)
				draw_l(&v.img, v.v0[y * v.m.w + x], v.v0[y * v.m.w + x + 1]);
		}
		y++;
	}
}

void	draw_map(t_vars v)
{
	int	x;

	if (v.m.w == 1 && v.m.h == 1)
		my_pixel_put(&v.img, v.v0[0].x, v.v0[0].y, v.v0->c);
	x = 0;
	while (x < v.m.w)
	{
		draw_row(v, x);
		x++;
	}
}
