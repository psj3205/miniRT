/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:50:12 by sejpark           #+#    #+#             */
/*   Updated: 2020/11/28 16:35:08 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "vec3.h"
#include "ray.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define	UP			126
#define	DOWN		125
#define	LEFT		123
#define	RIGHT		124
#define	W			13
#define	S			1
#define	A			0
#define	D			2
#define ESC			53
#define KeyPress	2
#define KeyRelease	3

typedef struct 	s_data
{
	void		*mlx;
	void		*mlx_win;
	float		aspect_ratio;
	int			width, height;
	int			x, y, z;
	int			up, down, left, right, forward, backward, r_rotate, l_rotate;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_camera
{
	float		viewport_height;
	float		viewport_width;
	float		focal_length;
	t_point3	origin;
	t_vec3		horizontal;
	t_vec3		vertical;
	t_vec3		lower_left_corner;
	float		angle;
}				t_camera;

typedef struct	s_engine
{
	t_data		data;
	t_camera	cam;
}				t_engine;

void            my_mlx_pixel_put(t_data *data, int x, int y, t_vec3 *color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = create_trgb(0,
									255.999 * color->x,
									255.999 * color->y,
									255.999 * color->z);
}

int				ft_move(t_data *data, t_camera *cam)
{
//	printf("left = %d, right = %d, up = %d, down = %d, for = %d, back = %d\n", data->left, data->right, data->up, data->down, data->forward, data->backward);
//	printf("r_rotate = %d, l_rotate = %d\n", data->r_rotate, data->l_rotate);
	if (data->left == 1)
	{
		cam->origin.x -= 0.1;
		printf("x = %f, y= %f z = %f angle = %f\n", cam->origin.x, cam->origin.y, cam->origin.z, cam->angle);
	}
	if (data->right == 1)
	{
		cam->origin.x += 0.1;
		printf("x = %f, y= %f z = %f angle = %f\n", cam->origin.x, cam->origin.y, cam->origin.z, cam->angle);
	}
	if (data->up == 1)
	{
		cam->origin.y += 0.1;
		printf("x = %f, y= %f z = %f angle = %f\n", cam->origin.x, cam->origin.y, cam->origin.z, cam->angle);
	}
	if (data->down == 1)
	{
		cam->origin.y -= 0.1;
		printf("x = %f, y= %f z = %f angle = %f\n", cam->origin.x, cam->origin.y, cam->origin.z, cam->angle);
	}
	if (data->forward == 1)
	{
		cam->origin.z -= 0.1;
		printf("x = %f, y= %f z = %f angle = %f\n", cam->origin.x, cam->origin.y, cam->origin.z, cam->angle);
	}
	if (data->backward == 1)
	{
		cam->origin.z += 0.1;
		printf("x = %f, y= %f z = %f angle = %f\n", cam->origin.x, cam->origin.y, cam->origin.z, cam->angle);
	}
	if (data->r_rotate == 1)
	{
		cam->angle += 1.0;
		printf("x = %f, y= %f z = %f angle = %f\n", cam->origin.x, cam->origin.y, cam->origin.z, cam->angle);
	}
	if (data->l_rotate == 1)
	{
		cam->angle -= 1.0;
		printf("x = %f, y= %f z = %f angle = %f\n", cam->origin.x, cam->origin.y, cam->origin.z, cam->angle);
	}
	return (0);
}

int				ft_key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if (keycode == LEFT)
		data->left = 1;
	if (keycode == RIGHT)
		data->right = 1;
	if (keycode == UP)
		data->up = 1;
	if (keycode == DOWN)
		data->down = 1;
	if (keycode == W)
		data->forward = 1;
	if (keycode == S)
		data->backward = 1;
	if (keycode == A)
		data->l_rotate = 1;
	if (keycode == D)
		data->r_rotate = 1;
	return (0);
}

int				ft_key_release(int keycode, t_data *data)
{
	if (keycode == LEFT)
		data->left = 0;
	if (keycode == RIGHT)
		data->right = 0;
	if (keycode == UP)
		data->up = 0;
	if (keycode == DOWN)
		data->down = 0;
	if (keycode == W)
		data->forward = 0;
	if (keycode == S)
		data->backward = 0;
	if (keycode == A)
		data->l_rotate = 0;
	if (keycode == D)
		data->r_rotate = 0;
	return (0);
}

float			ft_hit_sphere(t_point3 *center, float radius, t_ray *r)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	ft_vec3_sub(&oc, &(r->orig), center);
	a = ft_vec3_dot(&(r->dir), &(r->dir));
	b = 2.0 * ft_vec3_dot(&oc, &(r->dir));
	c = ft_vec3_dot(&oc, &oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
}

t_color			*ft_ray_color(t_color *target, t_ray *r)
{
	t_vec3		unit_dir;
	float		t;
	t_color		cal1;
	t_color		cal2;
	t_point3	sp_center;
	t_vec3		normal_vec;
	t_vec3		ray_at;

	t = ft_hit_sphere(ft_vec3_set_xyz(&sp_center, 0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		ft_ray_at(&ray_at, r, t);
		ft_vec3_set_xyz(&normal_vec, 0, 0, -1);
		ft_vec3_sub(&normal_vec, &ray_at, &normal_vec);
		ft_vec3_unit_vec(&normal_vec, &normal_vec);
		target->x = 0.5 * (normal_vec.x + 1);
		target->y = 0.5 * (normal_vec.y + 1);
		target->z = 0.5 * (normal_vec.z + 1);
		return (target);
	}
	ft_vec3_unit_vec(&unit_dir, &(r->dir));
	t = 0.5 * (unit_dir.y + 1.0);
	ft_vec3_multi_float(&cal1, (1.0 - t),
									ft_vec3_set_xyz(&cal1, 1.0, 1.0, 1.0));
	ft_vec3_multi_float(&cal2, t, ft_vec3_set_xyz(&cal2, 0.5, 0.7, 1.0));
	return (ft_vec3_add(target, &cal1, &cal2));
}

void			ft_camera_set(t_camera *cam, float aspect_ratio)
{
	cam->viewport_height = 2.0;
	cam->viewport_width = aspect_ratio * cam->viewport_height;
	cam->focal_length = 1.0;
//	ft_vec3_set_xyz(&cam->origin, 0.0, 0.0, 0.0);
	ft_vec3_set_xyz(&cam->horizontal, cam->viewport_width, 0.0, 0.0);
	ft_vec3_set_xyz(&cam->vertical, 0.0, cam->viewport_height, 0.0);
	cam->lower_left_corner.x = cam->origin.x
								- (cam->horizontal.x / 2)
								- (cam->vertical.x / 2) - 0; 
	cam->lower_left_corner.y = cam->origin.y
								- (cam->horizontal.y / 2)
								- (cam->vertical.y / 2) - 0; 
	cam->lower_left_corner.z = cam->origin.z
								- (cam->horizontal.z / 2)
								- (cam->vertical.z / 2)
								- cam->focal_length; 
// 각도 조절
//	cam->horizontal.x = cam->horizontal.x * cos(3.14 * cam->angle / 180.0) - cam->horizontal.z * sin(3.14 * cam->angle / 180.0);
//	cam->horizontal.z = cam->horizontal.x * sin(3.14 * cam->angle / 180.0) + cam->horizontal.z * cos(3.14 * cam->angle / 180.0);
//	cam->vertical.x = cam->vertical.x * cos(3.14 * cam->angle / 180.0) - cam->vertical.z * sin(3.14 * cam->angle / 180.0);
//	cam->vertical.z = cam->vertical.x * sin(3.14 * cam->angle / 180.0) + cam->vertical.z * cos(3.14 * cam->angle / 180.0);
////
}

t_ray			*ft_camera_cal_ray(t_ray *target, t_camera *cam,
															float u, float v)
{
	t_vec3 cal;

	cal.x = cam->lower_left_corner.x
			+ u * cam->horizontal.x
			+ v * cam->vertical.x
			- cam->origin.x;
	cal.y = cam->lower_left_corner.y
			+ u * cam->horizontal.y
			+ v * cam->vertical.y
			- cam->origin.y;
	cal.z = cam->lower_left_corner.z
			+ u * cam->horizontal.z
			+ v * cam->vertical.z
			- cam->origin.z;
	return (ft_ray_set(target, &(cam->origin), &cal));
}

int				ft_draw(t_data *data, t_camera *cam)
{
	int		i;
	int		j;
	t_vec3	color;
	t_ray	r;

	j = data->height - 1;
	while (j >= 0)
	{
		i = 0;
		ft_putstr_fd("\rScanlines remaining: ", 1);
		ft_putnbr_fd(j, 1);
		ft_putchar_fd(' ', 1);
		while (i < data->width)
		{
			ft_camera_cal_ray(&r, cam,
								(float)i / (data->width - 1),
								(float)j / (data->height - 1));
			ft_ray_color(&color, &r);
			my_mlx_pixel_put(data, i, data->height - 1 - j, &color);
			i++;
		}
		j--;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

int main_loop(t_engine *engine)
{
	ft_camera_set(&engine->cam, engine->data.aspect_ratio);
	ft_draw(&engine->data, &engine->cam);
	ft_move(&engine->data, &engine->cam);
	return (0);
}

int	main(void)
{
	t_engine	engine;

	engine.data.aspect_ratio = 16.0 / 9.0;
	engine.data.width = 600;
	engine.data.height = (int)(engine.data.width / engine.data.aspect_ratio);
	engine.data.right = 0;
	engine.data.left = 0;
	engine.data.up = 0;
	engine.data.down = 0;
	engine.data.forward = 0;
	engine.data.backward = 0;
	engine.data.r_rotate = 0;
	engine.data.l_rotate = 0;

	ft_vec3_set_xyz(&engine.cam.origin, 0.0, 0.0, 0.0);
	engine.data.mlx = mlx_init();
	engine.data.mlx_win = mlx_new_window(engine.data.mlx, engine.data.width, engine.data.height, "miniRT");
	engine.data.img = mlx_new_image(engine.data.mlx, engine.data.width, engine.data.height);
	engine.data.addr = mlx_get_data_addr(engine.data.img, &engine.data.bits_per_pixel, &engine.data.line_length, &engine.data.endian);

	mlx_hook(engine.data.mlx_win, 2, 1L<<0, ft_key_press, &engine.data);
	mlx_hook(engine.data.mlx_win, 3, 1L<<1, ft_key_release, &engine.data);
	mlx_loop_hook(engine.data.mlx, main_loop, &engine);
	mlx_loop(engine.data.mlx);
	return (0);
}
