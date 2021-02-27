/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 22:41:59 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/27 17:42:05 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "vec.h"
#include <math.h>
#include <stdio.h>

const float	g_pi = 3.1415926535897932385;
/* *********************************** 수정 ********************************* */
//t_camera	*ft_camera_set(t_camera *cam, t_point3 lookfrom, t_point3 lookat,
//							t_vec3 vup, float vfov, float aspect_ratio)
//{
//	float		theta;
//	float		h;
//	float		viewport_height;
//	float		viewport_width;
//
//	theta = ft_degrees_to_radians(vfov);
//	h = tan(theta / 2);
//	viewport_height = 2.0 * h;
//	viewport_width = aspect_ratio * viewport_height;
//	cam->w = ft_vec_unit_vec(ft_vec_sub(lookfrom, lookat));
//	cam->u = ft_vec_unit_vec(ft_vec_cross(vup, cam->w));
//	cam->v = ft_vec_cross(cam->w, cam->u);
//	cam->origin = ft_vec_set_xyz(lookfrom.x, lookfrom.y, lookfrom.z);
//	cam->horizontal = ft_vec_mul_f(viewport_width, cam->u);
//	cam->vertical = ft_vec_mul_f(viewport_height, cam->v);
//	cam->lower_left_corner = ft_vec_set_xyz(
//		cam->origin.x - cam->horizontal.x / 2 - cam->vertical.x / 2 - cam->w.x,
//		cam->origin.y - cam->horizontal.y / 2 - cam->vertical.y / 2 - cam->w.y,
//		cam->origin.z - cam->horizontal.z / 2 - cam->vertical.z / 2 - cam->w.z);
//	return (cam);
//}

void		ft_camera_set(t_camera *cam, t_point3 pos, t_vec3 dir, float vfov)
{
	t_cam_data	cam_data;

	cam_data.aspect_ratio = 16.0 / 9.0;
	cam_data.vup = ft_vec_set_xyz(0, 1, 0);
	cam_data.theta = ft_degrees_to_radians(vfov);
	cam_data.h = tan(cam_data.theta / 2);
	cam_data.viewport_h = 2.0 * cam_data.h;
	cam_data.viewport_w = cam_data.aspect_ratio * cam_data.viewport_h;
	cam->w = ft_vec_unit_vec(ft_vec_mul_f(-1, dir));
	cam->u = ft_vec_unit_vec(ft_vec_cross(cam_data.vup, cam->w));
	cam->v = ft_vec_cross(cam->w, cam->u);
	cam->origin = pos;
	cam->dir = dir;
	cam->horizontal = ft_vec_mul_f(cam_data.viewport_w, cam->u);
	cam->vertical = ft_vec_mul_f(cam_data.viewport_h, cam->v);
	cam->lower_left_corner = ft_vec_set_xyz(
		cam->origin.x - cam->horizontal.x / 2 - cam->vertical.x / 2 - cam->w.x,
		cam->origin.y - cam->horizontal.y / 2 - cam->vertical.y / 2 - cam->w.y,
		cam->origin.z - cam->horizontal.z / 2 - cam->vertical.z / 2 - cam->w.z);
}
/* ************************************************************************** */

t_ray		ft_camera_get_ray(t_camera cam, float u, float v)
{
	t_vec3	dir;

	dir.x = cam.lower_left_corner.x + u * cam.horizontal.x
			+ v * cam.vertical.x - cam.origin.x;
	dir.y = cam.lower_left_corner.y + u * cam.horizontal.y
			+ v * cam.vertical.y - cam.origin.y;
	dir.z = cam.lower_left_corner.z + u * cam.horizontal.z
			+ v * cam.vertical.z - cam.origin.z;
	return (ft_ray_set(cam.origin, ft_vec_unit_vec(dir)));
}

float		ft_degrees_to_radians(float degrees)
{
	return (degrees * g_pi / 180.0);
}
