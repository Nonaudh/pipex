#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include "pipex.h"

typedef struct s_pipex_bonus
{
    int     fd_infile;
    int     fd_outfile; 
    char    ***cmd;
    char    **cmd_path;
    int	    **p_fd;
	int	    *fork_pid;
}   t_pipex_bonus;

void    init_multi_pipe(int argc, char **argv, char **env);

void    multi_pipe(t_pipex_bonus *p_b, int argc, char **env);

#endif