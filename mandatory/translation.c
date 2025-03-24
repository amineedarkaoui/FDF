/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:01:35 by aedarkao          #+#    #+#             */
/*   Updated: 2025/01/30 15:28:40 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_map(t_map map, int x, int y)
{
	int	i;

	i = 0;
	while (i < map.w * map.h)
	{
		map.v[i].x += x;
		map.v[i].y += y;
		i++;
	}
}

void	translate_center(t_map map)
{
	t_point	center;

	center = get_map_center(map);
	translate_map(map, W_W / 2 - center.x, W_H / 2 - center.y);
}
