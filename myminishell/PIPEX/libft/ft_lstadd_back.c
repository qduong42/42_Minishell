/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:51:59 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/03 16:49:57 by ljahn            ###   ########.fr       */
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

// int	main(void)
// {
// 	t_list	*head;

// 	head = NULL;
// 	ft_lstadd_back(&head, ft_lstnew("Alloah"));
// 	printf("%s", (char *)head->content);
// }
