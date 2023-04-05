/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:01:51 by jose              #+#    #+#             */
/*   Updated: 2023/04/05 12:07:29 by jralph           ###   ########.fr       */
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

static int	ft_here_doc(char *limiter, char *file_name)
{
	int		fd_ret;
	char	*line;

	fd_ret = -1;
	fd_ret = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd_ret == -1)
		return (fd_ret);
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
	return (fd_ret);
}

void	ft_here_doc_manager(int *fd, char *file_name, int ac, char **av)
{
	if (!file_name)
		return ;
	fd[0] = ft_here_doc(av[2], file_name);
	fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND | O_EXCL, 0644);
	if (fd[1] == -1)
		fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0000);
	if (fd[0] == -1)
		ft_error(FILE_CANT_BE_READ, av[1], NULL);
	if (fd[1] == -1)
		ft_error(CAN_NOT_CREATE_OUTFILE, av[ac - 1], NULL);
}
