/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:15:55 by jose              #+#    #+#             */
/*   Updated: 2023/04/05 12:45:32 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	fd[2];
	int	ret_exit;

	if (ac != 5)
		ft_error(BAD_PARAMETERS, NULL, NULL);
	fd[0] = open(av[1], O_RDONLY, 0444);
	fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0644);
	if (fd[1] == -1)
		fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0000);
	if (fd[0] == -1)
		(close(fd[1]), ft_error(FILE_CANT_BE_READ, av[1], NULL));
	if (fd[1] == -1)
		(close(fd[0]), ft_error(CAN_NOT_CREATE_OUTFILE, av[ac - 1], NULL));
	ret_exit = pipex_manager(fd, ac, av, envp);
	return (close(fd[0]), close(fd[1]), ret_exit);
}
