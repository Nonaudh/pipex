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

void	free_the_pipe(t_pipe *f, int argc)
{
	int	pipe_number;
	int	i;

	pipe_number = argc - 4;
	i = 0;
	while (i < pipe_number)
	{
		free(f->pipe_fd[i]);
		i++;
	}
	free(f->pipe_fd);
}

void	close_all_except(t_pipe *f, int in, int out, int argc)
{
	int	i;

	i = 0;
	while (i < (argc - 4))
	{
		if (f->pipe_fd[i][0] != in)
			close(f->pipe_fd[i][0]);
		if (f->pipe_fd[i][1] != out)
			close(f->pipe_fd[i][1]);
		i++;
	}
}

void	init_pipe_fd(t_pipe *f, int argc)
{
	int	pipe_number;
	int	i;

	pipe_number = argc - 4;
	i = 0;
	f->pipe_fd = malloc(sizeof(int *) * (pipe_number));
	if (!f->pipe_fd)
		exit(EXIT_FAILURE);
	while (i < pipe_number)
	{
		f->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!f->pipe_fd[i])
			exit(EXIT_FAILURE);
		if (pipe(f->pipe_fd[i]))
		{
			//close_all_except(p_b, -1, -1, i + 3);
			//multi_clean_exit(p_b, argc);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
void	multi_clean_exit(t_pipex_bonus *p_b, int size)
{
	close(p_b->fd_infile);
	close(p_b->fd_outfile);
	if (p_b->here_doc)
		unlink("here_doc");
	free(p_b->cmd);
	free_the_tab(p_b->all_paths);
}
