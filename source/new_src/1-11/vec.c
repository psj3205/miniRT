/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:48:09 by sejpark           #+#    #+#             */
/*   Updated: 2021/02/27 17:27:26 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include <math.h>

t_vec3	ft_vec_add(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.x + v.x, u.y + v.y, u.z + v.z});
}

t_vec3	ft_vec_sub(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.x - v.x, u.y - v.y, u.z - v.z});
}

t_vec3	ft_vec_mul(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.x * v.x, u.y * v.y, u.z * v.z});
}

t_vec3	ft_vec_div(const t_vec3 u, const t_vec3 v)
{
	return ((t_vec3){u.x / v.x, u.y / v.y, u.z / v.z});
}

t_vec3	ft_vec_mul_f(const float t, const t_vec3 v)
{
	return ((t_vec3){v.x * t, v.y * t, v.z * t});
}

t_vec3	ft_vec_div_f(const float t, const t_vec3 v)
{
	return (ft_vec_mul_f(1 / t, v));
}

float	ft_vec_dot(const t_vec3 u, const t_vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	ft_vec_cross(const t_vec3 u, const t_vec3 v)
{
	t_vec3 result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;
	return (result);
}

float	ft_vec_len(const t_vec3 v)
{
	return (sqrt(ft_vec_sqr_len(v)));
}

float	ft_vec_sqr_len(const t_vec3 v)
{
	return (pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0));
}

t_vec3	ft_vec_unit_vec(const t_vec3 v)
{
	return (ft_vec_div_f(ft_vec_len(v), v));
}

t_vec3	ft_vec_set_xyz(const float x, const float y, const float z)
{
	return ((t_vec3){x, y, z});
}

int		create_trgb(const int t, const int r, const int g, const int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}