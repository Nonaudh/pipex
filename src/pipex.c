#include "../inc/pipex.h"

void	execute(t_pipex *p, char **env, int pfd, int pfd2)
{
	close(pfd);
	dup2(p->fd_infile, STDIN_FILENO);
	dup2(pfd2, STDOUT_FILENO);
	execve(check_path(p->cmd1[0], p), p->cmd1, env);
}

void	execute2(t_pipex *p, char **env, int pfd, int pfd2)
{
	close(pfd2);
	dup2(pfd, STDIN_FILENO);
	dup2(p->fd_outfile, STDOUT_FILENO);
	execve(check_path(p->cmd2[0], p), p->cmd2, env);
}

void	executes_program(t_pipex *p, char **env)
{
	int		pfd[2];
	int		pid1;
	int		pid2;

	if (pipe(pfd))
		exit(EXIT_FAILURE);
	if ((pid1 = fork()) < 0)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
		execute(p, env, pfd[0], pfd[1]);
	else
	{
		if ((pid2 = fork()) < 0)
			exit(EXIT_FAILURE);
		if (pid2 == 0)
			execute2(p, env, pfd[0], pfd[1]);
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main (int argc, char **argv, char **env)
{
	t_pipex	pipex;

	init_pipex(&pipex, argv, argc);
	parsing(argv, env, &pipex);
	executes_program(&pipex, env);
	clean_exit(&pipex);
	return (0);
}
