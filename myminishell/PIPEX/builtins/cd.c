/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:20:30 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/28 10:06:17 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * @brief can't change env's first element
 * 
 * @param to 
 * @param error 
 * @param env 
 * @return int 
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
	free (to_free);
	return (cd_ret);
}

int	ft_home(t_list *env)
{
	t_list	*tmp;
	int		cd_ret;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "HOME=", 5))
			cd_ret = change_dir(tmp->content + 5, \
			"ERROR: the home env variable is not properly defined\n", env);
		tmp = tmp->next;
	}
	return (cd_ret);
}

int	ft_oldpwd(t_list *env)
{
	t_list	*tmp;
	int		cd_ret;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "OLDPWD=", 7))
			cd_ret = change_dir(tmp->content + 7, \
			"ERROR: the OLPWD is corrupted\n", env);
		tmp = tmp->next;
	}
	return (cd_ret);
}

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
