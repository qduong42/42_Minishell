#ifndef MINISHELL_H
# define MINISHELL_H

extern int exit_status;

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
# include "PIPEX/pipex.h"
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

//last signifies if HD last or INPUT last, it takes last input 
//source and cleans HD or fd
//1 for input and 0 for HD
typedef struct s_pipe
{
	char			*sub;
	char			**argv;
	int				fd_in;
	int				fd_out;
	char			*hd;
	int				last;
	struct s_pipe 	*next;
}					t_pipe;

typedef struct s_shell
{
	struct s_list	*env;
	struct s_pipe	*s_p;
	char			*input;
}	t_shell;

t_list *create_env_list(char **envp);

void	env_solver(t_shell* s);

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
** LIBFT FUNCTIONS
*/

t_pipe	*ft_plstnew(void *content);

void	ft_plstadd_back(t_pipe **lst, t_pipe *new);

void	remove_quotes(t_shell*s);

void	print_final_array(t_pipe *list);

/*
**  Linus bool.c
*/  

int		special_token(char c);
int		ft_whitespace(char c);
int		valid_name(char *line);
int		unclosed_quotes(char *line);
void	file_exists(char *filename);
int		special(char *line);
int		single_dollar(char *line);
int		unexpected_newline(char *line);
int		consecutive_specials(char *line);

//			error_handeling.c
int		errors(char *line);

//			utils/ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);

//			pipex_stuff
void	show_prompt(int sig);

#endif
