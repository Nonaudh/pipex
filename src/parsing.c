#include "../inc/pipex.h"

void	parsing(char **argv, char **env, t_pipex *p)
{
	char	**all_paths;

	all_paths = paths(env);
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
	if (p->fd_infile != -1 && p->fd_outfile != -1)
	{
		p->cmd1_path = check_path(p->cmd1[0], all_paths);
		p->cmd2_path = check_path(p->cmd2[0], all_paths);
		//exit code (127);
	}
	else
	{
		p->cmd1_path = NULL;
		p->cmd2_path = NULL;
	}
	free_the_tab(all_paths);
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

void	open_here_doc(t_pipex *p, char **argv)
{
	p->fd_infile = open("here_doc.txt", O_RDONLY);
	if (p->fd_infile == -1)
		perror("here_doc.txt");
	p->fd_outfile = open(argv[5], O_RDWR | O_APPEND);
	if (p->fd_outfile == -1)
		perror(argv[5]);
}

void	open_files(t_pipex *p, char **argv)
{
	p->fd_infile = open(argv[1], O_RDONLY);
	if (p->fd_infile == -1)
		perror(argv[1]);
	p->fd_outfile = open(argv[4], O_RDWR | O_TRUNC);
	if (p->fd_outfile == -1)
		perror(argv[4]);
}

void    init_pipex(t_pipex *p, char **argv, int argc)
{	
	if (!ft_strncmp(argv[1], "here_doc", 8) && argc == 6)
	{
		p->here_doc = true;
		write_here_doc(argv);
		open_here_doc(p, argv);
		return ;
	}
	if (argc == 5)
	{
		p->here_doc = false;
		open_files(p, argv);
		return ;
	}
	error_argument();
}
