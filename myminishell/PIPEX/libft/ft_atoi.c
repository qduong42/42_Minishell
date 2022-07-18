/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:22:02 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:22:03 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int	is_digit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\n'
		|| *str == '\f' || *str == '\r' || *str == '\t'
		|| *str == '\v')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (is_digit(*str))
	{
		result *= 10;
		result += *str - 48;
		str++;
	}
	return (result * sign);
}

// int main(void)
// {
// 	char str[10] = " 	465dah5";
// 	printf("%d\n", ft_atoi(str));
// 	printf("%d", atoi(str));
// }