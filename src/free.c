/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jralph <jralph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:59 by jose              #+#    #+#             */
/*   Updated: 2023/04/04 02:04:32 by jralph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	ft_free_cmd(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	if (!cmd_list)
		return ;
	tmp = cmd_list;
	while (tmp)
	{
		cmd_list = tmp;
		ft_free_all(tmp->args);
		if (!access(tmp->path, X_OK))
			free(tmp->path);
		free(tmp->pipe_fd);
		tmp = tmp->next;
		free(cmd_list);
	}
}
