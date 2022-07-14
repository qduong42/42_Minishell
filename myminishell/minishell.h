#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_MAX 69

/*
**	INCLUDES
*/

# include "lft/libft.h"
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
// # include <termios.h> // tcsetattr, tcgetattr -> not used
// # include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs -> not used

# define PROMPT "\e[44m小さいshell \e[42mv0.42\e[0m $ "
# define PIPE '|'
# define S_Q '\''
# define D_Q '\"'
# define IN '<'
# define OUT '>'
# define AP ">>"
# define HD "<<"

typedef struct s_pipe
{
	t_list			*sub;
	int				fd_in;
	int				fd_out;
	int				hd;
}					t_pipe;

typedef struct s_shell
{
	t_list			*env;
	struct s_pipe	*s_p;
	char			*input;
}	t_shell;

t_list *create_env_list(char **envp);

void	env_solver(t_shell* s);

void	pipe_split(t_shell *s);

void	print_list(t_list *list);

void	int_red(t_shell *s);

void	input_handle(char *string, t_shell *s);

void	init_all(t_shell *s);

//			bool.c
int		special_token(char c);
int		whitespace(char c);
int		valid_name(char *line);
int		unclosed_quotes(char *line);
void	file_exists(char *filename);
void	error_msg(char *msg);
int		special(char *line);
int		single_dollar(char *line);
int		unexpected_newline(char *line);
int		consecutive_specials(char *line);

//			error_handeling.c
int		errors(char *line);

//			ft_cd.c
int		ft_cd(char **args, t_list *env);
int		ft_home(t_list *env);
int		pwd();
int		ft_oldpwd(t_list *env);

//			ft_echo.c
int		ft_echo(char **args);

#endif
