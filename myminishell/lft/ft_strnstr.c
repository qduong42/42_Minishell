/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:24:29 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:24:30 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

static int	ft_state(const char *haystack, const char *needle, size_t remaining)
{
	while (*needle)
	{
		if (*haystack != *needle || remaining == 0)
			return (0);
		haystack++;
		needle++;
		remaining--;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		if (*haystack == *needle)
			if (ft_state(haystack, needle, len))
				return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}

// int	main(void)
// {
// 	char	needle[5] = "";
// 	char	haystack[43] = "I can't say a fucking sentence without it.";

// 	printf("%s\n", ft_strnstr(haystack, needle, 0));
// 	printf("%s", strnstr(haystack, needle, 0));
// }
