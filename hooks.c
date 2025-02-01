/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:33:58 by aedarkao          #+#    #+#             */
/*   Updated: 2025/01/30 21:21:29 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		clean_n_quit(vars);
	return (0);
}

int	button_hook(t_vars *vars)
{
	clean_n_quit(vars);
	return (0);
}
