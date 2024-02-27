#include "../inc/pipex.h"

int	main (int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		pfd[2];
	int		pid1;
	int		pid2;
	//char 	*path;

	init_pipex(&pipex, argv, env);
	parsing(argc, argv, env, &pipex);
	/*path = check_path(pipex.cmd1[0], &pipex);
	if (path)
		ft_printf("%s\n", path);
	else
		ft_printf("KO\n");*/
	if (pipe(pfd))
		exit(EXIT_FAILURE);
	if ((pid1 = fork()) < 0)
		exit(EXIT_FAILURE);
	if (pid1 == 0)
	{
		dup2(pfd[0], STDOUT_FILENO);//pipex.fd_infile);
		close(pfd[0]);
		close(pfd[1]);
		execve(check_path(pipex.cmd1[0], &pipex), pipex.cmd1, env);
	}
	if ((pid2 = fork()) < 0)
		exit(EXIT_FAILURE);
	if (pid2 == 0)
	{
		dup2(pfd[1], STDIN_FILENO);//pipex.fd_outfile);
		close(pfd[0]);
		close(pfd[1]);
		execve(check_path(pipex.cmd2[0], &pipex), pipex.cmd2, env);
	}
	close(pfd[0]);
	close(pfd[1]);
	
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	clean_exit(&pipex);
}
