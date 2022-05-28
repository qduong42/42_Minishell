#ifndef MINISHELL_H
# define MINISHELL_H

/*
**	INCLUDES
*/

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

#endif