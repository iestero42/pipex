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
 * @brief Main pipeline function for executing commands.
 *
 * This function sets up the pipeline by creating two child processes and
 * executing commands using the specified input and output file descriptors.
 *
 * @param pipex_args   Structure containing pipeline arguments and file 
 * 						descriptors.
 * @param envp         Array of environment strings.
 * @param argv         Array of arguments for the main program.
 *
 * @details
 * The 'pipex' function performs the following tasks:
 * - Creates two child processes using 'fork'.
 * - In the first child process, it calls 'child_one' to execute the 
 * 		first command.
 * - In the second child process, it calls 'child_two' to execute the 
 * 		second command.
 * - Closes the pipe file descriptors using 'close_pipes'.
 * - Waits for both child processes to complete using 'waitpid'.
 * - Cleans up resources by calling 'parent_free'.
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
		perror("fork");
	if (child1 == 0)
		child_one(pipex_args, envp, argv);
	child2 = fork();
	if (child2 < 0)
		perror("fork");
	if (child2 == 0)
		child_two(pipex_args, envp, argv);
	close_pipes(pipex_args->end);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
	parent_free(pipex_args);
}

/**
 * @brief The main function responsible for generating the binary.
 *
 * This is the principal method that generates the binary for the 
 * pipeline program. It parses the command-line arguments, opens 
 * input and output files, and calls the 'pipex' function 
 * to execute the pipeline.
 *
 * @param ac    The number of command-line arguments.
 * @param argv  Array of command-line argument strings.
 * @param envp  Array of environment strings.
 *
 * @return      Returns 0 upon successful execution, or -1 in case of an error.
 *
 * @details
 * The 'main' function performs the following tasks:
 * - Checks if the number of command-line arguments is 5, as expected.
 * - Allocates memory for the 'pipex_args' structure.
 * - Opens the input and output files specified in 'argv'.
 * - Calls the 'pipex' function to execute the pipeline.
 * - Frees the allocated memory and returns 0 upon successful execution.
 * - Prints an error message and returns -1 in case of an error.
 */
int	main(int ac, char **argv, char **envp)
{
	t_pipex	*pipex_args;

	if (ac != 5)
	{
		ft_putstr_fd(strerror(EINVAL), 2);
		return (-1);
	}
	pipex_args = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex_args)
		return (-1);
	pipex_args->infile = open(argv[1], O_RDONLY);
	if (pipex_args->infile < 0)
		perror(argv[1]);
	pipex_args->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex_args->outfile < 0)
		perror(argv[4]);
	pipex(pipex_args, envp, argv);
	free(pipex_args);
	return (0);
}
