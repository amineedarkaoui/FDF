/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:16:52 by aedarkao          #+#    #+#             */
/*   Updated: 2025/01/30 20:06:39 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

unsigned char	get_color(int rgb, char color)
{
	if (color == 'r')
		return (((unsigned char *)&rgb)[2]);
	else if (color == 'g')
		return (((unsigned char *)&rgb)[1]);
	else
		return (((unsigned char *)&rgb)[0]);
}

void	get_color_distance(int color1, int color2, int distance[3])
{
	distance[0] = get_color(color1, 'r') - get_color(color2, 'r');
	distance[1] = get_color(color1, 'g') - get_color(color2, 'g');
	distance[2] = get_color(color1, 'b') - get_color(color2, 'b');
}

int	gcolor(int d, int index, int color1, int color2)
{
	int	r;
	int	g;
	int	b;
	int	distance[3];

	get_color_distance(color1, color2, distance);
	r = get_color(color1, 'r') - ((double)distance[0] / d) * index;
	g = get_color(color1, 'g') - ((double)distance[1] / d) * index;
	b = get_color(color1, 'b') - ((double)distance[2] / d) * index;
	return (r << 16 | g << 8 | b);
}
