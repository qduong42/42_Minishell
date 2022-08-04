/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:23:48 by qduong            #+#    #+#             */
/*   Updated: 2022/08/04 14:26:55 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len(char *str)
{
	int	len;
	int	i;
	int	quote;

	quote = 0;
	len = 0;
	i = 0;
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

char	*strcpywithout(char	*src, int len)
{
	char	*temp2;
	int		i;
	int		y;
	int		quote;

	quote = 0;
	i = 0;
	y = 0;
	temp2 = ft_calloc(1, len + 1);
	while (src[i])
	{
		if (src[i] == S_Q || src[i] == D_Q)
		{
			quote = src[i];
			if (delete_quote(src, i, quote))
				i++;
			else
			{
				temp2[y] = src[i];
				y++;
				i++;
			}
		}
		else
		{
			temp2[y] = src[i];
			y++;
			i++;
		}
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
			len = get_len(temp->argv[i]);
			temp2 = strcpywithout(temp->argv[i], len);
			free(temp->argv[i]);
			temp->argv[i] = temp2;
			i++;
		}
		temp = temp->next;
	}
}
