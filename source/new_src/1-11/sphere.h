/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:22:40 by sejpark           #+#    #+#             */
/*   Updated: 2021/03/01 19:45:54 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "hittable.h"

typedef struct	s_sphere
{
	t_point3	center;
	float		radius;
	t_color		color;
}				t_sphere;
t_sphere		ft_sphere_set(t_point3 cen, float diameter, t_color color);
float			ft_sphere_solve_t(t_sphere *sp, t_ray *r, t_t *t_range);
int				ft_sphere_hit(t_sphere *sp, t_ray *r, t_t *t_range,
									t_hit_rec *rec);
int				ft_sphere_sha_hit(t_sphere *sp, t_ray *r, t_t *t_range);
#endif
