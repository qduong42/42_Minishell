/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:24:39 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 10:05:23 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

// static int	ft_strlen(char const *str)
// {
// 	int	i;
// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	res = malloc(sizeof(char) * (j - i + 2));
	if (!res)
		return (NULL);
	k = 0;
	while (i <= j)
	{
		res[k] = s1[i];
		i++;
		k++;
	}
	res[k] = 0;
	return (res);
}
