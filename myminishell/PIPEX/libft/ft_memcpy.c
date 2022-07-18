/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:23:04 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:23:05 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char				*cdst;
	char				*csrc;
	unsigned int		temp;

	cdst = (char *)dst;
	csrc = (char *)src;
	temp = 0;
	if (!dst && !src)
		return (0);
	while (temp < n)
	{
		cdst[temp] = csrc[temp];
		temp++;
	}
	return (dst);
}
