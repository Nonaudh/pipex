#include "../inc/pipex.h"

int	main (int argc, char **argv, char **env)
{
	t_pipex	pipex;
	char *path;
	init_pipex(&pipex, argv, env);
	parsing(argc, argv, env, &pipex);
	path = search_path(pipex.cmd1[0], &pipex);
	if (path)
		ft_printf("%s\n", path);
	else
		ft_printf("KO\n");
	free(path);
	clean_exit(&pipex);
}
