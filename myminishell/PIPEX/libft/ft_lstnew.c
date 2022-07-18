/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:52:41 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/03 13:52:42 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void	*content)
{
	t_list	*res;

	res = malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->content = content;
	res->next = NULL;
	return (res);
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
// 	t_list	n1;
// 	t_list	n2;
// 	t_list	n3;

// 	n1.content = "This";
// 	n2.content = "Is";
// 	n3.content = "Nuts";
// 	head = &n2;
// 	n1.next = &n3;
// 	n2.next = &n1;
// 	n3.next = ft_lstnew("You lil shit");
// 	print_list_content(head);
// }
