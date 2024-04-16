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
	p->all_paths = find_paths(env);
	if (!p->all_paths)
	{
		//close(p->fd_infile);
		//close(p->fd_outfile);
		//exit(1);
	}
}

void	mandatory_pipe(char **argv, char **env)
{
	t_pipex	p;

	open_files(&p, argv);
	init_pipex(&p, argv, env);
	pipex(&p, env);
	clean_struct(&p);
	exit(p.status_code);
}

void	check_env(char **env)
{
	if (!*env)
	{
		ft_putendl_fd("No env", 2);
		exit (1);
	}
}

int	main(int argc, char **argv, char **env)
{
	//check_env(env);
	if (argc == 5)
		mandatory_pipe(argv, env);
	else if (argc > 5)
		pipe_bonus(argc, argv, env);
	error_argument();
	return (0);
}
