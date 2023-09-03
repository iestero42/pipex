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

/**
 * Child_one:
 * * Function to be executed by the first child process in a pipeline.
 *
 * @param pipex_args   Structure containing pipeline arguments and 
 * 						file descriptors.
 * @param envp         Array of environment strings.
 * @param argv         Array of arguments for the main program.
 */
void	child_one(t_pipex *pipex_args, char **envp, char **argv)
{
	if (dup2(pipex_args->infile, 0) < 0 || dup2(pipex_args->end[1], 1) < 0)
	{
		perror("Error in dup");
		exit(1);
	}
	if (close(pipex_args->end[0]) < 0)
	{
		perror("Error in closing end");
		exit(1);
	}
	exec_comand(pipex_args, envp, argv[2]);
	exit(0);
}

/**
 * Child_one:
 * * Function to be executed by the second child process in a pipeline.
 *
 * @param pipex_args   Structure containing pipeline arguments and 
 * 						file descriptors.
 * @param envp         Array of environment strings.
 * @param argv         Array of arguments for the main program.
 */
void	child_two(t_pipex *pipex_args, char **envp, char **argv)
{
	if (dup2(pipex_args->outfile, 1) < 0 || dup2(pipex_args->end[0], 0) < 0)
	{
		perror("Error in dup");
		exit(1);
	}
	if (close(pipex_args->end[1]) < 0)
	{
		perror("Error in closing end");
		exit(1);
	}
	exec_comand(pipex_args, envp, argv[3]);
	exit(0);
}
