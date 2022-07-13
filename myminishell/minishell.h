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

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_pipe
{
	char			*sub;
	char			**argv;
	int				fd_in;
	int				fd_out;
	int				hd;
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

void	print_list(t_pipe *list);

void	int_red(t_shell *s);

void	input_handle(char *string, t_pipe *s);

void	init_all(t_shell *s);

/*
** LIBFT FUNCTIONS
*/

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

size_t	ft_strlcat(char *dst, const char *src, size_t size);

void	*ft_calloc(size_t nmemb, size_t size);

int		ft_isalnum(int c);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_putstr_fd(char *s, int fd);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	*ft_memset(void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n);

int		ft_isalpha(int c);

int		ft_isdigit(int c);

void	ft_putchar_fd(char c, int fd);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s);

void	ft_lstadd_back(t_list **lst, t_list *new);

t_list	*ft_lstnew(void *content);

t_pipe	*ft_plstnew(void *content);

void	ft_plstadd_back(t_pipe **lst, t_pipe *new);

#endif
