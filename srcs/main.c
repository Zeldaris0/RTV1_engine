/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2021/02/23 14:50:56 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

double		*arr_add(double *pos, double *trs)
{
	pos[0] = pos[0] + trs[0];
	pos[1] = pos[1] + trs[1];
	pos[2] = pos[2] + trs[2];
	return (pos);
}

void		free_object(t_obj *object)
{
	int		i;
	t_obj	*object2;

	object = object->head;
	while (object != NULL)
	{
		i = 0;
		while (object->obj[i])
		{
			free(object->obj[i]);
			i++;
		}
		free(object->obj);
		object2 = object;
		object = object->next;
		free(object2);
	}
}

int			main(int argc, char **argv)
{
	t_obj	*object;
	t_sdl	sdl;
	t_color	*img_buff;

	object = (t_obj *)malloc(sizeof(t_obj));
	if (!parser(argc, argv, object))
	{
		ft_putendl("file ERROR :(");
		exit(0);
	}
	img_buff = malloc(W_WIDTH * W_HEIGHT * sizeof(t_color));
	render(img_buff, object);
	free_object(object);
	if (!startsdl(&sdl))
		exit(0);
	draw(sdl.rend, img_buff);
	while (1)
		if (exitsdl(sdl))
			break ;
	return (0);
}
