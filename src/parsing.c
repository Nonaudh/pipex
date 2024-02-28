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

void	parsing(char **argv, char **env, t_pipex *p)
{
	if (p->here_doc)
	{
		p->cmd1 = ft_split(argv[3], ' ');
		p->cmd2 = ft_split(argv[4], ' ');
	}
	else
	{
		p->cmd1 = ft_split(argv[2], ' ');
		p->cmd2 = ft_split(argv[3], ' ');
	}
	p->paths = paths(env);
}

int	write_here_doc(char **argv)
{
	char	*hd;
	int		fd_hd;

	fd_hd = open("here_doc.txt", O_RDWR | O_TRUNC | O_CREAT, 0777);
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
	return(0);
}

void    init_pipex(t_pipex *p, char **argv, int argc)
{
	if (argc < 5)
		exit(EXIT_FAILURE);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		p->here_doc = true;
		write_here_doc(argv);
		p->fd_infile = open("here_doc.txt", O_RDONLY);
		//if (p->fd_infile == -1)
			//exit(EXIT_FAILURE);
		p->fd_outfile = open(argv[5], O_RDWR | O_APPEND);
		//if (p->fd_outfile == -1)
			//exit(EXIT_FAILURE);
	}
	else
	{
		p->here_doc = false;
		p->fd_infile = open(argv[1], O_RDONLY);
		//if (p->fd_infile == -1)
			//exit(EXIT_FAILURE);
		p->fd_outfile = open(argv[4], O_RDWR | O_TRUNC);
		//if (p->fd_outfile == -1)
			//exit(EXIT_FAILURE);
	}	
}
