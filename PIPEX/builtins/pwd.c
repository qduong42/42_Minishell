/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:23:29 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/04 21:16:54 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * @brief cmd to ouput cwd (child buildin), arguments should not exist
 * 
 * @param cmd 
 * @return int exit status
 */
int	pwd(void)
{
	char	cwd[FT_PATH_MAX];

	if (getcwd(cwd, FT_PATH_MAX))
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	return (2);
}

/**
 * @brief Get the pwd string (allocated)
 * 
 * @return char* 
 */
char	*get_pwd(void)
{
	char		*cwd;

	cwd = malloc(sizeof(char) * FT_PATH_MAX);
	if (getcwd(cwd, FT_PATH_MAX))
		return (cwd);
	else
		free(cwd);
	return (NULL);
}

/**
 * @brief takes a single list element and replaces content
 * 
 * @param env 
 * @param new1 first part of the content (concatenated)
 * @param new2 second part of the content (concatenated)
 */
static void	replace_content(t_list *env, char *new1, char *new2)
{
	int	len;

	len = ft_strlen(new1) + ft_strlen(new2) + 1;
	free(env->content);
	env->content = malloc(sizeof(char) * len);
	ft_bzero(env->content, len);
	ft_strlcpy(env->content, new1, len);
	ft_strlcat(env->content, new2, len);
}

/**
 * @brief changes pwd/oldpwd to the desired values (NULL = no change)
 * 
 * @param pwd new value of pwd
 * @param oldpwd new value of oldpwd
 * @param env 
 */
void	update_env(char *pwd, char *oldpwd, t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (pwd)
		{
			if (!ft_strncmp(tmp->content, "PWD=", 4))
			{
				replace_content(tmp, "PWD=", pwd);
				return ;
			}
		}
		if (oldpwd)
		{
			if (!ft_strncmp(tmp->content, "OLDPWD=", 7))
			{
				replace_content(tmp, "OLDPWD=", oldpwd);
				return ;
			}
		}
		tmp = tmp->next;
	}
	if (oldpwd)
		ft_lstadd_back(&env, ft_lstnew(ft_strjoin("OLDPWD=", oldpwd)));
}
