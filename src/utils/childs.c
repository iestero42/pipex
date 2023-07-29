/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:25:02 by marvin            #+#    #+#             */
/*   Updated: 2023/07/27 14:25:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(t_pipex *pipex_args, char **envp, char **argv)
{
	dup2(pipex_args->infile, 0);
	dup2(pipex_args->end[1], 1);
	close(pipex_args->end[0]);
	exec_comand(pipex_args, envp, argv[2]);
}

void	child_two(t_pipex *pipex_args, char **envp, char **argv)
{
	dup2(pipex_args->outfile, 1);
	dup2(pipex_args->end[0], 0);
	close(pipex_args->end[1]);
	exec_comand(pipex_args, envp, argv[3]);
}
