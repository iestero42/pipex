/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:17:27 by yunlovex          #+#    #+#             */
/*   Updated: 2023/08/06 20:11:08 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < 2 *pipex->pipes)
	{
		close(pipex->end[i]);
		i++;
	}
}

int	free_struct(t_pipex *pipex)
{
	free(pipex);
	return (-1);
}

void	free_pipes(t_pipex *pipex)
{
	close_pipes(pipex);
	free(pipex->end);
	close(pipex->infile);
	close(pipex->outfile);
}

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
	if (pipex->here_doc > 0)
		unlink("tmp_doc.tmp");
}

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
