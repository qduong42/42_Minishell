NAME := pipex.a

OBJS = main.o ignore.o
DIRS = libft/libft.a get_next_line/get_next_line.a

#	compilation
CFLAGS = -Werror -Wextra -Wall
CC = gcc
DEPS = pipex.h # only direct dependency

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(MAKE) -C get_next_line
	ar -rcs $(NAME) $(OBJS)

all:	$(NAME)

clean:
	rm -f $(wildcard *.o)

fclean:	clean
	rm -f pipex

re:	fclean all