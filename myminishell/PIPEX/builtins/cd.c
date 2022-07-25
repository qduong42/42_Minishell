#include "../pipex.h"

static char	*get_pwd()
{
	char	*cwd;

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

static void	update_env(char *pwd, char *oldpwd, t_list *env)
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


int	ft_home(t_list *env)
{
	t_list	*tmp;
	int		cd_ret;
	char	*to_free;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "HOME=", 5))
		{
			to_free = get_pwd();
			cd_ret = chdir(tmp->content + 5);
			if (!cd_ret)
			{
				update_env(NULL, to_free, env);
				free(to_free);
				to_free = get_pwd();
				update_env(to_free, NULL, env);
			}
			else
			{
				error_msg("ERROR: the home env variable is not properly defined\n");
				cd_ret = 1;
			}
			free(to_free);
		}
		tmp = tmp->next;
	}
	return (cd_ret);
}

int	ft_oldpwd(t_list *env)
{
	t_list	*tmp;
	int		cd_ret;
	char	*to_free;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "OLDPWD=", 7))
		{
			to_free = get_pwd();
			cd_ret = chdir(tmp->content + 7);
			if (!cd_ret)
			{
				update_env(NULL, to_free, env);
				free(to_free);
				to_free = get_pwd();
				update_env(to_free, NULL, env);
			}
			else
			{
				error_msg("ERROR: the OLPWD is corrupted\n");
				cd_ret = 1;
			}
			free(to_free);
		}
		tmp = tmp->next;
	}
	return (cd_ret);
}

int	ft_cd(char **args, t_list *env)
{
	int		cd_ret;
	char	*to_free;

	if (!args[1])
		return (ft_home(env));
	else if (!ft_strncmp(args[1], "-", 2))
		return (ft_oldpwd(env));
	else
	{
		to_free = get_pwd();
		cd_ret = chdir(args[1]);
		if (!cd_ret)
		{
			update_env(NULL, to_free, env);
			free(to_free);
			to_free = get_pwd();
			update_env(to_free, NULL, env);
		}
		else
		{
			error_msg("ERROR: the given argument is not a valid directory\n");
			cd_ret = 1;
		}
		free(to_free);
	}
	return (cd_ret);
}
