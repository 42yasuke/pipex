/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:20:02 by jose              #+#    #+#             */
/*   Updated: 2023/04/09 02:58:29 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(int err, char *err_msg, int *fd, int is_exit)
{
	if (err == BAD_PARAMETERS)
		ft_printf("BAD PARAMETERS\n");
	if (err == FILE_CANT_BE_READ)
		ft_printf("%s: %s\n", err_msg, strerror(errno));
	else if (err == FILE_CANT_BE_READ)
		ft_printf("%s: %s\n", err_msg, strerror(errno));
	if (err == CMD_DOESNT_EXIST)
		ft_printf("%s: %s\n", err_msg, strerror(errno));
	if (err == CANT_CREATE_OUTFILE)
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
	if (is_exit)
		exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

static void	ft_strerr(t_cmd *cmd)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp = ft_strjoin(cmd->args[0], ": ");
	tmp2 = tmp;
	tmp = ft_strjoin(tmp, strerror(errno));
	free(tmp2);
	tmp2 = tmp;
	tmp = ft_strjoin(tmp, "\n");
	free(tmp2);
	(write(STDERR_FILENO, tmp, ft_strlen(tmp)), free(tmp));
}

void	ft_error2(int err, t_cmd *cmd, t_cmd *cmd_list, int *fd)
{
	(void)err;
	ft_strerr(cmd);
	ft_free_cmd(cmd_list);
	if (fd)
	{
		if (fd[0] != -1)
			close(fd[0]);
		if (fd[1] != -1)
			close(fd[1]);
	}
	exit(EXIT_BAD_CMD);
}

int	ft_error3(int ac, char **av, int is_hd)
{
	int	fd2;

	ft_printf("%s: %s\n", av[1], strerror(errno));
	fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0644);
	if (fd2 == -1)
		fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0000);
	if (fd2 == -1)
		ft_printf("%s: %s\n", av[ac - 1], strerror(errno));
	else
	{
		if (!is_hd)
			close(fd2);
		if (!access(av[1], F_OK))
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
