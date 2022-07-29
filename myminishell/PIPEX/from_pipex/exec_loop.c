/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:54:07 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 15:30:55 by ljahn            ###   ########.fr       */
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
	pipe(vars->working);
	if (vars->outfile > 2)
		vars->outfile = 1;
	if (cmd->fd_out > 2)
		vars->outfile = cmd->fd_out;
	if (cmd->next)
		vars->outfile = vars->working[1];
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
	int	fd;

	dup2(vars->carry, 0);
	if (cmd->hd)
	{
		fd = create_hd(cmd->hd);
		dup2(fd, 0);
	}
	dup2(vars->outfile, 1);
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
	waitpid(vars->pid, &vars->tmp, 0);
	free(vars->path);
	signal(SIGINT, show_prompt);
	g_exit_status = WEXITSTATUS(vars->tmp);
	close(vars->working[1]);
	if ((*cmd)->hd)
		unlink(".temp_doc");
	if (vars->carry > 2)
		close(vars->carry);
	if ((*cmd)->fd_in > 2)
		vars->carry = (*cmd)->fd_in;
	vars->carry = vars->working[0];
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
}
