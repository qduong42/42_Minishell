#include "minishell.h"

t_list *create_env_list(char **envp)
{
	t_list *a;
	int	i;

	a = ft_lstnew(envp[0]);
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&a, ft_lstnew(envp[i]));
		i++;
	}
	return (a);
}

void	env_solver(t_shell* s)
{
	int	i;
	int	quote;
	char *temp;

	i = 0;
	quote = 0;
	temp = ft_strtrim(s->input, " \t\n\v\f\r");
	free(s->input);
	s->input = temp;
	while (s->input[i])
	{
		if ((!quote || quote == '"') && s->input[i] == '$')
		{
			write(1, "found $", 7);
			//find_env(s);
		}
		else if ((s->input[i] == '"' || s->input[i] == '\'') && !quote)
		{
			quote = s->input[i];
			printf("quote:%c\n", quote);
		}
		else if (quote && (!(s->input[i]) || s->input[i] == quote))
		{
			printf("Found closing bracket:%c\n", quote);
			quote = 0;
		}
		i++;
	}
	return ;
}

// void	print_list(t_list *to_print)
// {
// 	t_list *current;
// 	current = to_print;
// 	while (current->next != NULL)
// 	{
// 		printf("%s\n", current->content);
// 		current = current->next;
// 	}
// 	printf("%s\n", current->content);
// }

//LEXER
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

// void	interpret(t_shell *s)
// {
// 	int i;

// 	i = 0;
// 	ft_putstr_fd(s->input, 1);
// 	while (s->input[i]!= '\0')
// 	{
// 		s->input = ft_strtrim(s->input, " \v\t\f\r\n");
// 		if (is_special(s->input[i]) == 0) // not pipe or in or out or dollar sign
// 			while 
// 	}
// }

// add_history functionality is built in, so further work required.`