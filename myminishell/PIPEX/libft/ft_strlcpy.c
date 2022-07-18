/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:24:12 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:24:13 by ljahn            ###   ########.fr       */
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

// int main (void)
// {
// 	char src[] = "coucou";
// 	char dest[10];
// 	memset(dest, 'A', 10);
// 	printf("%lu\n", ft_strlcpy(dest, src, 1));
// 	printf("o %s\n", dest);
// 	char src2[] = "coucou";
// 	memset(dest, 'A', 10);
// 	printf("%lu\n", strlcpy(dest, src2, 1));
// 	printf("c %s\n", dest);
// }