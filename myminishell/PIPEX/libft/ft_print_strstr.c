/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_strstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:38:09 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/28 11:38:10 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief printing a strstr
 * 
 * @param strstr 
 */
void	ft_print_strstr(char **strstr)
{
	int	i;

	i = 0;
	while (strstr[i])
	{
		printf("STRSTR: %s\n", strstr[i]);
		i++;
	}
}
