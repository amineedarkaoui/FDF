/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 05:19:31 by aedarkao          #+#    #+#             */
/*   Updated: 2025/01/30 18:22:35 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_img *img, t_map m)
{
	int	x;
	int	y;

	if (m.w == 1 && m.h == 1)
		my_pixel_put(img, m.v[0].x, m.v[0].y, m.v->c);
	x = -1;
	while (++x < m.w)
	{
		y = -1;
		while (++y < m.h)
		{
			if (y < m.h - 1 && x < m.w - 1)
			{
				draw_l(img, m.v[y * m.w + x], m.v[y * m.w + x + 1]);
				draw_l(img, m.v[y * m.w + x], m.v[(y + 1) * m.w + x]);
			}
			else if (y < m.h - 1 || x < m.w - 1)
			{
				if (x == m.w - 1)
					draw_l(img, m.v[y * m.w + x], m.v[(y + 1) * m.w + x]);
				if (y == m.h - 1)
					draw_l(img, m.v[y * m.w + x], m.v[y * m.w + x + 1]);
			}
		}
	}
}

void	clean_n_quit(t_vars *vars)
{
	free(vars->map.v);
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->mlx_win)
		mlx_destroy_window(vars->mlx, vars->mlx_win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	exit(0);
}

void	display_map(t_map map)
{
	t_vars	v;

	v.map = map;
	v.mlx = mlx_init();
	v.mlx_win = mlx_new_window(v.mlx, W_W, W_H, "FDF");
	v.img.img = mlx_new_image(v.mlx, W_W, W_H);
	v.img.addr = mlx_get_data_addr(v.img.img, &v.img.bpp, &v.img.ll, &v.img.e);
	isometric(map);
	dynamic_scale(&map);
	translate_center(map);
	draw_map(&v.img, map);
	mlx_hook(v.mlx_win, 2, 1L << 0, key_hook, &v);
	mlx_hook(v.mlx_win, 17, 0, button_hook, &v);
	mlx_put_image_to_window(v.mlx, v.mlx_win, v.img.img, 0, 0);
	mlx_loop(v.mlx);
}

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
	{
		ft_putstr_fd("Invalid number of args!\n", 1);
		return (1);
	}
	read_map(av[1], &map);
	display_map(map);
	return (0);
}
