/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:01:18 by ekraujin          #+#    #+#             */
/*   Updated: 2022/07/27 11:46:33 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char )c)
		return ((char *)s);
	return (0);
}

static char	*lbs(char *line, char *buf)
{
	int		len;
	char	*temp;
	char	*end;

	len = 0;
	while (buf[len] != '\n')
		len++;
	end = ft_substr(buf, 0, len + 1);
	temp = ft_strjoin(line, end);
	free(line);
	line = temp;
	ft_memmove(buf, ft_strchr(buf, '\n') + 1, BUFFER_SIZE - len);
	free(end);
	return (line);
}

static char	*jaf(char *line, char *buf)
{
	char	*temp;

	temp = ft_strjoin(line, buf);
	free(line);
	line = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	int			rs;
	static char	buf[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0)
		return (NULL);
	line = ft_calloc(1, sizeof(char));
	while (!ft_strchr(buf, '\n'))
	{
		if (*buf)
			line = jaf(line, buf);
		rs = read(fd, buf, BUFFER_SIZE);
		if (rs < 0 || !buf[0])
		{
			free(line);
			return (NULL);
		}
		buf[rs] = '\0';
		if (rs < BUFFER_SIZE && !(ft_strchr(buf, '\n')) && line[0] && !buf[0])
			return (line = jaf(line, buf));
	}
	line = lbs(line, buf);
	return (line);
}

// # include <fcntl.h>
// int main(void)
// {
//     int    fd;
//     char *res;
//     int i;

//     fd = open("text.txt", O_RDONLY);
//     printf("Fd: %i\n",fd);
//     i = 1;
// 	res = get_next_line(fd);
//     while (res)
//     {
//         printf("line %i: %s",i, res);
//         i++;
// 		res = get_next_line(fd);
// 	}
// }