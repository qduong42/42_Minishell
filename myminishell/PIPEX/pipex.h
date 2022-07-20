/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:27:05 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/20 17:55:41 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define PATH_MAX 69

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "../minishell.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../minishell.h"

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

typedef struct s_pipe t_pipe;

//			ignore.c
char	*get_path(char *cmd, char **env);
void	free_all(char **to_free);
void	conditions(t_vars *vars);
void	error_msg(char *msg);

//			pipex.c
int		pipex(t_pipe *cmd, t_list **env_lst);
char	**lst_to_strstr(t_list *env);

//			cd.c
int		ft_cd(char **args, t_list *env);
int		ft_home(t_list *env);
int		pwd();
int		ft_oldpwd(t_list *env);

//			echo.c
int		ft_echo(char **args);

//			export.c
int		ft_export(char **args, t_list **env);
char	**lst_to_strstr(t_list *env);
void	print_sorted_ev(t_list *env);

//			unset.c
int		unset(char	**args, t_list **env);

//			env.c
int		ft_env(t_list *env);

#endif