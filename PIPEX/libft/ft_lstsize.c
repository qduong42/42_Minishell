/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:52:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 09:51:34 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_lstadd_front(t_list **lst, t_list *new)
// {
// 	if (lst && new)
// 	{
// 		new->next = *lst;
// 		*lst = new;
// 	}
// }

// t_list	*ft_lstnew(void	*content)
// {
// 	t_list	*res;

// 	res = malloc(sizeof(t_list));
// 	if (!res)
// 		return (NULL);
// 	res->content = content;
// 	res->next = NULL;
// 	return (res);
// }

int	ft_lstsize(t_list *lst)
{
	int	res;

	res = 0;
	while (lst)
	{
		lst = lst->next;
		res++;
	}
	return (res);
}
