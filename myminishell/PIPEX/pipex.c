/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/28 10:24:34 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fucked_cat(t_pipe **cmd)
{
	int	i;

	i = 0;
	while ((*cmd))
	{
		printf("FD_IN: %d\n", (*cmd)->fd_in);
		printf("HD: %s\n", (*cmd)->hd);
		printf("CMD: %s\n", (*cmd)->argv[0]);
		if ((*cmd)->fd_in <= 2 && !(*cmd)->hd && \
		!ft_strncmp((*cmd)->argv[i], "cat", 4))
			(*cmd) = (*cmd)->next;
		else
			break ;
	}
}

void	init_pipex(t_vars *vars, t_pipe *cmd, t_list **env_lst)
{
	vars->outfile = 66;
	vars->carry = 0;
	if (cmd)
	{
		if (cmd->fd_in > 2)
			vars->carry = cmd->fd_in;
	}
	vars->env = lst_to_strstr(*env_lst);
}

void	pipex(t_pipe *cmd, t_list **env_lst)
{
	t_vars		vars;

	// print_shit(cmd);
	fucked_cat(&cmd);
	init_pipex(&vars, cmd, env_lst);
	while (cmd)
	{
		if (while_stroke(&cmd, &vars, env_lst))
			continue ;
		assign_outfile(&vars, cmd);
		if (!vars.pid)
		{
			duping(&vars, cmd);
			if (is_buildin(cmd))
				exit(exec_buildin(cmd, env_lst));
			else if (execve(vars.path, cmd->argv, vars.env))
			{
				perror("execve()");
				exit(127);
			}
		}
		aftershave(&vars, &cmd);
	}
	close_free(&vars);
}
