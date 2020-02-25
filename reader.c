/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashabdan <ashabdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 23:47:21 by ashabdan          #+#    #+#             */
/*   Updated: 2020/02/24 13:26:02 by ashabdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				validator(char *str)
{
	int		i;
	int		sides;
	int		hash;

	i = 0;
	sides = 0;
	hash = 0;
	while (str[i])
	{
		if (str[i] == '#' && str[19] == '\n')
		{
			hash += 1;
			sides += i > 0 && str[i - 1] == '#';
			sides += i < 20 && str[i + 1] == '#';
			sides += i > 4 && str[i - 5] == '#';
			sides += i < 14 && str[i + 5] == '#';
		}
		else if ((str[i] != 46 || str[i] == 10) && (i + 1) % 5 != 0 && i != 20)
			return (0);
		i += 1;
	}
	return (hash == 4 && (sides == 6 || sides == 8));
}

static void		getcoords(char *str, t_tet *node)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '#')
		{
			node->x[j] = i % 5;
			node->y[j] = i / 5;
			j += 1;
		}
		i += 1;
	}
}

void			movecoords(t_tet *node)
{
	int		lowest_x;
	int		lowest_y;
	int		i;

	lowest_x = 4;
	lowest_y = 4;
	i = 0;
	while (i < 4)
	{
		if (node->x[i] < lowest_x)
			lowest_x = node->x[i];
		if (node->y[i] < lowest_y)
			lowest_y = node->y[i];
		i += 1;
	}
	i = 0;
	while (i < 4)
	{
		node->x[i] -= lowest_x;
		node->y[i] -= lowest_y;
		i += 1;
	}
}

t_tet			*addnode(t_tet *tet_node, char *str, int index)
{
	t_tet	*node;
	t_tet	*head;

	head = NULL;
	node = (t_tet *)malloc(sizeof(t_tet));
	getcoords(str, node);
	movecoords(node);
	node->index = index;
	if (tet_node == NULL)
	{
		node->next = tet_node;
		return (node);
	}
	else
	{
		head = tet_node;
		while (tet_node->next != NULL)
			tet_node = tet_node->next;
		tet_node->next = node;
		node->next = NULL;
	}
	return (head);
}

void			cleanlst(t_tet **tets)
{
	t_tet	*tmp;

	tmp = NULL;
	while (*tets)
	{
		tmp = (*tets)->next;
		free(*tets);
		*tets = tmp;
	}
	*tets = NULL;
}
