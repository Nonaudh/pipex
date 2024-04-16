/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:11:22 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 15:11:25 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	command_in(t_pipex *p, char **env, int *pipe_fd)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(p->cmd1, ' ');
	if (!cmd)
		exit(-1);
	cmd_path = find_command_path(cmd[0], p->all_paths);
	close(pipe_fd[0]);
	dup2(p->fd_infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	clean_struct(p);
	if (cmd_path && p->fd_infile != -1)
		execve(cmd_path, cmd, env);
	close(pipe_fd[1]);
	free_the_tab(cmd);
	free(cmd_path);
	exit(127);
}

void	command_out(t_pipex *p, char **env, int *pipe_fd)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(p->cmd2, ' ');
	if (!cmd)
		exit(-1);
	cmd_path = find_command_path(cmd[0], p->all_paths);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(p->fd_outfile, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	clean_struct(p);
	if (cmd_path && p->fd_outfile != -1)
		execve(cmd_path, cmd, env);
	close(pipe_fd[0]);
	free_the_tab(cmd);
	free(cmd_path);
	exit(127);
}

void	wait_for_all_process(void)
{
	while (waitpid(-1, NULL, 0) > 0)
		;
}

void	pipex(t_pipex *p, char **env)
{
	int		pipe_fd[2];
	int		fork_pid[2];

	if (pipe(pipe_fd))
		exit(EXIT_FAILURE);
	fork_pid[0] = fork();
	if (fork_pid[0] < 0)
		exit(EXIT_FAILURE);
	if (fork_pid[0] == 0)
		command_in(p, env, pipe_fd);
	else
	{
		fork_pid[1] = fork();
		if (fork_pid[1] < 0)
			exit(EXIT_FAILURE);
		if (fork_pid[1] == 0)
			command_out(p, env, pipe_fd);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait_for_all_process();
}
