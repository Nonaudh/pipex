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
		init_cmds(p_b, argv);
	}
	else
	{
		p_b->cmd_count = 2;
		init_cmds(p_b, argv + 1);
	}
	p_b->all_paths = find_paths(env);
	if (!p_b->all_paths)
	{
		/*free(p_b->cmd);
		close(p_b->fd_infile);
		close(p_b->fd_outfile);
		exit (1);*/
	}
	p_b->status_code = 0;
}

void	init_cmds(t_pipex_bonus *p_b, char **argv)
{
	int	i;

	i = 0;
	p_b->cmd = malloc(sizeof(char *) * (p_b->cmd_count + 1));
	if (!p_b->cmd)
		exit(1);
	while (i < p_b->cmd_count)
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
}

void	check_if_here_doc(t_pipex_bonus *p_b, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "here_doc", 8) && argc == 6)
	{
		p_b->here_doc = true;
		write_here_doc(argv);
	}
	else
		p_b->here_doc = false;
}

void	pipe_bonus(int argc, char **argv, char **env)
{
	t_pipex_bonus	p_b;

	check_if_here_doc(&p_b, argc, argv);
	init_multi_pipe(&p_b, argc, argv, env);
	multi_pipe(&p_b, env);
	multi_clean_exit(&p_b);
	exit(p_b.status_code);
}
