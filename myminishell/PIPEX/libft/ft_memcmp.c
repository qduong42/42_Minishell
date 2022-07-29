/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:22:58 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 09:50:45 by qduong           ###   ########.fr       */
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
