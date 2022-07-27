/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortstrstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 12:11:35 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 12:12:15 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sortstrstr(char **strstr)
{
	char	*tmp;
	int		i;
	int		ordered;

	ordered = 0;
	while (ordered == 0)
	{
		i = 0;
		ordered = 1;
		while (strstr[i] && strstr[i + 1])
		{
			if (ft_strcmp(strstr[i], strstr[i + 1]) > 0)
			{
				tmp = strstr[i];
				strstr[i] = strstr[i + 1];
				strstr[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
	}
}
