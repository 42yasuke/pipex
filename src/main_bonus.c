/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:02:24 by jose              #+#    #+#             */
/*   Updated: 2023/02/10 23:56:15 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_else(int *fd1, int *fd2, int ac, char **av)
{
	*fd1 = open(av[1], O_RDONLY, 0444);
	*fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0644);
	if (*fd2 == -1)
		*fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0000);
	if (*fd1 == -1)
		ft_error(FILE_CANT_BE_READ, av[1]);
	if (*fd2 == -1)
		ft_error(CAN_NOT_CREATE_OUTFILE, av[ac - 1]);
}

int	main(int ac, char **av, char **envp)
{
	int	fd1;
	int	fd2;

	if (ac < 5)
		ft_error(BAD_PARAMETERS, NULL);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")))
		ft_here_doc_manager(&fd1, &fd2, ac, av);
	else
		ft_else(&fd1, &fd2, ac, av);
	dup2(fd1, STDIN_FILENO);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")))
		pipex_manager(fd2, ac - 1, av + 1, envp);
	else
		pipex_manager(fd2, ac, av, envp);
	close(fd1);
	close(fd2);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")))
		unlink(".here_doc");
	return (0);
}
