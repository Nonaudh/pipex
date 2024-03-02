#include "../inc/pipex.h"

void	free_the_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

void	clean_exit(t_pipex *p)
{
	if (p->here_doc)
		unlink("here_doc.txt");
	if(p->cmd1)
		free_the_tab(p->cmd1);
	if(p->cmd2)
		free_the_tab(p->cmd2);
	if(p->cmd1_path)
		free(p->cmd1_path);
	if(p->cmd2_path)
		free(p->cmd2_path);
	if (p->fd_infile != -1)
		close(p->fd_infile);
	if (p->fd_outfile != -1)
		close(p->fd_outfile);
}

char	*check_path(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	char	*dir;

	i = 0;
	if (!cmd)
		return (NULL);
	dir = ft_strjoin("/", cmd);
	
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], dir);
		if(!access(full_path, X_OK))
		{
			free(dir);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	free(dir);
	return (NULL);
}

char	**paths(char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	return (ft_split(env[i] + 5, ':'));
}

void	error_argument(void)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd("Arguments available\n", 2);
	ft_putendl_fd("\t./pipex infile cmd cmd1 outfile", 2);
	ft_putendl_fd("\t./pipex here_doc LIMITER cmd cmd1 outfile\n", 2);
	exit(EXIT_FAILURE);
}