/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/17 20:42:01 by ljahn            ###   ########.fr       */
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

void	carry_over(t_vars *vars)
{
	if (vars->i > 2 && !vars->here_doc)//If it isn't the first command
		vars->carry[0] = vars->working[0];
	else if (vars->i > 3 && vars->here_doc) // If it isn't the first command
		vars->carry[0] = vars->working[0];
	pipe(vars->working);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_vars	vars;

// 	init_all(&vars, ac, av, env);
// 	while (vars.i < vars.last_cmd + 1)
// 	{
// 		carry_over(&vars);
// 		vars.spliters = ft_split(vars.av[vars.i], ' ');
// 		vars.path = get_path(vars.spliters[0], vars.env);
// 		vars.pid = fork();
// 		if (!vars.pid)
// 		{
// 			assign_stdfds(&vars);
// 			if (execve(vars.path, vars.spliters, vars.env))
// 			{
// 				perror("execve()");
// 				exit(-1);
// 			}
// 		}
// 		waitpid(vars.pid, NULL, 0);
// 		closing_freeing(&vars);
// 		vars.i++;
// 	}
// 	close(vars.working[0]);
// 	close(vars.outfile);
// }

int	pipex(t_pipe *lst)
{
	return (0);
}