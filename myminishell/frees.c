/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:15:01 by qduong            #+#    #+#             */
/*   Updated: 2022/07/28 13:15:44 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (temp)
	{
		free (temp->content);
		temp = temp->next;
	}
}

void	free_pipes(t_pipe **sp)
{
	t_pipe	*pipe;
	t_pipe	*tmp;
	int		i;

	if (!sp)
		return ;
	pipe = *sp;
	while (pipe)
	{
		if (pipe->sub)
			free (pipe->sub);
		if (pipe->hd)
			free (pipe->hd);
		i = 0;
		while (pipe->argv[i])
		{
			free (pipe->argv[i]);
			i++;
		}
		free (pipe->argv);
		tmp = pipe->next;
		free (pipe);
		pipe = tmp;
	}
}

void	free_me(t_shell *s)
{
	if (s->input)
		free (s->input);
	ft_lstclear(&s->env, free);
	free_pipes(&(s->s_p));
}
