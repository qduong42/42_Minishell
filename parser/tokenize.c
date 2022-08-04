/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:23:48 by qduong            #+#    #+#             */
/*   Updated: 2022/08/04 14:56:03 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len(char *str, int quote, int len, int i)
{
	while (str[i])
	{
		if (str[i] == S_Q || str[i] == D_Q)
		{
			quote = str[i];
			if (delete_quote(str, i, quote))
				i++;
			else
			{
				i++;
				len++;
			}
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	copystuff(char *temp, char *src, int *i, int *y)
{
	temp[*y] = src[*i];
	(*y)++;
	(*i)++;
}

char	*strcpywithout(char	*src, int len, int i, int y)
{
	char	*temp2;
	int		quote;

	quote = 0;
	temp2 = ft_calloc(1, len + 1);
	while (src[i])
	{
		if (src[i] == S_Q || src[i] == D_Q)
		{
			quote = src[i];
			if (delete_quote(src, i, quote))
				i++;
			else
				copystuff(temp2, src, &i, &y);
		}
		else
			copystuff(temp2, src, &i, &y);
	}
	temp2[y] = '\0';
	return (temp2);
}

void	remove_quotes(t_shell	*s)
{
	t_pipe	*temp;
	int		i;
	char	*temp2;
	int		len;

	temp = s->s_p;
	len = 0;
	while (temp)
	{
		i = 0;
		while (temp->argv[i])
		{
			len = get_len(temp->argv[i], 0, 0, 0);
			temp2 = strcpywithout(temp->argv[i], len, 0, 0);
			free(temp->argv[i]);
			temp->argv[i] = temp2;
			i++;
		}
		temp = temp->next;
	}
}
