/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 13:09:37 by qduong            #+#    #+#             */
/*   Updated: 2022/08/04 20:41:15 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fnhandler(t_pipe *sp, int *i, int *z)
{
	char	fn[256];
	char	*temp;
	int		y;

	y = 0;
	while (sp->sub[*i] && sp->sub[*i] == ' ')
	{
		(*z)++;
		(*i)++;
	}
	while (sp->sub[*i] && sp->sub[*i] != ' ' && \
	sp->sub[*i] != '<' && sp->sub[*i] != '>')
	{
		(*z)++;
		fn[y] = sp->sub[*i];
		(*i)++;
		y++;
	}
	fn[y] = '\0';
	temp = ft_strtrim(fn, "\"'");
	return (temp);
}

int	iohandler(t_pipe *sp, int i, int id)
{
	int		z;
	int		be_r;
	char	*temp;

	z = 1;
	i++;
	be_r = i;
	if (id == 3 || id == 4)
		z++;
	if (id == 3 || id == 4)
		be_r--;
	temp = fnhandler(sp, &i, &z);
	if (id == 1)
		input(sp, temp);
	if (id == 2)
		output(sp, temp);
	if (id == 3)
		hd(sp, temp);
	if (id == 4)
		append(sp, temp);
	sp->sub = del_re(sp->sub, z, i, be_r);
	if (id != 3)
		free (temp);
	return (-1);
}
