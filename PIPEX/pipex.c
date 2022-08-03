/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/01 21:03:38 by qduong           ###   ########.fr       */
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
		if (((*cmd)->fd_in == -1 && !(*cmd)->hd && (*cmd)->argv[0] \
		&& !ft_strncmp((*cmd)->argv[0], "cat", 4)))
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
void	init_pipex(t_vars *vars, t_pipe **cmd, t_list **env_lst)
{
	fucked_cat(cmd);
	vars->outfile = 66;
	vars->carry = 0;
	if (*cmd)
	{
		if ((*cmd)->fd_in > 2)
			vars->carry = (*cmd)->fd_in;
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

	init_pipex(&vars, &cmd, env_lst);
	while (cmd && cmd->argv[0])
	{
		if (while_stroke(&cmd, &vars, env_lst))
			continue ;
		assign_outfile(&vars, cmd);
		if (!vars.pid)
		{
			duping(&vars, cmd);
			if (is_buildin(cmd))
				exit(exec_buildin(cmd, env_lst));
			else if (access(cmd->argv[0], F_OK) && \
			react_if_ncontained(path_error, "PATH=", env_lst))
				exit (1);
			else if (execve(vars.path, cmd->argv, vars.env))
			{
				perror("execve()");
				exit(127);
			}
		}
		aftershave(&vars, &cmd);
	}
	close_free(&vars, cmd);
}