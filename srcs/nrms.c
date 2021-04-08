/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nrms.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 10:19:07 by abenani           #+#    #+#             */
/*   Updated: 2021/02/22 10:54:01 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_vec	cylinder_nrm(t_obj *obj, t_ray ray, double t, t_vec p)
{
	t_vec	v;
	t_vec	c;
	t_vec	x;
	double	m;

	v = vec_unit(objvec(obj->obj[4]));
	c = objvec(obj->obj[0]);
	x = vec_sub(ray.org, c);
	m = vec_dot(vec_unit(ray.dir), v) * t + vec_dot(x, v);
	return (vec_unit(vec_sub(p, vec_add(c, vec_num(v, m)))));
}

t_vec	plane_nrm(t_obj *obj, t_vec dir)
{
	t_vec nrm;

	nrm = vec_unit(objvec(obj->obj[4]));
	if (vec_dot(dir, nrm) > 0)
		nrm = vec_num(nrm, -1);
	return (nrm);
}

t_vec	cone_nrm(t_obj *obj, t_ray ray, double t, t_vec p)
{
	t_vec	c;
	t_vec	v;
	double	k;
	double	m;

	k = tan(obj->oneint * (M_PI / 360));
	v = vec_unit(objvec(obj->obj[4]));
	c = objvec(obj->obj[0]);
	m = vec_dot(ray.dir, vec_num(v, t)) + vec_dot(vec_sub(ray.org,
	objvec(obj->obj[0])), v);
	return (vec_unit(vec_sub(vec_sub(p, c), vec_num(vec_num(v,
	(1 + k * k)), m))));
}

void	color_spec(t_light *lt, double spec)
{
	lt->color.r *= (spec * 2 + lt->diff);
	lt->color.g *= (spec * 2 + lt->diff);
	lt->color.b *= (spec * 2 + lt->diff);
	if (lt->color.r > 255)
		lt->color.r = 255;
	if (lt->color.g > 255)
		lt->color.g = 255;
	if (lt->color.b > 255)
		lt->color.b = 255;
	if (lt->color.r < 0)
		lt->color.r = 0;
	if (lt->color.g < 0)
		lt->color.g = 0;
	if (lt->color.b < 0)
		lt->color.b = 0;
}
