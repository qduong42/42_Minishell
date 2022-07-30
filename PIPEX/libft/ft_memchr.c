/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:22:55 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 09:51:30 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*su;

	i = 0;
	su = (unsigned char *)s;
	while (i < n)
	{
		if (*su == (unsigned char)c)
			return (su);
		i++;
		su++;
	}
	return (0);
}
