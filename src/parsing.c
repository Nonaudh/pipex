#include "../inc/pipex.h"

char	**paths(char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	if (env[i] == NULL)
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

void	parsing(int argc, char **argv, char **env, t_pipex *p)
{
	p->cmd1 = ft_split(argv[2], ' ');
	p->cmd2 = ft_split(argv[3], ' ');
	p->paths = paths(env);
}
void    init_pipex(t_pipex *p, char **argv, char **env)
{
	pid_t 	pid;
	char	*tab[] = {"what.txt", NULL};

	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		p->here_doc = 1;
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			ft_printf("ok\n");
			execve("/usr/bin/touch", tab, env);
			
		}
		wait((int *)-1);

	}
}