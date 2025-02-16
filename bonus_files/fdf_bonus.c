/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:44:28 by aedarkao          #+#    #+#             */
/*   Updated: 2025/02/16 16:50:47 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	draw_map(t_vars v)
{
	int	x;
	int	y;

	if (v.map.w == 1 && v.map.h == 1)
		my_pixel_put(&v.img, v.v0[0].x, v.v0[0].y, v.v0->c);
	x = -1;
	while (++x < v.map.w)
	{
		y = -1;
		while (++y < v.map.h)
		{
			if (y < v.map.h - 1 && x < v.map.w - 1)
			{
				draw_l(&v.img, v.v0[y * v.map.w + x], v.v0[y * v.map.w + x + 1]);
				draw_l(&v.img, v.v0[y * v.map.w + x], v.v0[(y + 1) * v.map.w + x]);
			}
			else if (y < v.map.h - 1 || x < v.map.w - 1)
			{
				if (x == v.map.w - 1)
					draw_l(&v.img, v.v0[y * v.map.w + x], v.v0[(y + 1) * v.map.w + x]);
				if (y == v.map.h - 1)
					draw_l(&v.img, v.v0[y * v.map.w + x], v.v0[y * v.map.w + x + 1]);
			}
		}
	}
}

void	clean_n_quit(t_vars *vars)
{
	free(vars->map.v);
	free(vars->v0);
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

void	perspective(t_vars v)
{
	int		i = 0;
	double	a = 280 / v.map.scale0;
	int		z;
	int		min = get_map_min(v).z;

	while (i < v.map.w * v.map.h)
	{
		if (min <= 0)
			z = v.v0[i].z + 1 + abs(get_map_min(v).z);
		else
			z = v.v0[i].z;
		if (v.v0[i].z != 0)
		{
			v.v0[i].x = (double)(v.v0[i].x * a) / z;
			v.v0[i].y = (double)(v.v0[i].y * a) / z;
		}
		i++;
	}
}

int	animate_map(t_vars *v)
{
	int	i;
	int	sleep_flag = 0;
	int	miny = 0;
	int maxy = 0;
	t_point	map_center;

	ft_bzero(v->img.addr, v->img.ll * W_H);
	i = 0;
	while (i < v->map.w * v->map.h)
	{
		miny = min_int(miny, v->v0[i].yf);
		maxy = max_int(maxy, v->v0[i].yf);
		i++;
	}
	i = 0;
	while (i < v->map.w * v->map.h)
	{
		if (v->map.v[i].y < v->map.v[i].yf)
		{

			v->map.v[i].y += max_int(maxy / 100, 1);
			v->map.v[i].y = min_int(v->map.v[i].y, v->map.v[i].yf);
			sleep_flag = 1;
		}
		else if (v->map.v[i].y > v->map.v[i].yf)
		{
			v->map.v[i].y += min_int(miny / 100, -1);
			v->map.v[i].y = max_int(v->map.v[i].y, v->map.v[i].yf);
			sleep_flag = 1;
		}
		i++;
	}
	if (sleep_flag)
		usleep(10000);
	copy_array(v->map.v, v->map.w * v->map.h, v->v0);
	map_center = get_map_center(*v);

	translate_map(*v, -map_center.x, -map_center.yf, -map_center.yf, -map_center.z);
	rotate_y(*v, v->angles.y);
	rotate_x(*v, v->angles.x);
	rotate_z(*v, v->angles.z);
	translate_map(*v, map_center.x, map_center.yf, map_center.yf, map_center.z);
	translate_map(*v, -map_center.x, -map_center.yf, -map_center.yf, 0);
	if (v->perspective % 2 == 1)
		perspective(*v);
	dynamic_scale(v);
	translate_center(*v);
	translate_map(*v, v->t.x, v->t.y, v->t.y, 0);
	draw_map(*v);
	mlx_put_image_to_window(v->mlx, v->mlx_win, v->img.img, 0, 0);
	return (0);
}

void	display_map(t_map map)
{
	t_vars	v;

	v.perspective = 0;
	v.s_flag = 0;
	v.t = (t_point){0, 0, 0, 0, 0};
	v.v0 = malloc(map.h * map.w * sizeof(t_point));
	v.angles = (t_angles){0.615472907, 0.785398, 0};
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

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
	{
		ft_putstr_fd("Invalid number of args!\n", 1);
		return (1);
	}
	read_map(av[1], &map);
	map.scale = 0;
	display_map(map);
	return (0);
}
