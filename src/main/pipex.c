/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:34:50 by marvin            #+#    #+#             */
/*   Updated: 2023/04/11 10:34:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Find_path:
 * * Finds and returns the 'PATH' environment variable value from the given 
 * * environment strings.
 *
 * @param envp   Array of environment strings.
 * @return       A pointer to the 'PATH' environment variable value.
 */
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

/**
 * Pipex:
 * * Executes a pipeline process with two child processes.
 *
 * @param pipex_args   Structure containing arguments and 
 * 						file descriptors for the pipeline.
 * @param envp         Array of environment strings.
 * @param argv         Array of arguments for the main program.
 */
void	pipex(t_pipex *pipex_args, char **envp, char **argv)
{
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipex_args->end) < 0)
		return (pipe_error(pipex_args));
	pipex_args->cmd_paths = ft_split(find_path(envp), ':');
	child1 = fork();
	if (child1 < 0)
		return (fork_error(pipex_args));
	if (child1 == 0)
		child_one(pipex_args, envp, argv);
	child2 = fork();
	if (child2 < 0)
		return (fork_error(pipex_args));
	if (child2 == 0)
		child_two(pipex_args, envp, argv);
	close_pipes(pipex_args->end);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	parent_free(pipex_args);
}

/**
 * Main:
 * * This is the principal method and the one responsable of
 * * generating the binary
*/
int	main(int ac, char **argv, char **envp)
{
	t_pipex	*pipex_args;

	if (ac != 5)
	{
		ft_printf("Error: %s", "Bad number of arguments");
		return (-1);
	}
	pipex_args = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex_args)
		return (-1);
	pipex_args->infile = open(argv[1], O_RDONLY);
	pipex_args->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex_args->infile < 0 || pipex_args->outfile < 0)
	{
		perror(argv[1]);
		return (-1);
	}
	pipex(pipex_args, envp, argv);
	free(pipex_args);
	return (0);
}
