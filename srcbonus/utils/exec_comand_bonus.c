/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:35:54 by marvin            #+#    #+#             */
/*   Updated: 2023/04/21 09:35:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * @brief Trims leading and trailing characters from a string.
 *
 * This function removes any leading or trailing characters specified in 'trim'
 * from the beginning or end of 's'. It returns a pointer to the trimmed string.
 *
 * @param s   The string to trim.
 * @param trim   The set of characters to trim from 's'.
 *
 * @return    A pointer to the trimmed string.
 */
void	trim_command(char **cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (cmd[i] != NULL)
	{
		j = -1;
		while (++j < 2)
		{
			if (cmd[i][0] == '\'')
			{
				tmp = ft_strtrim(cmd[i], "'");
				free(cmd[i]);
				cmd[i] = tmp;
			}
			else if (cmd[i][0] == '"')
			{
				tmp = ft_strtrim(cmd[i], "\"");
				free(cmd[i]);
				cmd[i] = tmp;
			}
		}
		i++;
	}
}

/**
 * @brief Find the full path to an executable command.
 *
 * This function searches for the full path to an executable command 'cmd' by
 * iterating through the 'paths' array. It constructs the full path by 
 * appending 'cmd' to each path in 'paths', and it checks if the command 
 * is accessible using the 'access' system call.
 *
 * @param paths   Array of search paths for executable commands.
 * @param cmd     The name of the command to find.
 *
 * @return        A pointer to the full path of the command, or NULL 
 * 					if not found.
 *
 * @details
 * The 'get_cmd' function is responsible for locating the full path of an 
 * executable command by searching through the 'paths' array, which typically 
 * contains directories where executable files are located.
 *
 * It iterates through 'paths', constructs the full path by appending '/' and 
 * 'cmd' to each path, and checks if the constructed path is accessible using 
 * 'access' with mode 0 (F_OK). If a valid path to the command is found, it 
 * is returned. Otherwise, it returns NULL to indicate that the command was 
 * not found.
 */
static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

/**
 * @brief Execute a command using 'execve'.
 *
 * This function executes a command specified in 'argv' using the 'execve'
 * system call. It also splits the command arguments, searches for the full
 * command path using 'get_cmd', and handles error conditions.
 *
 * @param pipex_args  A pointer to the 't_pipex' structure containing pipeline
 *                    arguments.
 * @param envp        Array of environment strings.
 * @param argv        The command string to execute.
 *
 * @details
 * The 'exec_comand' function is responsible for executing a command specified
 * in 'argv' using the 'execve' system call. It follows these steps: 1. Splits
 * the command string 'argv' into separate arguments using 'ft_split'. 2.
 * Searches for the full path to the command using 'get_cmd' and 'cmd_paths'.
 * 3. If a valid command path is found, it attempts to execute the command using
 * 'execve'. 4. If 'execve' fails, it cleans up resources, displays an error
 * message, and exits. 5. Memory allocated for 'cmd' and 'cmd_arg' is freed, and
 * child resources are released.
 */
void	exec_comand(t_pipex *pipex_args, char **envp, char *argv)
{
	char	*cmd;

	pipex_args->cmd_arg = split_command(argv);
	trim_command(pipex_args->cmd_arg);
	cmd = get_cmd(pipex_args->cmd_paths, pipex_args->cmd_arg[0]);
	if (execve(cmd, pipex_args->cmd_arg, envp) < 0)
	{
		child_free(pipex_args);
		if (cmd)
			free(cmd);
		perror("Error");
		exit(42);
	}
	free(cmd);
	child_free(pipex_args);
}
