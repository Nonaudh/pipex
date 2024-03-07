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
	char	**cmd1;
	char	**cmd2;
	char	*cmd1_path;
	char	*cmd2_path;
	int		status_code;
	t_bool	here_doc;

}	t_pipex;

void	init_pipex(t_pipex *p, int argc, char **argv, char **env);
void	parsing(t_pipex *p, char **env, char *infile, char *outfile);
void	parsing_out(t_pipex *p, char *outfile, char **all_paths);
void	parsing_in(t_pipex *p, char *infile, char **all_paths);

void	execute_programs(t_pipex *p, char **env);
void	command_out(t_pipex *p, char **env, int *pfd);
void	command_in(t_pipex *p, char **env, int *pfd);

void	error_argument(void);
char	**paths(char **env);
char	*find_command_path(char *cmd, char **paths);
void	clean_exit(t_pipex *p);
void	free_the_tab(char **tab);

void	init_bonus(t_pipex *p, int argc, char **argv, char **env);

#endif
