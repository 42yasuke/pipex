/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:15:19 by jose              #+#    #+#             */
/*   Updated: 2023/02/07 15:53:03 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_remove_outfile(char *outfile)
{
	int		pid;
	char	**args;
	int		status;

	pid = fork();
	if(!pid)
	{
		args = malloc(sizeof(*args) * (2 + 1));
		args[0] = ft_strdup("/usr/bin/rm");
		args[1] = ft_strdup("-f");
		args[2] = NULL;
		execve("/usr/bin/rm", args, NULL);
		ft_error(CAN_NOT_SUPRESS_OUTFILE, outfile);
		ft_free_all(args);
	}
	waitpid(pid, &status, 0);
}

void	ft_create_outfile(char *outfile)
{
	int	pid;
	char **args;

	ft_remove_outfile(outfile);
	pid = fork();
	if(!pid)
	{
		args = malloc(sizeof(*args) * (1 + 1));
		args[0] = ft_strdup("/usr/bin/touch");
		args[1] = NULL;
		execve("/usr/bin/touch", args, NULL);
		ft_error(CAN_NOT_REMOVE_OUTFILE, outfile);
		ft_free_all(args);
	}

}