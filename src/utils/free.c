/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:17:27 by yunlovex          #+#    #+#             */
/*   Updated: 2023/08/02 17:29:41 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(int *end)
{
	close(end[0]);
	close(end[1]);
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
