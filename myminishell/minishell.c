#include "minishell.h"

void	print_list(t_list *list)
{
	t_list *temp;
	temp = list;
	int i = 0;
	while (temp->next)
	{
		printf("List:%d%s\n", i, temp->content);
		temp = temp->next;
		i++;
	}
}

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
	// print_list(a);
	return (a);
}

int	variable_length(t_shell *s, int i)
{
	int len = 0;
	while (s->input[i])
	{
		if (ft_isalnum(s->input[i]) || s->input[i] == '_')
	 	len++;
		else if (!(ft_isalnum(s->input[i])) || !(s->input[i] == '_'))
			break;
		i++;
	}
	return len;
}

void	find_env(t_shell *s, int i)
{
	int len = 0;
	printf("input in find:%s\n", &s->input[i]);
	len = variable_length(s, i);
	// while (s->input[i])
	// {
	// 	if (ft_isalnum(s->input[i]) || s->input[i] == '_')
	//  	y++;
	// 	else if (!(ft_isalnum(s->input[i])) || !(s->input[i] == '_'))
	// 		break;
	// 	i++;
	// 	printf("Y:%d\n", y);
	// }
	t_list *current;
	current = (s->env);
	print_list(current);
	while (current->next != NULL)
	{
		// printf("CURRENT CONTENT:%s\n", &s->input[i]);
		if (ft_strncmp(&s->input[i], current->content, len) == 0)
			break ;
		current = current->next;
	}
	// printf("env found:%s\n", current->content);
	return ;
}

void	env_solver(t_shell *s)
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
			printf("INPUT:%s\n", s->input);
			//write(1, "found $", 7);
			// printf("env|_solv:I:%dYO!\n", i);
			find_env(s, i + 1);
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