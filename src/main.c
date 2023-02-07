/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:15:55 by jose              #+#    #+#             */
/*   Updated: 2023/02/07 15:56:15 by jose             ###   ########.fr       */
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
	(void)av;
	(void)envp;
	if (ac != 5)
		ft_error(BAD_PARAMETERS, NULL);
	if (access(av[1], R_OK))
		ft_error(FILE_CANT_BE_READ, av[1]);
	if (access(av[ac-1]), R_OK | W_OK)
		ft_create_outfile(av[ac-1]);
	return (0);
}