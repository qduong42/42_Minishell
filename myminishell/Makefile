NAME = minishell

CC = gcc

LDFLAGS = -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

CFLAGS = -Wall -Wextra -Werror -g -I $(HOME)/goinfre/.brew/opt/readline/include/

SRC = main.c utils/lists.c bool.c error_handling.c

OBJ = $(SRC:.c=.o)

#Parser files#
PARSER_DIR = parser/
PARSER_SRC = tokenize.c lexer.c minishell.c redirection.c
PARSER = $(addprefix $(PARSER_DIR),$(PARSER_SRC))
PARSER_OBJ = $(PARSER:.c=.o)

INCLUDE = minishell.h

DIRS = PIPEX/pipex.a PIPEX/get_next_line/get_next_line.a PIPEX/libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(PARSER_OBJ)
	$(MAKE) -C PIPEX
	$(CC) $(CFLAGS) $(OBJ) $(PARSER_OBJ) $(LDFLAGS) $(DIRS) -o $(NAME)

clean:
	$(MAKE) clean -C PIPEX/
	$(RM) $(OBJ) $(PARSER_OBJ)

fclean: clean
	$(MAKE) fclean -C PIPEX/
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
