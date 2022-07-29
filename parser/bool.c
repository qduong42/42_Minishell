/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:16:03 by qduong            #+#    #+#             */
/*   Updated: 2022/07/29 08:51:15 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	special_token(char c)
{
	char	specials[4];
	int		i;

	specials[0] = '<';
	specials[1] = '>';
	specials[2] = '|';
	specials[3] = '$';
	i = 0;
	while (i < 4)
	{
		if (c == specials[i])
			return (1);
		i++;
	}
	return (0);
}

int	unexpected_newline(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		if (special(line + i))
		{
			j = i + special(line + i);
			while (line[j] == ' ')
				j++;
			if (!line[j])
				return (1);
		}
		i++;
	}
	return (0);
}

int	single_dollar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (outside_quotes(line, i))
		{
			if (line[i] == '$')
			{
				if (line[i + 1] == ' ')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	special(char *line)
{
	if (line[0])
	{
		if (line[0] == '<' && line[1] == '<')
			return (2);
		if (line[0] == '>' && line[1] == '>')
			return (2);
	}
	if (special_token(line[0]))
		return (1);
	return (0);
}

int	consecutive_specials(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		if (outside_quotes(line, i))
		{
			if (line[i] == '|' && line[i + 1] == '|')
				return (1);
			if (line[i] == '$' && line[i + 1] == '$')
				return (1);
			if (special(line + i) && line[i] != '|')
			{
				j = i + special(line + i);
				while (line[j] == ' ')
					j++;
				if (special(line + j) && line[j] != '$')
					return (1);
			}
		}
		i++;
	}
	return (0);
}
