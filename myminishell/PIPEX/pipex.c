/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/20 16:46:54 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int exit_status = 0;

void	assign_stdfds(t_vars *vars)
{
	if (vars->i > FIRST_NOT_HERE_DOC && !vars->here_doc)// If not first, read from carry
		dup2(vars->carry[0], 0);
	if (vars->i > FIRST_HERE_DOC && vars->here_doc)//""""
		dup2(vars->carry[0], 0);
	if (vars->i != vars->last_cmd)//If not last command write to working pipe
		dup2(vars->working[1], 1);
	else if (vars->is_outfile)//If last command, write to whatever outfile
		dup2(vars->outfile, 1);
	else
		dup2(1, 1);
}

void	closing_freeing(t_vars *vars)
{
	close(vars->working[1]);
	if (vars->i > FIRST_NOT_HERE_DOC && !vars->here_doc)
		close(vars->carry[0]);
	if (vars->i > FIRST_HERE_DOC && vars->here_doc)
		close(vars->carry[0]);
	if (vars->i == FIRST_HERE_DOC && vars->here_doc)
	{
		close(vars->temp_doc);
		unlink(".temp_doc");
	}
	if (ft_strncmp(vars->path, vars->spliters[0], 69))
		free(vars->path);
	if (vars->i == FIRST_NOT_HERE_DOC && !vars->here_doc)
		close(vars->infile);
	free_all(vars->spliters);
}

void	print_strstr(char **strstr)
{
	int	i;

	i = 0;
	while(strstr[i])
	{
		printf("STRSTR: %s\n", strstr[i]);
		i++;
	}
}

int	buildin(t_pipe *cmd, t_list **env_lst)
{
	if (!ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0])))
		exit_status = ft_echo(cmd->argv);
	else if (!ft_strncmp(cmd->argv[0], "cd", ft_strlen(cmd->argv[0])))
		exit_status = ft_cd(cmd->argv, *env_lst);
	else if (!ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0])))
		exit_status = pwd();
	else if (!ft_strncmp(cmd->argv[0], "export", ft_strlen(cmd->argv[0])))
		exit_status = ft_export(cmd->argv, env_lst);
	else if (!ft_strncmp(cmd->argv[0], "unset", ft_strlen(cmd->argv[0])))
		exit_status = unset(cmd->argv, env_lst);
	else if (!ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0])))
		exit_status = ft_env(*env_lst);
	else if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0])))
		exit(0);
	else
		return (0);
	return (1);
}

char	**lst_to_strstr(t_list *env)
{
	char	**ret;
	int		i;
	t_list	*tmp;

	ret = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	i = 0;
	tmp = env;
	while (1)
	{
		if (i == ft_lstsize(env))
		{
			ret[i] = NULL;
			return (ret);
		}
		ret[i] = malloc(sizeof(char) * (ft_strlen(tmp->content) + 1));
		ft_strlcpy(ret[i], tmp->content, ft_strlen(tmp->content) + 1);
		i++;
		tmp = tmp->next;
	}
	return (NULL);
}

int	pipex(t_pipe *cmd, t_list **env_lst)
{
	t_vars		vars;
	int			local;
	int			carry;
	char		**env;

	vars.outfile = 1;
	env = lst_to_strstr(*env_lst);
	carry = 0;
	printf("FD_IN: %d\n", cmd->fd_in);
	if (cmd->fd_in > 0)
		carry = cmd->fd_in;
	while (cmd)
	{
		if (cmd->fd_out > 0)
			vars.outfile = cmd->fd_out;
		if (buildin(cmd, env_lst))
		{
			cmd = cmd->next;
			continue ;
		}
		pipe(vars.working);
		vars.path = get_path(cmd->argv[0], env);
		vars.pid = fork();
		if (!vars.pid)
		{
			dup2(carry, 0);
			if (!cmd->next)
				dup2(vars.outfile, 1);
			else
				dup2(vars.working[1], 1);
			if (execve(vars.path, cmd->argv, env))
			{
				perror("execve()");
				exit(-1);
			}
		}
		waitpid(vars.pid, &local, 0);
		if (carry)
			close(carry);
		if (cmd->next)
		{
			if ((cmd->next)->fd_in < 0)// Look if carry should be fd or pipe content
				carry = vars.working[0];
			else
			{
				close(vars.working[0]);
				carry = cmd->fd_in;
			}
		}
		else
			close(vars.working[0]); //don't forget to close the pipe if that's it.
		close(vars.working[1]);
		cmd = cmd->next;
	}
	if (carry)
		close(carry);
	if (vars.outfile != 1)
		close(vars.outfile);
	exit_status = WEXITSTATUS(local);
	if (exit_status == 255)
		exit_status = 127;
	return (0);
}
