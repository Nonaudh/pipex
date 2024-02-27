#ifndef PIPEX_H
# define PIPEX_H

#include "../lib/libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_pipex
{
    int     fd_infile;
    int     fd_outfile;
    int     here_doc;
    char    **cmd1;
    char    **cmd2;
    char    **paths;
}   t_pipex;

typedef enum e_bool
{ 
    false,
    true,
}   t_bool;

void	parsing(int argc, char **argv, char **env, t_pipex *p);
char	**paths(char **env);
void    init_pipex(t_pipex *p, char **argv, char **env);

char	*check_path(char *cmd, t_pipex *p);
void	clean_exit(t_pipex *p);
void	free_the_tab(char **tab);



#endif