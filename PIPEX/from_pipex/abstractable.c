/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstractable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:47:12 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/04 12:23:38 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * @brief closes all fds execept the standards
 * 
 */
void	close_all(void)
{
	int	i;

	i = 3;
	while (i < MAX_FDS)
	{
		close(i);
		i++;
	}
}

/**
 * @brief name contained in PATH -> absolute path
 * 
 * @param cmd the name (contained/not contained) in path
 * @param env the env-lst for PATH
 * @return char* the allocated absolute path
 */
char	*get_path(char *cmd, char **env)
{
	t_path	path;

	path.i = 0;
	while (env[path.i] && ft_strncmp(env[path.i], "PATH=", 5))
		path.i++;
	if (!env[path.i])
		return (ft_strdup(cmd));
	path.prefix = ft_split(env[path.i] + 5, ':');
	path.i_pre = 0;
	while (path.prefix[path.i_pre])
	{
		path.temp = ft_strjoin(path.prefix[path.i_pre], "/");
		path.joined = ft_strjoin(path.temp, cmd);
		free(path.temp);
		if (!access(path.joined, F_OK))
		{
			ft_free_all(path.prefix);
			return (path.joined);
		}
		free(path.joined);
		path.i_pre++;
	}
	ft_free_all(path.prefix);
	return (ft_strdup(cmd));
}

/**
 * @brief lst->strstr
 * 
 * @param env 
 * @return char** (allocated)
 */
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

/**
 * @brief put string to stderr
 * 
 * @param msg 
 */
void	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
}
