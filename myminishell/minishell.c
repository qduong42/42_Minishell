#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*line;

	while (69)
	{
		line = readline(PROMPT);
	}
	return (0);
}