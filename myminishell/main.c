#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	t_shell s;
	s.env = create_env_list(envp);

	while (69)
	{
		s.input = readline(PROMPT);
		if (!s.input[0])
			continue ;
		add_history(s.input);
		if (errors(s.input))
			continue ;
		init_all(&s);
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
		pipex(s.s_p, &s.env);
	}
	return (0);
}
