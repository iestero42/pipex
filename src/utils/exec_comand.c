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

#include "pipex.h"

/**
 * Get_cmd
 * * Searches for the specified command in the provided paths and 
 * * returns the full command path.
 *
 * @param paths   Array of path strings to search for the command.
 * @param cmd     The command to find.
 * @return        The full command path if found, or NULL if not found.
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
 * Exec_comand
 * * Executes a command with arguments in the child process.
 *
 * @param pipex_args   Structure containing pipeline 
 * 						arguments and file descriptors.
 * @param envp         Array of environment strings.
 * @param argv         The command to execute along with its arguments.
 */
void	exec_comand(t_pipex *pipex_args, char **envp, char *argv)
{
	char	*cmd;

	pipex_args->cmd_arg = ft_split(argv, ' ');
	cmd = get_cmd(pipex_args->cmd_paths, pipex_args->cmd_arg[0]);
	if (execve(cmd, pipex_args->cmd_arg, envp) < 0)
	{
		child_free(pipex_args);
		if (cmd)
			free(cmd);
		perror("Error");
		exit(1);
	}
	free(cmd);
	child_free(pipex_args);
}
