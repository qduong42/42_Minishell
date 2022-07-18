/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:24:08 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:24:09 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	j = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size < dstlen)
		return (size + srclen);
	if (size == 0)
		return (srclen);
	while (dst[i])
		i++;
	while (i < (size - 1) && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	return (dstlen + srclen);
}

// int	main(void)
// {
// 	char	*buff;

// 	buff = malloc(15 * sizeof(char));
// 	memset(buff, 'r', 15);
// 	strlcat(buff, "This has more than 20 chars.", 5);
// 	printf("%s", buff);
// }