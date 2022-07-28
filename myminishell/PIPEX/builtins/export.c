/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:14:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/28 11:36:39 by ljahn            ###   ########.fr       */
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
		ft_putstr_fd("\"\n", 1);
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
 * @brief Adds env variables
 * 
 * @param args 
 * @param env 
 * @return 1 indicates an invalid variable format
 */
int	ft_export(char **args, t_list **env)
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
				ft_lstadd_back(env, ft_lstnew(ft_strdup(args[i])));
			else
				error = 1;
			i++;
		}
	}
	return (error);
}
