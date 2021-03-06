/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:45:01 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 19:48:29 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/triangle.h"
#include <math.h>

t_triangle	ft_triangle_set(t_point3 p0, t_point3 p1, t_point3 p2,
															t_color color)
{
	t_triangle	tr;

	tr.pos.p0 = p0;
	tr.pos.p1 = p1;
	tr.pos.p2 = p2;
	tr.tr_plane.center = p0;
	tr.tr_plane.color = color;
	tr.tr_plane.norm = ft_vec_unit_vec(
			ft_vec_cross(ft_vec_sub(p1, p0), ft_vec_sub(p2, p0)));
	tr.edge.edge0 = ft_vec_sub(p1, p0);
	tr.edge.edge1 = ft_vec_sub(p2, p1);
	tr.edge.edge2 = ft_vec_sub(p0, p2);
	return (tr);
}

void		ft_triangle_set_c(t_triangle *tr, t_point3 p)
{
	tr->c.c0 = ft_vec_sub(p, tr->pos.p0);
	tr->c.c1 = ft_vec_sub(p, tr->pos.p1);
	tr->c.c2 = ft_vec_sub(p, tr->pos.p2);
}

double		ft_triangle_solve_t(t_triangle *tr, t_ray *r, t_t *t_range)
{
	return (ft_plane_solve_t(&tr->tr_plane, r, t_range));
}

int			ft_triangle_hit(t_triangle *tr, t_ray *r, t_t *t_range,
				t_hit_rec *rec)
{
	double	t;
	t_vec3	norm;
	t_edge	edge;
	t_c		c;

	t = ft_triangle_solve_t(tr, r, t_range);
	if (t == INFINITY)
		return (0);
	ft_triangle_set_c(tr, ft_ray_at(*r, t));
	norm = tr->tr_plane.norm;
	edge = tr->edge;
	c = tr->c;
	if (ft_vec_dot(norm, ft_vec_cross(edge.edge0, c.c0)) < 0)
		return (0);
	if (ft_vec_dot(norm, ft_vec_cross(edge.edge1, c.c1)) < 0)
		return (0);
	if (ft_vec_dot(norm, ft_vec_cross(edge.edge2, c.c2)) < 0)
		return (0);
	t_range->max = t;
	rec->t = t;
	rec->p = ft_ray_at(*r, rec->t);
	ft_set_face_normal(rec, r, &tr->tr_plane.norm);
	ft_set_hit_rec_color(rec, tr->tr_plane.color);
	return (1);
}

int			ft_triangle_sha_hit(t_triangle *tr, t_ray *r, t_t *t_range)
{
	double	t;
	t_vec3	norm;
	t_edge	edge;
	t_c		c;

	t = ft_triangle_solve_t(tr, r, t_range);
	if (t == INFINITY)
		return (0);
	ft_triangle_set_c(tr, ft_ray_at(*r, t));
	norm = tr->tr_plane.norm;
	edge = tr->edge;
	c = tr->c;
	if (ft_vec_dot(norm, ft_vec_cross(edge.edge0, c.c0)) < 0)
		return (0);
	if (ft_vec_dot(norm, ft_vec_cross(edge.edge1, c.c1)) < 0)
		return (0);
	if (ft_vec_dot(norm, ft_vec_cross(edge.edge2, c.c2)) < 0)
		return (0);
	return (1);
}
