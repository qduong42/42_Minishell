/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:54:07 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/04 20:52:46 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * @brief kills all open files, executes non-piping parent buildin
 * 
 * @param cmd 
 * @param vars 
 * @param env_lst 
 * @return int 
 */
int	while_stroke(t_pipe **cmd, t_vars *vars, t_list **env_lst)
{
	if (is_parent(*cmd))
	{
		if (vars->carry > 2)
			close(vars->carry);
		g_exit_status = exec_parent(*cmd, env_lst);
		pipe(vars->working);
		close(vars->working[1]);
		vars->carry = vars->working[0];
		*cmd = (*cmd)->next;
		return (1);
	}
	return (0);
}

/**
 * @brief assigns vars->outfile, calls pipe(), get_path() and fork()
 * 
 * @param vars 
 * @param cmd 
 */
void	assign_outfile(t_vars *vars, t_pipe *cmd)
{
	if (vars->outfile > 2)
		close(vars->outfile);
	vars->outfile = 1;
	if (cmd->next)
		pipe(vars->working);
	if (cmd->next)
		vars->outfile = vars->working[1];
	if (cmd->fd_out > 2)
		vars->outfile = cmd->fd_out;
	vars->path = get_path(cmd->argv[0], vars->env);
	vars->pid = fork();
}

/**
 * @brief dups vars->carry/heredoc_fd on 0 and vars->outfile on 1
 * 
 * @param vars 
 * @param cmd 
 */
void	duping(t_vars *vars, t_pipe *cmd)
{
	dup2(vars->carry, 0);
	if (vars->carry > 2)
		close(vars->carry);
	if (cmd->hd)
	{
		dup2(cmd->hd_fd, 0);
		if (cmd->hd_fd > 2)
			close(cmd->hd_fd);
	}
	dup2(vars->outfile, 1);
	if (vars->outfile > 2)
		close(vars->outfile);
}

/**
 * @brief global exit_status, signals during child
 * process, deleting heredoc, reassigning carry
 * 
 * @param vars 
 * @param cmd 
 */
void	aftershave(t_vars *vars, t_pipe **cmd)
{
	signal(SIGINT, SIG_IGN);
	free(vars->path);
	if (vars->carry > 2)
		close(vars->carry);
	if ((*cmd)->fd_in > 2)
		vars->carry = (*cmd)->fd_in;
	if ((*cmd)->next)
	{
		close(vars->working[1]);
		vars->carry = vars->working[0];
	}
	*cmd = (*cmd)->next;
}

/**
 * @brief closes/frees stuff of the last iteration
 * 
 * @param vars 
 */
void	close_free(t_vars *vars)
{
	if (vars->carry > 2)
		close(vars->carry);
	if (vars->outfile > 2)
		close(vars->outfile);
	ft_free_all(vars->env);
	close_all();
	if (vars->pid != -1)
	{
		while (vars->pid > 0)
			vars->pid = wait(&vars->tmp);
		g_exit_status = WEXITSTATUS(vars->tmp);
	}
	signal(SIGINT, show_prompt);
}
