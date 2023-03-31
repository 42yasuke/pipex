/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:39:29 by jose              #+#    #+#             */
/*   Updated: 2023/03/31 16:19:23 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_is_cmd_yes(char *path)
{
	size_t	i;

	i = 0;
	while (path[i] && i < (ft_strlen(path) - 2))
	{
		if (path[i] == 'y' && path[i + 1] == 'e' && path[i + 2] == 's')
			return (true);
		i++;
	}
	return (false);
}

static void	pipex2(t_cmd *cmd, t_cmd *cmd_list, int *pfd, int fd2)
{
	int	pid;
	int	pipefd[2];

	pid = fork();
	if (pid == -1)
		ft_error(FORK_FAILED, "fork failed");
	if (pipe(pipefd))
		ft_error(PIPE_FAILED, "pipe failed");
	(close(pfd[1]), dup2(pfd[0], STDIN_FILENO), close(pfd[0]));
	if (pid && cmd->next)
		pipex1(cmd->next, cmd_list, pipefd, fd2);
	else
		dup2(fd2, STDOUT_FILENO);
	if (!pid)
	{
		if (cmd->next)
			(close(pipefd[0]), dup2(pipefd[1], STDOUT_FILENO), \
			close(pipefd[1]));
		execve(cmd->path, cmd->args, cmd->envp);
		ft_error2(CMD_NOT_EXECUTED, cmd, cmd_list);
	}
	if (cmd->pid == -1)
		cmd->pid = pid;
}

void	pipex1(t_cmd *cmd, t_cmd *cmd_list, int *pfd, int fd2)
{
	int		pid;
	int		pipefd[2];

	(void)pfd;
	if (pipe(pipefd))
		ft_error(PIPE_FAILED, "pipe failed");
	pid = fork();
	if (pid == -1)
		ft_error(FORK_FAILED, "fork failed");
	if (pfd)
		(close(pfd[1]), dup2(pfd[0], STDIN_FILENO), close(pfd[0]));
	if (pid && cmd->next)
		pipex2(cmd->next, cmd_list, pipefd, fd2);
	else
		dup2(fd2, STDOUT_FILENO);
	if (!pid)
	{
		if (cmd->next)
			(close(pipefd[0]), dup2(pipefd[1], STDOUT_FILENO), \
			close(pipefd[1]));
		execve(cmd->path, cmd->args, cmd->envp);
		ft_error2(CMD_NOT_EXECUTED, cmd, cmd_list);
	}
	if (cmd->pid == -1)
		cmd->pid = pid;
}

void	pipex_manager(int fd2, int ac, char **av, char **envp)
{
	int		i;
	t_cmd	*cmd_list;
	t_cmd	*tmp;

	i = 2;
	cmd_list = ft_initialise_cmd(envp);
	while (i < ac - 1)
	{
		ft_add_cmd(cmd_list, av[i]);
		i++;
	}
	tmp = cmd_list;
	pipex1(tmp, cmd_list, NULL, fd2);
	while (tmp)
	{
		if (!ft_is_cmd_yes(tmp->path))
			waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	ft_free_cmd(cmd_list);
}
