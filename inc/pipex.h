#ifndef PIPEX_H
# define PIPEX_H

#include "../lib/libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>

typedef enum e_bool
{ 
    false,
    true
}   t_bool;

typedef struct s_pipex
{
    int     fd_infile;
    int     fd_outfile;
    t_bool  here_doc;
    char    **cmd1;
    char    **cmd2;
    char    *cmd1_path;
    char    *cmd2_path;
}   t_pipex;

void	parsing(char **argv, char **env, t_pipex *p);
char	**paths(char **env);
void    init_pipex(t_pipex *p, char **argv, int argc);

char	*check_path(char *cmd, char **paths);
void	clean_exit(t_pipex *p);
void	free_the_tab(char **tab);
void	error_argument(void);

#endif