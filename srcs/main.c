/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashabdan <ashabdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 23:34:40 by ashabdan          #+#    #+#             */
/*   Updated: 2020/02/24 18:00:45 by ashabdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		print_error(int err)
{
	if (err == 1)
		write(1, "usage: ./fillit source_file\n", 29);
	else if (err == 2)
		write(1, "error\n", 7);
	exit(EXIT_FAILURE);
}

static int		reader(int fd, t_tet **tets)
{
	int		read_bytes;
	int		amount;
	char	buf[BUF_SIZE + 1];

	ft_bzero(buf, BUF_SIZE + 1);
	amount = 0;
	read_bytes = BUF_SIZE;
	while (read_bytes == BUF_SIZE)
	{
		read_bytes = read(fd, buf, BUF_SIZE);
		if (validator(buf))
		{
			*tets = addnode(*tets, buf, amount);
			amount += 1;
		}
		else
		{
			cleanlst(tets);
			return (-1);
		}
		ft_bzero(buf, BUF_SIZE);
	}
	return (amount);
}

static void		solver(t_tet *tetlst, int map_size)
{
	char	*map;
	int		ret;

	map = newmap(map_size);
	while (!(ret = fit(tetlst, map, map_size)))
	{
		free(map);
		map_size += 1;
		map = newmap(map_size);
	}
	free(map);
}

int				main(int argc, char *argv[])
{
	int		fd;
	t_tet	*tets;
	int		n_tet;

	tets = NULL;
	if (argc != 2)
		print_error(1);
	fd = open(argv[1], O_RDONLY);
	if ((n_tet = reader(fd, &tets)) > 0 && n_tet < 27)
	{
		solver(tets, ft_sqrt(n_tet * 4));
		cleanlst(&tets);
	}
	else
		print_error(2);
	close(fd);
	return (0);
}
