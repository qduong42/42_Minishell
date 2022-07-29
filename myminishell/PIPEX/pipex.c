/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 14:32:31 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief goes to the next cmd if cat-cmd is blocking
 * 
 * @param cmd
 */
void	fucked_cat(t_pipe **cmd)
{
	while ((*cmd))
	{
		if ((*cmd)->fd_in <= 2 && !(*cmd)->hd && \
		!ft_strncmp((*cmd)->argv[0], "cat", 4) && \
		!(*cmd)->argv[1])
			(*cmd) = (*cmd)->next;
		else
			break ;
	}
}

/**
 * @brief the input for the first read (and strstr format for env)
 * 
 * @param vars A struct holding all for execution
 * @param cmd A struct holding all for execution
 * @param env_lst 
 */
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

/**
 * @brief executes cmd with right i/o
 * 
 * @param cmd a struct containing args and i/o infos
 * @param env_lst the env as a lst-data-structure
 */
void	pipex(t_pipe *cmd, t_list **env_lst)
{
	t_vars		vars;

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
			else if (react_if_ncontained(path_error, "PATH=", env_lst))
				exit (1);
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
