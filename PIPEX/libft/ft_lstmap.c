/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:52:35 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 09:51:39 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*fun(void *content)
// {
// 	char	*str;

// 	str = (char *)content;
// 	str[0] = 'X';
// 	return ((void *) str);
// }

// void	del(void *ptr)
// {
// 	t_list	*helper;

// 	helper = (t_list *)ptr;
// 	helper->content = NULL;
// }

t_list	*backbone(t_list *original)
{
	t_list	*ret;
	t_list	*temp;

	ret = NULL;
	while (original)
	{
		temp = ft_lstnew(NULL);
		if (!temp)
			return (NULL);
		ft_lstadd_back(&ret, temp);
		original = original->next;
	}
	return (ret);
}

void	initilizer(t_list *backbone_list, t_list *original, void *(*f) (void *))
{
	while (backbone_list && original)
	{
		backbone_list->content = f(original->content);
		backbone_list = backbone_list->next;
		original = original->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (*del) (void *))
{
	t_list	*res;

	res = backbone(lst);
	if (!res)
	{
		ft_lstclear(&res, del);
		return (NULL);
	}
	initilizer(res, lst, f);
	return (res);
}
