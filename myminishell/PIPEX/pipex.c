/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/24 22:00:16 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// carry -> member of vars.
// temp aka. local -> member of vars.
// clean up the vars struct.
// Thinking about where you need env as a list and where as a string.

void	while_stroke(t_pipe **cmd, t_vars *vars, t_list **env_lst);

int	pipex(t_pipe *cmd, t_list **env_lst)
{
	t_vars		vars;

	vars.outfile = 66; // INITALIZATION
	vars.carry = 0;//INFILE
	vars.env = lst_to_strstr(*env_lst); // FORMATING -- freed
	while (cmd)// Execution loop
	{
		// if (vars.outfile > 2)
		// 	close(vars.outfile);
		if (is_parent(cmd))//BUILDINS IN THE PARENT (cmd, carry, env_lst)
		{
			if (vars.carry > 2)// -- carry freed in this stroke, execpt last iteration
				close(vars.carry);
			exec_parent(cmd, env_lst);
			cmd = cmd->next;//PREPARING NEXT ITERATION
			continue ;
		}
		if (cmd->fd_in > 2)// file_precendence(vars, cmd);
		{
			if (vars.carry > 2) // --carry freed, before it is overwritten and before it is assigned
				close(vars.carry);
			vars.carry = cmd->fd_in;
		}
		// if (cmd->fd_out > 2)
		// {
		// 	if(vars.outfile > 2)
		// 		close(vars.outfile);
		// 	vars.outfile = cmd->fd_out;
		// }
		if (vars.outfile > 2)// CRUCIAL AFTER PIPE
		{
			close(vars.outfile);
			vars.outfile = 1;
		}
		pipe(vars.working);// Can be made implicit
		if (cmd->next) // A pipe has precendence over an outfile.
		{
			vars.outfile = vars.working[1];
		}
		vars.path = get_path(cmd->argv[0], vars.env);// --freed
		vars.pid = fork();// Can probably be made implicit
		if (!vars.pid)
		{
			dup2(vars.carry, 0); // dupping_and_buildin (vars, cmd);
			dup2(vars.outfile, 1);
			if (cmd->hd)
				dup2(create_hd(cmd->hd), 0); //-- unlinked
			if (is_buildin(cmd))
				exit(exec_buildin(cmd, env_lst)); // DOES NOT WORK AS INTENDED.
			else if (execve(vars.path, cmd->argv, vars.env))
			{
				perror("execve()");
				exit(127);
			}
		}
		sigignore(SIGINT); // child_exit(vars, cmd, ) ->local 'local'
		waitpid(vars.pid, &vars.tmp, 0);
		free(vars.path);
		signal(SIGINT, show_prompt);
		exit_status = WEXITSTATUS(vars.tmp);
		close(vars.working[1]); // CLOSE THE WRITING END OF THE PIPE
		if (cmd->hd)// DELETE THE HEREDOC
			unlink(".temp_doc");
		if (vars.carry > 2)// pipein_accendence(vars);
			close(vars.carry);
		vars.carry = vars.working[0];
		cmd = cmd->next;
	}
	if (vars.carry > 2)
		close(vars.carry);
	if (vars.outfile > 2) //is everything closed?
		close(vars.outfile);
	free_all(vars.env);
	return (0);
}
