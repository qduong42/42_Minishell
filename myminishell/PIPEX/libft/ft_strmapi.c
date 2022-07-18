/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:24:21 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/03 17:51:09 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f) (unsigned int, char))
{
	unsigned int		run;
	char				*res;

	if (!s || !f)
		return (NULL);
	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	run = 0;
	while (s[run])
	{
		res[run] = f(run, s[run]);
		run++;
	}
	res[run] = 0;
	return (res);
}

// char	add_one(char c)
// {
// 	return (c +1);
// }

// int	main(void)
// {
// 	printf("%s", ft_strmapi("Here we go!", &add_one));
// }