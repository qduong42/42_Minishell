NAME := pipex.a

SRCS = builtins/cd.c builtins/echo.c builtins/export.c builtins/unset.c builtins/env.c pipex.c from_pipex/else_if.c from_pipex/abstractable.c \
		from_pipex/exec_loop.c from_pipex/here_doc.c builtins/pwd.c
OBJS = cd.o echo.o export.o unset.o pipex.o env.o else_if.o abstractable.o exec_loop.o pwd.o here_doc.o
DIRS = libft/libft.a get_next_line/get_next_line.a

ifeq ($(UNAME), Darwin)
	CFLAGS = -D MAX_FDS=4096 -Wall -Wextra -Werror -g
else
	CFLAGS = -D MAX_FDS=1024 -Wall -Wextra -Werror -g
endif
CC = gcc
DEPS = pipex.h # only direct dependency

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(SRCS)
	$(MAKE) -C libft
	$(MAKE) -C get_next_line
	gcc $(CFLAGS) -c $(SRCS)
	ar -rcs $(NAME) $(OBJS) $(DIRS)

all:	$(NAME)

clean:
	rm -f $(wildcard *.o)
	rm -f */*.o

fclean:
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C get_next_line
	rm -f $(wildcard *.o)
	rm -f */*.o
	rm -f pipex.a

re:	fclean all