/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:23:23 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:23:24 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	long	schlong;

	schlong = n;
	if (schlong < 0)
	{
		write(fd, "-", 1);
		schlong *= -1;
	}
	digit = schlong % 10 + 48;
	if (schlong / 10 > 0)
	{
		ft_putnbr_fd(schlong / 10, fd);
	}
	write(fd, &digit, 1);
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("LAAL", O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	ft_putnbr_fd(0, fd);
// 	close(fd);
// }