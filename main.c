/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:27:05 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/04 16:18:20 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	show_prompt(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
		close_all();
	}
}

void	parser(t_shell *s)
{
	s->inv_fd_in = 0;
	env_solver(s, 0);
	pipe_split(s);
	int_red(s);
	space_split(s);
	remove_quotes(s);
}

int	ft_prompt(t_shell *s)
{
	s->s_p = NULL;
	s->input = readline(PROMPT);
	if (!s->input)
	{
		ft_putstr_fd("exit\n", 1);
		return (2);
	}
	if (!s->input[0])
	{
		free(s->input);
		return (1);
	}
	return (0);
}

void	loopyhoopy(t_shell *s)
{
	int	i;

	while (69)
	{
		i = ft_prompt(s);
		if (i == 2)
			break ;
		else if (i == 1)
			continue ;
		add_history(s->input);
		if (errors(s->input, &s->env))
			continue ;
		parser(s);
		free(s->input);
		here_fuck(s->s_p);
		pipex(s->s_p, &s->env);
		free_pipes(&s->s_p);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	s;

	(void)argc;
	(void)argv;
	s.env = create_env_list(envp);
	signal(SIGINT, show_prompt);
	signal(SIGQUIT, SIG_IGN);
	loopyhoopy(&s);
	free_me(&s);
	return (0);
}
