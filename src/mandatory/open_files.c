#include "../../inc/pipex.h"


void    open_infile(t_pipex *p, char *infile)
{
	if (access(infile, R_OK))
	{
		perror(infile);
		exit(1);
	}
	else
	{
		p->fd_infile = open(infile, O_RDONLY);
		if (!p->fd_infile)
			exit(-1);
	}
}

void    open_outfile(t_pipex *p, char *outfile)
{
	if (access(outfile, W_OK))
	{
		perror(outfile);
		close(p->fd_infile);
		exit(1);
	}
	else
	{
		p->fd_outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (p->fd_outfile == -1)
		{
			perror(outfile);
			close(p->fd_infile);
			exit(-1);
		}
	}
}

void	open_files(t_pipex *p, char **argv)
{
	open_infile(p, argv[1]);
	open_outfile(p, argv[4]);
}