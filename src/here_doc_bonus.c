/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:01:51 by jose              #+#    #+#             */
/*   Updated: 2023/04/09 02:59:21 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_no_use_limitter(char *limiter)
{
	char	*str_err;
	char	*tmp;

	str_err = "\nbash: warning: here-document delimited by EOF (wanted \'";
	str_err = ft_strjoin(str_err, limiter);
	tmp = str_err;
	str_err = ft_strjoin(str_err, "\')\n");
	write(STDERR_FILENO, str_err, ft_strlen(str_err));
	(free(str_err), free(tmp));
}

static int	ft_open_it_goodly(char *file_name)
{
	int		fd_ret;

	fd_ret = open(file_name, O_CREAT | O_WRONLY | O_APPEND | O_EXCL, 0644);
	if (fd_ret == -1)
	{
		unlink(file_name);
		fd_ret = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	return (fd_ret);
}

static int	ft_here_doc(char *limiter, char *file_name)
{
	int		fd_ret;
	char	*line;

	fd_ret = ft_open_it_goodly(file_name);
	write (STDOUT_FILENO, ">", ft_strlen(">"));
	line = get_next_line(STDIN_FILENO);
	while (line && !(ft_strlen(line) == ft_strlen(limiter) + 1 && \
	!ft_strncmp(line, limiter, ft_strlen(limiter))))
	{
		(write (fd_ret, line, ft_strlen(line)), free(line));
		write (STDOUT_FILENO, ">", ft_strlen(">"));
		line = get_next_line(STDIN_FILENO);
	}
	if (ft_strncmp(line, limiter, ft_strlen(limiter)))
		ft_no_use_limitter(limiter);
	if (line)
		(get_next_line(-10), free(line));
	return (close(fd_ret), open(file_name, O_RDONLY));
}

int	ft_here_doc_manager(int *fd, char *file_name, int ac, char **av)
{
	int	ret_exit;

	ret_exit = INT_MAX;
	if (!file_name)
		return (-1);
	fd[0] = ft_here_doc(av[2], file_name);
	if (fd[0] == -1)
		ret_exit = ft_error3(ac, av, true);
	fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND | O_EXCL, 0644);
	if (fd[1] == -1)
		fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd[1] == -1)
	{
		if (fd[0] != -1)
		{
			close(fd[0]);
			ret_exit = ft_error(CANT_CREATE_OUTFILE, av[ac - 1], NULL, false);
		}
	}
	return (ret_exit);
}
