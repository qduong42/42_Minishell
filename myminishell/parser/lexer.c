/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:18:50 by qduong            #+#    #+#             */
/*   Updated: 2022/07/20 23:20:03 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// LEXER

void	int_red(t_shell *s)
{
	t_pipe	*temp;
	int		i;
	int		quote;

	temp = s->s_p;
	while (temp)
	{
		i = 0;
		quote = 0;
		while (temp->sub[i])
		{
			if (!quote)
			{
				if (temp->sub[i] == IN)
				{
					if (!ft_strncmp(&temp->sub[i], HD, 2))
					{
						i++;
						i = iohandler(temp, i, 3, 0);
					}
					else
						i = iohandler(temp, i, 1, 1);
				}
				else if (temp->sub[i] == OUT)
				{
					if (!ft_strncmp(&temp->sub[i], AP, 2))
					{
						i++;
						i = iohandler(temp, i, 4, 0);
					}
					else
						i = iohandler(temp, i, 2, 0);
				}
				else if (temp->sub[i] == S_Q || temp->sub[i] == D_Q)
					quote = temp->sub[i];
			}
			else if (quote && (!temp->sub[i] || temp->sub[i] == quote))
				quote = 0;
			i++;
		}
		temp = temp->next;
	}
}

void	pipe_handle(t_shell *s, int *start, int i)
{
	char	*token;
	char	*temp;

	token = ft_substr(s->input, *start, i - *start);
	temp = ft_strtrim(token, " ");
	free(token);
	token = temp;
	ft_plstadd_back(&(s->s_p), ft_plstnew(token));
	*start = i + 1;
}

void	pipe_split(t_shell *s)
{
	int	i;
	int	quote;
	int start;

	i = 0;
	start = 0;
	quote = 0;
	while (1)
	{
		if ((s->input[i] == PIPE && !quote) || s->input[i] == '\0')
		{
			pipe_handle(s, &start, i);
			if (s->input[i] == '\0')
				break ;
		}
		else if ((s->input[i] == S_Q || s->input[i] == D_Q) && !quote)
			quote = s->input[i];
		else if (quote && (!(s->input[i]) || s->input[i] == quote))
			quote = 0;
		i++;
	}
}

//add_history functionality is built in, so further work required.