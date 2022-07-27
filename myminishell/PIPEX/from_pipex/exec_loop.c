/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:54:07 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 11:54:32 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	while_stroke(t_pipe **cmd, t_vars *vars, t_list **env_lst)
{
	if (is_parent(*cmd))
	{
		if (vars->carry > 2)
			close(vars->carry);
		exit_status = exec_parent(*cmd, env_lst);
		*cmd = (*cmd)->next;
		return (1);
	}
	return (0);
}

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

void	duping(t_vars *vars, t_pipe *cmd)
{
	dup2(vars->carry, 0);
	if (cmd->hd)
		dup2(create_hd(cmd->hd), 0);
	dup2(vars->outfile, 1);
}

void	aftershave(t_vars *vars, t_pipe **cmd)
{
	sigignore(SIGINT);
	waitpid(vars->pid, &vars->tmp, 0);
	free(vars->path);
	signal(SIGINT, show_prompt);
	exit_status = WEXITSTATUS(vars->tmp);
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

void	close_free(t_vars *vars)
{
	if (vars->carry > 2)
		close(vars->carry);
	if (vars->outfile > 2)
		close(vars->outfile);
	free_all(vars->env);
}
