/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:01:51 by jose              #+#    #+#             */
/*   Updated: 2023/02/10 15:34:17 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_here_doc(char *limiter)
{
	int		fd_ret;
	char	*line;

	fd_ret = -1;
	fd_ret = open(".here_doc", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd_ret == -1)
		return (fd_ret);
	write (STDOUT_FILENO, ">", ft_strlen(">"));
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) && \
	ft_strncmp(line, limiter, ft_strlen(limiter)) != -1)
	{
		write (fd_ret, line, ft_strlen(line));
		free(line);
		write (STDOUT_FILENO, ">", ft_strlen(">"));
		line = get_next_line(STDIN_FILENO);
	}
	if (!line)
		(close(fd_ret), fd_ret = -1);
	free(line);
	return (fd_ret);
}

void	ft_here_doc_manager(int *fd1, int *fd2, int ac, char **av)
{
	*fd1 = ft_here_doc(av[2]);
	*fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND | O_EXCL, 0644);
	if (*fd2 == -1)
		*fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0000);
	if (*fd1 == -1)
		ft_error(FILE_CANT_BE_READ, av[1]);
	if (*fd2 == -1)
		ft_error(CAN_NOT_CREATE_OUTFILE, av[ac - 1]);
}
