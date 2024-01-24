/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:30:51 by yunlovex          #+#    #+#             */
/*   Updated: 2024/01/24 11:13:57 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * @brief Handles errors during pipe process and cleans up resources.
 *
 * This function handles errors that may occur during the pipe creation process.
 * It is responsible for cleaning up resources associated with the pipeline,
 * including file descriptors, and printing an error message using 'perror'.
 *
 * @param pipex   A pointer to the 't_pipex' structure containing pipeline
 *                arguments and file descriptors.
 *
 * @return        -1 to indicate an error condition.
 *
 * @details
 * The 'pipe_error' function is typically called when there is an error in
 * creating pipes using the 'pipe' system call. It performs cleanup by closing
 * file descriptors, freeing allocated memory, and, if applicable, removing a
 * temporary file created for the here document feature.
 *
 * @note
 * This function should be used to handle pipe-related errors and should be
 * called when 'pipe' system calls fail.
 */
void	pipe_error(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex->end);
	if (pipex->here_doc > 0)
		unlink("tmp_doc.tmp");
	perror("pipex");
}

/**
 * @brief Displays an error message and returns an error code.
 *
 * This function displays an error message using 'ft_printf' and returns an error
 * code (-1) to indicate an error condition. It is used to report custom error
 * messages with additional context.
 *
 * @param str   The error message string to be displayed.
 *
 * @return      -1 to indicate an error condition.
 *
 * @details
 * The 'error_msg' function is typically called to report custom error messages.
 * It prints the provided error message using 'ft_printf' to the standard output
 * and returns -1 to signal an error condition.
 *
 * @note
 * This function should be used to display informative error messages when
 * necessary and to indicate that an error has occurred.
 */
int	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (-1);
}
