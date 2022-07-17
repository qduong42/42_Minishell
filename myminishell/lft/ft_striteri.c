/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:23:57 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:23:58 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f) (unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void	tester(unsigned int index, char *ptr)
// {
// 	*ptr += 1;
// }

// int	main(void)
// {
// 	char	c;
// 	char	*ptr;
// 	char	str[100] = "Ralf du alter Hund";

// 	c = 'g';
// 	ft_striteri(str, &tester);
// 	printf("%s", str);
// }