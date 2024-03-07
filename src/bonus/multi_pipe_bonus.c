/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:10:44 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 15:10:46 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	first_command(t_pipex_bonus *p_b, int argc, char **env)
{
	close_all_except(p_b, -1, p_b->p_fd[0][1], argc);
	dup2(p_b->fd_infile, STDIN_FILENO);
	dup2(p_b->p_fd[0][1], STDOUT_FILENO);
	execve(p_b->cmd_path[0], p_b->cmd[0], env);
}

void	middle_command(t_pipex_bonus *p_b, int argc, char **env, int i)
{
	close_all_except(p_b, p_b->p_fd[i - 1][0], p_b->p_fd[i][1], argc);
	dup2(p_b->p_fd[i - 1][0], STDIN_FILENO);
	dup2(p_b->p_fd[i][1], STDOUT_FILENO);
	execve(p_b->cmd_path[i], p_b->cmd[i], env);
}

void	last_command(t_pipex_bonus *p_b, int argc, char **env, int i)
{
	close_all_except(p_b, p_b->p_fd[i - 1][0], -1, argc);
	dup2(p_b->p_fd[i - 1][0], STDIN_FILENO);
	dup2(p_b->fd_outfile, STDOUT_FILENO);
	execve(p_b->cmd_path[i], p_b->cmd[i], env);
}

void	execute_command(t_pipex_bonus *p_b, int argc, char **env, int i)
{
	if (i == 0)
		first_command(p_b, argc, env);
	else if (i != argc - 4)
		middle_command(p_b, argc, env, i);
	if (i == argc - 4)
		last_command(p_b, argc, env, i);
}

void	multi_pipe(t_pipex_bonus *p_b, int argc, char **env)
{
	int	i;

	i = 0;
	init_pipe_fd(p_b, argc);
	while (i < (argc - 3))
	{
		p_b->fork_pid[i] = fork();
		if (p_b->fork_pid[i] < 0)
			exit(EXIT_FAILURE);
		if (p_b->fork_pid[i] == 0)
		{
			if (p_b->cmd_path[i])
				execute_command(p_b, argc, env, i);
			multi_clean_exit(p_b, argc);
			exit(EXIT_FAILURE);
		}
		else
			i++;
	}
	close_all_except(p_b, -1, -1, argc);
	waitpid(p_b->fork_pid[argc - 4], NULL, 0);
}
