/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:39:59 by jose              #+#    #+#             */
/*   Updated: 2023/02/09 14:34:27 by jose             ###   ########.fr       */
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
		free(tmp->path);
		tmp = tmp->next;
		free(cmd_list);
	}
}
