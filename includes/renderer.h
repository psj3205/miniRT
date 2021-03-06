/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejpark <sejpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:06:06 by sejpark           #+#    #+#             */
/*   Updated: 2021/05/23 20:13:42 by sejpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H
# define ESC		53
# define SPACEBAR	49
# define X_BTN		17
# define KEYPRESS	2
# define KEYRELEASE	3
# include "../library/mlx/includes/mlx.h"
# include "../library/libft/includes/libft.h"
# include "scene_reader.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>

typedef struct	s_pixel
{
	int	x;
	int	y;
}				t_pixel;
void			my_mlx_pixel_put(t_data *data, t_image *img, t_pixel p,
					t_vec3 *color);
void			ft_alloc_image(t_engine *engine);
void			ft_create_window(t_engine *engine);
t_color			ft_ray_color(t_ray *r, t_engine *engine);
int				ft_draw(t_engine *engine);
void			ft_window_close(t_engine *engine);
int				ft_key_press(int keycode, t_engine *engine);
int				ft_xbtn_click(t_engine *engine);
void			ft_engine_init(t_engine *engine);
#endif
