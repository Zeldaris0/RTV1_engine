/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsercamlight.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:09:29 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/23 14:49:29 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

int			arr_counter(char **arr, int flag)
{
	int i;
	int j;

	i = 0;
	if (arr == NULL || arr[0] == NULL)
		return (0);
	else
	{
		while (arr[++i])
		{
			if (flag == 1)
			{
				j = 0;
				while (arr[i][j])
				{
					if (j == 0 && arr[i][j] == '-')
						j++;
					if (arr[i][j] < '0' || arr[i][j] > '9')
						return (0);
					j++;
				}
			}
		}
		return (i - 1);
	}
}

void		check_helper(char **param, char **obt)
{
	delet_table(param);
	delet_table(obt);
}

int			check_cam(char *tab, t_obj *obj)
{
	t_check		c;
	t_objnum	o;

	c.i = 1;
	c.j = 0;
	if ((ft_stc("cam", tab, 3) != 0) || !(c.obt = ft_strsplit(tab, ':'))
			|| c.obt[0] == NULL)
		return (0);
	if (arr_counter(c.obt, 0) == 3)
	{
		if ((ft_stc("pos", c.obt[1], 3)) || (ft_stc("trs", c.obt[2], 3))
				|| (ft_stc("dir", c.obt[3], 3)))
			return (0);
		while (c.obt[c.i])
			paramtonum(&c);
		o.objnum = 3;
		o.add = 0;
		node_filler(0, c.allnum, o, obj);
		delet_table(c.obt);
		return (1);
	}
	return (0);
}

int			check_light(char *tab, t_obj *obj)
{
	t_check		c;
	t_objnum	o;

	c.i = 1;
	c.j = 0;
	if (((ft_stc("light", tab, 5) == 0) && (c.obt = ft_strsplit(tab, ':'))
	&& c.obt[0] != NULL) && arr_counter(c.obt, 0) == 4)
	{
		if ((ft_stc("pos", c.obt[1], 3)) || (ft_stc("trs", c.obt[2], 3))
				|| (ft_stc("col", c.obt[3], 3)) || (ft_stc("int", c.obt[4], 3)))
			return (0);
		while (c.i < 4)
			paramtonum(&c);
		c.param = ft_strsplit(c.obt[c.i], ',');
		if (arr_counter(c.param, 1) != 1)
			return (0);
		c.i = ft_atoi(c.param[1]);
		o.objnum = 3;
		o.add = c.i;
		node_filler(1, c.allnum, o, obj);
		check_helper(c.param, c.obt);
		return (1);
	}
	return (0);
}

int			check_sphere(char *tab, t_obj *obj)
{
	t_check		c;
	t_objnum	o;

	c.i = 1;
	c.j = 0;
	if (((ft_stc("sphere", tab, 6) == 0) && (c.obt = ft_strsplit(tab, ':'))
	&& c.obt[0] != NULL) && arr_counter(c.obt, 0) == 4)
	{
		if ((ft_stc("pos", c.obt[1], 3)) || (ft_stc("trs", c.obt[2], 3))
			|| (ft_stc("col", c.obt[3], 3)) || (ft_stc("rad", c.obt[4], 3)))
			return (0);
		while (c.i < 4)
			paramtonum(&c);
		c.param = ft_strsplit(c.obt[c.i], ',');
		if (arr_counter(c.param, 1) != 1)
			return (0);
		c.i = ft_atoi(c.param[1]);
		o.objnum = 3;
		o.add = c.i;
		node_filler(2, c.allnum, o, obj);
		check_helper(c.param, c.obt);
		return (1);
	}
	return (0);
}
