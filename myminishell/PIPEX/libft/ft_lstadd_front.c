/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:52:08 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/03 13:52:09 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

// void	print_list_content(t_list *head)
// {
// 	while (head)
// 	{
// 		printf("%s", head->content);
// 		head = head->next;
// 	}
// }

// int	main(void)
// {
// 	t_list	*head;
// 	// t_list	n1;
// 	// t_list	n2;
// 	// t_list	n3;

// 	// n1.content = "Here";
// 	// n2.content = " we";
// 	// n3.content = " go.";
// 	// n3.next = NULL;
// 	head = NULL;
// 	//n1.next = &n2;
// 	ft_lstadd_front(&head, ft_lstnew("3"));
// 	ft_lstadd_front(&head, ft_lstnew("2"));
// 	ft_lstadd_front(&head, ft_lstnew("1"));

// 	print_list_content(head);
// }