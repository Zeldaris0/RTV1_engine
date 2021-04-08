/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapesntools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:56:04 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/23 15:03:00 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_vec		camera_transform(t_cam cam, t_vec old_p)
{
	t_vec	new_p;

	new_p.x = old_p.x * cam.r.x + old_p.y * cam.u.x +
		old_p.z * cam.f.x + cam.pos.x;
	new_p.y = old_p.x * cam.r.y + old_p.y * cam.u.y +
		old_p.z * cam.f.y + cam.pos.y;
	new_p.z = old_p.x * cam.r.z + old_p.y * cam.u.z +
		old_p.z * cam.f.z + cam.pos.z;
	return (new_p);
}

t_vec		objvec(double *arr)
{
	t_vec vect;

	vect = vec(arr[0], arr[1], arr[2]);
	return (vect);
}

t_color		objcolor(double *arr)
{
	t_color col;

	col.r = arr[0];
	col.g = arr[1];
	col.b = arr[2];
	col.a = 255;
	return (col);
}

double		plane(t_obj *plane, t_vec org, t_vec dir)
{
	t_plane		pl;
	double		numone;

	pl.t = 0;
	pl.point = vec_add(objvec(plane->obj[1]), objvec(plane->obj[0]));
	pl.nor = vec_unit(vec_add(objvec(plane->obj[3]), objvec(plane->obj[4])));
	if (vec_dot(dir, pl.nor) == 0)
		return (0);
	numone = 1 / vec_dot(dir, pl.nor);
	pl.t = numone * (vec_dot(pl.point, pl.nor) - vec_dot(org, pl.nor));
	return (pl.t);
}
