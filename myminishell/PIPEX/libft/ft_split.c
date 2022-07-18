/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:23:44 by ljahn             #+#    #+#             */
/*   Updated: 2022/05/02 15:32:54 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc/malloc.h>

static int	counter(char const *s, char c)
{
	int	run;
	int	state;
	int	res;

	state = 1;
	res = 0;
	run = 0;
	while (s[run])
	{
		if (s[run] != c && state)
		{
			res++;
			state = 0;
		}
		else if (s[run] == c)
			state = 1;
		run++;
	}
	return (res);
}

static char	*copier(char const *s, int start, int end)
{
	int		i;
	char	*res;

	res = malloc((end - start + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (start < end)
		res[i++] = s[start++];
	res[i] = 0;
	return (res);
}

char	**get_res(char const *s, char c, char **res, int malloc_count)
{
	int		run;
	int		state;

	state = -1;
	run = 0;
	while (s[run])
	{
		if (s[run] != c && state == -1)
			state = run;
		if (s[run] == c && state >= 0)
		{
			res[malloc_count] = copier(s, state, run);
			malloc_count++;
			state = -1;
		}
		run++;
	}
	if (state >= 0)
	{
		res[malloc_count] = copier(s, state, run);
		malloc_count++;
	}
	res[malloc_count] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		malloc_count;
	char	**res;

	if (!s)
		return (NULL);
	res = malloc((counter(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	malloc_count = 0;
	res = get_res(s, c, res, malloc_count);
	return (res);
}

// int	main(void)
// {
// 	int		i;
// 	char	**ret;

// 	printf("%d",counter(" Tripouille ", ' '));
// 	i = 0;
// 	while (ret[i])
// 	{
// 		printf("%s", ret[i]);
// 		printf("executed");
// 		i++;
// 	}
// }
