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
 * @brief Find and return the 'PATH' environment variable value.
 *
 * This function searches for the 'PATH' environment variable in the provided
 * array of environment strings and returns its corresponding value.
 *
 * @param envp   Array of environment strings.
 *
 * @return       A pointer to the 'PATH' environment variable value.
 *
 * @details
 * The 'find_path' function iterates through the 'envp' array to locate the
 * 'PATH' environment variable. It returns a pointer to the value of the 'PATH'
 * variable, excluding the variable name itself.
 *
 * @note
 * This function is commonly used to retrieve the search paths for executable
 * files when working with shell-like programs.
 */
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

/**
 * @brief Open pipes for inter-process communication.
 *
 * This function creates pipes for inter-process communication and associates
 * them with the pipeline specified in the 'pipex_args' structure.
 *
 * @param pipex_args   A pointer to the 't_pipex' structure containing pipeline
 *                     arguments and file descriptors.
 *
 * @return             0 on success, -1 on failure.
 *
 * @details
 * The 'open_pipes' function is responsible for creating pipes that connect
 * multiple processes within a pipeline. It iterates through the 'end' array of
 * file descriptors in the 'pipex_args' structure and uses the 'pipe' system
 * call to create pipes. If the 'pipe' operation fails, the function returns -1
 * to indicate an error condition. On success, it returns 0.
 *
 * @note
 * This function is typically called before forking child processes for
 * executing commands within the pipeline.
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
 * @brief Fork child processes to execute commands within the pipeline.
 *
 * This function forks child processes to execute commands within the pipeline
 * specified in the 'pipex_args' structure. Each child process is responsible
 * for running a part of the pipeline.
 *
 * @param pipex_args   A pointer to the 't_pipex' structure containing pipeline
 *                     arguments and file descriptors.
 * @param envp         Array of environment strings.
 * @param argv         Array of arguments for the main program.
 *
 * @return             0 on success, -1 on failure.
 *
 * @details
 * The 'fork_process' function is called to create child processes for executing
 * commands within the pipeline. It iterates through the 'cmd_nb' number of
 * commands, creating a child process for each command.
 *
 * In each child process, it sets up the input and output using the 'childs'
 * function and executes the corresponding command using 'exec_comand'. The
 * 'close_pipes' function is called to close unused pipe ends. If a 'fork' or
 * 'exec' operation fails, the function returns -1 to indicate an error
 * condition. On successful execution of child processes, it returns 0.
 *
 * @note
 * This function is a crucial part of the pipeline execution process and should
 * be called after creating pipes with 'open_pipes'.
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
			perror("fork");
		else if (child == 0)
		{
			if (i == 0 && pipex_args->infile > -1)
				childs(pipex_args->infile, pipex_args->end[i * 2 + 1]);
			else if (i == pipex_args->pipes)
				childs(pipex_args->end[2 * (i - 1)], pipex_args->outfile);
			else if (pipex_args->outfile > -1)
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
 * @brief Execute the pipex program with bonus features, 
 * including multiple pipes.
 *
 * This function executes the pipex program with bonus features, which include
 * handling multiple pipes. It sets up the pipeline, forks child processes,
 * and manages their execution.
 *
 * @param pipex_args   A pointer to the 't_pipex' structure containing pipeline
 *                     arguments and file descriptors.
 * @param envp         Array of environment strings.
 * @param argv         Array of arguments for the main program.
 *
 * @details
 * The 'pipex_bonus' function is responsible for setting up and executing the
 * pipex program with additional features, such as multiple pipes. It follows
 * these steps:
 *
 * 1. Calls 'open_pipes' to create pipes for inter-process communication.
 * 2. Parses and stores the 'PATH' environment variable in 'cmd_paths'.
 * 3. Calls 'fork_process' to fork child processes for command execution.
 * 4. Closes pipes and waits for child processes to complete.
 * 5. Frees allocated resources using 'parent_free'.
 *
 * This function provides enhanced functionality for pipex, enabling more
 * complex pipelines and command execution.
 *
 * @note
 * This function should be used for executing pipex with bonus features and
 * managing child processes within the pipeline.
 */
void	pipex_bonus(t_pipex *pipex_args, char **envp, char **argv)
{
	int	i;

	if (open_pipes(pipex_args) < 0)
		return (pipe_error(pipex_args));
	pipex_args->cmd_paths = ft_split(find_path(envp), ':');
	fork_process(pipex_args, envp, argv);
	close_pipes(pipex_args);
	i = -1;
	while (++i < pipex_args->cmd_nb)
		wait(NULL);
	parent_free(pipex_args);
}

/**
 * @brief Main function for executing the pipex program.
 *
 * This is the main entry point of the pipex program. It parses command-line
 * arguments, sets up the pipeline, and manages the execution of the pipeline
 * processes.
 *
 * @param ac     The number of command-line arguments.
 * @param argv   Array of command-line argument strings.
 * @param envp   Array of environment strings.
 *
 * @return       0 on successful execution, or an error code on failure.
 *
 * @details
 * The 'main' function is responsible for the overall execution of the pipex
 * program. It follows these steps:
 *
 * 1. Check the number of command-line arguments and display an error message if
 *    there are fewer than 5 arguments.
 * 2. Allocate memory for the 't_pipex' structure ('pipex_args') and initialize
 *    it.
 * 3. Handle the 'here_doc' feature if present.
 * 4. Check the validity of input and output file descriptors, displaying an
 *    error message if they are invalid.
 * 5. Determine the number of commands and pipes in the pipeline.
 * 6. Allocate memory for pipe descriptors ('end') based on the number of pipes.
 * 7. Call 'pipex_bonus' to set up and execute the pipeline with bonus features.
 * 8. Free allocated memory and return 0 on successful execution.
 *
 * This function serves as the main control flow for pipex, managing the
 * initialization, execution, and cleanup of resources.
 */
int	main(int ac, char **argv, char **envp)
{
	t_pipex	*pipex_args;

	if (ac < 5)
		return (error_msg());
	pipex_args = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex_args)
		return (-1);
	here_doc(pipex_args, argv, ac);
	if (pipex_args->infile < 0 || pipex_args->outfile < 0)
		perror("Error");
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
