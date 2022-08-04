/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:23:45 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/04 16:14:32 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exit_one(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

void	here_child(char *delim, t_loc loc)
{
	if (!loc.pid)
	{
		signal(SIGINT, exit_one);
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
}

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
	here_child(delim, loc);
	signal(EOF, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	waitpid(loc.pid, &loc.local, 0);
	signal(EOF, SIG_DFL);
	signal(SIGINT, show_prompt);
	g_exit_status = WEXITSTATUS(loc.local);
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
