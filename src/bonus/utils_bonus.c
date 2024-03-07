/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:11:00 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 15:11:01 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	multi_clean_exit(t_pipex_bonus *p_b, int argc)
{
	int	i;

	i = 0;
	while (p_b->cmd[i])
	{
		free_the_tab(p_b->cmd[i]);
		i++;
	}
	free(p_b->cmd);
	i = 0;
	while (i < argc - 3)
	{
		free(p_b->cmd_path[i]);
		i++;
	}
	free(p_b->cmd_path);
	if (!p_b->status_code && p_b->fd_infile != -1)
	{
		free_the_pipe(p_b, argc);
		free(p_b->fork_pid);
	}
	if (p_b->fd_infile != -1)
		close(p_b->fd_infile);
	if (p_b->fd_outfile != -1)
		close(p_b->fd_outfile);
}

void	free_the_pipe(t_pipex_bonus *p_b, int argc)
{
	int	pipe_number;
	int	i;

	pipe_number = argc - 4;
	i = 0;
	while (i < pipe_number)
	{
		free(p_b->p_fd[i]);
		i++;
	}
	free(p_b->p_fd);
}

void	close_all_except(t_pipex_bonus *p_b, int in, int out, int argc)
{
	int	i;

	i = 0;
	while (i < (argc - 4))
	{
		if (p_b->p_fd[i][0] != in)
			close(p_b->p_fd[i][0]);
		if (p_b->p_fd[i][1] != out)
			close(p_b->p_fd[i][1]);
		i++;
	}
}

void	init_pipe_fd(t_pipex_bonus *p_b, int argc)
{
	int	pipe_number;
	int	i;

	pipe_number = argc - 4;
	i = 0;
	p_b->p_fd = malloc(sizeof(int *) * (pipe_number));
	if (!p_b->p_fd)
		exit(EXIT_FAILURE);
	while (i < pipe_number)
	{
		p_b->p_fd[i] = malloc(sizeof(int) * 2);
		if (!p_b->p_fd[i])
			exit(EXIT_FAILURE);
		if (pipe(p_b->p_fd[i]))
		{
			close_all_except(p_b, -1, -1, i + 3);
			multi_clean_exit(p_b, argc);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
