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


void	init_pipex(t_pipex *p, char **argv, char **env)
{
	p->status_code = 0;
	p->cmd1 = argv[2];
	p->cmd2 = argv[3];
	p->all_paths = paths(env);
	if (!p->all_paths)
	{
		ft_putendl_fd("PATHS not found", 2);
		exit(1);
	}
}

void	simple_pipe(int argc, char **argv, char **env)
{
	t_pipex p;
	(void)argc;

	open_files(&p, argv);
	init_pipex(&p, argv, env);
	execute_programs(&p, env);
	free_the_tab(p.all_paths);
	close(p.fd_infile);
	close(p.fd_outfile);
	exit(p.status_code);
}
