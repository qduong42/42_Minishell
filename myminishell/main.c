/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthien-h <cthien-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:27:05 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 20:22:40 by cthien-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	}
}
void	free_env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (temp)
	{
		free(temp->content);
		temp = temp->next;
	}
}

void	free_pipes(t_pipe **sp)
{
	t_pipe	*pipe;
	t_pipe	*tmp;
	int		i;

	if (!sp) return;
	pipe = *sp;
	while (pipe)
	{
		if (pipe->sub)
			free(pipe->sub);
		if (pipe->hd)
			free(pipe->hd);
		i = 0;
		while (pipe->argv[i])
		{
			free(pipe->argv[i]);
			i++;
		}
		free(pipe->argv);
		tmp = pipe->next;
		free(pipe);
		pipe = tmp;
	}
}

void	free_me(t_shell *s)
{
	if (s->input)
		free(s->input);
	ft_lstclear(&s->env, free);
	// free_env(s->env);
	free_pipes(&(s->s_p));
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_shell s;

	s.env = create_env_list(envp);
	signal(SIGINT, show_prompt);
	signal(SIGABRT, SIG_IGN);
	// sigignore(SIGABRT);
	init_all(&s);
	while (69)
	{
		s.input = readline(PROMPT);
		if (!s.input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		add_history(s.input);
		if (errors(s.input))
			continue ;
		printf("Raw Input:%s\n", s.input);
		write(1, "\n", 1);
		env_solver(&s);
		printf("Expanded Input:%s\n", s.input);
		write(1, "\n", 1);
		pipe_split(&s);
		// printf("Sub-pipes before red:\n");
		// write(1, "\n", 1);
		int_red(&s);
		// printf("Sub-pipes after red:\n");
		space_split(&s);
		remove_quotes(&s);
		if (!ft_strncmp(s.input, "exit", ft_strlen(s.input)))
			exit (0);
		if (s.input)
			free(s.input);
		pipex(s.s_p, &s.env);
		free_pipes(&(s.s_p));
		s.s_p = NULL;
		printf("EXIT STATUS: %d\n", exit_status);
	}
	free_me(&s);
	return (0);
}

// int	main(void)
// {
// 	struct stat buf;

// 	lstat("hundemon2", &buf);
// 	// shift_that(buf->st_mode);
// 	if (S_ISLNK(buf.st_mode))
// 		printf("YOU FAGOT IT'S A LINK\n");
// 	else
// 		printf("JUST KIDDING\n");
// 	return (0);
// }
