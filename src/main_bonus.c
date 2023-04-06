/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:02:24 by jose              #+#    #+#             */
/*   Updated: 2023/04/06 21:32:59 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_find_a_good_file_name(void)
{
	char	*file_name;
	char	*tmp;

	file_name = ft_strdup("/tmp/.here_doc");
	while (file_name && !access(file_name, F_OK))
	{
		tmp = file_name;
		file_name = ft_strjoin(file_name, "a");
		free(tmp);
	}
	return (file_name);
}

static void	ft_else(int *fd, int ac, char **av)
{
	fd[0] = open(av[1], O_RDONLY, 0444);
	if (fd[0] == -1)
		ft_error3(ac, av, false);
	fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC | O_EXCL, 0644);
	if (fd[1] == -1)
		fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0000);
	if (fd[1] == -1)
	{
		if (fd[0] != -1)
			close(fd[0]);
		ft_error(CAN_NOT_CREATE_OUTFILE, av[ac - 1], NULL);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	char	*file_name;
	int		ret_exit;

	if (ac < 5)
		ft_error(BAD_PARAMETERS, NULL, NULL);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")))
	{
		file_name = ft_find_a_good_file_name();
		ft_here_doc_manager(fd, file_name, ac, av);
	}
	else
		ft_else(fd, ac, av);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")))
		ret_exit = pipex_manager(fd, ac - 1, av + 1, envp);
	else
		ret_exit = pipex_manager(fd, ac, av, envp);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")))
		(unlink(file_name), free(file_name));
	return (close(fd[0]), close(fd[1]), ret_exit);
}
