# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose <jose@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 17:53:47 by jose              #+#    #+#              #
#    Updated: 2023/02/09 14:00:25 by jose             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

CFLAGS_OBJ = -Wall -Wextra -Werror -c -g

RM = rm -f

C_FILES =	main.c \
			error.c \
			free.c \
			cmd.c \
			pipex.c

SRC = $(addprefix src/, $(C_FILES))

OBJ = $(SRC:.c=.o)

INC = -I includes/

LIB = -L. -lft

NAME = pipex

all : $(NAME)

libft.a :
			make bonus -C libft

%.o : %.c
			$(CC) $(CFLAGS_OBJ) $< -o $@ $(LIB) $(INC)

$(NAME) : libft.a $(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB)

clean :
		make clean -C libft
		$(RM) $(OBJ)

fclean : clean
		$(RM) $(NAME) libft.a

re : fclean all

.PHONY : all fclean clean re bonus