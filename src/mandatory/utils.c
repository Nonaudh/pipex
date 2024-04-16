/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:11:29 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 15:11:44 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	error_argument(void)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd("Arguments available\n", 2);
	ft_putendl_fd("\t./pipex infile cmd cmd1 outfile", 2);
	ft_putendl_fd("\t./pipex infile cmd cmd1 cmd2 ... cmdn outfile\n", 2);
	ft_putendl_fd("\t./pipex here_doc LIMITER cmd cmd1 outfile\n", 2);
	exit(EXIT_FAILURE);
}

void	free_the_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

char	*find_command_path(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	char	*dir;

	i = 0;
	if (!cmd)
		return (NULL);
	dir = ft_strjoin("/", cmd);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], dir);
		if (!access(full_path, X_OK))
		{
			free(dir);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	free(dir);
	return (NULL);
}

char	**paths(char **env)
{
	int	i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

void	clean_struct(t_pipex *p)
{
	free_the_tab(p->all_paths);
	if (p->fd_infile != -1)
		close(p->fd_infile);
	if (p->fd_outfile != -1)	
		close(p->fd_outfile);
}
