/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:35:19 by qduong            #+#    #+#             */
/*   Updated: 2022/08/04 14:46:32 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * fd_in initialised with -2, close last fd if fd is set, open RDONLY
 * 
 * @param sp 
 * @param temp 
 */
void	input(t_pipe *sp, char *temp)
{
	if (sp->fd_in > 2)
		close(sp->fd_in);
	sp->fd_in = open(temp, O_RDONLY);
	if (sp->fd_in == -1)
	{
		sp->main->inv_fd_in = 1;
		perror(temp);
	}
	sp->last = 1;
}

void	output(t_pipe *sp, char *temp)
{
	if (sp->fd_out > 2)
		close(sp->fd_out);
	sp->fd_out = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (sp->fd_out == -1)
		perror(temp);
}

void	hd(t_pipe *sp, char *temp)
{
	if (sp->hd)
		free (sp->hd);
	sp->hd = temp;
	sp->last = 0;
}

void	append(t_pipe *sp, char *temp)
{
	if (sp->fd_out > 2)
		close(sp->fd_out);
	sp->fd_out = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (sp->fd_out == -1)
		perror(temp);
}
