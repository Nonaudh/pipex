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

void	init_struct(t_pipe *f, int argc)
{
	f->fork_pid = malloc(sizeof(int) * (argc - 3));
	if (!f->fork_pid)
		exit(-1);
	init_pipe_fd(f, argc);
}

void	multi_pipe(t_pipex_bonus *p_b, int argc, char **env)
{
	int	i;
	t_pipe f;

	i = 0;
	init_struct(&f, argc);
	while (i < (argc - 3))
	{
		f.fork_pid[i] = fork();
		if (f.fork_pid[i] < 0)
			exit(EXIT_FAILURE);
		if (f.fork_pid[i] == 0)
		{
			execute_command(p_b, &f, argc, env, i);
			//multi_clean_exit(p_b, argc);
			exit(EXIT_FAILURE);
		}
		else
			i++;
	}
	close_all_except(&f, -1, -1, argc);
	waitpid(f.fork_pid[argc - 4], NULL, 0);
}
