#include "minishell.h"

int	errors(char *line)
{
	if (unclosed_quotes(line))
	{
		error_msg("Error: unenclosed quotes\n");
		return (1);
	}
	if (unexpected_newline(line))
	{
		error_msg("Error: unexpected newline\n");
		return (1);
	}
	if (single_dollar(line))
	{
		error_msg("Error: single dollar sign\n");
		return (1);
	}
	if (consecutive_specials(line))
	{
		error_msg("Error: consecutive special tokens\n");
		return (1);
	}
	return (0);
}

// int	main(void)
// {
// 	char	*line;
// 	while (1)
// 	{
// 		line = readline("minishell: ");
// 		errors(line);
// 		free(line);
// 	}
// 	return (0);
// }
