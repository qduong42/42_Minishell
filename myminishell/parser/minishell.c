#include "../minishell.h"

//-2 is used because -1 is used for open error but also errno will be set which we can see...
//s_p = sub_pipes
void	init_all(t_shell *s)
{
	s->s_p = malloc(sizeof(t_pipe));
	s->s_p = NULL;
}

char 	*copy_envp(char *envp)
{
	int		len;
	char	*copy;

	len = ft_strlen(envp);
	copy = malloc(len + 1);
	ft_strlcpy(copy, envp, len + 1);
	return (copy);
}

t_list *create_env_list(char **envp)
{
	t_list *a;
	int	i;

	a = ft_lstnew(copy_envp(envp[0]));
	i = 1;
	while (envp[i])
	{

		ft_lstadd_back(&a, ft_lstnew(copy_envp(envp[i])));
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
		else if (!(ft_isalnum(s->input[i])) && !(s->input[i] == '_'))
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
	// printf("final1%s\n", new_final);
	ft_strlcat(new_final, env, be_do + env_len);
	// printf("final2%s\n", new_final);
	ft_strlcat(new_final, final + be_do + len, ft_strlen(final) - len + env_len + 1);
	// printf("final3%s\n", new_final);
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

char	*find_env(t_shell *s, int i)
{
	int len = 0;
	// printf("input in find:%s\n", &s->input[i]);
	len = variable_length(s, i);
	t_list *current;
	current = (s->env);
	//print_list(current);
	while (current->next != NULL)
	{
		// printf("input%s\n", &s->input[i]);
		char *tmp2;
		tmp2 = variable_name(&s->input[i], '=', len);
		// printf("tmp2:%s\n", tmp2);
		if (ft_strncmp(tmp2, current->content, len + 1) == 0 /* && ft_strchr(&s->input[i + len], '=') */)
		{
			free(tmp2);
			break ;
		}
		current = current->next;
	}
	char *env;
	env = current->content;
	if (current->next == NULL)
		env = "" ;
	// printf("env:%s\n", env);
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
	// printf("env found:%s\n", current->content);
	char *tmp;
	tmp = special_join(s->input, &env[x], len, i);
	free(s->input);
	// printf("Expanded:%s\n", tmp);
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
		if ((!quote || quote == D_Q) && s->input[i] == '$')
		{
			//write(1, "found $", 7);
			// printf("env|_solv:I:%dYO!\n", i);
			s->input = find_env(s, i + 1);
			i -= 1;
		}
		else if ((s->input[i] == D_Q || s->input[i] == S_Q) && !quote)
		{
			quote = s->input[i];
			// printf("FOUND\n");
			// printf("quote:%c\n", quote);
		}
		else if (quote && (!(s->input[i]) || s->input[i] == quote))
		{
			// printf("Found closing bracket:%c\n", quote);
			quote = 0;
		}
		i++;
	}
	return ;
}