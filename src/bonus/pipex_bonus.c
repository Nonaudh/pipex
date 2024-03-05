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

	fd_hd = open("here_doc.txt", O_RDWR | O_TRUNC | O_CREAT, 0666);
	ft_putstr_fd("> ", 0);
	hd = get_next_line(0);
	while (!ft_strnstr(hd, argv[2], ft_strlen(argv[2])))
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

void	init_bonus(t_pipex *p, int argc, char **argv, char **env)
{
	if (!ft_strncmp(argv[1], "here_doc", 8) && argc == 6)
	{
		p->here_doc = true;
		write_here_doc(argv);
		p->cmd1 = ft_split(argv[3], ' ');
		p->cmd2 = ft_split(argv[4], ' ');
		parsing(p, env, "here_doc.txt", argv[5]);
	}
	else
	{
		init_multi_pipe(argc, argv, env);
	}
}
