/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:47:32 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 11:47:38 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	print_strstr(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i])
	{
		printf("STRSTR: %s\n", strstr[i]);
		i++;
	}
}

void	print_shit(t_pipe *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		printf("SHIT %s\n", cmd->argv[i]);
		i++;
	}
	printf("ALLAHUABK: %s\n", cmd->hd);
}
