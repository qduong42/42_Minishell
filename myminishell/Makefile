NAME = minishell

SRC = minishell.c main.c lexer.c testing_utils.c redirection.c utils/libft_utils.c utils/lists.c

INCLUDE = minishell.h

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f

UNAME_S := $(shell uname -s)

LIB_MAC =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

LIB_LINUX = -lreadline

all: $(NAME)

$(NAME): $(OBJ)
ifeq ($(UNAME_S), Darwin)
	$(CC) $(CFLAGS) -o $(NAME) -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline $(OBJ)
else
	$(CC) $(CFLAGS) -o $(NAME) $(LIBS_LINUX) $(OBJ)   
endif

git add:
	git add $(INCLUDE) $(SRC) preplan/ Makefile

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
