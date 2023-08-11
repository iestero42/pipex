/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iestero- <iestero-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:30:51 by yunlovex          #+#    #+#             */
/*   Updated: 2023/08/11 13:21:40 by iestero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fork_error(t_pipex *pipex)
{
	parent_free(pipex);
	return (perror("Error in fork process"));
}

void	pipe_error(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex->end);
	if (pipex->here_doc > 0)
		unlink("tmp_doc.tmp");
	return (perror("Error in pipe process"));
}
