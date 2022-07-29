/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:24:12 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 09:51:10 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	int				count;

	count = 0;
	while (src[count])
		count++;
	i = 0;
	while (src[i] && i < dstsize - 1 && dstsize > 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = 0;
	return (count);
}
