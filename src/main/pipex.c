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

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	pipex(t_pipex *pipex_args, char **envp, char **argv)
{
	int		status;
	pid_t	child1;
	pid_t	child2;

	if (pipe(pipex_args->end))
		return (perror("Error in pipe process"));
	pipex_args->mypaths = find_path(envp);
	pipex_args->cmd_paths = ft_split(pipex_args->mypaths, ':');
	child1 = fork();
	if (child1 < 0)
		return (perror("Error in fork process"));
	if (child1 == 0)
		child_one(pipex_args, envp, argv);
	child2 = fork();
	if (child2 < 0)
		return (perror("Error in fork process"));
	if (child2 == 0)
		child_two(pipex_args, envp, argv);
	close_pipes(pipex_args->end);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	parent_free(pipex_args);
}

int	main(int ac, char **argv, char **envp)
{
	t_pipex	*pipex_args;

	pipex_args = (t_pipex *) malloc(sizeof(t_pipex));
	if (!pipex_args)
		return (-1);
	pipex_args->infile = open(argv[1], O_RDONLY);
	pipex_args->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex_args->infile < 0 || pipex_args->outfile < 0)
	{
		strerror(errno);
		return (-1);
	}
	pipex(pipex_args, envp, argv);
	return (0);
}
