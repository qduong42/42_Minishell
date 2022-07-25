/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/25 09:36:57 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// The child buildins need to have the right exit value

int	while_stroke(t_pipe **cmd, t_vars *vars, t_list **env_lst)
{
	if (is_parent(*cmd))//BUILDINS IN THE PARENT (cmd, carry, env_lst)
	{
		if (vars->carry > 2)// -- carry freed in this stroke, execpt last iteration
			close(vars->carry);
		exec_parent(*cmd, env_lst);
		*cmd = (*cmd)->next;//PREPARING NEXT ITERATION
		return (1) ;
	}
	return (0);
}

void	assign_outfile(t_vars *vars, t_pipe *cmd)
{
	pipe(vars->working);
	if (vars->outfile > 2)// CRUCIAL AFTER PIPE
	{
		close(vars->outfile);
		vars->outfile = 1;
	}
	if (cmd->fd_out > 2)
		vars->outfile = cmd->fd_out;
	if (cmd->next) // A pipe has precendence over an outfile.
		vars->outfile = vars->working[1];
	vars->path = get_path(cmd->argv[0], vars->env);// Impilicit
	vars->pid = fork();
}

void	duping(t_vars *vars, t_pipe *cmd)
{
	dup2(vars->carry, 0); // dupping_and_buildin (vars, cmd);
	if (cmd->hd)
		dup2(create_hd(cmd->hd), 0);
	dup2(vars->outfile, 1);
}

void	aftershave(t_vars *vars, t_pipe **cmd)
{
	sigignore(SIGINT); // child_exit(vars, cmd, ) ->local 'local'
	waitpid(vars->pid, &vars->tmp, 0);
	free(vars->path);
	signal(SIGINT, show_prompt);
	exit_status = WEXITSTATUS(vars->tmp);
	close(vars->working[1]); // CLOSE THE WRITING END OF THE PIPE
	if ((*cmd)->hd)// DELETE THE HEREDOC
		unlink(".temp_doc");
	if (vars->carry > 2)// pipein_accendence(vars);
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

void	init_pipex(t_vars *vars, t_pipe *cmd, t_list **env_lst)
{
	vars->outfile = 66; // INITALIZATION
	vars->carry = 0;//INFILE
	if (cmd->fd_in > 2)
		vars->carry = cmd->fd_in;
	vars->env = lst_to_strstr(*env_lst); // FORMATING -- freed
}

void	pipex(t_pipe *cmd, t_list **env_lst)
{
	t_vars		vars;

	init_pipex(&vars, cmd, env_lst);
	while (cmd)// Execution loop
	{
		if (while_stroke(&cmd, &vars, env_lst))
			continue ;
		assign_outfile(&vars, cmd);
		if (!vars.pid)
		{
			duping(&vars, cmd);
			if (is_buildin(cmd))
				exit(exec_buildin(cmd, env_lst)); // DOES NOT WORK AS INTENDED.
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
