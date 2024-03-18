/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:10:52 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 15:10:54 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	init_pipex_bonus(t_pipex_bonus *p_b, int argc, char **argv, char **env)
{
	if (!p_b->here_doc)
	{
		p_b->cmd_count = argc - 3;
		init_cmds(p_b, argc, argv);
	}
	else
	{
		p_b->cmd_count = 2;
		argc = 5;
		init_cmds(p_b, argc, argv + 1);
	}
	p_b->all_paths = paths(env);
	if (!p_b->all_paths)
			exit (-1);
	p_b->status_code = 0;
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
	p_b->cmd[i] = NULL;
}

void	init_multi_pipe(t_pipex_bonus *p_b, int argc, char **argv, char **env)
{
	open_bonus_files(p_b, argc, argv);
	init_pipex_bonus(p_b, argc, argv, env);
	multi_pipe(p_b, argc, env);
	multi_clean_exit(p_b, p_b->cmd_count);
	exit(p_b->status_code);
}

void	pipe_bonus(int argc, char **argv, char **env)
{
	t_pipex_bonus	p_b;

	if (!ft_strncmp(argv[1], "here_doc", 8) && argc == 6)
	{
		p_b.here_doc = true;
		write_here_doc(argv);
	}
	else
		p_b.here_doc = false;
	init_multi_pipe(&p_b, argc, argv, env);
}
