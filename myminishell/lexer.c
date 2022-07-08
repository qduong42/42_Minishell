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

void	pipe_handle(t_shell *s, int *start, int i)
{
	char *token;
	char *temp;
	token = ft_substr(s->input, *start, i - *start);
	temp = ft_strtrim(token, " ");
	free(token);
	token = temp;
	ft_lstadd_back(&(s->sub_pipes->sub), ft_lstnew(token));
	*start = i + 1;
}

// void	int_red(t_shell *s)
// {
// 	t_list *temp;
// 	temp = s->sub_pipes->sub;
// 	while (temp->next != NULL)
// 	{
// 		temp = temp->next;
// 	}
// 	// int i = 0;
// 	char *string;
// 	// int start = 0;
// 	string = temp->content;
// 	printf("string:%s\n", string);
	// while (string[i])
	// {
	// 	if (string[i] == '<' && string[i + 1])
	// 	{
	// 		i++;
	// 		if (string[i] == '<')
	// 		{
	// 			hdoc(s, &i);
	// 		}
	// 	}
	// 	else if (string[i] == '>' && string[i + 1])
	// 	{
	// 		i++;
	// 		if (string[i] == '>')
	// 		{
	// 			append(s, &i);
	// 		}
	// 	}
	// 	i++;
	// }
// }

void	pipe_split(t_shell *s)
{
	int	i;
	int	quote;
	int start;

	i = 0;
	start = 0;
	quote = 0;
	s->sub_pipes = malloc(sizeof(t_pipe));
	s->sub_pipes->sub = NULL;
	while (1)
	{
		if ((s->input[i] == PIPE && !quote) || s->input[i] == '\0')
		{
			pipe_handle(s, &start, i);
			if (s->input[i] == '\0')
				break ;
		}
		else if ((s->input[i] == '\'' || s->input[i] == '"') && !quote)
			quote = s->input[i];
		else if (quote && (!(s->input[i]) || s->input[i] == quote))
			quote = 0;
		i++;
	}
}

//add_history functionality is built in, so further work required.