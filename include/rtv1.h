/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 11:11:23 by abenani           #+#    #+#             */
/*   Updated: 2021/02/23 15:02:03 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <stdlib.h>
# include <fcntl.h>
# include "../SDL2-2.0.12/build/include/SDL2/SDL.h"
# include <math.h>
# include "../libft/libft.h"
# define W_WIDTH 750
# define W_HEIGHT 500
# define BUFF_SIZE 100

typedef struct		s_check
{
	char			**obt;
	char			**param;
	int				i;
	int				j;
	int				allnum[15];
}					t_check;

typedef	struct		s_node
{
	int				i;
	int				c;
	int				k;
	int				j;
}					t_node;

typedef	struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

typedef	struct		s_pars
{
	int				i;
	int				j;
	int				k;
	char			*tmp;
	char			*tmp2;
}					t_pars;

typedef	struct		s_obj
{
	int				id;
	int				oneint;
	double			**obj;
	struct s_obj	*next;
	struct s_obj	*head;
}					t_obj;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
}					t_sdl;

typedef struct		s_cam
{
	t_vec			f;
	t_vec			r;
	t_vec			u;
	t_vec			pos;
}					t_cam;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				a;
}					t_color;

typedef struct		s_shape
{
	t_vec			pos;
	t_vec			x;
	t_vec			nrm;
	int				rad;
	double			ang;
	double			t;
	double			tmp;
}					t_shape;

typedef struct		s_plane
{
	t_vec			point;
	t_vec			nor;
	double			t;
}					t_plane;

typedef struct		s_objnum
{
	int				objnum;
	int				add;
}					t_objnum;

typedef struct		s_cone
{
	t_vec			d;
	t_vec			v;
	t_vec			co;
	double			ang;
}					t_cone;

typedef struct		s_light
{
	t_vec			light;
	t_color			color;
	float			light_int;
	t_vec			nrm;
	t_vec			p;
	t_vec			l;
	t_vec			h;
	t_vec			c;
	double			diff;
	double			t;
}					t_light;

typedef	struct		s_eq
{
	double			a;
	double			b;
	double			c;
	t_vec			x;
	double			k;
	double			t1;
	double			t2;
	double			delta;
}					t_eq;

typedef struct		s_rlp
{
	int				i;
	int				j;
	int				c_num;
	float			ratio;
	float			x;
	float			y;
}					t_rlp;

typedef struct		s_ray
{
	t_vec			org;
	t_vec			dir;
}					t_ray;

int					startsdl(t_sdl *sdl);
int					exitsdl(t_sdl sdl);
void				draw(SDL_Renderer *rend, t_color *colors);
t_vec				vec(double x, double y, double z);
double				vec_dot(t_vec a, t_vec b);
t_vec				vec_cross(t_vec a, t_vec b);
double				vec_magnitude(t_vec vec);
t_vec				vec_unit(t_vec vec);
t_vec				vec_add(t_vec a, t_vec b);
t_vec				vec_num(t_vec vec, double num);
t_vec				vec_sub(t_vec a, t_vec b);
void				render(t_color *colors, t_obj *object);
t_cam				cam_mx(t_vec from, t_vec to);
t_vec				camera_transform(t_cam cam, t_vec old_p);
t_vec				objvec(double *arr);
t_color				objcolor(double *arr);
void				renderer_loop(t_color *img_buff, t_obj *obj, t_cam cam);
double				sphere(t_obj *sphere, t_vec org, t_vec dir);
double				plane(t_obj *plane, t_vec org, t_vec dir);
double				cylinder(t_obj *cylinder, t_vec org, t_vec dir);
double				cone(t_obj *cone, t_vec org, t_vec dir);
t_color				light_pixel(t_obj *obj, t_vec org, t_vec dir, double t);
double				*rotation(double *dir, double *rot);
double				min_ray(double t1, double t2);
t_vec				cylinder_nrm(t_obj *obj, t_ray ray, double t, t_vec p);
t_vec				plane_nrm(t_obj *obj, t_vec dir);
t_vec				cone_nrm(t_obj *obj, t_ray ray, double t, t_vec p);
void				color_spec(t_light *lt, double spec);
int					check_cam(char *tab, t_obj *obj);
int					check_light(char *tab, t_obj *obj);
void				delet_table(char **tab);
char				**nocomment(char **table);
char				**nospace_nocomment(char **table);
char				**file_reader(char **av, char **table);
int					parser(int ac, char **av, t_obj *object);
int					arr_counter(char **arr, int flag);
void				node_filler(int id, int *object, t_objnum o, t_obj *obj);
void				first_node(t_obj *obj, int *object, int objnum);
int					check_sphere(char *tab, t_obj *obj);
int					check_plane(char *tab, t_obj *obj);
int					check_cone(char *tab, t_obj *obj);
int					check_cy(char *tab, t_obj *obj);
double				*arr_add(double *pos, double *trs);
int					pixel_shadow(t_obj *obj, t_vec org, t_vec dir);
void				paramtonum(t_check *c);
void				check_helper(char **param, char **obt);
void				cone_helper(t_check *c);

#endif
