/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:23:19 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hittable.h"

void	ft_set_face_normal(t_hit_rec *rec, t_ray *r, t_vec3 *outward_normal)
{
	if (ft_vec_dot(r->dir, *outward_normal) < 0)
		rec->front_face = 1;
	else
		rec->front_face = 0;
	if (rec->front_face == 1)
		rec->normal = *outward_normal;
	else
		rec->normal = ft_vec_mul_f(-1, *outward_normal);
}

void	ft_set_hit_rec_color(t_hit_rec *rec, t_color color)
{
	rec->color = color;
}

void	ft_reset_hit_rec(t_hit_rec *rec)
{
	rec->p = ft_vec_set_xyz(0, 0, 0);
	rec->normal = ft_vec_set_xyz(0, 0, 0);
	rec->t = 0;
	rec->front_face = 0;
	rec->color = ft_vec_set_xyz(0, 0, 0);
}
