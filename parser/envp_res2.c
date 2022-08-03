/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_res2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:59:03 by qduong            #+#    #+#             */
/*   Updated: 2022/08/03 09:51:05 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (env)
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
