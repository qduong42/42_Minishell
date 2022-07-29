/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:51:59 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 09:49:46 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*moving_head;

	moving_head = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (moving_head->next != NULL)
			moving_head = moving_head->next;
		moving_head->next = new;
	}
}
