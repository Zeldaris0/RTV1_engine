/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:36:06 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/23 14:52:59 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

int		check_plane(char *tab, t_obj *obj)
{
	t_check		c;
	t_objnum	o;

	c.i = 1;
	c.j = 0;
	if ((ft_stc("plane", tab, 5) != 0)
			|| !(c.obt = ft_strsplit(tab, ':')) || c.obt[0] == NULL)
		return (0);
	if (arr_counter(c.obt, 0) == 5)
	{
		if ((ft_stc("pos", c.obt[1], 3)) || (ft_stc("trs", c.obt[2], 3))
				|| (ft_stc("col", c.obt[3], 3))
				|| (ft_stc("rot", c.obt[4], 3)) || (ft_stc("dir", c.obt[5], 3)))
			return (0);
		while (c.i < 6)
			paramtonum(&c);
		o.objnum = 5;
		o.add = 0;
		node_filler(3, c.allnum, o, obj);
		delet_table(c.obt);
		return (1);
	}
	return (0);
}

int		check_cone(char *tab, t_obj *obj)
{
	t_check		c;
	t_objnum	o;

	c.i = 1;
	c.j = 0;
	if (((ft_stc("cone", tab, 4) == 0) && (c.obt = ft_strsplit(tab, ':'))
	&& c.obt[0] != NULL) && arr_counter(c.obt, 0) == 6)
	{
		if ((ft_stc("pos", c.obt[1], 3)) || (ft_stc("trs", c.obt[2], 3))
				|| (ft_stc("col", c.obt[3], 3)) || (ft_stc("rot", c.obt[4], 3))
				|| (ft_stc("dir", c.obt[5], 3)) || (ft_stc("ang", c.obt[6], 3)))
			return (0);
		while (c.i < 6)
			paramtonum(&c);
		c.param = ft_strsplit(c.obt[c.i], ',');
		if (arr_counter(c.param, 1) != 1)
			return (0);
		cone_helper(&c);
		o.objnum = 5;
		o.add = c.i;
		node_filler(4, c.allnum, o, obj);
		check_helper(c.param, c.obt);
		return (1);
	}
	return (0);
}

void	paramtonum(t_check *c)
{
	c->param = ft_strsplit(c->obt[c->i], ',');
	if (arr_counter(c->param, 1) != 3)
	{
		ft_putendl("file ERROR :(");
		exit(0);
	}
	c->allnum[c->j] = ft_atoi(c->param[1]);
	c->allnum[c->j + 1] = ft_atoi(c->param[2]);
	c->allnum[c->j + 2] = ft_atoi(c->param[3]);
	c->i++;
	c->j += 3;
	delet_table(c->param);
}

int		check_cy(char *tab, t_obj *obj)
{
	t_check		c;
	t_objnum	o;

	c.i = 1;
	c.j = 0;
	if (((ft_stc("cylinder", tab, 8) == 0) && (c.obt = ft_strsplit(tab, ':'))
	&& c.obt[0] != NULL) && arr_counter(c.obt, 0) == 6)
	{
		if ((ft_stc("pos", c.obt[1], 3)) || (ft_stc("trs", c.obt[2], 3))
				|| (ft_stc("col", c.obt[3], 3)) || (ft_stc("rot", c.obt[4], 3))
				|| (ft_stc("dir", c.obt[5], 3)) || (ft_stc("rad", c.obt[6], 3)))
			return (0);
		while (c.i < 6)
			paramtonum(&c);
		c.param = ft_strsplit(c.obt[c.i], ',');
		if (arr_counter(c.param, 1) != 1)
			return (0);
		o.add = ft_atoi(c.param[1]);
		o.objnum = 5;
		node_filler(5, c.allnum, o, obj);
		check_helper(c.param, c.obt);
		return (1);
	}
	return (0);
}
