/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 14:34:06 by lberezyn          #+#    #+#             */
/*   Updated: 2018/02/25 14:34:10 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_rtv.h"

union u_color		ft_base_color(int r, int b, int g, int a)
{
	union u_color	col;

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 ||
		b > 255 || a < 0 || a > 255)
		ft_error(MES5);
	col.channels[2] = r;
	col.channels[1] = b;
	col.channels[0] = g;
	col.channels[3] = a;
	return (col);
}

void				ft_cr_sphere(t_obj *s, union u_color col,
								t_vec pos, double rad)
{
	s->type = 3;
	s->col = col;
	s->pos = pos;
	s->rad = rad;
}

void				ft_cr_cyl(t_obj *s, union u_color col,
								t_vec pos, t_vec rot)
{
	s->type = 4;
	s->col = col;
	s->pos = pos;
	s->rot = rot;
	s->rad = 4;
}

void				ft_cr_plane(t_obj *s, union u_color col,
								t_vec pos, t_vec rot)
{
	s->type = 2;
	s->col = col;
	s->pos = pos;
	s->rot = rot;
}

void				ft_cr_cone(t_obj *s, union u_color col,
								t_vec pos, t_vec rot)
{
	s->type = 5;
	s->col = col;
	s->pos = pos;
	s->rot = rot;
	s->rad = 10;
	s->alpha = 40;
}
