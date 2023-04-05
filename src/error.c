/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:20:02 by jose              #+#    #+#             */
/*   Updated: 2023/04/05 23:03:00 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int err, char *err_msg, int *fd)
{
	if (err == BAD_PARAMETERS)
		ft_printf("BAD PARAMETERS\n");
	if (err == FILE_CANT_BE_READ)
		ft_printf("%s: %s\n", err_msg, strerror(errno));
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

void	ft_error3(int ac, char **av, int is_hd)
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
			exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
