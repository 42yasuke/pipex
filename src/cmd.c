/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:15:19 by jose              #+#    #+#             */
/*   Updated: 2023/04/08 01:27:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_get_path2(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", ft_strlen("PATH")))
		i++;
	return (envp[i]);
}

static char	*ft_get_path(char *cmd, char **envp)
{
	char	*path_envp;
	char	**mypaths;
	int		i;
	char	*ret;
	char	*cmd_to_test;

	path_envp = ft_get_path2(envp);
	if (!path_envp)
		return (NULL);
	mypaths = ft_split(path_envp, ':');
	i = 0;
	ret = cmd;
	if (ret && !access(ret, X_OK))
		return (ft_free_all(mypaths), ret);
	cmd_to_test = ft_strjoin("/", cmd);
	while (mypaths[++i])
	{
		ret = ft_strjoin(mypaths[i], cmd_to_test);
		if (!access(ret, X_OK))
			break ;
		free(ret);
		ret = NULL;
	}
	return (free(cmd_to_test), ft_free_all(mypaths), ret);
}

t_cmd	*ft_initialise_cmd(char **envp)
{
	t_cmd	*cmd_list;

	cmd_list = malloc(sizeof(*cmd_list));
	if (!cmd_list)
		ft_error(MALLOC_FAILLED, "malloc failed", NULL, true);
	cmd_list->args = NULL;
	cmd_list->path = NULL;
	cmd_list->next = NULL;
	cmd_list->envp = envp;
	cmd_list->pid = -1;
	cmd_list->pipe_fd = NULL;
	return (cmd_list);
}

void	ft_add_cmd(t_cmd *cmd_list, char *cmd, int *fd)
{
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->path)
	{
		tmp->next = malloc (sizeof(*tmp));
		if (!tmp)
		{
			ft_free_cmd(cmd_list);
			ft_error(MALLOC_FAILLED, "malloc failed", fd, true);
		}
		tmp = tmp->next;
	}
	tmp->args = ft_split(cmd, ' ');
	tmp->next = NULL;
	tmp->envp = cmd_list->envp;
	tmp->pipe_fd = NULL;
	tmp->pid = -1;
	tmp->path = ft_get_path(tmp->args[0], cmd_list->envp);
	if (!tmp->path)
		tmp->path = cmd;
}
