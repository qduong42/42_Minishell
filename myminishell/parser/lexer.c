/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:19:42 by qduong            #+#    #+#             */
/*   Updated: 2022/07/26 11:24:08 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// LEXER
int	in_or_hd(t_pipe *temp, int i)
{
	if (!ft_strncmp(&(temp->sub[i]), HD, 2))
	{
		i = iohandler(temp, i + 1, 3);
	}
	else
	{
		i = iohandler(temp, i, 1);
	}
	return (i);
}

int	out_or_app(t_pipe *temp, int i)
{
	if (!ft_strncmp(&temp->sub[i], AP, 2))
		i = iohandler(temp, i + 1, 4);
	else
		i = iohandler(temp, i, 2);
	return (i);
}

void	clean_fd_hd(t_pipe *temp)
{
	if (temp->last == 1)
	{
		if (temp->hd)
		{
			free(temp->hd);
			temp->hd = NULL;
		}
	}
	if (temp->last == 0)
	{
		if (temp->fd_in > 2)
			close (temp->fd_in);
		temp->fd_in = -2;
	}
}

void	int_red(t_shell *s)
{
	t_pipe			*temp;
	int				i;
	int				quote;

	temp = s->s_p;
	while (temp)
	{
		i = 0;
		quote = 0;
		while (temp->sub[i])
		{
			if (!quote && temp->sub[i] == IN)
				i = in_or_hd(temp, i);
			else if (!quote && temp->sub[i] == OUT)
				i = out_or_app(temp, i);
			else if (temp->sub[i] == S_Q || temp->sub[i] == D_Q)
				quote = temp->sub[i];
			else if (quote && (!temp->sub[i] || temp->sub[i] == quote))
				quote = 0;
			i++;
		}
		clean_fd_hd(temp);
		printf("END HEREDOC:%s\t:END FD_IN:%d\n", temp->hd, temp->fd_in);
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

//add_history functionality is built in, so further work required.