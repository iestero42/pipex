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

#include "pipex_bonus.h"

/**
 * Find_path:
 * * Find and return the 'PATH' environment variable value 
 * * from the given environment strings.
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
 * Open_pipes:
 * * Open pipes for inter-process communication.
 *
 * @param pipex_args   Structure containing pipeline 
 * 						arguments and file descriptors.
 * @return             0 on success, -1 on failure.
 */
int	open_pipes(t_pipex *pipex_args)
{
	int	i;

	i = 0;
	while (i < pipex_args->pipes)
	{
		if (pipe(pipex_args->end + 2 * i) < 0)
			return (-1);
		i++;
	}
	return (0);
}

/**
 * Fork_process:
 * * Fork child processes to execute commands.
 *
 * @param pipex_args   Structure containing pipeline 
 * 						arguments and file descriptors.
 * @param envp         Array of environment strings.
 * @param argv         Array of arguments for the main program.
 * @return             0 on success, -1 on failure.
 */
int	fork_process(t_pipex *pipex_args, char **envp, char **argv)
{
	pid_t	child;
	int		i;

	i = 0;
	while (i < pipex_args->cmd_nb)
	{
		child = fork();
		if (child < 0)
			return (fork_error(pipex_args));
		if (child == 0)
		{
			if (i == 0)
				childs(pipex_args->infile, pipex_args->end[i * 2 + 1]);
			else if (i == pipex_args->pipes)
				childs(pipex_args->end[2 * (i - 1)], pipex_args->outfile);
			else
				childs(pipex_args->end[2 * (i - 1)],
					pipex_args->end[i * 2 + 1]);
			close_pipes(pipex_args);
			exec_comand(pipex_args, envp, argv[i + 2 + pipex_args->here_doc]);
		}
		i++;
	}
	return (0);
}

/**
 * Pipex_bonus:
 * * Executes the pipex program with bonus features, 
 * * including multiple pipes.
 *
 * @param pipex_args   Structure containing pipeline 
 * 						arguments and file descriptors.
 * @param envp         Array of environment strings.
 * @param argv         Array of arguments for the main program.
 */
void	pipex_bonus(t_pipex *pipex_args, char **envp, char **argv)
{
	int	i;

	if (open_pipes(pipex_args) < 0)
		return (pipe_error(pipex_args));
	pipex_args->cmd_paths = ft_split(find_path(envp), ':');
	if (fork_process(pipex_args, envp, argv) < 0)
		return ;
	close_pipes(pipex_args);
	i = -1;
	while (++i < pipex_args->cmd_nb)
		wait(NULL);
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

	if (ac < 5)
		return (error_msg("Error: Incorrect number of arguments"));
	pipex_args = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex_args)
		return (-1);
	here_doc(pipex_args, argv, ac);
	if (pipex_args->infile < 0 || pipex_args->outfile < 0)
	{
		perror("Error");
		return (free_pipex(pipex_args));
	}
	pipex_args->cmd_nb = ac - 3 - pipex_args->here_doc;
	pipex_args->pipes = ac - 4 - pipex_args->here_doc;
	if (pipex_args->cmd_nb == 1)
		return (free_pipex(pipex_args));
	pipex_args->end = (int *) malloc(sizeof(int) * 2
			* (ac - 4 - pipex_args->here_doc));
	if (!pipex_args->end)
		return (free_pipex(pipex_args));
	pipex_bonus(pipex_args, envp, argv);
	free(pipex_args);
	return (0);
}
