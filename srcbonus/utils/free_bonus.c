/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:17:27 by yunlovex          #+#    #+#             */
/*   Updated: 2023/12/11 12:12:47 by iestero-         ###   ########.fr       */
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
		close(pipex->end[i]);
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
int	free_pipex(t_pipex *pipex)
{
	if (pipex->infile < 0)
		close(pipex->infile);
	if (pipex->outfile < 0)
		close(pipex->outfile);
	if (pipex->here_doc > 0)
		unlink("tmp_doc.tmp");
	free(pipex);
	return (-1);
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

	i = ft_size(pipex->cmd_paths) - 1;
	close(pipex->infile);
	close(pipex->outfile);
	while (i >= 0)
	{
		free(pipex->cmd_paths[i]);
		i--;
	}
	free(pipex->cmd_paths);
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
