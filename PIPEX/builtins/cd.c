/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:20:30 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/03 14:25:30 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * @brief kepps track of env
 * 
 * @param to relative/absolute path
 * @param error msg to display if chdir() goes wrong
 * @param env 
 * @return int the exit status of chdir()
 */
int	change_dir(char *to, char *error, t_list *env)
{
	int		cd_ret;
	char	*to_free;

	to_free = get_pwd();
	cd_ret = chdir(to);
	if (!cd_ret)
	{
		update_env(NULL, to_free, env);
		free(to_free);
		to_free = get_pwd();
		update_env(to_free, NULL, env);
	}
	else
	{
		error_msg(error);
		cd_ret = 1;
	}
	if (to_free)
		free (to_free);
	return (cd_ret);
}

/**
 * @brief gets the path to 'home' and calls change_dir() with it
 * 
 * @param env to get the home-env-variable
 * @return int exit status
 */
int	ft_home(t_list *env)
{
	t_list	*tmp;
	int		cd_ret;

	tmp = env;
	while (1)
	{
		if (!tmp)
		{
			error_msg("Home is not set\n");
			cd_ret = 1;
			break ;
		}
		if (!ft_strncmp(tmp->content, "HOME=", 5))
		{
			cd_ret = change_dir(tmp->content + 5, \
			"ERROR: the home env variable is not properly defined\n", env);
			break ;
		}
		tmp = tmp->next;
	}
	return (cd_ret);
}

/**
 * @brief gets the path to 'oldpwd' and calls change_dir() with it
 * 
 * @param env to get the oldpwd-env-variable
 * @return int exit status
 */
int	ft_oldpwd(t_list *env)
{
	t_list	*tmp;
	int		cd_ret;

	tmp = env;
	while (1)
	{
		if (!tmp)
		{
			error_msg("OLDPWD is not set\n");
			cd_ret = 1;
			break ;
		}
		if (!ft_strncmp(tmp->content, "OLDPWD=", 7))
		{
			cd_ret = change_dir(tmp->content + 7, \
			"ERROR: the OLPWD is corrupted\n", env);
			break ;
		}
		tmp = tmp->next;
	}
	return (cd_ret);
}

/**
 * @brief a buildin of the parent process, changes it's working directory and env
 * 
 * @param args the command and arguments/options
 * @param env 
 * @return int exit status
 */
int	ft_cd(char **args, t_list *env)
{
	int			cd_ret;
	char		*to_free;

	if (!args[1] || !ft_strncmp(args[1], "~", 2))
		return (ft_home(env));
	else if (!ft_strncmp(args[1], "-", 2))
		return (ft_oldpwd(env));
	else if (args[1][0] == '~')
	{
		to_free = malloc(FT_PATH_MAX * sizeof(char));
		while (env)
		{
			if (!ft_strncmp(env->content, "HOME=", 5))
				ft_strlcpy(to_free, env->content + 5, FT_PATH_MAX);
			env = env->next;
		}
		ft_strlcat(to_free, args[1] + 1, FT_PATH_MAX);
		cd_ret = change_dir(to_free, \
		"ERROR: the given argument is not a valid directory\n", env);
		free(to_free);
	}
	else
		cd_ret = change_dir(args[1], \
		"ERROR: the given argument is not a valid directory\n", env);
	return (cd_ret);
}
