/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:21:30 by qduong            #+#    #+#             */
/*   Updated: 2022/07/29 14:13:40 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pch;

	pch = malloc((size * nmemb));
	if (!pch)
		return (NULL);
	ft_bzero (pch, nmemb * size);
	return (pch);
}

static char	*ft_bufnchecksplit(char	*returnline, char	*buf)
{
	int		index;
	char	*temp;
	int		len;

	len = 0;
	index = 0;
	index = ft_gnl_strrchr (buf, '\n');
	if (index != 0)
	{
		temp = ft_strjoin(returnline, buf);
		free (returnline);
		returnline = temp;
		while (buf[len])
			len++;
		ft_memmove(buf, buf + index, len - index);
		ft_bzero(buf + len - index, 1);
	}
	return (returnline);
}

static char	*ft_bufjoin(char *returnline, char *buf)
{
	char	*temp;

	temp = ft_strjoin(returnline, buf);
	free (returnline);
	returnline = temp;
	ft_bzero(buf, BUFFER_SIZE);
	return (returnline);
}

static char	*freeme(int bytes_read, char *returnline)
{
	if (bytes_read <= 0 && !(*returnline))
	{
		free(returnline);
		return (NULL);
	}
	return (returnline);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*returnline;
	int			bytes_read;

	returnline = ft_calloc(1, sizeof(char));
	while (!ft_gnl_strrchr(buf, '\n'))
	{
		if (*buf)
		{
			returnline = ft_bufjoin(returnline, buf);
		}
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		returnline = freeme(bytes_read, returnline);
		if (bytes_read < BUFFER_SIZE && !ft_gnl_strrchr(buf, '\n'))
		{
			returnline = ft_bufjoin(returnline, buf);
			return (returnline);
		}
	}
	returnline = ft_bufnchecksplit(returnline, buf);
	return (returnline);
}
//accounting for case where buf contains \n
//52-62 put in sub-function by passing buf and returnline