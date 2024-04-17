/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:24:52 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/19 14:24:54 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	init_struct(t_pipex_bonus *p_b, t_pipe *f)
{
	f->fork_pid = malloc(sizeof(int) * (p_b->cmd_count));
	if (!f->fork_pid)
		exit(1);
	f->cmd_count = &p_b->cmd_count;
	init_pipe_fd(f);
}

void	free_struct(t_pipe *f)
{
	free(f->fork_pid);
	free_the_pipe(f, *f->cmd_count - 1);
}

void	close_files_and_pipes(t_pipex_bonus *p_b, t_pipe *f)
{
	if (p_b->fd_infile != -1)
		close(p_b->fd_infile);
	if (p_b->fd_outfile != -1)
		close(p_b->fd_outfile);
	close_all_pipe(f, p_b->cmd_count - 1);
}
