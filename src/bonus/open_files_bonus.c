/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:25:24 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/19 14:25:26 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	write_here_doc(char **argv)
{
	char	*hd;
	int		fd_hd;

	fd_hd = open("/tmp/here_doc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_hd == -1)
		exit(1);
	ft_putstr_fd("> ", 0);
	hd = get_next_line(0);
	while (hd && (ft_strncmp(hd, argv[2], ft_strlen(argv[2]))
			|| (ft_strlen(hd) - 1 != ft_strlen(argv[2]))))
	{
		write(fd_hd, hd, ft_strlen(hd));
		free(hd);
		ft_putstr_fd("> ", 0);
		hd = get_next_line(0);
	}
	free(hd);
	close(fd_hd);
}

void	open_infile_bonus(t_pipex_bonus *p_b, char *infile)
{
	p_b->fd_infile = open(infile, O_RDONLY);
	if (p_b->fd_infile == -1)
		perror(infile);
	if (p_b->here_doc)
		unlink(infile);
}

void	open_outfile_bonus(t_pipex_bonus *p_b, char *outfile)
{
	if (!p_b->here_doc)
		p_b->fd_outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		p_b->fd_outfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (p_b->fd_outfile == -1)
		perror(outfile);
}

void	open_bonus_files(t_pipex_bonus *p_b, int argc, char **argv)
{
	if (!p_b->here_doc)
		open_infile_bonus(p_b, argv[1]);
	else
		open_infile_bonus(p_b, "/tmp/here_doc");
	open_outfile_bonus(p_b, argv[argc - 1]);
}
