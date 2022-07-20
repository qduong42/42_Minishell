/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:39 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/19 12:05:35 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_vars *vars)
{
	char	*buffer;

	while (1)
	{
		vars->temp_doc = open(".temp_doc", O_RDWR | O_CREAT | O_APPEND, 0644);
		if (vars->temp_doc == -1)
		{
			perror("open(temp_doc)");
			exit(-1);
		}
		ft_putstr_fd("heredoc> ", 1);
		buffer = get_next_line(0);
		if (!ft_strncmp(buffer, vars->av[2], ft_strlen(vars->av[2])))
		{
			free(buffer);
			break ;
		}
		ft_putstr_fd(buffer, vars->temp_doc);
		close(vars->temp_doc);
		free(buffer);
	}
}

void	conditions2(t_vars *vars)
{
	if (vars->ac >= 3)
	{
		if (ft_strncmp(vars->av[1], "here_doc", 8))
		{
			vars->infile = open(vars->av[1], O_RDONLY);
			if (vars->infile == -1)
			{
				perror("open(infile)");
				exit(-1);
			}
			dup2(vars->infile, 0);
			vars->i = 2;
			vars->here_doc = 0;
			if (vars->ac == 3)
			{
				vars->is_outfile = 0;
				vars->last_cmd = vars->ac - 1;
			}
			return ;
		}
		else
			ft_putstr_fd("pipex: here_doc requires one additional argument", 2);
		exit(-1);
	}
}

void	conditions(t_vars *vars)
{
	if (vars->ac < 3)
	{
		ft_putstr_fd("pipex: Wrong number of arguments", 2);
		exit(-1);
	}
	if (vars->ac >= 4)
	{
		if (!ft_strncmp(vars->av[1], "here_doc", 8))
		{
			here_doc(vars);
			dup2(vars->temp_doc, 0);
			vars->i = 3;
			vars->here_doc = 1;
			return ;
		}
	}
	conditions2(vars);
}

void	free_all(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

char	*get_path(char *cmd, char **env)
{
	t_path	path;

	path.i = 0;
	while (ft_strncmp(env[path.i], "PATH=", 5))
		path.i++;
	path.prefix = ft_split(env[path.i] + 5, ':');
	path.i_pre = 0;
	while (path.prefix[path.i_pre])
	{
		path.temp = ft_strjoin(path.prefix[path.i_pre], "/");
		path.joined = ft_strjoin(path.temp, cmd);
		free(path.temp);
		if (!access(path.joined, F_OK))
		{
			free_all(path.prefix);
			return (path.joined);
		}
		free(path.joined);
		path.i_pre++;
	}
	free_all(path.prefix);
	return (cmd);
}

void	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
}
