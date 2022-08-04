/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:57:28 by qduong            #+#    #+#             */
/*   Updated: 2022/08/04 14:57:22 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inside_diff(char *line, int pos, char quote)
{
	int		num;
	int		i;
	char	negative;

	if (quote == '\'')
		negative = '"';
	else if (quote == '"')
		negative = '\'';
	else
		return (0);
	i = 0;
	num = 0;
	while (i < pos)
	{
		if (quote_we_count(line, i, negative))
			num++;
		i++;
	}
	if (num % 2 == 1)
		return (1);
	return (0);
}

int	inside_same(char *line, int pos, char quote)
{
	int	qq_num;
	int	i;

	i = 0;
	qq_num = 0;
	while (i < pos)
	{
		if (quote_we_count(line, i, quote))
			qq_num++;
		i++;
	}
	if (qq_num % 2 == 1)
		return (1);
	return (0);
}

int	quote_we_count(char *str, int i, char search)
{
	if (str[i] == search)
	{
		if (!(inside_diff(str, i, str[i]) && !inside_same(str, i, str[i])))
			return (1);
	}
	return (0);
}

int	delete_quote(char *str, int i, char quote)
{
	if (inside_diff(str, i, quote) && !inside_same(str, i, quote))
		return (0);
	else
		return (1);
}

int	unclosed_quotes(char *line)
{
	int	q_num;
	int	qq_num;
	int	i;

	i = 0;
	q_num = 0;
	qq_num = 0;
	while (line[i])
	{
		if (q_num % 2 == 0)
		{
			if (line[i] == '"')
				qq_num++;
		}
		if (qq_num % 2 == 0)
		{
			if (line[i] == '\'')
				q_num++;
		}
		i++;
	}
	if (q_num % 2 == 1 || qq_num % 2 == 1)
		return (1);
	return (0);
}
