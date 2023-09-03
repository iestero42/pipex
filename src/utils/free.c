/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:17:27 by yunlovex          #+#    #+#             */
/*   Updated: 2023/09/03 11:48:42 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Close_pipes:
 * * Closes both read and write ends of a pipe.
 *
 * @param end   Array of integers representing pipe file descriptors.
 */
void	close_pipes(int *end)
{
	close(end[0]);
	close(end[1]);
}

/**
 * Parent_free:
 * * Frees resources allocated in the parent process.
 *
 * @param pipex   Structure containing pipeline arguments and file descriptors.
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
 * Child_free:
 * * Frees resources allocated in the child process.
 *
 * @param pipex   Structure containing pipeline arguments and file descriptors.
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
