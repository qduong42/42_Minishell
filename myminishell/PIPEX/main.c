/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/18 14:29:45 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

// int	main(int ac, char **av, char **env)
// {
	// t_vars	vars;

	// init_all(&vars, ac, av, env);
	// while (vars.i < vars.last_cmd + 1)
	// {
	// 	carry_over(&vars);
	// 	vars.spliters = ft_split(vars.av[vars.i], ' ');
	// 	vars.path = get_path(vars.spliters[0], vars.env);
	// 	vars.pid = fork();
	// 	if (!vars.pid)
	// 	{
	// 		assign_stdfds(&vars);
	// 		if (execve(vars.path, vars.spliters, vars.env))
	// 		{
	// 			perror("execve()");
	// 			exit(-1);
	// 		}
	// 	}
	// 	waitpid(vars.pid, NULL, 0);
	// 	closing_freeing(&vars);
	// 	vars.i++;
	// }
	// close(vars.working[0]);
	// close(vars.outfile);
// }

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

int	pipex(t_pipe *cmd, char **env)
{
	t_vars	vars;
	int		carry;

	carry = 0;
	if (cmd->fd_in > 0)
		carry = cmd->fd_in;
	while (cmd)
	{
		pipe(vars.working);
		vars.path = get_path(cmd->argv[0], env);
		vars.pid = fork();
		if (!vars.pid)
		{
			dup2(carry, 0);
			if (!cmd->next)
				dup2(1, 1);
			else
				dup2(vars.working[1], 1);
			if (execve(vars.path, cmd->argv, env))
			{
				perror("execve()");
				exit(-1);
			}
		}
		waitpid(vars.pid, NULL, 0);
		if (carry)
			close(carry);
		if (cmd->fd_in < 0)
			carry = vars.working[0];
		else
		{
			close(vars.working[0]);
			carry = cmd->fd_in;
		}
		close(vars.working[1]);
		cmd = cmd->next;
	}
	if (carry)
		close(carry);
	close(vars.outfile);
	return (0);
}
