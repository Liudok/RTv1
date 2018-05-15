/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:42:54 by lberezyn          #+#    #+#             */
/*   Updated: 2018/01/22 11:42:59 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_rtv.h"

t_gra			*key_hook_cam(t_gra *o, int keycode)
{
	if (keycode == 2)
		o->an_y += o->step;
	else if (keycode == 0)
		o->an_y -= o->step;
	else if (keycode == 1)
		o->an_z += o->step;
	else if (keycode == 13)
		o->an_z -= o->step;
	else if (keycode == 123)
		o->cam_mod.origin[0] += 0.1;
	else if (keycode == 124)
		o->cam_mod.origin[0] -= 0.1;
	else if (keycode == 126)
		o->cam_mod.origin[2] += 10;
	else if (keycode == 125)
		o->cam_mod.origin[2] -= 10;
	return (o);
}

t_gra			*key_hook_def(t_gra *o)
{
	o->cam_mod.origin[0] = o->cam_def.origin[0];
	o->cam_mod.origin[1] = o->cam_def.origin[1];
	o->cam_mod.origin[2] = o->cam_def.origin[2];
	o->cam_mod.dir = o->cam_def.dir;
	o->an_x = 0;
	o->an_y = 0;
	o->an_z = 0;
	return (o);
}

int				key_hook(int keycode, t_gra *o)
{
	if (keycode == 53)
	{
		mlx_destroy_image(o->mlx, o->img);
		mlx_destroy_window(o->mlx, o->win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 82)
		o = key_hook_def(o);
	else if (keycode >= 123 && keycode <= 126)
		o = key_hook_cam(o, keycode);
	else if (keycode >= 0 && keycode <= 13)
		o = key_hook_cam(o, keycode);
	mlx_clear_window(o->mlx, o->win);
	ft_draw(o);
	return (0);
}

t_vec			ft_rot_matrix(double alpha, double beta, double gamma, t_vec r)
{
	double		mat[3][3];
	t_vec		ret;

	mat[0][0] = cos(beta) * cos(gamma);
	mat[1][0] = cos(gamma) * sin(alpha) * sin(beta) - cos(alpha) * sin(gamma);
	mat[2][0] = cos(alpha) * cos(gamma) * sin(beta) + sin(alpha) * sin(gamma);
	mat[0][1] = cos(beta) * sin(gamma);
	mat[1][1] = cos(alpha) * cos(gamma) + sin(alpha) * sin(beta) * sin(gamma);
	mat[2][1] = -cos(gamma) * sin(alpha) + cos(alpha) * sin(beta) * sin(gamma);
	mat[0][2] = -sin(beta);
	mat[1][2] = cos(beta) * sin(alpha);
	mat[2][2] = cos(alpha) * cos(beta);
	ret[0] = (mat[0][0] * r[0]) + (mat[1][0] * r[1]) +
			(mat[2][0] * r[2]);
	ret[1] = (mat[0][1] * r[0]) + (mat[1][1] * r[1]) +
			(mat[2][1] * r[2]);
	ret[2] = (mat[0][2] * r[0]) + (mat[1][2] * r[1]) +
			(mat[2][2] * r[2]);
	return (ret);
}

void			ft_rotation(t_gra *o)
{
	double		a;
	double		b;
	double		c;

	o->alp = PI * (o->an_z) / 180;
	o->bet = PI * (o->an_y) / 180;
	o->gam = PI * (o->an_x) / 180;
	o->ray.dir = ft_rot_matrix(o->alp, o->bet, o->gam,
		ft_vecnormal(&o->ray.dir));
}
