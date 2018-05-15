/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:33:51 by lberezyn          #+#    #+#             */
/*   Updated: 2018/02/08 18:34:01 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_rtv.h"

void		ft_roots(t_gra *o, double a, double b, double c)
{
	double	deskr;
	double	q;

	deskr = b * b - 4 * a * c;
	if (deskr >= 0 && a != 0)
	{
		if (deskr == 0)
		{
			o->t0 = -0.5 * b / a;
			o->t1 = o->t0;
		}
		else
		{
			o->t0 = (-b + sqrt(deskr)) / (2 * a);
			o->t1 = (-b - sqrt(deskr)) / (2 * a);
		}
	}
	else
	{
		o->t0 = -1;
		o->t1 = -1;
	}
}

void		ft_sphere(t_gra *o, int i, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	t_vec	oc;
	double	deskr;

	a = ft_vecdot(&ray.dir, &ray.dir);
	oc[0] = (ray.start.x - o->obj[i]->pos[0]);
	oc[1] = (ray.start.y - o->obj[i]->pos[1]);
	oc[2] = (ray.start.z - o->obj[i]->pos[2]);
	b = 2 * ft_vecdot(&oc, &ray.dir);
	c = ft_vecdot(&oc, &oc) - (o->obj[i]->rad * o->obj[i]->rad);
	ft_roots(o, a, b, c);
}

void		ft_plane(t_gra *o, int i, t_ray ray)
{
	double	a;
	double	b;
	t_vec	oc;

	oc[0] = (ray.start.x - o->obj[i]->pos[0]);
	oc[1] = (ray.start.y - o->obj[i]->pos[1]);
	oc[2] = (ray.start.z - o->obj[i]->pos[2]);
	o->obj[i]->rot = ft_vecnormal(&o->obj[i]->rot);
	a = -(ft_vecdot(&oc, &o->obj[i]->rot));
	b = ft_vecdot(&ray.dir, &o->obj[i]->rot);
	if (b != 0)
		o->t0 = a / b;
	else
		o->t0 = -1;
	if (o->t0 < 0.0001)
		o->t0 = -1;
	o->t1 = o->t0;
}

void		ft_cylinder(t_gra *o, int i, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	t_vec	oc;

	o->obj[i]->rot = ft_vecnormal(&o->obj[i]->rot);
	a = (double)(ft_vecdot(&ray.dir, &ray.dir) -
			(ft_vecdot(&ray.dir, &o->obj[i]->rot) *
			ft_vecdot(&ray.dir, &o->obj[i]->rot)));
	oc[0] = (ray.start.x - o->obj[i]->pos[0]);
	oc[1] = (ray.start.y - o->obj[i]->pos[1]);
	oc[2] = (ray.start.z - o->obj[i]->pos[2]);
	b = 2 * (double)(ft_vecdot(&ray.dir, &oc) -
			ft_vecdot(&ray.dir, &o->obj[i]->rot) *
			ft_vecdot(&oc, &o->obj[i]->rot));
	c = (double)(ft_vecdot(&oc, &oc) - ft_vecdot(&oc, &o->obj[i]->rot) *
			ft_vecdot(&oc, &o->obj[i]->rot) -
			(o->obj[i]->rad * o->obj[i]->rad));
	ft_roots(o, a, b, c);
}

void		ft_cone(t_gra *o, int i, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	t_vec	oc;
	double	k;

	k = tan((o->obj[i]->alpha / 2) * PI / 180);
	o->obj[i]->rot = ft_vecnormal(&o->obj[i]->rot);
	oc[0] = (ray.start.x - o->obj[i]->pos[0]);
	oc[1] = (ray.start.y - o->obj[i]->pos[1]);
	oc[2] = (ray.start.z - o->obj[i]->pos[2]);
	a = ft_vecdot(&ray.dir, &ray.dir) - (1 + k * k) *
			ft_vecdot(&ray.dir, &o->obj[i]->rot) *
			ft_vecdot(&ray.dir, &o->obj[i]->rot);
	b = 2 * (ft_vecdot(&ray.dir, &oc) - (1 + k * k) *
			ft_vecdot(&ray.dir, &o->obj[i]->rot) *
			ft_vecdot(&oc, &o->obj[i]->rot));
	c = ft_vecdot(&oc, &oc) - (1 + k * k) * ft_vecdot(&oc, &o->obj[i]->rot) *
			ft_vecdot(&oc, &o->obj[i]->rot);
	ft_roots(o, a, b, c);
}
