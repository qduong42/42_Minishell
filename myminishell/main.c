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
		s.line = readline(PROMPT);
		add_history(s.line);
		env_solver(&s);
		// interpret(&s);
		if (!ft_strncmp(s.line, "exit", ft_strlen(s.line)))
			exit (0);
	}
	return (0);
}
