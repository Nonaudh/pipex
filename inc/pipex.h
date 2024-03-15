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

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	char	*cmd1;
	char	*cmd2;
	char	**all_paths;
	int		status_code;
}	t_pipex;


void	mandatory_pipe(int argc, char **argv, char **env);

void	bonus_pipe(int argc, char **argv, char **env);

void	init_pipex(t_pipex *p, char **argv, char **env);

void	open_files(t_pipex *p, char **argv);
void    open_infile(t_pipex *p, char *infile);
void    open_outfile(t_pipex *p, char *outfile);

void	check_env(char **env);


void	parsing(t_pipex *p, char **env, char *infile, char *outfile);
void	parsing_out(t_pipex *p, char *outfile, char **all_paths);
void	parsing_in(t_pipex *p, char *infile, char **all_paths);

void	execute_programs(t_pipex *p, char **env);
void	command_out(t_pipex *p, char **env, int *pfd);
void	command_in(t_pipex *p, char **env, int *pfd);

void	error_argument(void);
char	**paths(char **env);
char	*find_command_path(char *cmd, char **paths);
void	free_the_tab(char **tab);

#endif
