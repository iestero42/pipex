/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunlovex <yunlovex@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:41:29 by yunlovex          #+#    #+#             */
/*   Updated: 2023/08/06 12:58:32 by yunlovex         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc(t_pipex *pipex, char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (!ft_strcmp(argv[1], "here_doc"))
		create_temp_doc(pipex, argv);
	else
		pipex_args->infile = open(argv[1], O_RDONLY);
}

void	create_temp_doc(t_pipex *pipex, char **argv)
{
	char	*line;

	line = get_next_line(0);
	while (ft_strcmp(line, argv[2]))
	{
		pipex->infile = open("tmp_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (pipex->infile < 0)
			return ;
		ft_putstr_fd(line, pipex->infile);
		line = get_next_line(0);
	}
	pipex->here_doc = 1;
}
