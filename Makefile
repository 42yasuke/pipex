# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose <jose@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 17:53:47 by jose              #+#    #+#              #
#    Updated: 2023/01/31 18:27:01 by jose             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CFLAGS_OBJ = -Wall -Wextra -Werror -c

RM = rm -f

C_FILES = main.c

SRC = $(addprefix /src, $(C_FILES))

OBJ = $(SRC:.c=.o)

NAME = pipex

all : $(NAME)

libft.a :
			make -C libft

%.o : %.c
			$(CC) $(CFLAGS_OBJ) $< -o $@ -L. -lft

$(NAME) : libft.a OBJ
			$(CC) $(CFLAGS) $(OBJ) -o $@

clean :
		make clean -C libft
		$(RM) OBJ

fclean : clean
		$(RM) $(NAME) libft.a

re : fclean all

.PHONY : all fclean clean re bonus