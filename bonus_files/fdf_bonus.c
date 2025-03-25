/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:44:28 by aedarkao          #+#    #+#             */
/*   Updated: 2025/03/25 13:51:14 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	show_map(t_vars *v)
{
	t_point	map_center;

	ft_bzero(v->img.addr, v->img.ll * W_H);
	copy_array(v->m.v, v->m.w * v->m.h, v->v0);
	map_center = get_map_center(*v);
	translate_map(*v, -map_center.x, -map_center.y, -map_center.z);
	rotate_y(*v, v->angles.y);
	rotate_x(*v, v->angles.x);
	rotate_z(*v, v->angles.z);
	translate_map(*v, map_center.x, map_center.y, map_center.z);
	map_center = get_map_center(*v);
	translate_map(*v, -map_center.x, -map_center.y, 0);
	if (v->perspective % 2 == 1)
		perspective(*v);
	dynamic_scale(v);
	translate_center(v);
	translate_map(*v, v->t.x, v->t.y, 0);
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
	v.angles = (t_angles){0.615472907, MATH_PI / 4, 0};
	v.m = map;
	v.mlx = mlx_init();
	v.mlx_win = mlx_new_window(v.mlx, W_W, W_H, "FDF");
	v.img.img = mlx_new_image(v.mlx, W_W, W_H);
	v.img.addr = mlx_get_data_addr(v.img.img, &v.img.bpp, &v.img.ll, &v.img.e);
	printf("%d\n", v.img.bpp);
	mlx_hook(v.mlx_win, 2, 1L << 0, key_hook, &v);
	mlx_hook(v.mlx_win, 17, 0, button_hook, &v);
	mlx_loop_hook(v.mlx, show_map, &v);
	mlx_loop(v.mlx);
}

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
	{
		ft_putstr_fd("Error: Invalid number of args!\n", 2);
		return (1);
	}
	read_map(av[1], &map);
	map.scale = 0;
	display_map(map);
	return (0);
}
