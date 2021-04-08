/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:34:47 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/23 14:53:46 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		first_node(t_obj *obj, int *object, int objnum)
{
	t_node n;

	n.i = -1;
	n.c = 0;
	n.k = 0;
	n.j = 0;
	obj->id = 0;
	obj->oneint = 0;
	obj->obj = malloc(sizeof(double *) * 4);
	while (++n.i < 3)
		obj->obj[n.i] = malloc(sizeof(double) * 3);
	obj->next = NULL;
	obj->head = obj;
	while (n.c < objnum * 3)
	{
		if (n.c == 3 || n.c == 6)
		{
			n.k++;
			n.j = 0;
		}
		obj->obj[n.k][n.j] = object[n.c];
		n.j++;
		n.c++;
	}
	obj->obj[3] = NULL;
}

void		node_helper(t_node n, t_obj *obj, int *object, int objnum)
{
	while (++n.c < objnum * 3)
	{
		if (n.c == 3 || n.c == 6 || n.c == 9 || n.c == 12 || n.c == 15)
		{
			n.j++;
			n.k = 0;
		}
		obj->obj[n.j][n.k] = object[n.c];
		n.k++;
	}
}

void		node_filler(int id, int *object, t_objnum o, t_obj *obj)
{
	t_node n;

	n.i = -1;
	n.c = -1;
	n.j = 0;
	n.k = 0;
	if (id == 0)
		first_node(obj, object, o.objnum);
	else
	{
		while (obj->next != NULL)
			obj = obj->next;
		obj->next = (t_obj *)malloc(sizeof(t_obj));
		obj->next->head = obj->head;
		obj = obj->next;
		obj->id = id;
		obj->oneint = o.add;
		obj->obj = malloc(sizeof(double *) * o.objnum + 1);
		while (++n.i < o.objnum)
			obj->obj[n.i] = malloc(sizeof(double) * 3);
		obj->next = NULL;
		node_helper(n, obj, object, o.objnum);
	}
	obj->obj[o.objnum] = NULL;
}

void		cone_helper(t_check *c)
{
	if ((c->i = ft_atoi(c->param[1])) == 180)
		c->i = 0;
}
