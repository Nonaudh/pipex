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
	close(pfd[0]);
	dup2(p->fd_infile, STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	execve(p->cmd1_path, p->cmd1, env);
}

void	command_out(t_pipex *p, char **env, int *pfd)
{
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	dup2(p->fd_outfile, STDOUT_FILENO);
	execve(p->cmd2_path, p->cmd2, env);
}

void	pipex(t_pipex *p, char **env)
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
	t_pipex	pipex;

	init_pipex(&pipex, argc, argv, env);
	if (!pipex.status_code && pipex.fd_infile != -1)
		pipex(&pipex, env);
	clean_exit(&pipex);
	return (pipex.status_code);
}
