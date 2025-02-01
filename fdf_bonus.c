/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:44:28 by aedarkao          #+#    #+#             */
/*   Updated: 2025/02/01 17:12:14 by aedarkao         ###   ########.fr       */
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

void	perspective(t_map map)
{
	int	i;
	//int	min;

	// min = map.v[0].z;
	// i = 0;
	// while (i < map.w * map.h)
	// {
	// 	min = min_int(min, map.v[i].z);
	// 	i++;
	// }
	// if (min <= 0)
	// {
	// 	i = 0;
	// 	while (i < map.w * map.h)
	// 	{
	// 		map.v[i].z += abs(min) + 100;
	// 		i++;
	// 	}
	// }
	i = 0;
	while (i < map.w * map.h)
	{
		if (map.v[i].z != 0)
		{
			map.v[i].x = (map.v[i].x * 0.00000001) / map.v[i].z;
			map.v[i].y = (map.v[i].y * 0.00000001) / map.v[i].z;
		}
		else
		{
			map.v[i].x = map.v[i].x / 0.1;
			map.v[i].y = map.v[i].y / 0.1;
		}
		i++;
	}
}

int	animate_map(t_vars *v)
{
	int	i;
	//int	sleep_flag = 0;

	// printf("%d, %d\n", v->v0[41].yf, v->v0[41].y);
	// printf("%d, %d\n===========\n", v->map.v[41].yf, v->map.v[41].y);
	ft_bzero(v->img.addr, v->img.ll * W_H);
	i = 0;
	while (i < v->map.w * v->map.h)
	{
		if (v->v0[i].y < v->map.v[i].yf)
		{
			// printf("1------\n");
			v->v0[i].y++;
			//sleep_flag = 1;
		}
		else if (v->v0[i].y > v->map.v[i].yf)
		{
			// printf("2-----\n");
			v->v0[i].y--;
			//sleep_flag = 1;
		}
		i++;
	}
	// if (sleep_flag)
	// 	usleep(log(log(log(max_int(get_array_max(v->v0, v->map).yf, abs(get_array_min(v->v0, v->map).yf))))) * 1000);
	rotate_y(*v, v->angles.y);
	rotate_x(*v, v->angles.x);
	rotate_z(*v, v->angles.z);
	copy_array(v->map.v, v->map.h * v->map.w, v->v1);
	//perspective(v->map);
	dynamic_scale(v);
	translate_center(*v);
	translate_map(v->map, v->t.x, v->t.y);
	draw_map(&v->img, v->map);
	mlx_put_image_to_window(v->mlx, v->mlx_win, v->img.img, 0, 0);
	return (0);
}

void	display_map(t_map map)
{
	t_vars	v;

	v.s_flag = 0;
	v.t = (t_point){0, 0, 0, 0, 0};
	v.v0 = malloc(map.h * map.w * sizeof(t_point));
	v.v1 = malloc(map.h * map.w * sizeof(t_point));
	copy_array(map.v, map.w * map.h, v.v0);
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
