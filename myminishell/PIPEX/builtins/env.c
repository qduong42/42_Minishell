/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:55:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 09:49:30 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * @brief prints all the env-variables
 * 
 * @param cmd the arguments (should be empty)
 * @param env the linked-list to iterate
 * @return int exit status
 */
int	ft_env(t_pipe *cmd, t_list *env)
{
	if (cmd->argv[1] != NULL)
		return (127);
	while (env)
	{
		env = env->next;
	}
	return (0);
}
