/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:43:05 by lberezyn          #+#    #+#             */
/*   Updated: 2018/01/22 11:43:06 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_rtv.h"

void				ft_lightening(t_gra *o, int i)
{
	union u_color	a;

	a.color = o->clo_col;
	o->light = o->env_li;
	o->blik = 0;
	o->p = ft_vecscale(&o->ray.dir, o->clo) + o->cam_mod.origin;
	o->lp.start.x = o->p[0];
	o->lp.start.y = o->p[1];
	o->lp.start.z = o->p[2];
	o->blik_col.channels[0] = 0;
	o->blik_col.channels[1] = 0;
	o->blik_col.channels[2] = 0;
	o->blik_col.channels[3] = 0;
	ft_checklight(o, i, 0);
	a.channels[0] = ((a.channels[0] * o->light +
		o->blik_col.channels[0]) > 255) ? 255 :
		a.channels[0] * o->light + o->blik_col.channels[0];
	a.channels[1] = ((a.channels[1] * o->light +
		o->blik_col.channels[1]) > 255) ? 255 :
		a.channels[1] * o->light + o->blik_col.channels[1];
	a.channels[2] = ((a.channels[2] * o->light +
		o->blik_col.channels[2]) > 255) ? 255 :
		a.channels[2] * o->light + o->blik_col.channels[2];
	o->clo_col = a.color;
}

double				ft_shadow(t_gra *o, int k, t_ray ray)
{
	int				i;
	double			root;
	double			ret;

	i = -1;
	root = ft_magnitude(&ray.dir);
	ret = 0.0;
	ray.dir = ft_vecnormal(&ray.dir);
	while (++i < o->objs)
	{
		o->t0 = 0;
		if (i == k)
			continue;
		else if (o->obj[i]->type == 3)
			ft_sphere(o, i, ray);
		else if (o->obj[i]->type == 2)
			ft_plane(o, i, ray);
		else if (o->obj[i]->type == 4)
			ft_cylinder(o, i, ray);
		else if (o->obj[i]->type == 5)
			ft_cone(o, i, ray);
		if (o->t0 > 0.000000000001 && o->t0 < root)
			ret += o->t0;
	}
	return (ret);
}

t_vec				ft_normal(t_gra *o, int i, t_vec p)
{
	t_vec			n;
	double			m;
	t_vec			oc;

	if (o->obj[i]->type == 4 || o->obj[i]->type == 5)
	{
		oc[0] = (o->ray.start.x - o->obj[i]->pos[0]);
		oc[1] = (o->ray.start.y - o->obj[i]->pos[1]);
		oc[2] = (o->ray.start.z - o->obj[i]->pos[2]);
		m = ft_vecdot(&o->ray.dir, &o->obj[i]->rot) * o->t0 +
			ft_vecdot(&oc, &o->obj[i]->rot);
		n = p - o->obj[i]->pos - ft_vecscale(&o->obj[i]->rot, m);
		if (o->obj[i]->type == 5)
		{
			n = n - ft_vecscale(&o->obj[i]->rot, m *
				tan((o->obj[i]->alpha / 2) * PI / 180) *
				tan((o->obj[i]->alpha / 2) * PI / 180));
		}
	}
	else if (o->obj[i]->type == 2)
		n = o->obj[i]->rot;
	if (o->obj[i]->type == 3)
		n = ft_vecminus(&p, &o->obj[i]->pos);
	n = ft_vecnormal(&n);
	return (n);
}

void				*ft_threading(void *a)
{
	int				id;
	int				end;
	int				i;
	t_gra			*o;

	o = (t_gra *)a;
	i = o->i;
	id = o->i / OFFSET;
	o->i = i + OFFSET;
	end = i + OFFSET;
	while (i < end)
	{
		if (i >= WIN_W * WIN_H)
			pthread_exit(0);
		o->clo = -1;
		ft_tracer(*o, i % WIN_W, i / WIN_W, -1);
		i++;
	}
	pthread_exit(0);
}

void				ft_draw(t_gra *o)
{
	int				i;
	pthread_t		thr[THR_AMOUNT];

	o->i = 0;
	while (o->i < WIN_W * WIN_H)
	{
		i = 0;
		ft_bzero(thr, sizeof(pthread_t) * THR_AMOUNT);
		while (i < THR_AMOUNT)
		{
			pthread_create(&thr[i], NULL, ft_threading, o);
			i++;
		}
		i = 0;
		while (i < THR_AMOUNT)
		{
			pthread_join(thr[i], NULL);
			i++;
		}
	}
	mlx_put_image_to_window(o->mlx, o->win, o->img, 0, 0);
}
