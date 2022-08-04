/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:23:45 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/04 12:40:31 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/**
 * @brief open a heredoc file and write to it
 * -> added strlen check for line to allow empty newline input to not stop HD
 * @param delim the input at which writing is stopped
 * @return int the filedescriptor of the heredoc
 * 
 */
void	create_hd(char *delim, t_pipe *cmd)
{
	t_loc	loc;

	pipe(loc._pipe);
	loc.pid = fork();
	if (!loc.pid)
	{
		close(loc._pipe[0]);
		while (1)
		{
			ft_putstr_fd("> ", 2);
			loc.line = get_next_line(0);
			if (!ft_strncmp(loc.line, delim, ft_strlen(delim)))
			{
				free(loc.line);
				break ;
			}
			ft_putstr_fd(loc.line, loc._pipe[1]);
			free (loc.line);
		}
		close(loc._pipe[1]);
		exit_s(0);
	}
	waitpid(loc.pid, NULL, 0);
	close(loc._pipe[1]);
	cmd->hd_fd = loc._pipe[0];
}

/**
 * @brief gives hd fds to the struct (need to be closed later)
 * 
 * @param cmd 
 */
void	here_fuck(t_pipe *cmd)
{
	while (cmd)
	{
		if (cmd->hd)
			create_hd(cmd->hd, cmd);
		cmd = cmd->next;
	}
}
