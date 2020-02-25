/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashabdan <ashabdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 02:34:10 by ashabdan          #+#    #+#             */
/*   Updated: 2020/02/24 17:49:20 by ashabdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char			*newmap(int map_size)
{
	char	*map;
	int		square;
	int		i;

	i = 0;
	square = map_size * map_size;
	if (!(map = (char *)malloc(sizeof(char) * square + 1)))
		return (NULL);
	while (i < square)
	{
		map[i] = '.';
		i += 1;
	}
	map[i] = '\0';
	return (map);
}

static int		print(char *map, int n)
{
	int i;

	i = 1;
	while (*map)
	{
		write(1, map++, 1);
		if (!(i++ % n))
			write(1, "\n", 1);
	}
	return (1);
}

static void		removelast(char *map, int letter)
{
	char	c;
	int		i;
	int		flag;
	int		ret;

	i = 0;
	c = 'A' + letter;
	flag = 0;
	while (map[i])
	{
		if (map[i] == c)
		{
			if (flag == 0)
			{
				flag = 1;
				ret = i + 1;
			}
			map[i] = '.';
		}
		i += 1;
	}
}

static int		fillmap(t_tet *tets, char *map, int n_tet, int b)
{
	int		i;
	int		j;

	i = b;
	j = 0;
	while (map[i])
	{
		while (j < 4 && map[(i + (tets->y[j] * n_tet) + tets->x[j])] == '.' \
			&& tets->x[j] + i % n_tet < n_tet && tets->y[j] + i / n_tet < n_tet)
			j += 1;
		if (j == 4)
			break ;
		j = 0;
		i += 1;
	}
	if (j != 4)
		return (-1);
	j = 0;
	while (j < 4)
	{
		map[i + (tets->y[j] * n_tet) + tets->x[j]] = 'A' + tets->index;
		j += 1;
	}
	return (i);
}

int				fit(t_tet *tetlst, char *map, int n_tet)
{
	int		ret;
	int		last;
	int		start;

	last = 0;
	start = 0;
	if (tetlst == NULL)
		return (print(map, n_tet));
	if ((ret = fillmap(tetlst, map, n_tet, start)) > -1)
	{
		while (!fit(tetlst->next, map, n_tet))
		{
			removelast(map, tetlst->index);
			if ((ret = fillmap(tetlst, map, n_tet, ret + 1)) == -1)
				return (0);
		}
	}
	else
		return (0);
	return (1);
}
