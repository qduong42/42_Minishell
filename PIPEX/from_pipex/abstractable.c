/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstractable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:47:12 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/03 16:21:35 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
 * @brief open a heredoc file and write to it
 * -> added strlen check for line to allow empty newline input to not stop HD
 * @param delim the input at which writing is stopped
 * @return int the filedescriptor of the heredoc
 * 
 */
int	create_hd(char *delim)
{
	int		pid;
	int		_pipe[2];
	char	*line;

	pipe(_pipe);
	pid = fork();
	if (!pid)
	{
		close(_pipe[0]);
		while (1)
		{
			ft_putstr_fd("> ", 2);
			line = get_next_line(0);
			if (!ft_strncmp(line, delim, ft_strlen(delim)))
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, _pipe[1]);
			free (line);
		}
		exit(0);
	}
	waitpid(pid, NULL, 0);
	close(_pipe[1]);
	return (_pipe[0]);
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
