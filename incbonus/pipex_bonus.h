/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:22:48 by yunlovex          #+#    #+#             */
/*   Updated: 2023/08/11 13:10:19 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		*end;
	int		cmd_nb;
	int		infile;
	int		outfile;
	int		pipes;
	int		here_doc;
	char	**cmd_paths;
	char	**cmd_arg;

}	t_pipex;

void	childs(int read, int write);

void	fork_error(t_pipex *pipex);

void	pipe_error(t_pipex *pipex);

void	exec_comand(t_pipex *pipex_args, char **envp, char *argv);

int		ft_size(char **pointer);

void	parent_free(t_pipex *pipex);

void	child_free(t_pipex *pipex);

void	close_pipes(t_pipex *pipex);

int		ft_strcmp(char *s1, char *s2);

void	here_doc(t_pipex *pipex, char **argv, int ac);

int		free_pipex(t_pipex *pipex);

#endif