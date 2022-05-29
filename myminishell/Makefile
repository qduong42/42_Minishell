NAME = minishell

SRC = minishell.c

INCLUDE = minishell.h

LFT = ./lft

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@make bonus -C $(LFT)
	$(CC) $(CFLAGS) -o $(NAME) -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline $(OBJ) $(LFT)/libft.a


clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re