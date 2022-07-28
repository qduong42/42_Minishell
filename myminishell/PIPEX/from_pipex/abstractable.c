/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstractable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:47:12 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 21:22:01 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_path(char *cmd, char **env)
{
	t_path	path;

	path.i = 0;
	while (env[path.i] && ft_strncmp(env[path.i], "PATH=", 5))
		path.i++;
	if (!env[path.i])
		return (cmd);
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
	return (ft_strdup(cmd));
}

char	**lst_to_strstr(t_list *env)
{
	char	**ret;
	int		i;
	t_list	*tmp;

	ret = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	i = 0;
	tmp = env;
	while (1)
	{
		if (i == ft_lstsize(env))
		{
			ret[i] = NULL;
			return (ret);
		}
		ret[i] = malloc(sizeof(char) * (ft_strlen(tmp->content) + 1));
		ft_strlcpy(ret[i], tmp->content, ft_strlen(tmp->content) + 1);
		i++;
		tmp = tmp->next;
	}
	return (NULL);
}

int	create_hd(char *delim)
{
	int		fd;
	char	*line;

	while (1)
	{
		fd = open(".temp_doc", O_CREAT | O_RDWR | O_APPEND, 0777);
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!ft_strncmp(line, delim, ft_strlen(line) - 1))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
		close(fd);
	}
	return (fd);
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

void	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
}
