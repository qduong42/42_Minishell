/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:22:55 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:22:56 by ljahn            ###   ########.fr       */
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

// int	main(void)
// {
// 	char	*str;

// 	str = ft_memchr("Daggi bi", 'b', 8);
// 	printf("%s", str);
// }