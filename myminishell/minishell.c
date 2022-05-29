#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	if (!ft_strncmp(argv[0], "./minishell", ft_strlen(argv[0])))
	{
	char	*line;
	while (69)
	{
		line = readline(PROMPT);
		add_history(line); // add_history functionality is built in, so further work required.
		if (!ft_strncmp(line, "exit", ft_strlen(line)))
			exit (0);
	}
	return (0);
	}
	return (0);
}
