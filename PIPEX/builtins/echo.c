/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:55:03 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/03 11:41:26 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * @brief checks the edge case of mixed options (flags)
 * 
 * @param flag 
 * @return int (bool)
 */
int	mixed_flag(char *flag)
{
	int	i;

	i = 0;
	while (flag[i])
	{
		if (flag[i] != '-' && flag[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief prints space separated, either with no-newline option or without
 * 
 * @param args the cmd and arguments/options
 * @return int exit status
 */
int	ft_echo(char **args)
{
	int	n_option;
	int	i;

	i = 1;
	n_option = 0;
	if (ft_strstrlen(args) > 1)
	{
		while (!ft_strncmp(args[i], "-n", 2) && !mixed_flag(args[i]))
		{
			n_option = 1;
			i++;
		}
		while (args[i] && args[i + 1])
		{
			ft_putstr_fd(args[i], 1);
			ft_putstr_fd(" ", 1);
			i++;
		}
		if (args[i])
			ft_putstr_fd(args[i], 1);
	}
	if (!n_option)
		ft_putstr_fd("\n", 1);
	return (0);
}
