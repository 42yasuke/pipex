# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jralph <jralph@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 17:53:47 by jose              #+#    #+#              #
#    Updated: 2023/04/05 15:31:50 by jralph           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

CFLAGS_OBJ = -Wall -Wextra -Werror -c -g

RM = rm -f

C_FILES =	error.c \
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

src/main.o : src/main.c
			$(CC) $(CFLAGS_OBJ) $< -o $@ $(LIB) $(INC)

.mandatory : libft.a $(OBJ) src/main.o
			$(CC) $(CFLAGS) $(OBJ) src/main.o -o $(NAME) $(LIB)
			touch $@
			$(RM) .bonus

$(NAME) : .mandatory

.bonus : libft.a $(OBJ) src/main_bonus.o src/here_doc_bonus.o
			$(CC) $(CFLAGS) $(OBJ) src/here_doc_bonus.o src/main_bonus.o -o $(NAME) $(LIB)
			touch $@
			$(RM) .mandatory

bonus : .bonus

clean :
		make clean -C libft
		$(RM) src/*.o

fclean : clean
		$(RM) $(NAME) libft.a .mandatory .bonus

re : fclean all

.PHONY : all fclean clean re bonus