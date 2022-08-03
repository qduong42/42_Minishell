/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:14:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/02 12:07:47 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * @brief fancy print of env variables
 * 
 * @param env 
 */
void	print_sorted_ev(t_list *env)
{
	char	**splitters;
	int		i;
	int		j;

	splitters = lst_to_strstr(env);
	ft_sortstrstr(splitters);
	i = 0;
	while (splitters[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (splitters[i][j])
		{
			ft_putchar_fd(splitters[i][j], 1);
			if (splitters[i][j] == '=')
				ft_putchar_fd('\"', 1);
			j++;
		}
		if (valid_env(splitters[i]))
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	ft_free_all(splitters);
}

/**
 * @brief Checks for the format of an env variable
 * 
 * @param var the string to test
 * @return int a boolean (; 1 means is the right format)
 */
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
 * @brief duplicates the string till it hits the delimiter
 * 
 * @param str 
 * @param till 
 * @return char* (allocated)
 */
static char	*dup_till(char *str, char till)
{
	int		i;
	char	*ret;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != till && str[i])
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

/**
 * @brief checks if arg is valid (setting error),
 * unsets if allready existant, and adds to env
 * 
 * @param arg what should be added
 * @param error error, if the format of arg is invalid
 * @param env 
 */
void	perform_action(char *arg, int *error, t_list **env)
{
	char	*to_free;

	if (valid_env(arg))
	{
		to_free = dup_till(arg, '=');
		unset_one(env, to_free);
		free(to_free);
		ft_lstadd_back(env, ft_lstnew(ft_strdup(arg)));
	}
	else
		*error = 1;
}

/**
 * @brief Adds env variables
 * 
 * @param args 
 * @param env 
 * @return 1 indicates an invalid variable format
 */
int	ft_export(char **args, t_list **env)
{
	int		i;
	int		error;

	error = 0;
	if (!args[1])
		print_sorted_ev(*env);
	else
	{
		i = 1;
		while (args[i])
		{
			perform_action(args[i], &error, env);
			i++;
		}
	}
	return (error);
}
