/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:27:05 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/30 13:26:51 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FT_PATH_MAX 255

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "../minishell.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../minishell.h"

typedef struct s_vars
{
	int		tmp;
	int		carry;
	int		outfile;
	char	**env;
	pid_t	pid;
	int		working[2];
	char	*path;
	char	**spliters;
}	t_vars;

//Have you freed your splitters
typedef struct s_path
{
	int			i;
	int			i_pre;
	char		*joined;
	char		*temp;
	char		**prefix;
}	t_path;

typedef struct s_pipe	t_pipe;

typedef int				(*t_reaction) (void *);

//			pipex.c
void	pipex(t_pipe *cmd, t_list **env_lst);

//			cd.c
int		ft_cd(char **args, t_list *env);
int		ft_home(t_list *env);
int		ft_oldpwd(t_list *env);

//			pwd.c
int		pwd(t_pipe *cmd);
char	*get_pwd(void);
void	update_env(char *pwd, char *oldpwd, t_list *env);

//			echo.c
int		ft_echo(char **args);

//			export.c
int		ft_export(char **args, t_list **env);
char	**lst_to_strstr(t_list *env);
void	print_sorted_ev(t_list *env);
int		valid_env(char *var);

//			unset.c
int		ft_unset(char	**args, t_list **env);
void	unset_one(t_list **env, char *one);

//			env.c
int		ft_env(t_pipe *cmd, t_list *env);

//			else_if.c
int		is_buildin(t_pipe *cmd);
int		exec_buildin(t_pipe *cmd, t_list **env_lst);
int		is_parent(t_pipe *cmd);
int		exec_parent(t_pipe *cmd, t_list **env_lst);

//			abstractable.c
char	**lst_to_strstr(t_list *env);
int		create_hd(char *delim);
void	error_msg(char *msg);
char	*get_path(char *cmd, char **env);

//			exec_loop.c
int		while_stroke(t_pipe **cmd, t_vars *vars, t_list **env_lst);
void	assign_outfile(t_vars *vars, t_pipe *cmd);
void	duping(t_vars *vars, t_pipe *cmd);
void	aftershave(t_vars *vars, t_pipe **cmd);
void	close_free(t_vars *vars, t_pipe *cmd);

//			error_handeling.c
int		react_if_ncontained(t_reaction reaction, char *contained, t_list **env);
int		path_error(void *data);

//			error_handeling.c
int		react_if_ncontained(t_reaction reaction, char *contained, t_list **env);
int		path_error(void *data);

#endif