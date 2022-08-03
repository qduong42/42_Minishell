/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:57:28 by qduong            #+#    #+#             */
/*   Updated: 2022/08/03 19:32:30 by ljahn            ###   ########.fr       */
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

int	inside_SQ(char *line, int pos)
{
	int	q_num;
	int	i;

	i = 0;
	q_num = 0;
	while (i < pos)
	{
		if (line[i] == '\'')
			q_num++;
	}
	if (q_num % 2 == 1)
		return (1);
	return (0);
}

int	inside_DQ(char *line, int pos)
{
	int	qq_num;
	int	i;

	i = 0;
	qq_num = 0;
	while (i < pos)
	{
		if (line[i] == '"')
			qq_num++;
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
