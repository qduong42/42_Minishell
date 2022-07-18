/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:27:05 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/18 11:22:16 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>

# define FIRST_NOT_HERE_DOC 2
# define FIRST_HERE_DOC 3

typedef struct s_vars
{
	int		upper_exclu;
	int		outfile;
	int		infile;
	int		temp;
	int		temp_doc;
	int		ac;
	char	**av;
	char	**env;
	pid_t	pid;
	int		i;
	int		carry[1];
	int		working[2];
	char	*path;
	char	**spliters;
	int		here_doc;
	int		last_cmd;
	int		is_outfile;
}	t_vars;

typedef struct s_path
{
	int			i;
	int			i_pre;
	char		*joined;
	char		*temp;
	char		**prefix;
}	t_path;

typedef struct s_pipe
{
	char			*sub;
	char			**argv;
	int				fd_in;
	int				fd_out;
	char			*hd;
	struct s_pipe 	*next;
}					t_pipe;

//			ignore.c
char	*get_path(char *cmd, char **env);
void	free_all(char **to_free);
void	conditions(t_vars *vars);

//			main.c
int		pipex(t_pipe *cmd, char **env);

#endif