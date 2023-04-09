/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:02:24 by jose              #+#    #+#             */
/*   Updated: 2023/04/09 02:59:01 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_else(int *fd, int ac, char **av)
{
	int	ret_exit;

	ret_exit = INT_MAX;
	fd[0] = open(av[1], O_RDONLY, 0444);
	if (fd[0] == -1)
		ret_exit = ft_error3(ac, av, false);
	fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0644);
	if (fd[1] == -1)
		fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0000);
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

int	main(int ac, char **av, char **envp)
{
	int			fd[2];
	int			ret_exit;
	int			ret_exit2;

	if (ac < 5)
		ft_error(BAD_PARAMETERS, NULL, NULL, true);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")))
		ret_exit = ft_here_doc_manager(fd, ".here_doc", ac, av);
	else
		ret_exit = ft_else(fd, ac, av);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")))
		ret_exit2 = pipex_manager_b(fd, ac - 1, av + 1, envp);
	else
		ret_exit2 = pipex_manager(fd, ac, av, envp);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")))
		unlink(".here_doc");
	if (ret_exit == INT_MAX)
		return (close(fd[0]), close(fd[1]), ret_exit2);
	return (ret_exit);
}
