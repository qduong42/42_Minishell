/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 08:46:06 by ljahn             #+#    #+#             */
/*   Updated: 2022/08/04 14:48:40 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
**	INCLUDES
*/

// # include "lft/libft.h"
# include <stdio.h> // readline, printf
# include <stdlib.h> // malloc, free, exit, getenv, 
# include <fcntl.h> // open
# include <unistd.h> // access, unlink, close, read, write, pipe, dup, dup2,
// execve, fork, getcwd, chdir, stat, lstat, fstat, isatty, ttyname, ttyslot,
// ioctl
# include <sys/wait.h> // waitpid, wait, wait3, wait4
# include <signal.h> // signal, sigaction, kill
# include <sys/types.h> // opendir, closedir
# include <dirent.h> // readdir
# include <stdio.h> // perror
# include <string.h> // strerror
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/stat.h>
# include "PIPEX/pipex.h"
// # include <termios.h> // tcsetattr, tcgetattr -> not used

extern int	g_exit_status;

# define PROMPT "小さいshell v2.42 $ "
# define PIPE '|'
# define S_Q '\''
# define D_Q '\"'
# define IN '<'
# define OUT '>'
# define AP ">>"
# define HD "<<"

typedef int	(*t_reaction) (void *);

//last signifies if HD last or INPUT last, it takes last input 
//source and cleans HD or fd
//1 for input and 0 for HD
typedef struct s_shell
{
	struct s_list	*env;
	struct s_pipe	*s_p;
	char			*input;
	int				inv_fd_in;
}	t_shell;

typedef struct s_pipe
{
	char			*sub;
	char			**argv;
	int				fd_in;
	int				fd_out;
	char			*hd;
	int				hd_fd;
	int				last;
	struct s_pipe	*next;
	struct s_shell	*main;
}					t_pipe;

t_list	*create_env_list(char **envp);

void	env_solver(t_shell *s, int i);

void	pipe_split(t_shell *s);

void	print_list(t_pipe *list, int a);

void	int_red(t_shell *s);

// 0 for in, 1 for out, 2 for <<, 3 for >>
int		iohandler(t_pipe *sp, int i, int id);

void	init_all(t_shell *s);

void	space_split(t_shell *s);

//redirection.c
// char	*del_re(char *sub, int len_fn, int end, int be_r);

// void	ft_catall(char *dst, const char *src);

// void	input(t_pipe *sp, char *temp, int in);

// void	output(t_pipe *sp, char *temp);

// void	append(t_pipe *sp, char *temp);

// char	*iohandler(t_pipe *sp, int i, int id, int in);

/*
** Utils FUNCTIONS
*/

//lists.c

t_pipe	*ft_plstnew(void *content, t_shell *s);

void	ft_plstadd_back(t_pipe **lst, t_pipe *new);

//tokenize.c

void	remove_quotes(t_shell*s);

void	print_final_array(t_pipe *list);

//subpipes.c

void	pipe_split(t_shell *s);

//lexer.c

int		in_or_hd(t_pipe *temp, int i);

int		out_or_app(t_pipe *temp, int i);

void	clean_fd_hd(t_pipe *temp);

//utils.c

void	ft_catall(char *dst, const char *src);

char	*del_re(char *sub, int len_fn, int end, int be_r);

int		digit_len(int a);

//redir_sub.c

void	input(t_pipe *sp, char *temp);

void	output(t_pipe *sp, char *temp);

void	hd(t_pipe *sp, char *temp);

void	append(t_pipe *sp, char *temp);

// frees.c

void	free_env(t_list *env);

void	free_pipes(t_pipe **sp);

void	free_me(t_shell *s);

// envp_res2.c

int		variable_length(t_shell *s, int i);

char	*special_join(char *final, char *env, int len, int be_do);

char	*variable_name(char const *s1, char s2, int len);

int		env_len(char *env);

/*
**  Linus bool.c
*/

int		special_token(char c);
int		unexpected_newline(char *line);
int		single_dollar(char *line);
int		special(char *line);
int		consecutive_specials(char *line);

//bool2.c

int		delete_quote(char *str, int i, char quote);
int		unclosed_quotes(char *line);
int		outside_quotes(char *line, int pos);
int		ft_whitespace(char c);
int		quote_we_count(char *str, int i, char search);

//			error_handeling.c
int		errors(char *line, t_list **env);

//			utils/ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);

//			pipex_stuff
void	show_prompt(int sig);

//			main.c
void	free_pipes(t_pipe **sp);

#endif
