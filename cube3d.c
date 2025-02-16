#include <stdlib.h>
#include <mlx.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>

#define W_W 1920
#define W_H 1020

typedef struct s_point {
	int	x;
	int	y;
	int	yf;
	int	z;
	int	c;
}	t_point;

typedef struct s_angles {
	double	x;
	double	y;
	double	z;
}	t_angles;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		e;
}	t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_point		*cube;
	t_angles	angles;
	double		scale;
}	t_vars;

typedef struct s_line_vars {
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
	int	i;
}	t_line_vars;

void	rotate_x(t_point cube[8], double angle)
{
	int	i;
	int	y;
	int	z;

	i = 0;
	while (i < 8)
	{
		y = cos(angle) * cube[i].y - sin(angle) * cube[i].z;
		z = sin(angle) * cube[i].y + cos(angle) * cube[i].z;
		cube[i].y = y;
		cube[i].z = z;
		i++;
	}
}

void	rotate_y(t_point cube[8], double angle)
{
	int	i;
	int	x;
	int	z;

	i = 0;
	while (i < 8)
	{
		x = cos(angle) * cube[i].x + sin(angle) * cube[i].z;
		z = -sin(angle) * cube[i].x + cos(angle) * cube[i].z;
		cube[i].x = x;
		cube[i].z = z;
		i++;
	}
}

void	rotate_z(t_point cube[8], double angle)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < 8)
	{
		x = cos(angle) * cube[i].x - sin(angle) * cube[i].y;
		y = sin(angle) * cube[i].x + cos(angle) * cube[i].y;
		cube[i].x = x;
		cube[i].y = y;
		i++;
	}
}

int	are_coords_valid(int x, int y)
{
	int	c1;
	int	c2;

	c1 = (x < W_W && x >= 0);
	c2 = (y < W_H && y >= 0);
	return (c1 && c2);
}

void	my_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (are_coords_valid(x, y))
	{
		dst = data->addr + (y * data->ll + x * (data->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

int	is_greater(int a, int b)
{
	if (a > b)
		return (1);
	else
		return (-1);
}

void	draw_l(t_img *img, t_point a, t_point b)
{
	t_line_vars	v;

	v.dx = abs(b.x - a.x);
	v.dy = abs(b.y - a.y);
	v.sx = is_greater(b.x, a.x);
	v.sy = is_greater(b.y, a.y);
	v.err = v.dx - v.dy;
	v.i = 0;
	while (a.x != b.x || a.y != b.y)
	{
		my_pixel_put(img, a.x, a.y, a.c);
		v.err2 = 2 * v.err;
		if (v.err2 > -v.dy)
		{
			v.err -= v.dy;
			a.x += v.sx;
		}
		if (v.err2 < v.dx)
		{
			v.err += v.dx;
			a.y += v.sy;
		}
		v.i++;
	}
	my_pixel_put(img, b.x, b.y, a.c);
}

void	draw_cube(t_img *img, t_point cube[8])
{
	draw_l(img, cube[0], cube[1]);
	draw_l(img, cube[1], cube[2]);
	draw_l(img, cube[2], cube[3]);
	draw_l(img, cube[3], cube[0]);
	draw_l(img, cube[4], cube[5]);
	draw_l(img, cube[5], cube[6]);
	draw_l(img, cube[6], cube[7]);
	draw_l(img, cube[7], cube[4]);
	draw_l(img, cube[0], cube[4]);
	draw_l(img, cube[1], cube[5]);
	draw_l(img, cube[2], cube[6]);
	draw_l(img, cube[3], cube[7]);
}

int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	min_int(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

t_point	get_cube_min(t_point cube[8])
{
	t_point	min;
	int		i;

	min.x = cube[0].x;
	min.y = cube[0].y;
	min.z = cube[0].z;
	i = 0;
	while (i < 8)
	{
		min.x = min_int(min.x, cube[i].x);
		min.y = min_int(min.y, cube[i].y);
		min.z = min_int(min.z, cube[i].z);
		i++;
	}
	return (min);
}

t_point	get_cube_max(t_point cube[8])
{
	t_point	max;
	int		i;

	max.x = cube[0].x;
	max.y = cube[0].y;
	max.z = cube[0].z;
	i = 0;
	while (i < 8)
	{
		max.x = max_int(max.x, cube[i].x);
		max.y = max_int(max.y, cube[i].y);
		max.z = max_int(max.z, cube[i].z);
		i++;
	}
	return (max);
}

t_point	get_cube_center(t_point cube[8])
{
	t_point	max;
	t_point	min;

	min = get_cube_min(cube);
	max = get_cube_max(cube);
	return ((t_point){(max.x + min.x) / 2, (max.y + min.y) / 2, 0, (max.z + min.z) / 2, 0});
}

void	translate_cube(t_point cube[8], int x, int y, int z)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		cube[i].x += x;
		cube[i].y += y;
		cube[i].z += z;
		i++;
	}
}

void	translate_center(t_point cube[8])
{
	t_point	center;

	center = get_cube_center(cube);
	translate_cube(cube, W_W / 2 - center.x, W_H / 2 - center.y, 0);
}

void perspective(t_point cube[8])
{
	double	angle = 3.14 / 150.0;
	double	f = 1 / tan(angle / 2);
	for (int i = 0; i < 8; i++)
	{
		if (cube[i].z >= f)
		{
			cube[i].x = (double)(cube[i].x * f) / cube[i].z;
			cube[i].y = (double)(cube[i].y * f) / cube[i].z;
		}
	}
}

void	scale_cube(t_vars *v)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		v->cube[i].x = v->scale * v->cube[i].x;
		v->cube[i].y = v->scale * v->cube[i].y;
		v->cube[i].z = v->scale * v->cube[i].z;
		i++;
	}
}

