#include "../pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	free_splitters(char **splitters)
{
	int	i;

	i = 0;
	while (splitters[i])
	{
		free(splitters[i]);
		i++;
	}
	free(splitters);
}

void	sort_strstr(char **strstr)
{
	char	*tmp;
	int		i;
	int		ordered;

	ordered = 0;
	while (ordered == 0)
	{
		i = 0;
		ordered = 1;
		while (strstr[i] && strstr[i + 1])
		{
			if (ft_strcmp(strstr[i], strstr[i + 1]) > 0)
			{
				tmp = strstr[i];
				strstr[i] = strstr[i + 1];
				strstr[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
	}
}

void	print_sorted_ev(t_list *env)
{
	char	**splitters;
	int		i;

	splitters = lst_to_strstr(env);
	sort_strstr(splitters);
	i = 0;
	while (splitters[i])
	{
		printf("%s\n", splitters[i]);
		i++;
	}
	free_splitters(splitters);
}

int	valid_env(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
	{
		if (!var[i])
			return (0);
		if (!((var[i] >= 'A' && var[i] <= 'Z') || var[i] == '_'))
			return (0);
		i++;
	}
	i++;
	if (!var[i])
		return (0);
	return (1);
}

/**
 * @brief Adds env variables
 * 
 * @param args 
 * @param env 
 * @return 1 indicates an invalid variable format
 */
int	export(char **args, t_list **env)
{
	int	i;
	int	error;

	error = 0;
	if (!args[1])
		print_sorted_ev(*env);
	else
	{
		i = 1;
		while (args[i])
		{
			if (valid_env(args[i]))
				ft_lstadd_front(env, ft_lstnew(args[i]));
			else
				error = 1;
			i++;
		}
	}
	return (error);
}
