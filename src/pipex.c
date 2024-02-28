#include "../inc/pipex.h"

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
	{
		close(pfd[0]);
		dup2(p->fd_infile, STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		execve(check_path(p->cmd1[0], p), p->cmd1, env);
	}
	else
	{
		if ((pid2 = fork()) < 0)
			exit(EXIT_FAILURE);
		if (pid2 == 0)
		{
			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
			dup2(p->fd_outfile, STDOUT_FILENO);
			execve(check_path(p->cmd2[0], p), p->cmd2, env);
		}
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main (int argc, char **argv, char **env)
{
	t_pipex	pipex;
	/*int		pfd[2];
	int		pid1;
	int		pid2;*/

	init_pipex(&pipex, argv, env);
	parsing(argc, argv, env, &pipex);

	executes_program(&pipex, env);

	/*if (pipe(pfd))
		exit(EXIT_FAILURE);
	if ((pid1 = fork()) < 0)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
	{
		close(pfd[0]);
		dup2(pipex.fd_infile, STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		execve(check_path(pipex.cmd1[0], &pipex), pipex.cmd1, env);
	}
	else
	{
		if ((pid2 = fork()) < 0)
			exit(EXIT_FAILURE);
		if (pid2 == 0)
		{
			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
			dup2(pipex.fd_outfile, STDOUT_FILENO);
			execve(check_path(pipex.cmd2[0], &pipex), pipex.cmd2, env);
		}
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);*/
	clean_exit(&pipex);
}
