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
	free_the_tab(p->cmd1);
	free_the_tab(p->cmd2);
	free_the_tab(p->paths);
}

char	*search_path(char *cmd, t_pipex *p)
{
	int		i;
	char	*full_path;
	char	*dir;

	i = 0;
	dir = ft_strjoin("/", cmd);
	while (p->paths[i])
	{
		full_path = ft_strjoin(p->paths[i], dir);
		if(!access(full_path, X_OK))
		{
			free(dir);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(dir);
	return(NULL);
}
