/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:41:29 by yunlovex          #+#    #+#             */
/*   Updated: 2023/09/07 15:38:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * @brief Create a temporary document for 'here_doc' input.
 *
 * This function reads input lines from the standard input until a line
 * matching the specified delimiter is encountered. It appends each line to
 * a temporary document file named 'tmp_doc.tmp'. The input is used for
 * 'here_doc' processing in the pipeline.
 *
 * @param pipex   A pointer to the 't_pipex' structure.
 * @param argv    Command-line arguments passed to the program.
 *
 * @details
 * The 'create_temp_doc' function reads lines from the standard input and 
 * appends them to a temporary document file until a line matching the delimiter
 * (specified in 'argv[2]') is encountered. The input lines are read using 
 * 'get_next_line' and are written to the 'tmp_doc.tmp' file using 
 * 'ft_putstr_fd'. Once the delimiter is found, the function closes the input 
 * file descriptor and sets 'pipex->infile' to the descriptor of 'tmp_doc.tmp'. 
 * Additionally, it sets 'pipex->here_doc' to 1 to indicate that 'here_doc' 
 * input is active.
 */
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
		free(line);
		line = get_next_line(0);
	}
	free(tmp);
	free(line);
	close(pipex->infile);
	pipex->infile = open("tmp_doc.tmp", O_RDONLY);
	pipex->here_doc = 1;
}

/**
 * @brief Handle 'here_doc' input processing.
 *
 * This function checks if the first argument in 'argv' is "here_doc." If it is,
 * it invokes 'create_temp_doc' to create a temporary document with input lines.
 * Otherwise, it opens input and output files as specified in the 'argv' array.
 *
 * @param pipex   A pointer to the 't_pipex' structure.
 * @param argv    Command-line arguments passed to the program.
 * @param ac      The number of command-line arguments.
 *
 * @details
 * The 'here_doc' function is responsible for handling 'here_doc' input 
 * processing and setting up the input and output files for the pipeline. 
 * If the first argument in 'argv' is "here_doc," it calls 'create_temp_doc' 
 * to create a temporary document for input. Otherwise, it opens the input file 
 * specified in 'argv[1]' and the output file specified in 'argv[ac - 1]' 
 * for the pipeline.
 */
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
