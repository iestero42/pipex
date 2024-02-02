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
 * @brief Function executed by the first child process in a pipeline.
 *
 * This function is executed by the first child process in a pipeline. It
 * handles the redirection of input and output and executes the appropriate
 * command specified in 'argv[2]'.
 *
 * @param pipex_args   Structure containing pipeline arguments and file 
 * 						descriptors.
 * @param envp         Array of environment strings.
 * @param argv         Array of arguments for the main program.
 *
 * @details
 * The 'child_one' function performs the following tasks:
 * - Redirects the input from 'pipex_args->infile' and output to '
 * 		pipex_args->end[1]'.
 * - Closes 'pipex_args->end[0]'.
 * - Executes the command specified in 'argv[2]' using 'exec_comand'.
 * - Exits with a status code of 0.
 */
void	child_one(t_pipex *pipex_args, char **envp, char **argv)
{
	if (pipex_args->infile > -1 && pipex_args->outfile > -1)
	{
		if (dup2(pipex_args->infile, 0) < 0 || dup2(pipex_args->end[1], 1) < 0)
		{
			perror("Error");
			exit(127);
		}
		if (close(pipex_args->end[0]) < 0)
		{
			perror("Error");
			exit(127);
		}
		exec_comand(pipex_args, envp, argv[2]);
	}
	exit(0);
}

/**
 * @brief Function executed by the second child process in a pipeline.
 *
 * This function is executed by the second child process in a pipeline. It
 * handles the redirection of input and output and executes the appropriate
 * command specified in 'argv[3]'.
 *
 * @param pipex_args   Structure containing pipeline arguments and file 
 * 						descriptors.
 * @param envp         Array of environment strings.
 * @param argv         Array of arguments for the main program.
 *
 * @details
 * The 'child_two' function performs the following tasks:
 * - Redirects the input from 'pipex_args->end[0]' and output to 
 * 		'pipex_args->outfile'.
 * - Closes 'pipex_args->end[1]'.
 * - Executes the command specified in 'argv[3]' using 'exec_comand'.
 * - Exits with a status code of 0.
 */
void	child_two(t_pipex *pipex_args, char **envp, char **argv)
{
	if (pipex_args->outfile > -1 && pipex_args->infile > -1)
	{
		if (dup2(pipex_args->outfile, 1) < 0 || dup2(pipex_args->end[0], 0) < 0)
		{
			perror("Error in dup");
			exit(127);
		}
		if (close(pipex_args->end[1]) < 0)
		{
			perror("Error in closing end");
			exit(127);
		}
		exec_comand(pipex_args, envp, argv[3]);
	}
	exit(0);
}
