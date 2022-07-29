/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subpipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 10:17:02 by qduong            #+#    #+#             */
/*   Updated: 2022/07/29 12:30:56 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_handle(t_shell *s, int *start, int i)
{
	char	*token;
	char	*temp;

	token = ft_substr(s->input, *start, i - *start);
	temp = ft_strtrim(token, " ");
	if (token)
		free(token);
	token = temp;
	ft_plstadd_back(&(s->s_p), ft_plstnew(token, s));
	*start = i + 1;
}

void	pipe_split(t_shell *s)
{
	int	i;
	int	quote;
	int	start;

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
