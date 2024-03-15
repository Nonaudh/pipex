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

typedef struct s_pipe
{
	int	*fork_pid;
	int	**pipe_fd;
}	t_pipe;

typedef struct s_pipex_bonus
{
	int		fd_infile;
	int		fd_outfile;
	char	**cmd;
	int		cmd_count;
	char	**all_paths;
	int		status_code;
	t_bool	here_doc;
}	t_pipex_bonus;



void	init_multi_pipe(t_pipex_bonus *p_b, int argc, char **argv, char **env);

void	check_out(t_pipex_bonus *p_b, int argc, char **argv, char **all_paths);
void	check_in(t_pipex_bonus *p_b, char **argv, char **all_paths);
void	init_cmds(t_pipex_bonus *p_b, int argc, char **argv);

void	multi_pipe(t_pipex_bonus *p_b, int argc, char **env);
void	execute_command(t_pipex_bonus *p_b, t_pipe *f, int argc, char **env, int i);
void	last_command(t_pipex_bonus *p_b, t_pipe *f, int argc, char **env, int i);
void	middle_command(t_pipex_bonus *p_b, t_pipe *f, int argc, char **env, int i);
void	first_command(t_pipex_bonus *p_b, t_pipe *f, int argc, char **env);

void	init_bonus(t_pipex *p, int argc, char **argv, char **env);
int		write_here_doc(char **argv);

void	init_pipe_fd(t_pipe *f, int argc);
void	close_all_except(t_pipe *f, int in, int out, int argc);
void	free_the_pipe(t_pipe *f, int argc);
void	multi_clean_exit(t_pipex_bonus *p_b, int argc);

#endif
