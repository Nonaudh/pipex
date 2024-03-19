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

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_pipe
{
	int	*fork_pid;
	int	**pipe_fd;
	int	*cmd_count;
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

void	pipe_bonus(int argc, char **argv, char **env);
void	init_multi_pipe(t_pipex_bonus *p_b, int argc, char **argv, char **env);
void	init_cmds(t_pipex_bonus *p_b, char **argv);
void	init_pipex_bonus(t_pipex_bonus *p_b, int argc, char **argv, char **env);

void	open_bonus_files(t_pipex_bonus *p_b, int argc, char **argv);
void	open_outfile_bonus(t_pipex_bonus *p_b, char *outfile);
void	open_infile_bonus(t_pipex_bonus *p_b, char *infile);
void	write_here_doc(char **argv);

void	multi_pipe(t_pipex_bonus *p_b, int argc, char **env);
void	execute_command(t_pipex_bonus *p_b, t_pipe *f, char **env, int i);
void	last_command(t_pipex_bonus *p_b, t_pipe *f, char **env, int i);
void	middle_command(t_pipex_bonus *p_b, t_pipe *f, char **env, int i);
void	first_command(t_pipex_bonus *p_b, t_pipe *f, char **env);

void	multi_clean_exit(t_pipex_bonus *p_b);
void	init_pipe_fd(t_pipe *f, int argc);
void	close_all_except(t_pipe *f, int in, int out, int argc);
void	free_the_pipe(t_pipe *f, int argc);

void	init_struct(t_pipex_bonus *p_b, t_pipe *f, int argc);
void	free_struct(t_pipe *f);

#endif
