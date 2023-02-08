/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:39:29 by jose              #+#    #+#             */
/*   Updated: 2023/02/09 00:23:51 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_manager(int fd2, int ac, char **av, char **envp)
{
	int		i;
	t_cmd	*cmd_list;
	t_cmd	*tmp;

	i = 1;
	/*

	obtetir le chamin de chaque comande
	faire une liste chainee des commandes

	*/
	while (i < ac - 1)
	{
		
		i++;
	}
	tmp = cmd_list;
	while (tmp->next != NULL)
	{
		pipex1(tmp);
		tmp = tmp->next;
	}
	dup2(fd2, STDOUT_FILENO);
	pipex2(tmp);
	ft_free_cmd(cmd_list);
}

void	pipex1(t_cmd *cmd)
{
	int	pipefd[2];
	int	pid;

	if (pipe(pipefd))
		ft_error(PIPE_FAILED, "pipe failed");
	pid = fork();
	if (pid == -1)
		ft_error(FORK_FAILED, "fork failed");
	if (!pid)
	{
		close(pipefd[0]);
		dup2(pipfd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(cmd->path, cmd->args, cmd->envp);
		ft_error(CMD_NOT_FOUND, cmd->args[0]);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	waitpid(pid, NULL, 0);
}

void	pipex2(t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error(FORK_FAILED, "fork failed");
	if (!pid)
	{
		execve(cmd->path, cmd->args, cmd->envp);
		ft_error(CMD_NOT_FOUND, cmd->args[0]);
	}
	waitpid(pid, NULL, 0);
}
