/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:53:04 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/14 11:53:06 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	open_infile(t_pipex *p, char *infile)
{
	p->fd_infile = open(infile, O_RDONLY);
	if (p->fd_infile == -1)
		perror(infile);
}

void	open_outfile(t_pipex *p, char *outfile)
{
	p->fd_outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (p->fd_outfile == -1)
		perror(outfile);
}

void	open_files(t_pipex *p, char **argv)
{
	open_infile(p, argv[1]);
	open_outfile(p, argv[4]);
}
