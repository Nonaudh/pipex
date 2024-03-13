/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:11:13 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 15:11:16 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"


void	open_files(t_pipex *p, char **argv)
{
	if (access(argv[1], R_OK))
	{
		perror(argv[1]);
		p->fd_infile = -1;
	}
	else
	{
		p->fd_infile = open(argv[1], O_RDONLY);
		if (!p->fd_infile)
			exit(-1);
	}
	p->fd_outfile = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (p->fd_outfile == -1)
	{
		perror(argv[4]);
		exit(-1);
	}
}

void	simple_pipe(int argc, char **argv, char **env)
{
	t_pipex p;
	(void)argc;

	p.status_code = 0;
	p.cmd1 = argv[2];
	p.cmd2 = argv[3];
	p.all_paths = paths(env);
	open_files(&p, argv);
	execute_programs(&p, env);
	free_the_tab(p.all_paths);
	close(p.fd_infile);
	close(p.fd_outfile);
	exit(p.status_code);
}
