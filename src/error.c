/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:20:02 by jose              #+#    #+#             */
/*   Updated: 2023/02/09 02:24:35 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error (int err, char *infile)
{
	if (err == BAD_PARAMETERS)
		ft_printf("BAD PARAMETERS\n");
	if(err == FILE_CANT_BE_READ)
		ft_printf("%s can't be read: %s\n", infile, strerror(errno));
	if (err == CMD_DOESNT_EXIST)
		ft_printf("%s: %s\n", infile, strerror(errno));
	if (err == CAN_NOT_CREATE_OUTFILE)
		ft_printf("%s could not be created: %s\n", infile, strerror(errno));
	if (err == CMD_NOT_FOUND)
		ft_printf("%s : %s\n", infile, strerror(errno));
	if (err == FORK_FAILED)
		ft_printf("%s : %s\n", infile, strerror(errno));
	if (err == PIPE_FAILED)
		ft_printf("%s : %s\n", infile, strerror(errno));
	if (err == MALLOC_FAILLED)
		ft_printf("%s : %s\n", infile, strerror(errno));
	exit(EXIT_FAILURE);
}