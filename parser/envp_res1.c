/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_res1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:42:23 by qduong            #+#    #+#             */
/*   Updated: 2022/08/03 09:49:07 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (!ft_strncmp(envp[i], "OLDPWD=", 7))
		{
			i++;
			continue ;
		}
		ft_lstadd_back(&a, ft_lstnew(copy_envp(envp[i])));
		i++;
	}
	return (a);
}

int	find_env(t_shell *s, int i)
{
	int		len;
	t_list	*current;
	char	*tmp;
	int		e_len;

	len = variable_length(s, i);
	tmp = variable_name(&s->input[i], '=', len);
	current = (s->env);
	while (current)
	{
		if (ft_strncmp(tmp, current->content, len + 1) == 0)
			break ;
		current = current->next;
	}
	free(tmp);
	if (current != NULL)
	{
	e_len = env_len(current->content);
	tmp = special_join(s->input, &(((char *)current->content)[e_len]), len, i);
	}
	else
		tmp = special_join(s->input, NULL, len, i);
	free(s->input);
	s->input = tmp;
	return (i - 2);
}

char	*replace_d_q(t_shell *s, int i)
{
	int		g_exit_status_len;
	char	*replaced_str;
	char	*itoa_res;

	itoa_res = ft_itoa(g_exit_status);
	g_exit_status_len = digit_len(g_exit_status);
	replaced_str = ft_calloc(1, g_exit_status_len + ft_strlen(s->input) - 2);
	ft_strlcpy(replaced_str, s->input, i);
	ft_strlcat(replaced_str, itoa_res, i + g_exit_status_len);
	ft_strlcat(replaced_str, &(s->input[i + 1]), i + \
	ft_strlen(&(s->input[i + 1])) + 1 + g_exit_status_len);
	if (itoa_res)
		free(itoa_res);
	if (s->env)
		free(s->input);
	return (replaced_str);
}

void	env_solver(t_shell *s, int i)
{
	int		quote;
	char	*temp;

	quote = 0;
	temp = ft_strtrim(s->input, " \t\n\v\f\r");
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
			i = find_env(s, i + 1);
		}
		else if ((s->input[i] == D_Q || s->input[i] == S_Q) && !quote)
			quote = s->input[i];
		else if (quote && (!(s->input[i]) || s->input[i] == quote))
			quote = 0;
		i++;
	}
}
