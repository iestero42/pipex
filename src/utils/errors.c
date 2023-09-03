/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:30:51 by yunlovex          #+#    #+#             */
/*   Updated: 2023/09/03 11:48:51 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Fork_error:
 * * Handles errors that occur during the fork process and cleans up resources.
 *
 * @param pipex   Structure containing pipeline arguments and file descriptors.
 */
void	fork_error(t_pipex *pipex)
{
	parent_free(pipex);
	perror("Error in fork process");
}

/**
 * Pipe_error:
 * * Handles errors that occur during the pipe process and cleans up resources.
 *
 * @param pipex   Structure containing pipeline arguments and file descriptors.
 */
void	pipe_error(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	return (perror("Error in pipe process"));
}

/**
 * Error_msg:
 * * Prints an error message using perror and returns a status code (-1).
 *
 * @param str   The error message string.
 * @return      A status code (-1).
 */
int	error_msg(char *str)
{
	perror(str);
	return (-1);
}
