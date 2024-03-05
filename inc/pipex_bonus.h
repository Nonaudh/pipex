/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:08:44 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 15:08:48 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

typedef struct s_pipex_bonus
{
	int		fd_infile;
	int		fd_outfile;
	char	***cmd;
	char	**cmd_path;
	int		**p_fd;
	int		*fork_pid;
	int		status_code;
}	t_pipex_bonus;

void	init_multi_pipe(int argc, char **argv, char **env);
void	check_out(t_pipex_bonus *p_b, int argc, char **argv, char **all_paths);
void	check_in(t_pipex_bonus *p_b, char **argv, char **all_paths);
void	init_cmds(t_pipex_bonus *p_b, int argc, char **argv);

void	multi_pipe(t_pipex_bonus *p_b, int argc, char **env);
void	execute_command(t_pipex_bonus *p_b, int argc, char **env, int i);
void	last_command(t_pipex_bonus *p_b, int argc, char **env, int i);
void	next_command(t_pipex_bonus *p_b, int argc, char **env, int i);
void	first_command(t_pipex_bonus *p_b, int argc, char **env);

void	init_bonus(t_pipex *p, int argc, char **argv, char **env);
int		write_here_doc(char **argv);

void	init_pipe_fd(t_pipex_bonus *p_b, int argc);
void	close_all_except(t_pipex_bonus *p_b, int in, int out, int argc);
void	free_the_pipe(t_pipex_bonus *p_b, int argc);
void	multi_clean_exit(t_pipex_bonus *p_b, int argc);

#endif
