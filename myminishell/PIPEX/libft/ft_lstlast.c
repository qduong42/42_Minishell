/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:52:30 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/03 13:52:31 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (1)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
}

// int	main(void)
// {
// 	t_list	*head;

// 	head = NULL;
// 	ft_lstadd_front(&head, ft_lstnew("hey"));
// 	ft_lstadd_front(&head, ft_lstnew("la"));
// 	printf("%s", ft_lstlast(head)->content);
// }