/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:14:46 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/23 14:58:01 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

double		sphere(t_obj *sphere, t_vec org, t_vec dir)
{
	t_shape		sp;
	t_eq		sol;
	double		tmp;

	sp.t = 0;
	sp.rad = sphere->oneint;
	sp.pos = objvec(sphere->obj[0]);
	sp.x = vec_sub(org, sp.pos);
	sp.t = -1;
	sol.a = vec_dot(dir, dir);
	sol.b = 2 * vec_dot(dir, sp.x);
	sol.c = vec_dot(sp.x, sp.x) - sp.rad * sp.rad;
	sol.delta = sol.b * sol.b - 4 * sol.a * sol.c;
	if (sol.delta > 0)
	{
		sp.t = (-sol.b - sqrt(sol.delta)) / 2 * sol.a;
		tmp = (-sol.b + sqrt(sol.delta)) / 2 * sol.a;
		if (tmp < sp.t)
			sp.t = tmp;
	}
	return (sp.t);
}

double		*rotation(double *dir, double *rot)
{
	t_vec		ang;
	t_vec		ret;
	t_vec		v;

	v = objvec(dir);
	ang = vec_num(objvec(rot), (float)M_PI / 180);
	ret.x = v.x * cos(ang.z) - v.y * sin(ang.z);
	ret.y = v.x * sin(ang.z) + v.y * cos(ang.z);
	ret.z = v.z;
	v = ret;
	ret.x = v.x * cos(ang.y) + v.z * sin(ang.y);
	ret.y = v.y;
	ret.z = -v.x * sin(ang.y) + v.z * cos(ang.y);
	v = ret;
	ret.x = v.x;
	ret.y = v.y * cos(ang.x) - v.z * sin(ang.x);
	ret.z = v.y * sin(ang.x) + v.z * cos(ang.x);
	v = ret;
	dir[0] = ret.x;
	dir[1] = ret.y;
	dir[2] = ret.z;
	return (dir);
}

double		cylinder(t_obj *cylinder, t_vec org, t_vec dir)
{
	t_shape		cyl;
	t_eq		sol;
	double		tmp;

	cyl.rad = cylinder->oneint;
	cyl.pos = objvec(cylinder->obj[0]);
	cyl.x = vec_sub(org, cyl.pos);
	cyl.nrm = vec_unit(objvec(cylinder->obj[4]));
	cyl.t = 0;
	sol.a = vec_dot(dir, dir) - (vec_dot(dir, cyl.nrm) * vec_dot(dir, cyl.nrm));
	sol.b = 2.0 * (vec_dot(dir, cyl.x) - (vec_dot(dir, cyl.nrm)
				* vec_dot(cyl.x, cyl.nrm)));
	sol.c = vec_dot(cyl.x, cyl.x) - (vec_dot(cyl.x, cyl.nrm)
			* vec_dot(cyl.x, cyl.nrm)) - (cyl.rad * cyl.rad);
	sol.delta = sol.b * sol.b - (4.0 * sol.a * sol.c);
	if (sol.delta > 0)
	{
		cyl.t = (-sol.b + sqrt(sol.delta)) / (2 * sol.a);
		tmp = (-sol.b - sqrt(sol.delta)) / (2 * sol.a);
		if (tmp < cyl.t)
			cyl.t = tmp;
	}
	return (cyl.t);
}

double		min_ray(double t1, double t2)
{
	if (((t1 < t2 || t2 < 0.1) && t1 > 0.1))
		return (t1);
	else if (((t2 < t1 || t1 < 0.1) && t2 > 0.1))
	{
		return (t2);
	}
	return (0);
}

double		cone(t_obj *cone, t_vec org, t_vec dir)
{
	t_shape		cn;
	t_eq		sol;
	double		anng;

	anng = (double)cone->oneint;
	cn.t = 0;
	cn.nrm = vec_unit(objvec(cone->obj[4]));
	cn.ang = tan(anng * (M_PI / 360));
	cn.x = vec_sub(org, objvec(cone->obj[0]));
	sol.a = vec_dot(dir, dir) - (1 + cn.ang * cn.ang) *
		vec_dot(dir, cn.nrm) * vec_dot(dir, cn.nrm);
	sol.b = 2.0 * (vec_dot(dir, cn.x) - (1 + cn.ang * cn.ang) *
			vec_dot(dir, cn.nrm) * vec_dot(cn.x, cn.nrm));
	sol.c = vec_dot(cn.x, cn.x) - (1 + cn.ang * cn.ang) *
		vec_dot(cn.x, cn.nrm) * vec_dot(cn.x, cn.nrm);
	sol.delta = sol.b * sol.b - (4.0 * sol.a * sol.c);
	if (sol.delta > 0)
	{
		cn.t = (-sol.b - sqrt(sol.delta)) / (2.0 * sol.a);
		cn.tmp = (-sol.b + sqrt(sol.delta)) / (2.0 * sol.a);
		return (min_ray(cn.t, cn.tmp));
	}
	return (0);
}
