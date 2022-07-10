#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	while (69)
	{
		t_shell s;
		s.env = create_env_list(envp);
		//print_list(s.env);
		s.input = readline(PROMPT);
		add_history(s.input);
		printf("Raw Input:%s\n", s.input);
		ft_putendl_fd("", 1);
		env_solver(&s);
		printf("Expanded Input:%s\n", s.input);
		ft_putendl_fd("", 1);
		pipe_split(&s);
		printf("Sub-pipes:\n");
		print_list(s.sub_pipes->sub);
		ft_putendl_fd("", 1);
		int_red(&s);
		// interpret(&s);
		if (!ft_strncmp(s.input, "exit", ft_strlen(s.input)))
			exit (0);
	}
	return (0);
}
