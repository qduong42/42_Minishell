#include "minishell.h"

int exit_status = 0;

void	show_prompt(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
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

void	free_pipes(t_pipe *sp)
{
	t_pipe	*pipe;

	pipe = sp;
	while (pipe)
	{
		int	i = 0;
		while (pipe->argv[i])
		{
			free(pipe->argv[i]);
			i++;
		}
		pipe = pipe->next;
	}
	if (sp)
		free(sp);
}

void	free_me(t_shell *s)
{
	if (s->input)
		free(s->input);
	free_env(s->env);
	free_pipes(s->s_p);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_shell s;

	s.env = create_env_list(envp);
	signal(SIGINT, show_prompt);
	sigignore(SIGABRT);
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
		// if (s.input)
			free(s.input);
		pipex(s.s_p, &s.env);
		// free_pipes(s.s_p);
		printf("EXIT STATUS: %d\n", exit_status);
	}
	// free_me(&s);
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