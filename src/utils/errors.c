/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:30:51 by yunlovex          #+#    #+#             */
/*   Updated: 2023/09/07 16:20:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Handles errors during fork process and cleans up resources.
 *
 * This function handles errors that may occur during the fork process in
 * the pipeline. It performs cleanup by calling 'parent_free' and prints
 * an error message using 'perror'.
 *
 * @param pipex   Structure containing pipeline arguments and file descriptors.
 *
 * @details
 * The 'fork_error' function is called when an error occurs during the fork
 * process. It performs the following tasks:
 * - Calls 'parent_free' to clean up resources allocated in the parent process.
 * - Prints an error message using 'perror'.
 */
void	fork_error(t_pipex *pipex)
{
	parent_free(pipex);
	perror("Error in fork process");
}

/**
 * @brief Handles errors during pipe process and cleans up resources.
 *
 * This function handles errors that may occur during the pipe process in
 * the pipeline. It performs cleanup by closing input and output file
 * descriptors and prints an error message using 'perror'.
 *
 * @param pipex   Structure containing pipeline arguments and file descriptors.
 *
 * @details
 * The 'pipe_error' function is called when an error occurs during the pipe
 * process. It performs the following tasks:
 * - Closes the input and output file descriptors.
 * - Prints an error message using 'perror'.
 */
void	pipe_error(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	return (perror("Error in pipe process"));
}

/**
 * @brief Prints an error message using perror and returns a status code (-1).
 *
 * This function prints an error message using 'perror' and returns a status
 * code of -1 to indicate an error condition.
 *
 * @param str   The error message string.
 *
 * @return      A status code (-1).
 *
 * @details
 * The 'error_msg' function is used to print error messages with 'perror'
 * and return a status code of -1. It simplifies error reporting in the
 * pipeline program.
 */
int	error_msg(char *str)
{
	perror(str);
	return (-1);
}
