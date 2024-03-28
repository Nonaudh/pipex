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

void	first_command(t_pipex_bonus *p_b, t_pipe *f, char **env)
{
	char	**cmd_tmp;
	char	*cmd_path;

	cmd_tmp = ft_split(p_b->cmd[0], ' ');
	if (!cmd_tmp)
		exit(-1);
	cmd_path = find_command_path(cmd_tmp[0], p_b->all_paths);
	dup2(p_b->fd_infile, STDIN_FILENO);
	dup2(f->pipe_fd[0][1], STDOUT_FILENO);
	close_files_and_pipes(p_b, f);
	if (cmd_path)
		execve(cmd_path, cmd_tmp, env);
	multi_clean_exit(p_b);
	free_struct(f);
	free_the_tab(cmd_tmp);
	free(cmd_path);
	exit(127);
}

void	middle_command(t_pipex_bonus *p_b, t_pipe *f, char **env, int i)
{
	char	**cmd_tmp;
	char	*cmd_path;

	cmd_tmp = ft_split(p_b->cmd[i], ' ');
	if (!cmd_tmp)
		exit(-1);
	cmd_path = find_command_path(cmd_tmp[0], p_b->all_paths);
	dup2(f->pipe_fd[i - 1][0], STDIN_FILENO);
	dup2(f->pipe_fd[i][1], STDOUT_FILENO);
	close_files_and_pipes(p_b, f);
	if (cmd_path)
		execve(cmd_path, cmd_tmp, env);
	multi_clean_exit(p_b);
	free_struct(f);
	free_the_tab(cmd_tmp);
	free(cmd_path);
	exit(127);
}

void	last_command(t_pipex_bonus *p_b, t_pipe *f, char **env, int i)
{
	char	**cmd_tmp;
	char	*cmd_path;

	cmd_tmp = ft_split(p_b->cmd[i], ' ');
	if (!cmd_tmp)
		exit(-1);
	cmd_path = find_command_path(cmd_tmp[0], p_b->all_paths);
	dup2(f->pipe_fd[i - 1][0], STDIN_FILENO);
	dup2(p_b->fd_outfile, STDOUT_FILENO);
	close_files_and_pipes(p_b, f);
	if (cmd_path)
		execve(cmd_path, cmd_tmp, env);
	multi_clean_exit(p_b);
	free_struct(f);
	free_the_tab(cmd_tmp);
	free(cmd_path);
	exit(127);
}

void	execute_command(t_pipex_bonus *p_b, t_pipe *f, char **env, int i)
{
	if (i == 0)
		first_command(p_b, f, env);
	else if (i < p_b->cmd_count - 1)
		middle_command(p_b, f, env, i);
	if (i == p_b->cmd_count - 1)
		last_command(p_b, f, env, i);
}

void	multi_pipe(t_pipex_bonus *p_b, char **env)
{
	int		i;
	t_pipe	f;

	i = 0;
	init_struct(p_b, &f);
	while (i < p_b->cmd_count)
	{
		f.fork_pid[i] = fork();
		if (f.fork_pid[i] < 0)
			exit(EXIT_FAILURE);
		if (f.fork_pid[i] == 0)
		{
			execute_command(p_b, &f, env, i);
			exit(EXIT_FAILURE);
		}
		else
			i++;
	}
	close_files_and_pipes(p_b, &f);

	while (waitpid(-1, NULL, 0) > 0)
		;
	
	//waitpid(f.fork_pid[p_b->cmd_count - 1], NULL, 0);
	free_struct(&f);
}
