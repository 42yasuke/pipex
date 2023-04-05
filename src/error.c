/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:20:02 by jose              #+#    #+#             */
/*   Updated: 2023/04/05 12:38:24 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int err, char *err_msg, int *fd)
{
	if (err == BAD_PARAMETERS)
		ft_printf("BAD PARAMETERS\n");
	if (err == FILE_CANT_BE_READ && !access(err_msg, F_OK))
		(ft_printf("%s: %s\n", err_msg, strerror(errno)), exit(EXIT_SUCCESS));
	else if (err == FILE_CANT_BE_READ)
		ft_printf("%s: %s\n", err_msg, strerror(errno));
	if (err == CMD_DOESNT_EXIST)
		ft_printf("%s: %s\n", err_msg, strerror(errno));
	if (err == CAN_NOT_CREATE_OUTFILE)
		ft_printf("%s: %s\n", err_msg, strerror(errno));
	if (err == CMD_NOT_FOUND)
		ft_printf("%s: %s\n", err_msg, strerror(errno));
	if (err == FORK_FAILED)
		ft_printf("%s: %s\n", err_msg, strerror(errno));
	if (err == PIPE_FAILED)
		ft_printf("%s : %s\n", err_msg, strerror(errno));
	if (err == MALLOC_FAILLED)
		ft_printf("%s : %s\n", err_msg, strerror(errno));
	if (fd)
		(close(fd[0]), close(fd[1]));
	exit(EXIT_FAILURE);
}

void	ft_error2(int err, t_cmd *cmd_list, int *fd)
{
	char	*tmp;

	tmp = NULL;
	if (err == CMD_NOT_EXECUTED)
	{
		tmp = ft_strjoin(strerror(errno), "\n");
		write(STDERR_FILENO, tmp, ft_strlen(tmp));
		free(tmp);
		ft_free_cmd(cmd_list);
	}
	if (fd)
		(close(fd[0]), close(fd[1]));
	exit(EXIT_BAD_CMD);
}
