/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 20:39:33 by qduong            #+#    #+#             */
/*   Updated: 2022/07/16 16:49:51 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (lst)
	{
		if (*lst)
		{
			while (current -> next != NULL)
			{
				current = current -> next;
			}
			current -> next = new;
		}
		else
			*lst = new;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	(*new).next = NULL;
	return (new);
}

t_pipe	*ft_plstnew(void *content)
{
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->argv = NULL;
	new->sub = content;
	new->fd_in = -2;
	new->fd_out = -2;
	new->hd = NULL;
	new->next = NULL;
	return (new);
}

void	ft_plstadd_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*current;

	current = *lst;
	if (lst)
	{
		if (*lst)
		{
			while (current -> next != NULL)
			{
				current = current -> next;
			}
			current -> next = new;
		}
		else
			*lst = new;
	}
}
