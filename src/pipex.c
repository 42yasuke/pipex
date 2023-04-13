/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:39:29 by jose              #+#    #+#             */
/*   Updated: 2023/04/13 21:23:11 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	*pipex1(t_cmd *cmd, t_cmd *cmd_list, int *pfd, int *fd)
{
	int		pid;
	int		*pipefd;

	pipefd = malloc(sizeof(*pipefd) * 2);
	if (pipe(pipefd))
		ft_error(PIPE_FAILED, "pipe failed", fd, true);
	cmd->pipe_fd = pipefd;
	pid = fork();
	if (pid == -1)
		ft_error(FORK_FAILED, "fork failed", fd, true);
	if (!pid)
	{
		if (fd[1] != -1)
			close(fd[1]);
		if (!pfd)
			ft_help_pipex1(fd, pipefd, cmd_list);
		else
			pipex1_else(pfd, fd);
		(close(pipefd[0]), dup2(pipefd[1], STDOUT_FILENO), close(pipefd[1]));
		execve(cmd->path, cmd->args, cmd->envp);
		ft_error2(CMD_NOT_EXECUTED, cmd, cmd_list, fd);
	}
	return (cmd->pid = pid, pipefd);
}

static void	pipex2(t_cmd *cmd, t_cmd *cmd_list, int *pfd, int *fd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error(FORK_FAILED, "fork failed", fd, true);
	if (!pid)
	{
		if (fd[0] != -1)
			close(fd[0]);
		(close(pfd[1]), dup2(pfd[0], STDIN_FILENO), close(pfd[0]));
		if (fd[1] != -1)
			(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
		else
			(ft_free_cmd(cmd_list), exit(EXIT_SUCCESS));
		execve(cmd->path, cmd->args, cmd->envp);
		ft_error2(CMD_NOT_EXECUTED, cmd, cmd_list, fd);
	}
	cmd->pid = pid;
	cmd->pipe_fd = NULL;
}

static void	pipex_manager3(t_cmd *tmp, t_cmd *cmd_list, int *pipe_fd, int *fd)
{
	t_cmd	*tmp2;

	tmp2 = cmd_list;
	pipex2(tmp, cmd_list, pipe_fd, fd);
	while (tmp2)
	{
		if (tmp2->pipe_fd)
			(close(tmp2->pipe_fd[0]), close(tmp2->pipe_fd[1]));
		tmp2 = tmp2->next;
	}
}

static void	pipex_manager2(int *fd, t_cmd *cmd_list)
{
	t_cmd	*tmp2;
	t_cmd	*tmp;
	int		*pipe_fd;
	int		i;

	tmp = cmd_list;
	tmp2 = tmp;
	i = 0;
	pipe_fd = NULL;
	while (tmp->next)
	{
		if (i > 1)
			if (tmp2->pipe_fd)
				(close(tmp2->pipe_fd[0]), close(tmp2->pipe_fd[1]));
		pipe_fd = pipex1(tmp, cmd_list, pipe_fd, fd);
		tmp = tmp->next;
		if (i > 1)
			tmp2 = tmp2->next;
		i++;
	}
	if (i > 1)
		(close(tmp2->pipe_fd[0]), close(tmp2->pipe_fd[1]));
	pipex_manager3(tmp, cmd_list, pipe_fd, fd);
}

int	pipex_manager(int *fd, int ac, char **av, char **envp)
{
	int		i;
	t_cmd	*cmd_list;
	t_cmd	*tmp;

	i = 2;
	cmd_list = ft_initialise_cmd(envp);
	while (i < ac - 1)
	{
		ft_add_cmd(cmd_list, av[i], fd);
		i++;
	}
	pipex_manager2(fd, cmd_list);
	tmp = cmd_list;
	while (tmp)
	{
		waitpid(tmp->pid, &i, 0);
		tmp = tmp->next;
	}
	ft_free_cmd(cmd_list);
	if (!i)
		return (EXIT_SUCCESS);
	return (EXIT_BAD_CMD);
}
