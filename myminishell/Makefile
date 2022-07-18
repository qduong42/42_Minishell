NAME = minishell

SRC =  main.c utils/lists.c bool.c error_handeling.c

DIRS = PIPEX/libft/libft.a PIPEX/get_next_line/get_next_line.a PIPEX/pipex.a

#Parser files#
PARSER_SRC = tokenize.c lexer.c minishell.c redirection.c
PARSER_DIR = parser/
PARSER = $(addprefix $(PARSER_DIR),$(PARSER_SRC))
PARSER_OBJ = $(PARSER_SRC:.c=.o)

INCLUDE = minishell.h

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -g

RM = rm -f

UNAME_S := $(shell uname -s)

LIB_MAC =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

LIB_LINUX = -lreadline

all: $(NAME)

$(PARSER_OBJ): $(PARSER)
	$(CC) $(FLAGS) -c $(PARSER)

$(NAME): $(OBJ) $(PARSER_OBJ)
ifeq ($(UNAME_S), Darwin)

	$(MAKE) -C PIPEX
	$(CC) $(CFLAGS) $(DIRS) -o $(NAME) -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline $(OBJ) $(PARSER_OBJ)
else
	$(MAKE) -C PIPEX
	$(CC) $(CFLAGS) $(DIRS) -o $(NAME) $(LIBS_LINUX) $(OBJ) $(PARSER_OBJ)

endif

git add:
	git add $(INCLUDE) $(SRC) preplan/ Makefile

clean:
	$(RM) *.o
	$(MAKE) clean -C PIPEX/ 

fclean: clean
	$(MAKE) fclean -C PIPEX/ 
	$(RM) $(NAME)
	$(MAKE) clean -C PIPEX
	$(MAKE) fclean -C PIPEX

re: fclean all

.PHONY: all bonus clean fclean re
