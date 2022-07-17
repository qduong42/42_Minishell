/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:22:58 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:22:59 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int				i;
	unsigned char				*s1u;
	unsigned char				*s2u;

	s1u = (unsigned char *)s1;
	s2u = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (s1u[i] == s2u[i] && i < n - 1)
		i++;
	return (s1u[i] - s2u[i]);
}

// int	main(void)
// {
// 	char s2[] = {0, 0, 127, 0};
// 	char s3[] = {0, 0, 42, 0};

// 	printf("%d", ft_memcmp(s2, s3, 4));
// }