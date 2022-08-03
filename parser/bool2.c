/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:57:28 by qduong            #+#    #+#             */
/*   Updated: 2022/08/03 19:42:57 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	outside_quotes(char *line, int pos)
{
	int	q_num;
	int	qq_num;
	int	i;

	i = 0;
	q_num = 0;
	qq_num = 0;
	while (i < pos)
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
		return (0);
	return (1);
}

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
		if (line[i] == negative)
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
		if (line[i] == quote)
			qq_num++;
		i++;
	}
	if (qq_num % 2 == 1)
		return (1);
	return (0);
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

int	ft_whitespace(char c)
{
	char	white[5];
	int		i;

	white[0] = ' ';
	white[1] = '\t';
	white[2] = '\r';
	white[3] = '\v';
	white[4] = '\f';
	i = 0;
	while (i < 5)
	{
		if (c == white[i])
			return (1);
		i++;
	}
	return (0);
}
