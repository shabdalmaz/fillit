# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashabdan <ashabdan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/24 12:36:54 by ashabdan          #+#    #+#              #
#    Updated: 2020/02/24 18:40:08 by ashabdan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -c -I.
SRC = main.c utils.c reader.c solver.c
OBJECTS = $(SRC:.c=.o)
NAME = fillit

.PHONY: all clean fclean re

all:	$(NAME)

$(NAME):	$(OBJECTS)
	@$(CC) $(OBJECTS) -o $(NAME)

$(OBJECTS):
	@$(CC) $(CFLAGS) $(SRC)

fclean:	clean
	@rm -rf $(NAME)

clean:
	@rm -rf $(OBJECTS)

re:	fclean all
