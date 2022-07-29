/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:22:50 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 09:49:39 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	sizer(long holder)
{
	int	res;

	res = 0;
	if (holder == 0)
		return (1);
	while (holder > 0)
	{
		res++;
		holder /= 10;
	}
	return (res);
}

char	*ft_strrev(char *s)
{
	int		lower;
	int		upper;
	char	temp;

	lower = 0;
	upper = ft_strlen(s) - 1;
	while (lower < upper)
	{
		temp = s[lower];
		s[lower] = s[upper];
		s[upper] = temp;
		lower++;
		upper--;
	}
	return (s);
}

static void	digiter(char *s, long holder, int sign)
{
	int		i;

	i = 0;
	if (holder == 0)
	{
		s[i] = '0';
		i++;
	}
	while (holder > 0)
	{
		s[i++] = holder % 10 + 48;
		holder /= 10;
	}
	if (sign == -1)
	{
		s[i] = '-';
		i++;
	}
	s[i] = 0;
}

char	*ft_itoa(int n)
{
	char	*res;
	int		sign;
	long	holder;

	sign = 1;
	holder = n;
	if (n < 0)
	{
		sign = -1;
		holder *= -1;
		res = malloc((sizer(holder) + 2) * sizeof(char));
	}
	else
		res = malloc((sizer(holder) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	digiter(res, holder, sign);
	return (ft_strrev(res));
}
