/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:09:10 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 15:09:13 by ahuge            ###   ########.fr       */
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

void	parsing(t_pipex *p, char **env, char *infile, char *outfile);
char	**paths(char **env);
void	init_pipex(t_pipex *p, int argc, char **argv, char **env);

char	*check_path(char *cmd, char **paths);
void	clean_exit(t_pipex *p);
void	free_the_tab(char **tab);
void	error_argument(void);

void	init_bonus(t_pipex *p, int argc, char **argv, char **env);

#endif
