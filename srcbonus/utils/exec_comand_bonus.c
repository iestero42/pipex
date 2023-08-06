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

void	exec_comand(t_pipex *pipex_args, char **envp, char *argv)
{
	char	*cmd;

	pipex_args->cmd_arg = ft_split(argv, ' ');
	cmd = get_cmd(pipex_args->cmd_paths, pipex_args->cmd_arg[0]);
	if (!cmd)
	{
		child_free(pipex_args);
		perror("Error in command");
		exit(1);
	}
	if (execve(cmd, pipex_args->cmd_arg, envp) < 0)
	{
		child_free(pipex_args);
		perror("Error in execution");
		exit(1);
	}
}
