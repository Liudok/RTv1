/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:35:19 by lberezyn          #+#    #+#             */
/*   Updated: 2018/02/08 18:35:21 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_rtv.h"

t_vec			ft_vecnormal(t_vec *a)
{
	double		m;
	t_vec		v;

	v = *a;
	m = ft_magnitude(a);
	if (m != 0)
	{
		v[0] = v[0] / m;
		v[1] = v[1] / m;
		v[2] = v[2] / m;
	}
	return (v);
}

double			ft_magnitude(t_vec *a)
{
	double		root;
	t_vec		v;

	v = *a;
	root = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return (root);
}

double			ft_vecdot(t_vec *i, t_vec *j)
{
	double		d;
	t_vec		a;
	t_vec		b;

	a = *i;
	b = *j;
	d = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	return (d);
}

t_vec			ft_vecscale(t_vec *b, double n)
{
	t_vec		v;
	t_vec		a;

	a = *b;
	v[0] = a[0] * n;
	v[1] = a[1] * n;
	v[2] = a[2] * n;
	return (v);
}

t_vec			ft_vecminus(t_vec *i, t_vec *j)
{
	t_vec		v;
	t_vec		a;
	t_vec		b;

	a = *i;
	b = *j;
	v[0] = a[0] - b[0];
	v[1] = a[1] - b[1];
	v[2] = a[2] - b[2];
	return (v);
}
