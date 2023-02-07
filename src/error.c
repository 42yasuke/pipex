/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:20:02 by jose              #+#    #+#             */
/*   Updated: 2023/02/07 15:54:17 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error (int err, char *infile)
{
	if (err == 1)
		ft_printf("BAD PARAMETERS\n");
	if(err == 2)
		ft_printf("%s can't be read: %s\n", infile, strerror(errno));
	if (err == 3)
		ft_printf("%s: %s\n", infile, strerror(errno));
	if (err == 4)
		ft_printf("%s could not be deleted: %s\n", infile, strerror(errno));
	if (err == 5)
		ft_printf("%s could not be created: %s\n", infile, strerror(errno));
	exit(0);
}