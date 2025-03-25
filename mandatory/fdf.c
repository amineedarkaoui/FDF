/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 05:19:31 by aedarkao          #+#    #+#             */
/*   Updated: 2025/03/25 12:37:03 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
