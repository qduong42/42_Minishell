#include "minishell.h"

void	print_my_info(t_pipe *s_p)
{
	int	i;

	printf("SUB: %s\n", s_p->sub);
	printf("\n");
	i = 0;
	while (s_p->argv[i])
	{
		printf("ARGV[%d]: %s\n", i, s_p->argv[i]);
		i++;
	}
	printf("\n");
	printf("FD_IN: %d\n", s_p->fd_in);
	printf("FD_OUT: %d\n", s_p->fd_out);
	printf("HEREDOC: %s\n", s_p->hd);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_shell s;
	s.env = create_env_list(envp);

	while (69)
	{
		//print_list(s.env);
		s.input = readline(PROMPT);
		if (!s.input)
			break ;
		add_history(s.input);
		//error handling
		if (errors(s.input))
			continue ;
		init_all(&s);
		printf("Raw Input:%s\n", s.input);
		write(1, "\n", 1);
		env_solver(&s);
		printf("Expanded Input:%s\n", s.input);
		write(1, "\n", 1);
		free(s.input);
		pipe_split(&s);
		printf("Sub-pipes before red:\n");
		print_list(s.s_p, 1);
		write(1, "\n", 1);
		int_red(&s);
		printf("Sub-pipes after red:\n");
		print_list(s.s_p, 1);
		print_list(s.s_p, 2);
		space_split(&s);
		remove_quotes(&s);
		print_final_array(s.s_p);
		if (!ft_strncmp(s.input, "exit", ft_strlen(s.input)))
			exit (0);
	}
	return (0);
}
