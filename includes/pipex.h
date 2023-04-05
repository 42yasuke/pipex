/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose <jose@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:12:59 by jose              #+#    #+#             */
/*   Updated: 2023/04/05 23:02:08 by jose             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <string.h>
# include <stdbool.h>

# include "../libft/libft.h"

# define BAD_PARAMETERS 1
# define FILE_CANT_BE_READ 2
# define CMD_DOESNT_EXIST 3
# define CAN_NOT_CREATE_OUTFILE 4
# define CMD_NOT_FOUND 5
# define CMD_NOT_EXECUTED 1
# define FORK_FAILED 6
# define PIPE_FAILED 7
# define MALLOC_FAILLED 8
# define EXIT_BAD_CMD 127

typedef struct s_cmd
{
	char			*path;
	char			**args;
	char			**envp;
	struct s_cmd	*next;
	int				pid;
	int				*pipe_fd;
}	t_cmd;

/*	error.c	*/
void	ft_error(int err, char *infile, int *fd);
void	ft_error2(int err, t_cmd *cmd_list, int *fd);
void	ft_error3(int ac, char **av, int is_hd);

/*	cmd.c	*/
t_cmd	*ft_initialise_cmd(char **envp);
void	ft_add_cmd(t_cmd *cmd_list, char *cmd, int *fd);

/*	free.c	*/
void	ft_free_all(char **str);
void	ft_free_cmd(t_cmd *cmd_list);

/*	pipex.c	*/
int		pipex_manager(int *fd, int ac, char **av, char **envp);

/*	here_doc_bonus.c	*/
void	ft_here_doc_manager(int *fd, char *file_name, int ac, char **av);

#endif