/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:23:29 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 10:23:30 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s++, 1);
	}
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("LAAL", O_RDWR | O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	ft_putstr_fd("Hello", fd);
// 	close(fd);
// }