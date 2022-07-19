NAME := pipex.a

SRCS = buildins/cd.c buildins/echo.c buildins/export.c buildins/unset.c ignore.c pipex.c
OBJS = cd.o echo.o export.o unset.o ignore.o pipex.o
DIRS = libft/libft.a get_next_line/get_next_line.a

#	compilation
CFLAGS = -Werror -Wextra -Wall -g
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

fclean:
	rm -f $(wildcard *.o)
	rm -f pipex.a

re:	fclean all