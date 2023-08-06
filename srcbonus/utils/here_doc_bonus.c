/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:41:29 by yunlovex          #+#    #+#             */
/*   Updated: 2023/08/06 20:08:50 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	create_temp_doc(t_pipex *pipex, char **argv)
{
	char	*line;
	char	*tmp;

	line = get_next_line(0);
	tmp = ft_strjoin(ft_strdup(argv[2]), "\n");
	while (ft_strcmp(line, tmp))
	{
		pipex->infile = open("tmp_doc.tmp", O_CREAT | O_RDWR | O_APPEND, 0644);
		if (pipex->infile < 0)
			return ;
		ft_putstr_fd(line, pipex->infile);
		line = get_next_line(0);
	}
	free(tmp);
	close(pipex->infile);
	pipex->infile = open("tmp_doc.tmp", O_RDONLY);
	pipex->here_doc = 1;
}

void	here_doc(t_pipex *pipex, char **argv, int ac)
{
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		create_temp_doc(pipex, argv);
		pipex->outfile = open(argv[ac - 1], O_CREAT | O_RDWR, 0644);
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		pipex->outfile = open(argv[ac - 1], O_CREAT | O_RDWR
				| O_TRUNC, 0644);
	}
}
