/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtv.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:34:52 by lberezyn          #+#    #+#             */
/*   Updated: 2018/02/08 18:34:55 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RTV_H
# define FT_RTV_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <errno.h>
# include <stdlib.h>
# include <pthread.h>

# define MES1 "Usage : ./RTv1 scene_number(1-8)"
# define MES2 "File opening failed"
# define MES3 "Reading failure"
# define MES4 "Memory allocation failure"
# define MES5 "Invalid scene file"
# define WIN_W 800
# define WIN_H 800
# define THR_AMOUNT 16
# define OFFSET 10000
# define PI 3.14159265359

typedef double		t_vec __attribute__((vector_size(sizeof(double)*3)));

enum		e_light {
	ambient = 0,
	point = 1
};

typedef struct		s_dpoint
{
	double			x;
	double			y;
	double			z;
}					t_dpoint;

union				u_color
{
	unsigned int	color;
	unsigned char	channels[4];
};

typedef struct		s_camera
{
	t_vec			origin;
	t_vec			dir;
	t_dpoint		screen;
	double			vport_w;
	double			vport_h;
	double			vport_dist;
}					t_camera;

typedef struct		s_obj
{
	short			type;
	double			rad;
	t_vec			rot;
	t_vec			pos;
	union u_color	col;
	double			alpha;
}					t_obj;

typedef struct		s_li
{
	short			type;
	t_vec			pos;
	double			inten;
	union u_color	col;
}					t_li;

typedef struct		s_ray
{
	t_dpoint		start;
	t_vec			dir;
}					t_ray;

typedef struct		s_gra
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				sizeline;
	int				endian;
	t_camera		cam_def;
	t_camera		cam_mod;
	int				objs;
	t_obj			**obj;
	short			ligs;
	t_li			**lights;
	t_ray			ray;
	double			t0;
	double			t1;
	t_ray			lp;
	double			clo;
	int				clo_col;
	double			env_li;
	double			light;
	double			blik;
	union u_color	blik_col;
	t_vec			p;
	t_dpoint		start;
	double			temp;
	int				color;
	double			step;
	int				i;
	float			an_x;
	float			an_y;
	float			an_z;
	double			alp;
	double			bet;
	double			gam;
}					t_gra;

void				ft_init(t_gra *o);
int					ft_exit_x(void);
void				ft_draw(t_gra *o);
void				ft_error(char *s);
int					key_hook(int keycode, t_gra *o);
t_gra				*key_hook_rot(t_gra *o, int keycode);
t_gra				*key_hook_def(t_gra *o);

void				ft_scene_init(t_gra *o);
void				ft_cr_sphere(t_obj *s, union u_color col,
									t_vec pos, double rad);
void				ft_cr_plane(t_obj *s, union u_color col,
								t_vec pos, t_vec rot);
void				ft_cr_cyl(t_obj *s, union u_color col,
								t_vec pos, t_vec rot);
void				ft_cr_cone(t_obj *s, union u_color col,
								t_vec pos, t_vec rot);
void				ft_scene1(t_gra *o);
void				ft_scene2(t_gra *o);
void				ft_scene3(t_gra *o);
void				ft_scene4(t_gra *o);
void				ft_scene5(t_gra *o);
void				ft_scene50(t_gra *o);
void				ft_scene6(t_gra *o);
void				ft_scene7(t_gra *o);
void				ft_scene8(t_gra *o);
union u_color		ft_base_color(int r, int b, int g, int a);

void				ft_tracer(t_gra o, int x, int y, int i);
void				ft_get_ray(t_gra *o, int x, int y);
void				ft_rotation(t_gra *o);
t_vec				ft_rot_matrix(double alpha, double beta,
									double gamma, t_vec r);
void				ft_checklight(t_gra *o, int i, int k);
void				ft_lightening(t_gra *o, int i);
void				ft_find_clo(t_gra *o, int i);
double				ft_shadow(t_gra *o, int k, t_ray ray);

t_vec				ft_vecnormal(t_vec *v);
double				ft_vecdot(t_vec *a, t_vec *b);
t_vec				ft_vecscale(t_vec *a, double n);
t_vec				ft_vecsub(t_vec *a, t_vec *b);
t_vec				ft_vecminus(t_vec *i, t_vec *j);
double				ft_magnitude(t_vec *a);

t_vec				ft_normal(t_gra *o, int i, t_vec p);
void				ft_sphere(t_gra *o, int i, t_ray ray);
void				ft_cylinder(t_gra *o, int i, t_ray ray);
void				ft_plane(t_gra *o, int i, t_ray ray);
void				ft_cone(t_gra *o, int i, t_ray ray);

#endif
