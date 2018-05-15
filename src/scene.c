/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:35:32 by lberezyn          #+#    #+#             */
/*   Updated: 2018/02/08 18:35:34 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_rtv.h"

void			ft_scene_init(t_gra *o)
{
	int			k;

	k = -1;
	if (!(o->obj = (t_obj**)malloc(sizeof(t_obj*) * o->objs)))
		ft_error(MES4);
	if (!(o->lights = (t_li**)malloc(sizeof(t_li*) * o->ligs)))
		ft_error(MES4);
	while (++k < o->objs)
	{
		if (!(o->obj[k] = (t_obj*)malloc(sizeof(t_obj))))
		{
			free(o->obj);
			ft_error(MES4);
		}
	}
	k = -1;
	while (++k < o->ligs)
	{
		if (!(o->lights[k] = (t_li*)malloc(sizeof(t_li))))
		{
			free(o->lights);
			free(o->obj);
			ft_error(MES4);
		}
	}
}

void			ft_scene1(t_gra *o)
{
	o->objs = 1;
	o->ligs = 3;
	ft_scene_init(o);
	ft_cr_sphere(o->obj[0], ft_base_color(85, 5, 5, 0), (t_vec){0, 0, 40}, 25);
	o->lights[0]->type = ambient;
	o->lights[0]->col = ft_base_color(255, 255, 255, 0);
	o->lights[0]->pos = (t_vec){200, 200, 30};
	o->lights[0]->inten = 0.6;
	o->lights[1]->type = ambient;
	o->lights[1]->col = ft_base_color(255, 255, 255, 0);
	o->lights[1]->pos = (t_vec){80, 200, 0};
	o->lights[1]->inten = 0.6;
	o->lights[2]->type = ambient;
	o->lights[2]->col = ft_base_color(255, 255, 255, 0);
	o->lights[2]->pos = (t_vec){0, 40, -50};
	o->lights[2]->inten = 0.6;
}

void			ft_scene2(t_gra *o)
{
	o->objs = 3;
	o->ligs = 3;
	ft_scene_init(o);
	ft_cr_sphere(o->obj[0], ft_base_color(48, 214, 200, 0),
		(t_vec){0, 0, 150}, 25);
	ft_cr_plane(o->obj[1], ft_base_color(28, 114, 100, 0),
		(t_vec){10, -30, 0}, (t_vec){0, 1, 0});
	ft_cr_sphere(o->obj[2], ft_base_color(85, 5, 5, 0),
		(t_vec){30, 10, 150}, 25);
	o->lights[0]->type = ambient;
	o->lights[0]->col = ft_base_color(255, 255, 255, 0);
	o->lights[0]->pos = (t_vec){160, 200, -60};
	o->lights[0]->inten = 0.8;
	o->lights[1]->type = ambient;
	o->lights[1]->col = ft_base_color(255, 255, 255, 0);
	o->lights[1]->pos = (t_vec){50, 150, 160};
	o->lights[1]->inten = 0.6;
	o->lights[2]->type = ambient;
	o->lights[2]->col = ft_base_color(255, 255, 255, 0);
	o->lights[2]->pos = (t_vec){0, 100, 0};
	o->lights[2]->inten = 0.3;
}

void			ft_scene3(t_gra *o)
{
	o->objs = 1;
	o->ligs = 2;
	ft_scene_init(o);
	ft_cr_cone(o->obj[0], ft_base_color(255, 255, 255, 0),
		(t_vec){0, 0, 0}, (t_vec){0, 1, 0});
	o->lights[0]->type = ambient;
	o->lights[0]->col = ft_base_color(255, 255, 255, 0);
	o->lights[0]->pos = (t_vec){0, 200, -130};
	o->lights[0]->inten = 0.6;
	o->lights[1]->type = ambient;
	o->lights[1]->col = ft_base_color(255, 255, 255, 0);
	o->lights[1]->pos = (t_vec){-80, 200, 0};
	o->lights[1]->inten = 0.6;
}

void			ft_scene4(t_gra *o)
{
	o->objs = 1;
	o->ligs = 3;
	ft_scene_init(o);
	ft_cr_cyl(o->obj[0], ft_base_color(255, 235, 135, 0),
		(t_vec){0, 0, 0}, (t_vec){0, 1, 0});
	o->lights[0]->type = ambient;
	o->lights[0]->col = ft_base_color(255, 255, 255, 0);
	o->lights[0]->pos = (t_vec){160, 200, -60};
	o->lights[0]->inten = 0.2;
	o->lights[1]->type = ambient;
	o->lights[1]->col = ft_base_color(255, 255, 255, 0);
	o->lights[1]->pos = (t_vec){50, 200, 60};
	o->lights[1]->inten = 0.2;
	o->lights[2]->type = ambient;
	o->lights[2]->col = ft_base_color(255, 255, 255, 0);
	o->lights[2]->pos = (t_vec){0, -50, 0};
	o->lights[2]->inten = 0.4;
}
