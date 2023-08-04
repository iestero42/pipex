/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:35:02 by marvin            #+#    #+#             */
/*   Updated: 2023/04/11 10:35:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	int		end[2];
	int		infile;
	int		outfile;
	char	**cmd_paths;
	char	**cmd_arg;

}	t_pipex;

void	exec_comand(t_pipex *pipex_args, char **envp, char *argv);

void	child_two(t_pipex *pipex_args, char **envp, char **argv);

void	child_one(t_pipex *pipex_args, char **envp, char **argv);

void	exec_comand(t_pipex *pipex_args, char **envp, char *argv);

void	parent_free(t_pipex *pipex);

void	close_pipes(int *end);

void	parent_free(t_pipex *pipex);

void	child_free(t_pipex *pipex);

int		ft_size(char **pointer);

void	fork_error(t_pipex *pipex);

void	pipe_error(t_pipex *pipex);

#endif