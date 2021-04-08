/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:18:31 by abenani           #+#    #+#             */
/*   Updated: 2021/02/22 15:08:51 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

int		pixel_shadow(t_obj *obj, t_vec p, t_vec light)
{
	double	t;
	double	light_dst;
	double	tmp;
	t_vec	dir;

	dir = vec_unit(vec_sub(light, p));
	light_dst = vec_magnitude(vec_sub(light, p));
	t = light_dst;
	tmp = 0;
	if (obj->id == 2)
		tmp = sphere(obj, p, dir);
	if (obj->id == 3)
		tmp = plane(obj, p, dir);
	else if (obj->id == 5)
		tmp = cylinder(obj, p, dir);
	else if (obj->id == 4)
		tmp = cone(obj, p, dir);
	if (tmp > 0 && tmp < t)
		t = tmp;
	if (t < light_dst && t > 0.001)
		return (1);
	return (0);
}

t_color	ambient_color(t_obj *obj)
{
	t_color	light_c;
	t_color	color;
	float	light_int;

	light_int = obj->head->next->oneint;
	if (light_int < 0)
		light_int = 0;
	if (light_int > 255)
		light_int = 255;
	color = objcolor(obj->obj[2]);
	light_c = objcolor(obj->head->next->obj[2]);
	color.a = light_int;
	color.r = 0.5 * color.r + (light_int / 1500) * light_c.r;
	color.g = 0.5 * color.g + (light_int / 1500) * light_c.g;
	color.b = 0.5 * color.b + (light_int / 1500) * light_c.b;
	return (color);
}

double	diffuse_color(t_obj *obj, t_vec org, t_vec dir, t_light *lt)
{
	t_ray ray;

	ray.org = org;
	ray.dir = dir;
	lt->diff = 0;
	lt->p = vec_add(org, vec_num(dir, lt->t));
	lt->l = vec_unit(vec_sub(lt->light, lt->p));
	if (obj->id == 2)
		lt->nrm = vec_unit(vec_sub(lt->p, objvec(obj->obj[0])));
	if (obj->id == 3)
		lt->nrm = plane_nrm(obj, dir);
	if (obj->id == 5)
		lt->nrm = cylinder_nrm(obj, ray, lt->t, lt->p);
	if (obj->id == 4)
		lt->nrm = cone_nrm(obj, ray, lt->t, lt->p);
	lt->diff = vec_dot(lt->nrm, lt->l) * (lt->light_int / 170);
	if (lt->diff < 0)
		lt->diff = 0;
	return (lt->diff);
}

void	light_helper(t_vec *light, float *light_int, t_color *color, t_obj *obj)
{
	*light = objvec(obj->head->next->obj[0]);
	*light_int = obj->head->next->oneint;
	*color = objcolor(obj->obj[2]);
	if (*light_int < 0)
		*light_int = 0;
	if (*light_int > 255)
		*light_int = 255;
}

t_color	light_pixel(t_obj *obj, t_vec org, t_vec dir, double t)
{
	t_light	lt;
	t_obj	*lp;
	double	spec;

	lt.t = t;
	light_helper(&lt.light, &lt.light_int, &lt.color, obj);
	lt.color = ambient_color(obj);
	lt.diff = diffuse_color(obj, org, dir, &lt);
	lt.h = vec_unit(vec_add(vec_unit(vec_sub(org, lt.p)), vec_unit(lt.l)));
	spec = vec_dot(lt.nrm, lt.h);
	if ((spec = pow(spec, 64)) < 0)
		spec = 0;
	lp = obj->head->next->next;
	while (lp)
	{
		if (lp != obj)
			if (pixel_shadow(lp, lt.p, lt.light))
			{
				lt.color.a = 100;
				spec = 0;
			}
		lp = lp->next;
	}
	color_spec(&lt, spec);
	return (lt.color);
}
