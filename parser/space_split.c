/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:24:34 by qduong            #+#    #+#             */
/*   Updated: 2022/08/03 18:24:55 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	strcount(char *s, char c)
{
	int		counter;
	int		j;
	int		string;

	counter = 0;
	j = 0;
	string = 0;
	while (s[j] != '\0')
	{
		if (s[j] != c && string == 0 && outside_quotes(s, j))
		{
			string = 1;
			counter++;
		}
		else if (s[j] == c && outside_quotes(s, j))
		{
			string = 0;
		}
		j++;
	}
	return (counter);
}

char	**ft_space_split(char *s, char c)
{
	char	**array;
	int		start;
	size_t	i[2];

	array = malloc((strcount(s, c) + 1) * sizeof(char *));
	i[0] = 0;
	i[1] = 0;
	start = -1;
	if (!array || !s)
		return (NULL);
	while (i[0] <= ft_strlen(s))
	{
		if (start < 0 && s[i[0]] != c && outside_quotes(s, i[0]))
			start = i[0];
		else if ((s[i[0]] == c || i[0] == ft_strlen(s)) && \
		0 <= start && outside_quotes(s, i[0]))
		{
			array[i[1]] = ft_substr(s, start, i[0] - start);
			start = -1;
			i[1]++;
		}
		i[0]++;
	}
	array[i[1]] = 0;
	return (array);
}

void	space_split(t_shell *s)
{
	t_pipe	*temp;

	temp = s->s_p;
	while (temp)
	{
		temp->argv = ft_space_split(temp->sub, ' ');
		temp = temp->next;
	}
}
