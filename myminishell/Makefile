NAME = minishell

SRC = minishell.c main.c lexer.c testing_utils.c redirection.c bool.c error_handeling.c cd.c echo.c

INCLUDE = minishell.h

LFT = ./lft

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
	@make -C $(LFT)
	@make bonus -C $(LFT)
	$(CC) $(CFLAGS) -o $(NAME) -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline $(OBJ) $(LFT)/libft.a
else
	@make -C $(LFT)
	@make bonus -C $(LFT)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBS_LINUX) $(OBJ)   $(LFT)/libft.a
endif

git add:
	git add $(INCLUDE) $(SRC) preplan/ Makefile

clean:
	$(RM) *.o
	@make clean -C $(LFT)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LFT)

re: fclean all

.PHONY: all bonus clean fclean re
