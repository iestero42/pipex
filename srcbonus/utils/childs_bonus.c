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

#include "pipex_bonus.h"

/**
 * @brief Redirects standard input and output for a child process.
 *
 * This function redirects the standard input (stdin) and standard output 
 * (stdout) file descriptors for a child process to the specified input and 
 * output file descriptors. It uses the 'dup2' system call to achieve this 
 * redirection.
 *
 * @param read   The file descriptor to be used as the new standard input 
 * 					(stdin).
 * @param write  The file descriptor to be used as the new standard output 
 * 					(stdout).
 *
 * @details
 * The 'childs' function is typically called in a child process created by the 
 * 'fork' system call. It is used to set up the input and output 
 * for the child process, allowing it to read from 'read' and write to 'write' 
 * file descriptors, effectively establishing communication with other processes 
 * in a pipeline.
 *
 * If the 'dup2' operation fails, an error message is printed using 'perror', 
 * and the child process exits with an error code. This function should be used 
 * in the context of a child process, and any necessary error handling should be 
 * performed by the parent process.
 */
void	childs(int read, int write)
{
	if (dup2(read, 0) < 0
		|| dup2(write, 1) < 0)
	{
		perror("Error in dup");
		exit(1);
	}
}
