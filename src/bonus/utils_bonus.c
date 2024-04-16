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

void	free_the_pipe(t_pipe *f, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(f->pipe_fd[i]);
		i++;
	}
	free(f->pipe_fd);
}

void	close_all_pipe(t_pipe *f, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(f->pipe_fd[i][0]);
		close(f->pipe_fd[i][1]);
		i++;
	}
}

void	init_pipe_fd(t_pipe *f)
{
	int	i;

	i = 0;
	f->pipe_fd = malloc(sizeof(int *) * (*f->cmd_count - 1));
	if (!f->pipe_fd)
		exit(EXIT_FAILURE);
	while (i < *f->cmd_count - 1)
	{
		f->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!f->pipe_fd[i])
			exit(EXIT_FAILURE);
		if (pipe(f->pipe_fd[i]))
		{
			close_all_pipe(f, i + 1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	multi_clean_exit(t_pipex_bonus *p_b)
{
	free(p_b->cmd);
	if (p_b->all_paths)
		free_the_tab(p_b->all_paths);
}
