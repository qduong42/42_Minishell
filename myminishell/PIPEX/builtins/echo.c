/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:55:03 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/28 11:05:52 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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
		while (!ft_strncmp(args[i], "-n", 2))
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
