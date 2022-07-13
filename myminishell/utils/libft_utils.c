/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 22:56:29 by qduong            #+#    #+#             */
/*   Updated: 2022/07/13 00:42:25 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (size == 0)
	{
		return (src_len);
	}
	else
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		return (src_len);
	}
	return (src_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (src_len + size);
	while (src[i] && dst_len + i < size - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pch;

	pch = malloc((size * nmemb));
	if (!pch)
		return (NULL);
	ft_bzero (pch, nmemb * size);
	return (pch);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	tlen;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1)
	{
		s1++;
	}
	tlen = ft_strlen(s1);
	while (ft_strchr(set, s1[tlen - 1]) && *s1)
		tlen--;
	trim = ft_substr(s1, 0, tlen);
	return (trim);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (*s == 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	substr = malloc((sizeof(char) * len) + 1);
	if (!substr)
		return (NULL);
	while (s[start] != '\0' && i < len)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (n > 0 && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		else if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_bzero(void *s, size_t n)
{
	void	*r;
	size_t	m;

	r = s;
	m = n;
	ft_memset(r, 0, m);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*a;
	size_t	i;

	a = (char *)s;
	i = 0;
	while (i < n)
	{
		a[i] = (unsigned char) c;
		i++;
	}
	return (a);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*pch;
	int		lstr;

	pch = (char *) s;
	i = 0;
	lstr = (ft_strlen(s) + 1);
	while (i < lstr)
	{
		if (s[i] == (unsigned char) c)
		{
			return (pch + i);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc ((sizeof(char)) * (ft_strlen(s) + 1));
	if (!s2)
		return (NULL);
	while (s[i] != '\0')
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
