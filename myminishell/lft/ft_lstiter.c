/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:52:24 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/03 13:52:25 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f) (void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// void			lstiter_f(void *content) {
// 	char *s = content;

// 	s[0] = 'O';
// 	s[1] = 'K';
// }

// void	apply(void *list_element)
// {
// 	t_list	*head;

// 	head = (t_list *) list_element;
// 	head->content = "sugar bombs -- ";
// }

// int	main(void)
// {
// 	t_list	*head;

// 	head = NULL;
// 	ft_lstadd_back(&head, ft_lstnew(ft_strdup("KO !")));
// 	ft_lstadd_back(&head, ft_lstnew(ft_strdup("KO !")));
// 	printf("%s\n", head->content);
// 	ft_lstiter(head, lstiter_f);
// 	printf("%s", head->content);
// 	printf("%s", (head->next)->content);
// 	free(head->content);
// }