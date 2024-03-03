#include "../inc/pipex_bonus.h"

void	init_pipe_fd(t_pipex_bonus *p_b, int argc)
{
	int	pipe_number;
	int	i;

	pipe_number = argc - 4;
	i = 0;
	p_b->p_fd = malloc(sizeof(int *) * (pipe_number));

	while (i < pipe_number)
	{
		p_b->p_fd[i] = malloc(sizeof(int) * 2);
		if (pipe(p_b->p_fd[i]))
			exit(EXIT_FAILURE);
		i++;
	}

}

void	close_all_except(t_pipex_bonus *p_b, int in, int out, int argc)
{
	int	i;

	i = 0;
	while (i < (argc - 4))
	{
		if (p_b->p_fd[i][0] != in)
			close(p_b->p_fd[i][0]);
		if (p_b->p_fd[i][1] != out)
			close(p_b->p_fd[i][1]);
		i++;
	}
}

void	first_command(t_pipex_bonus *p_b, int argc, char **env)
{
	close_all_except(p_b, -1, p_b->p_fd[0][1], argc);
	dup2(p_b->fd_infile, STDIN_FILENO);
	dup2(p_b->p_fd[0][1] , STDOUT_FILENO);
	execve(p_b->cmd_path[0], p_b->cmd[0], env);
}

void	next_command(t_pipex_bonus *p_b, int argc, char **env, int i)
{
	close_all_except(p_b, p_b->p_fd[i - 1][0], p_b->p_fd[i][1], argc);
	dup2(p_b->p_fd[i - 1][0], STDIN_FILENO);
	dup2(p_b->p_fd[i][1] , STDOUT_FILENO);
	execve(p_b->cmd_path[i], p_b->cmd[i], env);
	ft_putendl_fd("ok", p_b->fd_outfile);
}

void	last_command(t_pipex_bonus *p_b, int argc, char **env, int i)
{
	close_all_except(p_b, p_b->p_fd[i - 1][0], -1, argc);
	dup2(p_b->p_fd[i - 1][0], STDIN_FILENO);
	dup2(p_b->fd_outfile, STDOUT_FILENO);
	execve(p_b->cmd_path[i], p_b->cmd[i], env);
}

void	execute_command(t_pipex_bonus *p_b, int argc, char **env, int i)
{
	if (i == 0)
		first_command(p_b, argc, env);

	else if (i != argc - 4)
	{
		next_command(p_b, argc, env, i);
	}
	if (i == argc - 4)
		last_command(p_b, argc, env, i);
}

void	free_the_pipe(t_pipex_bonus *p_b, int argc)
{
	int	pipe_number;
	int	i;

	pipe_number = argc - 4;
	i = 0;

	while (i < pipe_number)
	{
		free(p_b->p_fd[i]);
		i++;
	}
	free(p_b->p_fd);
}

void    multi_pipe(t_pipex_bonus *p_b, int argc, char **env)
{
	int i;

	init_pipe_fd(p_b, argc);
	//close_all_except(p_b, -1, -1, argc); /// <-
	p_b->fork_pid = malloc(sizeof(int) * (argc - 3));
	i = 0;

	while (i < (argc - 3))
	{
		p_b->fork_pid[i] = fork();
		if (p_b->fork_pid[i] < 0)
			exit(EXIT_FAILURE);

		if (p_b->fork_pid[i] == 0)
		{
			if (p_b->cmd_path[i])
				execute_command(p_b, argc, env, i);
			exit(EXIT_FAILURE);
		}
		else
			i++;
	}
	close_all_except(p_b, -1, -1, argc);
	waitpid(p_b->fork_pid[argc - 4], NULL, 0);
	free(p_b->fork_pid);
	free_the_pipe(p_b, argc);
}
