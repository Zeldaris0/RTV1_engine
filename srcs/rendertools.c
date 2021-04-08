/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendertools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 09:54:49 by abenani           #+#    #+#             */
/*   Updated: 2021/02/23 14:57:31 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		render(t_color *img_buff, t_obj *obj)
{
	t_cam cam;
	t_vec cam_pos;
	t_vec look_at;

	cam_pos = vec_add(objvec(obj->obj[0]), objvec(obj->obj[1]));
	look_at = vec_add(objvec(obj->obj[2]), objvec(obj->obj[1]));
	cam = cam_mx(cam_pos, look_at);
	renderer_loop(img_buff, obj, cam);
}

double		return_intrs(t_obj *obj, t_vec org, t_vec dir)
{
	if (obj->id == 2)
		return (sphere(obj, org, dir));
	else if (obj->id == 3)
		return (plane(obj, org, dir));
	else if (obj->id == 5)
		return (cylinder(obj, org, dir));
	else if (obj->id == 4)
		return (cone(obj, org, dir));
	else
		return (0);
}

t_color		pixel_fill(t_obj *obj, t_vec org, t_vec dir)
{
	t_color		black;
	double		t;
	double		tmp;
	t_obj		*theobj;

	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 255;
	t = INFINITY;
	tmp = 0;
	while (obj)
	{
		tmp = return_intrs(obj, org, dir);
		if (tmp > 0 && tmp < t)
		{
			t = tmp;
			theobj = obj;
		}
		obj = obj->next;
	}
	if (t < INFINITY)
		return (light_pixel(theobj, org, dir, t));
	return (black);
}

void		renderer_loop(t_color *img_buff, t_obj *obj, t_cam cam)
{
	t_rlp rlp;
	t_vec pt;

	rlp.ratio = (float)W_WIDTH / W_HEIGHT;
	rlp.j = -1;
	while (++rlp.j < W_HEIGHT)
	{
		rlp.i = -1;
		while (++rlp.i < W_WIDTH)
		{
			rlp.x = ((2 * ((float)(rlp.i + .5) / W_WIDTH) - 1) * rlp.ratio);
			rlp.y = (1 - 2 * ((float)(rlp.j + .5) / W_HEIGHT));
			pt = camera_transform(cam, vec(rlp.x, rlp.y, -1));
			rlp.c_num = W_WIDTH * rlp.j + rlp.i;
			img_buff[rlp.c_num] = pixel_fill(obj, cam.pos, vec_unit(vec_sub(pt,
							cam.pos)));
		}
	}
}

t_cam		cam_mx(t_vec from, t_vec to)
{
	t_cam	vecs;
	double	check;

	vecs.f = vec_unit(vec_add(from, vec_num(to, -1)));
	check = vec_dot(vec_unit(vec(0, 1, 0)), vecs.f);
	if (check == 1 || check == -1)
		vecs.r = vec_unit(vec_cross(vec(0, 1, 1), vecs.f));
	else
		vecs.r = vec_unit(vec_cross(vec(0, 1, 0), vecs.f));
	vecs.u = vec_unit(vec_cross(vecs.f, vecs.r));
	vecs.pos = from;
	return (vecs);
}
