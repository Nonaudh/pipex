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

void	init_cmds(t_pipex_bonus *p_b, int argc, char **argv)
{
	int	i;

	i = 0;
	p_b->cmd = malloc(sizeof(char **) * (argc - 2));
	if (!p_b->cmd)
		exit(-1);
	p_b->cmd_path = malloc(sizeof(char *) * (argc - 2));
	if (!p_b->cmd_path)
		exit(-1);
	while (i < argc - 3)
	{
		p_b->cmd[i] = ft_split(argv[i + 2], ' ');
		if (!p_b->cmd[i])
			exit(-1);
		i++;
	}
	p_b->cmd[i] = NULL;
}

void	check_in(t_pipex_bonus *p_b, char **argv, char **all_paths)
{
	if (access(argv[1], R_OK))
	{
		perror(argv[1]);
		p_b->fd_infile = -1;
		p_b->cmd_path[0] = NULL;
	}
	else
	{
		p_b->fd_infile = open(argv[1], O_RDONLY);
		if (p_b->fd_infile == -1)
			perror(argv[1]);
		p_b->cmd_path[0] = find_command_path(p_b->cmd[0][0], all_paths);
		if (!p_b->cmd_path[0])
			p_b->status_code = 127;
	}
}

void	check_out(t_pipex_bonus *p_b, int argc, char **argv, char **all_paths)
{
	int	i;

	i = 1;
	while (p_b->cmd[i])
	{
		p_b->cmd_path[i] = find_command_path(p_b->cmd[i][0], all_paths);
		if (!p_b->cmd_path[i])
			p_b->status_code = 127;
		i++;
	}
	p_b->cmd_path[i] = NULL;
	p_b->fd_outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (p_b->fd_outfile == -1)
		perror(argv[argc - 1]);
}

void	init_multi_pipe(int argc, char **argv, char **env)
{
	t_pipex_bonus	p_b;
	char			**all_paths;

	p_b.status_code = 0;
	all_paths = paths(env);
	if (!all_paths)
		exit (-1);
	init_cmds(&p_b, argc, argv);
	check_in(&p_b, argv, all_paths);
	check_out(&p_b, argc, argv, all_paths);
	free_the_tab(all_paths);
	if (!p_b.status_code && p_b.fd_infile != -1)
		multi_pipe(&p_b, argc, env);
	multi_clean_exit(&p_b, argc);
	exit(p_b.status_code);
}
