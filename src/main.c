/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:15:55 by jose              #+#    #+#             */
/*   Updated: 2023/02/09 00:04:26 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*

1. verifier que mes fichiers existes
2. si outfile existe on doit verfier les droits
3. si outfile n'existe pas on doit creer outfile et donner les droits necessairesss
4. verifier les commandes, est il possible de verifier une commande sans devoir l'executer ?

*/

int	main (int ac, char **av, char **envp)
{
	int	fd1;
	int	fd2;

	(void)envp;
	if (ac != 5)
		ft_error(BAD_PARAMETERS, NULL);
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[ac-1], O_RDWR);
	if (fd1 == -1)
		ft_error(FILE_CANT_BE_READ, av[1]);
	if (fd2 == -1)
		ft_error(CAN_NOT_CREATE_OUTFILE, av[ac-1]);
	dup2(fd1, STDIN_FILENO);
	pipex_manager(fd2, ac, av, envp);
	close(fd1);
	close(fd2);
	return (0);
}