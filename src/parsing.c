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

int	write_here_doc(t_pipex *p, char **argv)
{
	char	*hd;
	int		fd_hd;

	fd_hd = open("here_doc.txt", O_RDWR, O_CREAT);
	ft_putstr_fd("pipe heredoc> ", 0);
	hd = get_next_line(0);
	while (!ft_strnstr(hd, argv[2], ft_strlen(argv[2])))
	{
		write(fd_hd, hd, ft_strlen(hd));
		free(hd);
		ft_putstr_fd("pipe heredoc> ", 0);
		hd = get_next_line(0);
	}
	free(hd);
	close(fd_hd);
	return(fd_hd);
}

void    init_pipex(t_pipex *p, char **argv, char **env)
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		p->here_doc = true;
		p->fd_infile = write_here_doc(p, argv);
		p->fd_outfile = open(argv[5], O_WRONLY, O_APPEND);

		/*pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
			execve("/usr/bin/touch",
				(char *[]){"touch", "here_doc.txt", NULL}, env);
		wait(NULL);*/
		
	}
	else
	{
		p->here_doc = false;
		p->fd_infile = open(argv[1], O_RDONLY);
		p->fd_outfile = open(argv[4], O_WRONLY);
	}
		
}