double	min_double(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	dynamic_scale(t_vars *v)
{
	t_point	min;
	t_point	max;
	int		dx;
	int		dy;

	min = get_cube_min(v->cube);
	max = get_cube_max(v->cube);
	dx = max.x - min.x;
	dy = max.y - min.y;
	v->scale = min_double((0.3 * W_W) / dx, (0.3 * W_H) / dy);
	scale_cube(v);
}

int	animate_cube(t_vars *v)
{
	bzero(v->img.addr, v->img.ll * W_H);
	t_point new_cube[8];
	for (int i = 0; i < 8; i++)
		new_cube[i] = v->cube[i];
	t_point cube_center = get_cube_center(new_cube);
	translate_cube(new_cube, -cube_center.x, -cube_center.y, -cube_center.z);
	rotate_y(new_cube, v->angles.y);
	rotate_x(new_cube, v->angles.x);
	rotate_z(new_cube, v->angles.z);
	translate_cube(new_cube, cube_center.x, cube_center.y, cube_center.z);
	translate_cube(new_cube, -cube_center.x, -cube_center.y, 0);
	//dynamic_scale(v);
	perspective(new_cube);
	translate_cube(new_cube, 950, 500, 0);
	//translate_center(new_cube);
	draw_cube(&v->img, new_cube);
	mlx_put_image_to_window(v->mlx, v->mlx_win, v->img.img, 0, 0);
	v->angles.y -= 0.001;
	//v->angles.x += 0.0005;
	//usleep(100000);
	return (0);
}

void	display_cube(t_point cube[8])
{
	t_vars	v;

	v.mlx = mlx_init();
	v.cube = cube;
	v.angles = (t_angles){0, 0, 0};
	v.mlx_win = mlx_new_window(v.mlx, W_W, W_H, "FDF");
	v.img.img = mlx_new_image(v.mlx, W_W, W_H);
	v.img.addr = mlx_get_data_addr(v.img.img, &v.img.bpp, &v.img.ll, &v.img.e);
	mlx_loop_hook(v.mlx, animate_cube, &v);
	mlx_loop(v.mlx);
}

int main()
{
	t_point cube[8];
	int		d = 0;
	int		v = 1000;
	int		z = 400;

	cube[0] = (t_point){d+0, d+0, 0, d+0+z, 0xFF0000};
	cube[1] = (t_point){d+0, d+0, 0, d+v+z, 0xFF0000};
	cube[2] = (t_point){d+v, d+0, 0, d+v+z, 0xFF0000};
	cube[3] = (t_point){d+v, d+0, 0, d+0+z, 0xFF0000};
	cube[4] = (t_point){d+0, d+v, 0, d+0+z, 0xFF0000};
	cube[5] = (t_point){d+0, d+v, 0, d+v+z, 0xFF0000};
	cube[6] = (t_point){d+v, d+v, 0, d+v+z, 0xFF0000};
	cube[7] = (t_point){d+v, d+v, 0, d+0+z, 0xFF0000};
	display_cube(cube);

	return 0;
}
