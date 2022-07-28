/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:55:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/28 11:07:17 by ljahn            ###   ########.fr       */
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
		printf("%s\n", (char *)env->content);
		env = env->next;
	}
	return (0);
}
