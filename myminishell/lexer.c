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
	quote = 0;
	char *token;
	char *temp;
	s->sub_pipes = NULL;
	while (1)
	{
		if ((s->input[i] == PIPE && !quote) || s->input[i] == '\0')
		{
			token = ft_substr(s->input, start, i - start);
			temp = ft_strtrim(token, " ");
			free(token);
			token = temp;
			ft_lstadd_back(&(s->sub_pipes), ft_lstnew(token));
			start = i + 1;
			if (s->input[i] == '\0')
				break ;
		}
		else if ((s->input[i] == '\'' || s->input[i] == '"') && !quote)
			quote = s->input[i];
		else if (quote && (!(s->input[i]) || s->input[i] == quote))
			quote = 0;
		i++;
	}
	print_list(s->sub_pipes);
}

//add_history functionality is built in, so further work required.