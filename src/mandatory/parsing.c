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

void	parsing_in(t_pipex *p, char *infile, char **all_paths)
{
	if (access(infile, R_OK))
	{
		perror(infile);
		p->cmd1_path = NULL;
	}
	else
	{
		p->fd_infile = open(infile, O_RDONLY);
		if (p->fd_infile == -1)
			perror(infile);
		p->cmd1_path = find_command_path(p->cmd1[0], all_paths);
		if (!p->cmd1_path)
			p->status_code = 127;
	}
}

void	parsing_out(t_pipex *p, char *outfile, char **all_paths)
{
	p->cmd2_path = find_command_path(p->cmd2[0], all_paths);
	if (!p->cmd2_path)
		p->status_code = 127;
	if (p->here_doc)
	{
		p->fd_outfile = open(outfile, O_RDWR | O_APPEND | O_CREAT, 0666);
		if (p->fd_outfile == -1)
		{
			perror(outfile);
			exit(-1);
		}	
	}
	else
	{
		p->fd_outfile = open(outfile, O_RDWR | O_TRUNC | O_CREAT, 0666);
		if (p->fd_outfile == -1)
		{
			perror(outfile);
			exit(-1);
		}
	}
}

void	parsing(t_pipex *p, char **env, char *infile, char *outfile)
{
	char	**all_paths;

	all_paths = paths(env);
	if (!all_paths)
		exit(-1);
	parsing_in(p, infile, all_paths);
	parsing_out(p, outfile, all_paths);
	free_the_tab(all_paths);
}

void	init_pipex(t_pipex *p, int argc, char **argv, char **env)
{
	if (argc == 5)
	{
		p->here_doc = false;
		p->status_code = 0;
		p->cmd1 = ft_split(argv[2], ' ');
		if (!p->cmd1)
			exit(-1);
		p->cmd2 = ft_split(argv[3], ' ');
		if (!p->cmd1)
			exit(-1);
		p->fd_infile = -1;
		p->fd_outfile = -1;
		parsing(p, env, argv[1], argv[4]);
		return ;
	}
	if (argc > 5)
		init_bonus(p, argc, argv, env);
	else
		error_argument();
}
