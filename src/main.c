/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:42:14 by lberezyn          #+#    #+#             */
/*   Updated: 2018/01/22 11:42:21 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_rtv.h"

void		ft_get_scene(int i, t_gra *o)
{
	if (i == 1)
		ft_scene1(o);
	else if (i == 2)
		ft_scene2(o);
	else if (i == 3)
		ft_scene3(o);
	else if (i == 4)
		ft_scene4(o);
	else if (i == 5)
		ft_scene5(o);
	else if (i == 6)
		ft_scene6(o);
	else if (i == 7)
		ft_scene7(o);
	else if (i == 8)
		ft_scene8(o);
}

int			main(int ac, char **av)
{
	t_gra	o;

	if (ac != 2 || (ft_strlen(av[1]) > 1) ||
		!(ft_atoi(av[1]) > 0 && ft_atoi(av[1]) <= 8))
		ft_error(MES1);
	if (!(o.mlx = mlx_init()))
		ft_error("Initialization failure");
	if (!(o.win = mlx_new_window(o.mlx, WIN_W, WIN_H, "RTv1")))
	{
		free(o.mlx);
		ft_error(strerror(errno));
	}
	if (!(o.img = mlx_new_image(o.mlx, WIN_W, WIN_H)))
		ft_error(strerror(errno));
	if (!(o.addr = mlx_get_data_addr(o.img, &o.bpp,
			&o.sizeline, &o.endian)))
		ft_error(strerror(errno));
	ft_get_scene(ft_atoi(av[1]), &o);
	o.bpp = o.bpp / 8;
	ft_init(&o);
	ft_draw(&o);
	mlx_hook(o.win, 2, 0, key_hook, &o);
	mlx_hook(o.win, 17, 1L << 17, ft_exit_x, 0);
	mlx_loop(o.mlx);
	return (0);
}

void		ft_init(t_gra *o)
{
	o->cam_def.origin = (t_vec){0, 0, -100};
	o->cam_def.dir = (t_vec){0, 0, 1};
	o->cam_mod.origin = o->cam_def.origin;
	o->cam_mod.dir = o->cam_def.dir;
	o->cam_def.vport_dist = 1;
	o->cam_mod.vport_dist = 1;
	o->cam_def.vport_w = 0.5;
	o->cam_mod.vport_w = 0.5;
	o->cam_def.vport_h = 0.5;
	o->cam_mod.vport_w = 0.5;
	o->cam_mod.screen.z = o->cam_mod.vport_dist;
	o->env_li = 0.3;
	o->an_x = 0;
	o->an_y = 0;
	o->an_z = 0;
	o->step = 10;
	o->i = 0;
}

void		ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(0);
}

int			ft_exit_x(void)
{
	exit(1);
}
