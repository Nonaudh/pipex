#include "../../inc/pipex_bonus.h"

void	init_struct(t_pipe *f, int argc)
{
	f->fork_pid = malloc(sizeof(int) * (argc - 3));
	if (!f->fork_pid)
		exit(-1);
	init_pipe_fd(f, argc);
}

void	free_struct(t_pipe *f, int argc)
{
	free(f->fork_pid);
	free_the_pipe(f, argc);
}
