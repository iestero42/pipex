/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:30:51 by yunlovex          #+#    #+#             */
/*   Updated: 2024/01/24 10:42:48 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	perror("pipe");
}
