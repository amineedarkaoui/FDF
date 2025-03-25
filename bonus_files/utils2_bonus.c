/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:39:53 by aedarkao          #+#    #+#             */
/*   Updated: 2025/03/25 13:40:35 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	copy_array(t_point *array, int size, t_point *copy)
{
	int	i;

	i = 0;
	while (i < size)
	{
		copy[i] = array[i];
		i++;
	}
}

int	is_greater(int a, int b)
{
	if (a > b)
		return (1);
	else
		return (-1);
}
