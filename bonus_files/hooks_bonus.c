/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:33:58 by aedarkao          #+#    #+#             */
/*   Updated: 2025/03/25 13:56:46 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	change_z(t_vars *v, double n)
{
	int	i;

	i = 0;
	while (i < v->m.w * v->m.h)
	{
		v->m.v[i].y *= n;
		i++;
	}
}

void	reset_map(t_vars *v)
{
	int	i;

	v->perspective = 0;
	v->t = (t_point){0, 0, 0, 0, 0};
	v->angles = (t_angles){0.615472907, 0.785398, 0};
	v->m.scale = 0;
	i = 0;
	while (i < v->m.h * v->m.w)
	{
		v->m.v[i].y = v->m.v[i].y0;
		i++;
	}
}

int	key_hook2(int keycode, t_vars *v)
{
	if (keycode == 100)
		v->t.x += 10;
	else if (keycode == 97)
		v->t.x -= 10;
	else if (keycode == 91)
		change_z(v, 0.95);
	else if (keycode == 93)
		change_z(v, 1.05);
	else if (keycode == 112)
		v->perspective++;
	else if (keycode == 114)
		reset_map(v);
	else if (keycode == 102)
		v->angles = (t_angles){MATH_PI / 2, 0, 0};
	return (0);
}

int	key_hook(int keycode, t_vars *v)
{
	if (keycode == 65307)
		clean_n_quit(v);
	else if (keycode == 65362)
		v->angles.x -= 0.03;
	else if (keycode == 65364)
		v->angles.x += 0.03;
	else if (keycode == 65365)
		v->angles.z += 0.03;
	else if (keycode == 65366)
		v->angles.z -= 0.03;
	else if (keycode == 65361)
		v->angles.y += 0.03;
	else if (keycode == 65363)
		v->angles.y -= 0.03;
	else if (keycode == 61)
		v->m.scale += 0.1 * v->m.scale0;
	else if (keycode == 45 && (v->m.scale + v->m.scale0) >= 0.1 * v->m.scale0)
		v->m.scale -= 0.1 * v->m.scale0;
	else if (keycode == 119)
		v->t.y -= 10;
	else if (keycode == 115)
		v->t.y += 10;
	else
		key_hook2(keycode, v);
	return (0);
}

int	button_hook(t_vars *vars)
{
	clean_n_quit(vars);
	return (0);
}
