/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aedarkao <aedarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:44:40 by aedarkao          #+#    #+#             */
/*   Updated: 2025/03/25 13:49:15 by aedarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"

# define W_W 1920
# define W_H 1020
# define MATH_PI 3.14
# define MAX_COLOR	0xff4400
# define MIN_COLOR	0x00a2ff

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		e;
}	t_img;

typedef struct s_point {
	int	x;
	int	y;
	int	z;
	int	c;
	int	y0;
}	t_point;

typedef struct s_angles {
	double	x;
	double	y;
	double	z;
}	t_angles;

typedef struct s_map {
	int		w;
	int		h;
	double	scale;
	double	scale0;
	t_point	*v;
}	t_map;

typedef struct s_line_vars {
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
	int	i;
}	t_line_vars;

typedef struct s_vars
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_map		m;
	t_angles	angles;
	t_point		*v0;
	t_point		t;
	t_point		center;
	int			s_flag;
	double		offset;
	int			perspective;
}	t_vars;

typedef struct s_read_vars
{
	int		i;
	int		j;
	char	**row;
	char	*gnl;
	int		fd;
	int		is_colored;
	int		count;
}	t_read_vars;

void	read_map(char *filename, t_map *map);
void	translate_center(t_vars *v);
void	translate_map(t_vars v, int x, int y, int z);
void	rotate_x(t_vars v, double angle);
void	rotate_y(t_vars v, double angle);
void	rotate_z(t_vars v, double angle);
int		max_int(int a, int b);
int		min_int(int a, int b);
void	draw_l(t_img *img, t_point a, t_point b);
void	my_pixel_put(t_img *data, int x, int y, int color);
int		gcolor(int d, int index, int color1, int color2);
void	get_color_distance(int color1, int color2, int distance[3]);
void	isometric(t_map map);
void	scale_map(t_vars *v);
t_point	get_map_center(t_vars v);
t_point	get_map_min(t_vars v);
t_point	get_map_max(t_vars v);
t_point	get_array_min(t_point *v, t_map map);
t_point	get_array_max(t_point *v, t_map map);
void	dynamic_scale(t_vars *v);
int		key_hook(int keycode, t_vars *vars);
int		button_hook(t_vars *vars);
void	clean_n_quit(t_vars *vars);
void	free_split(char ***strs);
void	copy_array(t_point *array, int size, t_point *copy);
int		show_map(t_vars *v);
void	draw_map(t_vars v);
void	perspective(t_vars v);
int		is_greater(int a, int b);

#endif
