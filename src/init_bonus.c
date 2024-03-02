#include "../inc/pipex_bonus.h"

void	init_cmds(t_pipex_bonus *p_b, int argc, char **argv)
{
	int	i;

	i = 0;
	p_b->cmd = malloc(sizeof(char **) * (argc - 2));
	p_b->cmd_path = malloc(sizeof(char *) * (argc - 2));
	while (i < argc - 3)
	{
		p_b->cmd[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
	p_b->cmd[i] = NULL;
}

void	check_in(t_pipex_bonus *p_b, char **argv, char **all_paths)
{
	if (access(argv[1], R_OK))
	{
		perror(argv[1]);
		p_b->fd_infile = -1;
		p_b->cmd_path[0] = NULL;
	}
	else
	{
		p_b->fd_infile = open(argv[1], O_RDONLY);
		if (p_b->fd_infile == -1)
			perror(argv[1]);
		p_b->cmd_path[0] = check_path(p_b->cmd[0][0], all_paths);
	}
}

void	check_all_command(t_pipex_bonus *p_b, char **all_paths)
{
	int	i;

	i = 1;
	while (p_b->cmd[i])
	{
		p_b->cmd_path[i] = check_path(p_b->cmd[i][0], all_paths);
		i++;
	}
	p_b->cmd_path[i] = NULL;
}

void	check_out(t_pipex_bonus *p_b, int argc, char **argv)
{
	p_b->fd_outfile = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (p_b->fd_outfile == -1)
			perror(argv[argc - 1]);
}

void	init_multi_pipe(int argc, char **argv, char **env)
{
	t_pipex_bonus	p_b;
	char	**all_paths;

	all_paths = paths(env);
	init_cmds(&p_b, argc, argv);
	check_in(&p_b, argv, all_paths);
	check_all_command(&p_b, all_paths);
	check_out(&p_b, argc, argv);
	multi_pipe(&p_b, env);
	ft_putendl_fd("SUCCESS", 2);
	exit(EXIT_SUCCESS);
}
