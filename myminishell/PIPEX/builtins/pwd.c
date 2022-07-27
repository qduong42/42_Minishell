/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:23:29 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 10:25:37 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	pwd(t_pipe *cmd)
{
	char	cwd[PATH_MAX];

	if (cmd->argv[1] != NULL)
		return (1);
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	return (2);
}

char	*get_pwd(void)
{
	char		*cwd;

	cwd = malloc(sizeof(char) * PATH_MAX);
	if (getcwd(cwd, PATH_MAX))
		return (cwd);
	return (NULL);
}

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

void	update_env(char *pwd, char *oldpwd, t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (pwd)
		{
			if (!ft_strncmp(tmp->content, "PWD=", 4))
				replace_content(tmp, "PWD=", pwd);
		}
		if (oldpwd)
		{
			if (!ft_strncmp(tmp->content, "OLDPWD=", 7))
				replace_content(tmp, "OLDPWD=", oldpwd);
		}
		tmp = tmp->next;
	}
}
