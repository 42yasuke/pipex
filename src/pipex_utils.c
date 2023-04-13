/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:46:15 by jose              #+#    #+#             */
/*   Updated: 2023/04/13 21:23:55 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_help_pipex1(int *fd, int *pipefd, t_cmd *cmd_list)
{
	if (fd[0] != -1 && fd[1] != -1)
		(dup2(fd[0], STDIN_FILENO), close(fd[0]));
	else
		(close(pipefd[0]), close(pipefd[1]), \
		ft_free_cmd(cmd_list), exit(EXIT_SUCCESS));
}

void	ft_help_pipex12(int *fd, int *pipefd, t_cmd *cmd_list)
{
	if (fd[0] != -1)
		(dup2(fd[0], STDIN_FILENO), close(fd[0]));
	else
		(close(pipefd[0]), close(pipefd[1]), \
		ft_free_cmd(cmd_list), exit(EXIT_SUCCESS));
}

void	pipex1_suite(t_cmd *cmd, t_cmd *cmd_list, int *fd)
{
	if (fd[1] != -1)
		execve(cmd->path, cmd->args, cmd->envp);
	if (access(cmd->path, X_OK))
		ft_error2(CMD_NOT_EXECUTED, cmd, cmd_list, fd);
	(ft_free_cmd(cmd_list), exit(EXIT_SUCCESS));
}

void	pipex1_else(int *pfd, int *fd)
{
	if (fd[0] != -1)
		close(fd[0]);
	(close(pfd[1]), dup2(pfd[0], STDIN_FILENO), close(pfd[0]));
}
