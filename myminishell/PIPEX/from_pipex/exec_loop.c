#include "../pipex.h"

int	while_stroke(t_pipe **cmd, t_vars *vars, t_list **env_lst)
{
	if (is_parent(*cmd))//BUILDINS IN THE PARENT (cmd, carry, env_lst)
	{
		if (vars->carry > 2)// -- carry freed in this stroke, execpt last iteration
			close(vars->carry);
		exit_status = exec_parent(*cmd, env_lst);
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
