/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:33:58 by aedarkao          #+#    #+#             */
/*   Updated: 2025/03/24 11:58:50 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

// void	change_z(t_vars *v, int n)
// {
// 	int	i;

// 	i = 0;
// 	while (i < v->map.w * v->map.h)
// 	{
// 		v->map.v[i].y *= n;
// 		i++;
// 	}
// }

int	key_hook(int keycode, t_vars *v)
{
	if (keycode == 65307)
		clean_n_quit(v);
	if (keycode == 65362)
		v->angles.x += 0.01;
	if (keycode == 65364)
		v->angles.x -= 0.01;
	if (keycode == 65365)
		v->angles.z += 0.01;
	if (keycode == 65366)
		v->angles.z -= 0.01;
	if (keycode == 65361)
		v->angles.y -= 0.01;
	if (keycode == 65363)
		v->angles.y += 0.01;
	if (keycode == 61)
		v->map.scale += 0.01;
	if (keycode == 45 && (v->map.scale + v->map.scale0) >= 0.01)
		v->map.scale -= 0.01;
	if (keycode == 119)
		v->t.y -= 10;
	if (keycode == 115)
		v->t.y += 10;
	if (keycode == 100)
		v->t.x += 10;
	if (keycode == 97)
		v->t.x -= 10;
	// if (keycode == 91)
	// 	change_z(v, 0.9);
	// if (keycode == 93)
	// 	change_z(v, 1.1);
	if (keycode == 112)
		v->perspective++;
	if (keycode == 114)
	{
		v->perspective = 0;
		v->t = (t_point){0, 0, 0, 0};
		v->angles = (t_angles){0.615472907, 0.785398, 0};
		v->map.scale = 0;
	}
	if (keycode == 102)
		v->angles = (t_angles){3.14 / 2, 0, 0};
	return (0);
}

int	button_hook(t_vars *vars)
{
	clean_n_quit(vars);
	return (0);
}
