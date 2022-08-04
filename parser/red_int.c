/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:19:42 by qduong            #+#    #+#             */
/*   Updated: 2022/08/04 11:25:25 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	int_red(t_shell *s)
{
	t_pipe			*temp;
	int				i;

	temp = s->s_p;
	while (temp)
	{
		i = 0;
		while (temp->sub[i])
		{
			if (outside_quotes(temp->sub, i) && temp->sub[i] == IN)
				i = in_or_hd(temp, i);
			else if (outside_quotes(temp->sub, i) && temp->sub[i] == OUT)
				i = out_or_app(temp, i);
			i++;
		}
		clean_fd_hd(temp);
		temp = temp->next;
	}
}

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
