/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 09:22:48 by yunlovex          #+#    #+#             */
/*   Updated: 2023/08/03 19:31:55 by yunlovex         ###   ########.fr       */
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
	char	**cmd_paths;
	char	**cmd_arg;

}	t_pipex;

void	childs(int read, int write);

void	fork_error(t_pipex *pipex);

void	pipe_error(t_pipex *pipex);

void	exec_comand(t_pipex *pipex_args, char **envp, char *argv);

int		ft_size(char **pointer);

void	parent_free(t_pipex *pipex);

void	free_pipes(t_pipex *pipex);

void	child_free(t_pipex *pipex);

#endif