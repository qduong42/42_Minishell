/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 09:20:17 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/29 09:20:18 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
** redirection.c utils
*/

/**
 * catall from source to dst until no src, assumes dest is big enough
 * @param dst [char *] destination string
 * @param src [char *] source string
*/
void	ft_catall(char *dst, const char *src)
{
	int	i;
	int	dest_len;

	dest_len = ft_strlen(dst);
	i = 0;
	while (src[i])
	{
		dst[i + dest_len] = src[i];
		i++;
	}
	dst[i + dest_len] = '\0';
}

/**
 * deletes redirection and filename/LIM from char *sub
 * @param sub [char *] sub from [t_pipe *sp]
 * @param len_fn [int] len of filename
 * @param end [int] end of redirection -upon finding next space/ red after fn
 * @return [char *] temp to replace sub with 1 red removed and interpreted
*/
char	*del_re(char *sub, int len_fn, int end, int be_r)
{
	int		len;
	char	*temp;
	char	*final;

	len = 0;
	len = ft_strlen(sub);
	temp = ft_calloc(1, len - len_fn + 1);
	ft_strlcpy(temp, sub, be_r);
	ft_catall(temp, sub + end);
	final = ft_strtrim(temp, " ");
	free(temp);
	temp = final;
	if (sub)
		free(sub);
	return (temp);
}

/**
 * @brief util function for replace dollar Q
 * @param a -> exit status 
 * @return [int] digit length of exit status 
 */
int	digit_len(int a)
{
	int	i;

	i = 1;
	while (a)
	{
		a /= 10;
		i++;
	}
	return (i);
}
