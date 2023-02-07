/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:12:59 by jose              #+#    #+#             */
/*   Updated: 2023/02/07 16:00:48 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>

# include "../libft/libft.h"

# define BAD_PARAMETERS 1
# define FILE_CANT_BE_READ 2
# define CMD_DOESNT_EXIST 3
# define CAN_NOT_REMOVE_OUTFILE 4
# define CAN_NOT_CREATE_OUTFILE 5

/*	error.c	*/
void	ft_error (int err, char *infile);

/*	cmd.c	*/
void	ft_create_outfile(char *outfile);
void	ft_remove_outfile(char *outfile);

/*	free.c	*/
void ft_free_all(char **str);

#endif