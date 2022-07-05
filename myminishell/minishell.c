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
	return (len);
}

char	*special_join(char *final, char *env, int len, int be_do)
{
	int		env_len;
	char	*new_final;
	
	env_len = ft_strlen(env);
	new_final = ft_calloc(1, ft_strlen(final) - len + env_len);
	ft_strlcpy(new_final, final, be_do);
	printf("final1%s\n", new_final);
	ft_strlcat(new_final, env, be_do + env_len);
	printf("final2%s\n", new_final);
	ft_strlcat(new_final, final + be_do + len, ft_strlen(final) - len + env_len + 1);
	printf("final3%s\n", new_final);
	return (new_final);
}

char	*variable_name(char const *s1, char s2, int len)
{
	char	*newstring;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	newstring = malloc(sizeof(char) * (len + 1 + 1));
	if (!newstring)
		return (NULL);
	while (ft_isalnum(s1[i]) || s1[i] == '_')
	{
		newstring[i] = s1[i];
		i++;
	}
	newstring[i] = s2;
	i++;
	newstring[i] = '\0';
	return (newstring);
}

char	*find_env(t_shell *s, int i, char *final)
{
	int len = 0;
	// printf("input in find:%s\n", &s->input[i]);
	len = variable_length(s, i);
	t_list *current;
	current = (s->env);
	//print_list(current);
	while (current->next != NULL)
	{
		printf("input%s\n", &s->input[i]);
		char *tmp2;
		tmp2 = variable_name(&s->input[i], '=', len);
		printf("tmp2:%s\n", tmp2);
		if (ft_strncmp(tmp2, current->content, len + 1) == 0 /* && ft_strchr(&s->input[i + len], '=') */)
		{
			free(tmp2);
			break ;
		}
		current = current->next;
	}
	char *env;
	env = current->content;
	int x;
	x = 0;
	while (env[x])
	{
		if (env[x] == '=')
		{
			x++;
			break;
		}
		x++;
	}
	// printf("LEN\t%dva_END_IN:%d\n", len, va_end_in - 1);
	printf("env found:%s\n", current->content);
	char *tmp;
	tmp = special_join(final, &env[x], len, i);
	free(final);
	printf("tmp:%s\n", tmp);
	//expand(s)
	//LENGTH OF NEW STRING = i - 1 + LENGTH OF EXPANDED VARIABLE + count from va_end_in to END
	return (tmp);
}

void	env_solver(t_shell *s)
{
	int	i;
	int	quote;
	char *temp;
	// int end_index;

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
			s->input = find_env(s, i + 1, s->input);
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