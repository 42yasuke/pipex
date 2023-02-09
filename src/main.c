/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:15:55 by jose              #+#    #+#             */
/*   Updated: 2023/02/09 14:37:18 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	fd1;
	int	fd2;

	if (ac != 5)
		ft_error(BAD_PARAMETERS, NULL);
	fd1 = open(av[1], O_RDONLY, 0444);
	fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0244);
	if (fd1 == -1)
		ft_error(FILE_CANT_BE_READ, av[1]);
	if (fd2 == -1)
		ft_error(CAN_NOT_CREATE_OUTFILE, av[ac - 1]);
	dup2(fd1, STDIN_FILENO);
	pipex_manager(fd2, ac, av, envp);
	close(fd1);
	close(fd2);
	return (0);
}
