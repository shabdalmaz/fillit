/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashabdan <ashabdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 23:34:52 by ashabdan          #+#    #+#             */
/*   Updated: 2020/02/24 17:59:33 by ashabdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# define BUF_SIZE 21

typedef struct	s_tet
{
	int				x[4];
	int				y[4];
	int				index;
	struct s_tet	*next;
}				t_tet;

/*
** Reader functions
*/

int				validator(char *str);
t_tet			*addnode(t_tet *tet_node, char *str, int index);
void			cleanlst(t_tet **tets);

/*
** Solver functions
*/

char			*newmap(int	map_size);
int				fit(t_tet *tetlst, char *map, int n_tet);

/*
** Utils functions
*/

void			ft_bzero(void *s, size_t n);
int				ft_sqrt(int n);

#endif
