/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:42:23 by qduong            #+#    #+#             */
/*   Updated: 2022/07/27 21:40:57 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//-2 is used because -1 is used for open error
//but also errno will be set which we can see...
//s_p = sub_pipes
void	init_all(t_shell *s)
{
	// s->s_p = malloc(sizeof(t_pipe));
	s->s_p = NULL;
}

char	*copy_envp(char *envp)
{
	int		len;
	char	*copy;

	len = ft_strlen(envp);
	copy = malloc(len + 1);
	ft_strlcpy(copy, envp, len + 1);
	return (copy);
}

t_list	*create_env_list(char **envp)
{
	t_list	*a;
	int		i;

	a = ft_lstnew(copy_envp(envp[0]));
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&a, ft_lstnew(copy_envp(envp[i])));
		i++;
	}
	return (a);
}

int	variable_length(t_shell *s, int i)
{
	int	len;

	len = 0;
	while (s->input[i])
	{
		if (ft_isalnum(s->input[i]) || s->input[i] == '_')
			len++;
		else if (!(ft_isalnum(s->input[i])) && !(s->input[i] == '_'))
			break ;
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
	ft_strlcat(new_final, env, be_do + env_len);
	ft_strlcat(new_final, final + be_do + len, \
	ft_strlen(final) - len + env_len + 1);
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

int	env_len(char *env)
{
	int	x;

	x = 0;
	while (env[x])
	{
		if (env[x] == '=')
		{
			x++;
			break ;
		}
		x++;
	}
	return (x);
}

char	*find_env(t_shell *s, int i)
{
	int		len;
	t_list	*current;
	char	*tmp;
	int		e_len;

	len = variable_length(s, i);
	tmp = variable_name(&s->input[i], '=', len);
	current = (s->env);
	while (current->next != NULL)
	{
		if (ft_strncmp(tmp, current->content, len + 1) == 0)
			break ;
		current = current->next;
	}
	if (tmp)
		free(tmp);
	if (current->next == NULL)
		current->content = "" ;
	e_len = env_len(current->content);
	tmp = special_join(s->input, &(((char *)current->content)[e_len]), len, i);
	if (s->input)
		free(s->input);
	return (tmp);
}

int	digit_len(int a)
{
	int	i;

	i = 1;
	while (a)
	{
		a /= 10;
		i++;
	}
	return (i);
}

char	*replace_d_q(t_shell *s, int i)
{
	int		exit_status_len;
	char	*replaced_str;
	char	*itoa_res;

	itoa_res = ft_itoa(exit_status);
	exit_status_len = digit_len(exit_status);
	replaced_str = ft_calloc(1, exit_status_len + ft_strlen(s->input) - 2);
	ft_strlcpy(replaced_str, s->input, i);
	printf("replaced string1:%s\n", replaced_str);
	ft_strlcat(replaced_str, itoa_res, i + exit_status_len);
	printf("replaced string2:%s\n", replaced_str);
	ft_strlcat(replaced_str, &(s->input[i + 1]), i + \
	ft_strlen(&(s->input[i + 1])) + 1 + exit_status_len);
	printf("replaced string2:%s\n", replaced_str);
	if (itoa_res)
		free(itoa_res);
	if (s->env)
		free(s->input);
	return (replaced_str);
}

void	env_solver(t_shell *s)
{
	int		i;
	int		quote;
	char	*temp;

	i = 0;
	quote = 0;
	temp = ft_strtrim(s->input, " \t\n\v\f\r");
	if (s->input)
		free(s->input);
	s->input = temp;
	while (s->input[i])
	{
		if ((!quote || quote == D_Q) && s->input[i] == '$')
		{
			if (s->input[i + 1] == '?')
			{
				s->input = replace_d_q(s, i + 1);
				continue ;
			}
			s->input = find_env(s, i + 1);
			i -= 1;
		}
		else if ((s->input[i] == D_Q || s->input[i] == S_Q) && !quote)
			quote = s->input[i];
		else if (quote && (!(s->input[i]) || s->input[i] == quote))
			quote = 0;
		i++;
	}
}
