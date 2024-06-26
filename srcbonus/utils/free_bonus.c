/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:17:27 by yunlovex          #+#    #+#             */
/*   Updated: 2024/04/21 11:46:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * @brief Close all pipe descriptors in the 't_pipex' structure.
 *
 * This function closes all pipe descriptors stored in the 'end' array within
 * the 't_pipex' structure. It is used to release resources related to pipes.
 *
 * @param pipex   A pointer to the 't_pipex' structure containing pipe 
 * 					descriptors.
 *
 * @details
 * The 'close_pipes' function iterates through the 'end' array and closes each
 * pipe descriptor. This is essential for proper cleanup after using pipes in
 * the pipex program.
 */
void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < 2 * pipex->pipes)
	{
		if (close(pipex->end[i]) < 0)
			perror("end");
		i++;
	}
}

/**
 * @brief Free resources and close file descriptors in 't_pipex'.
 *
 * This function frees resources associated with the 't_pipex' structure and
 * closes file descriptors (if they are open). It is used when encountering
 * errors or when freeing the 't_pipex' structure.
 *
 * @param pipex   A pointer to the 't_pipex' structure to be freed.
 *
 * @return        Always returns -1 to indicate an error condition.
 *
 * @details
 * The 'free_pipex' function checks if the input and output file descriptors
 * and here_doc-related resources need to be closed or unlinked. It then frees
 * the 't_pipex' structure itself and returns -1 to indicate an error condition.
 */
int	free_pipex(t_pipex *pipex, char *msg)
{
	if (pipex->infile > 0)
		if (close(pipex->infile) < 0)
			perror("infile");
	if (pipex->outfile > 0)
		if (close(pipex->outfile) < 0)
			perror("outfile");
	if (pipex->here_doc > 0)
		unlink("tmp_doc.tmp");
	free(pipex);
	error_msg(msg);
	return (42);
}

/**
 * @brief Free resources in 't_pipex' related to the parent process.
 *
 * This function frees resources allocated in the 't_pipex' structure that are
 * related to the parent process. It is used for cleanup in the parent process
 * after child processes have executed.
 *
 * @param pipex   A pointer to the 't_pipex' structure.
 *
 * @details
 * The 'parent_free' function performs the following tasks:
 * - Closes input and output file descriptors.
 * - Frees memory allocated for 'cmd_paths' and 'end'.
 * - Unlinks the 'tmp_doc.tmp' file if the here_doc feature was used.
 * It is responsible for cleaning up resources used by the parent process.
 */
void	parent_free(t_pipex *pipex)
{
	int	i;

	if (close(pipex->infile) < 0)
		perror("infile");
	if (close(pipex->outfile) < 0)
		perror("outfile");
	if (pipex->cmd_paths)
	{
		i = ft_size(pipex->cmd_paths) - 1;
		while (i >= 0)
		{
			free(pipex->cmd_paths[i]);
			i--;
		}
		free(pipex->cmd_paths);
	}
	free(pipex->end);
	if (pipex->here_doc > 0)
		unlink("tmp_doc.tmp");
}

/**
 * @brief Free resources in 't_pipex' related to child processes.
 *
 * This function frees resources allocated in the 't_pipex' structure that are
 * related to child processes. It is used for cleanup in child processes after
 * command execution.
 *
 * @param pipex   A pointer to the 't_pipex' structure.
 *
 * @details
 * The 'child_free' function performs the following tasks:
 * - Frees memory allocated for 'cmd_arg'.
 * It is responsible for cleaning up resources used by child processes.
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

/**
 * @brief Frees a 2D array of characters.
 *
 * This function frees a 2D array of characters 'ptr'. It first calculates the
 * size of 'ptr' using the 'ft_size' function and subtracts 1 to get the index
 * of the last element. It then enters a loop where it frees the 'i'th element
 * of 'ptr' and decrements 'i'. The loop continues until 'i' is less than 0.
 * After the loop, it frees 'ptr'.
 *
 * @param ptr  The 2D array to be freed.
 */
void	double_free(char **ptr)
{
	int	i;

	i = ft_size(ptr) - 1;
	while (i >= 0)
	{
		free(ptr[i]);
		i--;
	}
	free(ptr);
}
