NAME = minishell

SRC = minishell.c main.c lexer.c testing_utils.c redirection.c utils/lists.c bool.c error_handeling.c tokenize.c

DIRS = PIPEX/libft/libft.a PIPEX/get_next_line/get_next_line.a PIPEX/pipex.a

INCLUDE = minishell.h

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -g

RM = rm -f

UNAME_S := $(shell uname -s)

LIB_MAC =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

LIB_LINUX = -lreadline

all: $(NAME)

$(NAME): $(OBJ)
ifeq ($(UNAME_S), Darwin)
	$(MAKE) -C PIPEX
	$(CC) $(CFLAGS) $(DIRS) -o $(NAME) -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline $(OBJ)
else
	$(MAKE) -C PIPEX
	$(CC) $(CFLAGS) $(DIRS) -o $(NAME) $(LIBS_LINUX) $(OBJ)   
endif

git add:
	git add $(INCLUDE) $(SRC) preplan/ Makefile

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)
	$(MAKE) clean -C PIPEX
	$(MAKE) fclean -C PIPEX

re: fclean all

.PHONY: all bonus clean fclean re
