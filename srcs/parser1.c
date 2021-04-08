/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:08:37 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/22 10:54:01 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		delet_table(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
}

char		**nocomment(char **table)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	while (table[i])
	{
		if (table[i][0] != '#')
			j++;
		i++;
	}
	tab = malloc(sizeof(char *) * (j + 1));
	i = -1;
	j = 0;
	while (table[++i])
		if (table[i][0] != '#')
		{
			tab[j] = ft_strdup(table[i]);
			j++;
		}
	tab[j] = NULL;
	delet_table(table);
	return (tab);
}

char		**nospace_nocomment(char **table)
{
	t_pars p;

	p.i = -1;
	table = nocomment(table);
	while (table[++p.i])
	{
		p.j = -1;
		p.k = 0;
		while (table[p.i][++p.j] != '\0')
			if (table[p.i][p.j] != ' ')
				p.k++;
		p.tmp = malloc(sizeof(char) * p.k + 1);
		p.j = -1;
		p.k = 0;
		while (table[p.i][++p.j] != '\0')
			if (table[p.i][p.j] != ' ')
				p.tmp[p.k++] = table[p.i][p.j];
		p.tmp[p.k] = '\0';
		p.tmp2 = table[p.i];
		table[p.i] = ft_strdup(p.tmp);
		free(p.tmp);
		free(p.tmp2);
	}
	return (table);
}

char		**file_reader(char **av, char **table)
{
	int		fd;
	char	tmp[BUFF_SIZE + 1];
	int		i;
	char	*tofree;
	char	*file_str;

	file_str = malloc(sizeof(char*));
	file_str[0] = '\0';
	if ((fd = open(av[1], 0)))
	{
		if (fd == -1)
			return (NULL);
		while ((i = read(fd, tmp, BUFF_SIZE)))
		{
			if (i < 0)
				return (NULL);
			tmp[i] = '\0';
			tofree = file_str;
			file_str = ft_strjoin(file_str, tmp);
			free(tofree);
		}
	}
	table = ft_strsplit(file_str, '\n');
	free(file_str);
	return (table);
}

int			parser(int ac, char **av, t_obj *object)
{
	char	**table;
	int		i;

	i = 1;
	table = NULL;
	if (ac != 2 || !(table = file_reader(av, table)) || !(table[2]))
		return (0);
	table = nospace_nocomment(table);
	if (!check_cam(table[0], object) || !check_light(table[1], object))
		return (0);
	while (table[++i])
		if (!check_sphere(table[i], object) && !check_plane(table[i], object)
				&& !check_cone(table[i], object) && !check_cy(table[i], object))
			return (0);
	delet_table(table);
	object = object->head;
	while (object != NULL)
	{
		object->obj[0] = arr_add(object->obj[0], object->obj[1]);
		if (object->id == 3 || object->id == 4 || object->id == 5)
			object->obj[4] = rotation(object->obj[4], object->obj[3]);
		object = object->next;
	}
	return (1);
}
