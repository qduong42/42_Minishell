/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:57:34 by qduong            #+#    #+#             */
/*   Updated: 2022/08/04 14:57:48 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
