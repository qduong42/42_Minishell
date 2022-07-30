/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:24:25 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 11:10:32 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char const *s1, char const *s2, unsigned int n)
{
	unsigned char	a;
	unsigned char	b;
	int				index;

	if (!s1 || !s2)
		return (0);
	index = 0;
	if (n == 0)
		return (0);
	while (s1[index] && (s1[index] == s2[index]) && n - 1)
	{
		index++;
		n--;
	}
	a = (unsigned char) s1[index];
	b = (unsigned char) s2[index];
	return (a - b);
}
