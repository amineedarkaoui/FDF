/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_super_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:59:47 by aedarkao          #+#    #+#             */
/*   Updated: 2025/01/31 15:02:58 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	free(vars->v0);
	free(vars->v1);
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

int	animate_map(t_vars *v)
{
	int	i;
	int	j;

	i = 0;
	while (i < v->map.h)
	{
		j = 0;
		while (j < v->map.w)
		{
			v->v0[i * v->map.w + j].z = perlin2d(j+v->offset, i+v->offset, 0.08, 10) * 1500;
			j++;
		}
		i++;
	}
	v->offset += 0.08;
	ft_bzero(v->img.addr, v->img.ll * W_H);
	rotate_y(*v, v->angles.y);
	rotate_x(*v, v->angles.x);
	rotate_z(*v, v->angles.z);
	copy_array(v->map.v, v->map.h * v->map.w, v->v1);
	scale_map(v);
	translate_map(v->map, v->t.x, v->t.y);
	draw_map(&v->img, v->map);
	mlx_put_image_to_window(v->mlx, v->mlx_win, v->img.img, 0, 0);
	return (0);
}

void	display_map(t_map map)
{
	t_vars	v;

	v.offset = 0;
	v.s_flag = 0;
	v.t = (t_point){0, 1300, 0, 0};
	v.v0 = malloc(map.h * map.w * sizeof(t_point));
	v.v1 = malloc(map.h * map.w * sizeof(t_point));
	copy_array(map.v, map.w * map.h, v.v0);
	v.angles = (t_angles){3.14 + 3.14/3, 0, 0};
	v.map = map;
	v.mlx = mlx_init();
	v.mlx_win = mlx_new_window(v.mlx, W_W, W_H, "FDF");
	v.img.img = mlx_new_image(v.mlx, W_W, W_H);
	v.img.addr = mlx_get_data_addr(v.img.img, &v.img.bpp, &v.img.ll, &v.img.e);
	mlx_hook(v.mlx_win, 2, 1L << 0, key_hook, &v);
	mlx_hook(v.mlx_win, 17, 0, button_hook, &v);
	mlx_loop_hook(v.mlx, animate_map, &v);
	mlx_loop(v.mlx);
}

int	main()
{
	t_map	map;
	int		i;
	int		j;

	map.h = 100;
	map.w = 100;
	map.scale0 = 0;
	map.scale = 0.25;
	map.v = malloc(map.h * map.w * sizeof(t_point));
	i = 0;
	while (i < map.h)
	{
		j = 0;
		while (j < map.w)
		{
			map.v[i * map.w + j].x = j * 100;
			map.v[i * map.w + j].y = i * 100;
			map.v[i * map.w + j].c = 0xFFFFFF;
			j++;
		}
		i++;
	}
	display_map(map);
	return (0);
}
