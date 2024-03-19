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
