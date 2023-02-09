/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:15:19 by jose              #+#    #+#             */
/*   Updated: 2023/02/09 03:00:27 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*ft_initialise_cmd(char **envp)
{
	t_cmd	*cmd_list;

	cmd_list = malloc(sizeof(*cmd_list));
	if (!cmd_list)
		ft_error(MALLOC_FAILLED, "malloc failed");
	cmd_list->args = NULL;
	cmd_list->path = NULL;
	cmd_list->next = NULL;
	cmd_list->envp = envp;
	return (cmd_list);
}

void	ft_add_cmd(t_cmd *cmd_list, char *cmd)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	if (!tmp->path)
	{
		tmp->next = malloc (*tmp);
		if (!tmp)
		{
			ft_free_cmd(cmd_list);
			ft_error(MALLOC_FAILLED, "malloc failed");
		}
		tmp = tmp->next;
	}
	tmp->args = ft_split(cmd, ' ');
	tmp->path = ft_get_path(tmp->args[0], cmd_list->envp);
	tmp->next = NULL;
	tmp->envp = cmd_list->envp;
}

char	*ft_get_path(char *cmd, char **envp)
{

}
