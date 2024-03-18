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

void	first_command(t_pipex_bonus *p_b, t_pipe *f, int argc, char **env)
{
	char **cmd_tmp;
	char *cmd_path;

	cmd_tmp = ft_split(p_b->cmd[0], ' ');
	if (!cmd_tmp)
		exit(-1);
	cmd_path = find_command_path(cmd_tmp[0], p_b->all_paths);
	close_all_except(f, -1, f->pipe_fd[0][1], argc);
	dup2(p_b->fd_infile, STDIN_FILENO);
	dup2(f->pipe_fd[0][1], STDOUT_FILENO);
	if (cmd_path)
		execve(cmd_path, cmd_tmp, env);
	close_all_except(f, -1, -1, argc);
	multi_clean_exit(p_b, argc);
	free_struct(f, argc);
	free_the_tab(cmd_tmp);
	free(cmd_path);
	exit(127);
}

void	middle_command(t_pipex_bonus *p_b, t_pipe *f, int argc, char **env, int i)
{
	char **cmd_tmp;
	char *cmd_path;

	cmd_tmp = ft_split(p_b->cmd[i], ' ');
	if (!cmd_tmp)
		exit(-1);
	cmd_path = find_command_path(cmd_tmp[0], p_b->all_paths);
	close_all_except(f, f->pipe_fd[i - 1][0], f->pipe_fd[i][1], argc);
	dup2(f->pipe_fd[i - 1][0], STDIN_FILENO);
	dup2(f->pipe_fd[i][1], STDOUT_FILENO);
	if (cmd_path)
		execve(cmd_path, cmd_tmp, env);
	close_all_except(f, -1, -1, argc);
	multi_clean_exit(p_b, argc);
	free_struct(f, argc);
	free_the_tab(cmd_tmp);
	free(cmd_path);
	exit(127);
}

void	last_command(t_pipex_bonus *p_b, t_pipe *f, int argc, char **env, int i)
{
	char **cmd_tmp;
	char *cmd_path;

	cmd_tmp = ft_split(p_b->cmd[i], ' ');
	if (!cmd_tmp)
		exit(-1);
	cmd_path = find_command_path(cmd_tmp[0], p_b->all_paths);
	close_all_except(f, f->pipe_fd[i - 1][0], -1, argc);
	dup2(f->pipe_fd[i - 1][0], STDIN_FILENO);
	dup2(p_b->fd_outfile, STDOUT_FILENO);
	if (cmd_path)
		execve(cmd_path, cmd_tmp, env);
	close_all_except(f, -1, -1, argc);
	multi_clean_exit(p_b, argc);
	free_struct(f, argc);
	free_the_tab(cmd_tmp);
	free(cmd_path);
	exit(127);
}

void	execute_command(t_pipex_bonus *p_b, t_pipe *f, int argc, char **env, int i)
{
	if (i == 0)
		first_command(p_b, f, argc, env);
	else if (i != argc - 4)
		middle_command(p_b, f, argc, env, i);
	if (i == argc - 4)
		last_command(p_b, f, argc, env, i);
}

void	multi_pipe(t_pipex_bonus *p_b, int argc, char **env)
{
	int	i;
	t_pipe f;
	int		status;

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
			exit(EXIT_FAILURE);
		}
		else
			i++;
	}
	waitpid(f.fork_pid[argc - 4], &status, WNOHANG);
	if(WIFEXITED(status))
		ft_putendl_fd("ok", 2);
		/*p_b->status_code = 0;
	else
		p_b->status_code = WEXITSTATUS(status);*/
	close_all_except(&f, -1, -1, argc);
	free_struct(&f, argc);
}
