/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_multi_pipe_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:10:11 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 15:10:34 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	open_infile_bonus(t_pipex_bonus *p_b, char *infile)
{
	if (access(infile, R_OK))
	{
		perror(infile);
		exit(1);
	}
	else
	{
		p_b->fd_infile = open(infile, O_RDONLY);
		if (!p_b->fd_infile)
			exit(-1);
	}
}
void	open_outfile_bonus(t_pipex_bonus *p_b, char *outfile)
{
	p_b->fd_outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (p_b->fd_outfile == -1)
	{
		perror(outfile);
		close(p_b->fd_infile);
		exit(-1);
	}
}
void	open_bonus_files(t_pipex_bonus *p_b, int argc, char **argv)
{
	open_infile_bonus(p_b, argv[1]);
	open_outfile_bonus(p_b, argv[argc - 1]);
}

void	init_pipex_bonus(t_pipex_bonus *p_b, int argc, char **argv, char **env)
{
	p_b->status_code = 0;
	p_b->all_paths = paths(env);
	if (!p_b->all_paths)
		exit (-1);
	init_cmds(p_b, argc, argv);
}

void	init_cmds(t_pipex_bonus *p_b, int argc, char **argv)
{
	int	i;

	i = 0;
	p_b->cmd = malloc(sizeof(char *) * (argc - 2));
	while (i < argc - 3)
	{
		p_b->cmd[i] = argv[i + 2];
		i++;
	}
	p_b->cmd = NULL;
}

void	init_multi_pipe(t_pipex_bonus *p_b, int argc, char **argv, char **env)
{
	open_bonus_files(p_b, argc, argv);
	init_pipex_bonus(p_b, argc, argv, env);
	multi_pipe(p_b, argc, env);
	exit(p_b->status_code);
}
