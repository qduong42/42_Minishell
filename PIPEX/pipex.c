/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/04 19:34:12 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief a saver exit
 * 
 * @param i 
 */
void	exit_s(int i)
{
	close_all();
	exit(i);
}

/**
 * @brief goes to the next cmd if cat-cmd is blocking
 * 
 * @param cmd
 */
void	fucked_cat(t_pipe **cmd)
{
	while ((*cmd))
	{
		if (((*cmd)->main->inv_fd_in == 1 && !(*cmd)->hd && (*cmd)->argv[0] \
		&& !ft_strncmp((*cmd)->argv[0], "cat", 4)))
		{
			(*cmd) = (*cmd)->next;
		}
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
	vars->pid = -1;
	vars->outfile = 66;
	vars->carry = 0;
	if (*cmd)
	{
		if ((*cmd)->fd_in > 2)
			vars->carry = (*cmd)->fd_in;
		if ((*cmd)->hd)
			vars->carry = (*cmd)->hd_fd;
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
				exit_s(exec_buildin(cmd, env_lst, &vars));
			else if (access(cmd->argv[0], F_OK) && \
			react_if_ncontained(path_error, "PATH=", env_lst))
				exit_s(1);
			else if (execve(vars.path, cmd->argv, vars.env))
			{
				perror("execve()");
				exit_s(127);
			}
		}
		aftershave(&vars, &cmd);
	}
	close_free(&vars);
}
