/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:52:13 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/03 13:52:14 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list	**lst, void (*del) (void *))
{
	t_list	*element;
	t_list	*element2;

	element = *lst;
	while (element && del)
	{
		element2 = element->next;
		del(element->content);
		free(element);
		element = element2;
	}
	*lst = NULL;
}
