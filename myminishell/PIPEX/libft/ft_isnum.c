/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:29:17 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/27 11:45:57 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isnum(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}
