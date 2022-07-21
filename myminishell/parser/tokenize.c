/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:23:48 by qduong            #+#    #+#             */
/*   Updated: 2022/07/21 22:28:31 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	strcount(char const *s, char c)
{
	int		counter;
	int		j;
	int		string;

	counter = 0;
	j = 0;
	string = 0;
	while (s[j] != '\0')
	{
		if (s[j] != c && string == 0)
		{
			string = 1;
			counter++;
		}
		else if (s[j] == c)
			string = 0;
		j++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
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
		if (start < 0 && s[i[0]] != c)
			start = i[0];
		else if ((s[i[0]] == c || i[0] == ft_strlen(s)) && 0 <= start)
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
	int		i;

	temp = s->s_p;
	while (temp)
	{
		i = 0;
		temp->argv = ft_split(temp->sub, ' ');
		while (temp->argv[i])
		{
		i++;
		}
		temp = temp->next;
	}
}

int	get_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == S_Q || str[i] == D_Q)
		{
			i++;
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

	i = 0;
	y = 0;
	temp2 = ft_calloc(1, len + 1);
	while (src[i])
	{
		if (src[i] == S_Q || src[i] == D_Q)
			i++;
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
