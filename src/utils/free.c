/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:17:27 by yunlovex          #+#    #+#             */
/*   Updated: 2023/09/07 15:49:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Close both read and write ends of a pipe.
 *
 * This function closes both the read and write ends of a pipe, as represented
 * by the file descriptors in the 'end' array.
 *
 * @param end   Array of integers representing pipe file descriptors.
 *
 * @details
 * The 'close_pipes' function takes an array of pipe file descriptors 'end' and
 * closes both the read and write ends of the pipe. It ensures proper cleanup
 * of pipe resources used in the pipeline.
 */
void	close_pipes(int *end)
{
	close(end[0]);
	close(end[1]);
}

/**
 * @brief Free resources allocated in the parent process.
 *
 * This function frees resources allocated in the parent process of the pipeline.
 * It is responsible for closing file descriptors and releasing memory related to
 * the parent process.
 *
 * @param pipex   Structure containing pipeline arguments and file descriptors.
 *
 * @details
 * The 'parent_free' function performs the following tasks:
 * - Closes the input and output file descriptors.
 * - Frees memory allocated for 'cmd_paths'.
 * It is essential for proper cleanup in the parent process.
 */
void	parent_free(t_pipex *pipex)
{
	int	i;

	i = ft_size(pipex->cmd_paths) - 1;
	close(pipex->infile);
	close(pipex->outfile);
	while (i >= 0)
	{
		free(pipex->cmd_paths[i]);
		i--;
	}
	free(pipex->cmd_paths);
}

/**
 * @brief Free resources allocated in the child process.
 *
 * This function frees resources allocated in the child process of the pipeline.
 * It is responsible for releasing memory related to the child process.
 *
 * @param pipex   Structure containing pipeline arguments and file descriptors.
 *
 * @details
 * The 'child_free' function performs the following tasks:
 * - Frees memory allocated for 'cmd_arg'.
 * It is essential for proper cleanup in child processes.
 */
void	child_free(t_pipex *pipex)
{
	int	i;

	i = ft_size(pipex->cmd_arg) - 1;
	while (i >= 0)
	{
		free(pipex->cmd_arg[i]);
		i--;
	}
	free(pipex->cmd_arg);
}
