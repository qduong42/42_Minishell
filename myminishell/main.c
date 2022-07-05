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
		env_solver(&s);
		pipe_split(&s);
		// interpret(&s);
		if (!ft_strncmp(s.input, "exit", ft_strlen(s.input)))
			exit (0);
	}
	return (0);
}
