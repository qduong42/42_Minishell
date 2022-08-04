NAME = minishell

CC = gcc

LDFLAGS = -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
	CFLAGS = -D MAX_FDS=4096 -Wall -Wextra -Werror -g -I $(HOME)/goinfre/.brew/opt/readline/include/
else
	CFLAGS = -D MAX_FDS=1024 -Wall -Wextra -Werror -g -I $(HOME)/goinfre/.brew/opt/readline/include/
endif

SRC = main.c utils/lists.c frees.c utils/utils.c

OBJ = $(SRC:.c=.o)


#Parser files#
PARSER_DIR = parser/
PARSER_SRC = bool.c bool2.c bool3.c envp_res1.c envp_res2.c error_handling.c \
red_int.c redir_main.c redir_sub.c subpipes.c tokenize.c space_split.c
PARSER = $(addprefix $(PARSER_DIR),$(PARSER_SRC))
PARSER_OBJ = $(PARSER:.c=.o)

INCLUDE = minishell.h

DIRS = PIPEX/pipex.a PIPEX/get_next_line/get_next_line.a PIPEX/libft/libft.a

all:	$(NAME)

$(NAME): $(OBJ) $(PARSER_OBJ)
	$(MAKE) -C PIPEX
	$(CC) $(CFLAGS) $(OBJ) $(PARSER_OBJ) $(LDFLAGS) $(DIRS) -o $(NAME)

clean:
	$(MAKE) clean -C PIPEX/
	$(RM) */*.o
	$(RM) */*/*.o
	$(RM) */*/*/*.o
	$(RM) $(OBJ) $(PARSER_OBJ)

fclean: clean
	$(MAKE) fclean -C PIPEX/
	$(RM) */*.o
	$(RM) */*/*.o
	$(RM) */*/*/*.o
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
