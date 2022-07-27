/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:24:35 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 12:24:36 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	env_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!((name[i] >= 'A' && name[i] <= 'Z') || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	unset_one(t_list **env, char *one)
{
	t_list	*tmp;
	t_list	*dragging;

	tmp = *env;
	dragging = NULL;
	while (1)
	{
		if (!tmp)
			break ;
		if (!ft_strncmp(tmp->content, one, ft_strlen(one)))
		{
			if (!dragging)
				*env = tmp->next;
			else
				dragging->next = tmp->next;
			free(tmp->content);
			free(tmp);
			break ;
		}
		dragging = tmp;
		tmp = tmp->next;
	}
}

int	unset(char **args, t_list **env)
{
	int		i;

	if (!args[1])
	{
		error_msg("Unset: invalid number of arguments\n");
		return (1);
	}
	else
	{
		i = 1;
		while (args[i])
		{
			if (!env_name(args[i]))
			{
				error_msg("Unset: invalid env variable name\n");
				return (1);
			}
			unset_one(env, args[i]);
			i++;
		}
	}
	return (0);
}
