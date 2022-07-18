/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:23:52 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:23:53 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*result;

	result = malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (result == 0)
		return (result);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

// int	main(void)
// {
// 	char	str[25] = "here we go you lil crap";
// 	char	*illusion;

// 	illusion = ft_strdup(str);
// 	printf("%s", illusion);
// }