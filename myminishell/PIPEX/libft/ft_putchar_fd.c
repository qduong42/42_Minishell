/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:23:17 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:23:18 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putchar_fd(char c, int fd)
{
	if (!fd)
		return ;
	write(fd, &c, sizeof(char));
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("LAAL", O_RDWR | O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	ft_putchar_fd('c', fd);
// 	close(fd);
// }