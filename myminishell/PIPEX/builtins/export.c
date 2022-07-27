/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:14:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 12:14:48 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free_all(splitters);
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
				ft_lstadd_front(env, ft_lstnew(args[i]));
			else
				error = 1;
			i++;
		}
	}
	return (error);
}
