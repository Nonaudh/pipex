/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:09:10 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 16:20:07 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	char	*cmd1;
	char	*cmd2;
	char	**all_paths;
	int		status_code;
}	t_pipex;

struct {
	int argc;
	char *argv[];
	char *envp[];

	int f 
} t_command;

struct {
	bool did_launch_well;
	pid_t pid;
}	t_execution_result;

t_execution exec_command(const t_command *command) {
	t_execution_result result;

	result.pid = fork();
	if (result.pid < 0) {
		return ((t_execution_result){.did_launch_well = false});
	}
	if (result.pid == 0) {
		dup2 ...
		execve 
		()
		...

	}
	return 
}

close_if_not_standard(int fd) {
	if (fd != 0 && fd != 1) {
		close (fd);
	}
}


exec_commands(const t_command *commands[], int fd_infile, int fd_outfile) {

	int fds[2];
	int fd_in = fd_infile;
	int fd_out;

	for command in num_commands {
		if (is not last command) {
			pipe(fds)
			fd_out= fds[1];
		}
		else {
			fd_out =fd_outfile
		}

		execute_command(command, fd_in, fd_out)
		close_if_not_standard(fd_out);
		close_if_not_standard(fd_in);

		fd_in = fds[0];
	}


}


void	mandatory_pipe(char **argv, char **env);
void	init_pipex(t_pipex *p, char **argv, char **env);
void	pipe_bonus(int argc, char **argv, char **env);

void	open_files(t_pipex *p, char **argv);
void	open_outfile(t_pipex *p, char *outfile);
void	open_infile(t_pipex *p, char *infile);

void	pipex(t_pipex *p, char **env);
void	command_in(t_pipex *p, char **env, int *pfd);
void	command_out(t_pipex *p, char **env, int *pfd);

void	clean_struct(t_pipex *p);
char	**paths(char **env);
char	*find_command_path(char *cmd, char **paths);
void	free_the_tab(char **tab);
void	error_argument(void);

#endif
