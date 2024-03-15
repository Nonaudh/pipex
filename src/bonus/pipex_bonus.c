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

int	write_here_doc(char **argv)
{
	char	*hd;
	int		fd_hd;

	fd_hd = open("here_doc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	ft_putstr_fd("> ", 0);
	hd = get_next_line(0);
	while (!ft_strnstr(hd, argv[2], ft_strlen(hd)))
	{
		write(fd_hd, hd, ft_strlen(hd));
		free(hd);
		ft_putstr_fd("> ", 0);
		hd = get_next_line(0);
	}
	free(hd);
	close(fd_hd);
	return (0);
}

void	multi_clean_exit(t_pipex_bonus *p_b, int size)
{
	close(p_b->fd_infile);
	close(p_b->fd_outfile);
	free(p_b->cmd);
	free_the_tab(p_b->all_paths);
}

void	bonus_pipe(int argc, char **argv, char **env)
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
