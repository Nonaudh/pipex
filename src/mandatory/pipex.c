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

void	command_in(t_pipex *p, char **env, int *pfd)
{
	char **cmd;
	char *cmd_path;

	cmd = ft_split(p->cmd1, ' ');
	if (!cmd)
		exit(-1);
	cmd_path = find_command_path(cmd[0], p->all_paths);
	close(pfd[0]);
	dup2(p->fd_infile, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	if (cmd_path)
		execve(cmd_path, cmd, env);
	else
		exit(127);
}

void	command_out(t_pipex *p, char **env, int *pfd)
{
	char **cmd;
	char *cmd_path;

	cmd = ft_split(p->cmd2, ' ');
	if (!cmd)
		exit(-1);
	cmd_path = find_command_path(cmd[0], p->all_paths);
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	dup2(p->fd_outfile, STDOUT_FILENO);
	if (cmd_path)
		execve(cmd_path, cmd, env);
	else
		exit(127);
}

void	execute_programs(t_pipex *p, char **env)
{
	int		pfd[2];
	int		pid[2];

	if (pipe(pfd))
		exit(EXIT_FAILURE);
	pid[0] = fork();
	if (pid[0] < 0)
		exit(EXIT_FAILURE);
	if (pid[0] == 0)
		command_in(p, env, pfd);
	else
	{
		pid[1] = fork();
		if (pid[1] < 0)
			exit(EXIT_FAILURE);
		if (pid[1] == 0)
			command_out(p, env, pfd);
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid[1], NULL, 0);
}

int	main(int argc, char **argv, char **env)
{

	if (argc == 5)
		simple_pipe(argc, argv, env);
	/*if (!pipex.status_code && pipex.fd_infile != -1)
		execute_programs(&pipex, env);
	clean_exit(&pipex);*/
	return (0);
}
