/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:20:02 by jose              #+#    #+#             */
/*   Updated: 2023/02/09 15:26:00 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int err, char *err_msg)
{
	if (err == BAD_PARAMETERS)
		ft_printf("BAD PARAMETERS\n");
	if (err == FILE_CANT_BE_READ)
		ft_printf("%s can't be read: %s\n", err_msg, strerror(errno));
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
	exit(EXIT_FAILURE);
}

void	ft_error2(int err, t_cmd *cmd, t_cmd *cmd_list)
{
	if (err == CMD_NOT_EXECUTED)
	{
		ft_printf("%s: %s\n", cmd->args[0], strerror(errno));
		ft_free_cmd(cmd_list);
	}
	exit(EXIT_FAILURE);
}
