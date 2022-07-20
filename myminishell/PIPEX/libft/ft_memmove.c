/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:23:08 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:23:09 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char				*cdst;
	char				*csrc;
	unsigned int		temp;

	cdst = (char *)dst;
	csrc = (char *)src;
	temp = 0;
	while (temp < n)
	{
		cdst[temp] = csrc[temp];
		temp++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (!dst && !src)
		return (0);
	if (src < dst)
	{
		while (len--)
			d[len] = s[len];
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
