#include "minishell.h"

// LEXER
// int	is_special(int a)
// {
// 	if (a == PIPE)
// 		return (1);
// 	else if (a == IN)
// 		return (2);
// 	else if (a == OUT)
// 		return (3);
// 	else if (a == DOL)
// 		return (4);
// 	else
// 		return (0);
// }

void	pipe_split(t_shell *s)
{
	int	i;
	int	quote;
	int start;

	i = 0;
	start = 0;
	char *token;
	printf("input%s\n", s->input);
	while (s->input[i]!= '\0')
	{
		if (s->input[i] == PIPE && !quote)
		{
			token =ft_substr(s->input, start, i - start);
			printf("TOKEN:%s\n", token);
			start = i + 1;
		}
		else if (s->input[i] == '\'' || s->input[i] == '"')
			quote = 1;
		else if (quote && (!(s->input[i]) || s->input[i] == quote))
		{
			quote = 0;
		}
		i++;
	}
	if (!s->input)
	{
	token =ft_substr(s->input, start, i - start);
	printf("TOKEN:%s\n", token);
	}
}

//add_history functionality is built in, so further work required.