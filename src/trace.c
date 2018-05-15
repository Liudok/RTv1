/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:07:59 by lberezyn          #+#    #+#             */
/*   Updated: 2018/02/08 12:08:03 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_rtv.h"

void			ft_get_ray(t_gra *o, int x, int y)
{
	o->cam_mod.screen.x = x - WIN_W / 2.0;
	o->cam_mod.screen.y = (WIN_H - y) - WIN_H / 2.0;
	o->ray.start.x = (double)o->cam_mod.origin[0];
	o->ray.start.y = (double)o->cam_mod.origin[1];
	o->ray.start.z = (double)o->cam_mod.origin[2];
	o->ray.dir[0] = o->cam_mod.screen.x *
		(o->cam_def.vport_w / WIN_W) - o->cam_mod.origin[0];
	o->ray.dir[1] = o->cam_mod.screen.y *
		(o->cam_def.vport_h / WIN_H) - o->cam_mod.origin[1];
	o->ray.dir[2] = o->cam_mod.screen.z;
	ft_rotation(o);
}

void			ft_find_clo(t_gra *o, int i)
{
	if (o->t0 < 0 && o->t1 < 0)
		o->clo = o->clo;
	else
	{
		if (o->t0 < 0)
			o->t0 = o->t1;
		else if (o->t1 < 0)
			;
		else
			o->t0 = (o->t0 < o->t1) ? o->t0 : o->t1;
		if (o->clo == -1 || o->clo > o->t0)
		{
			o->clo = o->t0;
			o->clo_col = o->obj[i]->col.color;
			ft_lightening(o, i);
		}
	}
}

void			ft_tracer(t_gra o, int x, int y, int i)
{
	ft_get_ray(&o, x, y);
	while (++i < o.objs)
	{
		if (o.obj[i]->type == 3)
			ft_sphere(&o, i, o.ray);
		else if (o.obj[i]->type == 2)
			ft_plane(&o, i, o.ray);
		else if (o.obj[i]->type == 4)
			ft_cylinder(&o, i, o.ray);
		else if (o.obj[i]->type == 5)
			ft_cone(&o, i, o.ray);
		ft_find_clo(&o, i);
	}
	*(int *)(o.addr + (x + y * WIN_W) * o.bpp) = (o.clo < 0) ? 0 : o.clo_col;
}

void			ft_blik(t_gra *o, int k, double dotsq)
{
	o->blik = exp(-250 * (1.0 - dotsq) / dotsq);
	o->blik_col.channels[0] = (o->blik_col.channels[0] +
		o->lights[k]->col.channels[0] * o->blik * o->lights[k]->inten >
		255) ? 255 : (o->blik_col.channels[0] + o->lights[k]->col.channels[0] *
		o->blik * o->lights[k]->inten);
	o->blik_col.channels[1] = (o->blik_col.channels[1] +
		o->lights[k]->col.channels[1] * o->blik * o->lights[k]->inten >
		255) ? 255 : (o->blik_col.channels[1] + o->lights[k]->col.channels[1] *
		o->blik * o->lights[k]->inten);
	o->blik_col.channels[2] = (o->blik_col.channels[2] +
		o->lights[k]->col.channels[2] * o->blik * o->lights[k]->inten >
		255) ? 255 : (o->blik_col.channels[2] + o->lights[k]->col.channels[2] *
		o->blik * o->lights[k]->inten);
}

void			ft_checklight(t_gra *o, int i, int k)
{
	t_vec		pc;
	double		cosi;
	t_vec		h;
	t_vec		v;
	t_vec		l;

	pc = ft_normal(o, i, o->p);
	v = o->cam_mod.origin - o->p;
	v = ft_vecnormal(&v);
	while (k < o->ligs)
	{
		o->lp.dir = o->lights[k]->pos - o->p;
		if ((ft_shadow(o, i, o->lp)) == 0)
		{
			l = ft_vecnormal(&o->lp.dir);
			h = l + v;
			h = ft_vecnormal(&h);
			cosi = ft_vecdot(&pc, &l);
			cosi = cosi < 0 ? 0 : cosi;
			o->light += cosi * o->lights[k]->inten;
			ft_blik(o, k, ft_vecdot(&h, &pc) * ft_vecdot(&h, &pc));
		}
		k++;
	}
}
